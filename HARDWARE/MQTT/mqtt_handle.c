#include "stm32f4xx.h"
#include "mqtt_handle.h"
#include "MQTTPacket.h"
#include "esp8266.h"
#include "string.h"
#include "stdio.h"
#include "usart3.h"
#include "string.h"
#include "timer.h"
#include "Delay.h"
//#include "GUI.h"
#include "ili9486.h"
#include "cjson.h"
#include "fan.h"
#include "dht11.h"

uint32_t Test_Value = 0;
MQTT_Parameter  BDTG_Device;

#define BUFMAX  400
uint8_t mqtt_buf[600] = {0};
uint8_t mqtt_data[600] = {0};  //���ڴ洢����
uint8_t esp8266_state = 0;

/*
char* mqtt_server = 	"115.28.209.116";//�������豸�͵ĵ�ַ 
char* mqtt_server_port = 	"1883";								 //��������Ӧ�˿ں�

char* platform_client_id = "20260319";                         //�ͻ���ID
char* platform_user_name = "bkrc";                                        //MQTT�˺�����
char* platform_password = "88888888";      //MQTT�˺�����
char* platform_topic_Name = "4560598837f074de";         //�豸��ʶ
char* platform_topic_SubName = "device/4560598837f074de/down";         //��������
char* platform_topic_PusName = "device/4560598837f074de/up";  //��������
*/

char* mqtt_server = 	"192.168.137.1";//�������豸�͵ĵ�ַ 
char* mqtt_server_port = 	"1883";								 //��������Ӧ�˿ں�

char* platform_client_id = "20260319";                         //�ͻ���ID
char* platform_user_name = "";                                        //MQTT�˺�����
char* platform_password = "";      //MQTT�˺�����
char* platform_topic_Name = "client";         //�豸��ʶ
char* platform_topic_SubName = "shixun/down";         //��������
char* platform_topic_PusName = "shixun/up";  //��������


char json_string[0x300]	=	{0};									//��ȡ����json��ʽ�ַ���
uint8_t mqtt_publish_state = 0;
uint8_t mqtt_connect_state = 0;
static char idat[128]={0};

void MQTT_Software_Init(void)										//������ʼ��
{					
	MQTT_Parameter_Init();
	if(esp8266_state)
	{
		//GUI_Show_Str(10,260,DARKBLUE,WHITE,"���ڽ�����ƽ̨..",32,0);
	}
	else
	{
		//GUI_Show_Str(30,260,RED,WHITE," WiFi����ʧ��...",32,0);
	}
	Delay_ms(500);
	sprintf(idat,"CIPSTART=\"TCP\",\"%s\",%s",mqtt_server,mqtt_server_port);	
	//GUI_Show_Str(10,260,DARKBLUE,WHITE,"����0",32,0);
	ESP8266_SCOM(idat,1);											//������վ
	//GUI_Show_Str(10,260,DARKBLUE,WHITE,"����1",32,0);
	ESP8266_SCOM("CIPMODE=1",1);									//����͸��ģʽ
	//GUI_Show_Str(10,260,DARKBLUE,WHITE,"����2",32,0);
	ESP8266_SCOM("CIPSEND",1);										//����͸��ģʽ
	//GUI_Show_Str(10,260,DARKBLUE,WHITE,"��������...",32,0);
	while(MQTT_Connect());											//���ӷ�����
	if(MQTT_Connect())
	{
		//GUI_Show_Str(10,260,DARKBLUE,WHITE,"������ƽ̨�ɹ�...",32,0);
		Delay_ms(500);
	}
	else	
	{
		//GUI_Show_Str(10,260,RED,WHITE,"������ƽ̨ʧ��...",32,0);
	}
	//GUI_Show_Str(10,260,DARKBLUE,WHITE,"������ƽ̨����...",32,0);
	Delay_ms(500);
	while(MQTT_Subscribe());										//����Ƶ��
	if(MQTT_Subscribe())
	{
		//GUI_Show_Str(10,260,RED,WHITE,"������ƽ̨ʧ��...",32,0);
	}
	else	
	{
		//GUI_Show_Str(10,260,DARKBLUE,WHITE,"������ƽ̨�ɹ�...",32,0);
		Delay_ms(500);
		TIM_Cmd(TIM3, ENABLE);											//������ʱ��3����������
	}
	
}

