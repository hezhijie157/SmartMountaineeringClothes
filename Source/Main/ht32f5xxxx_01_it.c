/*********************************************************************************************************//**
 * @file    IP/Example/ht32f5xxxx_01_it.c
 * @version $Rev:: 1704         $
 * @date    $Date:: 2017-08-17 #$
 * @brief   This file provides all interrupt service routine.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include "config.h"
/** @addtogroup Project_Template Project Template
  * @{
  */

/** @addtogroup IP_Examples IP
  * @{
  */

/** @addtogroup Example
  * @{
  */


/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
 * @brief   This function handles NMI exception.
 * @retval  None
 ************************************************************************************************************/
void NMI_Handler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles Hard Fault exception.
 * @retval  None
 ************************************************************************************************************/
void HardFault_Handler(void)
{
  while (1);
}

/*********************************************************************************************************//**
 * @brief   This function handles SVCall exception.
 * @retval  None
 ************************************************************************************************************/
void SVC_Handler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles PendSVC exception.
 * @retval  None
 ************************************************************************************************************/
void PendSV_Handler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles SysTick Handler.
 * @retval  None
 ************************************************************************************************************/
extern void TimingDelay(void);
void SysTick_Handler(void)
{
	
  TimingDelay();
}
/*********************************************************************************************************//**
 * @brief   This function handles LVD & BOD interrupt.
 * @retval  None
 ************************************************************************************************************/
//void LVD_BOD_IRQHandler(void)
//{
//}

/*********************************************************************************************************//**
 * @brief   This function handles RTC interrupt.
 * @retval  None
 ************************************************************************************************************/
//void RTC_IRQHandler(void)
//{
//}

/*********************************************************************************************************//**
 * @brief   This function handles Flash interrupt.
 * @retval  None
 ************************************************************************************************************/
//void FLASH_IRQHandler(void)
//{
//}

/*********************************************************************************************************//**
 * @brief   This function handles Wake-up interrupt.
 * @retval  None
 ************************************************************************************************************/
//void EVWUP_IRQHandler(void)
//{
//}

/*********************************************************************************************************//**
 * @brief   This function handles EXTI interrupt.
 * @retval  None
 ************************************************************************************************************/
//void EXTI0_1_IRQHandler(void)
//{
//}

/*********************************************************************************************************//**
 * @brief   This function handles EXTI interrupt.
 * @retval  None
 ************************************************************************************************************/
//void EXTI2_3_IRQHandler(void)
//{
//}

/*********************************************************************************************************//**
 * @brief   This function handles EXTI interrupt.
 * @retval  None
 ************************************************************************************************************/
//void EXTI4_15_IRQHandler(void)
//{
//}

/*********************************************************************************************************//**
 * @brief   This function handles CMP interrupt.
 * @retval  None
 ************************************************************************************************************/
//void COMP_IRQHandler(void)
//{
//}

/*********************************************************************************************************//**
 * @brief   This function handles ADC interrupt.
 * @retval  None
 ************************************************************************************************************/
//void ADC_IRQHandler(void)
//{
//}

/*********************************************************************************************************//**
 * @brief   This function handles MCTM interrupt.
 * @retval  None
 ************************************************************************************************************/
//void MCTM0_IRQHandler(void)
//{
//}

/*********************************************************************************************************//**
 * @brief   This function handles GPTM interrupt.
 * @retval  None
 ************************************************************************************************************/
//void GPTM0_IRQHandler(void)
//{
//}

/*********************************************************************************************************//**
 * @brief   This function handles GPTM interrupt.
 * @retval  None
 ************************************************************************************************************/
//void GPTM1_IRQHandler(void)
//{
//}

/*********************************************************************************************************//**
 * @brief   This function handles SCTM interrupt.
 * @retval  None
 ************************************************************************************************************/
//void SCTM0_IRQHandler(void)
//{
//}

/*********************************************************************************************************//**
 * @brief   This function handles SCTM interrupt.
 * @retval  None
 ************************************************************************************************************/
//void SCTM1_IRQHandler(void)
//{
//}

/*********************************************************************************************************//**
 * @brief   This function handles SCTM interrupt.
 * @retval  None
 ************************************************************************************************************/
//void SCTM2_IRQHandler(void)
//{
//}

/*********************************************************************************************************//**
 * @brief   This function handles SCTM interrupt.
 * @retval  None
 ************************************************************************************************************/
//void SCTM3_IRQHandler(void)
//{
//}



/*********************************************************************************************************//**
 * @brief   This function handles BFTM interrupt.
 * @retval  None
 ************************************************************************************************************/
//void BFTM1_IRQHandler(void)
//{
//}

/*********************************************************************************************************//**
 * @brief   This function handles I2C interrupt.
 * @retval  None
 ************************************************************************************************************/
//void I2C0_IRQHandler(void)
//{
//}

