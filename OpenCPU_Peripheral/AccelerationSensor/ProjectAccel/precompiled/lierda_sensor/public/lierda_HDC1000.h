/******************************************************************************
 * @内容	温湿度传感器相关驱动头文件
 * @设计	Lierda NB-IoT 软件设计团队@2018
******************************************************************************/

#ifndef SRC_APP_REFERENCE_APPLICATION_CORE_HDC1000_H_
#define SRC_APP_REFERENCE_APPLICATION_CORE_HDC1000_H_

#include "neulfw.h"
#include "lierdaI2C.h"

typedef struct
{
  uint8   Serial_ID[6];   //5字节16进制数据
  uint16   Manufacture;
  uint16   Device_ID;
  uint16   Config_Val;
  int16  Temperature;
  int16  Humidity;
}USER_THS_DEV_Typedef;
/////////计算公式///////////////////////////////////////////
//temper=[(d15:d0)/2^16]*165c-40c
//relative=[(d15:d0)/2^16]*100%
///////////HDC1000寄存器说明////////////////////////////////

#define HDC1000_I2C_ADDRESS         0x80//0x81 0x82 0x83
#define HDC1000_Read_Temperature    0x00
#define HDC1000_Read_Humidity       0x01
#define HDC1000_Read_Conf           0x02

#define HDC1000_DEVICE_ID           0xff
#define HDC1000_ID                  0x1000
//////////////////////////////////////////////////////////////
#define HDC1000_Rst                 15//0x8000软复位
#define HDC1000_Enht                13//0x2000//使能加热
#define HDC1000_Mode                12//0x1000//工作模式-为0时分开来读，为1时可以连续读温度在前
#define HDC1000_Trest               10//0x0000  0为温度14bit 1为11bit
#define HDC1000_Rhres               8 //0x0000 14 11 7bit 温度

/********************************************************
 *函数: uint8 lierda_HDC1000_Init(void);
 *入口: None
 *出口: None
 *概述: HDC1000初始化, 成功 返回 1，失败返回 0
 ********************************************************/
uint8 lierda_HDC1000_Init(void);

/********************************************************
 *函数: void lierda_HDC1000_UpdateInfo
 *入口: None
 *出口: None
 *概述: 用户获取HDC1000数据，温度，湿度（有符号整型）
 ********************************************************/
void lierda_HDC1000_UpdateInfo(int16 *Temper,int16 *Humidity);

/********************************************************
 *函数: void lierda_sensor_I2C_init
 *入口: SCL_pin, SDA_pin
 *出口: None
 *概述: 用户初始化I2C接口函数
 ********************************************************/
void lierda_sensor_I2C_init(uint8 SCL_pin, uint8 SDA_pin);

#endif /* SRC_APP_REFERENCE_APPLICATION_CORE_HDC1000_H_ */

