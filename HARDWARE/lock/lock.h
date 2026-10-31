#ifndef __JDQ_H_
#define __JDQ_H_
#include "sys.h"

#define Lock(X)   GPIO_WriteBit(GPIOI,GPIO_Pin_2,(BitAction)X)

#ifdef __cplusplus
extern "C" {
#endif

uint8_t Lock_Init(GPIO_TypeDef *port, uint16_t pin);
void Lock_WritePin(uint8_t enable);

#ifdef __cplusplus
}
#endif

#endif
