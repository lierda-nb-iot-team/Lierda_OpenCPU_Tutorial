/******************************************************************************
 * @brief    PRESERVE INTERFACE for Hi21XX security core
 * Copyright (c) 2017 Huawei Technologies Co. Ltd
******************************************************************************/
#ifndef PRESERVE_H_
#define PRESERVE_H_
#include "core.h"
#include "neulfw.h"
#include "hal.h"
#include "panic.h"
#if CORE == SECURITY
#include "preserve_security.h"
#endif

/** @defgroup HI21XX_MODULES Hi21XX Modules
 * Hi21XX Modules
 * @ingroup HI21XX_MODULES
 * @{
 * */

/** @} end of group libNEUL_SYSTEM */

/** @defgroup libNEUL_PRESERVE Hi21XX Preserved Region
 * Hi21XX libNeul Preserved Region
 * @ingroup HI21XX_MODULES
 * @{
 * */

#define PRESERVE VAR_SEGMENT("preserve")

PANIC_DESC* get_last_panic_handle(void);

void set_last_panic(PANIC_DESC last_panic);

exception_stack_frame_t* get_exception_stack_frame_handle(void);

void set_exception_stack_frame(exception_stack_frame_t exception_stack_frame_src);

exception_type_t get_last_exception(void);

void set_last_exception(exception_type_t last_exception_src);

bool preserve_valid(void);

void preserve_invalidate(void);

void preserve_init(void);

bool preserve_get_reboot_counter(uint32 *counter);

/** @} end of group libNEUL_PRESERVE */

#endif
