/*
 * lierdaADC.h
 *
 *  Created on: 2018年10月15日
 *      Author: Def_Lin
 */

#ifndef SRC_LIB_LIERDAADC_PUBLIC_LIERDAADC_H_
#define SRC_LIB_LIERDAADC_PUBLIC_LIERDAADC_H_

#include "aio_functions.h"

typedef enum{

	LIERDA_ADC_OK   			=  	0,
	LIERDA_ADC_FAILED			=	-1,
	LIERDAS_ERROR_BAD_PARAMS	=	-3,

}LIERDA_ADC_RET;



/******************************************************************************
 * @函数名:lierdaADCInit，用于初始化ADC
 * @参数:无
 * @返回值:若成功，返回AIO_FUNC_RET_OK
 * 		 若失败，返回AIO_FUNC_RET_ERROR
 * @重要修改记录:180830，Def创建函数
******************************************************************************/
extern LIERDA_ADC_RET lierdaADCInit(void);

/******************************************************************************
 * @函数名:lierdaADCDeinit，用于取消初始化ADC
 * @参数:无
 * @返回值:若成功，返回AIO_FUNC_RET_OK
 * 		 若失败，返回AIO_FUNC_RET_ERROR
 * @重要修改记录:180830，Def创建函数
******************************************************************************/
extern LIERDA_ADC_RET lierdaADCDeinit(void);


/******************************************************************************
 * @函数名:lierdaADCGetRaw，用于获取当前vbat电压的原始数值
 * @参数:读取到的数值
 * @返回值:若成功，返回AIO_FUNC_RET_OK
 * 		 若失败，返回AIO_FUNC_RET_ERROR
 * @重要修改记录:180830，Def创建函数
******************************************************************************/
extern LIERDA_ADC_RET lierdaADCGetRaw(uint32 *voltage);


/******************************************************************************
 * @函数名:lierdaReadAIOPin，用于获取当前PIO的电压
 * @参数:uint32 *voltage 获取到的电压值
 * 		uint8 aio_pin_number 所要获取电压的引脚
 * @返回值:若成功，返回AIO_FUNC_RET_OK
 * 		 若失败，返回AIO_FUNC_RET_ERROR
 * @重要修改记录:180830，Def创建函数
******************************************************************************/
extern AIO_FUNC_RET lierdaReadAIOPin(uint32 *voltage, uint8 aio_pin_number);


/******************************************************************************
 * @函数名:lierdaAIOCalibrateADC，用于电压的校准。
 * @参数:无
 * @返回值:若成功，返回AIO_FUNC_RET_OK
 * 		 若失败，返回AIO_FUNC_RET_ERROR
 * @重要修改记录:180830，Def创建函数
******************************************************************************/
extern AIO_FUNC_RET lierdaAIOCalibrateADC(void);


/******************************************************************************
 * @函数名:lierdaAIOTempVolt，用于获取VBat的电压，以及当前温度。
 * @参数:int16 *temp：温度的数值；
 * 		 uint32 *voltage：电压的数值
 * @返回值:若成功，返回AIO_FUNC_RET_OK
 * 		 若失败，返回AIO_FUNC_RET_ERROR
 * @重要修改记录:180830，Def创建函数
******************************************************************************/
extern AIO_FUNC_RET lierdaAIOTempVolt(int16 *temp,uint32 *voltage);

#endif /* SRC_LIB_LIERDAADC_PUBLIC_LIERDAADC_H_ */
