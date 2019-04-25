
#include "LierdaVbatTest.h"


/******************************************************************************
* @函数名 Vbat脚电压采集初始化函数
* @参数	param : 空参数
* @返回值  无
******************************************************************************/
void VbatSampInit(void)
{
	lierdaADCInit();  //ADC初始化
	lierdaAIOCalibrateADC();  //电压校准
}

/******************************************************************************
* @函数名 Vbat脚电压采集函数
* @参数	param : 空参数
* @返回值  无
******************************************************************************/
void VbatSampTest(void)
{
	int16 Temp=0;uint32 Vbat=0;
	if(lierdaAIOTempVolt(&Temp,&Vbat)==AIO_FUNC_RET_OK)
		lierdaLog("Vbat脚电压为：%d mV",Vbat);
	else
		lierdaLog("Vbat脚电压采样失败");
}
