/******************************************************************************
 * @brief    BOUDICA RTOS MASTER I2C DRIVER API
 * Copyright (c) 2017 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef  SRC_DRIVERS_FREERTOS_I2C_H_
#define  SRC_DRIVERS_FREERTOS_I2C_H_

/** @defgroup DRIVER_CMSIS_I2C Hi211X CMSIS I2C Driver
 * CMSIS I2C Driver
 * @ingroup DRIVER_CMSIS
 * @{
 * */

#include "Hi21XX_cores.h"
#include "neulfw.h"
#include "platform.h"
#include "hal_i2c.h"
#include "core.h"

typedef struct
{
    PIN     scl;/* Serial Clock Line */
    PIN     sda;/* Serial Data Line */
}I2C_PIN;

typedef struct
{
    uint8 i2c_config_mode;
    uint8 i2c_config_addr_type;
    uint16 i2c_config_half_time;
}I2C_CONFIGURATION;

/*!< I2C retern type*/
typedef enum
{
    /*!< I2C retern Ok*/
    I2C_RET_OK,
    /*!< I2C parameter error*/
    I2C_RET_PARAMETER_ERROR,
    /*!< I2C state error*/
    I2C_RET_STATE_ERROR,
    /*!< I2C slave is not responding*/
    I2C_RET_SLAVE_NOT_RESPONSE_ERROR,
    /*!< I2C retern error*/
    I2C_RET_ERROR,
} I2C_RET;

/**
 * I2C initialize
 * @return None
 */
void i2c_init(void);

/**
 * I2C deinit
 * @return None
 */
void i2c_deinit(void);

/**
 * I2C claim
 * @param  bus     I2C BUS
 * @param  i2c_pin i2c use pin
 * @return I2C_RET_OK i2c claim ok
 *         I2C_RET_ERROR i2c claim error
 */
I2C_RET i2c_claim(I2C_BUS* bus, I2C_PIN i2c_pin);

/**
 * I2C release
 * @param  bus     I2C BUS
 * @return I2C_RET_OK i2c release ok
 *         I2C_RET_ERROR i2c release error
 */
I2C_RET i2c_release(I2C_BUS bus);

/**
 * I2C activate
 * @param  bus     I2C BUS
 * @param  config  I2C config param
 *         The clock frequency of the I2C can be controlled by configuring config.i2c_config_half_time. The calculation method is:
 *          I2C_HALF_TIME = (core_clock_Khz)/(target_freq_Khz)/2
 *         The current clock_clock_Khz is approximately 51750 KHz.The specific value can be obtained by the function clocks_get_core_clock(void).
 * @return I2C_RET_OK i2c config ok
 *         I2C_RET_ERROR i2c config error
 * @note Current hardware tHD: STA and tHD: STO time is 1/4 of the clock cycle. Therefore in order to achieve the
 *       Standard-mode specification the clock speed must be reduced to 60kHz. Hi2115 is fully compliant with the
 *       Fast-Mode specification. However, if the connected device is only compatible with standard mode (legacy
 *       device), then should consult the device manufacturer for these parameters, or reduce the clock speed to 60kHz.
 */
I2C_RET i2c_activate(I2C_BUS bus, I2C_CONFIGURATION config);

/**
 * I2C deactivate
 * @param  bus     I2C BUS
 * @return I2C_RET_OK i2c deactivate ok
 *         I2C_RET_ERROR i2c deactivate error
 */
I2C_RET i2c_deactivate(I2C_BUS bus);

/**
 * I2C master transmite data in block mode
 * @param  I2C_BUS
 * @param  I2C slave address
 * @param  I2C transmite data buff point
 * @param  I2C transmite data number bytes
 * @return None
 */
I2C_RET i2c_master_send_data(I2C_BUS i2c_bus, uint16 addr, const uint8 *pdata, uint8 num_of_bytes);

/**
 * I2C master receive data in block mode
 * @param  I2C_BUS
 * @param  I2C slave address
 * @param  I2C receive data buff point
 * @param  I2C receive data number bytes
 * @return None
 */
I2C_RET i2c_master_receive_data(I2C_BUS i2c_bus, uint16 addr, uint8 *pdata, uint8 num_of_bytes);

/** @} end of group DRIVER_CMSIS_I2C */

#endif
