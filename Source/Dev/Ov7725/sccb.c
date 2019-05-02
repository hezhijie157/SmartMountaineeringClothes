#include "config.h"
#include "sccb.h"

#define SdelayTime   6
#define LdelayTime   12

//初始化SCCB接口
//CHECK OK
void SCCB_Init(void)
{			
 	  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    CKCUClock.Bit.PC         = 1;
    CKCUClock.Bit.AFIO       = 1;
    CKCUClock.Bit.BKP        = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
              
		//scl
		AFIO_GPxConfig(SCCB_SCLK_PORT, SCCB_SCLK_PIN, AFIO_MODE_DEFAULT); //HZJ  Want Check again!!
		GPIO_DirectionConfig(GPIO_PORT[SCCB_SCLK_PORT], SCCB_SCLK_PIN, GPIO_DIR_OUT);	 
		GPIO_OpenDrainConfig(GPIO_PORT[SCCB_SCLK_PORT],SCCB_SCLK_PIN,DISABLE);    ///WZH outPP Mode
		         
		//sda
		AFIO_GPxConfig(SCCB_SDA_PORT, SCCB_SDA_PIN, AFIO_MODE_DEFAULT);  //HZJ  Want Check again!!
		GPIO_DirectionConfig(GPIO_PORT[SCCB_SCLK_PORT], SCCB_SDA_PIN, GPIO_DIR_IN); //HZJ Modify  GPIO_DIR_OUT -> GPIO_DIR_IN
		GPIO_PullResistorConfig(GPIO_PORT[SCCB_SCLK_PORT], SCCB_SDA_PIN, GPIO_PR_UP);//HZJ Input PULLUP
		GPIO_InputConfig(GPIO_PORT[SCCB_SCLK_PORT], SCCB_SDA_PIN,ENABLE);  	//HZJ Input enable
		

		SCCB_SDA_OUT();	   
}			 



//SCCB起始信号
//当时钟为高的时候,数据线的高到低,为SCCB起始信号
//在激活状态下,SDA和SCL均为低电平
void SCCB_Start(void)
{
  
	
	SCCB_SDA_High();
	SCCB_SCL_High();
	Delay_10us(SdelayTime); 
	SCCB_SDA_Low();
	Delay_10us(SdelayTime); 
	SCCB_SCL_Low();
}

