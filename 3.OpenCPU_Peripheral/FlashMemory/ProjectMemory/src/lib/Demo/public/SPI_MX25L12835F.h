/******************************************************************************
 * @内容	SPI测试函数   MX25L12835F的读写操作头文件
 * @设计	Lierda NB-IoT 软件设计团队@2018
******************************************************************************/

#ifndef SRC_LIB_DEMO_PUBLIC_SPI_MX25L12835F_H_
#define SRC_LIB_DEMO_PUBLIC_SPI_MX25L12835F_H_

//include
#include "lierdaSPIsoft.h"
#include "lierdaSPI.h"
#include "lierdaGPIO.h"
#include "neulfw.h"
#include "lierda_app_main.h"
#include "string.h"

#define USESOFTSPI 0  //定义是否使用软件模拟SPI口       0:硬件SPI    1：软件SPI
#define SPI_CS     PIN_27
#define SPI_SCK    PIN_28
#define SPI_MISO   PIN_31
#define SPI_MOSI   PIN_32
#define SPI_CS_ENABLE()     lierdaGPIOClear(SPI_CS);
#define SPI_CS_DISABLE()     lierdaGPIOSet(SPI_CS);

#define SPI_FLASH_PageSize              256
#define SPI_FLASH_PerWritePageSize      256
#define W25X_WriteEnable		            0x06
#define W25X_WriteDisable		            0x04
#define W25X_ReadStatusReg		          0x05
#define W25X_WriteStatusReg		          0x01
#define W25X_ReadData			              0x03
#define W25X_FastReadData		            0x0B
#define W25X_FastReadDual		            0x3B
#define W25X_PageProgram		            0x02
#define W25X_BlockErase			            0xD8
#define W25X_SectorErase		            0x20
#define W25X_ChipErase			            0xC7
#define W25X_PowerDown			            0xB9
#define W25X_ReleasePowerDown	          0xAB
#define W25X_DeviceID			              0xAB
#define W25X_ManufactDeviceID   	      0x90
#define W25X_JedecDeviceID		          0x9F
#define WIP_Flag                        0x01  /* Write In Progress (WIP) flag */

#define Dummy_Byte                      0xFF

#define FLASH_SectorToErase   0x000000
#define FLASH_WriteAddress    FLASH_SectorToErase
#define FLASH_ReadAddress     FLASH_SectorToErase

#define countof(a)      (sizeof(a) / sizeof(*(a)))
#define TxBufferSize1   (countof(TxBuffer1) - 1)
#define RxBufferSize1   (countof(TxBuffer1) - 1)
#define BufferSize      (countof(Tx_Buffer)-1)

void Lierda_SPITest(void);
void MX25L12835F_spiInit(void);
uint32 SFLASH_ReadID(void);
void SPI_FLASH_WriteEnable(void);
void SPI_FLASH_WaitForWriteEnd(void);
void SPI_FLASH_SectorErase(uint32 SectorAddr);
void SPI_FLASH_PageWrite(uint8* pBuffer, uint32 WriteAddr, uint16 NumByteToWrite);
void SPI_FLASH_BufferWrite(uint8* pBuffer, uint32 WriteAddr, uint16 NumByteToWrite);
void SPI_FLASH_BufferRead(uint8* pBuffer, uint32 ReadAddr, uint16 NumByteToRead);



#endif /* SRC_LIB_DEMO_PUBLIC_SPI_MX25L12835F_H_ */
