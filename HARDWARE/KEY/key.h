#ifndef __KEY_H_
#define __KEY_H_
#include "sys.h"

#define KEY0() 	GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) 
#define KEY1() 	GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)	
#define KEY2() 	GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2) 
#define KEY3() 	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)	

#ifdef __cplusplus
extern "C" {
#endif

void Key_Hardware_Init(void);	//IO��ʼ��
uint8_t Key_Scan(uint8_t);  		//����ɨ�躯��
void Key_InitPin(GPIO_TypeDef *port, uint16_t pin, uint8_t active_level);
uint8_t Key_ReadPin(GPIO_TypeDef *port, uint16_t pin);

#ifdef __cplusplus
}
#endif

#endif
