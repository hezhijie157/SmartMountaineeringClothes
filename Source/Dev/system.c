#include "system.h"
#include "config.h"


u8 *pname;			//带路径的文件名 
FATFS g_fs;         /* Work area (file system object) for logical drive */
//FIL fsrc, fdst;      /* file objects */
//FRESULT res;
//UINT br,bw;
u8 z=1;
	extern struct bmp_280t bmp280;
void SysInit (void)
{

	Debug_Usart(115200);
	BF_TIM_int();
	//配置SPI1接口

	SysTick_Init();
	
	if(OV7725_Init()== 0x00 )
	{
		OV7725_Light_Mode(0);
		OV7725_Color_Saturation(0);
		OV7725_Brightness(0);
		OV7725_Contrast(0);
		OV7725_Special_Effects(0);
		OV7725_Window_Set(320,240,0);//QVGA模式输出
		OV7725_CS(RESET);
	}
	my_mem_init(SRAMIN);	//初始化内部内存池
	
	MSD0_SPI_Configuration();
	f_mount(0,&g_fs); 	
  z = exfuns_init();				//为fatfs相关变量申请内存  

	//
  	EXTIX_Init();
//	f_mount(0,&g_fs);
//	z = exfuns_init();	
//	EXTIX_Init();
//	BMP_Init(&bmp280);
}




/*
	
static void Task_GetTemperature(void)
{
	if( GetTempTimer ) return;
	GetTempTimer = GetTempTimerConst;  //获取温度
	g_val[5]=DS18B20_Get_Temp();
}


static void Task_SendOnenet(void)
{
	if( SendToOneNetTimer ) return;
	SendToOneNetTimer = SendToOneNetTimerConst;  //发送数据至云端
	Send_onenet();
}


static void Task_SendHIM(void)
{
	if( SetHMIDataTimer ) return;
	SetHMIDataTimer = SetHMIDataTimerConst;  //发送数据至触摸屏
	Send_HIM();
}

static void Task_GetATT7022(void)
{
	if( GetATT7022Timer  ) return;
	GetATT7022Timer  = GetATT7022TimerConst ;  //获取电能数据
	AttGetAllVolue();
}

static void Task_GetKey(void)//未使用
{
	if(GetOneNetKeyTimer)return;
	GetOneNetKeyTimer = GetOneNetKeyTimerConst;
 
}

static void Task_CompareKey(void)
{
		if(CompareKeyTimer)return;
	  CompareKeyTimer = CompareKeyTimerConst;
  	http_response_len=0;
	  WIFI_SendCmd(HTTP_Buf,0);
		Sket_Delayms(100);         //等待串口接收数据

		if(OneNet_get())         //获取云端Switch值
		{
			g_KeyFlag1=1;
//	  HMI_SendCmd("succ");    
		}
		else g_KeyFlag1=0;
//		HMI_SendCmd("error");

}
*/

static void Task_GetTemperature(void)
{
	if( GetTempTimer ) return;
	GetTempTimer = GetTempTimerConst;  //获取温度
	BMP_Get_press(&bmp280);
	BMP_Get_Temp(&bmp280);
}

static void Task_GetPicture(void)
{
		if(GetPictureTimer)return;
	  GetPictureTimer = GetPictureTimerConst;
	 
	if(ov_sta==2)
	{
	
	
		OV7725_RRST(RESET);				//开始复位读指针 
		OV7725_RCK_L;
		OV7725_RCK_H;
		OV7725_RCK_L;
		OV7725_RRST(SET);				//复位读指针结束 
		OV7725_RCK_H; 
		
    pname=mymalloc(SRAMIN,30);	//为带路径的文件名分配30个字节的内存			
    camera_new_pathname(pname);
//		bmp_encode(pname,0,0,240,320,0);
			bmp_encode(pname,0,0,320,240,0);
		ov_sta=0;					//开始下一次采集
 
		
	} 

}
/*******************************************************************************************************
** 函数: BackTask，后台任务
**------------------------------------------------------------------------------------------------------
** 参数: void
** 返回: 无
** 作者: 
********************************************************************************************************/
void BackTask(void)
{
//	Task_GetTemperature( );
//	Task_GetATT7022( );
//  Task_SendOnenet( );
//	Task_SendHIM( );
//	//Task_GetKey( );//
//	Task_CompareKey( );
	Task_GetPicture();

}
