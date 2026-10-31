#ifndef __ILI9486_H_
#define __ILI9486_H_

#include "stm32f4xx.h"
#include "stdlib.h"
#include "delay.h"

//ʱ�Ӷ���
#define LCD_ALL_GPIO_CLOCK      RCC_AHB1Periph_GPIOB   | RCC_AHB1Periph_GPIOC \
                                | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE \
                                | RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOG
#define LCD_FMSC_CLOCK          RCC_AHB3Periph_FSMC

//ʱ��ʹ�ܶ���
#define LCD_GPIO_CLOCK_INIT     RCC_AHB1PeriphClockCmd
#define LCD_FMSC_CLOCK_INIT     RCC_AHB3PeriphClockCmd

/********************LCD��ض���********************/
//LCD��λRESET����
#define LCD_RESET_PORT			GPIOB
#define LCD_RESET_PIN			GPIO_Pin_2

//LCD����BL����
#define LCD_BL_PORT             GPIOB
#define LCD_BL_PIN              GPIO_Pin_0

//FSMC D2,D3,NOE,NWE,D13,D14,D15,D0,D1
#define FSMC_PORT_1             GPIOD
#define FSMC_ALL_PIN_1          GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | \
                                GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15
#define FSMC_D2_PIN_SOURCE      GPIO_PinSource0
#define FSMC_D3_PIN_SOURCE      GPIO_PinSource1
#define FSMC_NOE_PIN_SOURCE     GPIO_PinSource4
#define FSMC_NWE_PIN_SOURCE     GPIO_PinSource5
#define FSMC_D13_PIN_SOURCE     GPIO_PinSource8
#define FSMC_D14_PIN_SOURCE     GPIO_PinSource9
#define FSMC_D15_PIN_SOURCE     GPIO_PinSource10
#define FSMC_D0_PIN_SOURCE      GPIO_PinSource14
#define FSMC_D1_PIN_SOURCE      GPIO_PinSource15

//FSMC D4,D5,D6,D7,D8,D9,D10,D11,D12
#define FSMC_PORT_2             GPIOE
#define FSMC_ALL_PIN_2          GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | \
                                GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15
#define FSMC_D4_PIN_SOURCE      GPIO_PinSource7
#define FSMC_D5_PIN_SOURCE      GPIO_PinSource8
#define FSMC_D6_PIN_SOURCE      GPIO_PinSource9
#define FSMC_D7_PIN_SOURCE      GPIO_PinSource10
#define FSMC_D8_PIN_SOURCE      GPIO_PinSource11
#define FSMC_D9_PIN_SOURCE      GPIO_PinSource12
#define FSMC_D10_PIN_SOURCE     GPIO_PinSource13
#define FSMC_D11_PIN_SOURCE     GPIO_PinSource14
#define FSMC_D12_PIN_SOURCE     GPIO_PinSource15

//FSMC A6
#define FSMC_PORT_3             GPIOF
#define FSMC_ALL_PIN_3          GPIO_Pin_12
#define FSMC_A6_PIN_SOURCE      GPIO_PinSource12

//FSMC NE4
#define FSMC_PORT_4             GPIOG
#define FSMC_ALL_PIN_4          GPIO_Pin_12
#define FSMC_NE4_PIN_SOURCE     GPIO_PinSource12

//LCD��λRESET�ı�ߵ͵�ƽ״̬
#define LCD_RESET_WR(X)         GPIO_WriteBit(LCD_RESET_PORT, LCD_RESET_PIN, (BitAction)X)
//LCD����BL�ı�ߵ͵�ƽ״̬
#define LCD_BL_WR(X)            GPIO_WriteBit(LCD_BL_PORT, LCD_BL_PIN, (BitAction)X)

typedef struct
{
    volatile uint16_t LCD_REG;
    volatile uint16_t LCD_DAT;
} LCD_TypeDef;

/********************����LCD��ַ********************/
#define LCD_BASE                (uint32_t)(0x6c000000 | ((1<<7) - 2))
#define LCD                     ((LCD_TypeDef *)LCD_BASE)

/********************����LCD��Ҫ����********************/
typedef struct
{
    uint16_t width;             //LCD����
    uint16_t height;            //LCD�߶�
    uint16_t id;                //LCD ID
    uint8_t dir;                //���������������ƣ�0��������1������
    uint16_t wramcmd;           //��ʼдgramָ��
    uint16_t setxcmd;           //����x����ָ��
    uint16_t setycmd;           //����y����ָ��
} _ILI9486_dev;

