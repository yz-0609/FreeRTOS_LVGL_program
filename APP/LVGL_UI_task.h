#ifndef __LVGL_UI_TASK_H
#define __LVGL_UI_TASK_H

#include "main.h"
#include "stdio.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "cmsis_os.h"




#define LVGL_UI_QUEUE_LENGTH 20U   //UI消息队列长度  

extern QueueHandle_t UI_queue_handle;    //UI消息队列句柄


// 定义UI消息类型枚举，用于区分不同类型的UI更新消息
typedef enum
{
    UI_TIME_UPDATE=0,
    UI_WEATHER_UPDATE,
    UI_DHT11_UPDATE,
    UI_MSG_MAX
}UI_msg_type_typdef;



// 定义时间更新消息结构体，包含时间相关的字段 ,软件定时器发送
typedef struct 
{

	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t min;
	uint8_t sec;    

}TIME_msg_typdef;

// 定义天气更新消息结构体，包含天气相关的字段
typedef struct 
{

	char city[8];
	char weather[8];
	char temp[8];   

}Weather_msg_typdef;

// 定义DHT11数据更新消息结构体，包含DHT11传感器相关的字段
typedef struct
{

    uint8_t dht11_humidity_int;
    uint8_t dht11_humidity_dec;
    uint8_t dht11_temperature_int;
    uint8_t dht11_temperature_dec;    

}DHT11_msg_typdef;


// 定义一个联合体，用于存储不同类型的UI消息数据
typedef union
{
    TIME_msg_typdef time_msg;          // 时间更新消息
    Weather_msg_typdef weather_msg;    // 天气更新消息
    DHT11_msg_typdef dht11_msg;       // DHT11数据更新消息
}UI_data_uion;


// 定义一个结构体，用于封装UI消息的类型、数据和时间戳等信息
typedef struct 
{

    UI_msg_type_typdef msg_type;  // 消息类型
    UI_data_uion msg_data;       // 消息数据
    uint32_t timestamp;          // 消息生成的时间戳，单位为毫秒

}UI_msg_typedef;


void UI_Send_msg_from_task(const UI_msg_typedef *msg, TickType_t timeout);
void UI_Send_msg_from_timer(const UI_msg_typedef *msg);

#endif

