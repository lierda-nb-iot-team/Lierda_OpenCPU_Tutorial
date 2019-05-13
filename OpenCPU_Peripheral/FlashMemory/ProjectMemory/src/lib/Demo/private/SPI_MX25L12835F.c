/******************************************************************************
 * @内容	SPI测试函数   MX25L12835F的读写操作
 * @设计	Lierda NB-IoT 软件设计团队@2018
******************************************************************************/
#include "SPI_MX25L12835F.h"

SPI_InitTypeDef SPI_MX25L12835F;

/************************************************
函数名称 ： MX25L12835F_spiInit
功    能 ： SPI初始化
参    数 ： 无
返 回 值 ： 无
*************************************************/
void MX25L12835F_spiInit(void)
{
#if USESOFTSPI
	SPI_MX25L12835F.DataSize=8;
	SPI_MX25L12835F.Mode=0;
	SPI_MX25L12835F.LierdaSPI_CS=SPI_CS;
	SPI_MX25L12835F.LierdaSPI_SCK=SPI_SCK;
	SPI_MX25L12835F.LierdaSPI_MISO=SPI_MISO;
	SPI_MX25L12835F.LierdaSPI_MOSI=SPI_MOSI;

	if (lierdaSPISoftInit(&SPI_MX25L12835F) == LierdaSPI_RET_OK)
		lierdaLog("SPI  Init  OK");
	else
		lierdaLog("SPI  Init  ERROR");
#else
	SPI_CONFIGURATION lierdaSPIconfig;
	SPI_PIN lierdaSPIpin;
	lierdaSPIconfig.data_size = 8;
	lierdaSPIconfig.clk_mode = SPI_CLK_MODE3;
	lierdaSPIconfig.clk_div = 0x02;
	lierdaSPIpin.interface = SPI_INTERFACE_SINGLE_UNIDIR;
	lierdaSPIpin.clk_pin = SPI_SCK;
	lierdaSPIpin.csb_pin = SPI_CS;
	lierdaSPIpin.miso_pin = SPI_MISO;
	lierdaSPIpin.mosi_pin = SPI_MOSI;
	if (lierdaSPIInit(lierdaSPIconfig, lierdaSPIpin) == SPI_RET_OK)
		lierdaLog("SPI  Init  OK");
	else
		lierdaLog("SPI  Init  ERROR");
#endif
}

/************************************************
函数名称 ： SFLASH_ReadID
功    能 ： 读取芯片ID SFLASH的ID
参    数 ： 无
返 回 值 ： ID --- 32位ID号
*************************************************/
uint32 SFLASH_ReadID(void)
{
 uint32 Temp = 0;
 uint8 idbuff[4]={0};uint8 cmd_JedecDeviceID=W25X_JedecDeviceID;
#if USESOFTSPI
  SPI_CS_ENABLE();                                 //使能器件

  lierdaSPIWriteByte(&SPI_MX25L12835F,cmd_JedecDeviceID);   //发送一个字节数据 《设备ID》指令

  idbuff[0]= lierdaSPIReadByte(&SPI_MX25L12835F);//读一个字节数据

  idbuff[1]= lierdaSPIReadByte(&SPI_MX25L12835F);//读一个字节数据

  idbuff[2]= lierdaSPIReadByte(&SPI_MX25L12835F);//读一个字节数据
   SPI_CS_DISABLE();  //失能器件
#else
   lierdaSPIRecvData(0,&cmd_JedecDeviceID,1,idbuff, 3,NULL,true);//false true
#endif
   Temp = (idbuff[0] << 16) | (idbuff[1] << 8) | idbuff[2];
  return Temp;
}
uint8 Tx_Buffer[]="lierda 软件SPI 测试";
uint8 Rx_Buffer[BufferSize];
/******************************************************************************
* @函数名	SPI测试
* @参数	        无
* @返回值        无
******************************************************************************/
void Lierda_SPITest(void)
 {
	uint32 ID;
	ID = SFLASH_ReadID();

	if (ID == 0xc22018)
	{
		lierdaLog("SFLASH_ReadID：\r\n%#x\r\nBufferSize=%d", ID,BufferSize);
		SPI_FLASH_SectorErase(FLASH_SectorToErase);
		/* 将发送缓冲区的数据写到flash中 */
		SPI_FLASH_BufferWrite(Tx_Buffer, FLASH_WriteAddress, BufferSize);
		lierdaLog("写入的数据为：\r\n\r\n%s", Tx_Buffer);
		/* 将刚刚写入的数据读出来放到接收缓冲区中 */
		SPI_FLASH_BufferRead(Rx_Buffer, FLASH_ReadAddress, BufferSize);
		lierdaLog("读出的数据为： \r\n\r\n%s", Rx_Buffer);
	}
	else
		lierdaLog("无FLASH  SFLASH_ReadID=%#x", ID);
}


/**
  * 函数功能: 使能串行Flash写操作
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
void SPI_FLASH_WriteEnable(void)
{
	uint8 cmd_WriteEnable=W25X_WriteEnable;
#if USESOFTSPI
  /* 选择串行FLASH: CS低电平 */
	SPI_CS_ENABLE();

  /* 发送命令：写使能 */
