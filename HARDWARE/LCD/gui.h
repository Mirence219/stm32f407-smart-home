#ifndef __GUI_H_
#define __GUI_H_

#include "stm32f4xx.h"
#include "ili9486.h"
#include "string.h"
#include "stdio.h"
#include "delay.h"

#ifdef __cplusplus
extern "C" {
#endif

// ��������ʽΪgb2312��ֵΪ2�������ʽΪutf-8����Ϊ3
#define ENCODING_BYTE_NUM           2

//LCD��ʼ������
void LCD_Init(void);

/**************ͼ�λ���**************/
//����GUI��㺯��
void GUI_Draw_Point(uint16_t x, uint16_t y, uint16_t c);
//����GUI����������ɫ����
void GUI_Fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t c);
//����GUI���ߺ���
void GUI_Draw_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t c);
//����GUI������(�����)����
void GUI_Draw_Rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t c);
//����GUI������(���)����
void GUI_Draw_Fill_Rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t c);
//����GUI��Բ����
void GUI_Circle(int xc, int yc, uint16_t c, uint16_t r, int fill);

/**************��ʾ�ַ�**************/
//��ʾ����Ӣ���ַ�����
void GUI_Show_English_Char(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t num, uint8_t size, uint8_t mode);
//��ʾ���ֱ���ֵ����
void GUI_Show_Int_Num(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, int32_t num, uint8_t len, uint8_t size, uint8_t mode);
//��ʾ�����������庯��
void GUI_Show_Chinese_Char(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, const char *s, uint8_t size, uint8_t mode);
//��ʾһ���ַ���������������Ӣ����ʾ��
void GUI_Show_Str(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, const char *str, uint8_t size, uint8_t mode);
//������ʾһ���ַ���������������Ӣ����ʾ��
void GUI_Str_Center(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, const char *str, uint8_t size, uint8_t mode);
//��ʾBMPͼ����
void GUI_Drawbmp16(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,const uint8_t *p);

//�����ۺϲ��Գ��������棨�׵ף�����
void GUI_Main_Test(void);

/**************���Ժ���**************/
//���Ʋ��Խ��溯��
void GUI_Draw_Test_Page(char *str, uint16_t color);
//�����ۺϲ��Գ��������棨�ڵף�����
void GUI_Test(void);
//��ɫ�����Ժ���
void GUI_Color_Test(void);
//���ο���ʾ�������Ժ���
void GUI_Fill_Rec_Test(void);
//Բ�ο���ʾ�������Ժ���
void GUI_Circle_Test(void);
//�ַ���ʾ���Ժ���
void GUI_English_Font_Test(void);
//������ʾ���Ժ���
void GUI_Chinese_Font_Test(void);
//ͼƬ��ʾ���Ժ���
void GUI_Pic_Test(void);
//��ʾһ���Զ������ش�С��16λBMPͼ��
void Gui_Drawbmp_Zoom(int16_t sx, int16_t sy, const unsigned char* p, uint16_t sw, uint16_t sh, uint16_t ew, uint16_t eh);

#ifdef __cplusplus
}
#endif

#endif
