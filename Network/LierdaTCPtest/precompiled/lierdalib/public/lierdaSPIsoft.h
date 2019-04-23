/******************************************************************************
 * @内容 lierda SPI驱动头文件
 * @设计 Lierda NB-IoT 软件设计团队@2018
******************************************************************************/

#ifndef SRC_LIB_LIERDASPI_PUBLIC_LIERDASPI_SOFT_H_
#define SRC_LIB_LIERDASPI_PUBLIC_LIERDASPI_SOFT_H_
//include
#include "lierdaGPIO.h"
#include "neulfw.h"
#include "lierda_app_main.h"

typedef enum
{
 LierdaSPI_RET_OK,
 LierdaSPI_RET_ERROR
}LierdaSPI_RET;

typedef struct
{
  uint32 Mode;               /*指定SPI操作模式 */
  uint32 DataSize;          /*指定SPI数据大小 */
  PIN LierdaSPI_CS;         /*定义SPI  CS引脚 */
  PIN LierdaSPI_SCK;       /*定义SPI  SCK引脚 */
  PIN LierdaSPI_MISO;      /*定义SPI  MISO引脚 */
  PIN LierdaSPI_MOSI;      /*定义SPI  MOSI引脚 */
}SPI_InitTypeDef;


/************************************************
函数名称 ： lierdaSPISoftInit
功    能 ： SPI初始化函数
参    数 ： *SPI_Init  SPI初始化句柄地址
返 回 值 ： 成功： LierdaSPI_RET_OK  失败：SPI_RET_ERROR
*************************************************/
uint8 lierdaSPISoftInit(SPI_InitTypeDef *SPI_Init);


/************************************************
函数名称 ： lierdaSPIWriteByte
功    能 ： SPI写一字节数据
参    数 ：*SPI_Init  SPI句柄地址     TxData  发送数据
返 回 值 ： 成功： LierdaSPI_RET_OK  失败：SPI_RET_ERROR
*************************************************/
uint8 lierdaSPIWriteByte(SPI_InitTypeDef *lierda_spi,uint8 TxData);

/************************************************
函数名称 ： lierdaSPIReadByte
功    能 ： SPI读一字节数据
参    数 ： *SPI_Init  SPI句柄地址
返 回 值 ： 读回来的字节数据
*************************************************/
uint8 lierdaSPIReadByte(SPI_InitTypeDef *lierda_spi);

/************************************************
函数名称 ： Lierda_SPIDeInit
功    能 ： SPI取消初始化函数
参    数 ： *SPI_Init  SPI初始化句柄地址
返 回 值 ：无
*************************************************/
void Lierda_SPIDeInit(SPI_InitTypeDef *SPI_Init);

#endif /* SRC_LIB_LIERDASPI_PUBLIC_LIERDASPI_SOFT_H_ */