//SCCB停止信号
//当时钟为高的时候,数据线的低到高,为SCCB停止信号
//空闲状况下,SDA,SCL均为高电平
void SCCB_Stop(void)
{
		SCCB_SDA_Low();
	Delay_10us(SdelayTime); 
	SCCB_SCL_High();
	Delay_10us(SdelayTime);
	SCCB_SDA_High();
	Delay_10us(SdelayTime);
//    SCCB_SDA(RESET);
//   Delay_10us(SdelayTime);  	 
//    SCCB_SCL(SET);	
//   Delay_10us(SdelayTime);   
//    SCCB_SDA(SET);	
//   Delay_10us(SdelayTime);  
	
}  
//产生NA信号
void SCCB_No_Ack(void)
{
	Delay_10us(SdelayTime);
	SCCB_SDA_High();
	SCCB_SCL_High();
  Delay_10us(SdelayTime);	
	SCCB_SCL_Low();
	Delay_10us(SdelayTime);
	SCCB_SDA_Low();
	Delay_10us(SdelayTime); 	
//	Delay_10us(SdelayTime);  
//	SCCB_SDA(SET);	
//	SCCB_SCL(SET);	
//	Delay_10us(SdelayTime);  
//	SCCB_SCL(RESET);	
//	Delay_10us(SdelayTime);  
//	SCCB_SDA(RESET);	
//	Delay_10us(SdelayTime);  
}
//SCCB,写入一个字节
//返回值:0,成功;1,失败. 
u8 SCCB_WR_Byte(u8 dat)
{
	u8 j,res;	 
		for(j=0;j<8;j++) //循环8次发送数据
	{
		if(dat&0x80)SCCB_SDA_High();	
		else SCCB_SDA_Low();
		dat<<=1;
		Delay_10us(SdelayTime);  
		SCCB_SCL_High();	
		Delay_10us(SdelayTime);  
		SCCB_SCL_Low();		   
	}		
  SCCB_SDA_IN();		//设置SDA为输入 	
	Delay_10us(SdelayTime);  
	SCCB_SCL_High();			//接收第九位,以判断是否发送成功
	Delay_10us(SdelayTime);  
	if(SCCB_READ_SDA)res=1;  //SDA=1发送失败，返回1
	else res=0;         //SDA=0发送成功，返回0
	SCCB_SCL_Low();	
  SCCB_SDA_OUT();		//设置SDA为输出 	
	return res;  
//	for(j=0;j<8;j++) //循环8次发送数据
//	{
//		if(dat&0x80)SCCB_SDA(SET);	
//		else SCCB_SDA(RESET);
//		dat<<=1;
//		Delay_10us(SdelayTime);  
//		SCCB_SCL(SET);	
//		Delay_10us(SdelayTime);  
//		SCCB_SCL(RESET);		   
//	}			 
//	SCCB_SDA_IN();		//设置SDA为输入 
//	Delay_10us(SdelayTime);  
//	SCCB_SCL(SET);			//接收第九位,以判断是否发送成功
//	Delay_10us(SdelayTime);  
//	if(SCCB_READ_SDA)res=1;  //SDA=1发送失败，返回1
//	else res=0;         //SDA=0发送成功，返回0
//	SCCB_SCL(RESET);		 
//	SCCB_SDA_OUT();		//设置SDA为输出    
//	return res;  
}	 
//SCCB 读取一个字节
//在SCL的上升沿,数据锁存
//返回值:读到的数据
u8 SCCB_RD_Byte(void)
{
	u8 temp=0,j;  
  SCCB_SDA_IN();		//设置SDA为输入 	
	for(j=8;j>0;j--) 	//循环8次接收数据
	{		     	  
		Delay_10us(SdelayTime);  
		SCCB_SCL_High();	
		temp=temp<<1;
		if(SCCB_READ_SDA)temp++;   
		Delay_10us(SdelayTime);  
		SCCB_SCL_Low();	
	}	 
	SCCB_SDA_OUT();		//设置SDA为输出 
	return temp;
} 							    
//写寄存器
//返回值:0,成功;1,失败.
u8 SCCB_WR_Reg(u8 reg,u8 data)
{
	u8 res=0;
	SCCB_Start(); 					//启动SCCB传输
	if(SCCB_WR_Byte(SCCB_ID))res=1;	//写器件ID	  
	Delay_10us(LdelayTime);  
  	if(SCCB_WR_Byte(reg))res=1;		//写寄存器地址	  
	Delay_10us(LdelayTime);
  	if(SCCB_WR_Byte(data))res=1; 	//写数据	 
  	SCCB_Stop();	  
  	return	res;
}		  					    
//读寄存器
//返回值:读到的寄存器值
u8 SCCB_RD_Reg(u8 reg)
{
	u8 val=0;
	SCCB_Start(); 				//启动SCCB传输
	SCCB_WR_Byte(SCCB_ID);		//写器件ID	  
	Delay_10us(LdelayTime);	 
  SCCB_WR_Byte(reg);			//写寄存器地址	  
	Delay_10us(LdelayTime);	  
	SCCB_Stop();   
	Delay_10us(LdelayTime);	   
	//设置寄存器地址后，才是读
	SCCB_Start();
	SCCB_WR_Byte(SCCB_ID|0X01);	//发送读命令	  
	Delay_10us(LdelayTime);
  	val=SCCB_RD_Byte();		 	//读取数据
  	SCCB_No_Ack();
  	SCCB_Stop();
  	return val;
}















