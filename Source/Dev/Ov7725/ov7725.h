#ifndef _OV7725_H__
#define _OV7725_H__
#include "config.h"
#include "sccb.h"


#define OV7725_MID				0X7FA2    
#define OV7725_PID				0X7721

#define OV7725_VSYNC_PIN  GPIO_PIN_8
#define OV7725_VSYNC_PORT	(GPIO_PA)

#define OV7725_WRST_PIN 	GPIO_PIN_11
#define OV7725_WRST_PORT	(GPIO_PC)

#define OV7725_WREN_PIN		GPIO_PIN_12
#define OV7725_WREN_PORT	(GPIO_PC)

#define OV7725_RCK_PIN		GPIO_PIN_14
#define OV7725_RCK_PORT		(GPIO_PA)

#define OV7725_RRST_PIN		GPIO_PIN_15
#define OV7725_RRST_PORT	(GPIO_PA)

#define OV7725_CS_PIN			GPIO_PIN_10
#define OV7725_CS_PORT		(GPIO_PC)

#define OV7725_DATA_PORT  (GPIO_PA)
#define FIFO_D0_PIN  GPIO_PIN_0
#define FIFO_D1_PIN  GPIO_PIN_1
#define FIFO_D2_PIN  GPIO_PIN_2
#define FIFO_D3_PIN  GPIO_PIN_3
#define FIFO_D4_PIN  GPIO_PIN_4
#define FIFO_D5_PIN  GPIO_PIN_5
#define FIFO_D6_PIN  GPIO_PIN_6
#define FIFO_D7_PIN  GPIO_PIN_7


#define OV7725_VSYNC  				GPIO_ReadInBit(GPIO_PORT[OV7725_VSYNC_PORT],OV7725_VSYNC_PIN)	//同步信号检测IO
#define OV7725_WRST(Status)		GPIO_WriteOutBits(GPIO_PORT[OV7725_WRST_PORT], OV7725_WRST_PIN, Status)		//写指针复位
#define OV7725_WREN(Status)		GPIO_WriteOutBits(GPIO_PORT[OV7725_WREN_PORT], OV7725_WREN_PIN, Status)		//写入FIFO使能
#define OV7725_RCK_H					GPIO_WriteOutBits(GPIO_PORT[OV7725_RCK_PORT], OV7725_RCK_PIN, SET)//设置读数据时钟高电平
#define OV7725_RCK_L					GPIO_WriteOutBits(GPIO_PORT[OV7725_RCK_PORT], OV7725_RCK_PIN, RESET)	//设置读数据时钟低电平
#define OV7725_RRST(Status)		GPIO_WriteOutBits(GPIO_PORT[OV7725_RRST_PORT], OV7725_RRST_PIN, Status)  		//读指针复位
#define OV7725_CS(Status)			GPIO_WriteOutBits(GPIO_PORT[OV7725_CS_PORT], OV7725_CS_PIN, Status) 		//片选信号(OE)
								  					 
#define OV7725_DATA   				GPIO_ReadInData(GPIO_PORT[OV7725_DATA_PORT]) 	//数据输入端口

	    				 
u8   OV7725_Init(void);		  	   		 
void OV7725_Light_Mode(u8 mode);
void OV7725_Color_Saturation(s8 sat);
void OV7725_Brightness(s8 bright);
void OV7725_Contrast(s8 contrast);
void OV7725_Special_Effects(u8 eft);
void OV7725_Window_Set(u16 width,u16 height,u8 mode);
#endif





















