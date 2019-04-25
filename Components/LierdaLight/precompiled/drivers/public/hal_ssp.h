/******************************************************************************
 * @brief    BOUDICA APPS SSP HAL Header File
 * Copyright (c) 2017 NEUL LIMITED
******************************************************************************/
#ifndef HAL_SSP_H_
#define HAL_SSP_H_

#include "neulfw.h"
#include "core.h"

/** @defgroup DRIVER_HAL_SSP Hi211X HAL SSP Driver
 * HAL SSP Driver
 * @ingroup DRIVER_HAL
 * @{
 * */

#define CLKEN_SSP0_MASK         (0x01 << 0)
#define CLKEN_SSP1_MASK         (0x01 << 1)
#define SSP_MIN_DATA_SIZE       (0x04)
#define SSP_MAX_DATA_SIZE       (0x10)
#define SSP_DATA_SIZE_MASK      (0x0F)
#define SSP_DATA_SIZE_SHIFT     (0x00)
#define SSP_FRF_MASK            (0x03)
#define SSP_FRF_SHIFT           (0x04)
#define SSP_SPI_CLK_MODE_MASK   (0x03)
#define SSP_SPI_CLK_MODE_SHIFT  (0x06)
#define SSP_SCR_MASK            (0xFF)
#define SSP_SCR_SHIFT           (0x08)
#define SSP_SSE_MASK            (0x01)
#define SSP_SSE_SHIFT           (0x01)
#define SSP_TXFIFO_FULL_MASK    (0x01)
#define SSP_TXFIFO_FULL_SHIFT   (0x01)
#define SSP_TXFIFO_EMPTY_MASK   (0x01)
#define SSP_TXFIFO_EMPTY_SHIFT  (0x00)
#define SSP_RXFIFO_EMPTY_MASK   (0x01)
#define SSP_RXFIFO_EMPTY_SHIFT  (0x02)
#define SSP_RXFIFO_FULL_MASK    (0x01)
#define SSP_RXFIFO_FULL_SHIFT   (0x03)
#define SSP_BUSY_MASK           (0x01)
#define SSP_BUSY_SHIFT          (0x04)
#define SSP_CPSR_MASK           (0xFF)
#define SSP_MIN_CPSR            (0x02)
#define SSP_MAX_CPSR            (254)

/*!< SSP Interrupt Type */
typedef enum
{
    HAL_SSPRORINTR,/*!< Receive Overrun Interrupt*/
    HAL_SSPRTINTR, /*!< Receive Timeout Interrupt*/
    HAL_SSPRXINTR, /*!< Receive FIFO    Interrupt*/
    HAL_SSPTXINTR, /*!< Transmit FIFO   Interrupt*/
    HAL_SSPMAXINTR
} HAL_SSP_INTER;

/*!< SSP BUS */
typedef enum
{
    SSP_BUS0,
    SSP_BUS1,
    SSP_BUS_MAX_NUM,
    SSP_BUS_NONE = SSP_BUS_MAX_NUM
}SSP_BUS;

/*!< SSP Interface Type */
typedef enum
{
    SSP_SPI_FRF,
    SSP_SSI_FRF,
    SSP_MIC_FRF,
    SSP_MAX_FRF
}SSP_FRF;

/*!< SSP SPI Clock Mode */
typedef enum
{
    SSP_SPI_CLK_MODE0,
    SSP_SPI_CLK_MODE1,
    SSP_SPI_CLK_MODE2,
    SSP_SPI_CLK_MODE3,
    SSP_SPI_CLK_MAX
}SSP_SPI_CLK_MODE;

typedef struct
{
    uint32 SSPCR0;
    uint32 SSPCR1;
    uint16 SSPDR;
    uint16 UNUSED1;         //Pads SSPDR to 32 bit alignment
    uint32 SSPSR;
    uint32 SSPCPSR;
    uint32 SSPIMSC;
    uint32 SSPRIS;
    uint32 SSPMIS;
    uint32 SSPICR;
    uint32 SSPDMACR;
    uint32 RESERVED[0x3EE];
    uint32 SSPPeriphID0;
    uint32 SSPPeriphID1;
    uint32 SSPPeriphID2;
    uint32 SSPPeriphID3;
    uint32 SSPPCellID0;
    uint32 SSPPCellID1;
    uint32 SSPPCellID2;
    uint32 SSPPCellID3;
} ssp_ctrl_t;

