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
#include "lierda_app_main.h"
#include "ServerProtocol.h"
#include "Lierda_NNMI.h"
#include "lierdaKVStorage.h"
#include "Lierda_Hdgps.h"
#include "lierda_gps.h"


#define KVID                1


#define TIMEDREPORT            1
#define TIMECOOLLECGPS         2
#define TIMESEARCHGPS          3


#define IMEI_LEN			15
#define IMSI_LEN			15
#define ICCID_LEN			20


#define REPORTCYCLE			60  //上报周期120S
#define COOLLCYCLE		    10	//GPS采样周期
#define MAXSEARTIME		    10	//最大搜星时间
#define SEARHOLDTIME	    20	//搜星保持时间

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
	OpenGPS,
	CloseGPS,

};

enum DeviceMode{
	StandardMode=0,
	TrackerMode,
};

struct SysKvSave{
	enum DeviceMode DeviceMode;//设备模式
	uint32 CollCycle;//搜星周期
	uint32 ReportCycle;//上报周期
	uint32 MaxSearchTimer;//最大搜星时间
	uint32 GpsHoldTimer;//保持时间
} __attribute__((packed));


struct SysGPS_INFO{
			uint8 		SerialNum;//序号
			uint8 		SignalQuality;//0X01有效   0x00无效
			uint32		longitude;//经度
			uint32		latitude;//维度
			uint8 		Position;//方位
			uint8		UtcTime[3];//UTC时间
			uint8		NowTime[3];//当前时间
} __attribute__((packed));

typedef struct
{
	uint8 GpsHoldFlag;//gps保持标志位
	uint8 GpsDataNum;//gps缓存数据个数
	uint8 GpsDataNumFullFlag;//gps缓存数据满标志位
	uint8 GpsDataGetFlag;//gps数据获取标志位
	uint8 GpsPositSuc;//GPS定位成功标志位
	enum DeviceMode SysMode;//系统模式
	uint32 GpsHoldTimer;//保持时间
	uint32 CollCycle;//搜星周期
	uint32 ReportCycle;//上报周期
	uint32 MaxSearchTimer;//最大搜星时间
	uint32 SendDataNum;//发送数据包个数
	uint32 AckDataNum;//应答数据包个数
	uint8 RegCompLedflag;//注册完成LED灯灭标志
	SysSta DeviceSta;//设备状态
	struct SysGPS_INFO gpsInfo;
	char Module_IMEI  [IMEI_LEN+1];
	char Module_IMSI  [IMSI_LEN+1];
	char Module_ICCID [ICCID_LEN+1];
}SysValue;


extern struct SysKvSave syskvsave;
extern SysValue Lierda_SysValue;

//
void TimerControlFun(uint8 timerid,uint8 control,uint32 timer);//定时器控制函数
void QueueSendDataFun(uint8 *msg);//队列发送函数
void lierda_App_main(void);
void lierda_App_task(void *param);
void Lierda_SoftTimerCallback(void *param);
void DeviceParameterSave(void);
void Deviceswitch(void);
#endif /* SRC_APP_REFERENCE_APPLICATION_CORE_APP_H_ */
