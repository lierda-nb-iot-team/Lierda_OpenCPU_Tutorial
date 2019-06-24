/******************************************************************************
 * @内容	华大北斗HD8020相关函数
 * @设计	Lierda NB-IoT 软件设计团队@2018
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

uint16 Usrt_buff_len = 0;   // 一完整包长度
uint16 Trans_buff_len = 0;  // 一分包长度
uint16 over_buff_len = 0;   // 判断接收数据长度是否超BUFF

// UART3 接收任务句柄
osThreadId_t  USRTTaskHandle = NULL;
UART_HandleTypeDef  lierdaUARTHandle;   //GPS串口句柄
uint8 UartData_Start=0;
uint8 timer_count=0;

// UART3 接收超时定时器句柄
static osTimerId_t  uart3_tick_timer = NULL;
#define UART3_TICK_TIMEOUT  30   // 定时器超时30ms
void uart3_tick_timeout_callback(void *argument );
void uart3_timer_tick(void);

// GPS  串口波特率  RX TX
uint32 midBaudRate=0;
uint8  midRXpin=0;
uint8  midTXpin=0;



/********************************************************
 *函数: void lierda_GPS_task_enable(void)
 *入口: None
 *出口: None
 *概述: 创建并启动GPS任务线程
 ********************************************************/
void lierda_GPS_task_enable(void)
{
	osThreadAttr_t usrt_task_attr = {
										"lierda_USRT_task",  /*任务名称*/
										0,
										NULL,
										0,
										NULL,
										250,   /*任务堆栈大小*/
										11,    /*任务优先级*/
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
 *函数: void lierda_GPS_task_disable(void)
 *入口: None
 *出口: None
 *概述: 终止GPS任务线程执行
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
 *函数: void lierda_GPS_data_get( GPSRMCStruct  *p_gps_user )
 *入口: None
 *出口: None
 *概述: 用户获取GPS数据函数(结构体指针)
 ********************************************************/
void lierda_GPS_data_get( GPSRMCStruct  *p_gps_user )
{
	memcpy(p_gps_user, &GPSData, sizeof(GPSRMCStruct));
}


/********************************************************
 *函数: void lierda_GPS_uart_init(uint32 BaudRate, uint8 RX_pin, uint8 TX_pin)
 *入口: None
 *出口: None
 *概述: 串口初始化函数
 ********************************************************/
void lierda_GPS_uart_init(void)
{
//	UART_HandleTypeDef  lierdaUARTHandle;   //串口句柄
	lierdaUARTHandle.baudrate  = UART_BAUD;
	lierdaUARTHandle.data_bits = UART_DATA_BITS_8;
	lierdaUARTHandle.parity    = UART_PARITY_NONE;
	lierdaUARTHandle.stopbits  = UART_STOP_BITS_1;
	lierdaUARTHandle.rx_pin    = RX_PIN;
	lierdaUARTHandle.tx_pin    = TX_PIN;
	lierdaUARTInit(&lierdaUARTHandle);
}

/********************************************************
 *函数: void uart3_timer_tick
 *入口: None
 *出口: None
 *概述: 串口超时定时器创建
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
 *函数: void uart3_tick_timeout_callback
 *入口: None
 *出口: None
 *概述: 软件定时器回调函数
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
					if(GPSData.Valid_status=='A')//定位成功
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
 *函数: void lierda_USRT_task(void *argument)
 *入口: None
 *出口: None
 *概述: 串口接收任务线程，用于处理串口数据接收
 ********************************************************/
void lierda_USRT_task(void *argument)
{
	UNUSED(argument);
	osDelay(500);  //加延时等待模组初始化完成
	memset(Usrt_buff, 0, USRT_SIZE);  // 清除BUFF
	Usrt_buff_len = 0;
	over_buff_len = 0;
	uart3_timer_tick();  // 创建UART3软件定时器接收超时
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
				if (osTimerStart(uart3_tick_timer, UART3_TICK_TIMEOUT)) // 启动定时器
				{
					lierdaLog("uart3_tick_timer start fail\r\n");
				}
				over_buff_len = 0;
				memset(Usrt_buff, 0, USRT_SIZE);  // 清除BUFF
				Usrt_buff_len = 0;
			}

			timer_count = 0;      //定期器计数清空
			over_buff_len += Trans_buff_len;

			if (over_buff_len >= USRT_SIZE-1)   // 防止Buff溢出 190102
			{
				over_buff_len = 0;
				memset(Usrt_buff, 0, USRT_SIZE);
				Usrt_buff_len = 0;
			}
			memcpy(Usrt_buff+Usrt_buff_len, Trans_buff, Trans_buff_len);
			Usrt_buff_len += Trans_buff_len;
		}
	    osDelay(10);  // 重要，需要加延时，阻塞该任务
	    (void) osThreadYield();  // 调用一次，切换任务，切换到任务就绪列表上优先级最高的那个任务
	}
}


/**  $GNRMC,062522.000,A,3016.72270,N,11959.31682,E,0.001,93.20,051118,,,A*7B  **/

/********************************************************
 *函数: uint32 iRMC_decode(char* buff,uint32 len)
 *入口: None
 *出口: None
 *概述: GPS串口数据解析
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
					GPSData.Latitude[i] = temp[i];   // 纬度
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
					GPSData.Longitude[i] = temp[i];   // 经度
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