#define HAL_SSP_IS_TX_FIFO_FULL(base)  (((base->SSPSR >> SSP_TXFIFO_FULL_SHIFT) & SSP_TXFIFO_FULL_MASK) == 0)
#define HAL_SSP_WRITE_DATA(base, data) (base->SSPDR = data)
#define HAL_SSP_READ_DATA(base)        (base->SSPDR)



/*!< HAL SSP Callback */
typedef void (*HAL_SSP_CALLBACK) (SSP_BUS);

/**
 * Init SSP, Disables Clocks And Interrupts ready for use
 * @return None
 */
void hal_ssp_init(void);

/**
 * Deinit SSP, Disable Clock And Interrupt
 * @return None
 */
void hal_ssp_deinit(void);

/**
 * Claim SSP Bus
 * @return SSP_BUS (SSP_BUS0,SSP_BUS1) or SSP_BUS_NONE if no busses free
 */
SSP_BUS hal_ssp_claim(void);

/**
 * Release SSP BUS
 * @param  bus SSP Bus (SSP_BUS0,SSP_BUS1)
 * @return None
 */
void hal_ssp_release (SSP_BUS bus);

/**
 * Set SSP Data Size
 * @param  bus SSP Bus (SSP_BUS0,SSP_BUS1)
 * @param  data_size Data Bits (4 Bit - 16 Bit)
 * @return True  Set Data Size Success
           False Set Data Size Fail
 */
bool hal_ssp_set_data_size(SSP_BUS bus, uint8 data_size);

/**
 * Get SSP Data Size in bits
 * @param  bus SSP Bus (SSP_BUS0,SSP_BUS1)
 * @return data_size
 */
uint8 hal_ssp_get_data_size(SSP_BUS bus);

/**
 * Set Frame Format (SPI, SSI, MicroWare)
 * @param  bus SSP Bus (SSP_BUS0,SSP_BUS1)
 * @param  frame_format SSP Interface Type (SPI, SSI, MicroWare)
 * @return True  Set Interface Type Success
           False Set Interface Type Fail
 */
bool hal_ssp_set_frame_format(SSP_BUS bus, SSP_FRF frame_format);

/**
 * Set SPI Clock Mode
 * @param  bus SSP Bus (SSP_BUS0,SSP_BUS1)
 * @param  ssp_spi_clk_mode SSP-SPI Clock Mode (Mode0, Mode1, Mode2, Mode3)
 * @return True  Set SSP-SPI Clock Mode Success
           False Set SSP-SPI Clock Mode Fail
 */
bool hal_ssp_set_spi_mode(SSP_BUS bus, SSP_SPI_CLK_MODE ssp_spi_clk_mode);

/**
 *                             Fpclk
 * SSP Data Bit Rate  = --------------------
 *                        CPSDVR x (1+SCR)
 */

/**
 * Set SCR
 * @param  bus SSP Bus (SSP_BUS0,SSP_BUS1)
 * @param  scr scr (0 - 255)
 * @return True  Set SCR Success
           False Set SCR Fail
 */
bool hal_ssp_set_serial_clock_rate(SSP_BUS bus, uint8 scr);

/**
 * Set CPSDVR
 * @param  bus SSP Bus (SSP_BUS0,SSP_BUS1)
 * @param  scr cpsr (2 - 254) even values only - the LSB is ignored (always viewed as 0)
 * @return True  Set CPSDVR Success
           False Set CPSDVR Fail
 */
bool hal_ssp_set_clock_prescale(SSP_BUS bus, uint8 cpsr);

/**
 * Enable SSP
 * @param  bus SSP Bus (SSP_BUS0,SSP_BUS1)
 * @return None
 */
