#ifndef _SPI_H
#define _SPI_H

///* Physical level marcos */

#define  SD_SPI   (HT_SPI1)

//Ñ¡ÔñÏß
#define  SD_SPI_SEL_PORT    (GPIO_PC)
#define  SD_SPI_SEL_PIN 			(GPIO_PIN_1)

#define  SD_SPI_SCLK_PIN 		  (GPIO_PIN_2)
#define  SD_SPI_SCLK_PORT 		  (GPIO_PC)

#define  SD_SPI_MOSI_PIN 			(GPIO_PIN_3)
#define  SD_SPI_MOSI_PORT			(GPIO_PC)

#define  SD_SPI_MISO_PIN			  (GPIO_PIN_6)
#define  SD_SPI_MISO_PORT			(GPIO_PB)

#define	SD_SPI_MOSI_OUT_H HT_GPIOC->SRR = GPIO_PIN_3
#define	SD_SPI_MOSI_OUT_L HT_GPIOC->RR = GPIO_PIN_3

#define	SPI_SCLK_OUT_H HT_GPIOC->SRR = GPIO_PIN_2
#define	SPI_SCLK_OUT_L HT_GPIOC->RR = GPIO_PIN_2


void SPI1_Init(int b_high);
int SPI1_ReadWrite(unsigned char data);
void SPI1_Gpio_Init(void);
#endif

