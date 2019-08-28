/******************************************************************************
 * @����	�û�������
 * @���	Lierda NB-IoT �������Ŷ�@2018
******************************************************************************/
#include "app.h"

//ȫ�ֱ���
osThreadAttr_t App_task_attr = { "lierda_App_task"/*��������*/, 0, NULL, 0, NULL,
		(400) /*�����ջ��С*/, 11/*�������ȼ�*/, 0, 0 };//�������Խṹ��
uint32 * App_task_handle = NULL;

osThreadAttr_t LedSta_task_attr = { "lierda_LedSta_task"/*��������*/, 0, NULL, 0, NULL,
		(256) /*�����ջ��С*/, 10/*�������ȼ�*/, 0, 0 };//�������Խṹ��
uint32 * LedSta_task_handle = NULL;

osThreadAttr_t nnmi_task_attr = { "lierda_NNMI_task"/*��������*/, 0, NULL, 0, NULL,
		(256) /*�����ջ��С*/, 11/*�������ȼ�*/, 0, 0 };//�������Խṹ��
uint32 * NNMITaskHandle = NULL;

kvTempHumi LierdatempHumiKv;
SysValue Lierda_SysValue;
osTimerId_t Timedreport_handle=NULL;
osTimerId_t TimedTempwarning_handle=NULL;
osTimerId_t TimedHumiwarning_handle=NULL;
osMessageQueueId_t Lierda_App_queue=NULL;
uint32 timercount=0,TempWarntimercount=0,HumiWarntimercount=0;

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
static void DeviceParameterConfig(void);
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
	TitlePrint("��ʪ�Ȳɼ�������");
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
						Lierda_ServerReg();//ע��δ��ɣ�����ע��
					TimerControlFun(TIMEDREPORT,1,1000);//�򿪶�ʱ��
					break;
				case key_data://������Ϣ����
					if(Lierda_SysValue.DeviceSta==Reg_Complete)
					{
						lierdaLog("�������������ϱ�");
						Lierda_ServerSendData();//��ע��������ϱ���Ϣ
					}
					else
						lierdaLog("δ���ע��");
					break;
				case Stachange_data://������Ϣ�ı�
					lierdaLog("DBG_INFO:������Ϣ�ı������ϱ�");
					Lierda_ServerSendData();//�ϱ���Ϣ
					break;
				case TempWarning_data://�б���
					 if(Lierda_SysValue.tempwarningflag==1)
					{
						lierdaLog("DBG_INFO:�¶ȱ��������ϱ�");
						Lierda_ServerSendData();//�ϱ���Ϣ
					}
					 else
						 lierdaLog("DBG_INFO:�¶ȱ���ȡ��");
					break;
				case HumiWarning_data://�б���
					 if(Lierda_SysValue.humiwarningfalg==1)
					{
						lierdaLog("DBG_INFO:ʪ�ȱ��������ϱ�");
						Lierda_ServerSendData();//�ϱ���Ϣ
					}
					 else
						 lierdaLog("DBG_INFO:ʪ�ȱ���ȡ��");
					break;
				default :break;
				}
			}
		osDelay(10);
	}
}


static void lierda_Device_Init(void)
{
	Lierda_KEY_Init(KEY2, GPIO_DIRECTION_INPUT); //������ʼ��
	lierda_sensor_I2C_init(PIN_14,PIN_15);//I2C��ʼ��
	lierda_HDC1000_Init();//��ʪ�ȴ�������ʼ��
	lierda_ReadSensor();//���ݻ�ȡ
}

