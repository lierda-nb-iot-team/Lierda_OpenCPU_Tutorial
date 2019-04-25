/*
 * LierdaUDPtest.c
 *
 *  Created on: 2019年4月23日
 *      Author: Def_Lin
 */

#include "LierdaUDPtest.h"
#include "lierda_app_main.h"
#include "lierdaNNMIData.h"
#include "lierda_module_status.h"

osThreadAttr_t test_task_attr = { "lierda_test_task"/*任务名称*/, 0, NULL, 0, NULL,
		(512) /*任务堆栈大小*/, 11/*任务优先级*/, 0, 0 };//任务属性结构体
uint32 * test_task_handle = NULL;

#define UDP_DATASEND  "AT+NSOST="

char udpcmd_buff[20]="AT+NSORF=";//AT指令读取数据
uint8 socketID;


static void lierdaUDPsend(void)
{
	char * ret = NULL;
	char tcp_UDPcmd_buff[100] = {0};
	uint8 count = 0;

	ret = lierdaATCall("AT+NSOCR=DGRAM,17,6555,1", 3000);  //创建UDP socket

	socketID = ret[2];


	if(strstr(ret,"OK"))
	{
		memcpy(tcp_UDPcmd_buff, UDP_DATASEND, 9);

		tcp_UDPcmd_buff[9] = socketID;

		memcpy(tcp_UDPcmd_buff + 10,",54.222.172.6,7500,18,0F3836353335323033303436383132371151",58);

		for (count = 0; count < 7; count++)
		{
			lierda_module_status_read();  //获取当前与平台的注册状态

			lierdaLog("Current network status is %s",module_status.charCGATT);

			if (strstr(module_status.charCGATT, "CGATT:1") != NULL) //若与平台已经注册成功则发送数据
			{
				lierdaLog("Current network status is %s",module_status.charCGATT);

				ret = lierdaATCall(tcp_UDPcmd_buff, 3000);  //UDP 发送数据

				lierdaLog("DBG_INFO:cmd:%s\r\n result:%s", tcp_UDPcmd_buff, ret);

				break;
			}
			else
			{
				lierdaLog("Current network status is %s",module_status.charCGATT);

				osDelay(3000);
			}

		}

		if (count >= 7) {

			lierdaLog("The network is poor!");

		}

	}
}

static void lierda_test_task(void *param)
{
	UNUSED(param);

	char *udpData_addr=NULL;

	osDelay(3000);

	lierdaUDPsend();

	for(;;)
	{
		lierdaSocketAcquireSemaphore();

		lierdaLog("DBG_INFO:收到TCP/UDP数据");

		udpcmd_buff[9] = socketID;

		memcpy(udpcmd_buff + 10, ",512", 4);

		lierdaLog("DBG_INFO:cmd:%s", udpcmd_buff);

		udpData_addr = lierdaATCall(udpcmd_buff, 3000);  //读取数据

		lierdaLog("DBG_INFO:result:%s", udpData_addr);  //打印UDP/TCP下行的数据

		osDelay(1);

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
