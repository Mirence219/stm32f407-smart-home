#include "gui.h"
#include "pic.h"
#include "font.h"

/*
��  �ܣ� LCD��ʼ������
��  ���� ��
����ֵ�� ��
*/
void LCD_Init(void)
{
    ILI9486_Init();
}

/*
��  �ܣ� ����GUI���
��  ���� (x,y)      ���λ������
		 c          Ҫ������ɫ
����ֵ�� ��
*/
void GUI_Draw_Point(uint16_t x, uint16_t y, uint16_t c)
{
	ILI9486_SetCursor(x, y);            //���ù��λ��
	ILI9486_DrawPoint_16Bit(c);         //�Թ��������д����ɫ
}

/*
��  �ܣ� ����GUI����������ɫ
��  ���� (sx,sy)    ָ������ʼ������
		 (ex,ey)    ָ���������������
		 c          Ҫ������ɫ
����ֵ�� ��
*/
void GUI_Fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t c)
{
	ILI9486_Fill(sx, sy, ex, ey, c);    //LCD��亯��
}

/*
��  �ܣ� ����GUI����
��  ���� (x1,y1)    �������
		 (x2,y2)    �յ�����
		 c          Ҫ������ɫ
����ֵ�� ��
˵  ���� ����ʹ��Bresenham�����㷨
*/
void GUI_Draw_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t c)
{
	// ����ѭ���ͼ���ʹ�õı���
	uint16_t t = 0;
	int xerr = 0, yerr = 0, delta_x = 0, delta_y = 0, distance = 0;
	int incx = 0, incy = 0, uRow = 0, uCol = 0;

	delta_x = x2 - x1;                  //����X���곤��
	delta_y = y2 - y1;                  //����Y���곤��
	uRow = x1;                          //��ʼX��ĵ㸳ֵ
	uCol = y1;                          //��ʼY��ĵ㸳ֵ

	if (delta_x > 0)                    //X��Ļ��߷�������
		incx = 1;                       //����X�᷽�����Ϊ1
	else if (delta_x == 0)              //X��Ļ��߷����޳���
		incx = 0;                       //����X�᷽�����Ϊ0
	else                                //����X��Ļ��߷�������
	{
		incx = -1;                      //����X�᷽�����Ϊ-1
		delta_x = -delta_x;             //����ֵȡ����������ȵľ���ֵ
	}

	if (delta_y > 0)                    //Y��Ļ��߷�������
		incy = 1;                       //����Y�᷽�����Ϊ1
	else if (delta_y == 0)              //Y��Ļ��߷����޳���
		incy = 0;                       //����Y�᷽�����Ϊ0
	else                                //����Y��Ļ��߷�������
	{
		incy = -1;                      //����Y�᷽�����Ϊ-1
		delta_y = -delta_y;             //����ֵȡ����������ȵľ���ֵ
	}

	if (delta_x > delta_y)              //�ж�X����Y��Ĵ�С
		distance = delta_x;             //ѡȡX�᳤�ȣ�X��>Y�ᣩ
	else
		distance = delta_y;             //ѡȡY�᳤�ȣ�Y��>X�ᣩ

	for (t = 0; t <= distance + 1; t++) //�������
	{
		GUI_Draw_Point(uRow, uCol, c);   //ѭ��ʹ��ָ����ɫ����
		xerr += delta_x;                //�����ж���xerrֵ�Լ�x��ĳ���ֵ
		yerr += delta_y;                //�����ж���yerrֵ�Լ�y��ĳ���ֵ

		if (xerr > distance)            //�ж�xerrֵ�Ƿ�����ж�ֵ
		{
			xerr -= distance;           //��ȥ�ж�ֵ���õ������´μ������ֵ
			uRow += incx;               //�´�����x����ֵ�ı�
		}

		if (yerr > distance)            //�ж�yerrֵ�Ƿ�����ж�ֵ
		{
			yerr -= distance;           //��ȥ�ж�ֵ���õ������´μ������ֵ
			uCol += incy;               //�´�����y����ֵ�ı�
		}
	}
}

/*
��  �ܣ� ����GUI������(�����)
��  ���� (x1,y1)    �������
		 (x2,y2)    �յ�����
		 c          Ҫ������ɫ
����ֵ�� ��
*/
void GUI_Draw_Rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t c)
{
	GUI_Draw_Line(x1, y1, x2, y1, c);    //ʹ�û���GUI���ߺ������Ƶ�һ����
	GUI_Draw_Line(x1, y1, x1, y2, c);    //ʹ�û���GUI���ߺ������Ƶڶ�����
	GUI_Draw_Line(x1, y2, x2, y2, c);    //ʹ�û���GUI���ߺ������Ƶ�������
	GUI_Draw_Line(x2, y1, x2, y2, c);    //ʹ�û���GUI���ߺ������Ƶ������ߣ���ɻ���
}

