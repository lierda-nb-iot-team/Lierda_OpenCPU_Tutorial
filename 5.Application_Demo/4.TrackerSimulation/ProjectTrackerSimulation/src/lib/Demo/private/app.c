/******************************************************************************
 * @内容	用户任务函数
 * @设计	Lierda NB-IoT 软件设计团队@2018
******************************************************************************/
#include "app.h"

//全局变量
osThreadAttr_t App_task_attr = { "lierda_App_task"/*任务名称*/, 0, NULL, 0, NULL,
		(512) /*任务堆栈大小*/, 11/*任务优先级*/, 0, 0 };//任务属性结构体
uint32 * App_task_handle = NULL;

osThreadAttr_t LedSta_task_attr = { "lierda_LedSta_task"/*任务名称*/, 0, NULL, 0, NULL,
		(250) /*任务堆栈大小*/, 10/*任务优先级*/, 0, 0 };//任务属性结构体
uint32 * LedSta_task_handle = NULL;

osThreadAttr_t nnmi_task_attr = { "lierda_NNMI_task"/*任务名称*/, 0, NULL, 0, NULL,
		(256) /*任务堆栈大小*/, 11/*任务优先级*/, 0, 0 };//任务属性结构体
uint32 * NNMITaskHandle = NULL;

struct SysKvSave syskvsave;
SysValue Lierda_SysValue;
osTimerId_t Timedreport_handle=NULL;
osTimerId_t TimeCoollecGps_handle=NULL;
osTimerId_t TimeSearchGps_handle=NULL;
osMessageQueueId_t Lierda_App_queue=NULL;
uint32 Retimercount=0,TimerCollCount=0,TimerSeachCount=0;

//函数定义
static void Lierda_TaskCreateFun(void);
static void Lierda_QueueCreateFun(void);
static void Lierda_TimerCreateFun(void);
static void TitlePrint( char *name);
static uint8 lierdaATDemoCall(char* cmd, char* result, uint16 timeOut, uint16 num);
static void SysInit(void);
static void NetworkConfigInit(void);
static void DeviceInfoGet(void);
static void lierda_Device_Init(void);
void DeviceParameterConfig(void);


/******************************************************************************
* @函数名	app任务线程
* @参数	    param : 空参数，无效
* @返回值  无
******************************************************************************/
void lierda_App_task(void *param)
{
	UNUSED(param);uint8 temp=0;
	osDelay(500);//等待模组初始化完成
	Lierda_SysValue.DeviceSta=Power_ON;
	Lierda_SysValue.RegCompLedflag=0;
	TitlePrint("定位器例程");
	SysInit();//系统参数初始化
	Lierda_ServerReg();//设备注册
	TimerControlFun(TIMEDREPORT,1,1000);//打开定时发送计数器
	for (;;)
	{
		if (osMessageQueueGet(Lierda_App_queue, (void*) &temp, NULL,osWaitForever) == osOK)
			{
				switch(temp)
				{
				case Timer_data://定时器消息
					TimerControlFun(TIMEDREPORT,0,1000);//关闭定时器
					if(Lierda_SysValue.DeviceSta==Reg_Complete)
					{
						lierdaLog("定时数据上报");
						Lierda_ServerSendData();//若注册完成则上报信息
					}
					else
						{
							Lierda_ServerReg();//注册未完成，继续注册
							lierdaLog("未完成注册");
						}
					TimerControlFun(TIMEDREPORT,1,1000);//打开定时器
					break;
				case key_data://按键消息来临
					if(Lierda_SysValue.DeviceSta==Reg_Complete)
					{
						if(Lierda_SysValue.SysMode==StandardMode)
						{
								lierdaLog("按键按下定位打开");
								Gps_Open();
								TimerControlFun(TIMESEARCHGPS,1,1000);
						}
					}
					else
					{
						Lierda_ServerReg();//注册未完成，继续注册
						lierdaLog("未完成注册");
					}
					break;
				case OpenGPS://打开GPS
					lierdaLog("DBG_INFO:打开GPS");
					Gps_Open();
					break;
				case CloseGPS://关闭GPS
					lierdaLog("DBG_INFO:关闭GPS\r\n定位结果：%d",Lierda_SysValue.GpsPositSuc);
					Gps_Close();
					break;
				case Stachange_data://配置信息改变
					Lierda_ServerSendData();//配置信息改变上报信息
					break;
				default :break;
				}
			}
		osDelay(10);
	}
}




