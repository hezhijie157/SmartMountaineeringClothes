#include "bsp_uart.h"
#include "config.h"

/*********************************************************************************************************//**
  * @brief UART1��ʼ�����������ж� ,�жϺ�����it.c
  * @param  baudrate :������
  * @retval None
  ***********************************************************************************************************/
void UART1_Init(long int baudrate)
{

 USART_InitTypeDef USART_InitStructure;
  /* Enable peripheral clock of AFIO                                                              */
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
  CKCUClock.Bit.AFIO   = 1;
  CKCUClock.Bit.UART1  = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  /* Config AFIO mode as USART0_Rx and USART0_Tx function.*/
	
  AFIO_GPxConfig(GPIO_PB, AFIO_PIN_4, AFIO_MODE_6);
  AFIO_GPxConfig(GPIO_PB, AFIO_PIN_5, AFIO_MODE_6);

  USART_InitStructure.USART_BaudRate = baudrate;
  USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
  USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
  USART_InitStructure.USART_Parity = USART_PARITY_NO;
  USART_InitStructure.USART_Mode = USART_MODE_NORMAL;

  USART_Init(HT_UART1, &USART_InitStructure);
                                                                                  
  USART_TxCmd(HT_UART1, ENABLE);
  USART_RxCmd(HT_UART1, ENABLE);
	 USART_IntConfig(HT_UART1, USART_INT_RXDR, ENABLE);
  /* Configure USART0 & USART1 interrupt                                                                    */
  NVIC_EnableIRQ(UART1_IRQn);
}

/********************************************************************************************************
**	������: 	void UART1_SendBuffer(char* cmd)
**------------------------------------------------------------------------------------------------------- 
**	����: 	�򴮿ڷ���һ���ַ�
**	�β� : dat  �ַ���
**	����ֵ: ��
*******************************************************************************************************/
void UART1_SendBuffer(char* dat)
{
	while(*dat!='\0')
	{
		USART_SendData(HT_UART1, *dat);
		
	  while (!USART_GetFlagStatus(HT_UART1, USART_FLAG_TXC));//�˴�����ʹ��sizeof
		dat++;
	}
  
}

/*********************************************************************************************************//**
  * @brief USART1_Init ,���Դ���
  * @param  baudrate :������
  * @retval None
  ***********************************************************************************************************/
#if DEBUG
void USART1_Init(long int baudrate)
{
	 USART_InitTypeDef USART_InitStructure;

  /* Enable peripheral clock of AFIO, USART0                                                                */
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
  CKCUClock.Bit.AFIO   = 1;
  COM1_CLK(CKCUClock)  = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  /* Config AFIO mode as USART0_Rx and USART0_Tx function.                                                  */
  AFIO_GPxConfig(GPIO_PA, AFIO_PIN_4, AFIO_FUN_USART_UART);    //TX
  AFIO_GPxConfig(GPIO_PA, AFIO_PIN_5, AFIO_FUN_USART_UART);  

  USART_InitStructure.USART_BaudRate = baudrate;
  USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
  USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
  USART_InitStructure.USART_Parity = USART_PARITY_NO;
  USART_InitStructure.USART_Mode = USART_MODE_NORMAL;

  USART_Init(HT_USART1, &USART_InitStructure);
  USART_TxCmd(HT_USART1, ENABLE);
  USART_RxCmd(HT_USART1, ENABLE);
	
//	 USART_IntConfig(HT_USART1, USART_INT_RXDR, ENABLE);
  /* Configure USART0 & USART1 interrupt                                                                    */
//  NVIC_EnableIRQ(USART1_IRQn);
}
#endif

/*********************************************************************************************************//**
  * @brief UART0��ʼ�����������ж� ,�жϺ�����it.c
  * @param  baudrate :������
  * @retval None
  ***********************************************************************************************************/
