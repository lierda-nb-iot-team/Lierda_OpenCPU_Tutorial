/*
 * lierdaDAC.h
 *
 *  Created on: 2018年10月31日
 *      Author: Def_Lin
 */

#ifndef SRC_LIB_LIERDADAC_PUBLIC_LIERDADAC_H_
#define SRC_LIB_LIERDADAC_PUBLIC_LIERDADAC_H_

#include <string.h>
#include <stdlib.h>
#include "neulfw.h"
#include "aio_manager.h"
#include "aio_pin.h"
#include "dac.h"


typedef enum{

	LIERDA_DAC_OK   			=  	0,
	LIERDA_DAC_FAILED			=	-1,
	LIERDAS_DAC_ERROR_BAD_PARAMS	=	-3,

}LIERDA_DAC_RET;


/******************************************************************************
 * @函数名:lierdaDACInit，用于初始化DAC
 * @参数:无
 * @返回值:若成功，返回LIERDA_DAC_OK
 * 		 若失败，返回LIERDA_DAC_FAILED或者LIERDAS_DAC_ERROR_BAD_PARAMS
 * @重要修改记录:180830，Def创建函数
******************************************************************************/
LIERDA_DAC_RET lierdaDACInit(void);


/******************************************************************************
 * @函数名:lierdaDACDeinit，用于取消初始化DAC
 * @参数:无
 * @返回值:若成功，返回LIERDA_DAC_OK
 * 		 若失败，返回LIERDA_DAC_FAILED或者LIERDAS_DAC_ERROR_BAD_PARAMS
 * @重要修改记录:180830，Def创建函数
******************************************************************************/
LIERDA_DAC_RET lierdaDACDeinit(void);


/******************************************************************************
 * @函数名:lierdaDACWriteRaw，用于输出DAC值
 * @参数:uint32 value：输出的值，范围(0-1023)
 * @返回值:若成功，返回LIERDA_DAC_OK
 * 		 若失败，返回LIERDA_DAC_FAILED或者LIERDAS_DAC_ERROR_BAD_PARAMS
 * @重要修改记录:180830，Def创建函数
******************************************************************************/
LIERDA_DAC_RET lierdaDACWriteRaw(uint32 value);


/******************************************************************************
 * @函数名:lierdaDACConnect，用于连接到AIO引脚
 * @参数:uint32 aio：要连接的AIO引脚号（0或1）
 * @返回值:若成功，返回LIERDA_DAC_OK
 * 		 若失败，返回LIERDA_DAC_FAILED或者LIERDAS_DAC_ERROR_BAD_PARAMS
 * @重要修改记录:180830，Def创建函数
******************************************************************************/
LIERDA_DAC_RET lierdaDACConnect(uint32 aio);

/******************************************************************************
 * @函数名:lierdaDACSetRange，用于设置DAC电压范围
 * @参数:DAC_VOLTAGE_RANGE range：需要设置的范围0-3,0对应1.2V，1对应2V，2对应2.8V，3对应3.6V
 * @返回值:若成功，返回LIERDA_DAC_OK
 * 		 若失败，返回LIERDA_DAC_FAILED或者LIERDAS_DAC_ERROR_BAD_PARAMS
 * @重要修改记录:180830，Def创建函数
******************************************************************************/
LIERDA_DAC_RET lierdaDACSetRange(DAC_VOLTAGE_RANGE range);


#endif /* SRC_LIB_LIERDADAC_PUBLIC_LIERDADAC_H_ */
