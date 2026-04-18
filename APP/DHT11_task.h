#ifndef __DHT11_TASK_H
#define __DHT11_TASK_H

#include "stdio.h"
#include "main.h"
#define  DHT11_PORT     GPIOC
#define  DHT11_PIN      GPIO_PIN_3



#define  DHT11_OUT(x)   do{x? HAL_GPIO_WritePin(DHT11_PORT,DHT11_PIN, GPIO_PIN_SET):HAL_GPIO_WritePin(DHT11_PORT,DHT11_PIN, GPIO_PIN_RESET);}while(0)
#define  DHT11_READ     HAL_GPIO_ReadPin(DHT11_PORT,DHT11_PIN)



void DHT11_read_data(uint8_t* result);


#endif

