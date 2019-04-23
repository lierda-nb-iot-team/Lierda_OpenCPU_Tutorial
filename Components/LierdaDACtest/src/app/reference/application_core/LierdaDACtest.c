/*
 * LierdaDACtest.c
 *
 *  Created on: 2019年4月23日
 *      Author: Def_Lin
 */
#include "LierdaDACtest.h"
#include "lierda_app_main.h"

osThreadAttr_t test_task_attr = { "lierda_test_task"/*任务名称*/, 0, NULL, 0, NULL,
		(512) /*任务堆栈大小*/, 11/*任务优先级*/, 0, 0 };//任务属性结构体
uint32 * test_task_handle = NULL;

static void Lierda_DAC_Init(void)
{
	lierdaDACInit(); //DAC初始化

	lierdaDACSetRange(3);//设置DAC输出电压范围

	lierdaDACConnect(LIERDA_AIO1);//用于建立DAC连接AIO引脚
}

static void lierda_test_task(void *param)
{
	UNUSED(param);

	Lierda_DAC_Init();

	osDelay(3000);

	for(;;)
	{
		if(LIERDA_DAC_OK==lierdaDACWriteRaw(1023))//输出电压到AIO引脚
		{
			lierdaLog("DBG_INFO:AIO电压输出成功");

			return ;
		}
		else
		{
			lierdaLog("DBG_INFO:AIO电压输出失败");

			return ;
		}

	}

}

void lierda_test_main(void)
{
	test_task_handle = osThreadNew(lierda_test_task, NULL, &test_task_attr); //创建测试任务

	if (test_task_handle == NULL)
	{
		lierdaLog("lierda_test_task任务创建失败");
	}
}
