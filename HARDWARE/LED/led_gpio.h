#ifndef LED_GPIO_H
#define LED_GPIO_H

#include "stm32f4xx.h"

#ifdef __cplusplus
extern "C" {
#endif

void LED_InitPin(GPIO_TypeDef *port, uint16_t pin);
void LED_WritePin(GPIO_TypeDef *port, uint16_t pin, uint8_t enabled);
void LED_TogglePin(GPIO_TypeDef *port, uint16_t pin);

#ifdef __cplusplus
}
#endif

#endif
