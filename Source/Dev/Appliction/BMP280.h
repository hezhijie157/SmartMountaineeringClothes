#ifndef _BMP_H
#define _BMP_H
#include "config.h"
#define CALIP_FIRST_ADDR    (0x88)
#define ID_ADDR             (0XD0)
#define RESET_ADDR          (0XE0)
#define STATUS_ADDR         (0XF3)
#define CREL_MEAS_ADDR      (0XF4)
#define CONFIG_ADDR         (0XF5)
#define PRESS_MSB_ADDR      (0XF7)
#define PRESS_LSB_ADDR      (0XF8)
#define PRESS_XLSB_ADDR     (0XF9)    //气压低位数据，只取bit7~4
#define TEMP_MSB            (0XFA)
#define TEMP_LSB_ADDR       (0XFB)
#define TEMP_XLSB_ADDR      (0XFC)    //温度低位数据，只取bit7~4

#define DATA_16bit          (0x01)
#define DATA_17bit          (0x02)
#define DATA_18bit          (0x03)
#define DATA_19bit          (0x04)
#define DATA_20bit          (0x05)

#define FILTER_OFF         (0X00)
#define FILTER_2           (0X01)
#define FILTER_4           (0X02)
#define FILTER_8           (0X03)
#define FILTER_16          (0X04)

#define SLEEP_MODE         (0X00)
#define FORCED_MODE        (0X01)
#define NORMAL_MODE        (0X03)
struct bmp280_calib_param_t {
	unsigned short int dig_T1;/**<calibration T1 data*/
	signed short int   dig_T2;/**<calibration T2 data*/
	signed short int   dig_T3;/**<calibration T3 data*/
	unsigned short int dig_P1;/**<calibration P1 data*/
	signed short int   dig_P2;/**<calibration P2 data*/
	signed short int   dig_P3;/**<calibration P3 data*/
	signed short int   dig_P4;/**<calibration P4 data*/
	signed short int   dig_P5;/**<calibration P5 data*/
	signed short int   dig_P6;/**<calibration P6 data*/
	signed short int   dig_P7;/**<calibration P7 data*/
	signed short int   dig_P8;/**<calibration P8 data*/
	signed short int   dig_P9;/**<calibration P9 data*/

	signed int         t_fine;/**<calibration t_fine data*/
};
struct bmp_280t
{
	struct bmp280_calib_param_t calib_param;
	char flag;      //flag 1:读取设备id失败，0：成功  2：写入设备失败
	unsigned char chip_id;
	char dev_addr;
	s32 un_compensate_temp;
	s32 un_compensate_pressure;
	double temperature;
	double pressure;
	double high;
	void (*delay)(unsigned long int);
	void (*read)(unsigned char ,unsigned char*,int);
	void (*write_byte)(unsigned char ,unsigned char);
};

void BMP_Init(struct bmp_280t *q_bmp);
void BMP_Get_press(struct bmp_280t *q_bmp);
void BMP_Get_Temp(struct bmp_280t *q_bmp);

#endif

