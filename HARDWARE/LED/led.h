#ifndef __LED_H_
#define __LED_H_
#include "sys.h"
#include "led_gpio.h"

#define LED0(X) GPIO_WriteBit(GPIOF,GPIO_Pin_9,(BitAction)X)	// LED0
#define LED1(X) GPIO_WriteBit(GPIOF,GPIO_Pin_10,(BitAction)X)	// LED1	 
#define LED2(X) GPIO_WriteBit(GPIOH,GPIO_Pin_14,(BitAction)X)	// LED2
#define LED3(X) GPIO_WriteBit(GPIOH,GPIO_Pin_15,(BitAction)X)	// LED3	

#define LED0_TOGGLE()	GPIO_ToggleBits ( GPIOF , GPIO_Pin_9  )
#define LED1_TOGGLE()	GPIO_ToggleBits ( GPIOF , GPIO_Pin_10 )
#define LED2_TOGGLE()	GPIO_ToggleBits ( GPIOH , GPIO_Pin_14  )
#define LED3_TOGGLE()	GPIO_ToggleBits ( GPIOH , GPIO_Pin_15  )

#ifdef __cplusplus
extern "C" {
#endif

void LED_Hardware_Init(void);

#ifdef __cplusplus
}
#endif

#endif
