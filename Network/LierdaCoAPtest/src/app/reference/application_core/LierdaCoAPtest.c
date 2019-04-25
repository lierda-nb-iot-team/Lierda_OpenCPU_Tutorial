/*
 * LierdaCoAPtest.c
 *
 *  Created on: 2019年4月23日
 *      Author: Def_Lin
 */
#include "lierda_app_main.h"
#include "LierdaCoAPtest.h"
#include "lierda_module_status.h"
#include "lierdaNNMIData.h"
#include "stdio.h"

osThreadAttr_t test_task_attr = { "lierda_test_task"/*任务名称*/, 0, NULL, 0, NULL,
		(512) /*任务堆栈大小*/, 11/*任务优先级*/, 0, 0 };//任务属性结构体
uint32 * test_task_handle = NULL;

char *at_cgpaddr_ret = NULL;
uint8 nnmi_buff[128];//测试buff
uint16 nnmi_buff_len;//下行数据接收长度

void TitlePrint( void );


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
	uint8 count = 0;

	for( count = 0;count < 7;count ++ )
	{
		lierda_module_status_read();//获取当前与平台的注册状态

		if(strstr(module_status.charNMSTATUS,"MO_DATA_ENABLED") != NULL)//若与平台已经注册成功则发送数据
		{
			lierdaLog("Current network status is %s",module_status.charNMSTATUS);

			lierdaATCalldemo("AT+NMGS=10,A9A1A2A3A4A5A6A7A8A9", "OK",3000, 5);

			break;
		}
		else
		{
			lierdaLog("Current network status is %s",module_status.charNMSTATUS);

			osDelay(3000);
		}

	}

	if( count >= 7 )
	{

		lierdaLog("The network is poor!");

	}


}

void TitlePrint( void )
{

	lierdaLog("******************************************************************************");
	lierdaLog("                       NB86 EVK开发板例程----CoAP数据收发                                                                                \r\n");
	lierdaLog(" 利尔达科技集团<www.lierda.com>");
	lierdaLog(" LSD Science&Technology Co.,Ltd");
	lierdaLog(" 杭州市余杭区文一西路1326号利尔达科技园");
	lierdaLog(" 物联网开发者社区<http://bbs.lierda.com>");
	lierdaLog("******************************************************************************\r\n");

}


static void lierda_test_task(void *param)
{
	UNUSED(param);
	uint8 i = 0;

	osDelay(500);

	TitlePrint();

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

void lierda_test_main(void)
{
	test_task_handle = osThreadNew(lierda_test_task, NULL, &test_task_attr); //创建测试任务

	if (test_task_handle == NULL)
	{
		lierdaLog("lierda_test_task任务创建失败");
	}
}
