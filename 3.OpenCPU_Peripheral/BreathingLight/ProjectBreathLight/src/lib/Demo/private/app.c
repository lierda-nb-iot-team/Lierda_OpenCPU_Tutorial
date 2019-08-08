/******************************************************************************
 * @����	�û�������
 * @���	Lierda NB-IoT �������Ŷ�@2018
******************************************************************************/
#include "app.h"
#include "core.h"
#include "watchdog.h"


osThreadAttr_t App_task_attr = { "lierda_App_task"/*��������*/, 0, NULL, 0, NULL,
		(256) /*�����ջ��С*/, 11/*�������ȼ�*/, 0, 0 };//�������Խṹ��
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
	/*����*/
	PWMtime = MAX_TIME;
	while(1){
		PWMtime -= SPEED;
		Led_loop(PWMtime,MAX_TIME-PWMtime);
		if(PWMtime < SPEED)
			break;
	}
	/*����*/
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
* @������	app�����߳�
* @����	    param : �ղ�������Ч
* @����ֵ  ��
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
	osThreadResume(App_task_handle); //700ms���˻ָ�����
}
/******************************************************************************
* @������ �����û��߳�
* @����	param : �ղ���
* @����ֵ  ��
******************************************************************************/
void lierda_App_main(void)
{
	App_task_handle = osThreadNew(lierda_App_task, NULL, &App_task_attr); //������������
	if (App_task_handle == NULL)
	{
		lierdaLog("	lierda_App_task���񴴽�ʧ��");
	}
	LierdaTimer_handle=osTimerNew (Lierda_SoftTimerCallback, osTimerPeriodic, NULL, NULL);
	if (LierdaTimer_handle == NULL)
	{
		lierdaLog("	LierdaTimer_handle��ʱ������ʧ��");
	}
}
