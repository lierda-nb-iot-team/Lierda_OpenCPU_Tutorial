/******************************************************************************
 * @内容	用户任务函数
 * @设计	Lierda NB-IoT 软件设计团队@2018
******************************************************************************/
#include "app.h"

//全局变量
osThreadAttr_t App_task_attr = { "lierda_App_task"/*任务名称*/, 0, NULL, 0, NULL,
		(400) /*任务堆栈大小*/, 11/*任务优先级*/, 0, 0 };//任务属性结构体
uint32 * App_task_handle = NULL;

osThreadAttr_t LedSta_task_attr = { "lierda_LedSta_task"/*任务名称*/, 0, NULL, 0, NULL,
		(256) /*任务堆栈大小*/, 10/*任务优先级*/, 0, 0 };//任务属性结构体
uint32 * LedSta_task_handle = NULL;

osThreadAttr_t nnmi_task_attr = { "lierda_NNMI_task"/*任务名称*/, 0, NULL, 0, NULL,
		(256) /*任务堆栈大小*/, 11/*任务优先级*/, 0, 0 };//任务属性结构体
uint32 * NNMITaskHandle = NULL;

kvTempHumi LierdatempHumiKv;
SysValue Lierda_SysValue;
osTimerId_t Timedreport_handle=NULL;
osTimerId_t TimedTempwarning_handle=NULL;
osTimerId_t TimedHumiwarning_handle=NULL;
osMessageQueueId_t Lierda_App_queue=NULL;
uint32 timercount=0,TempWarntimercount=0,HumiWarntimercount=0;

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
static void DeviceParameterConfig(void);
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
	TitlePrint("温湿度采集器例程");
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
						Lierda_ServerReg();//注册未完成，继续注册
					TimerControlFun(TIMEDREPORT,1,1000);//打开定时器
					break;
				case key_data://按键消息来临
					if(Lierda_SysValue.DeviceSta==Reg_Complete)
					{
						lierdaLog("按键按下数据上报");
						Lierda_ServerSendData();//若注册完成则上报信息
					}
					else
						lierdaLog("未完成注册");
					break;
				case Stachange_data://配置信息改变
					lierdaLog("DBG_INFO:配置信息改变数据上报");
					Lierda_ServerSendData();//上报信息
					break;
				case TempWarning_data://有报警
					 if(Lierda_SysValue.tempwarningflag==1)
					{
						lierdaLog("DBG_INFO:温度报警数据上报");
						Lierda_ServerSendData();//上报信息
					}
					 else
						 lierdaLog("DBG_INFO:温度报警取消");
					break;
				case HumiWarning_data://有报警
					 if(Lierda_SysValue.humiwarningfalg==1)
					{
						lierdaLog("DBG_INFO:湿度报警数据上报");
						Lierda_ServerSendData();//上报信息
					}
					 else
						 lierdaLog("DBG_INFO:湿度报警取消");
					break;
				default :break;
				}
			}
		osDelay(10);
	}
}


static void lierda_Device_Init(void)
{
	Lierda_KEY_Init(KEY2, GPIO_DIRECTION_INPUT); //按键初始化
	lierda_sensor_I2C_init(PIN_14,PIN_15);//I2C初始化
	lierda_HDC1000_Init();//温湿度传感器初始化
	lierda_ReadSensor();//数据获取
}

