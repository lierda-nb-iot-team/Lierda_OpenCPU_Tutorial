/******************************************************************************
 * @brief    lwip stats compatible header file
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/


#ifndef LWIP_SUPPORT_SYS_H
#define LWIP_SUPPORT_SYS_H

#include "lwip/opt.h"
#include "arch/sys_arch.h"

/** @addtogroup LWIP_SUPPORT
 * @{
 * */

/** Function prototype for thread functions */
typedef void (*lwip_thread_fn)(void *arg);

/** Create a nbew thread
 * @param name of thread
 * @param thread function to execute
 * @param arg parameters passed in
 * @param stacksize stack size in bytes for the new thread
 * @param prio priority of the new thread */
sys_thread_t sys_thread_new(const char *name, lwip_thread_fn thread, void *arg, int stacksize, int prio);

/** Ticks since power up.
 * @return ticks since power up
 */
u32_t sys_jiffies(void);

/** @} end of group LWIP_SUPPORT */

#endif /* LWIP_SUPPORT_SYS_H */
