#include "DHT11_task.h"
#include "gpio.h"
#include "string.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "LVGL_UI_task.h"




char data[5]={0};      //用于存储获得的数据

void DHT11_GPIO_OUT(void)
{
	//__HAL_RCC_GPIOC_CLK_ENABLE();    注意此函数初始化过PC5所以不用再开启时钟
    GPIO_InitTypeDef GPIO_InitStruct = {0};          // 引脚工作模式 初始化结构体
    GPIO_InitStruct.Pin = DHT11_PIN;                 // 引脚编号
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;      // 引脚工作模式：推挽输出
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;    // 引脚电平反转速度
    HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStruct);     // 初始化	
	
}

void DHT11_GPIO_IN(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};          // 引脚工作模式 初始化结构体
    GPIO_InitStruct.Pin = DHT11_PIN;                 // 引脚编号
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;          // 引脚工作模式：输入
    GPIO_InitStruct.Pull = GPIO_PULLUP;              // 打开上拉，引脚闲时为高电平
    HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStruct);     // 初始化
}


// 本地US粗略延时函数，减少移植时对外部文件依赖；
static void delay_us(uint32_t us)
{
    uint16_t i = 0;
    while (us--)
    {
        i = 30;
        while (i--);
    }
}




void DHT11_start(void)
{

	DHT11_GPIO_OUT();
	DHT11_OUT(1);
	DHT11_OUT(0);
	vTaskDelay(pdMS_TO_TICKS(25));   //rtos 阻塞延时交出CPU
	
	taskENTER_CRITICAL();   //通信时序微秒级操作，加入临界代码段保护

	DHT11_OUT(1);                //拉低25ms
	
	DHT11_GPIO_IN();             //切换输入模式
	
	

	while(DHT11_READ);           //等待拉低
	while(!DHT11_READ);          //等待拉高
	while(DHT11_READ);           //等待拉低


}


uint8_t DHT11_read_byte(void)
{
	uint8_t i=0;
	uint8_t temp=0;
	uint8_t read_data=0;

	
	for(i=0;i<8;i++)
	{
		while(!DHT11_READ);          //等待拉高

		delay_us(50);
		if(DHT11_READ==1)
		{
			temp=1;
			while(DHT11_READ);           //等待拉低

		}
		else
		{
			temp=0;
		}
		read_data=read_data<<1;       //read_data左移一位
		read_data|=temp;              //将temp的值塞进空位

	}
	return read_data;
}






void DHT11_task(void const * argument)
{
  uint8_t result[4] = {0};  // 存储最终结果的数组
  UI_msg_typedef DHT11_msg;              // 定义UI消息结构体变量

  for(;;)
  {
	uint8_t i=0;
	DHT11_start();

	DHT11_GPIO_IN();
	for(i=0;i<5;i++)
	{
		data[i]=DHT11_read_byte();
	}
	
	taskEXIT_CRITICAL();    //读数据完毕退出临时代码段
	
	if(data[0]+data[1]+data[2]+data[3]==data[4])
	{
		memcpy(result,data,4);
		// 构造UI消息
		DHT11_msg.msg_type = UI_DHT11_UPDATE;  // 设置消息类型为DHT11数据更新
		DHT11_msg.msg_data.dht11_msg.dht11_humidity_int = data[0];
		DHT11_msg.msg_data.dht11_msg.dht11_humidity_dec = data[1];
		DHT11_msg.msg_data.dht11_msg.dht11_temperature_int = data[2];
		DHT11_msg.msg_data.dht11_msg.dht11_temperature_dec = data[3];
		DHT11_msg.timestamp = xTaskGetTickCount()*portTICK_PERIOD_MS;  // 获取当前系统时间戳
		// 将消息发送到UI任务，等待10ms
		UI_Send_msg_from_task(&DHT11_msg, pdMS_TO_TICKS(10)); 
		// printf("湿度：%d.%dRH",data[0],data[1]);
		// printf("温度：%d.%d℃\r\n",data[2],data[3]);
	}	
    osDelay(pdMS_TO_TICKS(3000));
  }
  /* USER CODE END DHT11_task */
}

