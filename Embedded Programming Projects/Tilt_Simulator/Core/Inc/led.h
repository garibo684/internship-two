#ifndef INC_LED_H_
#define INC_LED_H_

#include "main.h"


void LedBlink(GPIO_TypeDef *port, uint16_t pin);
void LedBlinkMid(GPIO_TypeDef *port, uint16_t pin);
void LedBlinkFast(GPIO_TypeDef *port, uint16_t pin);


#endif /* INC_LED_H_ */
