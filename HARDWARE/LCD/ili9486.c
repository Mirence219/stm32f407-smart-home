#include "ili9486.h"

//新建lcddev结构体，默认为竖屏
_ILI9486_dev lcddev;

//画笔颜色（默认黑色）,背景颜色（默认白色）
uint16_t POINT_COLOR = 0x0000, BACK_COLOR = 0xFFFF;

/*
功  能： 液晶屏初始化，包含硬件初始化和软件初始化
参  数： 无
返回值： 无
*/
void ILI9486_Init(void)
{
    //液晶屏硬件初始化
    ILI9486_Hardware_Init();

    // 液晶屏软件初始化
    ILI9486_Software_Init();
}

/*
功  能： 液晶屏硬件初始化，设置连接液晶屏的GPIO口
参  数： 无
返回值： 无
*/
void ILI9486_Hardware_Init(void)
{
    //定义GPIO、FSMC相关结构体
    GPIO_InitTypeDef GPIO_InitStructure;
    FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef FSMC_NORSRAMTimingInitReadWriteStructure;
    FSMC_NORSRAMTimingInitTypeDef FSMC_NORSRAMTimingInitWriteStructure;

    //开启控制线和数据线的时钟
    LCD_GPIO_CLOCK_INIT(LCD_ALL_GPIO_CLOCK, ENABLE);
    LCD_FMSC_CLOCK_INIT(LCD_FMSC_CLOCK, ENABLE);

    /*LCD_BL*/
    //选择端口
    GPIO_InitStructure.GPIO_Pin = LCD_BL_PIN;
    //输出模式
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    //推挽输出
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    //输出速度
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    //初始化配置
    GPIO_Init(LCD_BL_PORT, &GPIO_InitStructure);

    /*LCD_REST*/
    //选择端口
    GPIO_InitStructure.GPIO_Pin = LCD_RESET_PIN;
    //初始化配置
    GPIO_Init(LCD_RESET_PORT, &GPIO_InitStructure);

    /*FSMC D2,D3,NOE,NWE,D13,D14,D15,D0,D1*/
    //选择端口
    GPIO_InitStructure.GPIO_Pin = FSMC_ALL_PIN_1;
    //复用模式
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    //推挽输出
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    //输出速度
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    //初始化配置
    GPIO_Init(FSMC_PORT_1, &GPIO_InitStructure);

    /*FSMC D4,D5,D6,D7,D8,D9,D10,D11,D12*/
    //选择端口
    GPIO_InitStructure.GPIO_Pin = FSMC_ALL_PIN_2;
    //初始化配置
    GPIO_Init(FSMC_PORT_2, &GPIO_InitStructure);

    /*FSMC A6*/
    //选择端口
    GPIO_InitStructure.GPIO_Pin = FSMC_ALL_PIN_3;
    //初始化配置
    GPIO_Init(FSMC_PORT_3, &GPIO_InitStructure);

    /*FSMC NE4*/
    //选择端口
    GPIO_InitStructure.GPIO_Pin = FSMC_ALL_PIN_4;
    //初始化配置
    GPIO_Init(FSMC_PORT_4, &GPIO_InitStructure);

    GPIO_PinAFConfig(FSMC_PORT_1, FSMC_D2_PIN_SOURCE, GPIO_AF_FSMC);
    GPIO_PinAFConfig(FSMC_PORT_1, FSMC_D3_PIN_SOURCE, GPIO_AF_FSMC);
    GPIO_PinAFConfig(FSMC_PORT_1, FSMC_NOE_PIN_SOURCE, GPIO_AF_FSMC);
    GPIO_PinAFConfig(FSMC_PORT_1, FSMC_NWE_PIN_SOURCE, GPIO_AF_FSMC);
    GPIO_PinAFConfig(FSMC_PORT_1, FSMC_D13_PIN_SOURCE, GPIO_AF_FSMC);
    GPIO_PinAFConfig(FSMC_PORT_1, FSMC_D14_PIN_SOURCE, GPIO_AF_FSMC);
    GPIO_PinAFConfig(FSMC_PORT_1, FSMC_D15_PIN_SOURCE, GPIO_AF_FSMC);
    GPIO_PinAFConfig(FSMC_PORT_1, FSMC_D0_PIN_SOURCE, GPIO_AF_FSMC);
    GPIO_PinAFConfig(FSMC_PORT_1, FSMC_D1_PIN_SOURCE, GPIO_AF_FSMC);
    GPIO_PinAFConfig(FSMC_PORT_2, FSMC_D4_PIN_SOURCE, GPIO_AF_FSMC);
    GPIO_PinAFConfig(FSMC_PORT_2, FSMC_D5_PIN_SOURCE, GPIO_AF_FSMC);
    GPIO_PinAFConfig(FSMC_PORT_2, FSMC_D6_PIN_SOURCE, GPIO_AF_FSMC);
    GPIO_PinAFConfig(FSMC_PORT_2, FSMC_D7_PIN_SOURCE, GPIO_AF_FSMC);
    GPIO_PinAFConfig(FSMC_PORT_2, FSMC_D8_PIN_SOURCE, GPIO_AF_FSMC);
    GPIO_PinAFConfig(FSMC_PORT_2, FSMC_D9_PIN_SOURCE, GPIO_AF_FSMC);
    GPIO_PinAFConfig(FSMC_PORT_2, FSMC_D10_PIN_SOURCE, GPIO_AF_FSMC);
    GPIO_PinAFConfig(FSMC_PORT_2, FSMC_D11_PIN_SOURCE, GPIO_AF_FSMC);
    GPIO_PinAFConfig(FSMC_PORT_2, FSMC_D12_PIN_SOURCE, GPIO_AF_FSMC);
    GPIO_PinAFConfig(FSMC_PORT_3, FSMC_A6_PIN_SOURCE, GPIO_AF_FSMC);
    GPIO_PinAFConfig(FSMC_PORT_4, FSMC_NE4_PIN_SOURCE, GPIO_AF_FSMC);

    FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable;
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
    FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &FSMC_NORSRAMTimingInitReadWriteStructure;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &FSMC_NORSRAMTimingInitWriteStructure;

    FSMC_NORSRAMTimingInitWriteStructure.FSMC_AddressSetupTime = 9;             //地址建立时间（ADDSET）为9个HCLK =54ns
    FSMC_NORSRAMTimingInitWriteStructure.FSMC_AddressHoldTime = 0x00;           //地址保持时间
    FSMC_NORSRAMTimingInitWriteStructure.FSMC_DataSetupTime = 8;                //数据保存时间为6ns*9个HCLK=54ns
    FSMC_NORSRAMTimingInitWriteStructure.FSMC_BusTurnAroundDuration = 0x00;
    FSMC_NORSRAMTimingInitWriteStructure.FSMC_CLKDivision = 0x00;
    FSMC_NORSRAMTimingInitWriteStructure.FSMC_DataLatency = 0x00;
    FSMC_NORSRAMTimingInitWriteStructure.FSMC_AccessMode = FSMC_AccessMode_A;   //模式A

    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);

    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);

    LCD_RESET_WR(0);
    Delay_ms(100);
    
    LCD_RESET_WR(1);
    Delay_ms(100);
}

