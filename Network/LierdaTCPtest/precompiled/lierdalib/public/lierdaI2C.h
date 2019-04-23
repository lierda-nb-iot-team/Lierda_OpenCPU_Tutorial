
#ifndef SRC_LIB_LIERDAI2C_PUBLIC_LIERDAI2C_H_
#define SRC_LIB_LIERDAI2C_PUBLIC_LIERDAI2C_H_

#include "neulfw.h"
#include "i2c.h"



typedef enum
{
  HAL_OK       = 0x00,
  HAL_ERROR    = 0x01,
  HAL_BUSY     = 0x02,
  HAL_TIMEOUT  = 0x03
} HAL_StatusTypeDef;



typedef struct
{
	I2C_BUS       				i2c_bus;
	uint8         				pin_scl;
	uint8         				pin_sda;
	HAL_I2C_ADDRESS_TYPE   		i2c_address_type;
	uint16						i2c_half_time;
	HAL_I2C_BUS_MODE			i2c_mode;
}I2C_HandleTypeDef;

/******************************************************************************
 * @函数名:lierdaI2CInit，用于初始化i2c
 * @参数:I2C_HandleTypeDef *hi2c初始化的配置句柄
 * @返回值:成功返回HAL_OK
 * 失败返回HAL_ERROR
 * @重要修改记录:180830，Def创建函数
******************************************************************************/
HAL_StatusTypeDef lierdaI2CInit(I2C_HandleTypeDef *hi2c);
/******************************************************************************
 * @函数名:lierdaI2CReadreg，用于i2c读取寄存器值
 * @参数:*hi2c 配置句柄，
 * 		i2c_slave_addr 传感器地址，
 * 		i2c_rx_reg_addr 所要读取的寄存器地址，
 * 		*data 读取的数值，
 * 		len 读取的长度，
 * 		readOnly 是否只读不发送寄存器地址
 * @返回值:若读取成功返回0，失败返回1
 * @重要修改记录:180830，Def创建函数
******************************************************************************/
uint8 lierdaI2CReadreg(I2C_HandleTypeDef *hi2c,uint8 i2c_slave_addr,uint16 i2c_rx_reg_addr, uint8 *data, uint8 len,uint8 readOnly);

/******************************************************************************
 * @函数名:lierdaI2CWritereg，用于i2c写入寄存器值
 * @参数:*hi2c 配置句柄，
 * 		i2c_slave_addr 传感器地址，
 * 		i2c_rx_reg_addr 所要写入的寄存器地址，
 * 		*data 写入的数值，
 * 		len 读取的长度
 * @返回值:若读取成功返回0，失败返回1
 * @重要修改记录:180830，Def创建函数
******************************************************************************/
uint8 lierdaI2CWritereg(I2C_HandleTypeDef *hi2c,uint8 i2c_slave_addr, uint8 i2c_tx_reg_addr,uint8 *data,uint8 len);

/******************************************************************************
 * @函数名:lierdaI2CRead，用于i2c读取寄存器值
 * @参数:*hi2c 配置句柄，
 * 		i2c_slave_addr 传感器地址，
 * 		*data 读取的数值，
 * 		data_len 读取的长度，
 * @返回值:若读取成功返回0，失败返回1
 * @重要修改记录:180830，Def创建函数
******************************************************************************/
I2C_RET lierdaI2CRead(I2C_HandleTypeDef *hi2c,uint8 i2c_slave_addr,uint8 *data, uint8 data_len);

/******************************************************************************
 * @函数名:lierdaI2CWrite，用于i2c写入寄存器值
 * @参数:*hi2c 配置句柄，
 * 		i2c_slave_addr 传感器地址，
 * 		i2c_rx_reg_addr 所要写入的寄存器地址，
 * 		*data 写入的数值（若往寄存器中写入数值，则将寄存器地址置于首位，后面跟要写入的数值）
 * 		data_len 写入的长度（该长度包括寄存器地址）
 * @返回值:若读取成功返回0，失败返回1
 * @重要修改记录:180830，Def创建函数
******************************************************************************/
I2C_RET lierdaI2CWrite(I2C_HandleTypeDef *hi2c,uint8 i2c_slave_addr,uint8 *data,uint8 data_len);

/******************************************************************************
 * @函数名:lierdaI2CDeinit，用于取消初始化i2c
 * @参数:*hi2c初始化配置句柄
 * @返回值:成功返回0，失败返回1
 * @重要修改记录:180830，Def创建函数
******************************************************************************/
uint8 lierdaI2CDeinit(I2C_HandleTypeDef *hi2c);





#endif /* SRC_LIB_LIERDAI2C_PUBLIC_LIERDAI2C_H_ */
