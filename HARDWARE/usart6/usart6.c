#include "stm32f4xx.h"
#include "usart6.h"

//储存串口一接收数据数组的长度
uint16_t usart6_length = 0;

/****************************************************************
功  能：串口6的初始化函数
参  数：baudrate		串口6的波特率
返回值：无
*****************************************************************/
void USART6_Hardware_Init(uint32_t baudrate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//开启外设时钟GPIOA
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	//开启外设时钟USART6
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);
	
	//引脚复用映射PA9和PA10到串口上
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_USART6);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_USART6);
	
	//GPIOC6 - Tx 初始化
	//选择端口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	//复用模式
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	//推挽输出
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	//输出速度
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	//初始化配置
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	//GPIOC7 - Rx 初始化
	//选择端口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	//复用模式
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	//无上拉下拉
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//初始化配置
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	//串口参数设置
	//设置波特率
	USART_InitStructure.USART_BaudRate = baudrate;
	//设置串口模式
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	//设置无硬件流控制
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	//8bit数据位
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	//无校验位
	USART_InitStructure.USART_Parity = USART_Parity_No;
	//1停止位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	//初始化配置串口1
	USART_Init(USART6,&USART_InitStructure);
	
	//串口1中断响应优先级设置
	//选择中断通道
	NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;
	//设置先占优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	//设置从优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 8;
	//设置中断通道开启
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	//初始化配置中断优先级
	NVIC_Init(&NVIC_InitStructure);
	
	//开启串口1接受中断使能
	USART_ITConfig(USART6,USART_IT_RXNE,ENABLE);
	
	//开启串口1
	USART_Cmd(USART6,ENABLE);
}

//储存串口一接收数据的数组
uint8_t usart6_buffer[USART6_RX_SIZE] = { 0 };
uint8_t usart6_tc   = 0;	//串口接收数据时的计数器
uint8_t usart6_flag = 0;	//串口标志位,1 表示接收完成,0 表示可以接收数据

/****************************************************************
功  能：串口1的接收中断服务函数
参  数：无
返回值：无
*****************************************************************/
void USART6_IRQHandler(void)
{

	//判断串口接收中断标志位
    if(USART_GetITStatus(USART6,USART_IT_RXNE) == SET)
    {
		//读取串口数据
		usart6_buffer[usart6_length++] = USART_ReceiveData(USART6);
		//如果储存超出长度
		if(usart6_length >= USART6_RX_SIZE)
		{
			//重新从数组0开始储存字节
			usart6_length = 0;
		}
    }
	//清除串口中断接收标志位
	USART_ClearITPendingBit(USART6,USART_IT_RXNE);
}

/****************************************************************
功  能：串口1发送单字节数据
参  数：src	发送的单字节数据
返回值：无
*****************************************************************/
void USART6_Send_Byte(uint8_t src)
{
	//发送数据
	USART_SendData(USART6,src);
	//等待串口发送完成
	while(USART_GetFlagStatus(USART6,USART_FLAG_TXE) == RESET);
}

/****************************************************************
功  能：串口1发送一定长度的字节数据
参  数：src	发送的字符串数据,length	发送字节/字符的长度
返回值：无
*****************************************************************/
void USART6_Send_Length_String(uint8_t *src,uint16_t length)
{
	uint16_t Tx_cut = 0;
	uint16_t Tx_length = 0;
	Tx_length = length;
	//循环发送指定长度的数据
	while(Tx_cut != Tx_length)
	{
		//发送一个字节信息
		USART6_Send_Byte(*(src+Tx_cut));
		//指针自增
		Tx_cut++;
	}
}

/****************************************************************
功  能：串口1发送字符串数据
参  数：src	发送的字符串数据,以'\0'即0x00标识结束发送数据
返回值：无
*****************************************************************/
void USART6_Send_String(char *src)
{
	uint16_t Tx_cut = 0;
	//检测到下一个发送字节为'\0'时停止发送
	while(*(src+Tx_cut) != '\0')
	{
		//发送一个字节信息
		USART6_Send_Byte(*(src+Tx_cut));
		//指针自增
		Tx_cut++;
	}
}

/****************************************************************
功  能：串口1清除储存数组的数据
参  数：无
返回值：无
*****************************************************************/
void USART6_Clear_Buffer(void)
{
	while(usart6_length)	  //清空接收到的数据
	{
		//指针自减
		usart6_length--;
		//数据清零
		usart6_buffer[usart6_length] = 0;
	}
}

