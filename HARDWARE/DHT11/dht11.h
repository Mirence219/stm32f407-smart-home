#ifndef __DHT11_H
#define __DHT11_H
#include "sys.h"
#include "delay.h"
#include "ili9486.h"
#include "gui.h"

#ifdef __cplusplus
extern "C" {
#endif

extern uint16_t temperature;
extern uint16_t humidity;

uint8_t DHT11_Init(GPIO_TypeDef *port, uint16_t pin);
uint8_t DHT11_Read_Data(uint16_t *temp, uint16_t *humi);	//��ȡ��ʪ��
uint8_t DHT11_Read_Byte(void);				//����һ���ֽ�
uint8_t DHT11_Read_Bit(void);				//����һ��λ
uint8_t DHT11_Check(void);					//����Ƿ����DHT11
void DHT11_Rst(void);						//��λDHT11
void DQ_OUT(void);
void DQ_IN(void);
void DHT11_Test(void);
void DHT11_WHILE(void);

#ifdef __cplusplus
}
#endif

#endif
