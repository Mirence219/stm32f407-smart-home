#include "stm32f4xx.h"
#include "esp8266.h"
#include "string.h"
#include "stdio.h"
#include "usart3.h"
#include "mqtt_handle.h"
#include "gui.h"
#include "delay.h"
#include "ili9486.h"

char* ssid = "MIRENCE 6418";			//���ӵ�·�������ȵ㣩������
char* password = "50921S>y";	//���ӵ�·�������ȵ㣩������ 


uint8_t esp8266_connect_state = 0;


uint8_t ESP8266_CheckOK(uint16_t wait_time)
{
	while(wait_time--)
	{
		if(usart3_length)
		{
			Delay_ms(5);
			if(usart3_length>3)
			{
				if((usart3_buffer[usart3_length-4] == 'O') && (usart3_buffer[usart3_length-3]=='K')\
					 && (usart3_buffer[usart3_length-2] == 0x0d) && (usart3_buffer[usart3_length-1]==0x0a))		
				{
					return 0;				//ok
				}
			}
			if(usart3_length>6)
			{
				if((usart3_buffer[usart3_length-7] == 'O') && (usart3_buffer[usart3_length-6]=='K')\
					 && (usart3_buffer[usart3_length-5] == 0x0d) && (usart3_buffer[usart3_length-1]==0x3e))		
				{
					return 0;				//ok
				}
			}
			if(usart3_length>3)
			{
				if((usart3_buffer[usart3_length-4] == 'O') && (usart3_buffer[usart3_length-3]=='R')\
					 && (usart3_buffer[usart3_length-2] == 0x0d) && (usart3_buffer[usart3_length-1]==0x0a))
				{
					if( (usart3_buffer[0] == 'A') && (usart3_buffer[1] == 'L') && (usart3_buffer[2] == 'R') \
						&& (usart3_buffer[3] == 'E') && (usart3_buffer[4] == 'A') && (usart3_buffer[5] == 'D') )
					{
						return 0; 			//ALREADY_OK
					}
					return 1;				//error
				}	
			}
			usart3_length = 0;			
		}
		Delay_ms(10);
	}
	return 2;							//other,overtime
}

static char edat[128]={0};
uint8_t ESP8266_SCOM(char *sdat,uint8_t mode)
{
	char st[4]={0x41,0x54,0x2B};		//AT+
	char et[3]={0x0D,0x0A};				//�س�����
	while(1)
	{
		usart3_length = 0;
		sprintf(edat,"%s%s%s",st,sdat,et);
		USART3_Send_Length_String((uint8_t *)edat,strlen(edat));
		char p[10];
		sprintf(p, "%d", ESP8266_CheckOK(1000));
		if(!ESP8266_CheckOK(1000))		//�ȴ����ճɹ���break�˳�����1
		{
			break;
		}
		else
		{
			if(!mode)					//ʧ�ܷ���0
			{
				return 0;
			}
		
		}
	}
		
	return 1;
}

static char sdat[64]={0};

void ESP8266_Software_Init(void)
{
	uint8_t connect_state = 0;
	uint8_t outmode[3] = {"+++"};
	uint8_t edat [6] = { 0x41,0x54,0x45,0x30,0x0D,0x0A };
	GUI_Show_Str(30,260,DARKBLUE,WHITE," WiFiģ��������...    ",32,0);
	while(1)
	{	
		if(!usart3_length)							
		{
			USART3_Send_Length_String(outmode,3);									//�˳�ESP8266�����Ѿ������͸��ģʽ(����������Ӱ��)
			Delay_ms(100);
			USART3_Send_Length_String(edat,6);
			Delay_ms(100);
		}
		else
		{
			GUI_Show_Str(30,260,DARKBLUE,WHITE," WiFi������...    ",32,0);
			Delay_ms(10);
			if(usart3_length>4)
			{
				Delay_ms(5);
				if((usart3_buffer[2] == 0x4f) && (usart3_buffer[3]==0x4b)\
				 && (usart3_buffer[4] == 0x0d) && (usart3_buffer[5]==0x0a))		//�ж�ESP8266��Ч��ʽ
				{
					usart3_length = 0;
					break;
				}
			}
			usart3_length = 0;
		}
	}
	ESP8266_SCOM("CWMODE=1",1);								//��Ϊ�ӻ�����·�������ȵ㣩
	sprintf(sdat,"CWJAP_DEF=\"%s\",\"%s\"",ssid,password);	//�ϳ��ַ�
	connect_state = ESP8266_SCOM(sdat,0);
	if(connect_state)
	{
		esp8266_state = 1;
		GUI_Show_Str(30,260,DARKBLUE,WHITE," WiFi���ӳɹ�...  ",32,0);
		Delay_ms(500);
	}
	else
	{
		GUI_Show_Str(30,260,RED,WHITE," WiFi����ʧ��...",32,0);
		ESP8266_Software_Init();
	}
	
	
}














