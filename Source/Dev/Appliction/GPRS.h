#ifndef _GPRS_H
#define _GPRS_H

#define USART1_REC_MAXLEN 200	//最大接收数据长度
#define STABLE_TIMES  1  //等待系统上电后的稳定

void SendTCP(char *IP_port,char *message);
void SendText(char *message);
#endif

