#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <hardware/led.h>

enum Color { RED = 0, YELLOW = 1, GREEN = 2 };

static char* color_names[] = {
	[RED] = "red",
	[YELLOW] = "yellow",
	[GREEN] = "green"
};

typedef enum Color Color;

void trafficLightUpdate();
void trafficLightSetDuration(Color color, uint32_t duration);
uint32_t trafficLightGetDuration(Color color);
void trafficLightStart();
void trafficLightInit(
		GPIO_TypeDef* red_port, uint16_t red_pin,
		GPIO_TypeDef* yellow_port, uint16_t yellow_pin,
		GPIO_TypeDef* green_port, uint16_t green_pin
);
bool isButtonAllowed();
Color getCurrentColor();
void setDurationRED(int duration);

#endif //TRAFFICLIGHT_H
