/******************************************************************************
 * @brief    BOUDICA APPS I2C HAL Header File
 * Copyright (c) 2017 Huawei Technologies Co. Ltd
 ******************************************************************************/

#ifndef  HAL_I2C_H
#define  HAL_I2C_H

#include "Hi21XX.h"
#include "core.h"
#include "platform_core.h"
#include "neulfw.h"
#include "Hi21XX_cores.h"
#include "commonc.h"

/** @defgroup DRIVER_HAL_I2C Hi211X HAL I2C Driver
 * HAL I2C Driver
 * @ingroup DRIVER_HAL
 * @{
 * */

#define  HAL_I2C_SOFT_RESET_SET        (1)
#define  HAL_I2C_SOFT_RESET_CLR        (0)

#define  HAL_I2C_START_SET             (1)
#define  HAL_I2C_START_CLR             (0)

#define  HAL_I2C_RESTART_SET           (1)
#define  HAL_I2C_RESTART_CLR           (0)

#define  HAL_I2C_TX_RX_BYTES_EACH_TIME (4)

#define  HAL_I2C_INTER_FLAG_IS_SET     (1)
#define  HAL_I2C_INTER_FLAG_NOT_SET    (0)

typedef void (*hal_i2c_callback)(void);

/*!< I2C mode */
typedef enum
{
    HAL_I2C_BUS_MODE_SLAVE,
    HAL_I2C_BUS_MODE_MASTER,
}HAL_I2C_BUS_MODE;

/*!< I2C Address type */
typedef enum
{
    HAL_I2C_ADDRESS_TYPE_7_BIT,
    HAL_I2C_ADDRESS_TYPE_10_BIT,
}HAL_I2C_ADDRESS_TYPE;

/*!< I2C slave access*/
typedef enum
{
    HAL_I2C_SLAVE_ACCESS_DISABLE,
    HAL_I2C_SLAVE_ACCESS_ENABLE,
}HAL_I2C_SLAVE_ACCESS;

/*!<I2C operation*/
typedef enum
{
    HAL_I2C_OPERATION_WRITE,
    HAL_I2C_OPERATION_READ,
}HAL_I2C_OPERATION;

/*!< I2C initialize registers*/
typedef struct
{
    uint32 hal_i2c_regs_interrupt_status;
    uint32 hal_i2c_regs_interrupt_clear;
    uint32 hal_i2c_regs_interrupt_enable;
    uint32 hal_i2c_regs_mode;
    uint32 hal_i2c_regs_tx_data;
    uint32 hal_i2c_regs_rx_data;
    uint32 hal_i2c_regs_tx_rd_wrb;
    uint32 hal_i2c_regs_tx_no_bytes;
    uint32 hal_i2c_regs_rx_no_bytes;
    uint32 hal_i2c_regs_rx_no_bytes_master;
    uint32 hal_i2c_regs_go;
    uint32 hal_i2c_regs_rx_early_threshold;
    uint32 hal_i2c_regs_rx_auto_nag_byte_cnt;
    uint32 hal_i2c_regs_half_time;
    uint32 hal_i2c_regs_address;
    uint32 hal_i2c_regs_addr_type;
    uint32 hal_i2c_regs_soft_reset;
    uint32 hal_i2c_regs_slave_rwb;
    uint32 hal_i2c_regs_master_sm;
    uint32 hal_i2c_regs_slave_sm;
    uint32 hal_i2c_regs_slave_enable;
    uint32 hal_i2c_regs_master_send_restart;
}HAL_I2C_REGS;

/*!< I2C interrupt type*/
typedef enum
{
    /*!< I2C slave address interrupt*/
    HAL_I2C_INTER_SLAVE_ADDRESS,
    /*!< I2C rx early data level interrupt*/
    HAL_I2C_INTER_RX_EARLY_DATA_LEVEL,
    /*!< I2C rx auto nag interrupt*/
    HAL_I2C_INTER_RX_AUTO_NAG,
    /*!< I2C rx overflow interrupt*/
    HAL_I2C_INTER_RX_OVERFLOW,
    /*!< I2C tx data starve interrupt*/
    HAL_I2C_INTER_TX_DATA_STARVE,
    /*!< I2C master bad ack interrupt*/
    HAL_I2C_INTER_MASTER_BAD_ACK,
    /*!< I2C master bad data ack interrupt*/
    HAL_I2C_INTER_MASTER_BAD_DATA_ACK,
    /*!< I2C tx complete interrupt*/
    HAL_I2C_INTER_TX_COMPLETE,
    /*!< I2C rx complete interrupt*/
    HAL_I2C_INTER_RX_COMPLETE,
    /*!< I2C slave start detect interrupt*/
    HAL_I2C_INTER_SLAVE_START_DETECT,
    /*!< I2C interrupt number*/
    HAL_I2C_INTER_MAX_NUM,
}HAL_I2C_INTER;