/*
��  �ܣ� ����GUI������(���)
��  ���� (x1,y1)    �������
		 (x2,y2)    �յ�����
		 c          Ҫ������ɫ
����ֵ�� ��
*/
void GUI_Draw_Fill_Rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t c)
{
	//����GUI������(���)ʹ�û���GUI����������ɫ����ɫΪָ����ɫ
	GUI_Fill(x1, y1, x2, y2, c);
}

/*
��  �ܣ� 8�Գ��Ի�Բ�㷨(�ڲ�����)
��  ���� (xc,yc)    Բ��������
		 (x,y)      ��������Բ�ĵ�����
		 c          ������ɫ
����ֵ�� ��
*/
static void GUI_Draw_Circle_8(int xc, int yc, int x, int y, uint16_t c)
{
	/* ��Բ�η�Ϊ����İ˸�45�����Σ�ÿ�����λ�һ���� */
	GUI_Draw_Point(xc + x, yc + y, c);   //�����꣨xc + x�� yc + y������
	GUI_Draw_Point(xc - x, yc + y, c);   //�����꣨xc - x�� yc + y������
	GUI_Draw_Point(xc + x, yc - y, c);   //�����꣨xc + x�� yc - y������
	GUI_Draw_Point(xc - x, yc - y, c);   //�����꣨xc - x�� yc - y������
	GUI_Draw_Point(xc + y, yc + x, c);   //�����꣨xc + y�� yc + x������
	GUI_Draw_Point(xc - y, yc + x, c);   //�����꣨xc - y�� yc + x������
	GUI_Draw_Point(xc + y, yc - x, c);   //�����꣨xc + y�� yc - x������
	GUI_Draw_Point(xc - y, yc - x, c);   //�����꣨xc - y�� yc - x������
}

/*
��  �ܣ� ����GUI��Բ
��  ���� (xc,yc)    Բ��������
		 c          ������ɫ
		 r          Բ�뾶
		 fill       ����жϱ�־��1-��䣬0-�����

����ֵ�� ��
˵  ���� ����ʹ��Bresenham��Բ�㷨
*/
void GUI_Circle(int xc, int yc, uint16_t c, uint16_t r, int fill)
{
	int x = 0, y = r, yi = 0, d = 0;

	d = 1 - r;

	if (fill)                                       //���ʽ��Բ��ʵ��Բ��
	{
		while (x <= y)                              //ѭ���жϣ�ֱ����ɻ�Բ
		{
			for (yi = x; yi <= y; yi++)             //ֱ��ѭ����㣬ѭ��һ����ɻ��ư�����
			{
				GUI_Draw_Circle_8(xc, yc, x, yi, c);//8�Գ��Ի�Բ��һ�λ��˸���
			}

			if (d < 0)                              //ͨ���㷨�����б�ֵd
				d = d + 2 * x + 3;
			else
			{
				d = d + 2 * (x - y) + 5;
				y--;
			}

			x++;                                    //����������һλ
		}
	}
	else                                            //�����ʽ��Բ������Բ��
	{
		while (x <= y)                              //ѭ���жϣ�ֱ����ɻ�Բ
		{
			GUI_Draw_Circle_8(xc, yc, x, y, c);     //8�Գ��Ի�Բ��һ�λ��˸���

			if (d < 0)                              //ͨ���㷨�����б�ֵd
			{
				d = d + 4 * x + 6;
			}
			else
			{
				d = d + 4 * (x - y) + 10;
				y--;
			}

			x++;                                    //����������һλ
		}
	}
}

