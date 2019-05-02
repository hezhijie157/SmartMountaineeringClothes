#ifndef UART_H
#define UART_H

#if DEBUG
#define Debug_Usart(x) USART1_Init(x)
#endif
void UART1_Init(long int baudrate);   //PB4\5    TX.RX
void UART0_Init(long int baudrate);   //PB2\3
void USART1_Init(long int baudrate);  //PA4\5
void USART0_Init(long int baudrate);   //PA2\3


void UART1_SendBuffer(char* dat);
void UART0_SendBuffer(char* dat);
void USART0_SendBuffer(char* dat);
void USART1_SendBuffer(char* dat);
#endif
