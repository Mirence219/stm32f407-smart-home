#ifndef __FAN_H
#define __FAN_H

#define FAN_OUT(X)	GPIO_WriteBit ( GPIOA , GPIO_Pin_1 , (BitAction) !X )

#include "sys.h"

#ifdef __cplusplus

extern "C" {
#endif

void TIM2_Int_Init(uint16_t arr, uint16_t psc);
void Fan_Handle(const uint8_t duty);

#ifdef __cplusplus
}
#endif

#endif
