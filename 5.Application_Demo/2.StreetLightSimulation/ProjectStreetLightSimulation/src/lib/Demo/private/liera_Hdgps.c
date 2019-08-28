/*
 * lierda_gps.c
 *
 *  Created on: 2018/11/06
 *      Author: LUO
 */

#include <Lierda_Hdgps.h>
#include "lierda_gps.h"
#include <stdio.h>
#include "string.h"
#include <stdlib.h>
#include "neulfw.h"
#include "lierda_app_main.h"
#include "cmsis_os2.h"
//#include "..coap/public/mem.h"



GPS_DATE  HA_GPSData={0};
static double atof_gps(const char *s);
static int is_digit(char ch);

/********************************************************
 *函数: void usart_init(void)
 *入口: None
 *出口: None
 *概述: 串口初始化函数
 ********************************************************/
void usart_init(void)
 {
	lierda_user_GPS_uart_init(UART_BAUD, RX_PIN, TX_PIN);
	 lierda_GPS_task_enable();
}


static int is_digit(char ch)
{
    if(ch>='0'&&ch<='9')
        return 1;
    else
        return 0;
}

static double atof_gps(const char *s)
{
    double power,value;
    int i=0;
    int sign=0;
    //assert(s!=NULL);//判断字符串是否为空
    //for(i=0;is_space(s[i]);i++);//除去字符串前的空格
    sign=(s[i]=='-')?-1:1;
    if(s[i]=='-'||s[i]=='+')//要是有符号位就前进一位
        i++;
    for(value=0.0;is_digit(s[i]);i++)//计算小数点钱的数字
        value=value*10.0+(s[i]-'0');
    if(s[i]=='.')
        i++;
    for(power=1.0;is_digit(s[i]);i++)//计算小数点后的数字
    {
        value=value*10.0+(s[i]-'0');
        power*=10.0;
    }
    return sign*value/power;
}
void gps_updata(uint8 *EW_data,uint32 *Longitude_data,uint32 *Latitude_data)
{
	memset(&HA_GPSData, 0 ,sizeof(GPSRMCStruct));
	lierda_GPS_data_get((GPSRMCStruct *)&HA_GPSData);
	  if(HA_GPSData.Valid_status=='A')
	{
		  float wf=  atof_gps(HA_GPSData.Latitude)/100;
		  float jf=   atof_gps(HA_GPSData.Longitude)/100;
		  int32 wd=(int32)wf;
		  int32 jd=(int32)jf;
		  wf=(((wf-wd)*100))*10000000/60;
		  jf=((jf-jd)*100)*10000000/60;
		  wd*=10000000;
		  jd*=10000000;
		  wf+=wd;
		  jf+=jd;
		if (HA_GPSData.EW_indicator == 'W')
			*EW_data = 0x01;
		else
			*EW_data = 0x00;
		if (HA_GPSData.NS_indicator == 'N')
			*EW_data = 0x10 |*EW_data;
		else
			*EW_data = *EW_data & 0xff;
		*Longitude_data = (uint32) (jf);
		*Latitude_data = (uint32) (wf);
//		 lierdaLog("GPS定位成功");
//		 lierdaLog("*EW_data:%x",*EW_data);
//		 lierdaLog("*Longitude_data:%x",*Longitude_data);
//		 lierdaLog("*Latitude_data:%x",*Latitude_data);
	}
	  else
	  {
		  //lierdaLog("GPS未定位成功，使用模拟数据");
		  *EW_data=0x10;
		  *Longitude_data =0x4784c880 ;  //0x4784c880  3016.71670,N,11959.30658,
		  *Latitude_data =0x120b5c60;  //0x120b5c60
	  }
}
