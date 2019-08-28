/******************************************************************************
 * @����	�û�������
 * @���	Lierda NB-IoT �������Ŷ�@2018
******************************************************************************/
#include "app.h"

//ȫ�ֱ���
osThreadAttr_t App_task_attr = { "lierda_App_task"/*��������*/, 0, NULL, 0, NULL,
		(512) /*�����ջ��С*/, 11/*�������ȼ�*/, 0, 0 };//�������Խṹ��
uint32 * App_task_handle = NULL;

osThreadAttr_t LedSta_task_attr = { "lierda_LedSta_task"/*��������*/, 0, NULL, 0, NULL,
		(250) /*�����ջ��С*/, 10/*�������ȼ�*/, 0, 0 };//�������Խṹ��
uint32 * LedSta_task_handle = NULL;

osThreadAttr_t nnmi_task_attr = { "lierda_NNMI_task"/*��������*/, 0, NULL, 0, NULL,
		(256) /*�����ջ��С*/, 11/*�������ȼ�*/, 0, 0 };//�������Խṹ��
uint32 * NNMITaskHandle = NULL;

struct SysKvSave syskvsave;
SysValue Lierda_SysValue;
osTimerId_t Timedreport_handle=NULL;
osTimerId_t TimeCoollecGps_handle=NULL;
osTimerId_t TimeSearchGps_handle=NULL;
osMessageQueueId_t Lierda_App_queue=NULL;
uint32 Retimercount=0,TimerCollCount=0,TimerSeachCount=0;

//��������
static void Lierda_TaskCreateFun(void);
static void Lierda_QueueCreateFun(void);
static void Lierda_TimerCreateFun(void);
static void TitlePrint( char *name);
static uint8 lierdaATDemoCall(char* cmd, char* result, uint16 timeOut, uint16 num);
static void SysInit(void);
static void NetworkConfigInit(void);
static void DeviceInfoGet(void);
static void lierda_Device_Init(void);
void DeviceParameterConfig(void);


/******************************************************************************
* @������	app�����߳�
* @����	    param : �ղ�������Ч
* @����ֵ  ��
******************************************************************************/
void lierda_App_task(void *param)
{
	UNUSED(param);uint8 temp=0;
	osDelay(500);//�ȴ�ģ���ʼ�����
	Lierda_SysValue.DeviceSta=Power_ON;
	Lierda_SysValue.RegCompLedflag=0;
	TitlePrint("��λ������");
	SysInit();//ϵͳ������ʼ��
	Lierda_ServerReg();//�豸ע��
	TimerControlFun(TIMEDREPORT,1,1000);//�򿪶�ʱ���ͼ�����
	for (;;)
	{
		if (osMessageQueueGet(Lierda_App_queue, (void*) &temp, NULL,osWaitForever) == osOK)
			{
				switch(temp)
				{
				case Timer_data://��ʱ����Ϣ
					TimerControlFun(TIMEDREPORT,0,1000);//�رն�ʱ��
					if(Lierda_SysValue.DeviceSta==Reg_Complete)
					{
						lierdaLog("��ʱ�����ϱ�");
						Lierda_ServerSendData();//��ע��������ϱ���Ϣ
					}
					else
						{
							Lierda_ServerReg();//ע��δ��ɣ�����ע��
							lierdaLog("δ���ע��");
						}
					TimerControlFun(TIMEDREPORT,1,1000);//�򿪶�ʱ��
					break;
				case key_data://������Ϣ����
					if(Lierda_SysValue.DeviceSta==Reg_Complete)
					{
						if(Lierda_SysValue.SysMode==StandardMode)
						{
								lierdaLog("�������¶�λ��");
								Gps_Open();
								TimerControlFun(TIMESEARCHGPS,1,1000);
						}
					}
					else
					{
						Lierda_ServerReg();//ע��δ��ɣ�����ע��
						lierdaLog("δ���ע��");
					}
					break;
				case OpenGPS://��GPS
					lierdaLog("DBG_INFO:��GPS");
					Gps_Open();
					break;
				case CloseGPS://�ر�GPS
					lierdaLog("DBG_INFO:�ر�GPS\r\n��λ�����%d",Lierda_SysValue.GpsPositSuc);
					Gps_Close();
					break;
				case Stachange_data://������Ϣ�ı�
					Lierda_ServerSendData();//������Ϣ�ı��ϱ���Ϣ
					break;
				default :break;
				}
			}
		osDelay(10);
	}
}




