/******************************************************************************
 * @内容	用户任务函数
 * @设计	Lierda NB-IoT 软件设计团队@2018
******************************************************************************/
#include "app.h"

osThreadAttr_t App_task_attr = { "lierda_App_task"/*任务名称*/, 0, NULL, 0, NULL,
		(256) /*任务堆栈大小*/, 11/*任务优先级*/, 0, 0 };//任务属性结构体
uint32 * App_task_handle = NULL;

osThreadAttr_t Key_task_attr = { "lierda_Key_task"/*任务名称*/, 0, NULL, 0, NULL,
		(256) /*任务堆栈大小*/, 11/*任务优先级*/, 0, 0 };//任务属性结构体
uint32 * Key_task_handle = NULL;
osThreadAttr_t NNMI_task_attr = { "lierda_NNMI_task"/*任务名称*/, 0, NULL, 0, NULL,
		(128) /*任务堆栈大小*/, 12/*任务优先级*/, 0, 0 };//任务属性结构体
uint32 * NNMI_task_handle = NULL;
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
	TitlePrint("网络连接例程");
	NetConnect_Init();//网络连接初始化
	for (;;)
	{
		lierda_module_status_read();//更新事件状态
		if(strstr(module_status.charCEREG,"+CEREG:1"))//查看网络连接是否正常
		{
			if(strstr(module_status.charNMSTATUS,"MO_DATA_ENABLED"))
			{
				lierdaLog("IoT平台连接成功");
				if(lierda_FotaEnableData()==LierdaFota_DataEnable)
				{
					lierdaLog("无FOTA事件发生，可以发数据");
					lierdaSendMsgToPlatform((uint8 *)"123456789", 9,MSG_NON_NORAI, 0,1);//向IoT平台发数据
				}
				else
					lierdaLog("FOTA中，不可以发数据");
			}
			else
				lierdaLog("IoT平台连接失败，请检查设备是否注册");
		}
		else
			lierdaLog("网络断开，请检查设备网络");
		osDelay(5000);//5秒更新一次事件状态
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
