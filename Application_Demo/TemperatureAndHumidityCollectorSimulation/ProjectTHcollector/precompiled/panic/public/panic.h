/******************************************************************************
 * @brief    PANIC module interface
 * Copyright (c) 2016 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef LIB_PANIC_PANIC_H
#define LIB_PANIC_PANIC_H

#include "neulfw.h"

/** @defgroup libNEUL_PANIC Hi21XX Panic Reporting
 * Hi21XX Panic Reporting
 * @ingroup HI21XX_MODULES
 * @{
 * */

typedef enum PANIC_ID
{
    // No panic
    PANIC_NONE,

    // Library related panics (other than RTOS)
    PANIC_ARM_CORE,
    PANIC_AT_CMD,
    PANIC_HAL,
    PANIC_ICENI,
    PANIC_DSP,
    PANIC_IRMALLOC_FAIL,
    PANIC_UART,
    PANIC_QUEUE_SLL,
    PANIC_IFLASH,
    PANIC_FLASH_DATA,
    PANIC_ADC,
    PANIC_WATCHDOG,
    PANIC_LOG,
    PANIC_LAYER2,
    PANIC_UTIL,
    PANIC_RADIOTEST,
    PANIC_MAC,
    PANIC_RADIO,
    PANIC_SERVICE_LAYER,
    PANIC_SIM,
    PANIC_LWIP,
    PANIC_ASSERT,
    PANIC_STATS,
    PANIC_UICC,
    PANIC_LL1,
    PANIC_SPI,
    PANIC_SSP0,
    PANIC_SSP1,
    PANIC_REBOOT,
    PANIC_UPDATEPKG,
    PANIC_NVRAM,
    PANIC_I2C0,
    PANIC_I2C1,
    PANIC_LWIP_SUPPORT,
    PANIC_DMA,
    // Someone calling abort() / exit()
    PANIC_EXIT,

    // RTOS related panics
    PANIC_TASK_STACK_OVERFLOW,
    PANIC_TASK_CREATE_FAILED,
    PANIC_INIT_FAILED,

    // Application panics
    PANIC_MAIN,

    // Development panics (these symbols will come and go from the code-base; if they have value beyond temporary debugging then they should be in a category above)
    PANIC_TEMPORARY_DEBUG,
    CCWW_FAULT,
    PANIC_ACTIVITY_INDICATION,
    PANIC_MEMCPY_BUFFER_OVERLAP,

    PANIC_QUEUE_FULL_PDCP,
    PANIC_QUEUE_FULL_L2_DL,
    PANIC_QUEUE_FULL_L2_UL,
    PANIC_QUEUE_FULL_LPP,
    PANIC_QUEUE_FULL_EMMSM,
    PANIC_QUEUE_FULL_AT,
    PANIC_QUEUE_FULL_MN,
    PANIC_QUEUE_FULL_PDH,
    PANIC_QUEUE_FULL_SIM,
    PANIC_QUEUE_FULL_SMS,
    PANIC_QUEUE_FULL_RRC,
    PANIC_QUEUE_FULL_LL1,
    PANIC_QUEUE_FULL_LWIP
} PANIC_ID;

typedef struct {
    PANIC_ID origin;
    uint32   code;
    uint32   timestamp_ms;
} PANIC_DESC;

/**Initialise the panic module*/
extern void panic_init(void);

/**De-initialise the panic module*/
extern void panic_deinit(void);

/** Get the last panic and reset it.
 *
 * @return   True of there was a last panic, when last will be written.
 * @param[out]  last    The PANIC_DESC to write the information to.
 */
extern bool panic_get_and_reset_last(PANIC_DESC *last);

/**Enter into infinite loop so that a debugger can break in and see the stack trace
 * @param source the origin of the panic
 * @param code panic origin specific information
 * @note This can be called before the panic_init is called to support panics during start-up and it will cope
 */
//lint -sem( panic, r_no )  panic does not return.
extern void panic(PANIC_ID source, uint32 code);

/**Conditionally panic or record a problem depending on how this module has been compiled; use this to highlight that a significant problem has occurred while developing
 * @param source the origin of the panic
 * @param code panic origin specific information
 * @note This can be called before the panic_init is called to support panics during start-up and it will cope
 */
extern void panic_fault(PANIC_ID source, uint32 code);

/**Register a callback to be called when panic runs
 * @param panic_callback   the callback function to use
 */
extern void panic_register_callback(void (*panic_callback)(void));

/** @} end of group libNEUL_PANIC */


#endif  /* LIB_PANIC_PANIC_H */
