/******************************************************************************
 * @brief    BOUDICA RTOS MASTER SPI DRIVER API
 * Copyright (c) 2017 NEUL LIMITED
******************************************************************************/

#ifndef SRC_DRIVERS_RTOS_SPI_H_
#define SRC_DRIVERS_RTOS_SPI_H_

#include "neulfw.h"
#include "platform_definitions.h"
#include "core.h"

/** @defgroup DRIVER_CMSIS_SPI Hi211X CMSIS SPI Driver
 * CMSIS SPI Driver
 * @ingroup DRIVER_CMSIS
 * @{
 * */

#if CORE == PROTOCOL
#include "hal_spi.h"
#define SPI_W_MAX_LEN   (128)
#define SPI_R_MAX_LEN   (128)
#elif CORE == APPS
#define SPI_W_MAX_LEN   (128)
#define SPI_R_MAX_LEN   (128)
typedef enum
{
    SPI_BUS0,
    SPI_BUS1,
    SPI_BUS_MAX_NUM
}SPI_BUS;
#else
//!< Define For Security, OtherWise Compile Fail
typedef enum
{
    SPI_BUS_MIN_NUM,
    SPI_BUS_MAX_NUM
}SPI_BUS;
#endif

typedef enum
{
    SPI_INTERFACE_SINGLE_BIDIR,
    SPI_INTERFACE_DOUBLE,
    SPI_INTERFACE_QUAD,
    SPI_INTERFACE_SINGLE_UNIDIR,
    SPI_INTERFACE_NONE
}SPI_INTERFACE;

typedef struct
{
    SPI_INTERFACE interface;
    PIN           clk_pin;
    PIN           csb_pin;
    PIN           mosi_pin;
    PIN           miso_pin;
}SPI_PIN;

typedef enum
{
    SPI_CLK_MODE0,
    SPI_CLK_MODE1,
    SPI_CLK_MODE2,
    SPI_CLK_MODE3
}SPI_CLK_MODE;

typedef struct
{
    uint8           data_size;
    uint8           clk_div;
    SPI_CLK_MODE    clk_mode;
}SPI_CONFIGURATION;

typedef enum
{
    SPI_RET_OK,    //!< The operation has completed successfully
    SPI_RET_BUSY,  //!< The operation is in process
    SPI_RET_UNINIT,//!< The operation fail because of not config
    SPI_RET_ERROR  //!< The operation fail because of other reasons
}SPI_RET;

typedef void (*SPI_CALLBACK) (SPI_RET);

void spi_init (void);

void spi_deinit (void);

/**
 * SPI Init
 * @param  bus SPI BUS
 * @return None
 */
SPI_RET spi_claim(SPI_BUS* bus, SPI_PIN spi_pin);

/**
 * SPI Deinit
 * @param  bus SPI BUS
 * @return None
 */
SPI_RET spi_release(SPI_BUS bus);

/**
 * Activate SPI
 * @param  bus           SPI BUS
 * @param  config        SPI Configuration
 * @param  spi_pin       SPI Pin
 * @return SPI_RET_OK    Activate SPI Succ
           SPI_RET_ERROR Activate SPI Fail
 */
SPI_RET spi_activate(SPI_BUS bus, SPI_CONFIGURATION config);

/**
 * DeAactivate SPI
 * @param  bus           SPI BUS
 * @param  ssp_pin       SPI Pin
 * @return SPI_RET_OK    Deactivate SPI Succ
           SPI_RET_ERROR Deactivate SPI Fail
 */
SPI_RET spi_deactivate(SPI_BUS bus);

/**
 * DeAactivate SPI
 * @param  bus           SPI BUS
 * @param  cmd_buff      Cmd Buffer Addr
 * @param  cmd_len       Cmd Len
 * @param  data_buff     Data Buffer Addr
 * @param  data_len      Data Len
 * @param  callback      Callback Function
 * @return SSP_RET_OK    Send Data Succ
           SSP_RET_ERROR Send Data Fail
 */
SPI_RET spi_send_data (SPI_BUS bus, uint8* cmd_buff,uint16 cmd_len, uint8* data_buff, uint16 data_len, SPI_CALLBACK callback);

/**
 * DeAactivate SSP
 * @param  bus           SPI BUS
 * @param  cmd_buff      Cmd Buffer Addr
 * @param  cmd_len       Cmd Len
 * @param  data_buff     Data Buffer Addr
 * @param  data_len      Data Len
 * @param  callback      Callback Function
 * @return SSP_RET_OK    Read Data Succ
           SSP_RET_ERROR Read Data Fail
 */
SPI_RET spi_recv_data (SPI_BUS bus, uint8* cmd_buff, uint16 cmd_len, uint8* data_buff, uint16 data_len, SPI_CALLBACK callback, bool ignore_rx_while_tx);

/** @} end of group DRIVER_CMSIS_SPI */

#endif
