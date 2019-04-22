/******************************************************************************
 * @brief    Hi211X CMSIS Neul Extensions
 * Copyright (c) 2017 Huawei Technologies Co. Ltd
 ******************************************************************************/

#ifndef _CMSIS_NEUL_EXTENSION_H
#define _CMSIS_NEUL_EXTENSION_H
#include <stdbool.h>

/** @defgroup CMSIS_OS_EXT CMSIS OS Extensions
 * CMSIS OS Extensions
 * @ingroup CMSIS
 * @{
 * */

/**Define a callback function for getting the UART working status
 * @note The UART working status is get via callback function in OS layer
 */
typedef bool (*cb_uart_is_need_awake_fn)(void);


/**Define a callback register fucntion for getting the UART working status
 * @note The UART working status is get via callback function in OS layer
 */
void osUartVetoCallbackRegister(cb_uart_is_need_awake_fn cb);

/**Add a veto on RTOS stopping the system clocks
 * @note If there is a veto on stopping the system clocks then the tickless RTOS operation will not be able to go into a low power sleep.
 *       Many vetoes may be independently added or removed; one or more will prevent RTOS stopping the system clocks.
 *       This function may be called in an interrupt context
 *       This function is thread safe and may be called before or after the RTOS scheduler is started
 */
void osAddStopClocksVeto(void);

/**Remove a veto on RTOS stopping the system clocks
 * @note This function will not do anything if there are no vetoes to remove
 *       Many vetoes may be independently added or removed; one or more will prevent RTOS stopping the system clocks.
 *       This function may be called in an interrupt context
 *       This function is thread safe and may be called before or after the RTOS scheduler is started
 */
void osRemoveStopClocksVeto(void);

/** @} end of group CMSIS_OS_EXT */

#endif
