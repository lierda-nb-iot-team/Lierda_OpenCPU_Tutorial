/*
 * LierdaLowPowertest.c
 *
 *  Created on: 2019年4月23日
 *      Author: Def_Lin
 */

#include "LierdaLowPowertest.h"
#include "lierda_app_main.h"

uint8 TestKeyFlag = 2;

/******************************************************************************
 * @函数名	createMsgQueue 创建消息队列
 * @参数	无
 * @返回值  无
 ******************************************************************************/
void createMsgQueue( void )
{
	msg_QueueId = osMessageQueueNew(2, 1, NULL); //创建队列

	if (msg_QueueId == NULL)
	{
		lierdaLog("create msg_QueueId failed.");
	}
}

/******************************************************************************
 * @函数名	TestKeyCallback 按键中断回调函数
 * @参数	PIN 中断引脚
 * @返回值  无
 ******************************************************************************/
static void TestKeyCallback(PIN pin)
{
	if (0==lierdaGPIORead(pin))
	{
		osDelay(10);  //消抖
		if (lierdaGPIORead(pin)==0)  //GPIO读取函数
		{
			while(lierdaGPIORead(pin)==0);

			osMessageQueuePut(msg_QueueId, &TestKeyFlag, 0,osNoWait);//队列发送消息
		}
	}
}


/******************************************************************************
 * @函数名	TestKeyInit 初始化测试按键
 * @参数	PIN 中断引脚,GPIO_DIRECTION 引脚模式
 * @返回值  无
 ******************************************************************************/
void TestKeyInit(PIN key_pin, GPIO_DIRECTION mode)
{
	lierdaGPIOClaim(key_pin, mode);  //GPIO声明

	lierdaGPIORegisterCallback(key_pin, GPIO_INTERRUPT_LOW,TestKeyCallback);//设置低电平触发按键中断
}



