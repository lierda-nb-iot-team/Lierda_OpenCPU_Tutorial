/*
 * LierdaCoAPtest.c
 *
 *  Created on: 2019年4月23日
 *      Author: Def_Lin
 */
#include "lierda_app_main.h"
#include "LierdaCoAPtest.h"
#include "lierda_module_status.h"

osThreadAttr_t test_task_attr = { "lierda_test_task"/*任务名称*/, 0, NULL, 0, NULL,
		(512) /*任务堆栈大小*/, 11/*任务优先级*/, 0, 0 };//任务属性结构体
uint32 * test_task_handle = NULL;

char *at_cgpaddr_ret = NULL;

static uint8 lierdaATCalldemo(char* cmd, char* result, uint16 timeOut, uint16 num)
{
	uint16 i;

	for (i = 0; i < num; i++)
	{
		at_cgpaddr_ret = lierdaATCall(cmd, timeOut);  //发送AT指令

		lierdaLog("DBG_INFO:cmd:%s\r\nresult:%s",cmd,at_cgpaddr_ret);

		if (strstr(at_cgpaddr_ret, result) != NULL)
		{
			return 1;
		}
		else
		{
			osDelay(1000);
		}
	}

	return 0;  //发送失败重启
}

static void sendCoAPdata(void)
{
	lierda_module_status_read();

    if(strstr(module_status.charNMSTATUS,"MO_DATA_ENABLED") != NULL)
    {

    	lierdaATCalldemo("AT+NMGS=10,A9A1A2A3A4A5A6A7A8A9", "OK",3000, 5);

    }


}



static void lierda_test_task(void *param)
{
	UNUSED(param);

	for(;;)
	{
		sendCoAPdata();

		osDelay(3000);

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