void hal_ssp_enable (SSP_BUS bus);

/**
 * Disable SSP
 * @param  bus SSP Bus (SSP_BUS0,SSP_BUS1)
 * @return None
 */
void hal_ssp_disable (SSP_BUS bus);

/**
 * Enable Interrupt
 * @param  bus SSP Bus (SSP_BUS0,SSP_BUS1)
 * @param  interr Interrupt Type
 * @return None
 */
void hal_ssp_enable_interrupt(SSP_BUS bus, HAL_SSP_INTER interr);

/**
 * Mask off Interrupt
 * @param  bus SSP Bus (SSP_BUS0,SSP_BUS1)
 * @param  interr Interrupt Type
 * @return None
 */
void hal_ssp_disable_interrupt(SSP_BUS bus, HAL_SSP_INTER interr);

/**
 * Register Interrupt Callback
 * @param  bus SSP Bus (SSP_BUS0,SSP_BUS1)
 * @param  interr Interrupt Type
 * @param  callback CallBack Function
 * @return None
 */
void hal_ssp_set_interrupt_callback(SSP_BUS bus, HAL_SSP_INTER interr, HAL_SSP_CALLBACK callback);

/**
 * SSP Write Data
 * @param  bus  SSP Bus (SSP_BUS0,SSP_BUS1)
 * @param  data Write Value
 * @return None
 */
void hal_ssp_write_data(SSP_BUS bus, uint16 data);

/**
 * SSP Read Data
 * @param  bus  SSP Bus (SSP_BUS0,SSP_BUS1)
 * @return uint16 Read Data Value
 */
uint16 hal_ssp_read_data (SSP_BUS bus);

/**
 * SSP Check TX FIFO Is Full
 * @param  bus  SSP Bus (SSP_BUS0,SSP_BUS1)
 * @return True  TXFIFO Is Full
           False TXFIFO Is Not Full
 */
bool hal_ssp_tx_fifo_is_full(SSP_BUS bus);

/**
 * SSP Check RX FIFO Is Full
 * @param  bus  SSP Bus (SSP_BUS0,SSP_BUS1)
 * @return True  RXFIFO Is Full
           False RXFIFO Is Not Full
 */
bool hal_ssp_rx_fifo_is_full (SSP_BUS bus);

/**
 * SSP Check RX FIFO Is Empty
 * @param  bus  SSP Bus (SSP_BUS0,SSP_BUS1)
 * @return True  RXFIFO Is Empty
           False RXFIFO Is Not Empty
 */
bool hal_ssp_rx_fifo_is_empty(SSP_BUS bus);

/**
 * SSP Check TX FIFO Is Empty
 * @param  bus  SSP Bus (SSP_BUS0,SSP_BUS1)
 * @return True  TXFIFO Is Empty
           False TXFIFO Is Not Empty
 */
bool hal_ssp_tx_fifo_is_empty(SSP_BUS bus);

/**
 * SSP Check Is Busy
 * @param  bus  SSP Bus (SSP_BUS0,SSP_BUS1)
 * @return True  SSP Is Busy
           False SSP Is Idle
 */
bool hal_ssp_is_busy(SSP_BUS bus);

bool hal_ssp_interrupt_is_set(SSP_BUS bus, HAL_SSP_INTER interr);

/**
 * Disables all the SSP interrupts, and sets the callbacks to NULL
 * @param bus Which bus to disable the interrupts off
 */
void hal_ssp_disable_all_interrupts(SSP_BUS bus);

/**
 * Gets the base ssp_ctrl_t address of this bus for use with the fast defines
 * @param bus The bus we are intrested in
 * @return The address of the register
 */
volatile ssp_ctrl_t *hal_ssp_get_base(SSP_BUS bus);

/**
 * IRQ handler for SSP0
 * @return None
 */
void IRQ_SSP0_Handler(void);

/**
 * IRQ handler for SSP1
 * @return None
 */
void IRQ_SSP1_Handler (void);

/** @} end of group DRIVER_HAL_SSP */

#endif /* HAL_SSP_H_ */
