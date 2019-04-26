/*
 * LierdaUDPtest.c
 *
 *  Created on: 2019年4月23日
 *      Author: Def_Lin
 */

#include "LierdaUDPtest.h"
#include "lierda_app_main.h"


void lierdaUDPsend(void)
{
	char * ret = NULL;
	char tcp_UDPcmd_buff[100] = {0};
	uint8 count = 0;

	ret = lierdaATCall("AT+NSOCR=DGRAM,17,6555,1", 3000);  //创建UDP socket

	socketID = ret[2];


	if(strstr(ret,"OK"))
	{
		memcpy(tcp_UDPcmd_buff, "AT+NSOST=", 9);

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


