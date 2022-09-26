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

void check() {
	int16_t n = buffer_elements();
	if (n <= 0) return;

	if(n > 20) {
	    buffer_clear();
	    transmit("ERROR");
	    return;
	}

	char buf_part[n];
	memcpy(buf_part, getBuffer(), n);


	if (setModeFlag == 1) {
		if (strcmp(buf_part, "1") == 0) {
			mode = 1;
			transmit("OK");
		} else if (strcmp(buf_part, "2") == 0) {
			mode = 2;
			transmit("OK");
		} else {
			transmit("ERROR");
		}
		buffer_clear();
		setModeFlag = 0;
		return;
	}
	if (setTimeoutFlag != 0) {
		setTimeoutFlag--;
		if (setTimeoutFlag == 0) {
			timeout = atoi(buf_part);
			if (timeout > 0) {
				setDurationRED(timeout*1000);
				transmit("OK");
			} else {
				transmit("ERROR");
			}
			buffer_clear();
		}
		return;
	}

	if (strcmp(buf_part, "?") == 0) {
		transmit(color_names[getCurrentColor()]);
		char mode_str[10];
		sprintf(mode_str, "mode %d", mode);
		transmit(mode_str);
		char timeout_str[10];
		sprintf(timeout_str, "timeout %d", (int) trafficLightGetDuration(RED));
		transmit(timeout_str);
		if (interruptsEnabled == 1) {
			transmit("I");
		} else {
			transmit("P");
		}
		buffer_clear();
	} else if (strcmp(buf_part, "set mode ") == 0) {
		setModeFlag = 1;
		buffer_clear();
	} else if (strcmp(buf_part, "set timeout ") == 0) {
		setTimeoutFlag = 2;
		buffer_clear();
	} else if (strcmp(buf_part, "set interrupts on") == 0) {
		__enable_irq();
		interruptsEnabled = 1;
		buffer_clear();
	} else if (strcmp(buf_part, "set interrupts off") == 0) {
		__disable_irq();
		interruptsEnabled = 0;
		buffer_clear();
	}
}



int getMode() {
	return mode;
}
int getInterruptsEnabled() {
	return interruptsEnabled;
}
