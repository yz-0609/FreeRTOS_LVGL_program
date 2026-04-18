#ifndef __UART1_H
#define __UART1_H

#include "stdint.h"

// 初始化
void uart1_rtos_init(void);

// 发送接口 (printf可以直接使用)
uint16_t Uart_Send_RTOS(uint8_t *data, uint16_t length);

// 接收接口
uint16_t UART1_WaitForRxFrame(uint32_t timeoutMs);
uint16_t UART1_GetRxNum(void);
uint8_t* UART1_GetRxData(void);
void     UART1_ClearRx(void);

#endif