static void lierda_Device_Init(void)
{
	uint16 kvlen=0;
	if((lierdaKVGet(KVID,sizeof(struct SysKvSave),&kvlen,(uint8 *) &syskvsave)==LIERDA_RET_OK)&&(kvlen==sizeof(struct SysKvSave)))
	{
		Lierda_SysValue.SysMode=syskvsave.DeviceMode;
		Lierda_SysValue.ReportCycle=syskvsave.ReportCycle;
		Lierda_SysValue.CollCycle=syskvsave.CollCycle;
		Lierda_SysValue.MaxSearchTimer=syskvsave.MaxSearchTimer;
		Lierda_SysValue.GpsHoldTimer=syskvsave.GpsHoldTimer;
	}
	else
	{
		DeviceParameterConfig();
		DeviceParameterSave();
	}
	Deviceswitch();

}
void Deviceswitch(void)
{
	Lierda_SysValue.GpsDataNum=0;
	Lierda_SysValue.GpsDataNumFullFlag=0;
	TimerControlFun(TIMEDREPORT,1,1000);//�򿪶�ʱ��
	if(Lierda_SysValue.SysMode==TrackerMode)
	{
		 TimerControlFun(TIMECOOLLECGPS,1,1000);
		 Key_Close();
	}
	else
	{
		Key_Open();
		TimerControlFun(TIMECOOLLECGPS,0,1000);
	}
}
void DeviceParameterConfig(void)
{
	Lierda_SysValue.SysMode=TrackerMode;//ϵͳĬ�϶�λģʽ
	Lierda_SysValue.ReportCycle=REPORTCYCLE;//Ĭ���ϱ�����
	Lierda_SysValue.CollCycle=COOLLCYCLE;//Ĭ����������
	Lierda_SysValue.MaxSearchTimer=MAXSEARTIME;//�������ʱ��
	Lierda_SysValue.GpsHoldTimer=SEARHOLDTIME;//���Ǳ���ʱ��
}
void DeviceParameterSave(void)
{
	syskvsave.CollCycle=Lierda_SysValue.CollCycle;
	syskvsave.DeviceMode=Lierda_SysValue.SysMode;
	syskvsave.MaxSearchTimer=Lierda_SysValue.MaxSearchTimer;
	syskvsave.ReportCycle=Lierda_SysValue.ReportCycle;
	syskvsave.GpsHoldTimer=Lierda_SysValue.GpsHoldTimer;
	if(lierdaKVSet(KVID,(uint8 *)&syskvsave, sizeof(struct SysKvSave))==LIERDA_RET_OK)
		lierdaLog("DBG_INFO:DeviceConfigSave SUC");
	else
		lierdaLog("DBG_INFO:DeviceConfigSave ERROR");
}

static void SysInit(void)
{
	lierda_GPS_task_enable();
	NetworkConfigInit();//�����ʼ��
	DeviceInfoGet();//�豸��Ϣ��ȡ
	lierda_Device_Init();//�豸��ʼ��
}


static void DeviceInfoGet(void)
{
	char * returaddr=NULL;
	returaddr = lierdaATCall("AT+CGSN=1", 1000);  //��ѯIMEI
	returaddr=strstr(returaddr,"+CGSN:");
	memcpy(Lierda_SysValue.Module_IMEI,returaddr+6,15);
	lierdaLog("DBG_INFO:IMEI:%s",Lierda_SysValue.Module_IMEI);
	returaddr = lierdaATCall("AT+NCCID", 1000);  //��ѯICCID
	returaddr=strstr(returaddr,"+NCCID:");
	memcpy(Lierda_SysValue.Module_ICCID,returaddr+7,20);
	lierdaLog("DBG_INFO:ICCID:%s",Lierda_SysValue.Module_ICCID);
	returaddr = lierdaATCall("AT+CIMI", 1000);  //��ѯIMSI
	memcpy(Lierda_SysValue.Module_IMSI,returaddr+2,15);
	lierdaLog("DBG_INFO:IMSI:%s",Lierda_SysValue.Module_IMSI);
}