/*
��  �ܣ� ��ʾ����Ӣ���ַ�
��  ���� (x,y)      �ַ���ʾλ����ʼ����
		 fc         ǰ�û�����ɫ
		 bc         ������ɫ
		 num        ��ֵ��0-94��
		 size       �����С
		 mode       ģʽ: 0,���ģʽ; 1,����ģʽ
����ֵ�� ��
*/
void GUI_Show_English_Char(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t num, uint8_t size, uint8_t mode)
{
	uint16_t double_byte = 0;                   //����ֵΪ˫�ֽ�

	num = num - ' ';                            //�õ��ַ�ƫ�ƺ��ֵ

	//���õ����ַ���ʾ����,��ʼ����(x,y),���ڿ�Ϊsize/2,��Ϊsize
	ILI9486_SetWindows(x, y, x + size / 2 - 1, y + size - 1);

	//�ж������С�Ƿ�淶���粻�淶�����С�ı�Ϊ32
	if ((size != 12) && (size != 16) && (size != 24) && (size != 32))
	{
		size = 32;
	}

	for (uint8_t pos = 0; pos < size; pos++)     //���ϵ���ѭ������
	{
		//�ж������С
		switch (size)
		{
		case 12:
			//ʹ��1206����
			double_byte = asc2_1206[num][pos];
			break;
		case 16:
			//ʹ��1608����
			double_byte = asc2_1608[num][pos];
			break;
		case 24:
			//ʹ��2412����
			double_byte = (asc2_2412[num][pos * 2 + 1] << 8) + asc2_2412[num][pos * 2];
			break;
		case 32:
			//ʹ��3216����
			double_byte = (asc2_3216[num][pos * 2 + 1] << 8) + asc2_3216[num][pos * 2];
			break;
		default:
			break;
		}

		for (uint8_t t = 0; t < size / 2; t++)			//������ѭ������,����������λ
		{
			if (!mode)									//����ģʽ�������屳��ɫ
			{
				if (double_byte & 0x01)					//�ж����λ�Ƿ���Ч
				{
					ILI9486_DrawPoint_16Bit(fc);        //��Ч��Ϳ������ɫ
				}
				else                                    //��Ч
				{
					ILI9486_DrawPoint_16Bit(bc);        //Ϳ����ɫ
				}
			}
			else										//���ģʽ���������屳��ɫ
			{
				if (double_byte & 0x01)					//�ж��ֽڵ����λ�Ƿ���Ч
				{
					GUI_Draw_Point(x + t, y + pos, fc);	//λ��Ч��ѡ��Ӧ�����Ϳ������ɫ
				}
			}
			double_byte >>= 1;                          //�ֽ�����һλ�����´��ж�
		}
	}

	//�ָ�����Ϊȫ��
	ILI9486_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);
}

/*
��  �ܣ� ��ʾ���ֱ���ֵ����32λ�ı���������ǿ��ת����int32_t��������ֵ
��  ���� (x,y)      �������
		 fc         ǰ�û�����ɫ
		 bc         ������ɫ
		 num        ��ֵ��Χ(-2147483648~2147483647)
		 len        ��ʾ������λ��������ʾֵ�ĳ��ȴ���len������ʾ������λ��ʾ
		 size       �����С
		 mode       ģʽ: 0,���ģʽ; 1,����ģʽ
����ֵ�� ��
*/
void GUI_Show_Int_Num(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, int32_t num, uint8_t len, uint8_t size, uint8_t mode)
{
	char show_len[8] = { 0 }, show_num[12] = { 0 };
	uint8_t t = 0;

	//�ж������С�Ƿ�淶���粻�淶�����С�ı�Ϊ32
	if ((size != 12) && (size != 16) && (size != 24) && (size != 32))
	{
		size = 32;
	}

	//len����������ʾλ��, ��: ��� %6d
	sprintf(show_len, "%%%dd", len);
	//�����ִ�������, �������num2charת��
	sprintf(show_num, show_len, num);

	//ѭ���ж��Ƿ�Ϊ������
	while (*(show_num + t) != 0)
	{
		//��ʾ�ִ�������ֵ
		GUI_Show_English_Char(x + (size / 2) * t, y, fc, bc, show_num[t], size, mode);
		//ָ��ƫ�Ƶ�ֵַ����
		t++;
	}
}