lierdaSPIWriteByte(&SPI_MX25L12835F,cmd_WriteEnable);

  /* 禁用串行Flash：CS高电平 */
  SPI_CS_DISABLE();
#else
  lierdaSPISendData(0, &cmd_WriteEnable,1, NULL, 0, NULL);
#endif
}
/**
  * 函数功能: 等待数据写入完成
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：Polls the status of the Write In Progress (WIP) flag in the
  *           FLASH's status  register  and  loop  until write  opertaion
  *           has completed.
  */
void SPI_FLASH_WaitForWriteEnd(void)
{
  uint8 FLASH_Status = 0;uint8 cmd_ReadStatusReg=W25X_ReadStatusReg;
#if USESOFTSPI
  /* Select the FLASH: Chip Select low */
  SPI_CS_ENABLE();

  /* Send "Read Status Register" instruction */
  lierdaSPIWriteByte(&SPI_MX25L12835F,cmd_ReadStatusReg);

  /* Loop as long as the memory is busy with a write cycle */
  do
  {
    /* Send a dummy byte to generate the clock needed by the FLASH
    and put the value of the status register in FLASH_Status variable */
    FLASH_Status =lierdaSPIReadByte(&SPI_MX25L12835F);
  }
  while ((FLASH_Status & WIP_Flag) == 1); /* Write in progress */

  /* Deselect the FLASH: Chip Select high */
  SPI_CS_DISABLE();
#else
  do
  {
	  lierdaSPIRecvData(0,&cmd_ReadStatusReg,1,&FLASH_Status, 1,NULL,true);
  }
  while ((FLASH_Status & WIP_Flag) == 1); /* Write in progress */

#endif
}
/**
  * 函数功能: 擦除扇区
  * 输入参数: SectorAddr：待擦除扇区地址，要求为4096倍数
  * 返 回 值: 无
  * 说    明：串行Flash最小擦除块大小为4KB(4096字节)，即一个扇区大小，要求输入参数
  *           为4096倍数。在往串行Flash芯片写入数据之前要求先擦除空间。
  */
void SPI_FLASH_SectorErase(uint32 SectorAddr)
{
	uint8 setaddr[4]={0};uint8 cmd_SectorErase=W25X_SectorErase;
	setaddr[0]=(SectorAddr & 0xFF0000)>>16;
	setaddr[1]=(SectorAddr & 0xFF00)>>8;
	setaddr[2]=SectorAddr & 0xFF;
  /* 发送FLASH写使能命令 */
  SPI_FLASH_WriteEnable();
  SPI_FLASH_WaitForWriteEnd();
#if USESOFTSPI
  /* 擦除扇区 */
  /* 选择串行FLASH: CS低电平 */
   SPI_CS_ENABLE();
  /* 发送扇区擦除指令*/
   lierdaSPIWriteByte(&SPI_MX25L12835F,cmd_SectorErase);

  /*发送擦除扇区地址的高位*/
   lierdaSPIWriteByte(&SPI_MX25L12835F,setaddr[0]);

  /* 发送擦除扇区地址的中位 */
   lierdaSPIWriteByte(&SPI_MX25L12835F,setaddr[1]);

  /* 发送擦除扇区地址的低位 */
   lierdaSPIWriteByte(&SPI_MX25L12835F,setaddr[2]);

  /* 禁用串行FLASH: CS 高电平 */
   SPI_CS_DISABLE();
#else
   lierdaSPISendData(0, &cmd_SectorErase,1, setaddr, 3, NULL);
#endif
  /* 等待擦除完毕*/
  SPI_FLASH_WaitForWriteEnd();
}
/**
  * 函数功能: 往串行FLASH按页写入数据，调用本函数写入数据前需要先擦除扇区
  * 输入参数: pBuffer：待写入数据的指针
  *           WriteAddr：写入地址
  *           NumByteToWrite：写入数据长度，必须小于等于SPI_FLASH_PerWritePageSize
  * 返 回 值: 无
  * 说    明：串行Flash每页大小为256个字节
  */

