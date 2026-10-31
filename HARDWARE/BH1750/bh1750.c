#include "bh1750.h"
#include <stdio.h>

uint8_t BUF[2]={0};
uint16_t result1750=0;

static uint8_t BH1750_Write_Command(uint8_t command)
{
	IIC_Start();
	IIC_Send_Byte(BH1750_Addr);
	if (IIC_Wait_Ack())
	{
		IIC_Stop();
		return 0;
	}
	IIC_Send_Byte(command);
	if (IIC_Wait_Ack())
	{
		IIC_Stop();
		return 0;
	}
	IIC_Stop();
	return 1;
}

static uint8_t BH1750_Read_Raw(uint16_t *raw)
{
	uint8_t high_byte;
	uint8_t low_byte;
	if (raw == 0)
	{
		return 0;
	}

	IIC_Start();
	IIC_Send_Byte(BH1750_Addr + 1);
	if (IIC_Wait_Ack())
	{
		IIC_Stop();
		return 0;
	}
	high_byte = IIC_Read_Byte(1);
	low_byte = IIC_Read_Byte(0);
	IIC_Stop();
	*raw = ((uint16_t)high_byte << 8) | low_byte;
	return 1;
}
/**************************************************************
*��  �ܣ��˿ڳ�ʼ��
*��  ��: ��
*����ֵ: �� 
**************************************************************/
uint8_t BH1750_Init(void)
{
	IIC_Init();
	if (!BH1750_Write_Command(BH1750_ON) ||
		!BH1750_Write_Command(BH1750_RSET) ||
		!BH1750_Write_Command(BH1750_CON))
	{
		return 0;
	}
	Delay_ms(120);
	return 1;
}

/**************************************************************
*��  �ܣ������豸��ַ
*��  ��: ��
*����ֵ: �� 
**************************************************************/
void Cmd_Write_BH1750(uint8_t cmd)
{
	BH1750_Write_Command(cmd);
	Delay_ms(5);
}


/**************************************************************
*��  �ܣ�����һ��H�ֱ���ģʽ
*��  ��: ��
*����ֵ: �� 
**************************************************************/
void Start_BH1750(void)
{
	Cmd_Write_BH1750(BH1750_ON);
	Cmd_Write_BH1750(BH1750_RSET);
	Cmd_Write_BH1750(BH1750_ONE);
}

/**************************************************************
*��  �ܣ��������ź�
*��  ��: ��
*����ֵ: �� 
**************************************************************/
void Read_BH1750(void)
{
	uint16_t raw;
	if (BH1750_Read_Raw(&raw))
	{
		BUF[0] = (uint8_t)(raw >> 8);
		BUF[1] = (uint8_t)raw;
		result1750 = raw;
	}
	else
	{
		BUF[0] = 0;
		BUF[1] = 0;
	}
}

/**************************************************************
*��  �ܣ��ϳɹ�������
*��  ��: ��
*����ֵ: �� 
**************************************************************/
void Convert_BH1750(void)
{
	result1750=BUF[0];
	result1750=(result1750<<8)+BUF[1];		//�ϳ����ݣ�����������
	result1750=(double)result1750/1.2;
}

uint8_t BH1750_Read_Lux(float *lux)
{
	uint16_t raw;
	if (lux == 0 || !BH1750_Read_Raw(&raw))
	{
		return 0;
	}

	*lux = (float)raw / 1.2f;
	result1750 = (uint16_t)*lux;
	return 1;
}

/**************************************************************
*��  �ܣ���ʾ��������
*��  ��: ��
*����ֵ: �� 
**************************************************************/
void BH1750_Test()
{
	char show[20];
	
	Start_BH1750();						//����һ��H�ֱ���ģʽ
    Delay_ms(120);						//��ʱ120ms
    Read_BH1750();						//������ȡ��� ��BUF���� 
    Convert_BH1750();					//ת�������result_lx

    sprintf(show," ���ն�: %4d Lx ",result1750);
    GUI_Str_Center(0, 360, BLACK, CONTENT_COLOR, show, 24, 0);
}