void lierda_ReadSensor(void)
{
	int16 temper=0,humidity=0;uint8 warningtemp=0;
	lierda_HDC1000_UpdateInfo(&temper,&humidity);
	Lierda_SysValue.Temperature=temper/10+Lierda_SysValue.TempCorrect;
	Lierda_SysValue.humidity=humidity;
	if(Lierda_SysValue.Temperature>Lierda_SysValue.HightTempThreshold)
	{
		//高温报警
		warningtemp=warningtemp|HIGHTTEMPW;
		Lierda_SysValue.tempwarningflag=1;
		if(Lierda_SysValue.oldtempwarning!=(warningtemp&0x03))
		{

			TimerControlFun(TIMETEMPDWARNING,1,1000);
			lierdaLog("DBG_INFO:高温报警");
		}
	}
	if(Lierda_SysValue.Temperature<Lierda_SysValue.LowTempThreshold)
	{
		//低温报警
		warningtemp=warningtemp|LOWTEMPW;
		Lierda_SysValue.tempwarningflag=1;
		if(Lierda_SysValue.oldtempwarning!=(warningtemp&0x03))
		{
			TimerControlFun(TIMETEMPDWARNING,1,1000);
			lierdaLog("DBG_INFO:低温报警");
		}
	}
	if(Lierda_SysValue.humidity>Lierda_SysValue.HightHumiThreshold)
	{
		//高湿报警
		warningtemp=warningtemp|HIGHTHUMIW;
		Lierda_SysValue.humiwarningfalg=1;
		if(Lierda_SysValue.oldhumiwarning!=(warningtemp&0x0c))
		{
			TimerControlFun(TIMEHUMIDWARNING,1,1000);
			lierdaLog("DBG_INFO:高湿报警");
		}
	}
	if(Lierda_SysValue.humidity<Lierda_SysValue.LowHumiThreshold)
	{
		//低湿报警
		warningtemp=warningtemp|LOWHUMIW;
		Lierda_SysValue.humiwarningfalg=1;
		if(Lierda_SysValue.oldhumiwarning!=(warningtemp&0x0c))
		{
			TimerControlFun(TIMEHUMIDWARNING,1,1000);
			lierdaLog("DBG_INFO:低湿报警");
		}
	}
	Lierda_SysValue.warning=warningtemp;
	if((warningtemp&0x03)==0)
	{
		Lierda_SysValue.tempwarningflag=0;
	}
	if((warningtemp&0x0c)==0)
	{
		Lierda_SysValue.humiwarningfalg=0;
	}
	Lierda_SysValue.oldhumiwarning=(warningtemp&0x0c);
	Lierda_SysValue.oldtempwarning=(warningtemp&0x03);
	//lierdaLog("DBG_INFO:Temperature=%d	humidity=%d",Lierda_SysValue.Temperature,Lierda_SysValue.humidity);
}


static void SysInit(void)
{
	Lierda_SysValue.AckDataNum=0;
	Lierda_SysValue.SendDataNum=0;
	DeviceParameterConfig();//设备参数配置
	NetworkConfigInit();//网络初始化
	DeviceInfoGet();//设备信息获取
	lierda_Device_Init();//设备初始化
}


static void DeviceParameterConfig(void)
{
	uint16 KvLen=0;
	if((lierdaKVGet(KVID, sizeof(kvTempHumi),&KvLen,(uint8 *)&LierdatempHumiKv)==LIERDA_RET_OK)&&(KvLen==sizeof(kvTempHumi)))
	{
		Lierda_SysValue.ReportCycle=LierdatempHumiKv.ReportCycle;
		Lierda_SysValue.HightTempThreshold=LierdatempHumiKv.HightTempThreshold;
		Lierda_SysValue.LowTempThreshold=LierdatempHumiKv.LowTempThreshold;
		Lierda_SysValue.TempDelayWarn=LierdatempHumiKv.TempDelayWarn;
		Lierda_SysValue.TempCorrect=LierdatempHumiKv.TempCorrect;
		Lierda_SysValue.HightHumiThreshold=LierdatempHumiKv.HightHumiThreshold;
		Lierda_SysValue.LowHumiThreshold=LierdatempHumiKv.LowHumiThreshold;
		Lierda_SysValue.HumiDelayWarn=LierdatempHumiKv.HumiDelayWarn;
		Lierda_SysValue.BatteryThreshold=LierdatempHumiKv.BatteryThreshold;
	}
	else
	{
		Lierda_SysValue.ReportCycle=REPORTCYCLE;
		Lierda_SysValue.HightTempThreshold=HIGHTTEMPTHRE*10;
		Lierda_SysValue.LowTempThreshold=LOWTTEMPTHRE*10;
		Lierda_SysValue.TempDelayWarn=TEMPDELYWARN;
		Lierda_SysValue.TempCorrect=TEMPCORRECT;
		Lierda_SysValue.HightHumiThreshold=HIGHTHUMITHRE;
		Lierda_SysValue.LowHumiThreshold=LOWTHUMITHRE;
		Lierda_SysValue.HumiDelayWarn=HUMIDELYWARN;
		Lierda_SysValue.BatteryThreshold=BATTERYTHRES;
		DeviceParametersave();
	}

}

