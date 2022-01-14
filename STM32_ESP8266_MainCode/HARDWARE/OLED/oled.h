#ifndef __OLED_H
#define __OLED_H 

#include "sys.h"
#include "stdlib.h"	

//-----------------OLED端口定义---------------- 

#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOC,GPIO_Pin_8)//CLK
#define OLED_SCLK_Set() GPIO_SetBits(GPIOC,GPIO_Pin_8)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOC,GPIO_Pin_9)//DIN
#define OLED_SDIN_Set() GPIO_SetBits(GPIOC,GPIO_Pin_9)

#define OLED_RST_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_11)//RES
#define OLED_RST_Set() GPIO_SetBits(GPIOB,GPIO_Pin_11)




#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

#define u8 unsigned char
#define u32 unsigned int

void OLED_ClearPoint(u8 x,u8 y);
void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_WaitAck(void);
void Send_Byte(u8 dat);
void OLED_WR_Byte(u8 dat,u8 mode);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);                                    //更新显存到OLED    PS:毎显示一次东西加一个更新显存
void OLED_Clear(void);                                      //清屏
void OLED_DrawPoint(u8 x,u8 y);                             //画点
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2);                //画线
void OLED_DrawCircle(u8 x,u8 y,u8 r);                       //画圆
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1);              //显示字符、ASICII
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1);           //显示字符串
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1);       //显示2个数字
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1);           //显示汉字
void OLED_ScrollDisplay(u8 num,u8 space);
void OLED_WR_BP(u8 x,u8 y);
void OLED_ShowPicture(u8 x0,u8 y0,u8 x1,u8 y1,u8 BMP[]);    //显示图片   图片分辨率128*64
void OLED_Init(void);                                       //OLED初始化

#endif
