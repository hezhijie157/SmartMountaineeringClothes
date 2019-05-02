#include "bsp_exti.h"
//#include "delay.h" 

#include "ov7725.h"


void EXTIX_Init(void)
{ //PA8 <----> ov7725 VSYNC
	  EXTI_InitTypeDef EXTI_InitStruct = {0};
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    
		CKCUClock.Bit.PA = 1;
    /* Enable the EXTI Clock                                                                                */
    CKCUClock.Bit.EXTI       = 1;
		CKCUClock.Bit.BKP				 = 1;
		CKCUClock.Bit.AFIO			 = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
		
		AFIO_GPxConfig(GPIO_PA,GPIO_PIN_8,AFIO_FUN_GPIO);
		GPIO_PullResistorConfig(HT_GPIOA,GPIO_PIN_8,GPIO_PR_DISABLE);
		GPIO_DirectionConfig(HT_GPIOA, GPIO_PIN_8, GPIO_DIR_IN);
    GPIO_InputConfig(HT_GPIOA, GPIO_PIN_8, ENABLE);

    /* Connect Button EXTI Channel to Button GPIO Pin                                                       */
    AFIO_EXTISourceConfig(AFIO_EXTI_CH_8,(AFIO_ESS_Enum) GPIO_PA);

    /* Configure button EXTI Line on falling edge                                                           */
    EXTI_InitStruct.EXTI_Channel = EXTI_CHANNEL_8;
    EXTI_InitStruct.EXTI_Debounce = EXTI_DEBOUNCE_DISABLE;
    EXTI_InitStruct.EXTI_DebounceCnt = 0;
    EXTI_InitStruct.EXTI_IntType =  EXTI_POSITIVE_EDGE ; //HZJ,Check Again!!
    EXTI_Init(&EXTI_InitStruct);
		
		
		  /* Enable Button EXTI Interrupt                                                                         */
    EXTI_IntConfig(EXTI_CHANNEL_8, ENABLE);
   
    NVIC_EnableIRQ(EXTI4_15_IRQn);
   
}
u8 ov_sta=0;	//帧中断标记
 //外部中断4~15服务程序

void EXTI4_15_IRQHandler(void)
{

 if(EXTI_GetEdgeStatus(EXTI_CHANNEL_8,EXTI_EDGE_POSITIVE))
  {
    if(ov_sta<2)
		{
			if(ov_sta==0)
			{
				OV7725_WRST(RESET);	 	//复位写指针		  		 
				OV7725_WRST(SET);	
				OV7725_WREN(SET);		//允许写入FIFO
			}else 
			{
				OV7725_WREN(RESET);		//禁止写入FIFO 
				OV7725_WRST(RESET);	 	//复位写指针		  		 
				OV7725_WRST(SET);	
			}
			ov_sta++;
		}
    EXTI_ClearEdgeFlag(EXTI_CHANNEL_8);
  }
	
		
}