/*
��  �ܣ� ��ʾ������������
��  ���� (x,y)      �������
		 fc         ǰ�û�����ɫ
		 bc         ������ɫ
		 s          �ַ�����ַ
		 size       �����С
		 mode       ģʽ: 0, ���ģʽ; 1,����ģʽ
����ֵ�� ��
*/
void GUI_Show_Chinese_Char(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, const char* s, uint8_t size, uint8_t mode)
{
	uint16_t HZnum = 0;
	uint8_t line_byte_num = 0;
	uint8_t* pointer_addr;
	uint32_t offset_addr;

	//�ж������С�Ƿ�淶���粻�淶�����С�ı�Ϊ32
	if ((size != 12) && (size != 16) && (size != 24) && (size != 32))
	{
		size = 32;
	}

	switch (size)
	{
	case 16:
		HZnum = sizeof(tfont16) / sizeof(typFNT_GB16);  //�Զ�ͳ�ƺ�����Ŀ
		line_byte_num = 2;                              //ÿ���ֽ���Ϊ2����ÿ���ֽ�8λ
		pointer_addr = (uint8_t*)tfont16;				//��������ȡģ��ַ
		offset_addr = sizeof(typFNT_GB16);              //ÿ�������ƫ������ַ
		break;
	case 24:
		HZnum = sizeof(tfont24) / sizeof(typFNT_GB24);  //�Զ�ͳ�ƺ�����Ŀ
		line_byte_num = 3;                              //ÿ���ֽ���Ϊ3����ÿ���ֽ�8λ
		pointer_addr = (uint8_t*)tfont24;				//��������ȡģ��ַ
		offset_addr = sizeof(typFNT_GB24);              //ÿ�������ƫ������ַ
		break;
	case 32:
		HZnum = sizeof(tfont32) / sizeof(typFNT_GB32);  //�Զ�ͳ�ƺ�����Ŀ
		line_byte_num = 4;                              //ÿ���ֽ���Ϊ4����ÿ���ֽ�8λ
		pointer_addr = (uint8_t*)tfont32;				//��������ȡģ��ַ
		offset_addr = sizeof(typFNT_GB32);              //ÿ�������ƫ������ַ
		break;
	default:
		break;
	}

	for (int k = 0; k < HZnum; k++)                             //ѭ��Ѱ��ƥ���Index[2]��Աֵ
	{
		//��Ӧ��Աֵƥ�䣬��size=16ʱ��Ϊ((tfont16[k].Index[0] == *(s)) && (tfont16[k].Index[1] == *(s + 1)))
		if ((*(pointer_addr + offset_addr * k + 0) == *(s)) && (*(pointer_addr + offset_addr * k + 1) == *(s + 1)))
		{
			ILI9486_SetWindows(x, y, x + size - 1, y + size - 1);//Ϊ�����������ô���

			for (int i0 = 0; i0 < size; i0++)                   //x����ѭ��ִ��дsize�У�����ʽ����
			{
				for (int i1 = 0; i1 < line_byte_num; i1++)      //ÿ��д�������ֽڣ�������
					for (int j = 0; j < 8; j++)                 //ÿ�ֽ�����˸����أ���λ��ǰ
					{
						if (!mode)                              //���ģʽ
						{
							//�ж��ֽ���Чλ,�����λ�����λ
							if ((*(pointer_addr + offset_addr * k + (i0 * line_byte_num + i1 + ENCODING_BYTE_NUM))) & (0x80 >> j))
							{
								ILI9486_DrawPoint_16Bit(fc);    //��ЧͿ������ɫ
							}
							else
							{
								ILI9486_DrawPoint_16Bit(bc);    //��Ч��Ϳ����ɫ
							}
						}
						else
						{
							//�ж��ֽ���Чλ,�����λ�����λ
							if ((*(pointer_addr + offset_addr * k + (i0 * line_byte_num + i1 + ENCODING_BYTE_NUM))) & (0x80 >> j))
							{
								//λ��Ч��ѡ��Ӧ�����Ϳ������ɫ
								GUI_Draw_Point(x + i1 * 8 + j, y + i0, fc);
							}
						}
					}
			}

			//���ҵ���Ӧ����ؼ�����ɻ��ֺ�����break�˳�forѭ������ֹ��������ظ�ȡģ��ʾ
			break;
		}
	}

	//�ָ�����Ϊȫ��
	ILI9486_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);
}

/*
��  �ܣ� ��ʾһ���ַ���,������Ӣ����ʾ
��  ���� (x,y)      �������1
		 fc         ǰ�û�����ɫ
		 bc         ������ɫ
		 str        �ַ���
		 size       �����С
		 mode       ģʽ: 0,���ģʽ; 1,����ģʽ
����ֵ�� ��
*/
void GUI_Show_Str(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, const char* str, uint8_t size, uint8_t mode)
{

	uint8_t bHz = 0;						//�ַ��������ģ�Ĭ�����ַ�

	//�ж������С�Ƿ�淶���粻�淶�����С�ı�Ϊ32
	if ((size != 12) && (size != 16) && (size != 24) && (size != 32))
	{
		size = 32;
	}

	while (*str != 0)                       //�ж�Ϊ��Ϊ������
	{
		if ((uint8_t)*str > 0x80) bHz = 1;	//����ʾ���ַ���飬�ж��Ƿ�Ϊ����

		if (!bHz)							//�ж����ַ�
		{
			//�����ʾ�ַ�����Ԥ��lcd����С���˳�����������Ļ���ֵ��ַ�����ʾ
			if (x > (lcddev.width - size / 2) || y > (lcddev.height - size))
			{
				x = 0;                      //��ʾ��ǰ
				y += size;                  //��ʾ����
			}

			if (*str == 0x0D)               //�ж��ǻ��з���
			{
				y += size;                  //��һ����ʾ�����껻��
			}
			else                            //�жϲ��ǻ��з�
			{
				//��ʾ��Ӧ�ߴ��ַ�
				GUI_Show_English_Char(x, y, fc, bc, *str, size, mode);
				x += size / 2;              //��ʾ���������ʼ��ʾ������׼���´���ʾ
			}

			str++;                          //��ʾ��ַ������׼����һ���ַ�
		}
		else                                //�ж�������
		{
			//�����ʾ�����ĳ���Ԥ��lcd����С������ʾ
			if (x > (lcddev.width - size) || y > (lcddev.height - size))
			{
				x = 0;
				y += size;
			}

			GUI_Show_Chinese_Char(x, y, fc, bc, str, size, mode);
			str += ENCODING_BYTE_NUM;       //��ʾ��ַ������׼����һ������
			x += size;                      //��ʾ���������ʼ��ʾ������׼���´���ʾ
			bHz = 0;                        //��ΪĬ���ַ������´��ַ��ж�
		}
	}
}