/*********************************************************************************************************//**
 * @brief   This function handles I2C interrupt.
 * @retval  None
 ************************************************************************************************************/
//void I2C1_IRQHandler(void)
//{
//}

/*********************************************************************************************************//**
 * @brief   This function handles I2C interrupt.
 * @retval  None
 ************************************************************************************************************/
//void I2C2_IRQHandler(void)
//{
//}

/*********************************************************************************************************//**
 * @brief   This function handles SPI interrupt.
 * @retval  None
 ************************************************************************************************************/
//void SPI0_IRQHandler(void)
//{
//}

/*********************************************************************************************************//**
 * @brief   This function handles SPI interrupt.
 * @retval  None
 ************************************************************************************************************/
//void SPI1_IRQHandler(void)
//{
//}

/*********************************************************************************************************//**
 * @brief   This function handles USART interrupt.
 * @retval  None
 ************************************************************************************************************/
extern char GPS_Buff[];
char Usart0_Rxbuff[GPS_Buff_MAX];
char Usart0_point=0;
extern gps_struct gps_data;
	 u8 Usart0_res;
void USART0_IRQHandler(void)
{

	if (USART_GetFlagStatus(HT_USART0, USART_FLAG_RXDR))
  {
			USART_ClearFlag(HT_USART0,USART_FLAG_RXDR);
		Usart0_res = USART_ReceiveData(HT_USART0); 
		if(Usart0_res=='$')
		{
			Usart0_point = 0;
		}
		Usart0_Rxbuff[Usart0_point++] = Usart0_res;
		if(Usart0_res == '\n')
		{
			if(Usart0_Rxbuff[4] == 'L' && gps_data.isGetData ==0)
			{
				memcpy(GPS_Buff,Usart0_Rxbuff,Usart0_point);
				gps_data.isGetData = 1;
			}
			  memset(Usart0_Rxbuff,'\0',GPS_Buff_MAX);
			  Usart0_point = 0;
		}
    return ;
  }
}

/*********************************************************************************************************//**
 * @brief   This function handles USART interrupt.
 * @retval  None
 ************************************************************************************************************/
u8 Usart1_res;
void USART1_IRQHandler(void)
{
	if(USART_GetFlagStatus(HT_USART1,USART_FLAG_RXDR))
  {
		USART_ClearFlag(HT_USART1,USART_FLAG_RXDR);
//		Usart1_res = USART_ReceiveData(HT_USART1);
  } 	
	
}

/*********************************************************************************************************//**
 * @brief   This function handles UART interrupt.
 * @retval  None
 ************************************************************************************************************/
//void UART0_IRQHandler(void)
//{
//}

/*********************************************************************************************************//**
 * @brief   This function handles UART interrupt.
 * @retval  None
 ************************************************************************************************************/
u8 Uart1_res = 0;
extern char Uart1_Buf[];//����2���ջ���
extern u8 First_Int;
void UART1_IRQHandler(void)
{
if(USART_GetFlagStatus(HT_UART1,USART_FLAG_RXDR))
  {
		USART_ClearFlag(HT_UART1,USART_FLAG_RXDR);
		Uart1_res= USART_ReceiveData(HT_UART1);
		Uart1_Buf[First_Int] = Uart1_res;  	  //�����յ����ַ����浽������
		First_Int++;                	  //����ָ������ƶ�
		if(First_Int >= UART1_BUF_LEN)       	  //���������,������ָ��ָ�򻺴���׵�ַ
		{
			First_Int = 0;
		}		
  }                                                                                                
}

/*********************************************************************************************************//**
 * @brief   This function handles UART interrupt.
 * @retval  None
 ************************************************************************************************************/
//void UART2_IRQHandler(void)
//{
//}

/*********************************************************************************************************//**
 * @brief   This function handles UART interrupt.
 * @retval  None
 ************************************************************************************************************/
//void UART3_IRQHandler(void)
//{
//}

/*********************************************************************************************************//**
 * @brief   This function handles SCI interrupt.
 * @retval  None
 ************************************************************************************************************/
//void SCI_IRQHandler(void)
//{
//}

/*********************************************************************************************************//**
 * @brief   This function handles I2S interrupt.
 * @retval  None
 ************************************************************************************************************/
//void I2S_IRQHandler(void)
//{
//}

/*********************************************************************************************************//**
 * @brief   This function handles USB interrupt.
 * @retval  None
 ************************************************************************************************************/
//void USB_IRQHandler(void)
//{
//}

/*********************************************************************************************************//**
 * @brief   This function handles PDMA interrupt.
 * @retval  None
 ************************************************************************************************************/
//void PDMA_CH0_1_IRQHandler(void)
//{
//}

/*********************************************************************************************************//**
 * @brief   This function handles PDMA interrupt.
 * @retval  None
 ************************************************************************************************************/
//void PDMA_CH2_5_IRQHandler(void)
//{
//}


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
