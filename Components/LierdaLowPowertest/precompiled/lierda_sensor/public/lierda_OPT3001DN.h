/******************************************************************************
 * @内容	OPT3001DN光照传感器头文件
 * @设计	Lierda NB-IoT 软件设计团队@2018
******************************************************************************/

#ifndef SRC_APP_REFERENCE_APPLICATION_CORE_OPT3001DN_H_
#define SRC_APP_REFERENCE_APPLICATION_CORE_OPT3001DN_H_

#include "neulfw.h"

#define OPT3001_RESULT		     0x00
#define OPT3001_CONFIGURATION	 0x01
#define OPT3001_LOW_LIMIT   	 0x02
#define OPT3001_HIGH_LIMIT  	 0x03
#define OPT3001_MANUFACTURER_ID	 0x7e
#define OPT3001_DEVICE_ID     	 0x7f

#define OPT3001DN_I2C_ADDRESS    0x88

#define OPT3001DN_MANUFACTURER_ID   0x5449
#define OPT3001DN_DEVICE_IDNum      0x3001

/******************************************************************************
* @函数名	OPT3001DN初始化函数
* @参数	无
* @返回值   1：成功  0：失败
******************************************************************************/
uint8 lierda_OPT3001_Init(void);

/******************************************************************************
* @函数名	获取光照数据函数
* @参数	*Lux  : 光照整数部分地址
* @返回值  无
******************************************************************************/
void lierda_OPT3001_UpdataInfo(uint32 *Lux);

#endif /* SRC_APP_REFERENCE_APPLICATION_CORE_OPT3001DN_H_ */



