#ifndef _GPS_H
#define _GPS_H
#define GPS_Buff_MAX       100
typedef struct gps_sct{
	char isGetData;
	double Lat;
	double Lon;
}gps_struct;
void GPS_init(void);
#endif