void SPI_FLASH_PageWrite(uint8* pBuffer, uint32 WriteAddr, uint16 NumByteToWrite)
{
	uint8 writaddr[5]={0};uint8 cmd_PageProgram=W25X_PageProgram;
	writaddr[0]=cmd_PageProgram;
	writaddr[1]=(WriteAddr & 0xFF0000)>>16;
	writaddr[2]=(WriteAddr & 0xFF00)>>8;
	writaddr[3]=WriteAddr & 0xFF;
  /* 发送FLASH写使能命令 */
  SPI_FLASH_WriteEnable();
#if USESOFTSPI
   /* 寻找串行FLASH: CS低电平 */
  SPI_CS_ENABLE();
  /* 写送写指令*/
  lierdaSPIWriteByte(&SPI_MX25L12835F,cmd_PageProgram);
  /*发送写地址的高位*/
  lierdaSPIWriteByte(&SPI_MX25L12835F,writaddr[1]);

  /*发送写地址的中位*/
  lierdaSPIWriteByte(&SPI_MX25L12835F,writaddr[2]);

  /*发送写地址的低位*/
  lierdaSPIWriteByte(&SPI_MX25L12835F,writaddr[3]);


  if(NumByteToWrite > SPI_FLASH_PerWritePageSize)
  {
     NumByteToWrite = SPI_FLASH_PerWritePageSize;
     //printf("Err: SPI_FLASH_PageWrite too large!\n");
  }

  /* 写入数据*/
  while (NumByteToWrite--)
  {
     /* 发送当前要写入的字节数据 */
	  lierdaSPIWriteByte(&SPI_MX25L12835F,*pBuffer);
     /* 指向下一字节数据 */
    pBuffer++;
  }

  /* 禁用串行FLASH: CS 高电平 */
  SPI_CS_DISABLE();
#else
  if(NumByteToWrite > SPI_FLASH_PerWritePageSize)
   {
      NumByteToWrite = SPI_FLASH_PerWritePageSize;
   }
   lierdaSPISendData(0, writaddr,4, pBuffer, NumByteToWrite, NULL);
#endif
  /* 等待写入完毕*/
  SPI_FLASH_WaitForWriteEnd();
}
/**
  * 函数功能: 往串行FLASH写入数据，调用本函数写入数据前需要先擦除扇区
  * 输入参数: pBuffer：待写入数据的指针
  *           WriteAddr：写入地址
  *           NumByteToWrite：写入数据长度
  * 返 回 值: 无
  * 说    明：该函数可以设置任意写入数据长度
  */
void SPI_FLASH_BufferWrite(uint8* pBuffer, uint32 WriteAddr, uint16 NumByteToWrite)
{
  uint8 NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

  Addr = WriteAddr % SPI_FLASH_PageSize;
  count = SPI_FLASH_PageSize - Addr;
  NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
  NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

  if (Addr == 0) /* 若地址与 SPI_FLASH_PageSize 对齐  */
  {
    if (NumOfPage == 0) /* NumByteToWrite < SPI_FLASH_PageSize */
    {
      SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
    }
    else /* NumByteToWrite > SPI_FLASH_PageSize */
    {
      while (NumOfPage--)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
        WriteAddr +=  SPI_FLASH_PageSize;
        pBuffer += SPI_FLASH_PageSize;
      }

      SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
    }
  }
  else /* 若地址与 SPI_FLASH_PageSize 不对齐 */
  {
    if (NumOfPage == 0) /* NumByteToWrite < SPI_FLASH_PageSize */
    {
      if (NumOfSingle > count) /* (NumByteToWrite + WriteAddr) > SPI_FLASH_PageSize */
      {
        temp = NumOfSingle - count;

        SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
        WriteAddr +=  count;
        pBuffer += count;

        SPI_FLASH_PageWrite(pBuffer, WriteAddr, temp);
      }
      else
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
      }
    }
    else /* NumByteToWrite > SPI_FLASH_PageSize */
    {
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
      NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

      SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
      WriteAddr +=  count;
      pBuffer += count;

      while (NumOfPage--)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
        WriteAddr +=  SPI_FLASH_PageSize;
        pBuffer += SPI_FLASH_PageSize;
      }

      if (NumOfSingle != 0)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
      }
    }
  }
}

/**
  * 函数功能: 从串行Flash读取数据
  * 输入参数: pBuffer：存放读取到数据的指针
  *           ReadAddr：读取数据目标地址
  *           NumByteToRead：读取数据长度
  * 返 回 值: 无
  * 说    明：该函数可以设置任意读取数据长度
  */
void SPI_FLASH_BufferRead(uint8* pBuffer, uint32 ReadAddr, uint16 NumByteToRead)
{
	uint8 READADDE[5]={0};uint8 cmd_ReadData=W25X_ReadData;
	READADDE[0]=cmd_ReadData;
	READADDE[1]=(ReadAddr & 0xFF0000)>>16;
	READADDE[2]=(ReadAddr & 0xFF00)>>8;
	READADDE[3]=ReadAddr & 0xFF;
#if USESOFTSPI
  /* 选择串行FLASH: CS低电平 */
	 SPI_CS_ENABLE();

  /* 发送 读 指令 */
	  lierdaSPIWriteByte(&SPI_MX25L12835F,cmd_ReadData);


  /* 发送 读 地址高位 */
	  lierdaSPIWriteByte(&SPI_MX25L12835F,READADDE[1]);

  /* 发送 读 地址中位 */
	  lierdaSPIWriteByte(&SPI_MX25L12835F,READADDE[2]);

  /* 发送 读 地址低位 */
	  lierdaSPIWriteByte(&SPI_MX25L12835F,READADDE[3]);

  while (NumByteToRead--) /* 读取数据 */
  {
     /* 读取一个字节*/
    *pBuffer = lierdaSPIReadByte(&SPI_MX25L12835F);
    /* 指向下一个字节缓冲区 */
    pBuffer++;
  }

  /* 禁用串行FLASH: CS 高电平 */
  SPI_CS_DISABLE();
#else
  lierdaSPIRecvData(0,READADDE,4,pBuffer, NumByteToRead,NULL,true);//true false
#endif
}


