/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
/*
GPIO-foundation
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==1
HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_5);
GPIO-NVIC
All GPIO interrupts invoke this callback function. 
Through the judgment of the pin parameter, 
it determines which pin triggers the interrupt (GPIO_Pin, parameter range: GPIO_PIN_0 to GPIO_PIN_15).
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin==GPIO_PIN_1)
	{
	
	}
}
*/
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

