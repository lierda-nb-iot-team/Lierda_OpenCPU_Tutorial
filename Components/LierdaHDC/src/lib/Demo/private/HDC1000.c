/******************************************************************************
 * @内容	温湿度传感器相关驱动函数
 * @设计	Lierda NB-IoT 软件设计团队@2018
******************************************************************************/
#include "HDC1000.h"


void   HDC1000_Soft_Reset(void);
uint16 HDC1000_Read_DeviceID(void);
void   HDC1000_Setting(void);
uint16 HDC1000_Read_Config(void);
uint16 HDC1000_Read_ManufacturerID(void);
uint8  HDC1000_Read_Temper_Humidity(int16 *nTemper,int16 *nHumidity);
uint8 HDC1000_Writereg(uint8 reg_addr,uint8 *data,uint8 len);
uint8 HDC1000_Rradreg(uint8 reg_addr,uint8 *data_buff,uint8 len);

USER_THS_DEV_Typedef  thsDeviceInfo;

I2C_HandleTypeDef  sensorI2CHandle;  // 声明，  I2C句柄， I2C读写操作使用


/******************************************************************************
* @函数名	I2C初始化函数
* @参数	无
* @返回值   无
******************************************************************************/
void I2C_init(void)
{
	sensorI2CHandle.i2c_bus = I2C_BUS1;
	sensorI2CHandle.pin_scl = I2C_SCL;
	sensorI2CHandle.pin_sda = I2C_SDA;
	sensorI2CHandle.i2c_address_type = HAL_I2C_ADDRESS_TYPE_7_BIT;
	sensorI2CHandle.i2c_half_time = 256;
	sensorI2CHandle.i2c_mode = HAL_I2C_BUS_MODE_MASTER;
	lierdaI2CInit(&sensorI2CHandle);
}

/******************************************************************************
* @函数名	HDC1000初始化函数
* @参数	无
* @返回值   1：成功  0：失败
******************************************************************************/
uint8 HDC1000_Init(void)
{
	uint8 ucCount;
	HDC1000_Soft_Reset();
	ucCount = 6;
	do {
		thsDeviceInfo.Device_ID = HDC1000_Read_DeviceID();
		osDelay(20);
	} while ((thsDeviceInfo.Device_ID != HDC1000_ID) && ((ucCount--) > 1));
	   if(ucCount==0)
	     return 0;
	HDC1000_Setting();
	osDelay(10);
	thsDeviceInfo.Config_Val = HDC1000_Read_Config();
	osDelay(10);
	thsDeviceInfo.Manufacture = HDC1000_Read_ManufacturerID();
	osDelay(10);
	//Read Serial ID
	HDC1000_Rradreg(0xfb,thsDeviceInfo.Serial_ID,2);
	osDelay(10);
	HDC1000_Rradreg(0xfc,thsDeviceInfo.Serial_ID+2,2);
	osDelay(10);
	HDC1000_Rradreg(0xfd,thsDeviceInfo.Serial_ID+4,2);
	osDelay(10);
	return 1;
}

/******************************************************************************
* @函数名    温湿度传感器数据获取函数
* @参数	*Temper      :温度数据地址
* @参数	*Humidity    :湿度数据地址
* @返回值   无
******************************************************************************/
void HDC1000_UpdateInfo(int16 *Temper,int16 *Humidity)
{
	uint8 value = 0x00;
	lierdaI2CWrite(&sensorI2CHandle,HDC1000_I2C_ADDRESS,&value,1);
	osDelay(50);
	HDC1000_Read_Temper_Humidity((int16*) &thsDeviceInfo.Temperature,(int16*) &thsDeviceInfo.Humidity);
	*Temper  =thsDeviceInfo.Temperature;
	*Humidity=thsDeviceInfo.Humidity;
}

uint8 HDC1000_Read_Temper_Humidity(int16 *nTemper,int16 *nHumidity)
{
	uint8 buffer[4];   // 获取4个字节数据，前2个字节为温度数据，后2个字节为湿度数据
	uint8 xStatus;
	xStatus=lierdaI2CRead(&sensorI2CHandle,HDC1000_I2C_ADDRESS,buffer, 4);
    *nTemper = (int16)(((((buffer[0]<<8)|buffer[1])/65536.0)*165-40)*100);  // 乘以100倍输出
    *nHumidity = (int16)((((buffer[2]<<8)|buffer[3])/65536.0)*100);         // 乘以100倍输出
    return xStatus;
}

void HDC1000_Setting(void)
{
    uint16 tempcom = 0;
    uint8 temp[2];
    tempcom = (1<<HDC1000_Mode) ;
    temp[0] = (uint8)(tempcom >> 8);
    temp[1] = (uint8)tempcom;
    HDC1000_Writereg(HDC1000_Read_Conf, temp, 2);
}

uint16 HDC1000_Read_ManufacturerID(void)
{
    uint8 buffer[2];
    HDC1000_Rradreg(HDC1000_Manufacturer_ID, buffer,2);
    return ((buffer[0]<<8)|buffer[1]);
}

uint16 HDC1000_Read_Config(void)
{
    uint8 buffer[2];
    HDC1000_Rradreg(HDC1000_Read_Conf, buffer,2);
    return ((buffer[0]<<8)|buffer[1]);
}
/******************************************************************************
* @函数名    HDC1000写寄存器操作
* @参数	reg_addr      :寄存器地址
* @参数	*data    :数据地址
* @返回值   0：成功  1：失败
******************************************************************************/
uint8 HDC1000_Writereg(uint8 reg_addr,uint8 *data,uint8 len)
{
	uint8 buff[4]={0};
	buff[0]=reg_addr;
	memcpy(buff+1,data,len);
	if(lierdaI2CWrite(&sensorI2CHandle,HDC1000_I2C_ADDRESS,buff,len+1))
		return 1;
	return 0;
}
/******************************************************************************
* @函数名    HDC1000读寄存器操作
* @参数	reg_addr      :寄存器地址
* @参数	*data_buff    :读回来的数据buff地址
* @返回值   0：成功  1：失败
******************************************************************************/
uint8 HDC1000_Rradreg(uint8 reg_addr,uint8 *data_buff,uint8 len)
{
	if(lierdaI2CWrite(&sensorI2CHandle,HDC1000_I2C_ADDRESS,&reg_addr,1))
		return 1;
	if(lierdaI2CRead(&sensorI2CHandle,HDC1000_I2C_ADDRESS,data_buff, len))
		return 1;
	return 0;
}
void HDC1000_Soft_Reset(void)
{
	uint8 temp[2];
	temp[0]=0x80;
	temp[1]=0x00;
	HDC1000_Writereg(HDC1000_Read_Conf,temp,2);
	osDelay(30);  //这里最好延时15ms以上
}

uint16 HDC1000_Read_DeviceID(void)
{
    uint8 buffer[2];
    HDC1000_Rradreg(HDC1000_DEVICE_ID,buffer,2);
    return ((buffer[0]<<8)|buffer[1]);
}


