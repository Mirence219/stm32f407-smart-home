#ifndef __BEEP_H
#define __BEEP_H	 
#include "sys.h" 

#ifdef __cplusplus
extern "C" {
#endif

uint8_t BEEP_InitPin(GPIO_TypeDef *port, uint16_t pin);
void BEEP_WritePin(GPIO_TypeDef *port, uint16_t pin, uint8_t enabled);
void BEEP_TogglePin(GPIO_TypeDef *port, uint16_t pin);

#define BEEP(X) BEEP_WritePin(GPIOH, GPIO_Pin_7, (uint8_t)(X))

#ifdef __cplusplus
}
#endif

#endif