/*
功  能： 液晶屏软件初始化，对液晶屏进行初始化操作（写指令）
参  数： 无
返回值： 无
*/
void ILI9486_Software_Init(void)
{
    /*************开始程序初始化*************/
    /* DSI write DCS command, use loose packet RGB 666 */
    ILI9486_WR_REG(0XF7);
    ILI9486_WR_DATA(0xA9);
    ILI9486_WR_DATA(0x51);
    ILI9486_WR_DATA(0x2C);
    ILI9486_WR_DATA(0x82);

    /* Power Control 1 (C0h) */
    ILI9486_WR_REG(0xC0);
    ILI9486_WR_DATA(0x11);
    ILI9486_WR_DATA(0x09);

    /* Power Control 2 (C1h) */
    ILI9486_WR_REG(0xC1);
    ILI9486_WR_DATA(0x41);

    /* VCOM Control (C5h) */
    ILI9486_WR_REG(0XC5);
    ILI9486_WR_DATA(0x00);
    ILI9486_WR_DATA(0x0A);
    ILI9486_WR_DATA(0x80);

    /* Frame Rate Control (In Normal Mode/Full Colors) (B1h) */
    ILI9486_WR_REG(0xB1);
    ILI9486_WR_DATA(0xA0);
    ILI9486_WR_DATA(0x11);

    /* Display Inversion Control (B4h) */
    ILI9486_WR_REG(0xB4);
    ILI9486_WR_DATA(0x02);

    /* Display Function Control (B6h) */
    ILI9486_WR_REG(0xB6);
    ILI9486_WR_DATA(0x00);
    ILI9486_WR_DATA(0x42);  //0 GS SS SM ISC[3:0];
    ILI9486_WR_DATA(0x3B);
    /* Entry Mode Set (B7h) */
    ILI9486_WR_REG(0xB7);
    ILI9486_WR_DATA(0xc6);

    /* HS Lanes Control (BEh) */
    ILI9486_WR_REG(0xBE);
    ILI9486_WR_DATA(0x00);
    ILI9486_WR_DATA(0x04);

    /* Set Image Function (E9h) */
    ILI9486_WR_REG(0xE9);
    ILI9486_WR_DATA(0x00);

    ILI9486_WR_REG(0x36);
    ILI9486_WR_DATA(0x08);

    /* Interface Pixel Format (3Ah) */
    ILI9486_WR_REG(0x3A);
    ILI9486_WR_DATA(0x55);  //0x55: 16 bits/pixel

    /* PGAMCTRL (Positive Gamma Control) (E0h) */
    ILI9486_WR_REG(0xE0);
    ILI9486_WR_DATA(0x00);
    ILI9486_WR_DATA(0x07);
    ILI9486_WR_DATA(0x10);
    ILI9486_WR_DATA(0x09);
    ILI9486_WR_DATA(0x17);
    ILI9486_WR_DATA(0x0B);
    ILI9486_WR_DATA(0x41);
    ILI9486_WR_DATA(0x89);
    ILI9486_WR_DATA(0x4B);
    ILI9486_WR_DATA(0x0A);
    ILI9486_WR_DATA(0x0C);
    ILI9486_WR_DATA(0x0E);
    ILI9486_WR_DATA(0x18);
    ILI9486_WR_DATA(0x1B);
    ILI9486_WR_DATA(0x0F);

    /* NGAMCTRL (Negative Gamma Control) (E1h) */
    ILI9486_WR_REG(0XE1);
    ILI9486_WR_DATA(0x00);
    ILI9486_WR_DATA(0x17);
    ILI9486_WR_DATA(0x1A);
    ILI9486_WR_DATA(0x04);
    ILI9486_WR_DATA(0x0E);
    ILI9486_WR_DATA(0x06);
    ILI9486_WR_DATA(0x2F);
    ILI9486_WR_DATA(0x45);
    ILI9486_WR_DATA(0x43);
    ILI9486_WR_DATA(0x02);
    ILI9486_WR_DATA(0x0A);
    ILI9486_WR_DATA(0x09);
    ILI9486_WR_DATA(0x32);
    ILI9486_WR_DATA(0x36);
    ILI9486_WR_DATA(0x0F);

    /* Sleep Out (11h) */
    ILI9486_WR_REG(0x11);
    Delay_ms(120);
    ILI9486_WR_REG(0x29);   //Display ON (29h)

    ILI9486_SetParam();     //设置LCD参数
    LCD_BL_WR(0);           //点亮背光
    ILI9486_Clear(WHITE);   //设置LCD背景显示颜色
}

