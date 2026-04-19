#include "LVGL_UI_task.h"
#include "esp8266.h"
#include "gpio.h"
#include "uart3.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include "lvgl.h"                // ��Ϊ����LVGL�ṩ�˸�������ͷ�ļ�����
#include "lv_port_disp.h"        // LVGL����ʾ֧��
#include "lv_port_indev.h"       // LVGL�Ĵ���֧��
#include "gui_guider.h"
#include "events_init.h"

#define UI_MAX_MSG_PER_CYCLE LVGL_UI_QUEUE_LENGTH
#define UI_DEGREE_SYMBOL     "\xC2\xB0"
#define UI_REFRESH_PERIOD_MS 50U
#define UI_DATE_TEXT_LEN     16U
#define UI_TIME_TEXT_LEN     16U
#define UI_LOCATION_TEXT_LEN 16U
#define UI_WEATHER_TEXT_LEN  16U
#define UI_TEMP_TEXT_LEN     16U
#define UI_HUMIDITY_TEXT_LEN 16U

lv_ui guider_ui;






QueueHandle_t UI_queue_handle;    //UI��Ϣ���о��


/* �����ܼ�����������ʧ�� / ��ʱ������ʧ�ܣ� */
static volatile uint32_t g_drop_task_send_total = 0;
static volatile uint32_t g_drop_timer_send_total = 0;

/* ����������ͳ�ƣ������±��Ӧ ui_msg_type_t�� */
static volatile uint32_t g_drop_task_send_by_type[UI_MSG_MAX] = {0};
static volatile uint32_t g_drop_timer_send_by_type[UI_MSG_MAX] = {0};

static TIME_msg_typdef g_pending_time_msg;
static Weather_msg_typdef g_pending_weather_msg;
static DHT11_msg_typdef g_pending_dht11_msg;
static bool g_pending_time_valid = false;
static bool g_pending_weather_valid = false;
static bool g_pending_dht11_valid = false;

static char g_last_date_text[UI_DATE_TEXT_LEN] = {0};
static char g_last_time_text[UI_TIME_TEXT_LEN] = {0};
static char g_last_location_text[UI_LOCATION_TEXT_LEN] = {0};
static char g_last_weather_text[UI_WEATHER_TEXT_LEN] = {0};
static char g_last_temp_text[UI_TEMP_TEXT_LEN] = {0};
static char g_last_humidity_text[UI_HUMIDITY_TEXT_LEN] = {0};
static bool g_last_date_valid = false;
static bool g_last_time_valid = false;
static bool g_last_location_valid = false;
static bool g_last_weather_valid = false;
static bool g_last_temp_valid = false;
static bool g_last_humidity_valid = false;

/* �ж���Ϣ�����Ƿ���Ч����ֹ����Խ�� */
/* Validate message type before indexing stats arrays. */
static inline bool ui_msg_type_valid(UI_msg_type_typdef t)
{
    return t < UI_MSG_MAX;
}

static void ui_copy_bounded_string(char *dst, uint32_t dst_size, const char *src, uint32_t src_size)
{
      uint32_t i = 0U;
      if ((dst == NULL) || (src == NULL) || (dst_size == 0U))
      {
            return;
      }

      while ((i < (dst_size - 1U)) && (i < src_size) && (src[i] != '\0'))
      {
            dst[i] = src[i];
            i++;
      }
      dst[i] = '\0';
}

static bool ui_text_changed_and_update_cache(char *cache, uint32_t cache_size, bool *cache_valid, const char *new_text)
{
      if ((cache == NULL) || (cache_valid == NULL) || (new_text == NULL) || (cache_size == 0U))
      {
            return false;
      }

      if ((*cache_valid) && (strcmp(cache, new_text) == 0))
      {
            return false;
      }

      ui_copy_bounded_string(cache, cache_size, new_text, cache_size);
      *cache_valid = true;
      return true;
}

static void ui_apply_time_update(const TIME_msg_typdef *time_msg)
{
      char date_text[UI_DATE_TEXT_LEN];
      char time_text[UI_TIME_TEXT_LEN];

      if (time_msg == NULL)
      {
            return;
      }

      (void)snprintf(date_text, sizeof(date_text), "%04u.%02u.%02u",
                     (unsigned int)time_msg->year,
                     (unsigned int)time_msg->month,
                     (unsigned int)time_msg->day);
      (void)snprintf(time_text, sizeof(time_text), "%02u:%02u:%02u",
                     (unsigned int)time_msg->hour,
                     (unsigned int)time_msg->min,
                     (unsigned int)time_msg->sec);

      if (ui_text_changed_and_update_cache(g_last_date_text, sizeof(g_last_date_text),
                                           &g_last_date_valid, date_text))
      {
            lv_label_set_text(guider_ui.time_screen_date_label, date_text);
      }
      if (ui_text_changed_and_update_cache(g_last_time_text, sizeof(g_last_time_text),
                                           &g_last_time_valid, time_text))
      {
            lv_label_set_text(guider_ui.time_screen_time_label, time_text);
      }
}

