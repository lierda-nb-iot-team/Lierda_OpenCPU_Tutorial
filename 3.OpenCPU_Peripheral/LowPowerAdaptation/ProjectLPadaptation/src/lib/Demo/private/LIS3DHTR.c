/******************************************************************************
 * @内容	三轴传感器相关驱动函数
 * @设计	Lierda NB-IoT 软件设计团队@2018
******************************************************************************/
#include "LIS3DHTR.h"
#include "lierda_app_main.h"
#include "cmsis_os2.h"
#include "string.h"
I2C_HandleTypeDef sensorI2CHandle;
AxesRaw_t gssAccData = { 0, 0, 0, 0, 0 };

void I2c_Init(void);
uint8 LIS3DH_init(void);
uint8 LIS3DH_GetStatusBit(uint8 statusBIT, uint8* val);
uint8 LIS3DH_SetIntMode(LIS3DH_Int1Mode_t int_mode);
uint8 LIS3DH_SetIntConfiguration(uint8 ic);
uint8 LIS3DH_SetInt1Threshold(uint8 ths);
uint8 LIS3DH_SetAxis(uint8 axis);
uint8 LIS3DH_SetFullScale(LIS3DH_Fullscale_t fs);
uint8 LIS3DH_SetODR(LIS3DH_ODR_t ov);
uint8 LIS3DH_SetMode(LIS3DH_Mode_t md);
uint8 LIS3DH_Get6DPosition(uint8* val);
uint8 LIS3DH_GetAccAxesRaw(AxesRaw_t* buff);
static uint8 LIS3DH_readreg(uint8 regaddr,uint8* databuff,uint16 len);
static uint8 LIS3DH_writereg(uint8 regaddr,uint8* databuff,uint16 len);
void LIS3DHUpdateInfo(int16 *LIS3DH_X,int16 *LIS3DH_Y,int16 *LIS3DH_Z);

/******************************************************************************
 * @函数名   I2C初始化函数
 * @参数	param : 空参数
 * @返回值  无
 ******************************************************************************/
void I2c_Init(void)
{
	sensorI2CHandle.i2c_bus = I2C_BUS1;
	sensorI2CHandle.pin_scl = I2C_SCL;
	sensorI2CHandle.pin_sda = I2C_SDA;
	sensorI2CHandle.i2c_address_type = HAL_I2C_ADDRESS_TYPE_7_BIT;
	sensorI2CHandle.i2c_half_time = 256;
	sensorI2CHandle.i2c_mode = HAL_I2C_BUS_MODE_MASTER;
	lierdaI2CInit(&sensorI2CHandle); //初始化I2C
}
/******************************************************************************
 * @函数名   I2C反初始化函数
 * @参数	param : 空参数
 * @返回值  无
 ******************************************************************************/
void I2c_DEInit(void)
{
	lierdaI2CDeinit(&sensorI2CHandle);
}
/******************************************************************************
* @函数名   三轴传感器初始化函数
* @参数	param : 空参数
* @返回值  1：成功  0 ：失败
******************************************************************************/
uint8 LIS3DH_init(void)
{
	uint8 ucResponse;
	uint8 ucState, ucDataTemp = 0x05;
	LIS3DH_readreg(LIS3DH_WHO_AM_I,&ucResponse, 1);
	while ((ucResponse != 0x33) && ((ucDataTemp--) > 0))
	{ //读取设备名称异常
		LIS3DH_readreg(LIS3DH_WHO_AM_I,&ucResponse, 1);
		if (ucDataTemp <= 1)
		{ //读取名称失败
			return 0;
		}
	}

	ucResponse = LIS3DH_SetODR(LIS3DH_ODR_100Hz);
	if (ucResponse == 1)
		osDelay(1);
	ucResponse = LIS3DH_SetMode(LIS3DH_LOW_POWER);
	if (ucResponse == 1)
		osDelay(1);
	//set Fullscale
	ucResponse = LIS3DH_SetFullScale(LIS3DH_FULLSCALE_2);
	if (ucResponse == 1)
		osDelay(1);
	//set axis Enable
	ucResponse = LIS3DH_SetAxis(
			LIS3DH_X_ENABLE | LIS3DH_Y_ENABLE | LIS3DH_Z_ENABLE);
	if (ucResponse == 1)
		osDelay(1);
	//configure Mems Sensor
	//set Interrupt Threshold
	ucResponse = LIS3DH_SetInt1Threshold(20);
	if (ucResponse == 1)
		osDelay(1);
	//set Interrupt configuration (all enabled)
	ucResponse = LIS3DH_SetIntConfiguration(
			LIS3DH_INT1_ZHIE_ENABLE | LIS3DH_INT1_ZLIE_ENABLE |
			LIS3DH_INT1_YHIE_ENABLE | LIS3DH_INT1_YLIE_ENABLE |
			LIS3DH_INT1_XHIE_ENABLE | LIS3DH_INT1_XLIE_ENABLE);
	if (ucResponse == 1)
		osDelay(1);
	//set Interrupt Mode
	ucResponse = LIS3DH_SetIntMode(LIS3DH_INT_MODE_6D_POSITION);
	if (ucResponse == 1)
		osDelay(1);
	//wait the xyz axis new data update
	ucDataTemp = 0x05;
	LIS3DH_GetStatusBit(LIS3DH_STATUS_REG_ZYXDA, &ucState);
	while ((ucState != MEMS_SET) && ((ucDataTemp--) > 0))
	{
		if (ucDataTemp <= 1) {	      //读取名称失败
			return 0;
		}
	}
	return 1;

}


