/******************************************************************************
 * @brief    Internal definitions for the Internal RAM memory allocator
 * Copyright (c) 2016 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef IRMALLOC_PRIVATE_H_
#define IRMALLOC_PRIVATE_H_

#include <string.h>
#include "neulfw.h"
#if defined USE_FREERTOS
#include "NeulFreeRTOS.h"
#endif
#ifndef CTYPESGEN
#include "hal.h"
#endif
#include "panic.h"

#include "irmalloc.h"
#include "extram_bget.h"

#if defined(NBIOT_SCONS_DEFINE)
void* irmalloc_via_cleanup(size_t size, void* (*allocator)(size_t size));
#endif

#endif /* IRMALLOC_PRIVATE_H_ */