/*
��  �ܣ� ������ʾһ���ַ���,������Ӣ����ʾ
��  ���� (x,y)      �������
		 fc         ǰ�û�����ɫ
		 bc         ������ɫ
		 str        �ַ���
		 size       �����С
		 mode       ģʽ: 0,���ģʽ; 1,����ģʽ
����ֵ�� ��
*/
void GUI_Str_Center(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, const char* str, uint8_t size, uint8_t mode)
{
	//����ַ����ܳ��ȣ������ַ�ռһ���ֽڣ�����ռ�����ֽ�
	uint16_t len = strlen((const char*)str);
	//ͨ���ܳ��Ȼ����ʾ��ʼ������
	uint16_t x1 = (lcddev.width - len * size / 2) / 2;
	//������ʾһ���ַ�����������Ӣ����ʾ��
	GUI_Show_Str(x + x1, y, fc, bc, str, size, mode);
}

/*
��  �ܣ� ��ʾһ��16λBMPͼ��
��  ���� (x0,y0)    �������
		 (x1,y1)    �յ�����
		 *p         ͼ��������ʼ��ַ
����ֵ�� ��
*/
void GUI_Drawbmp16(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, const uint8_t* p)
{
	uint32_t i = 0;
	uint16_t picH = 0, picL = 0;

	ILI9486_SetWindows(x0, y0, x0 + x1 - 1, y0 + y1 - 1);

	for (i = 0; i < x1 * y1; i++)
	{
		picL = *(p + i * 2);				                        //���ݵ�λ��ǰ
		picH = *(p + i * 2 + 1);			                        //���ݸ�λ�ں�
		ILI9486_DrawPoint_16Bit(picH << 8 | picL);                  //�ߵ�λ�ϲ�ѭ���������ң��ٴ��ϵ��»���
	}

	ILI9486_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);  //�ָ���ʾ����Ϊȫ��	
}

/******************************************TEST AREA*******************************************/
uint16_t ColorTab[5] = { BRED, YELLOW, RED, GREEN, BLUE };			//������ɫ����

/*
��  �ܣ� �����ۺϲ��Գ��������棨�׵ף�
��  ���� ��
����ֵ�� ��
*/
void GUI_Main_Test(void)
{
	//����
	ILI9486_Clear(BgColor);
    
    ILI9486_DrawRoundedRect(5,4,315,45,BgColor1,2);
	
    //��������
    
	GUI_Drawbmp16(15,4, 124, 40, gImage_logo);
    
    ILI9486_DrawRoundedRect(9,50,311,265,BgColor2,4);
    
    ILI9486_DrawRoundedRect(9+4,50+4,311-4,265-4,BgColor,4);
    
    ILI9486_DrawRoundedRect(9+4+5,50+4+5,311-4-5,265-4-4,TITLE_COLOR,4);
    
    ILI9486_DrawRoundedRect(9,272,310,462,BgColor3,5);
    
    ILI9486_DrawRoundedRect(9+10,272+20,310-9,462-9,CONTENT_COLOR,5);
    
    GUI_Str_Center(0, 480-16, WHITE, BgColor, "www.r8c.com", 16, 1);
}

/*
��  �ܣ� ���Ʋ��Խ���
��  ���� str       �ַ���ָ��
		 color     ���Խ����ʼ��ɫ
����ֵ�� ��
*/
void GUI_Draw_Test_Page(char* str, uint16_t color)
{
	//�����Ϸ��̶���
	GUI_Fill(0, 0, lcddev.width, 20, BLUE);
	//�����·��̶���down
	GUI_Fill(0, lcddev.height - 20, lcddev.width, lcddev.height, BLUE);
	//���û�����ɫΪ��ɫ
	POINT_COLOR = WHITE;
	//������ʾ�ִ���
	GUI_Str_Center(0, 2, WHITE, BLUE, str, 16, 1);
	//�·��̶���������ʾ���ٿ��ٴ� www.R8C.com��
	GUI_Str_Center(0, lcddev.height - 18, WHITE, BLUE, "www.R8C.com", 16, 1);
	//���Ʋ�������color��
	GUI_Fill(0, 20, lcddev.width, lcddev.height - 20, color);
}