uint8_t MQTT_Date_Conversion(void)									//�����Ľ��������е�������ȡ��json_string[]����,ʧ�ܷ���0,�ɹ�����1
{
	uint16_t k_length = usart3_length, c_length = 0, rk_state = 0 , rk_length = 0,s_length = 0;
	
	for(c_length = 0; c_length < k_length; c_length++)
	{
		if(usart3_buffer[c_length]=='{')
		{
			rk_state = 1;
			rk_length++;
		}
		else if(usart3_buffer[c_length]=='}')
		{
			rk_length--;
		}
		if(rk_state)
		{
			if(rk_length)											//{}����Ч����
			{
				json_string[s_length++]=usart3_buffer[c_length];
			}
			else
			{
				json_string[s_length++] = '}';
				json_string[s_length++] = '\0';
				rk_state = 2;
				break;
			}
		}
	}
	if(rk_state == 2)												//����?��
	{
		return 1;
	}
	return 0;														//ת��ʧ��
}

/*
���ܣ�MQTT������ʼ��
������device ����ʼ�����豸
*/
void MQTT_Parameter_Init(void)
{	
	MQTT_Parameter *mqtt_device;	

	mqtt_device = &BDTG_Device;
	mqtt_device->client_id = (char *)platform_client_id;
	mqtt_device->user_name = (char *)platform_user_name;
	mqtt_device->password = (char *)platform_password;	
	mqtt_device->topic_SubName = (char *)platform_topic_SubName;
	mqtt_device->topic_PusName = (char *)platform_topic_PusName;
}


/*
���ܣ�MQTT���ݷ���
������*str ����   len  ����
˵������װ���ڷ��ͺ���
*/
void MQTT_Data_Send(uint8_t *str, uint16_t len)
{
    USART3_Send_Length_String(str,len);	
}


/*
���ܣ����MQTT���ݷ�����־
˵����ͨ��������Ϣ�����ж������ж�
*/
uint8_t MQTT_Check_Ack(uint8_t mode_ack)
{
	uint8_t ack_flag = 0;	
	if(usart3_length)
	{
		Delay_ms(10);
		switch(mode_ack)      //ѡ������������
		{
			case CONNACK:
				if(usart3_buffer[1] == 0x02 || usart3_buffer[2] == 0x00 || usart3_buffer[3] == 0x00) //0x00 ��ʾ���ӳɹ�
				{
				   ack_flag = CONNACK;	
				}
			break;
			case PUBACK: 
				ack_flag = PUBACK; 					   
			break;
			case SUBACK:
				if(usart3_buffer[1] == 0x03 || usart3_buffer[2] == 0x00 || usart3_buffer[3] == 0x01) //0x01 ��ʾ���ĳɹ�
				{
					ack_flag = SUBACK;
				}	
			break;
			case UNSUBACK:

			break;
			default:
			break;
		}			
	}
	return ack_flag;
}


/*
���ܣ����ӷ�����
������device �����ӵ��豸
*/
char connect_buf[450];
uint16_t connect_len = 0;
uint8_t MQTT_Connect(void)
{ 
	//GUI_Str_Center(0,200,BLUE,BACK_COLOR,"222",32,0);
	uint8_t wait_time = 5;
	MQTTPacket_connectData data = MQTTPacket_connectData_initializer;	
	MQTT_Parameter *mqtt_parameter;     //MQTT����ָ��
	int buflen = sizeof(connect_buf);
	
	MQTT_Parameter_Init();	
	mqtt_parameter = &BDTG_Device;
	data.clientID.cstring = mqtt_parameter->client_id;	//�ͻ��˱�ʶ�� ID payload
	data.keepAliveInterval = 60;					  	//keep Alive ��λs
	data.cleansession = 1;							  	//�����Ự��־��λ
	data.username.cstring = mqtt_parameter->user_name;	//�û���
	data.password.cstring = mqtt_parameter->password;	//�û�����
	data.MQTTVersion = 4;
	connect_len = MQTTSerialize_connect((uint8_t *)connect_buf, buflen, &data); //����0FFFE�˺�/�������?     ����0X0000�ڴ治��

	do{
		//GUI_Str_Center(0,200,BLUE,BACK_COLOR,"111",32,0);
		usart3_length = 0;
		MQTT_Data_Send((uint8_t *)connect_buf, connect_len);   //MQTT���ݷ��� 	
		Delay_ms(3000);
		wait_time--;	
		if(!wait_time)
		{	
			return 1;		//��ʱ�˳�
		}
	}while(MQTT_Check_Ack(CONNACK) != CONNACK); 

	return 0;
}


