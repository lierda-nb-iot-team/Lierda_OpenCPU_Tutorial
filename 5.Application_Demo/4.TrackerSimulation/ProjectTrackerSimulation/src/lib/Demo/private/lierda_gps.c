/******************************************************************************
 * @����	���󱱶�HD8020��غ���
 * @���	Lierda NB-IoT �������Ŷ�@2018
******************************************************************************/

#include <stdio.h>
#include "string.h"
#include <stdlib.h>
#include "lierda_gps.h"
#include "neulfw.h"
#include "app_at_send_data.h"
#include "lierda_app_main.h"
#include "cmsis_os2.h"
#include "lierdaUART.h"

extern uint32 TimerSeachCount;
uint32 Get_NEMA_Form(char* source,char* result,uint32 len);
uint32 iRMC_decode(char* buff,uint32 len);
void lierda_USRT_task(void *argument);
void lierda_GPS_uart_init(void);

GPSRMCStruct  GPSData;
//GPSRMCStruct  *p_gps_data = &GPSData ;

uint16 Usrt_buff_len = 0;   // һ����������
uint16 Trans_buff_len = 0;  // һ�ְ�����
uint16 over_buff_len = 0;   // �жϽ������ݳ����Ƿ�BUFF

// UART3 ����������
osThreadId_t  USRTTaskHandle = NULL;
UART_HandleTypeDef  lierdaUARTHandle;   //GPS���ھ��
uint8 UartData_Start=0;
uint8 timer_count=0;

// UART3 ���ճ�ʱ��ʱ�����
static osTimerId_t  uart3_tick_timer = NULL;
#define UART3_TICK_TIMEOUT  30   // ��ʱ����ʱ30ms
void uart3_tick_timeout_callback(void *argument );
void uart3_timer_tick(void);

// GPS  ���ڲ�����  RX TX
uint32 midBaudRate=0;
uint8  midRXpin=0;
uint8  midTXpin=0;



/********************************************************
 *����: void lierda_GPS_task_enable(void)
 *���: None
 *����: None
 *����: ����������GPS�����߳�
 ********************************************************/
void lierda_GPS_task_enable(void)
{
	osThreadAttr_t usrt_task_attr = {
										"lierda_USRT_task",  /*��������*/
										0,
										NULL,
										0,
										NULL,
										250,   /*�����ջ��С*/
										11,    /*�������ȼ�*/
										0,
										0
									};
	USRTTaskHandle = osThreadNew (lierda_USRT_task, NULL, &usrt_task_attr);
	if (USRTTaskHandle == NULL)
	{
		lierdaLog("USRTTaskHandle,fail");
		return;
	}
}

/********************************************************
 *����: void lierda_GPS_task_disable(void)
 *���: None
 *����: None
 *����: ��ֹGPS�����߳�ִ��
 ********************************************************/
void lierda_GPS_task_disable(void)
{
    if (uart3_tick_timer != NULL)
    {
        (void)osTimerDelete(uart3_tick_timer);
        uart3_tick_timer = NULL;
    }

	osThreadTerminate(USRTTaskHandle);
	memset(&GPSData, 0, sizeof(GPSRMCStruct));
}

/********************************************************
 *����: void lierda_GPS_data_get( GPSRMCStruct  *p_gps_user )
 *���: None
 *����: None
 *����: �û���ȡGPS���ݺ���(�ṹ��ָ��)
 ********************************************************/
void lierda_GPS_data_get( GPSRMCStruct  *p_gps_user )
{
	memcpy(p_gps_user, &GPSData, sizeof(GPSRMCStruct));
}


/********************************************************
 *����: void lierda_GPS_uart_init(uint32 BaudRate, uint8 RX_pin, uint8 TX_pin)
 *���: None
 *����: None
 *����: ���ڳ�ʼ������
 ********************************************************/
void lierda_GPS_uart_init(void)
{
//	UART_HandleTypeDef  lierdaUARTHandle;   //���ھ��
	lierdaUARTHandle.baudrate  = UART_BAUD;
	lierdaUARTHandle.data_bits = UART_DATA_BITS_8;
	lierdaUARTHandle.parity    = UART_PARITY_NONE;
	lierdaUARTHandle.stopbits  = UART_STOP_BITS_1;
	lierdaUARTHandle.rx_pin    = RX_PIN;
	lierdaUARTHandle.tx_pin    = TX_PIN;
	lierdaUARTInit(&lierdaUARTHandle);
}

/********************************************************
 *����: void uart3_timer_tick
 *���: None
 *����: None
 *����: ���ڳ�ʱ��ʱ������
 ********************************************************/
void uart3_timer_tick(void)
{
	if (uart3_tick_timer == NULL)
	{
		uart3_tick_timer = osTimerNew(uart3_tick_timeout_callback, osTimerPeriodic, (void*)5, NULL);
	    if (uart3_tick_timer == NULL)
	    {
	    	lierdaLog("uart3_tick_timer new fail\r\n");
	    }
	}
	else
	{
	    osTimerStop (uart3_tick_timer);
	}
}

