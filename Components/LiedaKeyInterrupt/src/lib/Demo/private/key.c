/******************************************************************************
 * @内容	按键函数
 * @设计	Lierda NB-IoT 软件设计团队@2018
******************************************************************************/
#include "key.h"


static void sos_key_callback(PIN pin);
/******************************************************************************
 * @函数名	按键中断回调函数
 * @参数	    PIN 中断引脚
 * @返回值           无
 ******************************************************************************/
static void sos_key_callback(PIN pin)
{
	if (0==Lierda_KEY_Read(pin))
	{
		while (lierdaGPIORead(pin) == 0) ;//等待按键松开
		LEDx_StateSet(LED10 | LED11 | LED12, LED_TOGGLE); //按键中断来临LED10,LED11,LED12状态改变
	}
}
/******************************************************************************
 * @函数名	key GPIO声明和中断初始化
 * @参数     无
 * @返回值  无
 ******************************************************************************/
void Lierda_KEY_Init(void)
{
	lierdaGPIOClaim(KEY2, GPIO_DIRECTION_INPUT);  //GPIO声明为输入模式
	lierdaGPIORegisterCallback(KEY2, GPIO_INTERRUPT_LOW,sos_key_callback);//按键中断配置：低电平触发中断
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




