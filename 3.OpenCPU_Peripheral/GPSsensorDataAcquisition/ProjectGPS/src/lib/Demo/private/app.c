/******************************************************************************
 * @����	�û�������
 * @���	Lierda NB-IoT �������Ŷ�@2018
******************************************************************************/
#include "app.h"

osThreadAttr_t App_task_attr = { "lierda_App_task"/*��������*/, 0, NULL, 0, NULL,
		(256) /*�����ջ��С*/, 11/*�������ȼ�*/, 0, 0 };//�������Խṹ��
uint32 * App_task_handle = NULL;
osThreadAttr_t Gps_task_attr = { "lierda_Gps_task"/*��������*/, 0, NULL, 0, NULL,
		(256) /*�����ջ��С*/, 11/*�������ȼ�*/, 0, 0 };//�������Խṹ��
uint32 * Gps_task_handle = NULL;
osTimerId_t LierdaTimer_handle=NULL;

static void TitlePrint( char *name);
/******************************************************************************
* @������	app�����߳�
* @����	    param : �ղ�������Ч
* @����ֵ  ��
******************************************************************************/
void lierda_App_task(void *param)
{
	UNUSED(param);
	osDelay(500);//�ȴ�ģ���ʼ�����
	char *pRMC=NULL;
	TitlePrint("GPS����");
	for (;;)
	{
		if(DataEnd==1)//GPS���ݽ������
		{
			DataEnd=0;//���������ɱ�־λ
	    	pRMC = strstr((const char *) GpsDataBuff, "$GNRMC");//�ж������Ƿ�Ϊ��Ч����
	    	if ((pRMC)&&(GpsDataLen > 8))
	    	{
	    		memset(&Gps_Data, 0, sizeof(GPSRMCStruct));
	    		iRMC_decode((char *)(pRMC), 100);//GPS���ݽ���
	    		if(Gps_Data.Valid_status=='A')//�ж��Ƿ�Ϊ��Ч����
	    		{
	    			lierdaLog("ʱ�䣺%s %s(ddmmyy hhmmss.sss)\r\n������%c\r\nγ�ȣ�%s\r\n���ȣ�%s\r\n�ϱ���%c",Gps_Data.Date,Gps_Data.UTC_Time,Gps_Data.EW_indicator,Gps_Data.Latitude,Gps_Data.Longitude,Gps_Data.NS_indicator);
	    		}
	    		else
	    			lierdaLog("GPSδ��λ�ɹ�");
	    	}
	    	else
	    	{
	    		lierdaLog("GPSδ��λ�ɹ�");
	    	}
			osDelay(10);
			Gps_data_clear();//���GPS��������
		}
		osDelay(10);
	}
}
void Lierda_SoftTimerCallback(void *param)
{
	UNUSED(param);
	if(DataStart==1)
	{
		if(Timercount==10)
		{
			Timercount=0;
			DataStart=0;
			DataEnd=1;
		}
		Timercount++;
	}
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
	Gps_task_handle = osThreadNew(lierda_Gps_task, NULL, &Gps_task_attr); //������������
	if (Gps_task_handle == NULL)
	{
		lierdaLog("	lierda_Gps_task���񴴽�ʧ��");
	}
	LierdaTimer_handle=osTimerNew (Lierda_SoftTimerCallback, osTimerPeriodic, NULL, NULL);
	if (LierdaTimer_handle == NULL)
	{
		lierdaLog("	LierdaTimer_handle��ʱ������ʧ��");
	}
}

/******************************************************************************
* @������ ϵͳ��Ϣ��ӡ
* @����	 *name : ������
* @����ֵ  ��
******************************************************************************/
static void TitlePrint( char *name)
{

 lierdaLog("******************************************************************************");
 lierdaLog("                       NB86 EVK����������----%s                                    \r\n",name);
 lierdaLog(" ������Ƽ�����<www.lierda.com>");
 lierdaLog(" LSD Science&Technology Co.,Ltd");
 lierdaLog(" �������ຼ����һ��·1326��������Ƽ�԰");
 lierdaLog(" ����������������<http://bbs.lierda.com>");
 lierdaLog("******************************************************************************\r\n");
}
