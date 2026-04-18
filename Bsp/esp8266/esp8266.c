#include "esp8266.h"
#include "gpio.h"
#include "uart3.h"
#include "string.h"
#include "stdlib.h"
#include "stdarg.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "stdio.h"
#include "usart.h"
//注意此代码默认使用的是串口3
//注意此代码默认使用的是串口3
//注意此代码默认使用的是串口3


//esp8266模式定义
#define esp_STA_mode    1
#define esp_AP_mode     2
#define esp_STA_AP_mode 3 


//热点定义
#define wife_id         "Lab107_AX6"
#define wife_pwd        "lab120120."  //根据实际情况修改

//定义连接模式
#define esp_sigle_connect_mode  0    //单路连接
#define esp_mux_connect_mode    1    //多路连接



//定义TCP服务器参数
#define WEATHER_TCP_IP     "api.seniverse.com"    //根据电脑进行修改
#define TIME_TCP_IP        "api.k780.com"    //根据电脑进行修改
#define TCP_PORT   "80"




esp_typdef esp8266={0};    //定义结构体




//清空接受字节数
void esp_rxnum_clear(void)
{
	esp8266.esp_rxnum=0;
}




//发送数据
void esp_send_data(const char*ch,uint16_t len)
{
	esp_rxnum_clear();
	
	Uart3_Send_RTOS((uint8_t*)ch,len);
}
 
//发送不定长数据
void esp_send_variable_length_data(const char* pcString, ...)
{
	char mBuffer[256] = {0};                                       // 开辟一个缓存, 并把里面的数据置0
    va_list ap;                                                     // 新建一个可变参数列表
    va_start(ap, pcString);                                         // 列表指向第一个可变参数
    vsnprintf(mBuffer, 256, pcString, ap);                         


	Uart3_Send_RTOS((uint8_t*)mBuffer,strlen(mBuffer));
}


//获得接受字节数
uint16_t esp_getrxnum(void)
{
	
	if(UART3_WaitForRxFrame(pdMS_TO_TICKS(10)))   //堵塞读取
	{
		
		esp8266.esp_rxnum=UART3_GetRxNum();
		
		//串口接收到数据的转存
		memset(esp8266.esp_rxdata,0,esp_size);
		memcpy(esp8266.esp_rxdata,UART3_GetRxData(),esp8266.esp_rxnum);

		UART3_ClearRx();     //清空串口中RxNum
		
		
		
	}
	
	
	return esp8266.esp_rxnum;
	
}


//接受数据的外部转存 一般外部函数调用
void esp8266_copy_rxdata(char* data)
{
	   memcpy(data, esp8266.esp_rxdata, esp8266.esp_rxnum);

}





//发送AT指令并等待返回
uint8_t esp_sendAT(char* command,char* back)
{
	uint8_t timeout=250;
	esp_rxnum_clear();
	esp_send_data(command,strlen(command));   //发送指令


	
	//等待返回
	while(timeout--)
	{
		if(esp_getrxnum())
		{
			esp_rxnum_clear();
			if(strstr((char*)esp8266.esp_rxdata,back))    //在接收到的数据中找期待返回的指令
			{
				return 1;
			}
		}
		osDelay(pdMS_TO_TICKS(10));
	}
	
	
	//等待结束
	esp_rxnum_clear();
	
	return 0;
}



//esp8266是否正常
uint8_t esp_at_test(void)
{
	return esp_sendAT("AT\r\n","OK");    //注意此处发送给esp8266的指令必须携带新行
										//注意此处发送给esp8266的指令必须携带新行
										//注意此处发送给esp8266的指令必须携带新行
}

//esp8266设置模式
uint8_t esp_set_mode(uint8_t mode)
{
	switch(mode)
	{
		
		case esp_STA_mode:
			return esp_sendAT("AT+CWMODE=1\r\n","OK");
		case esp_AP_mode:
			return esp_sendAT("AT+CWMODE=2\r\n","OK");			
		case esp_STA_AP_mode:
			return esp_sendAT("AT+CWMODE=3\r\n","OK");		
		
		default:
			return 3;     //错误返回
		
	}
}





//esp8266设置单路连接模式
uint8_t esp_set_connect(uint8_t mode)
{
	char cmd[84];
	sprintf(cmd,"AT+CIPMUX=%d\r\n",mode);
	return esp_sendAT(cmd,"OK");
}




