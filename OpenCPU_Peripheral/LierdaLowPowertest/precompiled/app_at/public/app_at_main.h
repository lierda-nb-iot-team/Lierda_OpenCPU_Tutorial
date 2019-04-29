/******************************************************************************
 * @brief    APP AT main interface
 * Copyright (c) 2017 NEUL LIMITED
******************************************************************************/
#ifndef  APP_AT_MAIN_H_
#define  APP_AT_MAIN_H_

#include "app_at_uart_driver_if.h"


/** @defgroup libNEUL_APP_AT Hi21XX AT Command Processor
 * Hi21XX AT Command Processor
 * @ingroup HI21XX_MODULES
 * */

/** @defgroup libNEUL_APP_AT_API Hi21XX AT Command Processor API
 * Hi21XX AT Command Processor API
 * @ingroup libNEUL_APP_AT
 * @{
 * */

/** AT UART received at notify.
 */
typedef void (*at_uart_received_at_notify)(void);

/** Missing Doxygen
 *@return   .
 */
bool at_query_init_status(void);

/** Init for AT
 *@param    none.
 *@return   none.
 */
void at_init(at_uart_received_at_notify callback);

/** Set at in progress status.
 *@param   status The status to set.
 *@return   none.
 */
void at_set_in_progress_status(bool status );

/** AT Command processor main function to call within thread loop
 *@return    none.
 */
void at_main(void);

/** @} end of group libNEUL_APP_AT_API */

#endif
