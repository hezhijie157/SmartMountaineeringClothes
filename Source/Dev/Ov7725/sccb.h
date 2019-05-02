#ifndef __SCCB_H__
#define __SCCB_H__
#include "config.h"


#define SCCB_SCLK_PIN    GPIO_PIN_14      //HZJ
#define SCCB_SCLK_PORT  (GPIO_PC)
#define SCCB_SDA_PIN    GPIO_PIN_15    //HZJ
#define SCCB_SDA_PORT  (GPIO_PC)


#define SCCB_SDA_IN()  {\
												GPIO_DirectionConfig(GPIO_PORT[SCCB_SDA_PORT], SCCB_SDA_PIN, GPIO_DIR_IN);\
												GPIO_PullResistorConfig(GPIO_PORT[SCCB_SDA_PORT], SCCB_SDA_PIN, GPIO_PR_UP);\
												GPIO_InputConfig(GPIO_PORT[SCCB_SDA_PORT], SCCB_SDA_PIN,ENABLE);  \
											 } //HZJ

#define SCCB_SDA_OUT() { \
												GPIO_DirectionConfig(GPIO_PORT[SCCB_SDA_PORT], SCCB_SDA_PIN, GPIO_DIR_OUT);   \
                        GPIO_OpenDrainConfig(GPIO_PORT[SCCB_SCLK_PORT],SCCB_SDA_PIN,DISABLE); \
                       } //HZJ

//IO操作函数	 

#define SCCB_SCL(Status)    		GPIO_WriteOutBits(GPIO_PORT[SCCB_SCLK_PORT], SCCB_SCLK_PIN, Status)	//HZJ//SCL
#define SCCB_SDA(Status)    		GPIO_WriteOutBits(GPIO_PORT[SCCB_SDA_PORT], SCCB_SDA_PIN, Status) 	//HZJ//SDA	

#define SCCB_SCL_High()          HT_GPIOC->SRR = GPIO_PIN_14          
#define SCCB_SCL_Low()           HT_GPIOC->RR = GPIO_PIN_14
#define SCCB_SDA_High()          HT_GPIOC->SRR = GPIO_PIN_15          
#define SCCB_SDA_Low()           HT_GPIOC->RR = GPIO_PIN_15

#define SCCB_READ_SDA    	GPIO_ReadInBit(GPIO_PORT[SCCB_SDA_PORT],SCCB_SDA_PIN) //HZJ PGin(13)  		//输入SDA    
#define SCCB_ID   			0X42  			//OV7670的ID
///////////////////////////////////////////
void SCCB_Init(void);
void SCCB_Start(void);
void SCCB_Stop(void);
void SCCB_No_Ack(void);
u8 SCCB_WR_Byte(u8 dat);
u8 SCCB_RD_Byte(void);
u8 SCCB_WR_Reg(u8 reg,u8 data);
u8 SCCB_RD_Reg(u8 reg);
void TimingDelay(void);
void SysTick_Init(void);
 void Delay_10us(u32 nTime);
#endif