/********************************************************
 *����: void uart3_tick_timeout_callback
 *���: None
 *����: None
 *����: �����ʱ���ص�����
 ********************************************************/
void uart3_tick_timeout_callback(void *argument )
{
	char * pRMC = NULL;
	if (argument == (void*)5)
	{
		timer_count++;
		if(timer_count == 10)
		{
			if(UartData_Start == 1)
		    {
			    UartData_Start=0;
			    timer_count=0;
				osTimerStop (uart3_tick_timer);

			    pRMC = strstr((const char *)Usrt_buff, "$GNRMC");
				if ((pRMC) && (strlen((const char *)Usrt_buff) > 8))
				{
					memset(&GPSData, 0, sizeof(GPSRMCStruct));
					iRMC_decode((char *)(pRMC), 100);
					if(GPSData.Valid_status=='A')//��λ�ɹ�
					{
						Lierda_SysValue.GpsHoldFlag=1;

						Lierda_SysValue.GpsPositSuc=1;
						if(Lierda_SysValue.GpsDataGetFlag==0)
						{
							TimerSeachCount=0;
							Lierda_SysValue.GpsDataNum++;
							Lierda_SysValue.GpsDataGetFlag=1;
							gps_updata(&Lierda_SysValue.gpsInfo.Position,&Lierda_SysValue.gpsInfo.longitude,&Lierda_SysValue.gpsInfo.latitude);
							Lierda_SysValue.gpsInfo.SerialNum=Lierda_SysValue.GpsDataNum;
							Lierda_SysValue.gpsInfo.SignalQuality=0x01;
//							lierdaLog(" longitude: %#x\r\n",Lierda_SysValue.gpsInfo.longitude);
//							lierdaLog(" latitude: %#x\r\n",Lierda_SysValue.gpsInfo.latitude);
							Lierda_SysValue.gpsInfo.longitude=BigtoLittle32(Lierda_SysValue.gpsInfo.longitude);
							Lierda_SysValue.gpsInfo.latitude=BigtoLittle32(Lierda_SysValue.gpsInfo.latitude);
							memcpy(GpsDtaBuff+((Lierda_SysValue.GpsDataNum-1)*GPSDATAPACK_LEN),&Lierda_SysValue.gpsInfo,GPSDATAPACK_LEN);
							if(Lierda_SysValue.GpsDataNum==10)
							{
								Lierda_SysValue.GpsDataNum=0;
								Lierda_SysValue.GpsDataNumFullFlag=1;
							}
						}
					}
				}

//				lierdaLog(" GPS_RMC: %s\r\n",Usrt_buff);
			    memset(Usrt_buff, 0, USRT_SIZE);
			    Usrt_buff_len = 0;
		    }
		}
	}
}

/********************************************************
 *����: void lierda_USRT_task(void *argument)
 *���: None
 *����: None
 *����: ���ڽ��������̣߳����ڴ��������ݽ���
 ********************************************************/
void lierda_USRT_task(void *argument)
{
	UNUSED(argument);
	osDelay(500);  //����ʱ�ȴ�ģ���ʼ�����
	memset(Usrt_buff, 0, USRT_SIZE);  // ���BUFF
	Usrt_buff_len = 0;
	over_buff_len = 0;
	uart3_timer_tick();  // ����UART3�����ʱ�����ճ�ʱ
	for(;;)
	{
        memset(Trans_buff, 0, TRANS_SIZE);
        Trans_buff_len = 0;
		lierdaUARTReceive(&lierdaUARTHandle, Trans_buff, &Trans_buff_len, 0xffffffff);

		if (Trans_buff_len > 0)
		{
			if (UartData_Start == 0)
			{
				UartData_Start = 1;
				if (osTimerStart(uart3_tick_timer, UART3_TICK_TIMEOUT)) // ������ʱ��
				{
					lierdaLog("uart3_tick_timer start fail\r\n");
				}
				over_buff_len = 0;
				memset(Usrt_buff, 0, USRT_SIZE);  // ���BUFF
				Usrt_buff_len = 0;
			}

			timer_count = 0;      //�������������
			over_buff_len += Trans_buff_len;

			if (over_buff_len >= USRT_SIZE-1)   // ��ֹBuff��� 190102
			{
				over_buff_len = 0;
				memset(Usrt_buff, 0, USRT_SIZE);
				Usrt_buff_len = 0;
			}
			memcpy(Usrt_buff+Usrt_buff_len, Trans_buff, Trans_buff_len);
			Usrt_buff_len += Trans_buff_len;
		}
	    osDelay(10);  // ��Ҫ����Ҫ����ʱ������������
	    (void) osThreadYield();  // ����һ�Σ��л������л�����������б������ȼ���ߵ��Ǹ�����
	}
}


/**  $GNRMC,062522.000,A,3016.72270,N,11959.31682,E,0.001,93.20,051118,,,A*7B  **/

