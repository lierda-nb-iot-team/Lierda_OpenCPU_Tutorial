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



SysValue Lierda_SysValue;
osTimerId_t Timedreport_handle=NULL;
osMessageQueueId_t Lierda_App_queue=NULL;
uint32 timercount=0;

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
	TitlePrint("模拟路灯例程");
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
						Lierda_ServerSendData();//若注册完成则上报信息
					else
						Lierda_ServerReg();//注册未完成，继续注册
					TimerControlFun(TIMEDREPORT,1,1000);//打开定时器
					break;
				case key_data://按键消息来临
					if(Lierda_SysValue.DeviceSta==Reg_Complete)
						Lierda_ServerSendData();//若注册完成则上报信息
					else
						lierdaLog("未完成注册");
					break;
				case Stachange_data://灯的状态发生改变
					Lierda_ServerSendData();//上报信息
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
	lierda_OPT3001_Init();//OPT3001DN初始化
	usart_init();//GPS串口初始化
	lierda_ReadSensor();//数据获取
}

void lierda_ReadSensor(void)
{
	//GPS数据获取
	gps_updata(&Lierda_SysValue.gpsinfo.Position,&Lierda_SysValue.gpsinfo.longitude,&Lierda_SysValue.gpsinfo.latitude);
	//光照数据获取
	lierda_OPT3001_UpdataInfo(&Lierda_SysValue.Illuminance);
}


static void SysInit(void)
{
	Lierda_SysValue.AckDataNum=0;
	Lierda_SysValue.SendDataNum=0;
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
	if (strstr(returaddr, "+NCDP:180.101.147.115,5683") == NULL)
	{
		lierdaATDemoCall("AT+CFUN=0","OK",3000,5);  //关闭射频
		lierdaATDemoCall("AT+NCDP=180.101.147.115,5683","OK",3000,5);  //配置NCDP
		lierdaATDemoCall("AT+NRB","OK",7000,5);   //复位保存
	}
	Lierda_SysValue.DeviceSta=ConnectNet;
	lierdaATDemoCall("AT+CPSMS=0","OK",3000,5);
	lierdaATDemoCall("AT+CEDRXS=2,5,0101","OK",3000,5);
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
	uint8 temp=Timer_data;
	if(param==(void *)TIMEDREPORT)
	{
		timercount++;
		if(timercount==SENDCYCLE)
		{
			timercount=0;
			QueueSendDataFun(&temp);
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
