#ifndef HARDWARE_LED_H
#define HARDWARE_LED_H

#include <stdint.h>
#include <stdbool.h>

#include "stm32f4xx_hal.h"

struct Led;
typedef struct Led Led;
enum LedState { LED_TURN_ON, LED_TURN_OFF };
typedef enum LedState LedState;



void ledSetState(Led *led, LedState state);
void ledSetStateDuration(Led *led, LedState state, uint16_t duration);
LedState ledGetState(Led *led);
void ledSetPeriod(Led *led, uint16_t period, uint16_t duration);
Led* ledInit(LedState initState, GPIO_TypeDef* port, uint16_t pin);
void ledUpdateState(Led *led);
bool ledFinishedLightning(Led *led);


#endif //HARDWARE_LED_H
