#include <string.h>
#include "hardware/uart.h"
#include "buffer.h"
#include "state_control.h"

char nextByte;
char transmitBuffer[512];
int needToTransmit = 0;

void recieve() {
	if (getInterruptsEnabled() == 1) {
		HAL_UART_Receive_IT(&huart6, &nextByte, 1);
	} else {
		if (HAL_UART_Receive(&huart6, &nextByte, 1, 10) == HAL_OK) {
			buffer_push(nextByte);
			check();
		}
	}
}

void transmit(char msg[]) {
	if (getInterruptsEnabled() == 1) {
		if (HAL_UART_Transmit_IT(&huart6, (uint8_t*) msg, sizeof(msg)) != HAL_OK) {
			strcat(transmitBuffer, msg);
		}
	} else {
		HAL_UART_Transmit(&huart6, (uint8_t*) msg, sizeof(msg), 10);
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart == &huart6) {
		check();
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart == &huart6) {
		if (strcmp(transmitBuffer, "") != 0) {
			char buf[needToTransmit];
			memcpy(buf, transmitBuffer, needToTransmit);
			HAL_UART_Transmit_IT(&huart6, (uint8_t*) buf, needToTransmit);
			needToTransmit = 0;
			strcpy(transmitBuffer, "");		}
	}
}