/*
功  能： 向液晶屏写入8位指令
参  数： reg       待写入的指令值
返回值： 无
*/
void ILI9486_WR_REG(uint8_t reg)
{
    LCD->LCD_REG = reg;     //地址赋值
}

/*
功  能： 向液晶屏写入16位数据
参  数： data      待写入的数据
返回值： 无
*/
void ILI9486_WR_DATA(uint16_t data)
{
    LCD->LCD_DAT = data;    //地址赋值
}

/*
功  能： 向液晶屏写入一个16位颜色
参  数： color     RGB颜色
返回值： 无
*/
void ILI9486_DrawPoint_16Bit(uint16_t color)
{
#if ILI9486_USE8BIT_MODEL == 1      //用8位写入16位数据
    ILI9486_CS_CLR;                 //拉低使能脚允许写数据
    ILI9486_RD_SET;                 //读信号拉高
    ILI9486_RS_SET;                 //拉高选择信号位，控制写参数
    ILI9486_DATAOUT(color >> 8);    //数据线提供颜色的高八位
    ILI9486_WR_CLR;                 //拉低写脚
    ILI9486_WR_SET;                 //拉高写脚，完成数据写入寄存器
    ILI9486_DATAOUT(color);         //数据线提供颜色的低八位
    ILI9486_WR_CLR;                 //拉低写脚
    ILI9486_WR_SET;                 //拉高写脚，完成数据写入寄存器
    ILI9486_CS_SET;                 //拉高使能脚不允许写数据
#else                               //16位模式
    ILI9486_WR_DATA(color);         //使用16位数据线写入颜色
#endif
}

