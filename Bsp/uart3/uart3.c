#include "uart3.h"
#include "main.h"
#include "usart.h"
#include "string.h"
#include "stdio.h"

/* 引入 FreeRTOS 头文件 */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "stream_buffer.h"
#include "cmsis_os.h"


extern osMutexId tx_mutexHandle;
extern osSemaphoreId tx_space_semHandle;

extern osMutexId esp_mutexHandle;
extern osSemaphoreId esp_tx_space_semHandle;


/*************************************串口一************************************/
/* ================== 发送专区变量 ================== */
#define UART1_TX_BUFFER_SIZE      256

uint8_t uart1_tx_buffer[UART1_TX_BUFFER_SIZE];
volatile uint16_t uart1_tx_readIndex = 0;
volatile uint16_t uart1_tx_writeIndex = 0;
volatile uint8_t uart1_tx_busy = 0;
volatile uint16_t uart1_current_tx_len = 0;

void Uart1_TxProcess(void); // 提前声明




/*************************************串口三************************************/

/* ================== 接收专区变量 ================== */
#define DMA_RX_BUF_SIZE     512
#define MAX_RX_FRAME_SIZE   512

static uint8_t dma_rx_buffer[DMA_RX_BUF_SIZE]; // 硬件 DMA 专用数组
static uint16_t old_pos = 0;            // 记录上次 DMA 处理到的位置

// RTOS 接收专用流缓冲区
static StreamBufferHandle_t rx_stream_buffer;

// 提供给外部提取数据的静态帧缓存
static uint8_t  current_rx_frame[MAX_RX_FRAME_SIZE];
static uint16_t current_rx_len = 0;


/* ================== 发送专区变量 ================== */
#define TX_BUFFER_SIZE      512

uint8_t uart3_tx_buffer[TX_BUFFER_SIZE];
volatile uint16_t uart3_tx_readIndex = 0;
volatile uint16_t uart3_tx_writeIndex = 0;
volatile uint8_t uart3_tx_busy = 0;
volatile uint16_t uart3_current_tx_len = 0;

//// RTOS 发送保护资源
//static SemaphoreHandle_t tx_mutex;      // 防止多任务争抢发送
//static SemaphoreHandle_t tx_space_sem;  // 缓冲满时，阻塞任务等待 DMA 发送腾出空间

void Uart3_TxProcess(void); // 提前声明



/*************************************串口一************************************/




/**
 * @brief 计算待发送的数据长度
 */
uint16_t Uart1_TxGetLength(void) {
    return (uart1_tx_writeIndex + UART1_TX_BUFFER_SIZE - uart1_tx_readIndex) % UART1_TX_BUFFER_SIZE;
}

/**
 * @brief 计算发送缓冲区剩余空间
 */
uint16_t Uart1_TxGetRemain(void) {
    return UART1_TX_BUFFER_SIZE - 1 - Uart1_TxGetLength();
}

/**
 * @brief 向发送环形缓冲区写入数据，并触发DMA发送 (多任务绝对安全)
 */
uint16_t Uart1_Send_RTOS(uint8_t *data, uint16_t length) {
    if (length == 0) return 0;

    // 获取互斥锁，确保同一时刻只有一个任务在往环形队列里压数据
    xSemaphoreTake(tx_mutexHandle, portMAX_DELAY);

    uint16_t written = 0;
    while (written < length) 
    {
        uint16_t remain = Uart1_TxGetRemain();
        
        // 如果软件缓冲区满了怎么办？
        if (remain == 0) {
            Uart1_TxProcess(); // 确保 DMA 正在工作
            // 挂起当前任务，让出 CPU，等待 DMA 完成部分发送后释放信号量唤醒
           // 如果 DMA 启动失败没有中断，任务会在 10ms 后醒来，再次 continue 重新尝试启动 DMA，彻底告别死锁！
             // 【核心修复】：挂起前先释放互斥锁，让出发送权给高优先级任务
            xSemaphoreGive(tx_mutexHandle);
            
            // 挂起当前任务，等待 DMA 发送完成释放空间
            xSemaphoreTake(tx_space_semHandle, pdMS_TO_TICKS(10));
            
            // 【核心修复】：醒来后，重新获取互斥锁，继续未完成的发送
            xSemaphoreTake(tx_mutexHandle, portMAX_DELAY);
            continue; // 被唤醒后重新计算剩余空间
        }
        
        uint16_t to_write = (length - written) > remain ? remain : (length - written);
        uint16_t tail_len = UART1_TX_BUFFER_SIZE - uart1_tx_writeIndex;
        
        if (to_write <= tail_len) {
            memcpy(uart1_tx_buffer + uart1_tx_writeIndex, data + written, to_write);
        } else {
            memcpy(uart1_tx_buffer + uart1_tx_writeIndex, data + written, tail_len);
            memcpy(uart1_tx_buffer, data + written + tail_len, to_write - tail_len);
        }
        
        uart1_tx_writeIndex = (uart1_tx_writeIndex + to_write) % UART1_TX_BUFFER_SIZE;
        written += to_write;
    }
    
    // 触发底层硬件 DMA 发送
    Uart1_TxProcess();
    
    // 释放互斥锁
    xSemaphoreGive(tx_mutexHandle);
    return length;
}