/******************************************************************************
* @函数名 三轴传感器数据获取函数
* @参数	*LIS3DH_X :X轴数据地址
* @参数	*LIS3DH_Y :Y轴数据地址
* @参数	*LIS3DH_Z :Z轴数据地址
* @返回值   无
******************************************************************************/
void LIS3DHUpdateInfo(int16 *LIS3DH_X,int16 *LIS3DH_Y,int16 *LIS3DH_Z)
{
	uint8 ucResponse, position;
	ucResponse = LIS3DH_Get6DPosition(&position);  //中断位检测
	if ((ucResponse == 1) && (position))
	{
		LIS3DH_GetAccAxesRaw(&gssAccData);  //数据读取
		*LIS3DH_X=gssAccData.AXIS_X;
		*LIS3DH_Y=gssAccData.AXIS_Y;
		*LIS3DH_Z=gssAccData.AXIS_Z;
	}
}
/*******************************************************************************
 * Function Name  : LIS3DH_GetAccAxesRaw
 * Description    : Read the Acceleration Values Output Registers
 * Input          : buffer to empity by AxesRaw_t Typedef
 * Output         : None
 * Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
 *******************************************************************************/
uint8 LIS3DH_GetAccAxesRaw(AxesRaw_t* buff) {
	uint16 value;uint8 cmd;
	uint8 *valueL = (uint8 *) (&value);
	uint8 *valueH = ((uint8 *) (&value) + 1);
	cmd=LIS3DH_OUT_X_L;
	if (LIS3DH_readreg(cmd, valueL, 1))
		return 0;
	cmd=LIS3DH_OUT_X_H;
	if (LIS3DH_readreg( cmd, valueH, 1))
		return 0;
	buff->AXIS_X = value;
	cmd=LIS3DH_OUT_Y_L;
	if (LIS3DH_readreg( cmd, valueL, 1))
		return 0;
	cmd=LIS3DH_OUT_Y_H;
	if (LIS3DH_readreg( cmd, valueH, 1))
		return 0;
	buff->AXIS_Y = value;
	cmd=LIS3DH_OUT_Z_L;
	if (LIS3DH_readreg( cmd, valueL, 1))
		return 0;
	cmd=LIS3DH_OUT_Z_H;
	if (LIS3DH_readreg(cmd, valueH, 1))
		return 0;
	buff->AXIS_Z = value;
	return 1;
}

/*******************************************************************************
 * Function Name  : LIS3DH_Get6DPosition
 * Description    : 6D, 4D Interrupt Position Detect
 * Input          : Byte to empty by POSITION_6D_t Typedef
 * Output         : None
 * Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
 *******************************************************************************/
uint8 LIS3DH_Get6DPosition(uint8* val) {
	uint8 value;

	if (LIS3DH_readreg( LIS3DH_INT1_SRC, &value, 1))
		return 0;

	value &= 0x7F;

	switch (value) {
	case LIS3DH_UP_SX:
		*val = LIS3DH_UP_SX;
		break;
	case LIS3DH_UP_DX:
		*val = LIS3DH_UP_DX;
		break;
	case LIS3DH_DW_SX:
		*val = LIS3DH_DW_SX;
		break;
	case LIS3DH_DW_DX:
		*val = LIS3DH_DW_DX;
		break;
	case LIS3DH_TOP:
		*val = LIS3DH_TOP;
		break;
	case LIS3DH_BOTTOM:
		*val = LIS3DH_BOTTOM;
		break;
	}

	return 1;
}
/*******************************************************************************
 * Function Name  : LIS3DH_GetStatusBIT
 * Description    : Read the status register BIT
 * Input          : LIS3DH_STATUS_REG_ZYXOR, LIS3DH_STATUS_REG_ZOR, LIS3DH_STATUS_REG_YOR, LIS3DH_STATUS_REG_XOR,
 LIS3DH_STATUS_REG_ZYXDA, LIS3DH_STATUS_REG_ZDA, LIS3DH_STATUS_REG_YDA, LIS3DH_STATUS_REG_XDA,
 LIS3DH_DATAREADY_BIT
 val: Byte to be filled with the status bit
 * Output         : status register BIT
 * Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
 *******************************************************************************/
