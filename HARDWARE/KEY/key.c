#include "stm32f4xx.h"
#include "key.h"
#include "delay.h" 

static uint8_t key_clocks_initialized = 0;

void Key_InitPin(GPIO_TypeDef *port, uint16_t pin, uint8_t active_level)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	if (key_clocks_initialized == 0)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOA, ENABLE);
		key_clocks_initialized = 1;
	}

	GPIO_InitStructure.GPIO_Pin = pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = active_level ? GPIO_PuPd_DOWN : GPIO_PuPd_UP;
	GPIO_Init(port, &GPIO_InitStructure);
}

uint8_t Key_ReadPin(GPIO_TypeDef *port, uint16_t pin)
{
	return (uint8_t)GPIO_ReadInputDataBit(port, pin);
}

/**************************************************************
��  �ܣ�������ʼ������
��  ��: ��
����ֵ: ��
**************************************************************/
void Key_Hardware_Init(void)
{
	Key_InitPin(GPIOE, GPIO_Pin_4, Bit_RESET);
	Key_InitPin(GPIOE, GPIO_Pin_3, Bit_RESET);
	Key_InitPin(GPIOE, GPIO_Pin_2, Bit_RESET);
	Key_InitPin(GPIOA, GPIO_Pin_0, Bit_SET);
} 

/**************************************************************
��  �ܣ�������������
��  ��: mode:0,��֧��������;1,֧��������;
����ֵ: 0��û���κΰ�������
		1��KEY0����
		2��KEY1����
		3��KEY2����
		4��KEY3����
		ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>WK_UP!!
**************************************************************/
uint8_t Key_Scan(uint8_t mode)
{	 
	static uint8_t key_up=1;		//�������ɿ���־
	if(mode)key_up=1;		//֧������		  
	if(key_up&&(KEY0()==0||KEY1()==0||KEY2()==0||KEY3()==1))
	{
		Delay_ms(10);		//ȥ���� 
		key_up=0;
		if(KEY0()==0)return 1;
		else if(KEY1()==0)return 2;
		else if(KEY2()==0)return 3;
		else if(KEY3()==1)return 4;
	}else if(KEY0()==1&&KEY1()==1&&KEY2()==1&&KEY3()==0)key_up=1; 	    
 	return 0;				//�ް�������
}
