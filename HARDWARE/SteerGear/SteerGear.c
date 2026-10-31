#include "SteerGear.h"

void SteerGear_Init(void)
{
    TIM_TimeBaseInitTypeDef time_base;
    TIM_OCInitTypeDef output_compare;
    GPIO_InitTypeDef gpio;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM2);

    gpio.GPIO_Pin = GPIO_Pin_1;
    gpio.GPIO_Mode = GPIO_Mode_AF;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_Speed = GPIO_Speed_100MHz;
    gpio.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &gpio);

    time_base.TIM_Period = 19999;
    time_base.TIM_Prescaler = 83;
    time_base.TIM_CounterMode = TIM_CounterMode_Up;
    time_base.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM2, &time_base);

    TIM_OCStructInit(&output_compare);
    output_compare.TIM_OCMode = TIM_OCMode_PWM1;
    output_compare.TIM_OutputState = TIM_OutputState_Enable;
    output_compare.TIM_OCPolarity = TIM_OCPolarity_High;
    output_compare.TIM_Pulse = 500;
    TIM_OC2Init(TIM2, &output_compare);
    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM2, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
}

void SteerGear_SetPosition(uint8_t position)
{
    static const uint16_t PULSE_WIDTHS[5] = {500, 1000, 1500, 2000, 2500};
    if (position > 4)
    {
        position = 4;
    }
    TIM_SetCompare2(TIM2, PULSE_WIDTHS[position]);
}