/**
 * @brief 内部DMA发送处理函数，处理内存连续性与HAL库锁
 */
void Uart1_TxProcess(void) {
    uint32_t isr_status = 0;
    
    // 1. 判断当前是否处于中断环境中
    BaseType_t in_isr = xPortIsInsideInterrupt();
    
    // 2. 根据环境采取不同的临界区保护
    if (in_isr) {
        isr_status = taskENTER_CRITICAL_FROM_ISR(); // 中断专用临界区
    } else {
        taskENTER_CRITICAL();                       // 任务专用临界区
    }

    // 3. 业务逻辑：判断是否忙碌或无数据
    if (uart1_tx_busy || Uart1_TxGetLength() == 0) {
        if (in_isr) {
            taskEXIT_CRITICAL_FROM_ISR(isr_status);
        } else {
            taskEXIT_CRITICAL();
        }
        return; 
    }
    uart1_tx_busy = 1; 

    // 5. 计算并启动发送
    uint16_t len = Uart1_TxGetLength();
    uint16_t tail_len = UART1_TX_BUFFER_SIZE - uart1_tx_readIndex;

    if (len <= tail_len) {
        uart1_current_tx_len = len;      
    } else {
        uart1_current_tx_len = tail_len; 
    }

    if (HAL_UART_Transmit_DMA(&huart1, &uart1_tx_buffer[uart1_tx_readIndex], uart1_current_tx_len) != HAL_OK) {     
        uart1_tx_busy = 0; 
    }
    
    // 4. 退出临界区
    if (in_isr) {
        taskEXIT_CRITICAL_FROM_ISR(isr_status);
    } else {
        taskEXIT_CRITICAL();
    }
    
}


/* ================== 3. printf 重定向 ================== */
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
    // 重定向 printf，完美调用线程安全的发送函数
    Uart1_Send_RTOS((uint8_t *)&ch, 1);
    return ch;
}







/*************************************串口三************************************/



/* ================== 1. RTOS 串口初始化函数 ================== */
/**
 * @brief 串口一 RTOS环境 初始化函数
 */
void uart3_rtos_init(void)
{
    // 1. 创建 RTOS 资源
    rx_stream_buffer = xStreamBufferCreate(MAX_RX_FRAME_SIZE * 2, 1); // 触发阈值1字节
//    tx_mutex = xSemaphoreCreateMutex();
//    tx_space_sem = xSemaphoreCreateBinary();

    // 2. 启动串口 DMA 接收 + 空闲中断 (???须确保 CubeMX 里将 DMA 设为了 Circular 模式)
    HAL_UARTEx_ReceiveToIdle_DMA(&huart3, dma_rx_buffer, DMA_RX_BUF_SIZE);
    
    // 3. 关闭 DMA 的过半中断(Half Transfer)，只留 Idle 和 Full 中断
    __HAL_DMA_DISABLE_IT(huart3.hdmarx, DMA_IT_HT);
}


/* ================== 2. 外部请求的 接收接口 函数 ================== */

/**
 * @brief [核心] 阻塞等待串口数据到来 
 * @param timeoutMs RTOS阻塞超时时间
 * @return 接收到的字节数
 */
uint16_t UART3_WaitForRxFrame(uint32_t timeoutMs)
{
    // 挂起当前任务，直到 StreamBuffer 中有数据
    size_t len = xStreamBufferReceive(rx_stream_buffer, 
                                      current_rx_frame, 
                                      MAX_RX_FRAME_SIZE, 
                                      pdMS_TO_TICKS(timeoutMs));
    
    if (len > 0) {
        // 如果有数据，尝试把 StreamBuffer 里的剩余字节一并读出（非阻塞）
        //再读一次，读出剩余的字节（如果有的话），拼接到当前帧后面
        size_t more_len = xStreamBufferReceive(rx_stream_buffer, 
                                               current_rx_frame + len, 
                                               MAX_RX_FRAME_SIZE - len, 
                                               0);
        current_rx_len = len + more_len;
    } else {
        current_rx_len = 0;
    }
    
    return current_rx_len;
}

