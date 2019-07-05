/******************************************************************************
 * @鍐呭	鍗庡ぇ鍖楁枟HD8020鐩稿叧鍑芥暟
 * @璁捐	Lierda NB-IoT 杞欢璁捐鍥㈤槦@2018
******************************************************************************/

#ifndef SRC_LIB_GPS_PUBLIC_GPS_AYS_H_
#define SRC_LIB_GPS_PUBLIC_GPS_AYS_H_

#include "neulfw.h"
#include "ServerProtocol.h"

#define USRT_SIZE   1024
#define TRANS_SIZE  300
uint8  Usrt_buff[USRT_SIZE];
uint8  Trans_buff[TRANS_SIZE];

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
extern  GPSRMCStruct  GPSData;

/********************************************************
 *鍑芥暟: void lierda_GPS_task_enable(void)
 *鍏ュ彛: None
 *鍑哄彛: None
 *姒傝堪: 鍒涘缓骞跺惎鍔℅PS浠诲姟绾跨▼
 ********************************************************/
void lierda_GPS_task_enable(void);

/********************************************************
 *鍑芥暟: void lierda_GPS_task_disable(void)
 *鍏ュ彛: None
 *鍑哄彛: None
 *姒傝堪: 缁堟GPS浠诲姟绾跨▼鎵ц
 ********************************************************/
void lierda_GPS_task_disable(void);

/********************************************************
 *鍑芥暟: void lierda_GPS_data_get( GPSRMCStruct *p_gps_user )
 *鍏ュ彛: None
 *鍑哄彛: None
 *姒傝堪: 鐢ㄦ埛鑾峰彇GPS鏁版嵁鍑芥暟(缁撴瀯浣撴寚閽�)
 ********************************************************/
void lierda_GPS_data_get( GPSRMCStruct *p_gps_user);

void lierda_GPS_uart_init(void);


#endif /* SRC_LIB_GPS_PUBLIC_GPS_AYS_H_ */



