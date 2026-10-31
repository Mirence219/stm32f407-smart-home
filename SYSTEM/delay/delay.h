#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f4xx.h"

#ifdef __cplusplus
extern "C" {
#endif

void Delay_Init(void);
void Delay_us(uint16_t ctr);
void Delay_ms(uint16_t ctr);
void Delay_xms(uint16_t nms);

#ifdef __cplusplus
}
#endif

#endif
