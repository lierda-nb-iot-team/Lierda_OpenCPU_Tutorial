/*
 * HD_GPS.c
 *
 *  Created on: 2019年4月25日
 *      Author: Administrator
 */
#include "HD_GPS.h"

UART_HandleTypeDef  UARTHandle;
uint8 GpsDataBuff[GPSDATALENMAX];
uint8 UartDataBuff[GPSDATALENMAX];
uint16 GpsDataLen=0;
uint16 UartDataLen=0;
uint16 GpsDataLenoverflag=0;
uint8 DataStart=0;
uint8 DataEnd=0;
uint8 Timercount=0;
GPSRMCStruct  Gps_Data;
void GPS_uart_init(void);
void Gps_data_clear(void);
uint32 Get_NEMA_Form(char* source,char* result,uint32 len);
/******************************************************************************
* @函数名	串口接收任务线程，用于处理串口数据接收
* @参数	    param : 空参数，无效
* @返回值  无
******************************************************************************/
void lierda_Gps_task(void *argument)
{
	UNUSED(argument);
	osDelay(500);  //加延时等待模组初始化完成
	GPS_uart_init();//串口初始化
	osTimerStart(LierdaTimer_handle,30);//启动一个30ms定时器
	Gps_data_clear();
	for(;;)
	{
		lierdaUARTReceive(&UARTHandle,UartDataBuff, &UartDataLen, 0xffffffff);//串口接收数据
		if(UartDataLen>3)
		{
			if(DataStart==0)
				DataStart=1;//开始接收数据
			Timercount=0;//定时器标志清零
			GpsDataLenoverflag=GpsDataLenoverflag+UartDataLen; //GPS数据缓冲区溢出标志
			if(GpsDataLenoverflag<GPSDATALENMAX-1)
			{
				memcpy(GpsDataBuff+GpsDataLen,UartDataBuff,UartDataLen);//串口缓冲区数据放进GPS数据缓冲区
				GpsDataLen=GpsDataLen+UartDataLen;
			}
			else
			{
				GpsDataLenoverflag=0;
				Gps_data_clear();
			}
            UartDataLen=0;
            memset(UartDataBuff,0,GPSDATALENMAX);
		}
		osDelay(10);
	}

}

/******************************************************************************
* @函数名	UART初始化
* @参数	    param : 空参数，无效
* @返回值       无
******************************************************************************/
void GPS_uart_init(void)
{
	UARTHandle.baudrate  = 9600;
	UARTHandle.data_bits = UART_DATA_BITS_8;
	UARTHandle.parity    = UART_PARITY_NONE;
	UARTHandle.stopbits  = UART_STOP_BITS_1;
	UARTHandle.rx_pin    = RX_pin;
	UARTHandle.tx_pin    = TX_pin;
	lierdaUARTInit(&UARTHandle);
}

void Gps_data_clear(void)
{
	memset(GpsDataBuff,0,GPSDATALENMAX);
	GpsDataLen=0;
	GpsDataLenoverflag=0;
}

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
				Gps_Data.UTC_Time[i] = temp[i];
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
			Gps_Data.Valid_status = temp[0];
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
					Gps_Data.Latitude[i] = temp[i];   // 纬度
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
			Gps_Data.NS_indicator = temp[0];
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
					Gps_Data.Longitude[i] = temp[i];   // 经度
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
    		Gps_Data.EW_indicator=temp[0];
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
    			Gps_Data.Spd[i] = temp[i];
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
    			Gps_Data.cog[i] = temp[i];
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
    			Gps_Data.Date[i] = temp[i];
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