void lierda_ReadSensor(void)
{
	int16 temper=0,humidity=0;uint8 warningtemp=0;
	lierda_HDC1000_UpdateInfo(&temper,&humidity);
	Lierda_SysValue.Temperature=temper/10+Lierda_SysValue.TempCorrect;
	Lierda_SysValue.humidity=humidity;
	if(Lierda_SysValue.Temperature>Lierda_SysValue.HightTempThreshold)
	{
		//���±���
		warningtemp=warningtemp|HIGHTTEMPW;
		Lierda_SysValue.tempwarningflag=1;
		if(Lierda_SysValue.oldtempwarning!=(warningtemp&0x03))
		{

			TimerControlFun(TIMETEMPDWARNING,1,1000);
			lierdaLog("DBG_INFO:���±���");
		}
	}
	if(Lierda_SysValue.Temperature<Lierda_SysValue.LowTempThreshold)
	{
		//���±���
		warningtemp=warningtemp|LOWTEMPW;
		Lierda_SysValue.tempwarningflag=1;
		if(Lierda_SysValue.oldtempwarning!=(warningtemp&0x03))
		{
			TimerControlFun(TIMETEMPDWARNING,1,1000);
			lierdaLog("DBG_INFO:���±���");
		}
	}
	if(Lierda_SysValue.humidity>Lierda_SysValue.HightHumiThreshold)
	{
		//��ʪ����
		warningtemp=warningtemp|HIGHTHUMIW;
		Lierda_SysValue.humiwarningfalg=1;
		if(Lierda_SysValue.oldhumiwarning!=(warningtemp&0x0c))
		{
			TimerControlFun(TIMEHUMIDWARNING,1,1000);
			lierdaLog("DBG_INFO:��ʪ����");
		}
	}
	if(Lierda_SysValue.humidity<Lierda_SysValue.LowHumiThreshold)
	{
		//��ʪ����
		warningtemp=warningtemp|LOWHUMIW;
		Lierda_SysValue.humiwarningfalg=1;
		if(Lierda_SysValue.oldhumiwarning!=(warningtemp&0x0c))
		{
			TimerControlFun(TIMEHUMIDWARNING,1,1000);
			lierdaLog("DBG_INFO:��ʪ����");
		}
	}
	Lierda_SysValue.warning=warningtemp;
	if((warningtemp&0x03)==0)
	{
		Lierda_SysValue.tempwarningflag=0;
	}
	if((warningtemp&0x0c)==0)
	{
		Lierda_SysValue.humiwarningfalg=0;
	}
	Lierda_SysValue.oldhumiwarning=(warningtemp&0x0c);
	Lierda_SysValue.oldtempwarning=(warningtemp&0x03);
	//lierdaLog("DBG_INFO:Temperature=%d	humidity=%d",Lierda_SysValue.Temperature,Lierda_SysValue.humidity);
}


static void SysInit(void)
{
	Lierda_SysValue.AckDataNum=0;
	Lierda_SysValue.SendDataNum=0;
	DeviceParameterConfig();//�豸��������
	NetworkConfigInit();//�����ʼ��
	DeviceInfoGet();//�豸��Ϣ��ȡ
	lierda_Device_Init();//�豸��ʼ��
}


static void DeviceParameterConfig(void)
{
	uint16 KvLen=0;
	if((lierdaKVGet(KVID, sizeof(kvTempHumi),&KvLen,(uint8 *)&LierdatempHumiKv)==LIERDA_RET_OK)&&(KvLen==sizeof(kvTempHumi)))
	{
		Lierda_SysValue.ReportCycle=LierdatempHumiKv.ReportCycle;
		Lierda_SysValue.HightTempThreshold=LierdatempHumiKv.HightTempThreshold;
		Lierda_SysValue.LowTempThreshold=LierdatempHumiKv.LowTempThreshold;
		Lierda_SysValue.TempDelayWarn=LierdatempHumiKv.TempDelayWarn;
		Lierda_SysValue.TempCorrect=LierdatempHumiKv.TempCorrect;
		Lierda_SysValue.HightHumiThreshold=LierdatempHumiKv.HightHumiThreshold;
		Lierda_SysValue.LowHumiThreshold=LierdatempHumiKv.LowHumiThreshold;
		Lierda_SysValue.HumiDelayWarn=LierdatempHumiKv.HumiDelayWarn;
		Lierda_SysValue.BatteryThreshold=LierdatempHumiKv.BatteryThreshold;
	}
	else
	{
		Lierda_SysValue.ReportCycle=REPORTCYCLE;
		Lierda_SysValue.HightTempThreshold=HIGHTTEMPTHRE*10;
		Lierda_SysValue.LowTempThreshold=LOWTTEMPTHRE*10;
		Lierda_SysValue.TempDelayWarn=TEMPDELYWARN;
		Lierda_SysValue.TempCorrect=TEMPCORRECT;
		Lierda_SysValue.HightHumiThreshold=HIGHTHUMITHRE;
		Lierda_SysValue.LowHumiThreshold=LOWTHUMITHRE;
		Lierda_SysValue.HumiDelayWarn=HUMIDELYWARN;
		Lierda_SysValue.BatteryThreshold=BATTERYTHRES;
		DeviceParametersave();
	}

}