uint16_t UART3_GetRxNum(void) {
    return current_rx_len;
}

uint8_t *UART3_GetRxData(void) {
    return current_rx_frame;
}

void UART3_ClearRx(void) {
    current_rx_len = 0;
}


/* ================== 3. 发送相关函数 (线程安全改造) ================== */

/**
 * @brief 计算待发送的数据长度
 */
uint16_t Uart3_TxGetLength(void) {
    return (uart3_tx_writeIndex + TX_BUFFER_SIZE - uart3_tx_readIndex) % TX_BUFFER_SIZE;
}

/**
 * @brief 计算发送缓冲区剩余空间
 */
uint16_t Uart3_TxGetRemain(void) {
    return TX_BUFFER_SIZE - 1 - Uart3_TxGetLength();
}

/**
 * @brief 向发送环形缓冲区写入数据，并触发DMA发送 (多任务绝对安全)
 */
uint16_t Uart3_Send_RTOS(uint8_t *data, uint16_t length) {
    if (length == 0) return 0;

    // 获取互斥锁，确保同一时刻只有一个任务在往环形队列里压数据
    xSemaphoreTake(esp_mutexHandle, portMAX_DELAY);

    uint16_t written = 0;
    while (written < length) 
    {
        uint16_t remain = Uart3_TxGetRemain();
        
        // 如果软件缓冲区满了怎么办？
        if (remain == 0) {
            Uart3_TxProcess(); // 确保 DMA 正在工作
            // 挂起当前任务，让出 CPU，等待 DMA 完成部分发送后释放信号量唤醒
           // 如果 DMA 启动失败没有中断，任务会在 10ms 后醒来，再次 continue 重新尝试启动 DMA，彻底告别死锁！
			 // 【核心修复】：挂起前先释放互斥锁，让出发送权给高优先级任务
            xSemaphoreGive(esp_mutexHandle);
            
            // 挂起当前任务，等待 DMA 发送完成释放空间
            xSemaphoreTake(esp_tx_space_semHandle, pdMS_TO_TICKS(10));
            
            // 【核心修复】：醒来后，重新获取互斥锁，继续未完成的发送
            xSemaphoreTake(esp_mutexHandle, portMAX_DELAY);
            continue; // 被唤醒后重新计算剩余空间
        }
        
        uint16_t to_write = (length - written) > remain ? remain : (length - written);
        uint16_t tail_len = TX_BUFFER_SIZE - uart3_tx_writeIndex;
        
        if (to_write <= tail_len) {
            memcpy(uart3_tx_buffer + uart3_tx_writeIndex, data + written, to_write);
        } else {
            memcpy(uart3_tx_buffer + uart3_tx_writeIndex, data + written, tail_len);
            memcpy(uart3_tx_buffer, data + written + tail_len, to_write - tail_len);
        }
        
        uart3_tx_writeIndex = (uart3_tx_writeIndex + to_write) % TX_BUFFER_SIZE;
        written += to_write;
    }
    
    // 触发底层硬件 DMA 发送
    Uart3_TxProcess();
    
    // 释放互斥锁
    xSemaphoreGive(esp_mutexHandle);
    return length;
}

/**
 * @brief 内部DMA发送处理函数，处理内存连续性与HAL库锁
 */
