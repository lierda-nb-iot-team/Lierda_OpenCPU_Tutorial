/*
 * HD_GPS.h
 *
 *  Created on: 2019Äê4ÔÂ25ÈÕ
 *      Author: Administrator
 */

#ifndef SRC_LIB_DEMO_PUBLIC_HD_GPS_H_
#define SRC_LIB_DEMO_PUBLIC_HD_GPS_H_

#include "lierdaUART.h"
#include "neulfw.h"
#include "cmsis_os2.h"
#include "string.h"
#include <assert.h>
#include "lierda_app_main.h"
#include "app.h"

#define RX_pin PIN_26
#define TX_pin PIN_24
#define GPSDATALENMAX 1024

typedef struct
{
	char	UTC_Time[20];			//Current time	hhmmss.sss
	char	Valid_status;			//V = Data Invalid / Receiver Warning, A=Data Valid
	char	Latitude[20];			//User datum latitude degrees, minutes, decimal minutes format
	char	NS_indicator;			//N/S Indicator  Hemisphere N=north or S=south
	char	Longitude[20];			//User datum latitude degrees, minutes, decimal minutes format
	char	EW_indicator;			//E/W indicator  'E'= East, or 'W' = West
	char	Spd[20];				//Speed  Speed Over Ground
	char	cog[20];				//COG  Course Over Ground
	char	Date[7];				//Current Date in Day, Month Year format ddmmyy
}GPSRMCStruct;
extern  GPSRMCStruct  Gps_Data;

extern uint8 DataStart;
extern uint8 DataEnd;
extern uint8 Timercount;
extern uint8 GpsDataBuff[GPSDATALENMAX];
extern uint16 GpsDataLen;
void lierda_Gps_task(void *argument);
void Gps_data_clear(void);
uint32 iRMC_decode(char* buff,uint32 len);


#endif /* SRC_LIB_DEMO_PUBLIC_HD_GPS_H_ */
