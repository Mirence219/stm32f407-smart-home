#include "stm32f4xx.h"
#include "fan.h"

/**************************************************************
功  能：通用定时器2中断初始化
参  数: arr：自动重装值
		 psc：时钟预分频数
		 定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
		 Ft=定时器工作频率,单位:Mhz
		 这里使用的是定时器2
返回值: 无
**************************************************************/
void TIM2_Int_Init(uint16_t arr, uint16_t psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);			// 使能GPIOA时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  			// 使能TIM2时钟
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM2); 		// GPIOA1复用为定时器2

    //GPIOA0初始化设置
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;						//
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;					// 复用功能
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				    // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			    // 100MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);						    // 初始化GPIO

    TIM_TimeBaseStructure.TIM_Period        = arr; 				    // 自动重装载值
    TIM_TimeBaseStructure.TIM_Prescaler     = psc;  				// 定时器分频
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up; 	// 向上计数模式
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;

    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);				    // 初始化TIM2

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 			    // 选择定时器模式:TIM脉冲宽度调制模式2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	// 比较输出使能
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;		// 输出极性:TIM输出比较极性低
    TIM_OC2Init(TIM2, &TIM_OCInitStructure);						// 根据T指定的参数初始化外设TIM2 OC1

    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);				// 使能TIM2在CCR1上的预装载寄存器

    TIM_ARRPreloadConfig(TIM2, ENABLE);							    // ARPE使能

    TIM_Cmd(TIM2, ENABLE);  										// 使能TIM2
}

/*******************************************************************
功  能：电动风扇节点模拟
参  数: duty：风速
返回值: 无
********************************************************************/
void Fan_Handle(uint8_t duty)
{
    if(duty == 0)
    {
        TIM_SetCompare2(TIM2, 0);
    }
    else if(duty == 1)
    {
        TIM_SetCompare2(TIM2, 100);
    }
    else if(duty == 2)
    {
        TIM_SetCompare2(TIM2, 150);
    }
    else if(duty == 3)
    {
        TIM_SetCompare2(TIM2, 200);
    }
}