/*
功  能： 向液晶屏写入8位指令,16位数据
参  数： LI9486_reg        寄存器地址
         ILI9486_value     要写入的数据
返回值： 无
*/
void ILI9486_WriteReg(uint8_t ILI9486_reg, uint16_t ILI9486_value)
{
    ILI9486_WR_REG(ILI9486_reg);        //选择寄存器
    ILI9486_WR_DATA(ILI9486_value);     //写入需要的数据/功能
}

/*
功  能： 开始写GRAM
         在给液晶屏传送RGB数据前，应该发送写GRAM指令
参  数： 无
返回值： 无
*/
void ILI9486_WriteRAM_Prepare(void)
{
    ILI9486_WR_REG(lcddev.wramcmd);     //写入填充颜色指令
}

/*
功  能： 在指定位置(一个像素点)写入"画笔"颜色
参  数： (x,y)         光标坐标
返回值： 无
*/
void ILI9486_DrawPoint(uint16_t x, uint16_t y)
{
    ILI9486_SetCursor(x, y);            //设置光标位置
#if ILI9486_USE8BIT_MODEL == 1          //用8位写入16位数据
    ILI9486_CS_CLR;                     //拉低使能脚允许写数据
    ILI9486_RD_SET;                     //读信号拉高
    ILI9486_RS_SET;                     //拉高选择信号位，控制写参数
    ILI9486_DATAOUT(POINT_COLOR >> 8);  //数据线提供"画笔"颜色的程序高八位
    ILI9486_WR_CLR;                     //拉低写脚
    ILI9486_WR_SET;                     //拉高写脚，完成数据写入寄存器
    ILI9486_DATAOUT(POINT_COLOR);       //数据线提供"画笔"颜色的低八位
    ILI9486_WR_CLR;                     //拉低写脚
    ILI9486_WR_SET;                     //拉高写脚，完成数据写入寄存器
    ILI9486_CS_SET;                     //拉高使能脚不允许写数据
#else                                   //16位模式
    ILI9486_WR_DATA(POINT_COLOR);       //使用16位写入"画笔"颜色
#endif
}

