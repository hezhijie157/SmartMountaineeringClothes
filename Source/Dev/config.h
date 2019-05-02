#ifndef _CONFIG_H
#define _CONFIG_H


// MAIN_CONFIG��	main.c ����#define  MAIN_CONFIG
#ifdef 	 MAIN_CONFIG										// ͷ�ļ������C�ļ�����,���������ͻ������ 
	#define  EXT											// ���ļ��ж���ı���
#else
	#define  EXT	extern									// ȫ���ļ�����������
#endif

#define  DEBUG     1      //����ʹ��λ

#if DEBUG
#define DEBUG_PRINT(...) 							                     \
		do {					  					                     \
		  printf("In %s - function %s at line %d: ", __FILE__, __func__, __LINE__);	\
		  printf(__VA_ARGS__);								\
		} while(0)
#else
  #define DEBUG_PRINT(...) (void)0
#endif	

#define FAIL     0
#define TURE     !FAIL	
	
#include "ht32.h"
#include "ht32_board.h"
#include "string.h"
#include "stdarg.h"
#include "stdlib.h"
#include "bsp_18b20.h"
#include "bsp_spi.h"
#include "bsp_i2c.h"
#include "bsp_uart.h"
#include "system.h"
#include "SPI_MSD0_Driver.h"
#include "ff.h"
#include "exfuns.h"
#include "malloc.h"
#include "ov7725.h"
#include "bsp_exti.h"
#include "bsp_BFTM.h"
#include "bmp.h"
#include "BMP280.h"
#include "GPS.h"
#include "GPRS.h"
#include "GA6_Error.h"
#include "bsp_SysTick.h"

#define UART1_BUF_LEN 	  100 //����2���泤��
#endif

