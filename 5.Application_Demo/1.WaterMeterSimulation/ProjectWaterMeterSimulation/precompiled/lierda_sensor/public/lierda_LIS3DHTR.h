/******************************************************************************
 * @内容	三轴传感器头文件
 * @设计	Lierda NB-IoT 软件设计团队@2018
******************************************************************************/

#ifndef SRC_APP_REFERENCE_APPLICATION_CORE_LIS3DHTR_H_
#define SRC_APP_REFERENCE_APPLICATION_CORE_LIS3DHTR_H_

#include "neulfw.h"

#define gssI2C_ADDRESS          0x30  // 7bit地址，SDO接地    0011000x
//Register Definition
#define LIS3DH_WHO_AM_I			0x0F  // device identification register
// CONTROL REGISTER 1
#define LIS3DH_CTRL_REG1		0x20
#define LIS3DH_ODR_BIT		    0x04
#define LIS3DH_LPEN				0x03

//CONTROL REGISTER 4
#define LIS3DH_CTRL_REG4		0x23
#define LIS3DH_HR				0x03
#define LIS3DH_FS				0x04

//INT1 REGISTERS
#define LIS3DH_INT1_THS                                0x32
#define LIS3DH_INT1_DURATION                           0x33

//INTERRUPT 1 CONFIGURATION
#define LIS3DH_INT1_CFG				                   0x30
#define LIS3DH_ANDOR                                   0x07
#define LIS3DH_INT_6D                                  0x06
#define LIS3DH_ZHIE                                    0x05
#define LIS3DH_ZLIE                                    0x04
#define LIS3DH_YHIE                                    0x03
#define LIS3DH_YLIE                                    0x02
#define LIS3DH_XHIE                                    0x01
#define LIS3DH_XLIE                                    0x00
//INT1_CFG bit mask
#define LIS3DH_INT1_AND                                0x80
#define LIS3DH_INT1_OR                                 0x00
#define LIS3DH_INT1_ZHIE_ENABLE                        0x20
#define LIS3DH_INT1_ZHIE_DISABLE                       0x00
#define LIS3DH_INT1_ZLIE_ENABLE                        0x10
#define LIS3DH_INT1_ZLIE_DISABLE                       0x00
#define LIS3DH_INT1_YHIE_ENABLE                        0x08
#define LIS3DH_INT1_YHIE_DISABLE                       0x00
#define LIS3DH_INT1_YLIE_ENABLE                        0x04
#define LIS3DH_INT1_YLIE_DISABLE                       0x00
#define LIS3DH_INT1_XHIE_ENABLE                        0x02
#define LIS3DH_INT1_XHIE_DISABLE                       0x00
#define LIS3DH_INT1_XLIE_ENABLE                        0x01
#define LIS3DH_INT1_XLIE_DISABLE                       0x00

//STATUS REGISTER bit mask
#define LIS3DH_STATUS_REG_ZYXOR                        0x80    // 1	:	new data set has over written the previous one
							// 0	:	no overrun has occurred (default)
#define LIS3DH_STATUS_REG_ZOR                          0x40    // 0	:	no overrun has occurred (default)
							// 1	:	new Z-axis data has over written the previous one
#define LIS3DH_STATUS_REG_YOR                          0x20    // 0	:	no overrun has occurred (default)
							// 1	:	new Y-axis data has over written the previous one
#define LIS3DH_STATUS_REG_XOR                          0x10    // 0	:	no overrun has occurred (default)
							// 1	:	new X-axis data has over written the previous one
#define LIS3DH_STATUS_REG_ZYXDA                        0x08    // 0	:	a new set of data is not yet avvious one
                                                        // 1	:	a new set of data is available
#define LIS3DH_STATUS_REG_ZDA                          0x04    // 0	:	a new data for the Z-Axis is not availvious one
                                                        // 1	:	a new data for the Z-Axis is available
#define LIS3DH_STATUS_REG_YDA                          0x02    // 0	:	a new data for the Y-Axis is not available
                                                        // 1	:	a new data for the Y-Axis is available
#define LIS3DH_STATUS_REG_XDA                          0x01    // 0	:	a new data for the X-Axis is not available

