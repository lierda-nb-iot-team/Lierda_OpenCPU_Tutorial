/******************************************************************************
 * @内容	用户任务函数
 * @设计	Lierda NB-IoT 软件设计团队@2018
******************************************************************************/
#include "app.h"

osThreadAttr_t App_task_attr = { "lierda_App_task"/*任务名称*/, 0, NULL, 0, NULL,
		(256) /*任务堆栈大小*/, 11/*任务优先级*/, 0, 0 };//任务属性结构体
uint32 * App_task_handle = NULL;
osThreadAttr_t Gps_task_attr = { "lierda_Gps_task"/*任务名称*/, 0, NULL, 0, NULL,
		(256) /*任务堆栈大小*/, 11/*任务优先级*/, 0, 0 };//任务属性结构体
uint32 * Gps_task_handle = NULL;
osTimerId_t LierdaTimer_handle=NULL;

static void TitlePrint( char *name);
/******************************************************************************
* @函数名	app任务线程
* @参数	    param : 空参数，无效
* @返回值  无
******************************************************************************/
void lierda_App_task(void *param)
{
	UNUSED(param);
	osDelay(500);//等待模组初始化完成
	char *pRMC=NULL;
	TitlePrint("GPS例程");
	for (;;)
	{
		if(DataEnd==1)//GPS数据接收完成
		{
			DataEnd=0;//清除接收完成标志位
	    	pRMC = strstr((const char *) GpsDataBuff, "$GNRMC");//判断数据是否为有效数据
	    	if ((pRMC)&&(GpsDataLen > 8))
	    	{
	    		memset(&Gps_Data, 0, sizeof(GPSRMCStruct));
	    		iRMC_decode((char *)(pRMC), 100);//GPS数据解析
	    		if(Gps_Data.Valid_status=='A')//判断是否为有效数据
	    		{
	    			lierdaLog("时间：%s %s(ddmmyy hhmmss.sss)\r\n东西：%c\r\n维度：%s\r\n经度：%s\r\n南北：%c",Gps_Data.Date,Gps_Data.UTC_Time,Gps_Data.EW_indicator,Gps_Data.Latitude,Gps_Data.Longitude,Gps_Data.NS_indicator);
	    		}
	    		else
	    			lierdaLog("GPS未定位成功");
	    	}
	    	else
	    	{
	    		lierdaLog("GPS未定位成功");
	    	}
			osDelay(10);
			Gps_data_clear();//清空GPS报文数据
		}
		osDelay(10);
	}
}
void Lierda_SoftTimerCallback(void *param)
{
	UNUSED(param);
	if(DataStart==1)
	{
		if(Timercount==10)
		{
			Timercount=0;
			DataStart=0;
			DataEnd=1;
		}
		Timercount++;
	}
}
/******************************************************************************
* @函数名 创建用户线程
* @参数	param : 空参数
* @返回值  无
******************************************************************************/
void lierda_App_main(void)
{
	App_task_handle = osThreadNew(lierda_App_task, NULL, &App_task_attr); //创建测试任务
	if (App_task_handle == NULL)
	{
		lierdaLog("	lierda_App_task任务创建失败");
	}
	Gps_task_handle = osThreadNew(lierda_Gps_task, NULL, &Gps_task_attr); //创建测试任务
	if (Gps_task_handle == NULL)
	{
		lierdaLog("	lierda_Gps_task任务创建失败");
	}
	LierdaTimer_handle=osTimerNew (Lierda_SoftTimerCallback, osTimerPeriodic, NULL, NULL);
	if (LierdaTimer_handle == NULL)
	{
		lierdaLog("	LierdaTimer_handle定时器创建失败");
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
