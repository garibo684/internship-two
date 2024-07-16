#include "led.h"

void LedBlink(GPIO_TypeDef *port, uint16_t pin)
{
	HAL_GPIO_TogglePin(port, pin);
	HAL_Delay(500);
}

void LedBlinkMid(GPIO_TypeDef *port, uint16_t pin)
{
	HAL_GPIO_TogglePin(port, pin);
	HAL_Delay(100);
}

void LedBlinkFast(GPIO_TypeDef *port, uint16_t pin)
{
	HAL_GPIO_TogglePin(port, pin);
}
