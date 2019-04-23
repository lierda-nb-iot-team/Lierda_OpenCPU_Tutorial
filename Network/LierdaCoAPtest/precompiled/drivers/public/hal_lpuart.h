/******************************************************************************
 * @brief    LOW POWER UART HAL INTERFACE
 * Copyright (c) 2015 NEUL LIMITED
******************************************************************************/
#ifndef HAL_LPUART_H
#define HAL_LPUART_H

#include "neulfw.h"
#include "platform_definitions.h"
#include "hal_lpuart_specific.h"


/** @defgroup DRIVER_HAL_LPUART Hi211X HAL LP UART Driver
 * HAL LPUART Driver
 * @ingroup DRIVER_HAL
 * @{
 * */

typedef enum
{
    HAL_LPUART_WORDLENGTH_5BIT,
    HAL_LPUART_WORDLENGTH_6BIT,
    HAL_LPUART_WORDLENGTH_7BIT,
    HAL_LPUART_WORDLENGTH_8BIT
} HAL_LPUART_WORDLENGTH; // Wordlengths for LPUART

typedef enum
{
    HAL_LPUART_PARITY_SET_DISABLED,
    HAL_LPUART_PARITY_SET_ODD,
    HAL_LPUART_PARITY_SET_EVEN
} HAL_LPUART_PARITY_SET; // Parity Enable for LPUART


typedef enum
{
    HAL_LPUART_STOP_SET_ENABLED,
    HAL_LPUART_STOP_SET_DISABLED
} HAL_LPUART_STOP_SET; // Stop bit Enable for LPUART


typedef enum
{
    HAL_LPUART_INTERRUPT_NONE,
    HAL_LPUART_INTERRUPT_PARITY_ERROR,
    HAL_LPUART_INTERRUPT_FRAME_ERROR,
    HAL_LPUART_INTERRUPT_SUCCESSFUL_WORD,
    HAL_LPUART_INTERRUPT_START_BIT,
} HAL_LPUART_INTERRUPT; // Stop bit Enable for LPUART


typedef enum
{
    HAL_LPUART_SYNCMODE_DEFAULT,
    HAL_LPUART_SYNCMODE_LATER,
    HAL_LPUART_SYNCMODE_EARLIER,
    HAL_LPUART_SYNCMODE_EVEN_EARLIER
} HAL_LPUART_SYNCMODE; // Sync Mode for LPUART


#define HAL_LPUART_ISER_INT_MASK (0x00010000)

#define HAL_LPUART_FIFO_MASK (0x0700)

/** RX and TX FIFO sizes */
#define HAL_LPUART_RX_FIFO_SIZE  (7)
#define HAL_LPUART_TX_FIFO_SIZE  (3)

#define HAL_LPUART_CTRL_SYNC_MODE_BIT_SHIFT (16)
#define HAL_LPUART_CTRL_SYNC_MODE_MASK (3u<<HAL_LPUART_CTRL_SYNC_MODE_BIT_SHIFT)

#define HAL_LPUART_CTRL_WORDLENGTH_SHIFT (18)
#define HAL_LPUART_CTRL_WORDLENGTH_MASK (3u<<HAL_LPUART_CTRL_WORDLENGTH_SHIFT)

#define HAL_LPUART_CTRL_INT_START_BIT_SHIFT (20)
#define HAL_LPUART_CTRL_INT_START_BIT_MASK (1u<<HAL_LPUART_CTRL_INT_START_BIT_SHIFT)

#define HAL_LPUART_CTRL_INTERRUPT_SHIFT (20)
#define HAL_LPUART_CTRL_INTERRUPT_MASK (0xFu<<HAL_LPUART_CTRL_INTERRUPT_SHIFT)

#define HAL_LPUART_CTRL_INT_FRAME_ERROR_SHIFT (21)
#define HAL_LPUART_CTRL_INT_FRAME_ERROR_MASK (1u<<HAL_LPUART_CTRL_INT_FRAME_ERROR_SHIFT)

#define HAL_LPUART_CTRL_INT_PARITY_ERROR_SHIFT (22)
#define HAL_LPUART_CTRL_INT_PARITY_ERROR_MASK (1u<<HAL_LPUART_CTRL_INT_PARITY_ERROR_SHIFT)

#define HAL_LPUART_CTRL_INT_SUCCESSFUL_RX_WORD_SHIFT (23)
#define HAL_LPUART_CTRL_INT_SUCCESSFUL_RX_WORD_MASK (1u<<HAL_LPUART_CTRL_INT_SUCCESSFUL_RX_WORD_SHIFT)