/*
��  �ܣ� �����ۺϲ��Գ��������棨�ڵף�
��  ���� ��
����ֵ�� ��
*/
void GUI_Test(void)
{
	//��ʾgui���棨��ɫ���棬��ʵ�ḻ��
	GUI_Draw_Test_Page("TFT���Գ���", BLACK);
	GUI_Str_Center(0, 60, WHITE, WHITE, "�ٿ��ٴ�", 16, 1);
	GUI_Str_Center(0, 90, RED, WHITE, "�ۺϲ��Գ���", 16, 1);
	GUI_Str_Center(0, 120, YELLOW, WHITE, "3.5' ILI9486 320X480", 16, 1);
	GUI_Str_Center(0, 150, BLUE, WHITE, "www.R8C.com 2018-12-20", 16, 1);
	Delay_ms(500);
	Delay_ms(500);
}

/*
��  �ܣ� ��ɫ�����ԣ���������ɫ����ɫ����ɫ����ɫ����ɫ
��  ���� ��
����ֵ�� ��
*/
void GUI_Color_Test(void)
{
	//����gui����
	GUI_Draw_Test_Page("����1:��ɫ������", WHITE);

	//���Ʋ������򣨰�ɫ��������ʾ��Ӧ��ɫӢ��
	GUI_Fill(0, 20, lcddev.width, lcddev.height - 20, WHITE);
	GUI_Show_Str(lcddev.width - 50, 30, BLUE, YELLOW, "White", 16, 1);
	Delay_ms(500);
	//���Ʋ������򣨺�ɫ��������ʾ��Ӧ��ɫӢ��
	GUI_Fill(0, 20, lcddev.width, lcddev.height - 20, BLACK);
	GUI_Show_Str(lcddev.width - 50, 30, BLUE, YELLOW, "Black", 16, 1);
	Delay_ms(500);
	//���Ʋ������򣨺�ɫ��������ʾ��Ӧ��ɫӢ��
	GUI_Fill(0, 20, lcddev.width, lcddev.height - 20, RED);
	GUI_Show_Str(lcddev.width - 50, 30, BLUE, YELLOW, "Red", 16, 1);
	Delay_ms(500);
	//���Ʋ���������ɫ��������ʾ��Ӧ��ɫӢ��
	GUI_Fill(0, 20, lcddev.width, lcddev.height - 20, GREEN);
	GUI_Show_Str(lcddev.width - 50, 30, BLUE, YELLOW, "Green", 16, 1);
	Delay_ms(500);
	//���Ʋ������򣨻�ɫ��������ʾ��Ӧ��ɫӢ��
	GUI_Fill(0, 20, lcddev.width, lcddev.height - 20, YELLOW);
	GUI_Show_Str(lcddev.width - 58, 30, BLUE, YELLOW, "Yellow", 16, 1);
	Delay_ms(500);
	Delay_ms(500);
}

/*
��  �ܣ� ���ο���ʾ�������ԣ�������ʾ�ۺ�ɫ����ɫ����ɫ����ɫ����ɫ���ο�
		 ��ʱ500��������ΰ��շۺ�ɫ����ɫ����ɫ����ɫ����ɫ�����ο�
��  ���� ��
����ֵ�� ��
*/
void GUI_Fill_Rec_Test(void)
{
	uint8_t i = 0;
	GUI_Draw_Test_Page("����2:GUI����������", WHITE);

	//ѭ��ִ����Σ�������崦�������ͬ��ɫ��������
	for (i = 0; i < 5; i++)
	{
		//���Ʒ�������
		GUI_Draw_Rectangle(lcddev.width / 2 - 100 + (i * 40), lcddev.height / 2 - 100 + (i * 40), lcddev.width / 2 - 100 + (i * 40) + 60, lcddev.height / 2 - 100 + (i * 40) + 60, ColorTab[i]);
		Delay_ms(100);
	}
	//��ʱ������ʾ
	Delay_ms(500);
	//ѭ��ִ����Σ�������崦�������ͬ��ɫ������
	for (i = 0; i < 5; i++)
	{
		//����������
		GUI_Draw_Fill_Rectangle(lcddev.width / 2 - 100 + (i * 40), lcddev.height / 2 - 100 + (i * 40), lcddev.width / 2 - 100 + (i * 40) + 60, lcddev.height / 2 - 100 + (i * 40) + 60, ColorTab[i]);
		Delay_ms(100);
	}
	//��ʱ������ʾ
	Delay_ms(500);
}