/*
���ܣ���Ϣ����
������*topic   ���ĵ�����
����ֵ��0���ĳɹ�  1����ʧ��
*/
unsigned char sub_buf[300];
uint8_t MQTT_Subscribe(void)
{
	uint8_t wait_time = 10;
	int buflen = sizeof(sub_buf);
	int msgid = 1;
	int req_qos = 0;
	uint16_t len;
	MQTTString topicString = MQTTString_initializer;
	MQTT_Parameter *mqtt_parameter;   //MQTT����ָ��
	
	MQTT_Parameter_Init();
	mqtt_parameter = &BDTG_Device;
	topicString.cstring = mqtt_parameter->topic_SubName;
	len = MQTTSerialize_subscribe(sub_buf, buflen, 0, msgid, 1, &topicString, &req_qos);
	
	do{
		usart3_length = 0;
		MQTT_Data_Send((uint8_t *)sub_buf, len);   //MQTT���ݷ���	
		Delay_ms(1000);
		wait_time--;	
		if(!wait_time)
		{	
			return 1;		//��ʱ�˳�
		}		
	}while(MQTT_Check_Ack(SUBACK) != SUBACK);
	
	return 0;
}



/*
���ܣ���Ϣ����
������*topic ����������
       *str  ����������
����ֵ��0����ʧ�� 1�����ɹ�
*/
unsigned char buf[0x300];
uint8_t MQTT_Publish(char *str)
{
	int buflen = sizeof(buf);
	uint16_t payloadlen,len;
	uint8_t *payload = (uint8_t *)str;
	MQTTString topicString = MQTTString_initializer;
	payloadlen = strlen(str);	
    MQTT_Parameter *mqtt_parameter;   //MQTT����ָ��

	mqtt_parameter = &BDTG_Device;
		
	topicString.cstring = mqtt_parameter->topic_PusName; 
	
	len = MQTTSerialize_publish(buf, buflen, 0, 0, 0, 0, topicString, (uint8_t *)payload, payloadlen);
	
	MQTT_Data_Send(buf, len);
	
	return 1;
}


/*
���ܣ����ֽ������ϴ����ݵ�OneNET (ֻ�ʺ�OneNETƽ̨������ƽ̨��ʹ��MQTT_Publish����)
������*topic ����������
       *id   id ��ʽ��char * id = "{\"ds_id\":\"data\"}
       *data  ���ݣ�
       datalen�����ݵĳ���		
����ֵ����
*/
uint8_t MQTT_PublishHex(char *topic, char *id, uint8_t *data, uint32_t datalen)
{
	
	uint32_t link = 0;			//����ƴ�ӱ�ʶ
	uint32_t linkdata = 0;
	uint32_t idLength = 0;		//����id����
	
		
	uint8_t payloadBuf[BUFMAX-3] = {0};	//���ƴ�Ӻ������,��ΪOneNET��Ҫ������λ��ʶ���Լ�ȥ3
	
	uint8_t buf[BUFMAX];					//������л��������
	
	uint32_t buflen = sizeof(buf);	    //���л����鳤��
	
	uint32_t payloadlen,len;				//��Ч���صĳ��ȣ�MQTT�����ܳ���
	
	uint8_t *payload;					//��Ч��������
	
	MQTTString topicString = MQTTString_initializer;
	
	idLength = strlen(id);

	payloadlen = idLength + datalen + 3 + 4;			
	
	payloadBuf[0] = 0x02;				//�ϴ�����2 �����Ƹ�ʽ
	payloadBuf[1] = (idLength>>8) & 0xff;//�ϴ����ݳ���  �߰�λ
	payloadBuf[2] = idLength & 0xff;	    //�ϴ����ݳ���  �Ͱ�λ
	
	for(; link<idLength; link++)
	{
		payloadBuf[3 + link] = id[link];	//ƴ���ַ�
	}
	payloadBuf[3+link] = (datalen>>24) & 0xff;	
	
	payloadBuf[4+link] = (datalen>>16) & 0xff;
	
	payloadBuf[5+link] = (datalen>>8) & 0xff;
	
	payloadBuf[6+link] = datalen & 0xff;
	
	
	for(; linkdata<idLength; linkdata++)
	{
		payloadBuf[7+link+linkdata] = data[linkdata]; //ƴ���ַ�
	}
	
	payload = (uint8_t *)payloadBuf;		
	topicString.cstring = topic;		  //�ϴ�������
	
	len = MQTTSerialize_publish(buf, buflen, 0, 0, 0, 0, topicString, payload, payloadlen); //���л����ݡ��������ݰ����ܳ���
	
	MQTT_Data_Send(buf, len);
	
	return 1;
}

