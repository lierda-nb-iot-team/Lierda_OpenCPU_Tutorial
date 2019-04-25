/******************************************************************************
 * @内容	用户任务函数
 * @设计	Lierda NB-IoT 软件设计团队@2018
******************************************************************************/
#include "app.h"

osThreadAttr_t App_task_attr = { "lierda_App_task"/*任务名称*/, 0, NULL, 0, NULL,
		(256) /*任务堆栈大小*/, 11/*任务优先级*/, 0, 0 };//任务属性结构体
uint32 * App_task_handle = NULL;

/******************************************************************************
* @函数名	app任务线程
* @参数	    param : 空参数，无效
* @返回值  无
******************************************************************************/
void lierda_App_task(void *param)
{
	UNUSED(param);int16 X=0,Y=0,Z=0;
	osDelay(500);//等待模组初始化完成
	lierdaLog("三轴传感器LIS3DH Demo");
	I2c_Init();//I2c总线初始化
	if(LIS3DH_init())  //HDC1000初始化
		lierdaLog("LIS3DH Init Success");
	else
		lierdaLog("LIS3DH Init Fail");
	for (;;)
	{
		LIS3DHUpdateInfo(&X,&Y,&Z);  //三轴数据采集
		lierdaLog("X:%d  Y:%d  Z:%d",X,Y,Z);  //三轴数据通过AT口打印
		osDelay(5000);//每5秒采集一次三轴数据
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
