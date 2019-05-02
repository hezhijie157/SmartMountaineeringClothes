#include "config.h"
char GPS_Buff[GPS_Buff_MAX];
gps_struct gps_data;
 
void GPS_init(void)
{
	USART0_Init(9600);
	memset(GPS_Buff,'\0',GPS_Buff_MAX);
	gps_data.Lat = 0;
	gps_data.Lon = 0;
	gps_data.isGetData = 0;
	DEBUG_PRINT("GPS initial complete¡£buffer is clear\r\n");
}

u8 GPS_DataHandle(gps_struct *gps_p )
{
	 char buffe[50];
	if(gps_data.isGetData == 1)
	{
		if(strstr(GPS_Buff,",,,,,,"))
		{
		    //nosign
			return FAIL;
		}
		sscanf(GPS_Buff,"%*[^,],%[^,]",buffe);
		gps_data.Lat = atof(buffe);
		
		memset(buffe,'\0',sizeof(buffe));
		sscanf(GPS_Buff,"%*[^N]%[^E]",buffe);
		sscanf(buffe,"%*[^,],%[^,]",GPS_Buff);
		gps_data.Lon = atof(GPS_Buff);
		return TURE;
	}
	else
	{
		return FAIL;
	}
}
