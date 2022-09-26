#include "traffic_light.h"

#include <stdbool.h>

int durationRED = 6000;
static uint16_t durations[4] = {
        [RED] = 6000,
        [YELLOW] = 1500,
        [GREEN] = 1500
};

static Led *leds[3];

static Color currentColor;
static Color nextColor = RED;
static bool isCurrentFlashing = false;
static bool isNextFlashing = false;

void trafficLightSetDuration(Color color, uint32_t duration) {
    durations[color] = duration;
}

uint32_t trafficLightGetDuration(Color color) {
    return durations[color];
}

void trafficLightUpdate() {
    if (ledFinishedLightning(leds[currentColor])) {
        currentColor = nextColor;
        isCurrentFlashing = isNextFlashing;
        switch (nextColor) {
        	case RED:
        		durations[RED] = durationRED;
				nextColor = GREEN;
				isNextFlashing = false;
				break;
        	case GREEN:
        		if (!isCurrentFlashing) {
        			isNextFlashing = true;
        			nextColor = GREEN;
        		} else {
        			isNextFlashing = false;
        			nextColor = YELLOW;
        		}
        		break;
        	case YELLOW:
				nextColor = RED;
				isNextFlashing = false;
				break;
        }
        if (!isCurrentFlashing) {
		    ledSetStateDuration(leds[currentColor], LED_TURN_ON, durations[currentColor]);
	    } else {
		    ledSetPeriod(leds[currentColor], durations[currentColor] >> 2, durations[currentColor]);
	    }
    }
    ledUpdateState(leds[RED]);
    ledUpdateState(leds[YELLOW]);
    ledUpdateState(leds[GREEN]);
}

void trafficLightInit(
		GPIO_TypeDef* red_port, uint16_t red_pin,
		GPIO_TypeDef* yellow_port, uint16_t yellow_pin,
		GPIO_TypeDef* green_port, uint16_t green_pin
) {
    leds[RED] = ledInit(LED_TURN_OFF, red_port, red_pin);
    leds[YELLOW] = ledInit(LED_TURN_OFF, yellow_port, yellow_pin);
    leds[GREEN] = ledInit(LED_TURN_OFF, green_port, green_pin);
}

void trafficLightStart() {
	nextColor = RED;
	isNextFlashing = false;
    trafficLightUpdate();
}

bool isButtonAllowed() {
	return currentColor == RED && getMode() == 1;
}

Color getCurrentColor() {
	return currentColor;
}

void setDurationRED(int duration) {
	durationRED = duration;
}
