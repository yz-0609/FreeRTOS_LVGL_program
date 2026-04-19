#include "LVGL_UI_task.h"
#include "esp8266.h"
#include "gpio.h"
#include "uart3.h"
#include "stdio.h"
#include <stdlib.h>
#include "lvgl.h"                // ��Ϊ����LVGL�ṩ�˸�������ͷ�ļ�����
#include "lv_port_disp.h"        // LVGL����ʾ֧��
#include "lv_port_indev.h"       // LVGL�Ĵ���֧��
#include "gui_guider.h"
#include "events_init.h"

#define UI_MAX_MSG_PER_CYCLE 10U
#define UI_DEGREE_SYMBOL     "\xC2\xB0"

lv_ui guider_ui;






QueueHandle_t UI_queue_handle;    //UI��Ϣ���о��


/* �����ܼ�����������ʧ�� / ��ʱ������ʧ�ܣ� */
static volatile uint32_t g_drop_task_send_total = 0;
static volatile uint32_t g_drop_timer_send_total = 0;

/* ����������ͳ�ƣ������±��Ӧ ui_msg_type_t�� */
static volatile uint32_t g_drop_task_send_by_type[UI_MSG_MAX] = {0};
static volatile uint32_t g_drop_timer_send_by_type[UI_MSG_MAX] = {0};

/* �ж���Ϣ�����Ƿ���Ч����ֹ����Խ�� */
static bool ui_msg_type_valid(UI_msg_type_typdef t)
{
    return  (t < UI_MSG_MAX);
}

static void ui_apply_time_update(const UI_msg_typedef *msg)
{
      if(msg == NULL)
      {
            return;
      }

      lv_label_set_text_fmt(guider_ui.time_screen_date_label,
                            "%04u.%02u.%02u",
                            (unsigned int)msg->msg_data.time_msg.year,
                            (unsigned int)msg->msg_data.time_msg.month,
                            (unsigned int)msg->msg_data.time_msg.day);

      lv_label_set_text_fmt(guider_ui.time_screen_time_label,
                            "%02u:%02u:%02u",
                            (unsigned int)msg->msg_data.time_msg.hour,
                            (unsigned int)msg->msg_data.time_msg.min,
                            (unsigned int)msg->msg_data.time_msg.sec);
}

static void ui_apply_weather_update(const UI_msg_typedef *msg)
{
      if(msg == NULL)
      {
            return;
      }

      lv_label_set_text_fmt(guider_ui.weaher_screen_location_label,
                            "%.*s",
                            (int)sizeof(msg->msg_data.weather_msg.city),
                            msg->msg_data.weather_msg.city);
      lv_label_set_text_fmt(guider_ui.weaher_screen_weather_label,
                            "%.*s",
                            (int)sizeof(msg->msg_data.weather_msg.weather),
                            msg->msg_data.weather_msg.weather);
}

static void ui_apply_dht11_update(const UI_msg_typedef *msg)
{
      if(msg == NULL)
      {
            return;
      }

      lv_label_set_text_fmt(guider_ui.t_h_screen_temp_label,
                            "%u.%u" UI_DEGREE_SYMBOL "C",
                            (unsigned int)msg->msg_data.dht11_msg.dht11_temperature_int,
                            (unsigned int)msg->msg_data.dht11_msg.dht11_temperature_dec);

      lv_label_set_text_fmt(guider_ui.t_h_screen_humidity_label,
                            "%u.%u%%RH",
                            (unsigned int)msg->msg_data.dht11_msg.dht11_humidity_int,
                            (unsigned int)msg->msg_data.dht11_msg.dht11_humidity_dec);
}

static void ui_process_msg(const UI_msg_typedef *msg)
{
      if((msg == NULL) || !ui_msg_type_valid(msg->msg_type))
      {
            return;
      }

      switch(msg->msg_type)
      {
            case UI_TIME_UPDATE:
                  ui_apply_time_update(msg);
                  break;
            case UI_WEATHER_UPDATE:
                  ui_apply_weather_update(msg);
                  break;
            case UI_DHT11_UPDATE:
                  ui_apply_dht11_update(msg);
                  break;
            default:
                  break;
      }
}

void LVGL_UI_Queue_Init(void)
{
      UI_queue_handle = xQueueCreate(LVGL_UI_QUEUE_LENGTH, sizeof(UI_msg_typedef));  // ����һ������Ϊ10��Ԫ�ش�СΪUI_msg_type_typdef�Ķ���
      if (UI_queue_handle == NULL) {
         printf("Failed to create UI message queue\r\n");
      }
}




void LVGL_UI_task(void const * argument)
{
   UI_msg_typedef ui_msg;

   LVGL_UI_Queue_Init();   // ��ʼ��UI��Ϣ����
	
	setup_ui(&guider_ui);           // ��ʼ�� UI
	events_init(&guider_ui);       // ��ʼ�� �¼�
	
	
//   UBaseType_t uxFreeStack;

	for(;;)
	{
            uint32_t handled_msgs = 0;
            while((handled_msgs < UI_MAX_MSG_PER_CYCLE) &&
                  (xQueueReceive(UI_queue_handle, &ui_msg, 0) == pdPASS))
            {
                  ui_process_msg(&ui_msg);
                  handled_msgs++;
            }

		lv_timer_handler();
//      uxFreeStack = uxTaskGetStackHighWaterMark(NULL);
//      printf("LVGL_UI_task Free Stack: %lu words\r\n", uxFreeStack);
		osDelay(pdMS_TO_TICKS(5));
	}
	
}

void UI_Send_msg_from_task(const UI_msg_typedef *msg, TickType_t timeout)
{
   if((UI_queue_handle == NULL) || (msg == NULL))
   {
      return;
   }

   if(xQueueSend(UI_queue_handle, msg, timeout) != pdPASS)
   {
      g_drop_task_send_total++;   // ������ʧ�ܵ��ܼ�������
      if(msg!=NULL&&ui_msg_type_valid(msg->msg_type))
      {
         g_drop_task_send_by_type[msg->msg_type]++;  // ������Ϣ����ͳ��������ʧ�ܵķ����ͼ�������
      }

   }

}


void UI_Send_msg_from_timer(const UI_msg_typedef *msg)
{
   if((UI_queue_handle == NULL) || (msg == NULL))
   {
      return;
   }

   if(xQueueSend(UI_queue_handle, msg, 0) != pdPASS)
   {
      g_drop_timer_send_total++;   // ��ʱ������ʧ�ܵ��ܼ�������
      if(msg!=NULL&&ui_msg_type_valid(msg->msg_type))
      {
         g_drop_timer_send_by_type[msg->msg_type]++;  // ������Ϣ����ͳ�ƶ�ʱ������ʧ�ܵķ����ͼ�������
      }

   }

}
