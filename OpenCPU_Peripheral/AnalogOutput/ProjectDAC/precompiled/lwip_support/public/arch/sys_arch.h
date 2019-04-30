/******************************************************************************
 * @brief    lwip sys_arch compatible header file
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef LWIP_SUPPORT_ARCH_SYS_ARCH_H_
#define LWIP_SUPPORT_ARCH_SYS_ARCH_H_

#include "cmsis_os2.h"

/** @addtogroup LWIP_SUPPORT
 * @{
 * */

typedef osMessageQueueId_t  sys_sem_t;
typedef osMessageQueueId_t  sys_mbox_t;
typedef osThreadId_t        sys_thread_t;
typedef uint32              sys_prot_t;
typedef osMutexId_t         sys_mutex_t;

/** @} end of group LWIP_SUPPORT */

#endif /* LWIP_SUPPORT_ARCH_SYS_ARCH_H_ */
