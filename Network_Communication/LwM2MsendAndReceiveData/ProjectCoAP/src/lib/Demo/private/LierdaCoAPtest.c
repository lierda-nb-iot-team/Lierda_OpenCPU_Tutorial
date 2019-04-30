/*
 * LierdaCoAPtest.c
 *
 *  Created on: 2019年4月23日
 *      Author: Def_Lin
 */
#include "lierda_app_main.h"
#include "LierdaCoAPtest.h"
#include "lierda_module_status.h"
#include "stdio.h"

/******************************************************************************
 * @函数名	lierdaATCalldemo
 * @描述    调用虚拟AT接口发送AT指令
 * @参数    无
 * @返回值  无
 ******************************************************************************/
static uint8 lierdaATCalldemo(char* cmd, char* result, uint16 timeOut, uint16 num)
{
	uint16 i;
	char *at_cgpaddr_ret = NULL;

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

	return 0;
}

/******************************************************************************
 * @函数名	sendCoAPdata
 * @描述    发送CoAP数据
 * @参数    无
 * @返回值  无
 ******************************************************************************/
void sendCoAPdata(void)
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

