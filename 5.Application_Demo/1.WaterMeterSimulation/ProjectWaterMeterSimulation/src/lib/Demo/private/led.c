/******************************************************************************
 * @内容	LED相关函数
 * @设计	Lierda NB-IoT 软件设计团队@2018
******************************************************************************/
#include "led.h"

static void PowerOnSta(void);
static void NetConnectSta(void);
static void DeviceRegSta(void);
static void RegCompleteSta(void);
/******************************************************************************
* @函数名	LED初始化
* @参数	        无
* @返回值       无
******************************************************************************/
void Lierda_Led_Init(void)
{
	lierdaGPIOInit();
	lierdaGPIOClaim(LED_10,GPIO_DIRECTION_OUTPUT);  //LED_10 GPIO声明
	lierdaGPIOClaim(LED_11,GPIO_DIRECTION_OUTPUT);  //LED_11 GPIO声明
	lierdaGPIOClaim(LED_12,GPIO_DIRECTION_OUTPUT);  //LED_12 GPIO声明
}
uint8 GetLEDState(PIN led_pin)
{
	bool PinState;
	uint8 ledState;

	PinState = lierdaGPIORead(led_pin);
	if(PinState)
		ledState = 0;	//关
	else
		ledState = 1;	//开

	return ledState;
}
void SendDataled(void)
{
	LED11_ON;
	osDelay(300);
	LED11_OFF;
}
void ReceiveDataled(void)
{
	LED12_ON;
	osDelay(300);
	LED12_OFF;
}
static void PowerOnSta(void)
{
	LED10_OFF;
	LED11_OFF;
	LED12_OFF;
}
static void NetConnectSta(void)
{
	LED10_ON;
	osDelay(300);
	LED10_OFF;
	osDelay(100);
}
static void DeviceRegSta(void)
{
	LED10_ON;
	osDelay(700);
	LED10_OFF;
	osDelay(300);
}
static void RegCompleteSta(void)
{
	LED10_OFF;
	Lierda_SysValue.RegCompLedflag=1;
}
/******************************************************************************
* @函数名	app任务线程
* @参数	    param : 空参数，无效
* @返回值  无
******************************************************************************/
void lierda_LedSta_task(void *param)
{
	UNUSED(param);uint8 count=0;
	osDelay(500);//等待模组初始化完成
	Lierda_Led_Init();//LED灯初始化
	for (;;)
	{
		switch(Lierda_SysValue.DeviceSta)
		{
			case Power_ON:
				PowerOnSta();//开机状态
				break;
			case ConnectNet:
				NetConnectSta();//网络连接状态
				break;
			case Device_Reg:
				DeviceRegSta();//设备注册状态
				break;
			case Reg_Complete:
				if(Lierda_SysValue.RegCompLedflag==0)
					RegCompleteSta();//注册完成状态
				break;
			default:; break;
		}
		count++;
		if(count==100)
		{
			count=0;
			lierda_ReadSensor();//1s更新一次外设信息
		}
		osDelay(10);
	}
}
