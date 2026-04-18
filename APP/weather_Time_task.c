#include "weather_Time_task.h"
#include "esp8266.h"
#include "uart3.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "stdio.h"
#include "jsmn.h"
#include "jsmn_util.h"
#include "time.h"
#include "rtc.h"
#include <stdlib.h>
#include "LVGL_UI_task.h"

#define WINTER_URL  "GET https://api.seniverse.com/v3/weather/now.json?key=Syd350Nk9UhcuU9Jv&location=shanghai&language=zh-Hans&unit=c\r\n"
#define TIME_URL    "GET http://api.k780.com:88/?app=life.time&appkey=78932&sign=e1f38bbaa4f93550c3ff8afeff2ff2f6&format=json&HTTP/1.1\r\n"
#define TIME_ZOOM               (8 * 60 * 60)   // 东八区时间偏移，单位为秒

static jsmn_parser parser;
static int num_token=256;
static jsmntok_t token[256];

static HAL_StatusTypeDef status_time,status_date;
static struct tm *tm;    // 用于存储解析后的时间信息
static RTC_DateTypeDef rtc_data;
static RTC_TimeTypeDef rtc_time;

extern osThreadId TimeHandle;
extern osTimerId myTimer01Handle;
extern osThreadId WeatherHandle;





//软件定时器回调函数，时间任务函数，负责获取网络时间并设置RTC
void time_enter(void)
{
	UI_msg_typedef time_msg;
	time_msg.msg_type = UI_TIME_UPDATE;  // 设置消息类型为时间更新

    RTC_DateTypeDef rtc_data;
    RTC_TimeTypeDef rtc_time;

    HAL_RTC_GetTime(&hrtc, &rtc_time, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &rtc_data, RTC_FORMAT_BIN);	

	time_msg.msg_data.time_msg.year = 2000 + rtc_data.Year;  // RTC日期中的年份是从2000年开始的，所以需要加上2000
	time_msg.msg_data.time_msg.month = rtc_data.Month;
	time_msg.msg_data.time_msg.day = rtc_data.Date;
	time_msg.msg_data.time_msg.hour = rtc_time.Hours;
	time_msg.msg_data.time_msg.min = rtc_time.Minutes;
	time_msg.msg_data.time_msg.sec = rtc_time.Seconds;

	time_msg.timestamp = xTaskGetTickCount()*portTICK_PERIOD_MS;  // 获取当前系统时间戳，单位为毫秒

	UI_Send_msg_from_timer(&time_msg);

    // printf("%02d:%02d:%02d\r\n", rtc_time.Hours, rtc_time.Minutes, rtc_time.Seconds);
    // printf("%02d/%02d/%02d\r\n",2000 + rtc_data.Year, rtc_data.Month, rtc_data.Date);	
}


void Time_task(void const * argument)
{
	
	esp_time_init();   //注意调用！！！，否则会卡死程序

	

	for(;;)
	{
		jsmn_init(&parser);  //时间数据解析器初始化
		esp_send_variable_length_data(TIME_URL);
		printf("\r\n");
		if(esp_getrxnum())
		{
			int time_token_len = jsmn_parse(&parser, (char *)esp8266.esp_rxdata, 512, token, num_token);
			printf("Received data: %s\r\n", esp8266.esp_rxdata);
			if(time_token_len <= 0)
			{
				printf("jsmn_parse failed\r\n");
				// printf("Received data: %s\r\n", esp8266.esp_rxdata);
				// printf("Token length: %d\r\n", time_token_len);
				goto RETRY_WAIT;
			}
			
			jsmn_item_t root;
			JSMN_ItemInit(&root, token, 0, time_token_len);
			
			jsmn_item_t time_results_item;
			if(JSMN_GetObjectItem((char *)esp8266.esp_rxdata, &root, "result", &time_results_item)!=0)
			{
				// printf("Failed to get time results item\r\n");
				goto RETRY_WAIT;
			}

			jsmn_item_t timestamp_item;
			if (JSMN_GetObjectItem((char *)esp8266.esp_rxdata, &time_results_item, "timestamp", &timestamp_item) != 0) {
				// printf("Get timestamp object failed\r\n");
				goto RETRY_WAIT;
			}
			
			char timestamp_str[16];
			JSMN_GetValueStringBuffered((char *)esp8266.esp_rxdata, &timestamp_item, timestamp_str, 16);

			uint32_t timestamp_val = atoi(timestamp_str) + TIME_ZOOM;

			tm = localtime(&timestamp_val);
			rtc_data.Year = tm->tm_year - 100; 
			rtc_data.Month = tm->tm_mon + 1;
			rtc_data.Date = tm->tm_mday;
			rtc_time.Hours = tm->tm_hour;
			rtc_time.Minutes = tm->tm_min;
			rtc_time.Seconds = tm->tm_sec;

			status_time = HAL_RTC_SetTime(&hrtc, &rtc_time, RTC_FORMAT_BIN);  //设置RTC时间
			status_date = HAL_RTC_SetDate(&hrtc, &rtc_data, RTC_FORMAT_BIN);  //设置RTC日期


			if(status_time == HAL_OK && status_date == HAL_OK)
			{
				// printf("RTC time/date set successfully\r\n");
				osTimerStart(myTimer01Handle,950);
				xTaskNotifyGive(WeatherHandle);  // 通知天气任务可以开始获取天气信息了
				osThreadTerminate(TimeHandle);  // 成功设置时间后，终止时间任务，因为不需要再获取时间了
				goto RETRY_WAIT;
			}
			else
			{
				// printf("Failed to set RTC time/date\r\n");
				goto RETRY_WAIT;
			}

		}
RETRY_WAIT:			
		osDelay(pdMS_TO_TICKS(5000));  // 每5秒尝试获取一次时间，直到成功为止
	}
	
	
}



