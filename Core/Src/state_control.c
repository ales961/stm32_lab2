#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "state_control.h"
#include "buffer.h"
#include "hardware/uart.h"
#include "traffic_light.h"

int mode = 1;
int interruptsEnabled = 0;

int setModeFlag = 0;
int setTimeoutFlag = 0;

int timeout;

void check(struct buffer* buffer) {
	int8_t n = buffer_elements(buffer);
	if (n <= 0) return;

	if(n > 20) {
	    buffer_clear(buffer);
	    transmit((uint8_t*) "ERROR");
	    return;
	}

	char buf_part[n];
	memcpy(buf_part, buffer->data, n);


	if (setModeFlag == 1) {
		if (strcmp(buf_part, "1") == 0) {
			mode = 1;
			transmit((uint8_t*) "OK");
		} else if (strcmp(buf_part, "2") == 0) {
			mode = 2;
			transmit((uint8_t*) "OK");
		} else {
			transmit((uint8_t*) "ERROR");
		}
		buffer_clear(buffer);
		setModeFlag = 0;
		return;
	}
	if (setTimeoutFlag != 0) {
		setTimeoutFlag--;
		if (setTimeoutFlag == 0) {
			timeout = atoi(buf_part);
			if (timeout > 0) {
				setDurationRED(timeout*1000);
				transmit((uint8_t*) "OK");
			} else {
				transmit((uint8_t*) "ERROR");
			}
			buffer_clear(buffer);
		}
		return;
	}

	if (strcmp(buf_part, "?") == 0) {
		uint8_t state_str[50];
		char interrupt = (interruptsEnabled == 1) ? 'I' : 'P';
		sprintf((char*) state_str, "\n%s\n\rmode %d\n\rtimeout %d\n\r%c\n\r",
				color_names[getCurrentColor()],
				mode,
				(int) trafficLightGetDuration(RED),
				interrupt);
		transmit(state_str);
		buffer_clear(buffer);
	} else if (strcmp(buf_part, "set mode ") == 0) {
		setModeFlag = 1;
		buffer_clear(buffer);
	} else if (strcmp(buf_part, "set timeout ") == 0) {
		setTimeoutFlag = 2;
		buffer_clear(buffer);
	} else if (strcmp(buf_part, "set interrupts on") == 0) {
		__enable_irq();
		interruptsEnabled = 1;
		buffer_clear(buffer);
	} else if (strcmp(buf_part, "set interrupts off") == 0) {
		__disable_irq();
		interruptsEnabled = 0;
		buffer_clear(buffer);
	}
}



int getMode() {
	return mode;
}
int getInterruptsEnabled() {
	return interruptsEnabled;
}
