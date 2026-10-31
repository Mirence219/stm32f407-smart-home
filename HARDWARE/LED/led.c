#include "stm32f4xx.h"
#include "led.h" 

static uint8_t led_clocks_initialized = 0;

void LED_InitPin(GPIO_TypeDef *port, uint16_t pin)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	if (led_clocks_initialized == 0)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOH, ENABLE);
		led_clocks_initialized = 1;
	}

	GPIO_ResetBits(port, pin);
	GPIO_InitStructure.GPIO_Pin = pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(port, &GPIO_InitStructure);
}

void LED_WritePin(GPIO_TypeDef *port, uint16_t pin, uint8_t enabled)
{
	GPIO_WriteBit(port, pin, enabled ? Bit_SET : Bit_RESET);
}

void LED_TogglePin(GPIO_TypeDef *port, uint16_t pin)
{
	GPIO_ToggleBits(port, pin);
}

/*******************************************************************
��  �ܣ�LED IO��ʼ��  
��  ��: ��
����ֵ: ��
********************************************************************/
void LED_Hardware_Init(void)
{
	LED_InitPin(GPIOF, GPIO_Pin_9);
	LED_InitPin(GPIOF, GPIO_Pin_10);
	LED_InitPin(GPIOH, GPIO_Pin_14);
	LED_InitPin(GPIOH, GPIO_Pin_15);
}
