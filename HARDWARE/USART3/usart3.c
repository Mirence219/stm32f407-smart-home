#include "usart3.h"

volatile uint8_t usart3_buffer[USART3_BUFFER_SIZE];
volatile uint16_t usart3_length = 0;

void USART3_Hardware_Init(uint32_t baudrate)
{
    GPIO_InitTypeDef gpio_init;
    USART_InitTypeDef usart_init;
    NVIC_InitTypeDef nvic_init;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);
    gpio_init.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    gpio_init.GPIO_Mode = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &gpio_init);

    USART_DeInit(USART3);
    usart_init.USART_BaudRate = baudrate;
    usart_init.USART_WordLength = USART_WordLength_8b;
    usart_init.USART_StopBits = USART_StopBits_1;
    usart_init.USART_Parity = USART_Parity_No;
    usart_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    usart_init.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART3, &usart_init);
    USART_ClearITPendingBit(USART3, USART_IT_RXNE);
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

    nvic_init.NVIC_IRQChannel = USART3_IRQn;
    nvic_init.NVIC_IRQChannelPreemptionPriority = 3;
    nvic_init.NVIC_IRQChannelSubPriority = 3;
    nvic_init.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic_init);

    usart3_length = 0;
    USART_Cmd(USART3, ENABLE);
}

void USART3_Send_Data_length(const uint8_t *data, uint16_t length)
{
    uint16_t i;
    if (data == 0)
    {
        return;
    }

    for (i = 0; i < length; ++i)
    {
        while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET)
        {
        }
        USART_SendData(USART3, data[i]);
    }
    while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
    {
    }
}

void USART3_Send_Length_String(const uint8_t *data, uint16_t length)
{
    USART3_Send_Data_length(data, length);
}

void USART3_IRQHandler(void)
{
    if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
    {
        const uint8_t data = (uint8_t)USART_ReceiveData(USART3);

        if (usart3_length < USART3_BUFFER_SIZE)
        {
            usart3_buffer[usart3_length++] = data;
        }
        else
        {
            usart3_length = 0;
            usart3_buffer[usart3_length++] = data;
        }
    }
}
