//#include "weather.h"
//#include "esp8266.h"
//#include "uart3.h"
//#include "FreeRTOS.h"
//#include "task.h"
//#include "cmsis_os.h"
//#include "stdio.h"
//#include "jsmn.h"
//#include "jsmn_util.h"
//#include "time.h"
//#include "rtc.h"
//#include <stdlib.h>


//#define WINTER_URL  "GET https://api.seniverse.com/v3/weather/now.json?key=Syd350Nk9UhcuU9Jv&location=shanghai&language=zh-Hans&unit=c\r\n"
//#define TIME_URL    "GET http://api.k780.com:88/?app=life.time&appkey=78932&sign=e1f38bbaa4f93550c3ff8afeff2ff2f6&format=json&HTTP/1.1\r\n"
//#define TIME_ZOOM               (8 * 60 * 60)   // 东八区时间偏移，单位为秒

//static jsmn_parser parser;
//static int num_token=256;
//static jsmntok_t token[256];


//static jsmn_parser time_parser;
//static int time_num_token=256;
//static jsmntok_t time_token[256];
//static struct tm *tm;    // 用于存储解析后的时间信息
//static RTC_DateTypeDef rtc_data;
//static RTC_TimeTypeDef rtc_time;





//void Weather_Time_Init(void)
//{
//  esp_weather_time_init();   //注意调用！！！，否则会卡死程序
//  jsmn_init(&parser);    //天气数据解析器初始化
//  jsmn_init(&time_parser);  //时间数据解析器初始化
//}


// 


////获取天气信息
//void Get_Weather(void)
//{
//	esp_send_variable_length_data(WINTER_URL);
//	printf("\r\n");
//	//接受测试
//	if(esp_getrxnum())
//	{
//		int token_len = jsmn_parse(&parser, (char *)esp8266.esp_rxdata, 512, token, num_token);
//				if(token_len <= 0)
//				{
//					printf("jsmn_parse failed\r\n");
//					printf("Received data: %s\r\n", esp8266.esp_rxdata);
//					printf("Token length: %d\r\n", token_len);
//					return;
//				}
//				
//				jsmn_item_t root;
//				JSMN_ItemInit(&root, token, 0, token_len);
//				
//				jsmn_item_t results_item;
//				JSMN_GetObjectItem((char *)esp8266.esp_rxdata, &root, "results", &results_item);
//				
//				int results_array_size =  JSMN_GetArraySize(&results_item);
//				
//				for(int i = 0; i< results_array_size; i++) 
//				{
//					jsmn_item_t root_results_item;
//					JSMN_GetArrayItem(&results_item, i, &root_results_item);
//					
//					jsmn_item_t loaction_item;
//					
//					JSMN_GetObjectItem((char *)esp8266.esp_rxdata, &root_results_item, "location", &loaction_item);
//					
//					jsmn_item_t name_item;
//					JSMN_GetObjectItem((char *)esp8266.esp_rxdata, &loaction_item, "name", &name_item);
//					
//					char name_item_str[16];
//					
//					JSMN_GetValueStringBuffered((const char *)esp8266.esp_rxdata, &name_item, name_item_str, 16);
//					printf("Name item string: %s\r\n", name_item_str);
//					
//					jsmn_item_t now_item;
//					JSMN_GetObjectItem((char *)esp8266.esp_rxdata, &root_results_item, "now", &now_item);
//					
//					jsmn_item_t text_item;
//					JSMN_GetObjectItem((char *)esp8266.esp_rxdata, &now_item, "text", &text_item);
//					
//					char text_item_str[16];
//            		JSMN_GetValueStringBuffered((char *)esp8266.esp_rxdata, &text_item, text_item_str, 16);
//            		printf("Text item string: %s\r\n", text_item_str);
//					
//					jsmn_item_t temperature_item;
//					JSMN_GetObjectItem((char *)esp8266.esp_rxdata, &now_item, "temperature", &temperature_item);
//					
//					
//					char temperature_item_str[16];
//            		JSMN_GetValueStringBuffered((char *)esp8266.esp_rxdata, &temperature_item, temperature_item_str, 16);
//           			 printf("Temperature item string: %s\r\n", temperature_item_str);
//				}
//	}	

//}


//uint8_t Get_Time(void)
//{
//	HAL_StatusTypeDef status_time,status_date;
//	esp_send_variable_length_data(TIME_URL);
//	printf("\r\n");
//	if(esp_getrxnum())
//	{
//		int time_token_len = jsmn_parse(&time_parser, (char *)esp8266.esp_rxdata, 512, time_token, time_num_token);
//		printf("Received data: %s\r\n", esp8266.esp_rxdata);
//		if(time_token_len <= 0)
//		{
//			printf("jsmn_parse failed\r\n");
//			printf("Received data: %s\r\n", esp8266.esp_rxdata);
//			printf("Token length: %d\r\n", time_token_len);
//			return 0;
//		}
//		
//		jsmn_item_t root;
//		JSMN_ItemInit(&root, time_token, 0, time_token_len);
//		
//		jsmn_item_t time_results_item;
//		if(JSMN_GetObjectItem((char *)esp8266.esp_rxdata, &root, "result", &time_results_item)!=0)
//		{
//			printf("Failed to get time results item\r\n");
//			return 0;
//		}

//		jsmn_item_t timestamp_item;
//        if (JSMN_GetObjectItem((char *)esp8266.esp_rxdata, &time_results_item, "timestamp", &timestamp_item) != 0) {
//            printf("Get timestamp object failed\r\n");
//            return 0;
//        }
//        
//        char timestamp_str[16];
//        JSMN_GetValueStringBuffered((char *)esp8266.esp_rxdata, &timestamp_item, timestamp_str, 16);

//		uint32_t timestamp_val = atoi(timestamp_str) + TIME_ZOOM;

//        tm = localtime(&timestamp_val);
//		rtc_data.Year = tm->tm_year - 100; 
//        rtc_data.Month = tm->tm_mon + 1;
//        rtc_data.Date = tm->tm_mday;
//        rtc_time.Hours = tm->tm_hour;
//        rtc_time.Minutes = tm->tm_min;
//        rtc_time.Seconds = tm->tm_sec;

//        status_time = HAL_RTC_SetTime(&hrtc, &rtc_time, RTC_FORMAT_BIN);  //设置RTC时间
//        status_date = HAL_RTC_SetDate(&hrtc, &rtc_data, RTC_FORMAT_BIN);  //设置RTC日期


//		if(status_time == HAL_OK && status_date == HAL_OK)
//		{
//			return 1; // 成功
//		}
//		else
//		{
//			printf("Failed to set RTC time/date\r\n");
//			return 0; // 失败
//		}

//	}
//	return 0; // 默认返回失败
//}


//void time_enter(void)
//{
//    RTC_DateTypeDef rtc_data;
//    RTC_TimeTypeDef rtc_time;

//    HAL_RTC_GetTime(&hrtc, &rtc_time, RTC_FORMAT_BIN);
//    HAL_RTC_GetDate(&hrtc, &rtc_data, RTC_FORMAT_BIN);	

//    printf("%02d:%02d:%02d\r\n", rtc_time.Hours, rtc_time.Minutes, rtc_time.Seconds);
//    printf("%02d/%02d/%02d\r\n",2000 + rtc_data.Year, rtc_data.Month, rtc_data.Date);	
//}


