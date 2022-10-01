#ifndef UART_H
#define UART_H

#include "usart.h"

void uart_buffersInit();
void recieve();
void transmit(uint8_t* msg);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);

#endif
