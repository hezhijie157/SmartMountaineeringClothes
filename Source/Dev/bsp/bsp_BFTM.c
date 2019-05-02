#include "bsp_BFTM.h"

void BF_TIM_int(void) 
{
	unsigned char i;
	
	CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
  /*
     Configures the system clock in startup file (startup_ht32fxxxx.s)
     by calling SystemInit function. Please refer to system_ht32fxxxx.c.
  */
  CKCUClock.Bit.BFTM0      = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);
//  HT32F_DVB_LEDInit(HT_LED1);
  NVIC_EnableIRQ(BFTM0_IRQn);
  /* toggel LED1 every 0.5 second by match interrupt                                                        */
  BFTM_SetCompare(HT_BFTM0, SystemCoreClock/10 * 1);//1秒一次
  BFTM_SetCounter(HT_BFTM0, 0);
  BFTM_IntConfig(HT_BFTM0, ENABLE);
  BFTM_EnaCmd(HT_BFTM0, ENABLE);
	
	for(i=0;i< MAX_TIMER ;i++)
	 g_Timer[i] = 0;   //全局定时器初始化

}



/*********************************************************************************************************//**
 * @brief   This function handles BFTM interrupt.定时器中断
 * @retval  None
 ************************************************************************************************************/
void BFTM0_IRQHandler(void)
{ 
	unsigned char i;
	  for (i = 0; i < MAX_TIMER; i++)					// 定时时间递减							
			if( g_Timer[i] ) g_Timer[i]-- ;
  BFTM_ClearFlag(HT_BFTM0);
} 

