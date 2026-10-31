#ifndef __BH1750_H__
#define __BH1750_H__
#include "stm32f4xx.h"
#include "delay.h"
#include "i2c.h"
#include "ili9486.h"
#include "gui.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BH1750_Addr 0x46				//0100 0110   ����ַλ = 0x23��
#define BH1750_ON   0x01
#define BH1750_CON  0x10
#define BH1750_ONE  0x20
#define BH1750_RSET 0x07

uint8_t BH1750_Init(void);
uint8_t BH1750_Read_Lux(float *lux);
void Start_BH1750(void);				//�ϵ磬����������ݼĴ���
void Read_BH1750(void);					//�����Ķ�ȡ�ڲ��Ĵ�������
void Convert_BH1750(void);
void BH1750_Test(void); 

#ifdef __cplusplus
}
#endif

#endif
