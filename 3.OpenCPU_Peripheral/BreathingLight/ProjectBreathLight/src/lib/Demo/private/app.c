/******************************************************************************
 * @内容	用户任务函数
 * @设计	Lierda NB-IoT 软件设计团队@2018
******************************************************************************/
#include "app.h"
#include "core.h"
#include "watchdog.h"


osThreadAttr_t App_task_attr = { "lierda_App_task"/*任务名称*/, 0, NULL, 0, NULL,
		(256) /*任务堆栈大小*/, 11/*任务优先级*/, 0, 0 };//任务属性结构体
uint32 * App_task_handle = NULL;
osTimerId_t LierdaTimer_handle=NULL;


#define MAX_TIME (10000)
#define MIN_TIME (0)
#define SPEED    (100)

int PWMtime = 0;

static void delay_us(uint32 us)
{
	for (uint32 i = us; i > 0; i--)
	{
		__NOP();
		__NOP();
		__NOP();
		__NOP();
		__NOP();
		__NOP();
		__NOP();
		__NOP();
		__NOP();
	}
}


static void Led_loop(int on,int off)
{
	LED10_ON;
	delay_us(on);
	LED10_OFF;
	delay_us(off);
}


static void Led_breath(void)
{
	/*渐暗*/
	PWMtime = MAX_TIME;
	while(1){
		PWMtime -= SPEED;
		Led_loop(PWMtime,MAX_TIME-PWMtime);
		if(PWMtime < SPEED)
			break;
	}
	/*渐亮*/
	PWMtime = MAX_TIME;
	while(1)
	{
		PWMtime -= SPEED;
		Led_loop(MAX_TIME-PWMtime,PWMtime);
		if(PWMtime < SPEED)
			break;
	}

}


/******************************************************************************
* @函数名	app任务线程
* @参数	    param : 空参数，无效
* @返回值  无
******************************************************************************/
void lierda_App_task(void *param)
{
	UNUSED(param);

	gpio_claim(PIN_25, GPIO_DIRECTION_OUTPUT);
	for (;;)
	{
		Led_breath();
		osDelay(1);
	}
}

void Lierda_SoftTimerCallback(void *param)
{
	UNUSED(param);
	osThreadResume(App_task_handle); //700ms到了恢复任务
}
/******************************************************************************
* @函数名 创建用户线程
* @参数	param : 空参数
* @返回值  无
******************************************************************************/
void lierda_App_main(void)
{
	App_task_handle = osThreadNew(lierda_App_task, NULL, &App_task_attr); //创建测试任务
	if (App_task_handle == NULL)
	{
		lierdaLog("	lierda_App_task任务创建失败");
	}
	LierdaTimer_handle=osTimerNew (Lierda_SoftTimerCallback, osTimerPeriodic, NULL, NULL);
	if (LierdaTimer_handle == NULL)
	{
		lierdaLog("	LierdaTimer_handle定时器创建失败");
	}
}
