/******************************************************************************
 * @内容	用户任务头文件
 * @设计	Lierda NB-IoT 软件设计团队@2018
******************************************************************************/

#ifndef SRC_APP_REFERENCE_APPLICATION_CORE_APP_H_
#define SRC_APP_REFERENCE_APPLICATION_CORE_APP_H_
//include
#include "neulfw.h"
#include "cmsis_os2.h"
#include "string.h"
#include <assert.h>
#include "led.h"
#include "key.h"
#include "lierda_HDC1000.h"
#include "lierda_OPT3001DN.h"
#include "lierda_app_main.h"
#include "ServerProtocol.h"
#include "Lierda_NNMI.h"
#include "Lierda_Hdgps.h"

#define TIMEDREPORT 1
#define IMEI_LEN			15
#define IMSI_LEN			15
#define ICCID_LEN			20
#define SENDCYCLE			30

typedef enum
{
	Power_ON=1,
	ConnectNet,
	Device_Reg,
	Reg_Complete,
}SysSta;
enum datatype{
	Timer_data=1,
	key_data,
	Stachange_data,
};
struct SysGPS_INFO{

			uint8 		Position;
			uint32		longitude;
			uint32		latitude;

};

typedef struct
{
	uint8 StreetLightSta;//路灯状态
	uint32 Illuminance;//光照强度
	uint32 SendDataNum;//发送数据包个数
	uint32 AckDataNum;//应答数据包个数
	uint8 RegCompLedflag;//注册完成LED灯灭标志
	SysSta DeviceSta;//设备状态
	char Module_IMEI  [IMEI_LEN+1];
	char Module_IMSI  [IMSI_LEN+1];
	char Module_ICCID [ICCID_LEN+1];
	struct SysGPS_INFO gpsinfo;
}SysValue;

extern SysValue Lierda_SysValue;

//
void TimerControlFun(uint8 timerid,uint8 control,uint32 timer);//定时器控制函数
void QueueSendDataFun(uint8 *msg);//队列发送函数
void lierda_App_main(void);
void lierda_App_task(void *param);
void Lierda_SoftTimerCallback(void *param);
void lierda_ReadSensor(void);

#endif /* SRC_APP_REFERENCE_APPLICATION_CORE_APP_H_ */