static void lierda_Device_Init(void)
{
	uint16 kvlen=0;
	if((lierdaKVGet(KVID,sizeof(struct SysKvSave),&kvlen,(uint8 *) &syskvsave)==LIERDA_RET_OK)&&(kvlen==sizeof(struct SysKvSave)))
	{
		Lierda_SysValue.SysMode=syskvsave.DeviceMode;
		Lierda_SysValue.ReportCycle=syskvsave.ReportCycle;
		Lierda_SysValue.CollCycle=syskvsave.CollCycle;
		Lierda_SysValue.MaxSearchTimer=syskvsave.MaxSearchTimer;
		Lierda_SysValue.GpsHoldTimer=syskvsave.GpsHoldTimer;
	}
	else
	{
		DeviceParameterConfig();
		DeviceParameterSave();
	}
	Deviceswitch();

}
void Deviceswitch(void)
{
	Lierda_SysValue.GpsDataNum=0;
	Lierda_SysValue.GpsDataNumFullFlag=0;
	TimerControlFun(TIMEDREPORT,1,1000);//打开定时器
	if(Lierda_SysValue.SysMode==TrackerMode)
	{
		 TimerControlFun(TIMECOOLLECGPS,1,1000);
		 Key_Close();
	}
	else
	{
		Key_Open();
		TimerControlFun(TIMECOOLLECGPS,0,1000);
	}
}
void DeviceParameterConfig(void)
{
	Lierda_SysValue.SysMode=TrackerMode;//系统默认定位模式
	Lierda_SysValue.ReportCycle=REPORTCYCLE;//默认上报周期
	Lierda_SysValue.CollCycle=COOLLCYCLE;//默认搜星周期
	Lierda_SysValue.MaxSearchTimer=MAXSEARTIME;//最大搜星时间
	Lierda_SysValue.GpsHoldTimer=SEARHOLDTIME;//搜星保持时间
}
void DeviceParameterSave(void)
{
	syskvsave.CollCycle=Lierda_SysValue.CollCycle;
	syskvsave.DeviceMode=Lierda_SysValue.SysMode;
	syskvsave.MaxSearchTimer=Lierda_SysValue.MaxSearchTimer;
	syskvsave.ReportCycle=Lierda_SysValue.ReportCycle;
	syskvsave.GpsHoldTimer=Lierda_SysValue.GpsHoldTimer;
	if(lierdaKVSet(KVID,(uint8 *)&syskvsave, sizeof(struct SysKvSave))==LIERDA_RET_OK)
		lierdaLog("DBG_INFO:DeviceConfigSave SUC");
	else
		lierdaLog("DBG_INFO:DeviceConfigSave ERROR");
}

static void SysInit(void)
{
	lierda_GPS_task_enable();
	NetworkConfigInit();//网络初始化
	DeviceInfoGet();//设备信息获取
	lierda_Device_Init();//设备初始化
}


static void DeviceInfoGet(void)
{
	char * returaddr=NULL;
	returaddr = lierdaATCall("AT+CGSN=1", 1000);  //查询IMEI
	returaddr=strstr(returaddr,"+CGSN:");
	memcpy(Lierda_SysValue.Module_IMEI,returaddr+6,15);
	lierdaLog("DBG_INFO:IMEI:%s",Lierda_SysValue.Module_IMEI);
	returaddr = lierdaATCall("AT+NCCID", 1000);  //查询ICCID
	returaddr=strstr(returaddr,"+NCCID:");
	memcpy(Lierda_SysValue.Module_ICCID,returaddr+7,20);
	lierdaLog("DBG_INFO:ICCID:%s",Lierda_SysValue.Module_ICCID);
	returaddr = lierdaATCall("AT+CIMI", 1000);  //查询IMSI
	memcpy(Lierda_SysValue.Module_IMSI,returaddr+2,15);
	lierdaLog("DBG_INFO:IMSI:%s",Lierda_SysValue.Module_IMSI);
}