/*
��  �ܣ� Բ�ο���ʾ�������ԣ�������ʾ�ۺ�ɫ����ɫ����ɫ����ɫ����ɫԲ�ο�
		��ʱ500��������ΰ��շۺ�ɫ����ɫ����ɫ����ɫ����ɫ���Բ�ο�
��  ���� ��
����ֵ�� ��
*/
void GUI_Circle_Test(void)
{
	uint8_t i = 0;
	GUI_Draw_Test_Page("����3:GUI��Բ������", WHITE);

	//ѭ��ִ����Σ�������崦�������ͬ��ɫ�����Բ��
	for (i = 0; i < 5; i++)
	{
		GUI_Circle(lcddev.width / 2 - 80 + (i * 40), lcddev.height / 2 + 100 - (i * 60), ColorTab[i], 50, 0);
		Delay_ms(100);
	}
	//��ʱ������ʾ
	Delay_ms(500);
	//ѭ��ִ����Σ�������崦�������ͬ��ɫ���Բ��
	for (i = 0; i < 5; i++)
	{
		GUI_Circle(lcddev.width / 2 - 80 + (i * 40), lcddev.height / 2 + 100 - (i * 60), ColorTab[i], 50, 1);
		Delay_ms(100);
	}

	Delay_ms(500);
}

/*
��  �ܣ� �ַ���ʾ����
��  ���� ��
����ֵ�� ��
*/
void GUI_English_Font_Test(void)
{
	GUI_Draw_Test_Page("����4:�ַ���ʾ����", BLACK);
	//��ʾ6*12��8*16��12*24��16*32��С���ִ���
	GUI_Show_Str(10, 30, RED, BLUE, "6X12:abcdefghijklmnopqrstuvwxyz", 12, 0);
	GUI_Show_Str(10, 50, RED, BLUE, "6X12:ABCDEFGHIJKLMNOPQRSTUVWXYZ", 12, 1);
	GUI_Show_Str(10, 70, RED, BLUE, "6X12:0123456789~!@#$%^&*()_+{}:<>?/|-+.", 12, 0);
	GUI_Show_Str(10, 90, RED, BLUE, "8X16:abcdefghijklmnopqrstuvwxyz", 16, 1);
	GUI_Show_Str(10, 110, RED, BLUE, "8X16:ABCDEFGHIJKLMNOPQRSTUVWXYZ", 16, 0);
	GUI_Show_Str(10, 130, RED, BLUE, "8X16:0123456789~!@#$%^&*()_+{}:<>?/|-+.", 16, 1);
	GUI_Show_Str(10, 150, RED, BLUE, "12X24:abcdefghijklmnopqrs", 24, 1);
	GUI_Show_Str(10, 180, RED, BLUE, "12X24:tuvwxyzABCDEFGHIJKL", 24, 0);
	GUI_Show_Str(10, 210, RED, BLUE, "12X24:MNOPQRSTUVWXYZ01234", 24, 1);
	GUI_Show_Str(10, 240, RED, BLUE, "12X24:56789~!@#$%^&*()_+{", 24, 0);
	GUI_Show_Str(10, 270, RED, BLUE, "12X24:}:<>?/|-+.", 24, 1);
	GUI_Show_Str(10, 300, RED, BLUE, "16X32:WWW.R8C.COM", 32, 0);
	Delay_ms(500);
	Delay_ms(500);
}

/*
��  �ܣ� ������ʾ����
��  ���� ��
����ֵ�� ��
*/
void GUI_Chinese_Font_Test(void)
{
	GUI_Draw_Test_Page("����5:������ʾ����", BLACK);
	//��ʾ16X16��24X24,32X32��С�������ַ�
	GUI_Show_Str(10, 50, WHITE, YELLOW, "16X16:�ٿ��ٴ����������Ƽ���չ���޹�˾", 16, 1);
	GUI_Show_Str(10, 80, WHITE, YELLOW, "24X24:���Ĳ���", 24, 1);
	GUI_Show_Str(10, 120, WHITE, YELLOW, "32X32:�������", 32, 1);
	Delay_ms(500);
	Delay_ms(500);
}

/*
��  �ܣ� ͼƬ��ʾ���ԣ�������ʾ���40X40 QQͼ��
��  ���� ��
����ֵ�� ��
*/
void GUI_Pic_Test(void)
{
	uint8_t i = 0;
	GUI_Draw_Test_Page("����6:ͼƬ��ʾ����", WHITE);
	//ѭ��ִ�����Σ���ɻ�ͼ
	for (i = 0; i <= 3; i++)
	{
		//��ͼ
		GUI_Drawbmp16(20 + 40 * i, 40 + 80 * i, 40, 40, gImage_smile);
		//��ʾͼƬ����
		GUI_Show_Str(20 + 40 * i, 80 + 80 * i, BLUE, YELLOW, "SMILE", 16, 1);
	}
	for (i = 1; i <= 3; i++)
	{
		//��ͼ(�Ŵ���С)
		Gui_Drawbmp_Zoom(60 + i * i * 17, i * 40, gImage_smile, 40, 40, 25 * i, 25 * i);
	}
	//��ʱһ����ʾ
	Delay_ms(500);
	Delay_ms(500);
}