static void NetworkConfigInit(void)
{
	char * returaddr=NULL;
	returaddr = lierdaATCall("AT+NCDP?", 3000);  //��ѯNCDP
	lierdaLog("DBG_INFO:NCDP?:%s",returaddr);
	if (strstr(returaddr, "+NCDP:117.60.157.137,5683") == NULL)
	{
		lierdaATDemoCall("AT+CFUN=0","OK",3000,5);  //�ر���Ƶ
		lierdaATDemoCall("AT+NCDP=117.60.157.137,5683","OK",3000,5);  //����NCDP
		lierdaATDemoCall("AT+NRB","OK",7000,5);   //��λ����
	}
	Lierda_SysValue.DeviceSta=ConnectNet;
	lierdaATDemoCall("AT+CPSMS=1","OK",3000,5);//��PSM
	lierdaATDemoCall("AT+NPSMR=1","OK",3000,5);//��PSMģʽ֪ͨ
	osDelay(3000);
	lierdaATDemoCall("AT+CGATT=1","OK",2000,5);
	do
	{
		returaddr = lierdaATCall("AT+CGATT?", 1000);  //��ѯ�Ƿ���������

		if(strstr(returaddr, "+CGATT:1") == NULL)
			{
				osDelay(1000);
				lierdaLog("DBG_INFO:���ڸ�������");
			}
	}while(strstr(returaddr, "+CGATT:1") == NULL);
	lierdaLog("DBG_INFO:���總�ųɹ�");
}
/******************************************************************************
* @������ ����ATָ���
* @����	   cmd :ATָ����ü�"\r\n"
* @����	result :Ԥ�ڵ���ȷ������Ϣ
* @����    timeOut :��ʱʱ��,ms
* @����             num  :���Դ���
* @����ֵ            1:���ͳɹ�        0 ������ʧ��
******************************************************************************/
 static uint8 lierdaATDemoCall(char* cmd, char* result, uint16 timeOut, uint16 num)
{
	uint16 i;char *returaddr=NULL;
	for (i = 0; i < num; i++)
	{
		returaddr = lierdaATCall(cmd, timeOut);  //����ATָ��
		lierdaLog("DBG_INFO:cmd:%s\r\nresult:%s",cmd,returaddr);
		if (strstr(returaddr, result) != NULL)
			return 1;
		else
			osDelay(1000);
	}
	return 0;  //����ʧ��
}
void Lierda_SoftTimerCallback(void *param)
{
	uint8 temp=0;
	if(param==(void *)TIMEDREPORT)
	{
		Retimercount++;
		if(Retimercount==(Lierda_SysValue.ReportCycle+1))
		{
			temp=Timer_data;
			Retimercount=0;
			QueueSendDataFun(&temp);
		}
	}
	else if(param==(void *)TIMECOOLLECGPS)
	{
		TimerCollCount++;
		if(TimerCollCount==Lierda_SysValue.CollCycle+1)
		{
			TimerCollCount=0;
			TimerControlFun(TIMECOOLLECGPS,0,1000);
			TimerControlFun(TIMESEARCHGPS,1,1000);
			temp=OpenGPS;
			QueueSendDataFun(&temp);
		}
	}
	else if(param==(void *)TIMESEARCHGPS)
	{
		TimerSeachCount++;
		LED10_TOGGLE;
		if(Lierda_SysValue.GpsHoldFlag==0)
		{
			if(TimerSeachCount==Lierda_SysValue.MaxSearchTimer+1)
			{
				TimerControlFun(TIMESEARCHGPS,0,1000);
				LED10_OFF;
				TimerSeachCount=0;
				temp=CloseGPS;
				QueueSendDataFun(&temp);
				Lierda_SysValue.GpsHoldFlag=0;
				if(Lierda_SysValue.GpsPositSuc==0)
				{
						Lierda_SysValue.GpsDataNum++;
					    Lierda_SysValue.gpsInfo.SerialNum=Lierda_SysValue.GpsDataNum;
						Lierda_SysValue.gpsInfo.SignalQuality=0x01;
						Lierda_SysValue.gpsInfo.longitude=0x4784c880;//0x4784c880
						Lierda_SysValue.gpsInfo.longitude=BigtoLittle32(Lierda_SysValue.gpsInfo.longitude);
						Lierda_SysValue.gpsInfo.latitude=0x120c2640;//0x120c2640
						Lierda_SysValue.gpsInfo.latitude=BigtoLittle32(Lierda_SysValue.gpsInfo.latitude);
						Lierda_SysValue.gpsInfo.Position=0x02;
						memcpy(GpsDtaBuff+((Lierda_SysValue.GpsDataNum-1)*GPSDATAPACK_LEN),&Lierda_SysValue.gpsInfo,GPSDATAPACK_LEN);
						if(Lierda_SysValue.GpsDataNum==10)
						{
							Lierda_SysValue.GpsDataNum=0;
							Lierda_SysValue.GpsDataNumFullFlag=1;
						}

				}
				if(Lierda_SysValue.SysMode!=StandardMode)
					TimerControlFun(TIMECOOLLECGPS,1,1000);
				else
					TimerControlFun(TIMECOOLLECGPS,0,1000);
			}
		}
		else
		{
			if(TimerSeachCount==Lierda_SysValue.GpsHoldTimer+1)
			{
				TimerSeachCount=0;
				LED10_OFF;
				temp=CloseGPS;
				QueueSendDataFun(&temp);
				TimerControlFun(TIMESEARCHGPS,0,1000);
				if(Lierda_SysValue.SysMode!=StandardMode)
					TimerControlFun(TIMECOOLLECGPS,1,1000);
				else
					TimerControlFun(TIMECOOLLECGPS,0,1000);
			}
		}

	}
}
/******************************************************************************
* @������ �����û��߳�
* @����	param : �ղ���
* @����ֵ  ��
******************************************************************************/
void lierda_App_main(void)
{
	Lierda_TaskCreateFun();//���񴴽�
	Lierda_QueueCreateFun();//���д���
	Lierda_TimerCreateFun();//��ʱ������
}

