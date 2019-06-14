/*
 * LierdaAdcTest.c
 *
 *  Created on: 2019年4月25日
 *      Author: Administrator
 */
#include "LierdaAdcTest.h"

/******************************************************************************
* @函数名 ADC采样初始化
* @参数	param : 空参数
* @返回值  无
******************************************************************************/
void AdcSampInit(void)
{
	lierdaADCInit();  //ADC初始化
	lierdaAIOCalibrateADC();  //电压校准
}

/******************************************************************************
* @函数名 Vbat脚电压采集函数
* @参数	param : 空参数
* @返回值  无
******************************************************************************/
void AdcSampTest(void)
{
	uint32 Adc_voltage=0;
	if(lierdaReadAIOPin(&Adc_voltage, AIO0)==AIO_FUNC_RET_OK)
		lierdaLog("AIO0脚电压为：%d mV",Adc_voltage);
	else
		lierdaLog("AIO0脚电压采样失败");
	Adc_voltage=0;
	if(lierdaReadAIOPin(&Adc_voltage, AIO1)==AIO_FUNC_RET_OK)
		lierdaLog("AIO1脚电压为：%d mV",Adc_voltage);
	else
		lierdaLog("AIO1脚电压采样失败");
}