static void NetworkConfigInit(void)
{
	char * returaddr=NULL;
	returaddr = lierdaATCall("AT+NCDP?", 3000);  //查询NCDP
	lierdaLog("DBG_INFO:NCDP?:%s",returaddr);
	if (strstr(returaddr, "+NCDP:117.60.157.137,5683") == NULL)
	{
		lierdaATDemoCall("AT+CFUN=0","OK",3000,5);  //关闭射频
		lierdaATDemoCall("AT+NCDP=117.60.157.137,5683","OK",3000,5);  //配置NCDP
		lierdaATDemoCall("AT+NRB","OK",7000,5);   //复位保存
	}
	Lierda_SysValue.DeviceSta=ConnectNet;
	lierdaATDemoCall("AT+CPSMS=1","OK",3000,5);//打开PSM
	lierdaATDemoCall("AT+NPSMR=1","OK",3000,5);//打开PSM模式通知
	osDelay(3000);
	lierdaATDemoCall("AT+CGATT=1","OK",2000,5);
	do
	{
		returaddr = lierdaATCall("AT+CGATT?", 1000);  //查询是否附着上网络

		if(strstr(returaddr, "+CGATT:1") == NULL)
			{
				osDelay(1000);
				lierdaLog("DBG_INFO:正在附着网络");
			}
	}while(strstr(returaddr, "+CGATT:1") == NULL);
	lierdaLog("DBG_INFO:网络附着成功");
}
/******************************************************************************
* @函数名 发送AT指令函数
* @参数	   cmd :AT指令，不用加"\r\n"
* @参数	result :预期的正确返回信息
* @参数    timeOut :延时时间,ms
* @参数             num  :重试次数
* @返回值            1:发送成功        0 ：发送失败
******************************************************************************/
 static uint8 lierdaATDemoCall(char* cmd, char* result, uint16 timeOut, uint16 num)
{
	uint16 i;char *returaddr=NULL;
	for (i = 0; i < num; i++)
	{
		returaddr = lierdaATCall(cmd, timeOut);  //发送AT指令
		lierdaLog("DBG_INFO:cmd:%s\r\nresult:%s",cmd,returaddr);
		if (strstr(returaddr, result) != NULL)
			return 1;
		else
			osDelay(1000);
	}
	return 0;  //发送失败
}
void Lierda_SoftTimerCallback(void *param)
{
	uint8 temp=0;
	if(param==(void *)TIMEDREPORT)
	{
		Retimercount++;
		if(Retimercount==(Lierda_SysValue.ReportCycle+1))
		{
			temp=Timer_data;
			Retimercount=0;
			QueueSendDataFun(&temp);
		}
	}
	else if(param==(void *)TIMECOOLLECGPS)
	{
		TimerCollCount++;
		if(TimerCollCount==Lierda_SysValue.CollCycle+1)
		{
			TimerCollCount=0;
			TimerControlFun(TIMECOOLLECGPS,0,1000);
			TimerControlFun(TIMESEARCHGPS,1,1000);
			temp=OpenGPS;
			QueueSendDataFun(&temp);
		}
	}
	else if(param==(void *)TIMESEARCHGPS)
	{
		TimerSeachCount++;
		LED10_TOGGLE;
		if(Lierda_SysValue.GpsHoldFlag==0)
		{
			if(TimerSeachCount==Lierda_SysValue.MaxSearchTimer+1)
			{
				TimerControlFun(TIMESEARCHGPS,0,1000);
				LED10_OFF;
				TimerSeachCount=0;
				temp=CloseGPS;
				QueueSendDataFun(&temp);
				Lierda_SysValue.GpsHoldFlag=0;
				if(Lierda_SysValue.GpsPositSuc==0)
				{
						Lierda_SysValue.GpsDataNum++;
					    Lierda_SysValue.gpsInfo.SerialNum=Lierda_SysValue.GpsDataNum;
						Lierda_SysValue.gpsInfo.SignalQuality=0x01;
						Lierda_SysValue.gpsInfo.longitude=0x4784c880;//0x4784c880
						Lierda_SysValue.gpsInfo.longitude=BigtoLittle32(Lierda_SysValue.gpsInfo.longitude);
						Lierda_SysValue.gpsInfo.latitude=0x120c2640;//0x120c2640
						Lierda_SysValue.gpsInfo.latitude=BigtoLittle32(Lierda_SysValue.gpsInfo.latitude);
						Lierda_SysValue.gpsInfo.Position=0x02;
						memcpy(GpsDtaBuff+((Lierda_SysValue.GpsDataNum-1)*GPSDATAPACK_LEN),&Lierda_SysValue.gpsInfo,GPSDATAPACK_LEN);
						if(Lierda_SysValue.GpsDataNum==10)
						{
							Lierda_SysValue.GpsDataNum=0;
							Lierda_SysValue.GpsDataNumFullFlag=1;
						}

				}
				if(Lierda_SysValue.SysMode!=StandardMode)
					TimerControlFun(TIMECOOLLECGPS,1,1000);
				else
					TimerControlFun(TIMECOOLLECGPS,0,1000);
			}
		}
		else
		{
			if(TimerSeachCount==Lierda_SysValue.GpsHoldTimer+1)
			{
				TimerSeachCount=0;
				LED10_OFF;
				temp=CloseGPS;
				QueueSendDataFun(&temp);
				TimerControlFun(TIMESEARCHGPS,0,1000);
				if(Lierda_SysValue.SysMode!=StandardMode)
					TimerControlFun(TIMECOOLLECGPS,1,1000);
				else
					TimerControlFun(TIMECOOLLECGPS,0,1000);
			}
		}

	}
}
/******************************************************************************
* @函数名 创建用户线程
* @参数	param : 空参数
* @返回值  无
******************************************************************************/
void lierda_App_main(void)
{
	Lierda_TaskCreateFun();//任务创建
	Lierda_QueueCreateFun();//队列创建
	Lierda_TimerCreateFun();//定时器创建
}

