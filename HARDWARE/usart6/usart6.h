#ifndef __USART6_H_
#define __USART6_H_

#include "stm32f4xx.h"

#ifdef __cplusplus
extern "C" {
#endif

//定义串口接受最大存储的数据为50个字节,可根据实际需要修改定义
#define USART6_RX_SIZE 300
//储存串口6接收数据的数组
extern uint8_t usart6_buffer[];
//储存串口6接收数据数组的长度
extern uint16_t usart6_length;

//串口6的初始化函数
void USART6_Hardware_Init(uint32_t baudrate);
//串口6发送单字节数据
void USART6_Send_Byte(uint8_t src);
//串口6发送一定长度的字符串数据
void USART6_Send_Length_String(uint8_t *src,uint16_t length);
//串口6发送字符串数据
void USART6_Send_String(char *src);
//串口6清除储存数据
void USART6_Clear_Buffer(void);

#ifdef __cplusplus
}
#endif
	
#endif
