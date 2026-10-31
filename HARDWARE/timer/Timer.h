#ifndef __TIMER_H__
#define __TIMER_H__

#include "stm32f4xx.h"

#ifdef __cplusplus
extern "C" {
#endif

extern volatile uint32_t global_times;
extern volatile uint32_t delay_ms_const;

void Timer_Init(uint16_t arr,uint16_t psc);
u32 gt_get_sub(u32 c);
u32 gt_get(void);
extern uint32_t time3_turn_counter;//定时上行发布
extern uint32_t mqtt_set_publish_time;


void Timer3_Hardware_Init(uint16_t arr,uint16_t pere);	//LED初始化

#ifdef __cplusplus
}
#endif

#endif