#define HAL_LPUART_CTRL_PARITY_SET_SHIFT (24)
#define HAL_LPUART_CTRL_PARITY_SET_MASK (3u<<HAL_LPUART_CTRL_PARITY_SET_SHIFT) // here is included bit 25 (parity invert shift)

#define HAL_LPUART_CTRL_STOP_SET_SHIFT (26)
#define HAL_LPUART_CTRL_STOP_SET_MASK (1u<<HAL_LPUART_CTRL_STOP_SET_SHIFT)

#define HAL_LPUART_STATUS_FRAME_ERRORS_SHIFT (0)
#define HAL_LPUART_STATUS_FRAME_ERRORS_MASK (0xFu<<HAL_LPUART_STATUS_FRAME_ERRORS_SHIFT)

#define HAL_LPUART_STATUS_PARITY_ERRORS_SHIFT (4)
#define HAL_LPUART_STATUS_PARITY_ERRORS_MASK (0xFu<<HAL_LPUART_STATUS_PARITY_ERRORS_SHIFT)

#define HAL_LPUART_STATUS_FIFO_LEVEL_SHIFT (8)
#define HAL_LPUART_STATUS_FIFO_LEVEL_MASK (0x7u<<HAL_LPUART_STATUS_FIFO_LEVEL_SHIFT)


/**
 * @brief Initialise the LPUART HAL module.
 * @return true if the initialisation was successful, false otherwise.
 */
bool hal_lpuart_init( void );

/**
 * de-inits the lpuart - removes the clock from the device
 */
void hal_lpuart_deinit(void);

/**
 * Sets the wordlength for the LPUART.
 * @param wordlength
 */
void hal_lpuart_set_wordlength(HAL_LPUART_WORDLENGTH wordlength);

/**
 * @brief sets the parity to use by the LPUART.
 * @param parity_set
 */
void hal_lpuart_set_parity(HAL_LPUART_PARITY_SET parity_set);

/**
 * @brief Enables or disables the stop bit.
 * @param stop_set
 */
void hal_lpuart_set_stop(HAL_LPUART_STOP_SET stop_set);

/**
 * @brief Clears the lpuart irq interrupt. Handy for tests.
 */
void hal_lpuart_clear_irq(void);

/**
 * @brief Sets the Syncmode for the LPUART
 * @param syncmode
 */
void hal_lpuart_set_syncmode(HAL_LPUART_SYNCMODE syncmode);

/**
 * @brief Set a callback function for the LPUART.
 * @param func callback function of the type void (*func)(void).
 */
void hal_lpuart_set_callback( void (*func)(void) );

/**
 * @brief get the number of accumulated parity errors. Handy for tests.
 * @return
 */
uint8 hal_lpuart_get_parity_errors(void);

/**
 * @brief get the number of accumulated frame errors. Handy for tests.
 * @return
 */
uint8 hal_lpuart_get_frame_errors(void);

/**
 * @brief get the internal LPUART FIFO level
 * @return
 */
uint8 hal_lpuart_get_fifo_level(void);

 /**
 * @brief Gets a word (uint8) from the fifo buffer.
 * @param data return word.
 * @return true if success, false for fail.
 */
bool hal_lpuart_get_word(uint8* data);


/**
 * Set PIN used to signal RTS state
 * @param rts_pin The PIN assigned for LP UART RTS
 * @note Assumes this PIN has been configured as a GPIO output
 * @nate Set to PIN_NONE to disable signalling of RTS state
 */
void hal_lpuart_assign_rts_pin( PIN rts_pin );

/**
 * @brief Set the interrupts for the LPUART.
 * They are cumulative, therefore if you set one type of interrupt and then another the device will interrupt under both conditions.
 * if you want to disable them all set it to HAL_LPUART_INTERRTUPT_NONE.
 * @note Apart from that you need to enable LPUART interrupts hal_lpuart_enable_interrupts()
 * @param interrupt_cause
 */
void hal_lpuart_set_interrupts(HAL_LPUART_INTERRUPT interrupt_cause);

/**
 * @brief Unset the interrupts for the LPUART.
 * They are cumulative, therefore if you unset one type of interrupt and then another the device will not interrupt under both conditions.
 * @note Apart from that you need to enable LPUART interrupts hal_lpuart_enable_interrupts()
 * @param interrupt_cause
 */
void hal_lpuart_unset_interrupts(HAL_LPUART_INTERRUPT interrupt_cause);

/**
 * @brief Disables the LPUART interrupts
 */
void hal_lpuart_disable_interrupts(void);

/**
 * @brief enables the LPUART interrupts
 */
void hal_lpuart_enable_interrupts(void);

/** @} end of group DRIVER_HAL_LPUART */

#endif  /* HAL_LPUART_H */
