/******************************************************************************
 * @内容	按键函数
 * @设计	Lierda NB-IoT 软件设计团队@2018
******************************************************************************/
#include "key.h"


/******************************************************************************
 * @函数名	按键中断回调函数
 * @参数	    PIN 中断引脚
 * @返回值           无
 ******************************************************************************/
void sos_key_callback(PIN pin)
{
	uint8 temp=key_data;
	if (0==lierdaGPIORead(pin))
	{
		osDelay(10);  //消抖
		if (lierdaGPIORead(pin)==0)  //GPIO读取函数
		{
			while(lierdaGPIORead(pin)==0);
			QueueSendDataFun(&temp);//队列发送消息
		}
	}
}

void Key_Open(void)
{
	Lierda_KEY_Init(KEY2, GPIO_DIRECTION_INPUT); //按键初始化
}

void Key_Close(void)
{
	Lierda_KEY_Init(KEY2, GPIO_DIRECTION_INPUT); //按键初始化
	lierdaGPIORelease(KEY2);
}
/******************************************************************************
 * @函数名	GPIO声明和中断初始化
 * @参数	key_pin:初始化的GPIO引脚
 * @参数                 mode：引脚的工作模式：输出/输入
 * @返回值  无
 ******************************************************************************/
void Lierda_KEY_Init(PIN key_pin, GPIO_DIRECTION mode)
{
	lierdaGPIOInit();
	lierdaGPIOClaim(key_pin, mode);  //GPIO声明
	lierdaGPIORegisterCallback(key_pin, GPIO_INTERRUPT_LOW,sos_key_callback);//按键中断初始化
}
/******************************************************************************
 * @函数名	GPIO读取函数
 * @参数	key_pin:读取引脚
 * @返回值   1：高电平     0：低电平
 ******************************************************************************/
uint8 Lierda_KEY_Read(PIN key_pin)
{
	if (lierdaGPIORead(key_pin))
	{
		osDelay(10);  //消抖
		if (lierdaGPIORead(key_pin))  //GPIO读取函数
			return 1;
		else
			return 0;
	}
	else
		return 0;
}




