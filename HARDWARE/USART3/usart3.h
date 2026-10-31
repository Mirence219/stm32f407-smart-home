#ifndef USART3_H
#define USART3_H

#include "stm32f4xx.h"

#define USART3_BUFFER_SIZE 512

extern volatile uint8_t usart3_buffer[USART3_BUFFER_SIZE];
extern volatile uint16_t usart3_length;

void USART3_Hardware_Init(uint32_t baudrate);
void USART3_Send_Data_length(const uint8_t *data, uint16_t length);
void USART3_Send_Length_String(const uint8_t *data, uint16_t length);

#endif