/*
功能： 画LCD像素点函数
参数： x     像素点x坐标
       y     像素点y坐标
       color 要设置的颜色
返回值： 无
*/
void ILI9486_DrawPixel(uint16_t x, uint16_t y, uint16_t color)
{
    ILI9486_SetWindows(x, y, x, y); // 设置像素点的区域为单个点
    ILI9486_WR_DATA(color);         // 写入颜色数据
}

/*
功能： 画LCD圆角矩形
参数： sx         指定区域开始点x坐标
       sy         指定区域开始点y坐标
       ex         指定区域结束点x坐标
       ey         指定区域结束点y坐标
       innerColor 圆角框内的颜色
       radius     圆角半径
返回值： 无
*/

void ILI9486_DrawRoundedRect(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t innerColor, uint16_t radius)
{
    uint16_t width = ex - sx + 1;
    uint16_t height = ey - sy + 1;

    // 确保半径不超过矩形宽度和高度的一半
    if (radius > width / 2) {
        radius = width / 2;
    }
    if (radius > height / 2) {
        radius = height / 2;
    }

    // 画圆角
    for (int16_t y = -radius; y <= radius; y++) {
        for (int16_t x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                // 确定圆角的内切位置
                int16_t rx = x < 0 ? sx + radius : ex - radius;
                int16_t ry = y < 0 ? sy + radius : ey - radius;
                ILI9486_DrawPixel(rx + x, ry + y, innerColor);
            }
        }
    }

    // 填充矩形内部
    for (int16_t x = sx + radius; x < ex - radius; x++) {
        for (int16_t y = sy; y <= ey; y++) {
            ILI9486_DrawPixel(x, y, innerColor);
        }
    }

    for (int16_t y = sy + radius; y < ey - radius; y++) {
        for (int16_t x = sx; x <= ex; x++) {
            ILI9486_DrawPixel(x, y, innerColor);
        }
    }
}



/*
功  能： LCD区域填充函数
参  数： sx     指定区域开始点x坐标
         sy     指定区域开始点y坐标
         ex     指定区域结束点x坐标
         ey     指定区域结束点y坐标
         c      要填充的颜色
返回值： 无
*/
void ILI9486_Fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t c)
{
    uint16_t i = 0, j = 0;                      //建立全局变量
    uint16_t width = ex - sx + 1;               //得到填充的宽度
    uint16_t height = ey - sy + 1;              //高度
    ILI9486_SetWindows(sx, sy, ex - 1, ey - 1); //设置填充区域
#if ILI9486_USE8BIT_MODEL == 1                  //用8位写入16位数据
    ILI9486_RS_SET;                             //拉高选择信号位，控制写参数
    ILI9486_CS_CLR;                             //拉低使能脚允许写数据
    for (i = 0; i < height; i++)                //高度for循环
    {
        for (j = 0; j < width; j++)             //宽度for循环
        {
            ILI9486_DATAOUT(c >> 8);            //数据线提供颜色的代码高八位
            ILI9486_WR_CLR;                     //拉低写脚
            ILI9486_WR_SET;                     //拉高写脚，完成数据写入寄存器
            ILI9486_DATAOUT(c);                 //数据线提供颜色的低八位
            ILI9486_WR_CLR;                     //拉低写脚
            ILI9486_WR_SET;                     //拉高写脚，完成数据写入寄存器
        }
    }
    ILI9486_CS_SET;                             //拉高使能脚不允许写数据
#else                                           //16位模式
    for (i = 0; i < height; i++)                //高度for循环
    {
        for (j = 0; j < width; j++)             //宽度for循环
            ILI9486_WR_DATA(c);                 //写入数据
    }
#endif
    ILI9486_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);//恢复窗口设置为全屏
}

