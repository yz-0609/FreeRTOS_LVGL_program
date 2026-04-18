#ifndef __ESP8266_H
#define __ESP8266_H



#include "stdio.h"
#include "uart3.h"

#define esp_size    1024
typedef struct             
{
	uint8_t esp_flag; 
	uint16_t esp_rxnum;
	uint8_t esp_rxdata[esp_size];
}esp_typdef;


extern esp_typdef esp8266;    //定义结构体



void esp8266_copy_rxdata(char* data);
void esp_rxnum_clear(void);
void esp_send_data(const char* ch,uint16_t len);
uint16_t esp_getrxnum(void);
void esp_init(void);
uint8_t esp_sendAT(char* command,char* back);
uint8_t esp_at_test(void);
uint8_t esp_set_mode(uint8_t mode);
uint8_t esp_jion_ip(char* id,char* pwd);
uint8_t esp_set_connect(uint8_t mode);
uint8_t esp_connect_TCP(char* ip,char* port);
uint8_t esp_enter_clear_transmit(void);
void esp_send_variable_length_data(const char* pcString, ...);

void esp_time_init(void);
void esp_weather_init(void);




#endif




