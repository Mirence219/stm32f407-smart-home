#include "stm32f4xx.h"
#include "beep.h"

static uint32_t beep_gpio_clock(GPIO_TypeDef *port)
{
	if (port == GPIOA) return RCC_AHB1Periph_GPIOA;
	if (port == GPIOB) return RCC_AHB1Periph_GPIOB;
	if (port == GPIOC) return RCC_AHB1Periph_GPIOC;
	if (port == GPIOD) return RCC_AHB1Periph_GPIOD;
	if (port == GPIOE) return RCC_AHB1Periph_GPIOE;
	if (port == GPIOF) return RCC_AHB1Periph_GPIOF;
	if (port == GPIOG) return RCC_AHB1Periph_GPIOG;
	if (port == GPIOH) return RCC_AHB1Periph_GPIOH;
	if (port == GPIOI) return RCC_AHB1Periph_GPIOI;
	return 0;
}

uint8_t BEEP_InitPin(GPIO_TypeDef *port, uint16_t pin)
{
	const uint32_t clock = beep_gpio_clock(port);
	GPIO_InitTypeDef GPIO_InitStructure;
	if (clock == 0 || pin == 0)
	{
		return 0;
	}

	RCC_AHB1PeriphClockCmd(clock, ENABLE);
	GPIO_ResetBits(port, pin);
	GPIO_InitStructure.GPIO_Pin = pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(port, &GPIO_InitStructure);
	return 1;
}

void BEEP_WritePin(GPIO_TypeDef *port, uint16_t pin, uint8_t enabled)
{
	GPIO_WriteBit(port, pin, enabled ? Bit_SET : Bit_RESET);
}

void BEEP_TogglePin(GPIO_TypeDef *port, uint16_t pin)
{
	GPIO_ToggleBits(port, pin);
}
