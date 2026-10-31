#include "dht11.h"
#include <stdio.h>
#include <stddef.h>

static GPIO_TypeDef *dht11_port = 0;
static uint16_t dht11_pin = 0;

static uint32_t DHT11_GPIO_Clock(GPIO_TypeDef *port)
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

#define DHT11_IO_IN()    DQ_IN()
#define DHT11_IO_OUT()   DQ_OUT()
#define DHT11_DQ_OUT(X)  GPIO_WriteBit(dht11_port, dht11_pin, (BitAction)(X))
#define DHT11_DQ_IN()    GPIO_ReadInputDataBit(dht11_port, dht11_pin)

uint16_t temperature;
uint16_t humidity;
/**************************************************************
*��  �ܣ���λDHT11
*��  ��: ��
*����ֵ: ��
**************************************************************/
void DHT11_Rst(void)
{
    DHT11_IO_OUT(); 	//SET OUTPUT
    DHT11_DQ_OUT(0); 	//����DQ
    Delay_ms(20);    	//��������18ms
    DHT11_DQ_OUT(1); 	//DQ=1
    Delay_us(40);     	//��������20~40us
}

/**************************************************************
*��  �ܣ��ȴ�DHT11�Ļ�Ӧ
*��  ��: ��
*����ֵ: ����1:δ��⵽DHT11�Ĵ��ڣ� ����0:����
**************************************************************/
uint8_t DHT11_Check(void)
{
    uint8_t retry = 0;
    DHT11_IO_IN();						//SET INPUT

    while (DHT11_DQ_IN() && retry < 100)		//DHT11������40~80us
    {
        retry++;
        Delay_us(1);
    }

    if(retry >= 100)return 1;
    else retry = 0;

    while (!DHT11_DQ_IN() && retry < 100)		//DHT11���ͺ���ٴ�����40~80us
    {
        retry++;
        Delay_us(1);
    }

    if(retry >= 100)return 1;

    return 0;
}

/**************************************************************
*��  �ܣ���DHT11��ȡһ��λ
*��  ��: ��
*����ֵ: 1/0
**************************************************************/
uint8_t DHT11_Read_Bit(void)
{
    uint8_t retry = 0;

    while(DHT11_DQ_IN() && retry < 100)	//�ȴ���Ϊ�͵�ƽ
    {
        retry++;
        Delay_us(1);
    }

    retry = 0;

    while(!DHT11_DQ_IN() && retry < 100)	//�ȴ���ߵ�ƽ
    {
        retry++;
        Delay_us(1);
    }

    Delay_us(40);					//�ȴ�40us

    if(DHT11_DQ_IN())return 1;
    else return 0;
}

/**************************************************************
*��  �ܣ���DHT11��ȡһ���ֽ�
*��  ��: ��
*����ֵ: ����������
**************************************************************/
uint8_t DHT11_Read_Byte(void)
{
    uint8_t i, dat;
    dat = 0;

    for (i = 0; i < 8; i++)
    {
        dat <<= 1;
        dat |= DHT11_Read_Bit();
    }

    return dat;
}

/**************************************************************
*��  �ܣ���DHT11��ȡһ������
*��  ��: temp:�¶�ֵ(��Χ:0~50��)��humi:ʪ��ֵ(��Χ:20%~90%)
*����ֵ: 0,����;1,��ȡʧ��
**************************************************************/
uint8_t DHT11_Read_Data(uint16_t *temp, uint16_t *humi)
{
    uint8_t buf[5];
    uint8_t i;
    uint16_t new_humi;
    uint16_t new_temp;

    if (temp == 0 || humi == 0 || dht11_port == 0 || dht11_pin == 0)
    {
        return 1;
    }

    DHT11_Rst();

    if(DHT11_Check() == 0)
    {
        for(i = 0; i < 5; i++)	//��ȡ40λ����
        {
            buf[i] = DHT11_Read_Byte();
        }

        if((buf[0] + buf[1] + buf[2] + buf[3]) == buf[4])
        {
            new_humi = buf[0] * 10 + buf[1];
            new_temp = buf[2] * 10 + buf[3];
            *humi = new_humi;
            *temp = new_temp;
            temperature = new_temp;
            humidity = new_humi;
            return 0;
        }
        return 1;
    }
    else return 1;
}

/**************************************************************
*��  �ܣ���ʼ��DHT11��IO�� DQ��ͬʱ���DHT11�Ĵ���
*��  ��: ��
*����ֵ: ����1:�����ڣ�����0:����
**************************************************************/
uint8_t DHT11_Init(GPIO_TypeDef *port, uint16_t pin)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    uint32_t gpio_clock = DHT11_GPIO_Clock(port);

    if (gpio_clock == 0 || pin == 0 || (pin & (pin - 1)) != 0)
    {
        return 1;
    }

    dht11_port = port;
    dht11_pin = pin;
    RCC_AHB1PeriphClockCmd(gpio_clock, ENABLE);

    GPIO_InitStructure.GPIO_Pin = pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(port, &GPIO_InitStructure);
    GPIO_SetBits(port, pin);

    DHT11_Rst();
    return DHT11_Check();
}

/**************************************************************
*��  �ܣ���ʼ������˿�
*��  ��: ��
*����ֵ: ��
**************************************************************/
void DQ_OUT(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    if (dht11_port == 0 || dht11_pin == 0) return;
    GPIO_InitStructure.GPIO_Pin = dht11_pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(dht11_port, &GPIO_InitStructure);
}

/**************************************************************
*��  �ܣ���ʼ������˿�
*��  ��: ��
*����ֵ: ��
**************************************************************/
void DQ_IN(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    if (dht11_port == 0 || dht11_pin == 0) return;
    GPIO_InitStructure.GPIO_Pin = dht11_pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(dht11_port, &GPIO_InitStructure);
}

/**************************************************************
*��  �ܣ�DHT11���������
*��  ��: ��
*����ֵ: ��
**************************************************************/
void DHT11_WHILE(void)
{
    while(DHT11_Init(GPIOA, GPIO_Pin_1))
    {
        Delay_ms(50);
    }
}
/**************************************************************
*��  �ܣ���ȡ��ʪ��ֵ
*��  ��: ��
*����ֵ: ��
**************************************************************/
void DHT11_Test()
{
}

