#include "hardware/button.h"

static GPIO_TypeDef* port;
static uint16_t pin;
static buttonActionListener onClickHandler = NULL;

void buttonInit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
	port = GPIOx;
    pin = GPIO_Pin;
    onClickHandler = NULL;
}

void buttonSetOnClick(buttonActionListener actionListener) {
    onClickHandler = actionListener;
}

bool buttonIsPressed() {
    return HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_RESET ? true : false;
}

static volatile uint32_t clickStart = 0;

void buttonUpdateState() {
    uint32_t time = HAL_GetTick();
    bool isPressed = buttonIsPressed();

    if (!isPressed && clickStart > 0 && (time - clickStart) >= SHORT_CLICK) {
        clickStart = 0;
        if (onClickHandler != NULL)
            (*onClickHandler)();
    } else if (isPressed && clickStart == 0) {
        clickStart = time;
    }
}