uint8 LIS3DH_GetStatusBit(uint8 statusBIT, uint8* val) {
	uint8 value;
	if (LIS3DH_readreg( LIS3DH_STATUS_REG, &value, 1))
		return 0;
	switch (statusBIT) {
	case LIS3DH_STATUS_REG_ZYXOR:
		if (value &= LIS3DH_STATUS_REG_ZYXOR) {
			*val = MEMS_SET;
			return 1;
		} else {
			*val = MEMS_RESET;
			return 1;
		}
	case LIS3DH_STATUS_REG_ZOR:
		if (value &= LIS3DH_STATUS_REG_ZOR) {
			*val = MEMS_SET;
			return 1;
		} else {
			*val = MEMS_RESET;
			return 1;
		}
	case LIS3DH_STATUS_REG_YOR:
		if (value &= LIS3DH_STATUS_REG_YOR) {
			*val = MEMS_SET;
			return 1;
		} else {
			*val = MEMS_RESET;
			return 1;
		}
	case LIS3DH_STATUS_REG_XOR:
		if (value &= LIS3DH_STATUS_REG_XOR) {
			*val = MEMS_SET;
			return 1;
		} else {
			*val = MEMS_RESET;
			return 1;
		}
	case LIS3DH_STATUS_REG_ZYXDA:
		if (value &= LIS3DH_STATUS_REG_ZYXDA) {
			*val = MEMS_SET;
			return 1;
		} else {
			*val = MEMS_RESET;
			return 1;
		}
	case LIS3DH_STATUS_REG_ZDA:
		if (value &= LIS3DH_STATUS_REG_ZDA) {
			*val = MEMS_SET;
			return 1;
		} else {
			*val = MEMS_RESET;
			return 1;
		}
	case LIS3DH_STATUS_REG_YDA:
		if (value &= LIS3DH_STATUS_REG_YDA) {
			*val = MEMS_SET;
			return 1;
		} else {
			*val = MEMS_RESET;
			return 1;
		}
	case LIS3DH_STATUS_REG_XDA:
		if (value &= LIS3DH_STATUS_REG_XDA) {
			*val = MEMS_SET;
			return 1;
		} else {
			*val = MEMS_RESET;
			return 1;
		}

	}
	return 0;
}
/*******************************************************************************
 * Function Name  : LIS3DH_SetIntMode
 * Description    : Interrupt 1 Configuration mode (OR, 6D Movement, AND, 6D Position)
 * Input          : LIS3DH_INT_MODE_OR, LIS3DH_INT_MODE_6D_MOVEMENT, LIS3DH_INT_MODE_AND,
 LIS3DH_INT_MODE_6D_POSITION
 * Output         : None
 * Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
 *******************************************************************************/
uint8 LIS3DH_SetIntMode(LIS3DH_Int1Mode_t int_mode) {
	uint8 value;

	if (LIS3DH_readreg( LIS3DH_INT1_CFG, &value, 1))
		return 0;
	value &= 0x3F;
	value |= (int_mode << LIS3DH_INT_6D);

	if (LIS3DH_writereg(LIS3DH_INT1_CFG, &value, 1))
		return 0;
	return 1;
}
/*******************************************************************************
 * Function Name  : LIS3DH_SetIntConfiguration
 * Description    : Interrupt 1 Configuration (without LIS3DH_6D_INT)
 * Input          : LIS3DH_INT1_AND/OR | LIS3DH_INT1_ZHIE_ENABLE/DISABLE | LIS3DH_INT1_ZLIE_ENABLE/DISABLE...
 * Output         : None
 * Note           : You MUST use all input variable in the argument, as example
 * Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
 *******************************************************************************/
uint8 LIS3DH_SetIntConfiguration(uint8 ic) {
	uint8 value;

	if (LIS3DH_readreg(LIS3DH_INT1_CFG, &value, 1))
		return 0;
	value &= 0x40;
	value |= ic;
	if (LIS3DH_writereg( LIS3DH_INT1_CFG, &value, 1))
		return 0;

	return 1;
}

/*******************************************************************************
 * Function Name  : LIS3DH_SetInt1Threshold
 * Description    : Sets Interrupt 1 Threshold
 * Input          : Threshold = [0,31]
 * Output         : None
 * Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
 *******************************************************************************/
