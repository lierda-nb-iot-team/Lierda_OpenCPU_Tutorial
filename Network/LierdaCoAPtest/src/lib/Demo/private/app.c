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
	UNUSED(param);
	uint8 i = 0;

	osDelay(5000);

	sendCoAPdata();//发送测试数据

	lierdaNNMIDataInit();//NNMI下行数据接收初始化

	for(;;)
	{
		lierdaNNMIDataReceived(nnmi_buff, &nnmi_buff_len, 0xFFFFFFFF); //NNMI下行数据接收

		if (nnmi_buff_len > 0)
		{
			lierdaLog("下行数据 :");

			for (i = 0; i < nnmi_buff_len; i++)
			{
				lierdaLog("%x", nnmi_buff[i]);
			}

			memset(nnmi_buff, 0, nnmi_buff_len);

			nnmi_buff_len = 0;
		}
		osDelay(2000);
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
