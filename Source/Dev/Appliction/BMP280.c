#include "config.h"

#define BMP_DEV_ADDR  (0XEC)
#define BMP_RE        (0XED)
#define BMP_ID        (0X58)
struct bmp_280t bmp280;
void delay_ms(unsigned long int ms);
void BMP_WriteByte(unsigned char addr,unsigned char buff);
void BMP_Read(unsigned char addr,unsigned char *buff,int size);
/*******************************************************************************************************
** 函数: BMP_Init, 
**------------------------------------------------------------------------------------------------------
** 参数: void
** 返回: void
*******************************************************************************************************/
void BMP_Init(struct bmp_280t *q_bmp)
{
	u8 data_calip[24] = {0};
	I2c_GpioInit();
	DEBUG_PRINT("I2C init complete\r\n");
	q_bmp->dev_addr = BMP_DEV_ADDR;
	q_bmp->read = BMP_Read;
	q_bmp->write_byte = BMP_WriteByte;
	q_bmp->delay = delay_ms;
	q_bmp->read(ID_ADDR,&(q_bmp->chip_id),1);
	
	if(q_bmp->chip_id != BMP_ID)
	{
		q_bmp->flag = 1;
		DEBUG_PRINT("BMP read chip id failure, error :%d",q_bmp->flag);
		return;
	}
	q_bmp->read(CALIP_FIRST_ADDR,data_calip,24);
	
	q_bmp->calib_param.dig_T1 = (u16)((((u16)((u8)data_calip[1]))<<8)|data_calip[0]);
	q_bmp->calib_param.dig_T2 = (s16)((((s16)((s8)data_calip[3]))<<8)|data_calip[2]);
	q_bmp->calib_param.dig_T3 = (s16)((((s16)((s8)data_calip[5]))<<8)|data_calip[4]);	
	q_bmp->calib_param.dig_P1 = (u16)((((u16)((u8)data_calip[7]))<<8)|data_calip[6]);		
	q_bmp->calib_param.dig_P2 = (s16)((((s16)((s8)data_calip[9]))<<8)|data_calip[8]);		
	q_bmp->calib_param.dig_P3 = (s16)((((s16)((s8)data_calip[11]))<<8)|data_calip[10]);	
	q_bmp->calib_param.dig_P4 = (s16)((((s16)((s8)data_calip[13]))<<8)|data_calip[12]);
	q_bmp->calib_param.dig_P5 = (s16)((((s16)((s8)data_calip[15]))<<8)|data_calip[14]);
	q_bmp->calib_param.dig_P6 = (s16)((((s16)((s8)data_calip[17]))<<8)|data_calip[16]);	
	q_bmp->calib_param.dig_P7 = (s16)((((s16)((s8)data_calip[19]))<<8)|data_calip[18]);	
	q_bmp->calib_param.dig_P8 = (s16)((((s16)((s8)data_calip[21]))<<8)|data_calip[20]);	
	q_bmp->calib_param.dig_P9 = (s16)((((s16)((s8)data_calip[23]))<<8)|data_calip[22]);	
	DEBUG_PRINT("BMP init complete\r\n");
		/*/开始配置*/
	q_bmp->write_byte(CONFIG_ADDR,0x10);  //配置filter  *16 【100】和采样间隔时间 0.5ms 【000】
  q_bmp->delay(500);
	DEBUG_PRINT("BMP config filter and ts_b complete\r\n");
	q_bmp->write_byte(CREL_MEAS_ADDR,0x2f); //配置osrs_t *1 【001】和osrs_p *4 【011】,和电源模式为normal 【11】
	q_bmp->delay(500);
	DEBUG_PRINT("BMP config osrs_t 、osrs_p and power compelet\r\n ");
}

