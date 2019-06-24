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

#define KVID                1


#define TIMEDREPORT         1
#define TIMETEMPDWARNING        2
#define TIMEHUMIDWARNING        3


#define IMEI_LEN			15
#define IMSI_LEN			15
#define ICCID_LEN			20

#define HIGHTTEMPW          0X01
#define LOWTEMPW            0X01<<1
#define HIGHTHUMIW          0X01<<2
#define LOWHUMIW            0X01<<3
#define LOWPOWREW           0X01<<4

#define REPORTCYCLE			300  //上报周期300S
#define HIGHTTEMPTHRE		30	//高温报警阈值30℃
#define LOWTTEMPTHRE		10	//低温报警阈值10℃
#define TEMPDELYWARN		1	//温度延时报警1min
#define TEMPCORRECT		    0	//温度修正值0
#define HIGHTHUMITHRE		80 //高湿报警阈值80%
#define LOWTHUMITHRE		20	//低湿报警阈值20%
#define HUMIDELYWARN		1	//湿度延时报警1min
#define BATTERYTHRES		20	//电池报警阈值20%

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
	TempWarning_data,
	HumiWarning_data,
};
struct SysGPS_INFO{

			uint8 		Position;
			uint32		longitude;
			uint32		latitude;

};

typedef struct
{
	uint16 Temperature;//温度
	uint8 humidity;//湿度
	uint8 tempwarningflag;//温度报警标志位信息
	uint8 humiwarningfalg;//湿度报警信息标志位
	uint8 oldtempwarning;//上次温度报警信息
	uint8 oldhumiwarning;//上次湿度度报警信息
	uint8 warning;//报警信息
	uint32 ReportCycle;//上报周期
	uint16 HightTempThreshold;//高温报警阈值
	uint16 LowTempThreshold;//低温报警阈值
	uint8  TempDelayWarn;//温度延时报警
	uint16 TempCorrect;//温度修正值
	uint8  HightHumiThreshold;//高湿报警阈值
	uint8  LowHumiThreshold;//低湿报警阈值
	uint8  HumiDelayWarn;//湿度延时报警
	uint8  BatteryThreshold;//电池报警阈值
	uint32 SendDataNum;//发送数据包个数
	uint32 AckDataNum;//应答数据包个数
	uint8 RegCompLedflag;//注册完成LED灯灭标志
	SysSta DeviceSta;//设备状态
	char Module_IMEI  [IMEI_LEN+1];
	char Module_IMSI  [IMSI_LEN+1];
	char Module_ICCID [ICCID_LEN+1];
}SysValue;
typedef struct
{
	uint32 ReportCycle;//上报周期
	uint16 HightTempThreshold;//高温报警阈值
	uint16 LowTempThreshold;//低温报警阈值
	uint8  TempDelayWarn;//温度延时报警
	uint16 TempCorrect;//温度修正值
	uint8  HightHumiThreshold;//高湿报警阈值
	uint8  LowHumiThreshold;//低湿报警阈值
	uint8  HumiDelayWarn;//湿度延时报警
	uint8  BatteryThreshold;//电池报警阈值
} __attribute__((packed)) kvTempHumi;


extern kvTempHumi LierdatempHumiKv;
extern SysValue Lierda_SysValue;

//
void TimerControlFun(uint8 timerid,uint8 control,uint32 timer);//定时器控制函数
void QueueSendDataFun(uint8 *msg);//队列发送函数
void lierda_App_main(void);
void lierda_App_task(void *param);
void Lierda_SoftTimerCallback(void *param);
void lierda_ReadSensor(void);
void DeviceParametersave(void);

#endif /* SRC_APP_REFERENCE_APPLICATION_CORE_APP_H_ */
