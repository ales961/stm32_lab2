#include <string.h>
#include "hardware/uart.h"
#include "buffer.h"
#include "state_control.h"

uint8_t nextByte;
int needToTransmit = 0;

struct buffer buffer;
struct buffer transmit_buffer;

void uart_buffersInit() {
	buffer = buffer_create();
	transmit_buffer = buffer_create();
}

void recieve() {
	if (getInterruptsEnabled() == 1) {
		HAL_UART_Receive_IT(&huart6, &nextByte, 1);
	} else {
		if (HAL_UART_Receive(&huart6, &nextByte, 1, 10) == HAL_OK) {
			buffer_push(&buffer, nextByte);
			check(&buffer);
		}
	}
}

void transmit(uint8_t* msg) {
	if (getInterruptsEnabled() == 1) {
		if (HAL_UART_Transmit_IT(&huart6, msg, strlen((char*) msg)) != HAL_OK) {
			for (int i = 0; i < strlen((char*) msg); i++) {
				buffer_push(&transmit_buffer, msg[i]);
			}
		}
	} else {
		HAL_UART_Transmit(&huart6, msg, strlen((char*) msg), 50);
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart == &huart6) {
		check(&buffer);
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart == &huart6) {
		if (buffer_elements(&transmit_buffer) != 0) {
			uint8_t byte = buffer_pop(&transmit_buffer);
			transmit(&byte);
		}
	}
}
