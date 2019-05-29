/*
 * lierdaSPI.h
 *
 *  Created on: 2018年10月18日
 *      Author: Def_Lin
 */

#ifndef SRC_LIB_LIERDASPI_PUBLIC_LIERDASPI_H_
#define SRC_LIB_LIERDASPI_PUBLIC_LIERDASPI_H_



#include "spi.h"
#include "hal_ssp.h"

SPI_BUS       spi_bus;

/******************************************************************************
 * @函数名:lierdaADCInit，用于初始化SPI
 * @参数:SPI_CONFIGURATION spi_config:SPI相关配置
 * 		SPI_PIN spi_pin：SPI引脚
 * @返回值:若成功，返回SPI_RET_OK
 * 		 若失败，返回SPI_RET_ERROR
 * @重要修改记录:180830，Def创建函数
******************************************************************************/
SPI_RET lierdaSPIInit(SPI_CONFIGURATION spi_config, SPI_PIN spi_pin);

/******************************************************************************
 * @函数名:lierdaSPIDeinit，用于取消初始化SPI
 * @参数:SPI_CONFIGURATION spi_config:SPI相关配置
 * 		SPI_PIN spi_pin：SPI引脚
 * @返回值:若成功，返回SPI_RET_OK
 * 		 若失败，返回SPI_RET_ERROR
 * @重要修改记录:180830，Def创建函数
******************************************************************************/
SPI_RET lierdaSPIDeinit(void);

/******************************************************************************
 * @函数名:lierdaSPISendData，用于写入SPI数据
 * @参数:SPI_BUS bus:声明的SPI总线
 * 		uint8* cmd_buff：命令buffer，对于某些不需要的设备使用时填NULL，对应的"cmd_len"也填0
 * 		uint16 cmd_len：命令长度
 * 		uint8* data_buff：写入的数据
 * 		uint16 data_len：写入的数据长度
 * 		SPI_CALLBACK callback：回调函数
 * @返回值:若成功，返回SPI_RET_OK
 * 		 若失败，返回SPI_RET_ERROR
 * @重要修改记录:180830，Def创建函数
******************************************************************************/
SPI_RET lierdaSPISendData(SPI_BUS bus, uint8* cmd_buff,uint16 cmd_len, uint8* data_buff, uint16 data_len, SPI_CALLBACK callback);


/******************************************************************************
 * @函数名:lierdaSPIRecvData，用于读取SPI数据
 * @参数:SPI_BUS bus:声明的SPI总线
 * 		uint8* cmd_buff：命令buffer，对于某些不需要的设备使用时填NULL，对应的"cmd_len"也填0
 * 		uint16 cmd_len：命令长度
 * 		uint8* data_buff：写入的数据
 * 		uint16 data_len：写入的数据长度
 * 		SPI_CALLBACK callback：回调函数
 * 		bool ignore_rx_while_tx：当发送时，是否忽略接收。一般填TRUE
 * @返回值:若成功，返回SPI_RET_OK
 * 		 若失败，返回SPI_RET_ERROR
 * @重要修改记录:180830，Def创建函数
******************************************************************************/
SPI_RET lierdaSPIRecvData(SPI_BUS bus, uint8* cmd_buff, uint16 cmd_len, uint8* data_buff, uint16 data_len, SPI_CALLBACK callback, bool ignore_rx_while_tx);

#endif /* SRC_LIB_LIERDASPI_PUBLIC_LIERDASPI_H_ */
