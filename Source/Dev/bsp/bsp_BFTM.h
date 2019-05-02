#ifndef _BSP_BFTM_H
#define _BSP_BFTM_H

#include "config.h"

#define  MAX_TIMER  		8						// 最大定时器个数
EXT volatile unsigned long  g_Timer[MAX_TIMER]; 
#define  GetTempTimer	      g_Timer[0]				// 获取温度数据定时器
#define  SendToOneNetTimer  g_Timer[1]	 			//定时发送数据至OneNet
#define  SetHMIDataTimer  	g_Timer[2]	 			// 发送数据至串口屏
#define  GetATT7022Timer  	g_Timer[3]	 			//定时获取电能芯片相关数据
#define  GetOneNetKeyTimer  g_Timer[4]	 			//查询云端开关
#define  GetNAOZHONGTimer   g_Timer[5]        //闹钟
#define  CompareKeyTimer    g_Timer[6]        //将判断是否关闭继电器判断移动到外面
#define  GetPictureTimer       g_Timer[7] 
void BF_TIM_int(void);     

#endif
