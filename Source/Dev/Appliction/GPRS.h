#ifndef _GPRS_H
#define _GPRS_H

#define USART1_REC_MAXLEN 200	//���������ݳ���
#define STABLE_TIMES  1  //�ȴ�ϵͳ�ϵ����ȶ�

void SendTCP(char *IP_port,char *message);
void SendText(char *message);
#endif

