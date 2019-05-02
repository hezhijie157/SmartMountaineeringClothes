#include "bsp_SysTick.h"

/* Private variables ---------------------------------------------------------------------------------------*/
static vu32 DelayTime;

void SysTick_Init()
{
	SYSTICK_ClockSourceConfig(SYSTICK_SRC_STCLK);       // Default : CK_SYS/8
  SYSTICK_SetReloadValue(SystemCoreClock / 8 / 100000); // (CK_SYS/8/1000) = 1ms on chip
  SYSTICK_IntConfig(ENABLE);                          // Enable SYSTICK Interrupt
}

void Delay(u32 nTime)//20ms
{
	nTime = nTime * 20*100;
  /* Enable the SysTick Counter */
  SYSTICK_CounterCmd(SYSTICK_COUNTER_CLEAR);
  SYSTICK_CounterCmd(SYSTICK_COUNTER_ENABLE);

  DelayTime = nTime ;

  while(DelayTime != 0);


}
void Delay_10us(u32 nTime)
{
  /* Enable the SysTick Counter */
  SYSTICK_CounterCmd(SYSTICK_COUNTER_CLEAR);
  SYSTICK_CounterCmd(SYSTICK_COUNTER_ENABLE);

  DelayTime = nTime ;

  while(DelayTime != 0);
}

void TimingDelay(void)
{
  if(DelayTime != 0)
  {
    DelayTime--;
  }
}
