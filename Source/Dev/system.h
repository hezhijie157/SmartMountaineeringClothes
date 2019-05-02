#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "config.h"
EXT float g_val[9];
EXT char g_KeyFlag1;
#define  GetTempTimerConst        2
#define  SendToOneNetTimerConst   20
#define  SetHMIDataTimerConst  	  5
#define  GetATT7022TimerConst     2
#define  GetOneNetKeyTimerConst   3
#define  CompareKeyTimerConst     3
#define  GetPictureTimerConst    20 //1∑÷÷”“ª’≈Õº∆¨
void BackTask(void);
void SysInit(void);
void KeyInit(void);

#endif