static void ui_apply_weather_update(const Weather_msg_typdef *weather_msg)
{
      char location[UI_LOCATION_TEXT_LEN];
      char weather[UI_WEATHER_TEXT_LEN];

      if (weather_msg == NULL)
      {
            return;
      }

      ui_copy_bounded_string(location, sizeof(location),
                             weather_msg->city,
                             sizeof(weather_msg->city));
      ui_copy_bounded_string(weather, sizeof(weather),
                             weather_msg->weather,
                             sizeof(weather_msg->weather));

      if (ui_text_changed_and_update_cache(g_last_location_text, sizeof(g_last_location_text),
                                           &g_last_location_valid, location))
      {
            lv_label_set_text(guider_ui.weaher_screen_location_label, location);
      }
      if (ui_text_changed_and_update_cache(g_last_weather_text, sizeof(g_last_weather_text),
                                           &g_last_weather_valid, weather))
      {
            lv_label_set_text(guider_ui.weaher_screen_weather_label, weather);
      }
}

static void ui_apply_dht11_update(const DHT11_msg_typdef *dht11_msg)
{
      char temp_text[UI_TEMP_TEXT_LEN];
      char humidity_text[UI_HUMIDITY_TEXT_LEN];

      if (dht11_msg == NULL)
      {
            return;
      }

      (void)snprintf(temp_text, sizeof(temp_text), "%u.%u" UI_DEGREE_SYMBOL "C",
                     (unsigned int)dht11_msg->dht11_temperature_int,
                     (unsigned int)dht11_msg->dht11_temperature_dec);
      (void)snprintf(humidity_text, sizeof(humidity_text), "%u.%u%%RH",
                     (unsigned int)dht11_msg->dht11_humidity_int,
                     (unsigned int)dht11_msg->dht11_humidity_dec);

      if (ui_text_changed_and_update_cache(g_last_temp_text, sizeof(g_last_temp_text),
                                           &g_last_temp_valid, temp_text))
      {
            lv_label_set_text(guider_ui.t_h_screen_temp_label, temp_text);
      }
      if (ui_text_changed_and_update_cache(g_last_humidity_text, sizeof(g_last_humidity_text),
                                           &g_last_humidity_valid, humidity_text))
      {
            lv_label_set_text(guider_ui.t_h_screen_humidity_label, humidity_text);
      }
}

static void ui_process_msg(const UI_msg_typedef *msg)
{
      if ((msg == NULL) || !ui_msg_type_valid(msg->msg_type))
      {
            return;
      }

      switch (msg->msg_type)
      {
            case UI_TIME_UPDATE:
                  g_pending_time_msg = msg->msg_data.time_msg;
                  g_pending_time_valid = true;
                  break;
            case UI_WEATHER_UPDATE:
                  g_pending_weather_msg = msg->msg_data.weather_msg;
                  g_pending_weather_valid = true;
                  break;
            case UI_DHT11_UPDATE:
                  g_pending_dht11_msg = msg->msg_data.dht11_msg;
                  g_pending_dht11_valid = true;
                  break;
            default:
                  break;
      }
}

static void ui_flush_pending_updates(void)
{
      if (g_pending_time_valid)
      {
            ui_apply_time_update(&g_pending_time_msg);
            g_pending_time_valid = false;
      }

      if (g_pending_weather_valid)
      {
            ui_apply_weather_update(&g_pending_weather_msg);
            g_pending_weather_valid = false;
      }

      if (g_pending_dht11_valid)
      {
            ui_apply_dht11_update(&g_pending_dht11_msg);
            g_pending_dht11_valid = false;
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
   TickType_t last_wake_time;

   LVGL_UI_Queue_Init();   // ��ʼ��UI��Ϣ����
	
	setup_ui(&guider_ui);           // ��ʼ�� UI
	events_init(&guider_ui);       // ��ʼ�� �¼�
      last_wake_time = xTaskGetTickCount();
	
	
//   UBaseType_t uxFreeStack;

	for(;;)
	{
            if (UI_queue_handle != NULL)
            {
                  uint32_t handled_msgs = 0;
                  while ((handled_msgs < UI_MAX_MSG_PER_CYCLE) &&
                        (xQueueReceive(UI_queue_handle, &ui_msg, 0) == pdPASS))
                  {
                        ui_process_msg(&ui_msg);
                        handled_msgs++;
                  }
            }

            ui_flush_pending_updates();
		lv_timer_handler();
//      uxFreeStack = uxTaskGetStackHighWaterMark(NULL);
//      printf("LVGL_UI_task Free Stack: %lu words\r\n", uxFreeStack);
		vTaskDelayUntil(&last_wake_time, pdMS_TO_TICKS(UI_REFRESH_PERIOD_MS));
	}
	
}

void UI_Send_msg_from_task(const UI_msg_typedef *msg, TickType_t timeout)
{
   if ((UI_queue_handle == NULL) || (msg == NULL))
   {
      return;
   }

   if (xQueueSend(UI_queue_handle, msg, timeout) != pdPASS)
   {
      g_drop_task_send_total++;   // ������ʧ�ܵ��ܼ�������
      if (ui_msg_type_valid(msg->msg_type))
      {
         g_drop_task_send_by_type[msg->msg_type]++;  // ������Ϣ����ͳ��������ʧ�ܵķ����ͼ�������
      }

   }

}


void UI_Send_msg_from_timer(const UI_msg_typedef *msg)
{
   if ((UI_queue_handle == NULL) || (msg == NULL))
   {
      return;
   }

   if (xQueueSend(UI_queue_handle, msg, 0) != pdPASS)
   {
      g_drop_timer_send_total++;   // ��ʱ������ʧ�ܵ��ܼ�������
      if (ui_msg_type_valid(msg->msg_type))
      {
         g_drop_timer_send_by_type[msg->msg_type]++;  // ������Ϣ����ͳ�ƶ�ʱ������ʧ�ܵķ����ͼ�������
      }

   }

}