void Uart3_TxProcess(void) {
    uint32_t isr_status = 0;
    
    // 1. 判断当前是否处于中断环境中
    BaseType_t in_isr = xPortIsInsideInterrupt();
    
    // 2. 根据环境采取不同的临界区保护
    if (in_isr) {
        isr_status = taskENTER_CRITICAL_FROM_ISR(); // 中断专用临界区
    } else {
        taskENTER_CRITICAL();                       // 任务专用临界区
    }

    // 3. 业务逻辑：判断是否忙碌或无数据
    if (uart3_tx_busy || Uart3_TxGetLength() == 0) {
        if (in_isr) {
            taskEXIT_CRITICAL_FROM_ISR(isr_status);
        } else {
            taskEXIT_CRITICAL();
        }
        return; 
    }
    uart3_tx_busy = 1; 

    // 5. 计算并启动发送
    uint16_t len = Uart3_TxGetLength();
    uint16_t tail_len = TX_BUFFER_SIZE - uart3_tx_readIndex;

    if (len <= tail_len) {
        uart3_current_tx_len = len;      
    } else {
        uart3_current_tx_len = tail_len; 
    }

    if (HAL_UART_Transmit_DMA(&huart3, &uart3_tx_buffer[uart3_tx_readIndex], uart3_current_tx_len) != HAL_OK) {     
        uart3_tx_busy = 0; 
    }
	
	    // 4. 退出临界区
    if (in_isr) {
        taskEXIT_CRITICAL_FROM_ISR(isr_status);
    } else {
        taskEXIT_CRITICAL();
    }
	
}



/* ================== 5. 串口中断回调函数 ================== */

/**
 * @brief HAL库 接收事件回调函数 (涵盖IDLE空闲中断、全满中断)
 */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)    
{
    if(huart == &huart3)
    {
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        uint16_t data_length = 0;
        
        // 1. 提取当前数据
        if (Size > old_pos) 
        {
            data_length = Size - old_pos;
            if (data_length > 0) {
                xStreamBufferSendFromISR(rx_stream_buffer, &dma_rx_buffer[old_pos], data_length, &xHigherPriorityTaskWoken);
            }
        }
        else if (Size < old_pos) 
        {
            data_length = DMA_RX_BUF_SIZE - old_pos;
            if (data_length > 0) {
                xStreamBufferSendFromISR(rx_stream_buffer, &dma_rx_buffer[old_pos], data_length, &xHigherPriorityTaskWoken);
            }
            if (Size > 0) {
                xStreamBufferSendFromISR(rx_stream_buffer, &dma_rx_buffer[0], Size, &xHigherPriorityTaskWoken);
            }
        }
        
        old_pos = Size;
        
        // 2. 【核心防断流补丁】
        // 检查 HAL 库是否自作聪明把接收状态改回了 READY (关闭了 DMA)
        // 如果被关了，必须在 1 微秒内立刻重启，防止下一波数据漏接！
        if (huart->RxState == HAL_UART_STATE_READY)
        {
            HAL_UARTEx_ReceiveToIdle_DMA(&huart3, dma_rx_buffer, DMA_RX_BUF_SIZE);
            __HAL_DMA_DISABLE_IT(huart3.hdmarx, DMA_IT_HT);
            old_pos = 0; // 重启后，硬件指针必回 0，软件记录也要跟着回 0
        }
        
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}	

/**
 * @brief HAL库 串口硬件错误回调函数 (防死机自动复活机制)
 */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    if (huart == &huart3) 
    {
        // 遇到极高频的溢出(ORE)错误，底层会自动关闭 DMA
        // 必须重新启动，并且【极其重要：必须把 old_pos 归零！】
        HAL_UARTEx_ReceiveToIdle_DMA(&huart3, dma_rx_buffer, DMA_RX_BUF_SIZE);
        __HAL_DMA_DISABLE_IT(huart3.hdmarx, DMA_IT_HT); 
        old_pos = 0; // 不归零会导致提取出几百个乱码 / 空字符
    }	
}
/**
 * @brief HAL库 串口发送完成回调函数 (由DMA TX完成中断触发)
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
	
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	
	
    if (huart == &huart1) {
        

        uart1_tx_readIndex = (uart1_tx_readIndex + uart1_current_tx_len) % UART1_TX_BUFFER_SIZE;
        uart1_tx_busy = 0;
        
        // 释放信号量，通知那些因为发送缓冲区满而挂起的任务
        xSemaphoreGiveFromISR(tx_space_semHandle, &xHigherPriorityTaskWoken);
        
        if (Uart1_TxGetLength() > 0) {
            Uart1_TxProcess(); 
        }


    }
	
	
	
	
	
	
	    else if (huart == &huart3) {
        

        uart3_tx_readIndex = (uart3_tx_readIndex + uart3_current_tx_len) % TX_BUFFER_SIZE;
        uart3_tx_busy = 0;
        
        // 释放信号量，通知那些因为发送缓冲区满而挂起的任务
        xSemaphoreGiveFromISR(esp_tx_space_semHandle, &xHigherPriorityTaskWoken);
        
        if (Uart3_TxGetLength() > 0) {
            Uart3_TxProcess(); 
        }

    }
		
	        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

}





