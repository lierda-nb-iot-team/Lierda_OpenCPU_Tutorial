/******************************************************************************
 * @内容	华大北斗HD8020相关函数
 * @设计	Lierda NB-IoT 软件设计团队@2018
******************************************************************************/

#ifndef SRC_LIB_GPS_PUBLIC_GPS_AYS_H_
#define SRC_LIB_GPS_PUBLIC_GPS_AYS_H_

#include "neulfw.h"

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
 *函数: void lierda_GPS_task_enable(void)
 *入口: None
 *出口: None
 *概述: 创建并启动GPS任务线程
 ********************************************************/
void lierda_GPS_task_enable(void);

/********************************************************
 *函数: void lierda_GPS_task_disable(void)
 *入口: None
 *出口: None
 *概述: 终止GPS任务线程执行
 ********************************************************/
void lierda_GPS_task_disable(void);

/********************************************************
 *函数: void lierda_GPS_data_get( GPSRMCStruct *p_gps_user )
 *入口: None
 *出口: None
 *概述: 用户获取GPS数据函数(结构体指针)
 ********************************************************/
void lierda_GPS_data_get( GPSRMCStruct *p_gps_user);

/********************************************************
 *函数: void lierda_user_GPS_uart_init(uint32 uBaudRate, uint8 uRX_pin, uint8 uTX_pin)
 *入口: uBaudRate，波特率     uRX_pin，接收管脚     uTX_pin，发送管脚
 *出口: None
 *概述: 串口初始化函数
 *备注: 先执行串口初始化函数，后执行创建并启动GPS任务线程函数
 ********************************************************/
void lierda_user_GPS_uart_init(uint32 uBaudRate, uint8 uRX_pin, uint8 uTX_pin);


#endif /* SRC_LIB_GPS_PUBLIC_GPS_AYS_H_ */