//esp8266作为设备入网函数
uint8_t esp_jion_ip(char* id,char* pwd)
{
	char cmd[84];
	sprintf(cmd,"AT+CWJAP=\"%s\",\"%s\"\r\n",id,pwd);
	return esp_sendAT(cmd,"WIFI GOT IP");
}




//连接到TCP服务器
uint8_t esp_connect_TCP(char* ip,char* port)
{
	char cmd[84];
	sprintf(cmd,"AT+CIPSTART=\"TCP\",\"%s\",%s\r\n",ip,port);
	return esp_sendAT(cmd,"CONNECT");
}




//进入透传模式
uint8_t esp_enter_clear_transmit(void)
{
	uint8_t ret;
	ret=esp_sendAT("AT+CIPMODE=1\r\n","OK");
	ret+=esp_sendAT("AT+CIPSEND\r\n",">");
	if(ret==2)
	return 1;
	else
	return 0;
}



void esp_stop_transmit(void)
{
	// 1. 发送+++前必须保证至少等待 200~500ms（防止与上一次发的透传数据粘连）
	osDelay(pdMS_TO_TICKS(500)); 
	
	// 2. 清空接收缓存区，防止把透传的数据当成了AT指令返回值
	esp_rxnum_clear();
	
	// 3. 使用与其他地方统一的底层发送函数，且不要带 \r\n
	Uart3_Send_RTOS((uint8_t*)"+++", 3);
	
	// 4. 发送+++后必须等待至少 1000ms（非常重要！）
	osDelay(pdMS_TO_TICKS(1500)); 
	
	// 5. 测试一下是否成功退出了透传模式（多发两遍容错）
	esp_at_test();
	esp_at_test();
}


uint8_t esp_close_TCP(void)
{
	// 尝试关闭TCP连接，这里不作为死循环条件，防止连接本身已断开发ERROR导致死机
	uint8_t ret = esp_sendAT("AT+CIPCLOSE\r\n","OK");
	if (ret == 0)
	{
		esp_sendAT("AT+CIPCLOSE\r\n", "ERROR"); // 处理本身无连接的情况
	}
	return 1; // 强制返回1，只管关闭不管成功与否，避免死循环
}



//初始化函数
void esp_init(void)
{
	printf("ESP8266 start setting\r\n");

	osDelay(pdMS_TO_TICKS(300));        //注意上电后初始化前延时确保esp8266稳定
	esp8266.esp_flag=0;
	
	
	//ESP8266其他设置
	printf("1.ESP8266 are ok\r\n");
	
	while(esp_at_test()==0);
	osDelay(pdMS_TO_TICKS(500));
	

	
	printf("2.set mode\r\n");
	while(esp_set_mode(esp_STA_mode)==0);
	osDelay(pdMS_TO_TICKS(500));	
	
	
	
	printf("3.set single connection\r\n");
	while(esp_set_connect(esp_sigle_connect_mode)==0);
	osDelay(pdMS_TO_TICKS(500));	
	
	
	
	printf("4.jion ip\r\n");
	while(esp_jion_ip(wife_id,wife_pwd)==0);
	osDelay(pdMS_TO_TICKS(2500));	        //连接网络所需要的时间较长
	
	

	
}





void esp_time_init(void)
{

	esp_init();
	
	printf("6.join time TCP\r\n");
	while(esp_connect_TCP(TIME_TCP_IP,TCP_PORT)==0);       //链接时间服务器
	osDelay(pdMS_TO_TICKS(500));
	
	
	printf("7.enter transparent mode\r\n");
	while(esp_enter_clear_transmit()==0);	
	osDelay(pdMS_TO_TICKS(500));
	

	printf("ESP8266 OK\r\n");		
}



void esp_weather_init(void)
{

	printf("esp_stop_transmit\r\n");
	esp_stop_transmit();
	osDelay(pdMS_TO_TICKS(500));

	printf("esp_close_TCP\r\n");
	while(esp_close_TCP()==0);   //关闭与时间服务器的TCP连接
	osDelay(pdMS_TO_TICKS(500));

	printf("5.join weather TCP\r\n");
	while(esp_connect_TCP(WEATHER_TCP_IP,TCP_PORT)==0);	   //链接心知天气服务器
	osDelay(pdMS_TO_TICKS(500));

	printf("7.enter transparent mode\r\n");
	while(esp_enter_clear_transmit()==0);	
	osDelay(pdMS_TO_TICKS(500));
	

	printf("ESP8266 OK\r\n");		
}
