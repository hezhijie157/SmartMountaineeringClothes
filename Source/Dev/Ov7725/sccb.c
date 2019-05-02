#include "config.h"
#include "sccb.h"

#define SdelayTime   6
#define LdelayTime   12

//��ʼ��SCCB�ӿ�
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



//SCCB��ʼ�ź�
//��ʱ��Ϊ�ߵ�ʱ��,�����ߵĸߵ���,ΪSCCB��ʼ�ź�
//�ڼ���״̬��,SDA��SCL��Ϊ�͵�ƽ
void SCCB_Start(void)
{
  
	
	SCCB_SDA_High();
	SCCB_SCL_High();
	Delay_10us(SdelayTime); 
	SCCB_SDA_Low();
	Delay_10us(SdelayTime); 
	SCCB_SCL_Low();
}

//SCCBֹͣ�ź�
//��ʱ��Ϊ�ߵ�ʱ��,�����ߵĵ͵���,ΪSCCBֹͣ�ź�
//����״����,SDA,SCL��Ϊ�ߵ�ƽ
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
//����NA�ź�
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
//SCCB,д��һ���ֽ�
//����ֵ:0,�ɹ�;1,ʧ��. 
u8 SCCB_WR_Byte(u8 dat)
{
	u8 j,res;	 
		for(j=0;j<8;j++) //ѭ��8�η�������
	{
		if(dat&0x80)SCCB_SDA_High();	
		else SCCB_SDA_Low();
		dat<<=1;
		Delay_10us(SdelayTime);  
		SCCB_SCL_High();	
		Delay_10us(SdelayTime);  
		SCCB_SCL_Low();		   
	}		
  SCCB_SDA_IN();		//����SDAΪ���� 	
	Delay_10us(SdelayTime);  
	SCCB_SCL_High();			//���յھ�λ,���ж��Ƿ��ͳɹ�
	Delay_10us(SdelayTime);  
	if(SCCB_READ_SDA)res=1;  //SDA=1����ʧ�ܣ�����1
	else res=0;         //SDA=0���ͳɹ�������0
	SCCB_SCL_Low();	
  SCCB_SDA_OUT();		//����SDAΪ��� 	
	return res;  
//	for(j=0;j<8;j++) //ѭ��8�η�������
//	{
//		if(dat&0x80)SCCB_SDA(SET);	
//		else SCCB_SDA(RESET);
//		dat<<=1;
//		Delay_10us(SdelayTime);  
//		SCCB_SCL(SET);	
//		Delay_10us(SdelayTime);  
//		SCCB_SCL(RESET);		   
//	}			 
//	SCCB_SDA_IN();		//����SDAΪ���� 
//	Delay_10us(SdelayTime);  
//	SCCB_SCL(SET);			//���յھ�λ,���ж��Ƿ��ͳɹ�
//	Delay_10us(SdelayTime);  
//	if(SCCB_READ_SDA)res=1;  //SDA=1����ʧ�ܣ�����1
//	else res=0;         //SDA=0���ͳɹ�������0
//	SCCB_SCL(RESET);		 
//	SCCB_SDA_OUT();		//����SDAΪ���    
//	return res;  
}	 
//SCCB ��ȡһ���ֽ�
//��SCL��������,��������
//����ֵ:����������
u8 SCCB_RD_Byte(void)
{
	u8 temp=0,j;  
  SCCB_SDA_IN();		//����SDAΪ���� 	
	for(j=8;j>0;j--) 	//ѭ��8�ν�������
	{		     	  
		Delay_10us(SdelayTime);  
		SCCB_SCL_High();	
		temp=temp<<1;
		if(SCCB_READ_SDA)temp++;   
		Delay_10us(SdelayTime);  
		SCCB_SCL_Low();	
	}	 
	SCCB_SDA_OUT();		//����SDAΪ��� 
	return temp;
} 							    
//д�Ĵ���
//����ֵ:0,�ɹ�;1,ʧ��.
u8 SCCB_WR_Reg(u8 reg,u8 data)
{
	u8 res=0;
	SCCB_Start(); 					//����SCCB����
	if(SCCB_WR_Byte(SCCB_ID))res=1;	//д����ID	  
	Delay_10us(LdelayTime);  
  	if(SCCB_WR_Byte(reg))res=1;		//д�Ĵ�����ַ	  
	Delay_10us(LdelayTime);
  	if(SCCB_WR_Byte(data))res=1; 	//д����	 
  	SCCB_Stop();	  
  	return	res;
}		  					    
//���Ĵ���
//����ֵ:�����ļĴ���ֵ
u8 SCCB_RD_Reg(u8 reg)
{
	u8 val=0;
	SCCB_Start(); 				//����SCCB����
	SCCB_WR_Byte(SCCB_ID);		//д����ID	  
	Delay_10us(LdelayTime);	 
  SCCB_WR_Byte(reg);			//д�Ĵ�����ַ	  
	Delay_10us(LdelayTime);	  
	SCCB_Stop();   
	Delay_10us(LdelayTime);	   
	//���üĴ�����ַ�󣬲��Ƕ�
	SCCB_Start();
	SCCB_WR_Byte(SCCB_ID|0X01);	//���Ͷ�����	  
	Delay_10us(LdelayTime);
  	val=SCCB_RD_Byte();		 	//��ȡ����
  	SCCB_No_Ack();
  	SCCB_Stop();
  	return val;
}