void Weather_task(void const * argument)
{
	uint32_t notify_value =0;
	notify_value=ulTaskNotifyTake(pdTRUE, portMAX_DELAY);  // 等待时间任务的通知，直到时间设置成功后才开始获取天气信息
	if(notify_value!=0)
	printf("Received notification to start Weather task\r\n");
	esp_weather_init();
	UI_msg_typedef weather_msg;
	weather_msg.msg_type = UI_WEATHER_UPDATE;  // 设置消息类型为天气更新


	for(;;)
	{
		esp_send_variable_length_data(WINTER_URL);
		printf("\r\n");
		jsmn_init(&parser); 
		//接受测试
		if(esp_getrxnum())
		{
			int token_len = jsmn_parse(&parser, (char *)esp8266.esp_rxdata, 512, token, num_token);
					if(token_len <= 0)
					{
						printf("jsmn_parse failed\r\n");
						// printf("Received data: %s\r\n", esp8266.esp_rxdata);
						// printf("Token length: %d\r\n", token_len);
						return;
					}
					
					jsmn_item_t root;
					JSMN_ItemInit(&root, token, 0, token_len);
					
					jsmn_item_t results_item;
					JSMN_GetObjectItem((char *)esp8266.esp_rxdata, &root, "results", &results_item);
					
					int results_array_size =  JSMN_GetArraySize(&results_item);
					
					for(int i = 0; i< results_array_size; i++) 
					{
						jsmn_item_t root_results_item;
						JSMN_GetArrayItem(&results_item, i, &root_results_item);
						
						jsmn_item_t loaction_item;
						
						JSMN_GetObjectItem((char *)esp8266.esp_rxdata, &root_results_item, "location", &loaction_item);
						
						jsmn_item_t name_item;
						JSMN_GetObjectItem((char *)esp8266.esp_rxdata, &loaction_item, "name", &name_item);
						

						//城市名称字符串缓冲区
						// char name_item_str[16];
						JSMN_GetValueStringBuffered((const char *)esp8266.esp_rxdata, &name_item, weather_msg.msg_data.weather_msg.city, 8);
						// printf("Name item string: %s\r\n", weather_msg.msg_data.weather_msg.city);
						
						jsmn_item_t now_item;
						JSMN_GetObjectItem((char *)esp8266.esp_rxdata, &root_results_item, "now", &now_item);
						
						jsmn_item_t text_item;
						JSMN_GetObjectItem((char *)esp8266.esp_rxdata, &now_item, "text", &text_item);
						

						//天气状况字符串缓冲区
						// char text_item_str[16];
						JSMN_GetValueStringBuffered((char *)esp8266.esp_rxdata, &text_item, weather_msg.msg_data.weather_msg.weather, 8);
						// printf("Text item string: %s\r\n", weather_msg.msg_data.weather_msg.weather);
						
						jsmn_item_t temperature_item;
						JSMN_GetObjectItem((char *)esp8266.esp_rxdata, &now_item, "temperature", &temperature_item);
						
						//温度字符串缓冲区
						// char temperature_item_str[16];
						JSMN_GetValueStringBuffered((char *)esp8266.esp_rxdata, &temperature_item, weather_msg.msg_data.weather_msg.temp, 8);
						// printf("Temperature item string: %s\r\n", weather_msg.msg_data.weather_msg.temp);
					}
			weather_msg.timestamp = xTaskGetTickCount()*portTICK_PERIOD_MS;  // 获取当前系统时间戳，单位为毫秒		
			UI_Send_msg_from_task(&weather_msg, pdMS_TO_TICKS(10));  // 将消息发送到UI任务，等待10ms
		}	
		
		osDelay(pdMS_TO_TICKS(10000));  // 每60秒获取一次天气信息
	}
}

