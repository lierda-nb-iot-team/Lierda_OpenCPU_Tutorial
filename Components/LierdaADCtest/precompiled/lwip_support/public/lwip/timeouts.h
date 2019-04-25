/******************************************************************************
 * @brief    simple timers for lwip
 * Copyright (c) 2017 Huawei Technologies Co. Ltd
******************************************************************************/
#ifndef _TIMEOUTS_H
#define _TIMEOUTS_H

#include <lwip/arch.h>

/** @addtogroup LWIP_SUPPORT
 * @{
 * */

/** timeout callback function prototype
 * @param arg  arguements to pass to callback
 */
typedef void (* sys_timeout_handler)(void *arg);

/** current time in milliseconds,
 */
u32_t sys_now(void);

/** add a timeout
 * @param time to trigger handler at
 * @param handler to add
 * @param arguments to handler to add
 */
void sys_timeout(u32_t msecs, sys_timeout_handler handler, void *arg);

/** remove a timeout
 * @param handler to remove
 * @param arguments to handler to remove
 */
void sys_untimeout(sys_timeout_handler handler, const void *arg);

/** @} end of group LWIP_SUPPORT */

#endif /* _TIMEOUTS_H */