/**********************************************************
*��  �ܣ���Json��ʽ�ϴ����ݵ�OneNET  (ֻ�ʺ�OneNETƽ̨������ƽ̨��ʹ��my_mqttPublish����)
*��  ����topic�����������⣻str �ϴ������ݸ�ʽ���£�
		char * payload_onenet = "{ \"datastreams\":[{\"id\":\"Tempreture\",\"datapoints\":[{\"value\":36}]}]}";
*����ֵ����
**********************************************************/

void PublishJson(char *str)
{
	uint32_t link =0;			//����ƴ��
	uint32_t botyLength = 0;		//���ݳ���
		
	uint8_t payloadBuf[BUFMAX-3] = {0};	//���ƴ�Ӻ������,��ΪOneNET��Ҫ������λ��ʶ���Լ�ȥ3
	
	uint8_t buf[BUFMAX];					//������л��������
	
	uint32_t buflen = sizeof(buf);					//���л����鳤��
	
	uint32_t payloadlen,len;							//��Ч���صĳ��ȣ�MQTT�����ܳ���
	
	uint8_t *payload;								//��Ч��������
	
	MQTTString topicString = MQTTString_initializer;
	

	botyLength = strlen(str);
	payloadlen = botyLength+3;
	
	
	payloadBuf[0] = 0x03;						//�ϴ�����1 json��ʽ
	payloadBuf[1] = (botyLength>>8)&0xff;		//�ϴ����ݳ���  �߰�λ
	payloadBuf[2] = (botyLength)&0xff;			//�ϴ����ݳ���  �Ͱ�λ
	
	for(;link<botyLength;link++)
	{
		payloadBuf[3+link] = str[link];			//ƴ���ַ�
	}
	
	
	payload=(u8 *)payloadBuf;					//
	topicString.cstring = platform_topic_PusName;				//�ϴ�������
	

	len = MQTTSerialize_publish(buf, buflen, 0, 0, 0, 0, topicString, payload, payloadlen);		//���л����ݡ��������ݰ����ܳ���
	
	Delay_ms(50);//�ȴ�50���룬��ֹ������һ���������ݻ�δ���?
	
	MQTT_Data_Send(buf,len);
	return ;
}

void MQTT_Heartbeat(void)
{
	uint8_t buf[] = {0xC0,0x00};
	if(mqtt_connect_state)
	{
		MQTT_Data_Send(buf,2);
		mqtt_connect_state = 0;
	}
}

void Platform_Auto_Login(void)
{
	ESP8266_Software_Init();
	MQTT_Software_Init();
}

