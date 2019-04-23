/******************************************************************************
 * @内容	用户任务函数
 * @设计	Lierda NB-IoT 软件设计团队@2018
******************************************************************************/
#include "app.h"

osThreadAttr_t App_task_attr = { "lierda_App_task"/*任务名称*/, 0, NULL, 0, NULL,
		(256) /*任务堆栈大小*/, 11/*任务优先级*/, 0, 0 };//任务属性结构体
uint32 * App_task_handle = NULL;
osTimerId_t LierdaTimer_handle=NULL;


/******************************************************************************
* @函数名	app任务线程
* @参数	    param : 空参数，无效
* @返回值  无
******************************************************************************/
void lierda_App_task(void *param)
{
	UNUSED(param);uint8 count=0;
	osDelay(500);//等待模组初始化完成
	lierdaLog("LED Demo");
	Lierda_Led_Init();
	LEDx_StateSet(LED10|LED11|LED12,LED_OFF);
	osTimerStart(LierdaTimer_handle,700);//启动一个700ms定时器
	for (;;)
	{
		switch (count)
		{
		case 0:
			LED10_ON;
			LED12_OFF;
			break;
		case 1:
			LED10_OFF;
			LED11_ON;
			break;
		case 2:
			LED11_OFF;
			LED12_ON;
			break;
		}
		count++;
		if (count == 3)
			count = 0;
		osThreadSuspend(App_task_handle); //挂起任务
	}
}
void Lierda_SoftTimerCallback(void *param)
{
	UNUSED(param);
	osThreadResume(App_task_handle); //700ms到了恢复任务
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
	LierdaTimer_handle=osTimerNew (Lierda_SoftTimerCallback, osTimerPeriodic, NULL, NULL);
	if (LierdaTimer_handle == NULL)
	{
		lierdaLog("	LierdaTimer_handle定时器创建失败");
	}
}
