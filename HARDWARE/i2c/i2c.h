#ifndef __I2C_H
#define __I2C_H
#include "sys.h" 

//IO操作函数	 
#define IIC_SCL(X)  GPIO_WriteBit(GPIOH,GPIO_Pin_4,(BitAction)X) 	//SCL
#define IIC_SDA(X)  GPIO_WriteBit(GPIOH,GPIO_Pin_5,(BitAction)X) 	//SDA	 
#define READ_SDA()  GPIO_ReadInputDataBit(GPIOH,GPIO_Pin_5)		    //输入SDA 

//IIC所有操作函数
void IIC_Init(void);                		//初始化IIC的IO口	
void SDA_OUT(void);						//PA4输出
void SDA_IN(void);  						//PA4输入
void IIC_Start(void);					//发送IIC开始信号
void IIC_Stop(void);	  					//发送IIC停止信号
void IIC_Send_Byte(uint8_t txd);			//IIC发送一个字节
uint8_t IIC_Read_Byte(unsigned char ack);	//IIC读取一个字节
uint8_t IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);						//IIC发送ACK信号
void IIC_NAck(void);						//IIC不发送ACK信号

void IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);

#endif