static void Lierda_TaskCreateFun(void)
{
	App_task_handle = osThreadNew(lierda_App_task, NULL, &App_task_attr); //����������
	if (App_task_handle == NULL)
	{
		lierdaLog("	lierda_App_task ���񴴽�ʧ��");
	}
	LedSta_task_handle = osThreadNew(lierda_LedSta_task, NULL, &LedSta_task_attr); //����LED��״̬����
	if (LedSta_task_handle == NULL)
	{
		lierdaLog("	lierda_App_task ���񴴽�ʧ��");
	}

	NNMITaskHandle = osThreadNew (lierda_MMNI_task, NULL, &nnmi_task_attr);//�������������������
	if (NNMITaskHandle == NULL)
	{
		lierdaLog("	lierda_MMNI_task ���񴴽�ʧ��");
	}

}

void QueueSendDataFun(uint8 *msg)
{
	osMessageQueuePut (Lierda_App_queue, msg, 0,0);
}

void TimerControlFun(uint8 timerid,uint8 control,uint32 timer)
{
	if(control==1)
	{
		if(timerid==TIMEDREPORT)
		{
			Retimercount=0;
			if(osTimerIsRunning(Timedreport_handle))
			{
				osTimerStop(Timedreport_handle);
			}
			osTimerStart(Timedreport_handle,timer);
		}
		else if(timerid==TIMECOOLLECGPS)
		{
			TimerCollCount=0;
			if(osTimerIsRunning(TimeCoollecGps_handle))
			{
				osTimerStop(TimeCoollecGps_handle);
			}
			osTimerStart(TimeCoollecGps_handle,timer);
		}
		else if(timerid==TIMESEARCHGPS)
		{
			TimerSeachCount=0;
			if(osTimerIsRunning(TimeSearchGps_handle))
			{
				osTimerStop(TimeSearchGps_handle);
			}
			osTimerStart(TimeSearchGps_handle,timer);
		}
	}
	else
	{
		if(timerid==TIMEDREPORT)
		{
			Retimercount=0;
			if(osTimerIsRunning(Timedreport_handle))
			{
				osTimerStop(Timedreport_handle);
			}
		}
		else if(timerid==TIMECOOLLECGPS)
		{
			TimerCollCount=0;
			if(osTimerIsRunning(TimeCoollecGps_handle))
			{
				osTimerStop(TimeCoollecGps_handle);
			}
		}
		else if(timerid==TIMESEARCHGPS)
		{
			TimerSeachCount=0;
			if(osTimerIsRunning(TimeSearchGps_handle))
			{
				osTimerStop(TimeSearchGps_handle);
			}
		}
	}
}


static void Lierda_QueueCreateFun(void)
{
	Lierda_App_queue = osMessageQueueNew(5, 1, NULL); //����
	if (Lierda_App_queue == NULL)
	{
		lierdaLog("	Lierda_App_queue ���д���ʧ��");
	}

}




static void Lierda_TimerCreateFun(void)
{
	Timedreport_handle=osTimerNew (Lierda_SoftTimerCallback, osTimerPeriodic, (void *)TIMEDREPORT, NULL);
	if (Timedreport_handle == NULL)
	{
		lierdaLog("	Timedreport_handle ��ʱ������ʧ��");
	}
	TimeCoollecGps_handle=osTimerNew (Lierda_SoftTimerCallback, osTimerPeriodic, (void *)TIMECOOLLECGPS, NULL);
	if (TimeCoollecGps_handle == NULL)
	{
		lierdaLog("	TimeCoollecGps_handle ��ʱ������ʧ��");
	}
	TimeSearchGps_handle=osTimerNew (Lierda_SoftTimerCallback, osTimerPeriodic, (void *)TIMESEARCHGPS, NULL);
	if (TimeSearchGps_handle == NULL)
	{
		lierdaLog("	TimeSearchGps_handle ��ʱ������ʧ��");
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
