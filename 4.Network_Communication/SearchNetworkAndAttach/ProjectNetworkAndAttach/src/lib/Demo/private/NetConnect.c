/*
 * NetConnect.c
 *
 *  Created on: 2019��4��26��
 *      Author: Administrator
 */
#include "NetConnect.h"

/******************************************************************************
* @������    �������ӳ�ʼ��
* @����	     ��
* @����ֵ     ��
******************************************************************************/
void NetConnect_Init(void)
{
	NET_PARA_RET  cause;
  	struct NET_Local_Para  net_local_pa =
  	{
  	   1,
       8, //��һ����ɢ�������� (>=1)
  	   5, //�ڶ�����ɢ�������� (>=1)
	   0,
	   0,
	   2,
       2,
	   {"117.60.157.137,5683"},
  	};
  	cause = lierda_net_local_config_init(&net_local_pa);
  	if (cause != 0)
  	{
  		lierdaLog("lierda_net_local_config_init,fail,%d\r\n",cause);
  	}
  	lierda_network_dealwith_task_enable();//��������ʹ��
}
