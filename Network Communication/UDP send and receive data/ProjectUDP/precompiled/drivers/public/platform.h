/******************************************************************************
 * @brief    Hi2115 Platform Header
 * Copyright (c) 2016 NEUL LIMITED
 ******************************************************************************/

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "platform_core.h"

/** @defgroup DRIVER_PLATFORM Hi21XX Base Driver Definitions
 * Hi21XX Base Driver definitions
 * @ingroup DRIVER_HAL
 * @{
 * */

/**  Reference clock in Hz */
#define CLOCKS_REFERENCE_CLOCK_FREQ   32768

#define ICCID_LEN 20
typedef struct {
    unsigned char iccid_upload;
    char iccid_data[ICCID_LEN];
}projcfg_data;
/** 
 * Peripheral Manager functions supported by all cores 
 */
typedef enum
{
    FUNC_UNCLAIMED        = 0,
    FUNC_GPIO             = 1,
    FUNC_UART0_TXD        = 2,
    FUNC_UART0_TXIR       = 3,
    FUNC_UART0_O2         = 4,
    FUNC_UART0_O1         = 5,
    FUNC_UART0_RTS        = 6,
    FUNC_UART0_DTR        = 7,
    FUNC_UART0_RXD        = 8,
    FUNC_UART0_RXIR       = 9,
    FUNC_UART0_CTS        = 10,
    FUNC_UART0_DCD        = 11,
    FUNC_UART0_DSR        = 12,
    FUNC_UART0_RI         = 13,
    FUNC_UART1_TXD        = 14,
    FUNC_UART1_TXIR       = 15,
    FUNC_UART1_O2         = 16,
    FUNC_UART1_O1         = 17,
    FUNC_UART1_RTS        = 18,
    FUNC_UART1_DTR        = 19,
    FUNC_UART1_RXD        = 20,
    FUNC_UART1_RXIR       = 21,
    FUNC_UART1_CTS        = 22,
    FUNC_UART1_DCD        = 23,
    FUNC_UART1_DSR        = 24,
    FUNC_UART1_RI         = 25,
    FUNC_LPUART_RXD       = 26,
    FUNC_LPUART_TXD       = 27,
    FUNC_DBG_CLK0         = 112,
    FUNC_DBG_CLK1         = 113,
    FUNC_DBG_CLK2         = 114,
    FUNC_DBG_CLK3         = 115,
    FUNC_RADIO_PIO        = 128,
    FUNC_UICC_CLK         = 129,
    FUNC_UICC_RST         = 130,
    FUNC_UICC_IO          = 131,
    FUNC_DSP_TMS          = 132,
    FUNC_DSP_TDI          = 133,
    FUNC_DSP_TDO          = 134,
    FUNC_DSP_TRST         = 135,
    FUNC_SPI_SCLK         = 136,
    FUNC_SPI_CSB          = 137,
    FUNC_SPI_UNIDIR_IN    = 138,
    FUNC_SPI_UNIDIR_OUT   = 139,
    FUNC_SPI_BIDIR_DATA0  = 140,
    FUNC_SPI_BIDIR_DATA1  = 141,
    FUNC_SPI_BIDIR_DATA2  = 142,
    FUNC_SPI_BIDIR_DATA3  = 143,
    FUNC_DSP_TCK          = 144,
    FUNC_RADIO_RFFE_SCLK  = 145,
    FUNC_RADIO_RFFE_SDATA = 146,
    FUNC_PWM0             = 192,
    FUNC_PWM0B            = 193,
    FUNC_PWM1             = 194,
    FUNC_PWM1B            = 195,
    FUNC_SSP0TXD          = 196,
    FUNC_SSP0RXD          = 197,
    FUNC_SSP0TRX          = 198,
    FUNC_SSP0CLK          = 199,
    FUNC_SSP0FSS          = 200,
    FUNC_SSP1CLK          = 201,
    FUNC_SSP1FSS          = 202,
    FUNC_SSP1TXD          = 203,
    FUNC_SSP1RXD          = 204,
    FUNC_SSP1TRX          = 205,
    FUNC_I2C0_SDA         = 206,
    FUNC_I2C0_SCL         = 207,
    FUNC_I2C1_SDA         = 208,
    FUNC_I2C1_SCL         = 209,
    FUNC_UART2_TXD        = 210,
    FUNC_UART2_TXIR       = 211,
    FUNC_UART2_O2         = 212,
    FUNC_UART2_O1         = 213,
    FUNC_UART2_RTS        = 214,
    FUNC_UART2_DTR        = 215,
    FUNC_UART2_RXD        = 216,
    FUNC_UART2_RXIR       = 217,
    FUNC_UART2_CTS        = 218,
    FUNC_UART2_DCD        = 219,
    FUNC_UART2_DSR        = 220,
    FUNC_UART2_RI         = 221,
    FUNC_MAX              = 222    //!< Limit to range of valid values
} FUNC;

/** @} end of group DRIVER_PLATFORM */

#endif /* PLATFORM_H_ */