void DeviceParametersave(void)
{
	LierdatempHumiKv.ReportCycle=Lierda_SysValue.ReportCycle;
	LierdatempHumiKv.HightTempThreshold=Lierda_SysValue.HightTempThreshold;
	LierdatempHumiKv.LowTempThreshold=Lierda_SysValue.LowTempThreshold;
	LierdatempHumiKv.TempDelayWarn=Lierda_SysValue.TempDelayWarn;
	LierdatempHumiKv.TempCorrect=Lierda_SysValue.TempCorrect;
	LierdatempHumiKv.HightHumiThreshold=Lierda_SysValue.HightHumiThreshold;
	LierdatempHumiKv.LowHumiThreshold=Lierda_SysValue.LowHumiThreshold;
	LierdatempHumiKv.HumiDelayWarn=Lierda_SysValue.HumiDelayWarn;
	LierdatempHumiKv.BatteryThreshold=Lierda_SysValue.BatteryThreshold;
	if(lierdaKVSet(KVID, (uint8 *)&LierdatempHumiKv, sizeof(kvTempHumi))==LIERDA_RET_OK)
		lierdaLog("DBG_INFO:DeviceParametersave OK");
	else
		lierdaLog("DBG_INFO:DeviceParametersave error");
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
		timercount++;
		if(timercount==(Lierda_SysValue.ReportCycle+1))
		{
			temp=Timer_data;
			timercount=0;
			QueueSendDataFun(&temp);
		}
	}
	if(param==(void *)TIMETEMPDWARNING)
	{
		TempWarntimercount++;
		if(TempWarntimercount==((Lierda_SysValue.TempDelayWarn*60)+1))
		{
			 temp=TempWarning_data;
			 TempWarntimercount=0;
			 QueueSendDataFun(&temp);
			TimerControlFun(TIMETEMPDWARNING,0,1000);
		}
	}
	if(param==(void *)TIMEHUMIDWARNING)
	{
		HumiWarntimercount++;
		if(HumiWarntimercount==((Lierda_SysValue.HumiDelayWarn*60)+1))
		{
			 temp=HumiWarning_data;
			 HumiWarntimercount=0;
			 QueueSendDataFun(&temp);
			TimerControlFun(TIMEHUMIDWARNING,0,1000);
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
			if(osTimerIsRunning(Timedreport_handle))
			{
				osTimerStop(Timedreport_handle);
			}
			osTimerStart(Timedreport_handle,timer);
		}
		else if(timerid==TIMETEMPDWARNING)
		{
			if(osTimerIsRunning(TimedTempwarning_handle))
			{
				osTimerStop(TimedTempwarning_handle);
			}
			osTimerStart(TimedTempwarning_handle,timer);
		}
		else if(timerid==TIMEHUMIDWARNING)
		{
			if(osTimerIsRunning(TimedHumiwarning_handle))
			{
				osTimerStop(TimedHumiwarning_handle);
			}
			osTimerStart(TimedHumiwarning_handle,timer);
		}
	}
	else
	{
		if(timerid==TIMEDREPORT)
		{
			if(osTimerIsRunning(Timedreport_handle))
			{
				osTimerStop(Timedreport_handle);
			}
		}
		else if(timerid==TIMETEMPDWARNING)
		{
			if(osTimerIsRunning(TimedTempwarning_handle))
			{
				osTimerStop(TimedTempwarning_handle);
			}
		}
		else if(timerid==TIMEHUMIDWARNING)
		{
			if(osTimerIsRunning(TimedHumiwarning_handle))
			{
				osTimerStop(TimedHumiwarning_handle);
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
	TimedTempwarning_handle=osTimerNew (Lierda_SoftTimerCallback, osTimerPeriodic, (void *)TIMETEMPDWARNING, NULL);
	if (TimedTempwarning_handle == NULL)
	{
		lierdaLog("	TimedTempwarning_handle ��ʱ������ʧ��");
	}
	TimedHumiwarning_handle=osTimerNew (Lierda_SoftTimerCallback, osTimerPeriodic, (void *)TIMEHUMIDWARNING, NULL);
	if (TimedHumiwarning_handle == NULL)
	{
		lierdaLog("	TimedHumiwarning_handle ��ʱ������ʧ��");
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