/*!< HAL I2C retern type*/
typedef enum
{
    /*!<HAL I2C retern Ok*/
    HAL_I2C_RET_OK,
    /*!<HAL I2C retern error*/
    HAL_I2C_RET_ERROR,
} HAL_I2C_RET;

/*!< I2C master sub block machine status */
typedef enum
{
    HAL_I2C_BUS_SM_WAIT_HOST = 0xF0,
    HAL_I2C_BUS_SM_START_PAUSE = 0xF8,
    HAL_I2C_BUS_SM_PAUSE_WR = 0xE5,
    HAL_I2C_BUS_SM_PAUSE_RD = 0xD5,
    HAL_I2C_BUS_SM_WAIT_GO_LOW = 0xA0,
}HAL_I2C_BUS_SM_STATUS;

/**
 * Init I2C, disables clocks and interrupts ready for use
 * @return none
 */
void hal_i2c_init(void);

/**
 * Deinit I2C, disable clock and interrupt
 * @return none
 */
void hal_i2c_deinit(void);

/**
 * Claim I2C bus
 * @return I2C_BUS
 */
I2C_BUS hal_i2c_claim(void);

/**
 * Release I2C BUS
 * @param  I2C bus
 * @return None
 */
void hal_i2c_release (I2C_BUS bus);

/**
 * Enable I2C clock in the clock register
 * @param  I2C_BUS
 * @return None
 */
void hal_i2c_enable_clock(I2C_BUS i2c_bus);

/**
 * Disable I2C clock in the clock register
 * @param  I2C_BUS
 * @return None
 */
void hal_i2c_disable_clock(I2C_BUS i2c_bus);

/**
 * Get The value of the interrupt type in interrupt status register
 * @param  I2C_BUS
 * @param  I2C interrupt type
 * @return 1 The value of the interrupt flag is 1
           0 The value of the interrupt flag is 0
 */
uint8 hal_i2c_get_interrupt_status(I2C_BUS i2c_bus, HAL_I2C_INTER i2c_interrupt_type);

/**
 * Get the value of the master sub block machine status register
 * @param  I2C_BUS
 * @return Master sub block machine status
 */
uint32 hal_i2c_get_master_sm_status(I2C_BUS i2c_bus);

/**
 * Enable I2C interrupt type
 * @param  I2C_BUS
 * @param  I2C interrupt type
 * @return None
 */
void hal_i2c_enable_interrupt(I2C_BUS i2c_bus, HAL_I2C_INTER i2c_interrupt_type);

/**
 * Disable I2C interrupt type
 * @param  I2C_BUS
 * @param  I2C interrupt type
 * @return None
 */
void hal_i2c_disable_interrupt(I2C_BUS i2c_bus, HAL_I2C_INTER i2c_interrupt_type);

/**
 * Check whether the I2C interrupt type is enabled in interrupt enable register
 * @param  I2C_BUS
 * @param  I2C interrupt type
 * @return 1  The I2C interrupt type is enabled
           0  The I2C interrupt type is disabled
 */
uint8  hal_i2c_interrupt_is_enable(I2C_BUS i2c_bus, HAL_I2C_INTER i2c_interrupt_type);

/**
 * Clear I2C interrupt flag in interrupt clear register
 * @param  I2C_BUS
 * @param  I2C interrupt type
 * @return None
 */
void hal_i2c_clear_interrupt_flag(I2C_BUS i2c_bus, HAL_I2C_INTER i2c_interrupt_type);

/**
 * Send A start signal
 * @param  I2C_BUS
 * @return None
 */
void hal_i2c_start(I2C_BUS i2c_bus);

/**
 * Send A restart for next transmission
 * @param  I2C_BUS
 * @return None
 */
void hal_i2c_restart(I2C_BUS i2c_bus);

