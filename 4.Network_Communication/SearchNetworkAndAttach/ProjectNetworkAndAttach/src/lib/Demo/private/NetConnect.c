/*
 * NetConnect.c
 *
 *  Created on: 2019年4月26日
 *      Author: Administrator
 */
#include "NetConnect.h"

/******************************************************************************
* @函数名    网络连接初始化
* @参数	     无
* @返回值     无
******************************************************************************/
void NetConnect_Init(void)
{
	NET_PARA_RET  cause;
  	struct NET_Local_Para  net_local_pa =
  	{
  	   1,
       8, //第一轮离散加网因子 (>=1)
  	   5, //第二轮离散加网因子 (>=1)
	   0,
	   0,
	   2,
       2,
	   {"180.101.147.115,5683"},
  	};
  	cause = lierda_net_local_config_init(&net_local_pa);
  	if (cause != 0)
  	{
  		lierdaLog("lierda_net_local_config_init,fail,%d\r\n",cause);
  	}
  	lierda_network_dealwith_task_enable();//网络连接使能
}
