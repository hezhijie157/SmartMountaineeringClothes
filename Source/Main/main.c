/*********************************************************************************************************//**
 * @file    IP/Example/main.c
 * @version $Rev:: 971          $
 * @date    $Date:: 2016-09-08 #$
 * @brief   Main program.
 *************************************************************************************************************
*/
// <<< Use Configuration Wizard in Context Menu >>>

/* Includes ------------------------------------------------------------------------------------------------*/

#define  MAIN_CONFIG
#include "config.h"

/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
	extern struct bmp_280t bmp280;
        /* Work area (file system object) for logical drive */
 FIL fsrc, fdst;      /* file objects */
 FRESULT res;
extern UINT bw;
char textFileBuffer[] = {"hhhsdsadad"};
char buffer[250];
int main(void)
{

//	KeyInit();
	//π“‘ÿSDø® 	
	SysInit();
 //master

//Tortoise

	while(1)
	{
		 BackTask();
	}

}




