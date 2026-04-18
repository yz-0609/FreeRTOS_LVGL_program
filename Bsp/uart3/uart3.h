#ifndef __UART3_H
#define __UART3_H

#include "stdint.h"

// 初始化
void uart3_rtos_init(void);

// 发送接口 (printf可以直接使用)
uint16_t Uart3_Send_RTOS(uint8_t *data, uint16_t length);

// 接收接口
uint16_t UART3_WaitForRxFrame(uint32_t timeoutMs);
uint16_t UART3_GetRxNum(void);
uint8_t* UART3_GetRxData(void);
void     UART3_ClearRx(void);

#endif