/*
��  �ܣ� ��ʾһ���Զ������ش�С��16λBMPͼ��
��  ���� (sx,sy)    ��ʾͼ����������
		 *p         ͼ��������ʼ��ַ
		 (sw,sh)    ԭͼ��Ŀ��͸�
		 (ew,wh)    ��Ҫ��ʾͼƬ�Ŀ��͸�
����ֵ�� ��
*/
#define BMP16_RES(X,Y,Z) ((uint16_t)((*(p+(Y)*sw*2+(X)*2+1)>>3)*(Z))<<11)+((uint16_t)((((*(p+(Y)*sw*2+(X)*2+1)&0x7)<<3)+(*(p+(Y)*sw*2+(X)*2)>>5))*(Z))<<5)+(uint16_t)((*(p+(Y)*sw*2+(X)*2)&0x1f)*(Z))
void Gui_Drawbmp_Zoom(int16_t sx, int16_t sy, const unsigned char* p, uint16_t sw, uint16_t sh, uint16_t ew, uint16_t eh)
{
	uint16_t i = 0, j = 0, k = 0, l = 0, new_color;
	float ratiow, ratiow2, ratioh, ratioh2, kw, kh;

	//ͼ����ʼ��ַ����ȷ�˳�
	if (sx<0 || sx>lcddev.width || sy<0 || sy>lcddev.height) return;
	//ͼ�񳬳�����Ļ����ʾ
	if (((sx + ew) > lcddev.width) || ((sy + eh) > lcddev.height)) return;

	ILI9486_SetWindows(sx, sy, sx + ew - 1, sy + eh - 1);   //����������ʼΪx,y

	while (1)                                               //ѭ����ֵ
	{
		kh = (float)l / eh * (sh - 1);                      //����߶���ֵ

		if (kh > k)                                         //�ж��߶���ֵ��ʹk�����kh��Ϊ����
		{
			k++;
		}
		else
		{
			if (kh >= (sh - 1)) break;                      //�жϳ����߶������������ͼ

			//���������������صĸ߶ȱ�ֵ
			ratioh = k - kh;
			ratioh2 = 1 - ratioh;

			i = 0, j = 0;                                   //���û���һ��ʹ�õı���Ϊ0
			while (1)
			{
				kw = (float)j / ew * (sw - 1);              //���������ֵ

				if (kw > i)                                 //�ж�������ֵ��ʹi�����kw��Ϊ����
				{
					i++;
				}
				else
				{
					if (kw >= (sw - 1)) break;              //�жϳ������������һ�л�ͼ

					//���������������صĿ��ȱ�ֵ
					ratiow = i - kw;
					ratiow2 = 1 - ratiow;

					if ((i != 0) && (k != 0))
					{
						//�ǵ�һ��Ҳ�ǵ�һ�е�RGB���㣬���ٽ����ĸ�����ֵ����������ڻ��
						new_color = BMP16_RES(i - 1, k - 1, ratiow * ratioh) + BMP16_RES(i, k - 1, ratiow2 * ratioh) + \
							BMP16_RES(i - 1, k, ratiow * ratioh2) + BMP16_RES(i, k, ratiow2 * ratioh2);
					}
					else if ((i == 0) && (k != 0))
					{
						//��һ�е�RGBֵ���㣨���˵�һ�����أ��������ҵ���������ֵ����������ڻ��
						new_color = BMP16_RES(0, k - 1, ratioh) + BMP16_RES(0, k, ratioh2);
					}
					else if ((i != 0) && (k == 0))
					{
						//��һ�е�RGBֵ���㣨���˵�һ�����أ��������µ���������ֵ����������ڻ��
						new_color = BMP16_RES(i - 1, 0, ratiow) + BMP16_RES(i, 0, ratiow2);
					}
					else
					{
						//��һ����������ɫĬ��Ϊ��һ��ԭ������ɫ
						new_color = BMP16_RES(0, 0, 1);
					}

					ILI9486_DrawPoint_16Bit(new_color);     //ѡ������ɫ��������ɫ��������ɫ��
					j++;                                    //���ȵļ���ֵ�Լ�
				}
			}

			l++;                                            //�߶ȵļ���ֵ�Լ�
		}
	}

	//�ָ���ʾ����Ϊȫ��
	ILI9486_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);
}
