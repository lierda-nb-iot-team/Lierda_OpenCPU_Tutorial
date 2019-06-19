/******************************************************************************
* @内容	GPS头文件
 * @设计	Lierda NB-IoT 软件设计团队@2018
******************************************************************************/
#ifndef SRC_LIB_OPENMCU_PUBLIC_LIERDA_HDGPS_H_
#define SRC_LIB_OPENMCU_PUBLIC_LIERDA_HDGPS_H_

#include "neulfw.h"
#include "lierdaGPIO.h"

#define RX_PIN    PIN_26
#define TX_PIN    PIN_24
#define UART_BAUD 9600
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
}GPS_DATE;

extern GPS_DATE  HA_GPSData;
void usart_init(void);
void gps_updata(uint8 *EW_data,uint32 *Longitude_data,uint32 *Latitude_data);

#endif /* SRC_LIB_OPENMCU_PUBLIC_LIERDA_HDGPS_H_ */