#ifdef __cplusplus
extern "C" {
#endif

extern _ILI9486_dev lcddev;

/********************�û�������********************/
#define USE_HORIZONTAL          1   // 0: landscape, 1: portrait
#define ILI9486_USE8BIT_MODEL   0   //�������������Ƿ�ʹ��8λģʽ  0,ʹ��16λģʽ��1,ʹ��8λģʽ

/********************����LCD�ĳߴ�********************/
#if USE_HORIZONTAL == 0
    #define LCD_W   480
    #define LCD_H   320
#else
    #define LCD_W   320
    #define LCD_H   480
#endif

/********************Ĭ����ɫ********************/
extern uint16_t POINT_COLOR;    //������ɫ��Ĭ�Ϻ�ɫ��
extern uint16_t BACK_COLOR;     //������ɫ��Ĭ�ϰ�ɫ��

/********************ɨ�跽����********************/
#define L2R_U2D     0           //������,���ϵ���
#define L2R_D2U     1           //������,���µ���
#define R2L_U2D     2           //���ҵ���,���ϵ���
#define R2L_D2U     3           //���ҵ���,���µ���

#define U2D_L2R     4           //���ϵ���,������
#define U2D_R2L     5           //���ϵ���,���ҵ���
#define D2U_L2R     6           //���µ���,������
#define D2U_R2L     7           //���µ���,���ҵ���

#define DFT_SCAN_DIR    U2D_L2R //Ĭ�ϵ�ɨ�跽��

/********************��ɫ�壬��ɫ��0~255�����Լ�����RGB********************/
#define MYRED       222
#define MYGREEN     33
#define MYBLUE      111
#define MYCOLOR     ((MYRED & 0xf8) << 8) | ((MYGREEN & 0xfc) << 3) | ((MYBLUE & 0xf8) >> 3)

/********************RGB 565��ɫ��ʽ********************/
#define WHITE       0xFFFF      //��ɫ
#define BLACK       0x0000      //��ɫ
#define BLUE        0x001F      //��ɫ
#define BRED        0XF81F      //����ɫ
#define GRED        0XFFE0      //����ɫ
#define GBLUE       0X07FF      //����ɫ
#define RED         0xF800      //��ɫ
#define MAGENTA     0xF81F      //Ʒ��ɫ
#define GREEN       0x07E0      //��ɫ
#define CYAN        0x7FFF      //��ɫ
#define YELLOW      0xFFE0      //��ɫ
#define BROWN       0XBC40      //��ɫ
#define BRRED       0XFC07      //�غ�ɫ
#define GRAY        0X8430      //��ɫ
#define DARKBLUE    0X01CF      //����ɫ
#define LIGHTBLUE   0X7D7C      //ǳ��ɫ
#define GRAYBLUE    0X5458      //����ɫ
#define LIGHTGREEN  0X841F      //ǳ��ɫ
#define LIGHTGRAY   0XC618      //ǳ��ɫ(PANNEL),���屳��ɫ
#define LGRAYBLUE   0XA651      //ǳ����ɫ(�м����ɫ)
#define LBBLUE      0X2B12      //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)
//�Զ�����ɫ

#define BgColor         0x0002  //�ı�������ɫ
#define BgColor1        0x2ab7  //�ı�������ɫ
#define BgColor2        0x645f  //�ı�������ɫ

#define BgColor3        0x114c  //�ı�������ɫ

#define CONTENT_COLOR   0x6CBE  //�ı�������ɫ
#define TITLE_COLOR     0x1A14  //���ⱳ����ɫ

//Һ������ʼ��������Ӳ����ʼ����������ʼ��
void ILI9486_Init(void);
//Һ����Ӳ����ʼ������������Һ������GPIO��
void ILI9486_Hardware_Init(void);
//Һ����������ʼ������Һ�������г�ʼ��������дָ�
void ILI9486_Software_Init(void);
//��Һ����д��8λָ���
void ILI9486_WR_REG(uint8_t reg);
//��Һ����д��16λ���ݺ���
void ILI9486_WR_DATA(uint16_t data);
//��Һ����д��һ��16λ��ɫ
void ILI9486_DrawPoint_16Bit(uint16_t color);
//��Һ����д��8λָ��,16λ���ݺ���
void ILI9486_WriteReg(uint8_t ILI9486_reg, uint16_t ILI9486_value);
//дGRAMָ���
void ILI9486_WriteRAM_Prepare(void);
//��ָ��λ��(һ�����ص�)д��"����"��ɫ
void ILI9486_DrawPoint(uint16_t x, uint16_t y);
//LCD������亯��
void ILI9486_Fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t c);
//LCDȫ�������������
void ILI9486_Clear(uint16_t color);
//������ʾ������ʼ����ͽ�������
void ILI9486_SetWindows(uint16_t xstar, uint16_t ystar, uint16_t xend, uint16_t yend);
//���ù��λ��
void ILI9486_SetCursor(uint16_t Xpos, uint16_t Ypos);
//����LCD����������ѡ�������������
void ILI9486_SetParam(void);

void ILI9486_DrawRoundedRect(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t innerColor, uint16_t radius);
void ILI9486_DrawPixel(uint16_t x, uint16_t y, uint16_t color); 

#ifdef __cplusplus
}
#endif

#endif