void DeviceParametersave(void)
{
	LierdatempHumiKv.ReportCycle=Lierda_SysValue.ReportCycle;
	LierdatempHumiKv.HightTempThreshold=Lierda_SysValue.HightTempThreshold;
	LierdatempHumiKv.LowTempThreshold=Lierda_SysValue.LowTempThreshold;
	LierdatempHumiKv.TempDelayWarn=Lierda_SysValue.TempDelayWarn;
	LierdatempHumiKv.TempCorrect=Lierda_SysValue.TempCorrect;
	LierdatempHumiKv.HightHumiThreshold=Lierda_SysValue.HightHumiThreshold;
	LierdatempHumiKv.LowHumiThreshold=Lierda_SysValue.LowHumiThreshold;
	LierdatempHumiKv.HumiDelayWarn=Lierda_SysValue.HumiDelayWarn;
	LierdatempHumiKv.BatteryThreshold=Lierda_SysValue.BatteryThreshold;
	if(lierdaKVSet(KVID, (uint8 *)&LierdatempHumiKv, sizeof(kvTempHumi))==LIERDA_RET_OK)
		lierdaLog("DBG_INFO:DeviceParametersave OK");
	else
		lierdaLog("DBG_INFO:DeviceParametersave error");
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
		timercount++;
		if(timercount==(Lierda_SysValue.ReportCycle+1))
		{
			temp=Timer_data;
			timercount=0;
			QueueSendDataFun(&temp);
		}
	}
	if(param==(void *)TIMETEMPDWARNING)
	{
		TempWarntimercount++;
		if(TempWarntimercount==((Lierda_SysValue.TempDelayWarn*60)+1))
		{
			 temp=TempWarning_data;
			 TempWarntimercount=0;
			 QueueSendDataFun(&temp);
			TimerControlFun(TIMETEMPDWARNING,0,1000);
		}
	}
	if(param==(void *)TIMEHUMIDWARNING)
	{
		HumiWarntimercount++;
		if(HumiWarntimercount==((Lierda_SysValue.HumiDelayWarn*60)+1))
		{
			 temp=HumiWarning_data;
			 HumiWarntimercount=0;
			 QueueSendDataFun(&temp);
			TimerControlFun(TIMEHUMIDWARNING,0,1000);
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
			if(osTimerIsRunning(Timedreport_handle))
			{
				osTimerStop(Timedreport_handle);
			}
			osTimerStart(Timedreport_handle,timer);
		}
		else if(timerid==TIMETEMPDWARNING)
		{
			if(osTimerIsRunning(TimedTempwarning_handle))
			{
				osTimerStop(TimedTempwarning_handle);
			}
			osTimerStart(TimedTempwarning_handle,timer);
		}
		else if(timerid==TIMEHUMIDWARNING)
		{
			if(osTimerIsRunning(TimedHumiwarning_handle))
			{
				osTimerStop(TimedHumiwarning_handle);
			}
			osTimerStart(TimedHumiwarning_handle,timer);
		}
	}
	else
	{
		if(timerid==TIMEDREPORT)
		{
			if(osTimerIsRunning(Timedreport_handle))
			{
				osTimerStop(Timedreport_handle);
			}
		}
		else if(timerid==TIMETEMPDWARNING)
		{
			if(osTimerIsRunning(TimedTempwarning_handle))
			{
				osTimerStop(TimedTempwarning_handle);
			}
		}
		else if(timerid==TIMEHUMIDWARNING)
		{
			if(osTimerIsRunning(TimedHumiwarning_handle))
			{
				osTimerStop(TimedHumiwarning_handle);
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
	TimedTempwarning_handle=osTimerNew (Lierda_SoftTimerCallback, osTimerPeriodic, (void *)TIMETEMPDWARNING, NULL);
	if (TimedTempwarning_handle == NULL)
	{
		lierdaLog("	TimedTempwarning_handle 定时器创建失败");
	}
	TimedHumiwarning_handle=osTimerNew (Lierda_SoftTimerCallback, osTimerPeriodic, (void *)TIMEHUMIDWARNING, NULL);
	if (TimedHumiwarning_handle == NULL)
	{
		lierdaLog("	TimedHumiwarning_handle 定时器创建失败");
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