/**
 * Set I2C soft reset
 * @param  I2C_BUS
 * @return None
 */
void hal_i2c_soft_reset(I2C_BUS i2c_bus);

/**
 * Set I2C mode
 * @param  I2C_BUS
 * @param  I2C_MODE_MASTER Or I2C_MODE_SLAVE
 * @return None
 */
void hal_i2c_set_mode(I2C_BUS i2c_bus, HAL_I2C_BUS_MODE i2c_mode);

/**
 * Set I2C half time
 * @param  I2C_BUS
 * @param  I2C half time
 * @return None
 */
void hal_i2c_set_clock_half_time(I2C_BUS i2c_bus, uint32 i2c_half_time);

/**
 * Set I2C address type
 * @param  I2C_BUS
 * @param  I2C_7_BIT_ADDR_TYPE or I2C_10_BIT_ADDR_TYPE
 * @return None
 */
void hal_i2c_set_addr_type(I2C_BUS i2c_bus, HAL_I2C_ADDRESS_TYPE i2c_addr_type);

/**
 * Set I2C address
 * @param  I2C_BUS
 * @param  I2C 7 bit address or I2C 10 bit address
 * @return None
 */
void hal_i2c_set_addr(I2C_BUS i2c_bus, uint16 i2c_addr);

/**
 * Set I2C slave access
 * @param  I2C_BUS
 * @param  I2C_SLAVE_ENABLE_VALUE Or I2C_SLAVE_DISABLE_VALUE
 * @return None
 */
void hal_i2c_slave_access(I2C_BUS i2c_bus, HAL_I2C_SLAVE_ACCESS i2c_slave_access);

/**
 * Get I2C receive data
 * @param  I2C_BUS
 * @return The value of receive register
 */
uint32 hal_i2c_get_rx_data(I2C_BUS i2c_bus);

/**
 * Get I2C receive data length
 * @param  I2C_BUS
 * @return The value of receive register
 */
uint32 hal_i2c_get_rx_length(I2C_BUS i2c_bus);

/**
 * Get I2C transmite data
 * @param  I2C_BUS
 * @param  transmite data buff point
 * @return The value of transmite register
 */
void hal_i2c_set_tx_data(I2C_BUS i2c_bus, const uint32* buff);

/**
 * Set I2C operation type
 * @param  I2C_BUS
 * @param  I2C_OPERATION_WRITE Or I2C_OPERATION_READ
 * @return None
 */
void hal_i2c_set_operation_type(I2C_BUS i2c_bus, HAL_I2C_OPERATION i2c_operation_type);

/**
 * Set I2C receive early threshold number
 * @param  I2C_BUS
 * @param  I2C receive early threshold number
 * @return None
 */
void hal_i2c_set_rx_early_threshold(I2C_BUS i2c_bus, uint8 i2c_rx_early_threshold);

/**
 * Set I2C receive auto nag byte cnt
 * @param  I2C_BUS
 * @param  I2C receive auto nag Byte cnt
 * @return None
 */
void hal_i2c_rx_auto_nag_byte_cnt(I2C_BUS i2c_bus, uint8 i2c_rx_auto_nag_byte_cnt);


/**
 * I2C master transmite data config
 * @param  I2C_BUS
 * @param  I2C slave address
 * @param  I2C transmite number of byte
 * @return None
 */
void hal_i2c_master_transmite_config(I2C_BUS i2c_bus, uint16 addr, uint8 num_of_bytes);

/**
 * I2C master send start signal, slave address with read bit
 * or slave address with write bit
 * @param  I2C_BUS
 * @return I2C_RET_ERROR I2C transmite fail
           I2C_RET_OK    I2C transmite succ
 */
HAL_I2C_RET hal_i2c_master_send_slave_addr(I2C_BUS i2c_bus);

/**
 * I2C master receive data config
 * @param  I2C_BUS
 * @param  I2C slave address
 * @param  I2C receive number of byte
 * @return None
 */
void hal_i2c_master_receive_config(I2C_BUS i2c_bus, uint16 addr, uint8 num_of_bytes);

/**
 * Sets the callback to be used by the I2C
 * @param Func the callback function to sse
 * @return None
 */
void hal_i2c_set_callback(hal_i2c_callback func);

/** @} end of group DRIVER_HAL_I2C */

#endif