#define LIS3DH_DATAREADY_BIT                           LIS3DH_STATUS_REG_ZYXDA
//STATUS_REG_AXIES
#define LIS3DH_STATUS_REG			                   0x27
#define LIS3DH_ZYXOR                                   0x07
#define LIS3DH_ZOR                                     0x06
#define LIS3DH_YOR                                     0x05
#define LIS3DH_XOR                                     0x04
#define LIS3DH_ZYXDA                                   0x03
#define LIS3DH_ZDA                                     0x02
#define LIS3DH_YDA                                     0x01
#define LIS3DH_XDA                                     0x00
//INTERRUPT 1 SOURCE REGISTER
#define LIS3DH_INT1_SRC				                   0x31
#define MEMS_SET                                       0x01
#define MEMS_RESET                                     0x00
//OUTPUT REGISTER
#define LIS3DH_OUT_X_L					0x28
#define LIS3DH_OUT_X_H					0x29
#define LIS3DH_OUT_Y_L					0x2A
#define LIS3DH_OUT_Y_H					0x2B
#define LIS3DH_OUT_Z_L					0x2C
#define LIS3DH_OUT_Z_H					0x2D
typedef enum {
  LIS3DH_INT_MODE_OR                   =               0x00,
  LIS3DH_INT_MODE_6D_MOVEMENT          =               0x01,
  LIS3DH_INT_MODE_AND                  =               0x02,
  LIS3DH_INT_MODE_6D_POSITION          =               0x03
} LIS3DH_Int1Mode_t;
typedef enum {
  LIS3DH_ODR_1Hz		        =		0x01,
  LIS3DH_ODR_10Hz               =		0x02,
  LIS3DH_ODR_25Hz		        =		0x03,
  LIS3DH_ODR_50Hz		        =		0x04,
  LIS3DH_ODR_100Hz		        =		0x05,
  LIS3DH_ODR_200Hz		        =		0x06,
  LIS3DH_ODR_400Hz		        =		0x07,
  LIS3DH_ODR_1620Hz_LP		    =		0x08,
  LIS3DH_ODR_1344Hz_NP_5367HZ_LP   =	0x09
} LIS3DH_ODR_t;
typedef enum {
  LIS3DH_UP_SX                         =               0x44,
  LIS3DH_UP_DX                         =               0x42,
  LIS3DH_DW_SX                         =               0x41,
  LIS3DH_DW_DX                         =               0x48,
  LIS3DH_TOP                           =               0x60,
  LIS3DH_BOTTOM                        =               0x50
} LIS3DH_POSITION_6D_t;
typedef enum {
  LIS3DH_POWER_DOWN                    =		0x00,
  LIS3DH_LOW_POWER 		               =		0x01,
  LIS3DH_NORMAL			               =		0x02
} LIS3DH_Mode_t;
typedef enum {
  LIS3DH_FULLSCALE_2                   =               0x00,
  LIS3DH_FULLSCALE_4                   =               0x01,
  LIS3DH_FULLSCALE_8                   =               0x02,
  LIS3DH_FULLSCALE_16                  =               0x03
} LIS3DH_Fullscale_t;
typedef enum {
  LIS3DH_X_ENABLE                      =               0x01,
  LIS3DH_X_DISABLE                     =               0x00,
  LIS3DH_Y_ENABLE                      =               0x02,
  LIS3DH_Y_DISABLE                     =               0x00,
  LIS3DH_Z_ENABLE                      =               0x04,
  LIS3DH_Z_DISABLE                     =               0x00
} LIS3DH_AXISenable_t;
typedef struct {
  int16 AXIS_X;
  int16 AXIS_Y;
  int16 AXIS_Z;
  uint8 Current_Direction; //表示垂直向上的是传感器的那个面
  uint8 En_DebugInfo;
} AxesRaw_t;

/********************************************************
 *函数: uint8 lierda_LIS3DH_Init(void);
 *入口: None
 *出口: None
 *概述: LIS3DHTR初始化, 成功返回 1，失败返回 0
 ********************************************************/
uint8 lierda_LIS3DH_Init(void);

/********************************************************
 *函数: void lierda_LIS3DH_UpdateInfo
 *入口: *LIS3DH_X, *LIS3DH_Y, *LIS3DH_Z
 *出口: None
 *概述: 用户获取LIS3DHTR数据，三轴X方向，Y方向，Z方向数据（有符号整型）
 ********************************************************/
void lierda_LIS3DH_UpdateInfo(int16 *LIS3DH_X, int16 *LIS3DH_Y, int16 *LIS3DH_Z);

#endif /* SRC_APP_REFERENCE_APPLICATION_CORE_LIS3DHTR_H_ */


