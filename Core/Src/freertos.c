/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "semphr.h"
#include "stream_buffer.h"
#include "DHT11_task.h"
#include "uart3.h"
#include "weather_Time_task.h"
#include "esp8266.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
//手动定义事件标志组

//EventGroupHandle_t eventgroup_handle;


/* USER CODE END Variables */
osThreadId taskLED_REDHandle;
osThreadId DHT11Handle;
osThreadId WeatherHandle;
osThreadId TimeHandle;
osThreadId LVGL_UIHandle;
osTimerId myTimer01Handle;
osMutexId tx_mutexHandle;
osMutexId esp_mutexHandle;
osSemaphoreId tx_space_semHandle;
osSemaphoreId esp_tx_space_semHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartTaskLED_RED(void const * argument);
void DHT11_task(void const * argument);
void Weather_task(void const * argument);
void Time_task(void const * argument);
void LVGL_UI_task(void const * argument);
void Callback01(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* GetTimerTaskMemory prototype (linked to static allocation support) */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/* USER CODE BEGIN GET_TIMER_TASK_MEMORY */
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];

void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize )
{
  *ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
  *ppxTimerTaskStackBuffer = &xTimerStack[0];
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
  /* place for user code */
}
/* USER CODE END GET_TIMER_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* definition and creation of tx_mutex */
  osMutexDef(tx_mutex);
  tx_mutexHandle = osMutexCreate(osMutex(tx_mutex));

  /* definition and creation of esp_mutex */
  osMutexDef(esp_mutex);
  esp_mutexHandle = osMutexCreate(osMutex(esp_mutex));

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of tx_space_sem */
  osSemaphoreDef(tx_space_sem);
  tx_space_semHandle = osSemaphoreCreate(osSemaphore(tx_space_sem), 1);

  /* definition and creation of esp_tx_space_sem */
  osSemaphoreDef(esp_tx_space_sem);
  esp_tx_space_semHandle = osSemaphoreCreate(osSemaphore(esp_tx_space_sem), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* definition and creation of myTimer01 */
  osTimerDef(myTimer01, Callback01);
  myTimer01Handle = osTimerCreate(osTimer(myTimer01), osTimerPeriodic, NULL);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of taskLED_RED */
  osThreadDef(taskLED_RED, StartTaskLED_RED, osPriorityNormal, 0, 128);
  taskLED_REDHandle = osThreadCreate(osThread(taskLED_RED), NULL);

  /* definition and creation of DHT11 */
  osThreadDef(DHT11, DHT11_task, osPriorityNormal, 0, 128);
  DHT11Handle = osThreadCreate(osThread(DHT11), NULL);

  /* definition and creation of Weather */
  osThreadDef(Weather, Weather_task, osPriorityNormal, 0, 256);
  WeatherHandle = osThreadCreate(osThread(Weather), NULL);

  /* definition and creation of Time */
  osThreadDef(Time, Time_task, osPriorityNormal, 0, 256);
  TimeHandle = osThreadCreate(osThread(Time), NULL);

  /* definition and creation of LVGL_UI */
  osThreadDef(LVGL_UI, LVGL_UI_task, osPriorityAboveNormal, 0, 2048);
  LVGL_UIHandle = osThreadCreate(osThread(LVGL_UI), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  //手动创建事件标志组
  
//  eventgroup_handle=xEventGroupCreate();
  uart3_rtos_init();   //注意调用！！！，否则会卡死程序
  
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartTaskLED_RED */
/**
  * @brief  Function implementing the taskLED_RED thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartTaskLED_RED */
void StartTaskLED_RED(void const * argument)
{
  /* USER CODE BEGIN StartTaskLED_RED */
  /* Infinite loop */
  for(;;)
  {
//	  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_5);
//	  printf("红色LED闪烁\r\n");
      osDelay(1);
  }
  /* USER CODE END StartTaskLED_RED */
}

/* USER CODE BEGIN Header_DHT11_task */
/**
* @brief Function implementing the DHT11 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_DHT11_task */
__weak void DHT11_task(void const * argument)
{
  /* USER CODE BEGIN DHT11_task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END DHT11_task */
}

/* USER CODE BEGIN Header_Weather_task */
/**
* @brief Function implementing the Weather thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Weather_task */
__weak void Weather_task(void const * argument)
{
  /* USER CODE BEGIN Weather_task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Weather_task */
}

/* USER CODE BEGIN Header_Time_task */
/**
* @brief Function implementing the Time thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Time_task */
__weak void Time_task(void const * argument)
{
  /* USER CODE BEGIN Time_task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Time_task */
}

/* USER CODE BEGIN Header_LVGL_UI_task */
/**
* @brief Function implementing the LVGL_UI thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LVGL_UI_task */
__weak void LVGL_UI_task(void const * argument)
{
  /* USER CODE BEGIN LVGL_UI_task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END LVGL_UI_task */
}

/* Callback01 function */
void Callback01(void const * argument)
{
  /* USER CODE BEGIN Callback01 */
  time_enter();
  /* USER CODE END Callback01 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