/*******************************************************************************************************
** 函数: BMP_Get_Temp, 
**------------------------------------------------------------------------------------------------------
** 参数: q_bmp
** 返回: void
*******************************************************************************************************/
void BMP_Get_Temp(struct bmp_280t *q_bmp)
{
	double var1,var2;
	u8 v_data[3],status;
	DEBUG_PRINT("开始采集温度\r\n");
	q_bmp->read(STATUS_ADDR,&status,1);
	if((status & 0x08) == 0x08)
	{
		DEBUG_PRINT("温度采样未结束 status ：%d\r\n",status);
		return;
	}
		DEBUG_PRINT("温度采样完成 status ：%d\r\n",status);
	q_bmp->read(TEMP_MSB,v_data,3);
	q_bmp->un_compensate_temp = (((s32)v_data[0])<<12)|((s32)v_data[1]<<4) |((v_data[2]>>4)&0x0f);
	var1 = (((double)q_bmp->un_compensate_temp)/16384.0 -((double)q_bmp->calib_param.dig_T1)/1024.0)*((double)q_bmp->calib_param.dig_T2);
	var2 = ((((double)q_bmp->un_compensate_temp)/131072.0 - ((double)q_bmp->calib_param.dig_T1)/8192.0) * (((double)q_bmp->un_compensate_temp)/131072.0
        		- ((double)q_bmp->calib_param.dig_T1)/8192.0))*((double)q_bmp->calib_param.dig_T3);
	q_bmp->calib_param.t_fine = (s32)(var1 + var2);
	q_bmp->temperature = (var1 + var2)/5120.0;
	DEBUG_PRINT("温度读取完成 Temperature is ：%lf\r\n",q_bmp->temperature);
}
/*******************************************************************************************************
** 函数: BMP_Get_press, 
**------------------------------------------------------------------------------------------------------
** 参数: q_bmp
** 返回: void
*******************************************************************************************************/
void BMP_Get_press(struct bmp_280t *q_bmp)
{
	double var1,var2,p;
	u8 v_data[3],status;
		DEBUG_PRINT("开始采集气压\r\n");
	q_bmp->read(STATUS_ADDR,&status,1);
	if((status & 0x08) == 0x08)
	{
		DEBUG_PRINT("气压采样未结束 status ：%d\r\n",status);
		return;
	}
	q_bmp->read(PRESS_MSB_ADDR,v_data,3);
	q_bmp->un_compensate_pressure = (((s32)v_data[0])<<12)|((s32)v_data[1]<<4) |((v_data[2]>>4)&0x0f);
		DEBUG_PRINT("气压采样完成 status ：%d\r\n",status);
	var1 = ((double)q_bmp->calib_param.t_fine/2.0)-64000.0;
	var2 = var1 * var1 * ((double)q_bmp->calib_param.dig_P6)/32768.0;
	var2 = var2 + var1 * ((double)q_bmp->calib_param.dig_P5) * 2.0;
	var2 = (var2/4.0) + (((double)q_bmp->calib_param.dig_P4) * 65536.0);
	var1 = (((double)q_bmp->calib_param.dig_P3) * var1 *var1/524288.0 + ((double)q_bmp->calib_param.dig_P2) * var1)
					/524288.0;
	var1 = (1.0 + var1 / 32768.0)*((double)q_bmp->calib_param.dig_P1);
	if(var1 == 0.0)
	{
		DEBUG_PRINT("avoid exception casued by division by zero. var1 is: %lf\r\n",var1);
		return ;
	}
	p = 1048576.0 - (double)q_bmp->un_compensate_pressure;
	p = (p - (var2/4096.0)) * 6250.0/var1;
	var1 = ((double)q_bmp->calib_param.dig_P9) * p * p / 2147483648.0;
	var2 = p * ((double)q_bmp->calib_param.dig_P8) / 32768.0;
	p = p + (var1 + var2 + (double)q_bmp->calib_param.dig_P7) / 16.0;
	q_bmp->pressure = p/100;
	q_bmp->high = (1013.25-q_bmp->pressure)*9.02;
	DEBUG_PRINT("气压读取完成 pressure is ：%lf\r\n",q_bmp->pressure);
	DEBUG_PRINT("高度换算完成 high is ：%lf\r\n",q_bmp->high);
}
/*******************************************************************************************************
** 函数: BMP_WriteByte,向指定地址写入一字节数据
**------------------------------------------------------------------------------------------------------
** 参数: addr 地址 ，buff 数据
** 返回: void
********************************************************************************************************/
void BMP_WriteByte(unsigned char addr,unsigned char buff)
{	
	I2cStart();
	I2cWriteByte(BMP_DEV_ADDR);           I2cNoACK();
	I2cWriteByte(addr);                   I2cNoACK();
	I2cWriteByte(buff);                   I2cNoACK();	
 	I2cStop();
	
}

/*******************************************************************************************************
** 函数: BMP_ReadByte,从指定地址读取一字节数据
**------------------------------------------------------------------------------------------------------
** 参数: addr 地址 ，buff 数据指针
** 返回: void
********************************************************************************************************/
void BMP_ReadByte(unsigned char addr,unsigned char *buff)
{
	I2cStart();
	I2cWriteByte(BMP_DEV_ADDR);   I2cNoACK(); 
	I2cWriteByte(addr);           I2cNoACK(); 	
	I2cStart();
	I2cWriteByte(BMP_RE);         I2cNoACK(); 	
	I2cReadByte(buff);           I2cNoACK();// I2cNoACK();
	I2cStop();
}
/*******************************************************************************************************
** 函数: BMP_Read,从指定地址读取字符串数据
**------------------------------------------------------------------------------------------------------
** 参数: addr 地址 ，buff 数据指针 ，size 数据长度
** 返回: void
********************************************************************************************************/
void BMP_Read(unsigned char addr,unsigned char *buff,int size)
{
	I2cStart();
	I2cWriteByte(BMP_DEV_ADDR);     I2cNoACK(); 
	I2cWriteByte(addr);             I2cNoACK(); 	
	I2cStart();
	I2cWriteByte(BMP_RE);           I2cNoACK(); 	
	while(size--)
	{
		I2cReadByte(buff++); 
		if(size)
		{
			I2cACK();
		}
		else 
		{
			I2cNoACK();
		}
	}
	I2cStop();

}

/*******************************************************************************************************
** 函数: delay_ms,延时
**------------------------------------------------------------------------------------------------------
** 参数: ms
** 返回: void
********************************************************************************************************/
void delay_ms(unsigned long int ms)
{
	while(ms--);
}

