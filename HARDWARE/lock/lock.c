#include "stm32f4xx.h"
#include "lock.h"

uint8_t Lock_Init(GPIO_TypeDef *port, uint16_t pin)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);	//使能GPIO时钟
	//选择端口
	GPIO_InitStructure.GPIO_Pin = pin;	
	//输出模式
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	//推挽输出
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	//输出速度
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	//初始化配置
	GPIO_Init(port, &GPIO_InitStructure);
	return 1;
}

void Lock_WritePin(uint8_t enabled)
{
	Lock(enabled);
}


