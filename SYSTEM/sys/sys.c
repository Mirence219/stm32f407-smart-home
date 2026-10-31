#include "sys.h" 

//�ر������ж�(���ǲ�����fault��NMI�ж�)
void INTX_DISABLE(void)
{
    __disable_irq();
}
//���������ж�
void INTX_ENABLE(void)
{
    __enable_irq();
}

void SoftReset(void)
{
	__set_FAULTMASK(1);		//�ر������ж�
	NVIC_SystemReset();		//������λ
}
