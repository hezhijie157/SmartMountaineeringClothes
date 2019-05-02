#ifndef _BSP_SYSTICK_H
#define _BSP_SYSTICK_H

#include "config.h"

void SysTick_Init(void);
void Delay(u32 nTime);
void TimingDelay(void);
void Delay_10us(u32 nTime);
#endif

