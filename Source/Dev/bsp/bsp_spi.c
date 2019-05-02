#include "ht32.h"
#include "config.h"
#include "bsp_spi.h"



/*******************************************************************************************************
** 函数: SPI_Init, SPI延时函数
**------------------------------------------------------------------------------------------------------
** 参数: NONE 
** 返回: NONE
*******************************************************************************************************/
void SPI1_Init(int b_high)
{
SPI_InitTypeDef  SPI_InitStructure;
	 /*  SPI Configuration                                                                                     */
  SPI_InitStructure.SPI_Mode = SPI_MASTER;
  SPI_InitStructure.SPI_FIFO = SPI_FIFO_DISABLE;
  SPI_InitStructure.SPI_DataLength = SPI_DATALENGTH_8;
  SPI_InitStructure.SPI_SELMode = SPI_SEL_SOFTWARE;
  SPI_InitStructure.SPI_SELPolarity = SPI_SELPOLARITY_LOW;
  SPI_InitStructure.SPI_FirstBit = SPI_FIRSTBIT_MSB;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_HIGH;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_SECOND;
  SPI_InitStructure.SPI_RxFIFOTriggerLevel = 0;
  SPI_InitStructure.SPI_TxFIFOTriggerLevel = 0;
	 if(b_high == 0)
  {
	  SPI_InitStructure.SPI_ClockPrescaler = 16;
  }
  else
  {
	  SPI_InitStructure.SPI_ClockPrescaler = 2;
  }

	SPI_Init(SD_SPI, &SPI_InitStructure);

  SPI_SELOutputCmd(SD_SPI, ENABLE);


}


void SPI1_Gpio_Init(void)
{
		  /*  Enable AFIO & SPI SEL pin port & SPI clock                                                            */
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
  FLASH_SPI_SEL_CLK(CKCUClock) = 1;
  FLASH_SPI_CLK(CKCUClock)     = 1;
  CKCUClock.Bit.AFIO           = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

	  /*  Configure SPI SEL pin                                                                                 */
  GPIO_SetOutBits(GPIO_PORT[GPIO_PD], GPIO_PIN_0);
  GPIO_DirectionConfig(GPIO_PORT[GPIO_PD], GPIO_PIN_0, GPIO_DIR_OUT);

  /*  Configure SPI SCK pin_PIN_5, SPI MISO pin 9, SPI MOSI pin 8                                                    */
  AFIO_GPxConfig(GPIO_PC, FLASH_SPI_SCK_AFIO_PIN, FLASH_SPI_SCK_AFIO_MODE);
  AFIO_GPxConfig(GPIO_PC, FLASH_SPI_MISO_AFIO_PIN, FLASH_SPI_MISO_AFIO_MODE);
  AFIO_GPxConfig(GPIO_PC, FLASH_SPI_MOSI_AFIO_PIN, FLASH_SPI_MOSI_AFIO_MODE);

	

  MSD0_card_disable(); 

  MSD0_SPIHighSpeed(0);		

  SPI_Cmd(HT_SPI1, ENABLE);// SPI_Cmd(SPI1, ENABLE);  //HZJ
	
}
/*******************************************************************************************************
** 函数: SPI2_ReadWrite, SPI发送一个字节，同时接收一个字节
**------------------------------------------------------------------------------------------------------
** 参数: dat 发送数据 
** 返回: 接收数据
*******************************************************************************************************/
int SPI1_ReadWrite(uint8_t data)
{

	 /* Loop while Tx buffer register is empty                                                                 */
  while (!SPI_GetFlagStatus(SD_SPI, SPI_FLAG_TXBE));

  /* Send byte through the SPIx peripheral                                                                  */
  SPI_SendData(SD_SPI, data);

  /* Loop while Rx is not empty                                                                             */
  while (!SPI_GetFlagStatus(SD_SPI, SPI_FLAG_RXBNE));

  /* Return the byte read from the SPI                                                                      */
  return SPI_ReceiveData(SD_SPI);
}
