#ifndef __MQTT_HANDLE_H_
#define __MQTT_HANDLE_H_

#include "stm32f4xx.h"

#ifdef __cplusplus
extern "C" {
#endif

//������ƽ̨����Ĳ���
typedef struct _MQTT_Parameter_{
	char *client_id;     //�豸������������Ӱ�����ƣ�
	char *user_name;     //�û�����������Ӱ��ʱƽ̨���ɣ�
	char *password;      //���루������Ӱ��ʱƽ̨���ɣ�
    char *topic_SubName; //������������ƣ�Ҫ�յ��Ǹ����ⷢ������Ϣ�� 
	char *topic_PusName; //������������ƣ�������Ϣ�����⣩
}MQTT_Parameter;

extern char* mqtt_server;//�������豸�͵ĵ�ַ 
extern char* mqtt_server_port;//��������Ӧ�˿ں�

extern char* platform_client_id;
extern char* platform_user_name;
extern char* platform_password;	
extern char* platform_topic_SubName;
extern char* platform_topic_PusName;
extern uint8_t esp8266_state;

extern uint8_t mqtt_publish_state;
extern uint8_t mqtt_connect_state;
extern char json_string[];
void MQTT_Software_Init(void);
uint8_t MQTT_Date_Conversion(void);

//void MQTT_Data_Receive(uint8_t dat);
void MQTT_Parameter_Init(void);
uint8_t MQTT_Connect(void);
uint8_t MQTT_Subscribe(void);
uint8_t MQTT_Publish(char *str);
uint8_t MQTT_PublishHex(char *topic, char *id, uint8_t *data, uint32_t datalen);
void PublishJson(char *str);
void MQTT_Heartbeat(void);
void Platform_Auto_Login(void);
void MQTT_Receive(void);
void MQTT_Pub(void);

#ifdef __cplusplus
}
#endif

#endif

