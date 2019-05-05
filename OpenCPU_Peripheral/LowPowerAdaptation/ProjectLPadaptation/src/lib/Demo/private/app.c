/******************************************************************************
 * @内容	用户任务函数
 * @设计	Lierda NB-IoT 软件设计团队@2018
******************************************************************************/
#include "app.h"


osThreadAttr_t App_task_attr = { "lierda_App_task"/*任务名称*/, 0, NULL, 0, NULL,
		(256) /*任务堆栈大小*/, 11/*任务优先级*/, 0, 0 };//任务属性结构体
uint32 * App_task_handle = NULL;

extern uint8 TestKeyFlag;

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



/******************************************************************************
* @函数名	app任务线程
* @参数	    param : 空参数，无效
* @返回值  无
******************************************************************************/
void lierda_App_task(void *param)
{
	UNUSED(param);

	uint8 temp = 0;
	int16 LIS3DH_X = 0,LIS3DH_Y = 0,LIS3DH_Z = 0;

	osDelay(500);

	TitlePrint("低功耗测试");

	createMsgQueue();

	lierdaLog("waiting init complete.");

	osDelay(3000);

	TestKeyInit(PIN_12,GPIO_DIRECTION_INPUT);

	I2c_Init();

	LIS3DH_init();

	lierdaLog("press k2 button to get LIS3DH data.");

	for (;;)
	{
		if (osMessageQueueGet(msg_QueueId, &temp, NULL, 0xffffffff) == osOK)//等待消息队列，任务处于阻塞状态时进入低功耗模式
		{
			if(temp == TestKeyFlag)
			{

				LIS3DHUpdateInfo(&LIS3DH_X, &LIS3DH_Y, &LIS3DH_Z);  //三轴数据获取

				lierdaLog("X轴:%d,Y轴:%d,Z轴:%d", LIS3DH_X, LIS3DH_Y, LIS3DH_Z);  //三轴数据打印

			}

		}
		osDelay(500);
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
