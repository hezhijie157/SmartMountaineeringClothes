#ifndef _BSP_BFTM_H
#define _BSP_BFTM_H

#include "config.h"

#define  MAX_TIMER  		8						// ���ʱ������
EXT volatile unsigned long  g_Timer[MAX_TIMER]; 
#define  GetTempTimer	      g_Timer[0]				// ��ȡ�¶����ݶ�ʱ��
#define  SendToOneNetTimer  g_Timer[1]	 			//��ʱ����������OneNet
#define  SetHMIDataTimer  	g_Timer[2]	 			// ����������������
#define  GetATT7022Timer  	g_Timer[3]	 			//��ʱ��ȡ����оƬ�������
#define  GetOneNetKeyTimer  g_Timer[4]	 			//��ѯ�ƶ˿���
#define  GetNAOZHONGTimer   g_Timer[5]        //����
#define  CompareKeyTimer    g_Timer[6]        //���ж��Ƿ�رռ̵����ж��ƶ�������
#define  GetPictureTimer       g_Timer[7] 
void BF_TIM_int(void);     

#endif