static void Lierda_TaskCreateFun(void)
{
	App_task_handle = osThreadNew(lierda_App_task, NULL, &App_task_attr); //创建主任务
	if (App_task_handle == NULL)
	{
		lierdaLog("	lierda_App_task 任务创建失败");
	}
	LedSta_task_handle = osThreadNew(lierda_LedSta_task, NULL, &LedSta_task_attr); //创建LED灯状态任务
	if (LedSta_task_handle == NULL)
	{
		lierdaLog("	lierda_App_task 任务创建失败");
	}

	NNMITaskHandle = osThreadNew (lierda_MMNI_task, NULL, &nnmi_task_attr);//创建下行任务接受任务
	if (NNMITaskHandle == NULL)
	{
		lierdaLog("	lierda_MMNI_task 任务创建失败");
	}

}

void QueueSendDataFun(uint8 *msg)
{
	osMessageQueuePut (Lierda_App_queue, msg, 0,0);
}

void TimerControlFun(uint8 timerid,uint8 control,uint32 timer)
{
	if(control==1)
	{
		if(timerid==TIMEDREPORT)
		{
			Retimercount=0;
			if(osTimerIsRunning(Timedreport_handle))
			{
				osTimerStop(Timedreport_handle);
			}
			osTimerStart(Timedreport_handle,timer);
		}
		else if(timerid==TIMECOOLLECGPS)
		{
			TimerCollCount=0;
			if(osTimerIsRunning(TimeCoollecGps_handle))
			{
				osTimerStop(TimeCoollecGps_handle);
			}
			osTimerStart(TimeCoollecGps_handle,timer);
		}
		else if(timerid==TIMESEARCHGPS)
		{
			TimerSeachCount=0;
			if(osTimerIsRunning(TimeSearchGps_handle))
			{
				osTimerStop(TimeSearchGps_handle);
			}
			osTimerStart(TimeSearchGps_handle,timer);
		}
	}
	else
	{
		if(timerid==TIMEDREPORT)
		{
			Retimercount=0;
			if(osTimerIsRunning(Timedreport_handle))
			{
				osTimerStop(Timedreport_handle);
			}
		}
		else if(timerid==TIMECOOLLECGPS)
		{
			TimerCollCount=0;
			if(osTimerIsRunning(TimeCoollecGps_handle))
			{
				osTimerStop(TimeCoollecGps_handle);
			}
		}
		else if(timerid==TIMESEARCHGPS)
		{
			TimerSeachCount=0;
			if(osTimerIsRunning(TimeSearchGps_handle))
			{
				osTimerStop(TimeSearchGps_handle);
			}
		}
	}
}


static void Lierda_QueueCreateFun(void)
{
	Lierda_App_queue = osMessageQueueNew(5, 1, NULL); //创建
	if (Lierda_App_queue == NULL)
	{
		lierdaLog("	Lierda_App_queue 队列创建失败");
	}

}




static void Lierda_TimerCreateFun(void)
{
	Timedreport_handle=osTimerNew (Lierda_SoftTimerCallback, osTimerPeriodic, (void *)TIMEDREPORT, NULL);
	if (Timedreport_handle == NULL)
	{
		lierdaLog("	Timedreport_handle 定时器创建失败");
	}
	TimeCoollecGps_handle=osTimerNew (Lierda_SoftTimerCallback, osTimerPeriodic, (void *)TIMECOOLLECGPS, NULL);
	if (TimeCoollecGps_handle == NULL)
	{
		lierdaLog("	TimeCoollecGps_handle 定时器创建失败");
	}
	TimeSearchGps_handle=osTimerNew (Lierda_SoftTimerCallback, osTimerPeriodic, (void *)TIMESEARCHGPS, NULL);
	if (TimeSearchGps_handle == NULL)
	{
		lierdaLog("	TimeSearchGps_handle 定时器创建失败");
	}
}
/******************************************************************************
* @函数名 系统信息打印
* @参数	 *name : 例程名
* @返回值  无
******************************************************************************/
static void TitlePrint( char *name)
{

 lierdaLog("******************************************************************************");
 lierdaLog("                       NB86 EVK开发板例程----%s                                    \r\n",name);
 lierdaLog(" 利尔达科技集团<www.lierda.com>");
 lierdaLog(" LSD Science&Technology Co.,Ltd");
 lierdaLog(" 杭州市余杭区文一西路1326号利尔达科技园");
 lierdaLog(" 物联网开发者社区<http://bbs.lierda.com>");
 lierdaLog("******************************************************************************\r\n");
}