/*
功  能： LCD全屏填充清屏函数
参  数： color     要清屏的填充色
返回值： 无
*/
void ILI9486_Clear(uint16_t color)
{
    ILI9486_Fill(0, 0, lcddev.width , lcddev.height , color);//LCD全屏填充清屏
}

/*
功  能： 设置显示窗口起始坐标和结束坐标
参  数： (xstar,ystar)     窗口左上角起始坐标
         (xend,yend)       窗口右下角结束坐标
返回值： 无
******************************************************************/
void ILI9486_SetWindows(uint16_t xstar, uint16_t ystar, uint16_t xend, uint16_t yend)
{
    ILI9486_WR_REG(lcddev.setxcmd);     //Column Address Set列地址设置
    ILI9486_WR_DATA(xstar >> 8);        //X起始地址高八位
    ILI9486_WR_DATA(0x00FF & xstar);    //X起始地址低八位
    ILI9486_WR_DATA(xend >> 8);         //X结束地址高八位
    ILI9486_WR_DATA(0x00FF & xend);     //X结束地址低八位

    ILI9486_WR_REG(lcddev.setycmd);     //Page Address Set页地址设置
    ILI9486_WR_DATA(ystar >> 8);        //Y起始地址高八位
    ILI9486_WR_DATA(0x00FF & ystar);    //Y起始地址低八位
    ILI9486_WR_DATA(yend >> 8);         //Y结束地址高八位
    ILI9486_WR_DATA(0x00FF & yend);     //Y结束地址低八位

    ILI9486_WriteRAM_Prepare();         //开始写GRAM指令
}

/*
功  能： 设置光标位置
参  数： Xpos      横坐标
         Ypos      纵坐标
返回值： 无
*/
void ILI9486_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
    ILI9486_WR_REG(lcddev.setxcmd);                 //Column Address Set列地址设置
    ILI9486_WR_DATA(Xpos >> 8);                     //Xpos起始地址高八位
    ILI9486_WR_DATA(0x00FF & Xpos);                 //Xpos起始地址低八位
    ILI9486_WR_DATA((lcddev.width - 1) >> 8);       //结束地址高八位
    ILI9486_WR_DATA(0x00FF & (lcddev.width - 1));   //结束地址低八位

    ILI9486_WR_REG(lcddev.setycmd);                 //Page Address Set页地址设置
    ILI9486_WR_DATA(Ypos >> 8);                     //Y起始地址高八位
    ILI9486_WR_DATA(0x00FF & Ypos);                 //Y起始地址低八位
    ILI9486_WR_DATA((lcddev.height - 1) >> 8);      //结束地址高八位
    ILI9486_WR_DATA(0x00FF & (lcddev.height - 1));  //结束地址低八位
    ILI9486_WriteRAM_Prepare();                     //开始写GRAM指令
}

/*
功  能： 设置LCD参数，用于选择横屏还是竖屏
参  数： 无
返回值： 无
*/
void ILI9486_SetParam(void)
{
    lcddev.setxcmd = 0x2A;  //写X起始和结束点的寄存器地址
    lcddev.setycmd = 0x2B;  //写Y起始和结束点的寄存器地址
    lcddev.wramcmd = 0x2C;  //填充指令的寄存器地址
#if USE_HORIZONTAL == 0     //使用横屏
    lcddev.dir = 1;         //横屏参数
    lcddev.width = 480;     //设置宽为480
    lcddev.height = 320;    //设置高为320
    ILI9486_WriteReg(0x36, (1 << 3) | (1 << 7) | (1 << 5));//设置显示参数，BGR==1,MY==1,MX==0,MV==1
#else                       //使用竖屏
    lcddev.dir = 0;         //竖屏参数
    lcddev.width = 320;     //设置宽为320
    lcddev.height = 480;    //设置高为480
    ILI9486_WriteReg(0x36, (1 << 3) | (1 << 6) | (1 << 7));//设置显示参数，BGR==1,MY==0,MX==0,MV==0
#endif
}