void UART0_Init(long int baudrate)
{

 USART_InitTypeDef USART_InitStructure;
  /* Enable peripheral clock of AFIO                                                              */
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
  CKCUClock.Bit.AFIO   = 1;
  CKCUClock.Bit.UART0  = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  /* Config AFIO mode as USART0_Rx and USART0_Tx function.*/
	
  AFIO_GPxConfig(GPIO_PB, AFIO_PIN_2, AFIO_MODE_6);   //TX
  AFIO_GPxConfig(GPIO_PB, AFIO_PIN_3, AFIO_MODE_6);

  USART_InitStructure.USART_BaudRate = baudrate;
  USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
  USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
  USART_InitStructure.USART_Parity = USART_PARITY_NO;
  USART_InitStructure.USART_Mode = USART_MODE_NORMAL;

  USART_Init(HT_UART0, &USART_InitStructure);
                                                                                  
  USART_TxCmd(HT_UART0, ENABLE);
  USART_RxCmd(HT_UART0, ENABLE);
	 USART_IntConfig(HT_UART0, USART_INT_RXDR, ENABLE);
  /* Configure USART0 & USART1 interrupt                                                                    */
  NVIC_EnableIRQ(UART0_IRQn);
}

/********************************************************************************************************
**	������: 	void UART0_SendBuffer(char* cmd)
**------------------------------------------------------------------------------------------------------- 
**	����: 	�򴮿ڷ���һ���ַ�
**	�β� : dat  �ַ���
**	����ֵ: ��
*******************************************************************************************************/
void UART0_SendBuffer(char* dat)
{
	while(*dat!='\0')
	{
		USART_SendData(HT_UART0, *dat);
		
	  while (!USART_GetFlagStatus(HT_UART0, USART_FLAG_TXC));//�˴�����ʹ��sizeof
		dat++;
	}
  
}
/*********************************************************************************************************//**
  * @brief USART0_int  
  * @param  baudrate :������
  * @retval None
  ***********************************************************************************************************/
void USART0_Init(long int baudrate)
{
	  USART_InitTypeDef USART_InitStructure;
  /* Enable peripheral clock of AFIO                                                              */
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
  CKCUClock.Bit.AFIO   = 1;
  CKCUClock.Bit.USART0  = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  /* Config AFIO mode as USART0_Rx and USART0_Tx function.
	*/
  AFIO_GPxConfig(GPIO_PA, AFIO_PIN_2, AFIO_MODE_6);//tx
  AFIO_GPxConfig(GPIO_PA, AFIO_PIN_3, AFIO_MODE_6);
	
  USART_InitStructure.USART_BaudRate = baudrate;
  USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
  USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
  USART_InitStructure.USART_Parity = USART_PARITY_NO;
  USART_InitStructure.USART_Mode = USART_MODE_NORMAL;

  USART_Init(HT_USART0, &USART_InitStructure);
                                                                                  
  USART_TxCmd(HT_USART0, ENABLE);
  USART_RxCmd(HT_USART0, ENABLE);                                                                          
  USART_IntConfig(HT_USART0, USART_INT_RXDR, ENABLE);
  /* Configure USART0 & USART1 interrupt                                                                    */
  NVIC_EnableIRQ(USART0_IRQn);
}
/********************************************************************************************************
**	������: 	void UART0_SendBuffer(char* cmd)
**------------------------------------------------------------------------------------------------------- 
**	����: 	�򴮿ڷ���һ���ַ�
**	�β� : dat  �ַ���
**	����ֵ: ��
*******************************************************************************************************/
void USART0_SendBuffer(char* dat)
{
	while(*dat!='\0')
	{
		USART_SendData(HT_USART0, *dat);
		
	  while (!USART_GetFlagStatus(HT_USART0, USART_FLAG_TXC));//�˴�����ʹ��sizeof
		dat++;
	}
  
}
void USART1_SendBuffer(char* dat)
{
	while(*dat!='\0')
	{
		USART_SendData(HT_USART1, *dat);
		
	  while (!USART_GetFlagStatus(HT_USART1, USART_FLAG_TXC));//�˴�����ʹ��sizeof
		dat++;
	}
  
}