/********************************************************
 *����: uint32 iRMC_decode(char* buff,uint32 len)
 *���: None
 *����: None
 *����: GPS�������ݽ���
 ********************************************************/
uint32 iRMC_decode(char* buff,uint32 len)
{
    uint32 temp_len=0;
    char  temp[20];

    len=len-7;
    buff=buff+7;

    //char	UTC_Time[20];			//Current time	hhmmss.sss
    if(len>0)
    {
        temp_len=Get_NEMA_Form(buff,temp,len);
        if(temp_len!=0)
        {
			for (uint8 i = 0; i < temp_len; i++)
			{
				GPSData.UTC_Time[i] = temp[i];
			}
			len = len - temp_len;
			buff = buff + temp_len;
		}
        else
        {
            return 0;
        }
    }

	//Valid_status;			//V = Data Invalid / Receiver Warning, A=Data Valid
	if (len > 0)
	{
		temp_len = Get_NEMA_Form(buff, temp, len);
		if (temp_len != 0)
		{
			GPSData.Valid_status = temp[0];
			len = len - temp_len;
			buff = buff + temp_len;
		}
		else
		{
			return 0;
		}
	}

    //Latitude[20];			//User datum latitude degrees, minutes, decimal minutes format
    if(len>0)
    {
        temp_len=Get_NEMA_Form(buff,temp,len);
        if(temp_len!=0)
        {
            if(temp_len>2)
            {
				for (uint8 i = 0; i < temp_len; i++)
				{
					GPSData.Latitude[i] = temp[i];   // γ��
				}
            }
            len=len-temp_len;
            buff=buff+temp_len;
        }
        else
        {
            return 0;
        }
    }

    //NS_indicator;
	if (len > 0)
	{
		temp_len = Get_NEMA_Form(buff, temp, len);
		if (temp_len != 0)
		{
			GPSData.NS_indicator = temp[0];
			len = len - temp_len;
			buff = buff + temp_len;
		}
		else
		{
			return 0;
		}
	}

    //Longitude[20];			//User datum latitude degrees, minutes, decimal minutes format
    if(len>0)
    {
        temp_len=Get_NEMA_Form(buff,temp,len);
        if(temp_len!=0)
        {
			if (temp_len > 2)
			{
				for (uint8 i = 0; i < temp_len; i++)
				{
					GPSData.Longitude[i] = temp[i];   // ����
				}
			}
            len=len-temp_len;
            buff=buff+temp_len;
        }
        else
        {
            return 0;
        }
    }

    //EW_indicator;			//E/W indicator  'E'= East, or 'W' = West
    if(len>0)
    {
    	temp_len=Get_NEMA_Form(buff,temp,len);
    	if(temp_len!=0)
    	{
    		GPSData.EW_indicator=temp[0];
    		len=len-temp_len;
    		buff=buff+temp_len;
    	}
    	else
    	{
    		return 0;
    	}
    }

    //Spd;					//Speed  Speed Over Ground
    if(len>0)
   	{
    	temp_len=Get_NEMA_Form(buff,temp,len);
    	if(temp_len!=0)
    	{
    		for (uint8 i = 0; i < temp_len; i++)
    		{
    			GPSData.Spd[i] = temp[i];
    		}
//    		strncpy(RMCData.Spd,(const char *)temp,temp_len);
    		len=len-temp_len;
    		buff=buff+temp_len;
    	}
    	else
    	{
    		return 0;
    	}
    }

    //cog;					//COG  Course Over Ground
    if(len>0)
    {
    	temp_len=Get_NEMA_Form(buff,temp,len);
    	if(temp_len!=0)
    	{
    		for(uint8 i = 0; i < temp_len; i++)
    		{
    			GPSData.cog[i] = temp[i];
    		}
//    		strncpy(RMCData.cog,(const char *)temp,temp_len);
    		len=len-temp_len;
    		buff=buff+temp_len;
    	}
    	else
    	{
    		return 0;
    	}
    }

    //char	Date[6];				//Current Date in Day, Month Year format ddmmyy
    if(len>0)
   	{
    	temp_len=Get_NEMA_Form(buff,temp,len);
    	if(temp_len!=0)
    	{
    		for (uint8 i = 0; i < temp_len; i++)
    		{
    			GPSData.Date[i] = temp[i];
    		}
    		len=len-temp_len;
    		buff=buff+temp_len;
    	}
    	else
    	{
    		return 0;
    	}
    }
    return 1;
}

uint32 Get_NEMA_Form(char* source,char* result,uint32 len)
{
	uint32	i;
	if(*source=='*'||*source=='$')		//with no message head,*=checksum,$=start all is end
		return 0;
	for(i=1;i<=len;i++)
	{
		if(*source==',')
		{
			*result=0;
			return	i;
		}
		if(*source=='*')
		{
			*result=0;
			return	i;
		}
		*result=*source;
		result++;
		source++;
	}
	return	0;
}





