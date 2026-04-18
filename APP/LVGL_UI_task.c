#include "LVGL_UI_task.h"
#include "esp8266.h"
#include "gpio.h"
#include "uart3.h"
#include "stdio.h"
#include <stdlib.h>
#include "lvgl.h"                // 它为整个LVGL提供了更完整的头文件引用
#include "lv_port_disp.h"        // LVGL的显示支持
#include "lv_port_indev.h"       // LVGL的触屏支持
#include "gui_guider.h"
#include "events_init.h"

lv_ui guider_ui;






QueueHandle_t UI_queue_handle;    //UI消息队列句柄


/* 丢包总计数（任务发送失败 / 定时器发送失败） */
static volatile uint32_t g_drop_task_send_total = 0;
static volatile uint32_t g_drop_timer_send_total = 0;

/* 丢包分类型统计（数组下标对应 ui_msg_type_t） */
static volatile uint32_t g_drop_task_send_by_type[UI_MSG_MAX] = {0};
static volatile uint32_t g_drop_timer_send_by_type[UI_MSG_MAX] = {0};

void LVGL_UI_Queue_Init(void)
{
      UI_queue_handle = xQueueCreate(LVGL_UI_QUEUE_LENGTH, sizeof(UI_msg_typedef));  // 创建一个长度为10，元素大小为UI_msg_type_typdef的队列
      if (UI_queue_handle == NULL) {
         printf("Failed to create UI message queue\r\n");
      }
}




void LVGL_UI_task(void const * argument)
{

   LVGL_UI_Queue_Init();   // 初始化UI消息队列
	
	setup_ui(&guider_ui);           // 初始化 UI
	events_init(&guider_ui);       // 初始化 事件
	
	
//   UBaseType_t uxFreeStack;

	for(;;)
	{
		lv_timer_handler();
//      uxFreeStack = uxTaskGetStackHighWaterMark(NULL);
//      printf("LVGL_UI_task Free Stack: %lu words\r\n", uxFreeStack);
		osDelay(pdMS_TO_TICKS(5));
	}
	
}




/* 判断消息类型是否有效，防止数组越界 */
static inline bool ui_msg_type_valid(UI_msg_type_typdef t)
{
    return  (t < UI_MSG_MAX);
}


void UI_Send_msg_from_task(const UI_msg_typedef *msg, TickType_t timeout)
{
   if(xQueueSend(UI_queue_handle, msg, timeout) != pdPASS)
   {
      g_drop_task_send_total++;   // 任务发送失败的总计数自增
      if(msg!=NULL&&ui_msg_type_valid(msg->msg_type))
      {
         g_drop_task_send_by_type[msg->msg_type]++;  // 根据消息类型统计任务发送失败的分类型计数自增
      }

   }

}


void UI_Send_msg_from_timer(const UI_msg_typedef *msg)
{
   if(xQueueSend(UI_queue_handle, msg, 0) != pdPASS)
   {
      g_drop_timer_send_total++;   // 定时器发送失败的总计数自增
      if(msg!=NULL&&ui_msg_type_valid(msg->msg_type))
      {
         g_drop_timer_send_by_type[msg->msg_type]++;  // 根据消息类型统计定时器发送失败的分类型计数自增
      }

   }

}