uint8 LIS3DH_SetInt1Threshold(uint8 ths) {

	if (ths > 127)
		return 0;
	if (LIS3DH_writereg(LIS3DH_INT1_THS, &ths, 1))
		return 0;
	return 1;
}
/*******************************************************************************
 * Function Name  : LIS3DH_SetAxis
 * Description    : Enable/Disable LIS3DH Axis
 * Input          : LIS3DH_X_ENABLE/DISABLE | LIS3DH_Y_ENABLE/DISABLE | LIS3DH_Z_ENABLE/DISABLE
 * Output         : None
 * Note           : You MUST use all input variable in the argument, as example
 * Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
 *******************************************************************************/
uint8 LIS3DH_SetAxis(uint8 axis) {
	uint8 value;
	if (LIS3DH_readreg( LIS3DH_CTRL_REG1, &value, 1))
		return 0;
	value &= 0xF8;
	value |= (0x07 & axis);
	if (LIS3DH_writereg( LIS3DH_CTRL_REG1, &value, 1))
		return 0;

	return 1;
}

uint8 LIS3DH_SetODR(LIS3DH_ODR_t ov) {
	uint8 value;
	if (LIS3DH_readreg(LIS3DH_CTRL_REG1, &value, 1))
		return 0;
	value &= 0x0f;
	value |= ov << LIS3DH_ODR_BIT;
	if (LIS3DH_writereg(LIS3DH_CTRL_REG1,&value,1))
		return 0;
	return 1;
}
static uint8 LIS3DH_writereg(uint8 regaddr,uint8* databuff,uint16 len)
{
	uint8 buff[3];
	buff[0]=regaddr;
	memcpy(buff+1,databuff,len);
	if(lierdaI2CWrite(&sensorI2CHandle,gssI2C_ADDRESS,buff,1+len))
		return 1;
	return 0;
}
static uint8 LIS3DH_readreg(uint8 regaddr,uint8* databuff,uint16 len)
{

	if(lierdaI2CWrite(&sensorI2CHandle,gssI2C_ADDRESS,&regaddr,1))
		return 1;
	if(lierdaI2CRead(&sensorI2CHandle,gssI2C_ADDRESS,databuff,len))
		return 1;
	return 0;
}
/*******************************************************************************
 * Function Name  : LIS3DH_SetMode
 * Description    : Sets LIS3DH Operating Mode
 * Input          : Modality (LIS3DH_NORMAL, LIS3DH_LOW_POWER, LIS3DH_POWER_DOWN)
 * Output         : None
 * Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
 *******************************************************************************/
uint8 LIS3DH_SetMode(LIS3DH_Mode_t md) {
	uint8 value;
	uint8 value2;
	static uint8 ODR_old_value;
	if (LIS3DH_readreg(LIS3DH_CTRL_REG1, &value, 1))
		return 0;
	if (LIS3DH_readreg( LIS3DH_CTRL_REG4, &value2, 1))
		return 0;
	if ((value & 0xF0) == 0)
		value = value | (ODR_old_value & 0xF0); //if it comes from POWERDOWN

	switch (md) {

	case LIS3DH_POWER_DOWN:
		ODR_old_value = value;
		value &= 0x0F;
		break;

	case LIS3DH_NORMAL:
		value &= 0xF7;
		value |= (MEMS_RESET << LIS3DH_LPEN);
		value2 &= 0xF7;
		value2 |= (MEMS_SET << LIS3DH_HR);   //set HighResolution_BIT
		break;

	case LIS3DH_LOW_POWER:
		value &= 0xF7;
		value |= (MEMS_SET << LIS3DH_LPEN);
		value2 &= 0xF7;
		value2 |= (MEMS_RESET << LIS3DH_HR); //reset HighResolution_BIT
		break;

	default:
		return 0;
	}
	if (LIS3DH_writereg(LIS3DH_CTRL_REG1, &value, 1))
		return 0;
	if (LIS3DH_writereg(LIS3DH_CTRL_REG4, &value2, 1))
		return 0;
	return 1;
}

/*******************************************************************************
 * Function Name  : LIS3DH_SetFullScale
 * Description    : Sets the LIS3DH FullScale
 * Input          : LIS3DH_FULLSCALE_2/LIS3DH_FULLSCALE_4/LIS3DH_FULLSCALE_8/LIS3DH_FULLSCALE_16
 * Output         : None
 * Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
 *******************************************************************************/
uint8 LIS3DH_SetFullScale(LIS3DH_Fullscale_t fs) {
	uint8 value;
	if (LIS3DH_readreg(LIS3DH_CTRL_REG4, &value, 1))
		return 0;

	value &= 0xCF;
	value |= (fs << LIS3DH_FS);
	if (LIS3DH_writereg( LIS3DH_CTRL_REG4, &value, 1))
		return 0;
	return 1;
}