/**************************************************************
*��  �ܣ������ϱ���ƽ̨
*��  ��: ��
*����ֵ: �� 
**************************************************************/
static char *out;
static char sdat[0x450] = { 0 };//����JSON�ĳ���
static cJSON  *bkrc_id,*receive_id,*testTem,*temF,*temT;
uint8_t num = 0;
char str[50];
void MQTT_Pub(void)
{
	if(mqtt_publish_state)
	{
		/*
		{
			"sign": "51c59d644193430c",
			"type": 1,
			"data": {
				"ģ����?": {
					"ģ�ͱ�ʶ": 23
				}
			}
		}
		*/
		 //����json��ʽ
		bkrc_id=cJSON_CreateObject();
		cJSON_AddStringToObject(bkrc_id,"sign",platform_topic_Name);
		cJSON_AddStringToObject(bkrc_id,"type","3");
		
		cJSON_AddItemToObject(bkrc_id, "data",testTem = cJSON_CreateObject());
		cJSON_AddItemToObject(testTem, "tempHum",temT = cJSON_CreateObject());
		
		cJSON_AddNumberToObject(temT,"tempValue",temperature/10);
		cJSON_AddNumberToObject(temT,"humValue",humidity/10);
		//0x00�ڵ�״̬
		cJSON_AddItemToObject(testTem, "FAN",temF = cJSON_CreateObject());
		
		cJSON_AddNumberToObject(temF,"FAN_Sta",Test_Value);

		
		out=cJSON_Print(bkrc_id);									//ת��Ϊ�ַ���
		sprintf(sdat,"%s",out);										//��ȡ����̬�ڴ�
		MQTT_Publish(sdat);											//����ȡ���ݷ���
		cJSON_Delete(bkrc_id);										//�ͷ�
		free(out);													//�ͷ�
		
		mqtt_publish_state = 0;
		
	}
	MQTT_Heartbeat();		//��ʱ������
}
/**************************************************************
*��  �ܣ�������ƽ̨�·�����
*��  ��: ��
*����ֵ: �� 
**************************************************************/
static cJSON *message,*messdata;
char *mess_str;

char str[50];
void MQTT_Receive(void)
{
	char *str_1 = "msg";
	char *str_2;
	if (usart3_length)//�жϴ������ݽ���
	{
		Delay_ms(50);
		if (MQTT_Date_Conversion())                        //��ȡ��Ч����,��Ч��ֱ���˳�
		{
			receive_id = cJSON_Parse(json_string);            //��ȡ�����е��ض���ʽ��ȥ�����ݵ�ͷ
			if (receive_id != NULL)
			{
					cJSON *sta = cJSON_GetObjectItem(receive_id, "FAN_Sta");
					if (sta != NULL && cJSON_IsNumber(sta))
					{
						Test_Value = sta->valueint; // ��ȡ����ֵ
						Fan_Handle(Test_Value);
						if(Test_Value == 1)
						{
							//GUI_Str_Center(0,350,BLUE,BACK_COLOR,"���ȿ���",32,0);
						}
						else
						{
							//GUI_Str_Center(0,350,BLUE,BACK_COLOR,"���ȹر�",32,0);
						}
					}
//					/******��Ч��Json���ݣ�������ȡ��Ҫ��lock��ֵ
//					{
//						"message":
//						{
//							"Test_Num":25
//						},
//						"type":"msg"
//					*/
//				message      = cJSON_GetObjectItem(receive_id, "message");
//				str_2 = cJSON_GetObjectItem(receive_id, "type")->valuestring;
//				if(strcmp(str_1, str_2) == 0)           //�ж��Ƿ����������·����ݣ�������ƽ̨���󷵻ص�����
//				{
//					mess_str = message->valuestring;			//��ȡ�ַ���
//					messdata = cJSON_Parse(mess_str);    	//��ȡ�����е��ض���ʽ��ȥ�����ݵ�ͷ
//					if(messdata != NULL)
//					{																		
//						Test_Value = cJSON_GetObjectItem(messdata, "FAN_Sta")->valueint;//��ȡRLED����������?����int��
//					}
//					else
//					{
//						Test_Value = cJSON_GetObjectItem(message, "FAN_Sta")->valueint;//��ȡrValue����������?����int��
//					}
//					Fan_Handle(Test_Value);
//					if(Test_Value == 1)
//					{
//						//GUI_Str_Center(0,350,BLUE,BACK_COLOR,"���ȿ���",32,0);
//					}
//					else
//					{
//						//GUI_Str_Center(0,350,BLUE,BACK_COLOR,"���ȹر�",32,0);
//					}
//				}
				cJSON_Delete(bkrc_id);
			}
		}
		usart3_length = 0;
	}
}
