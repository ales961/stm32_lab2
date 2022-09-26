#ifndef UART_H
#define UART_H

#include "usart.h"

void recieve();
void transmit(char msg[]);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);

#endif
