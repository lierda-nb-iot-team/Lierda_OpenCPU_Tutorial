/*----------------------------------------------------------------------------
 * Copyright (c) <2013-2017>, <Huawei Technologies Co., Ltd>
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Notice of Export Control Law
 * ===============================================
 * Huawei LiteOS may be subject to applicable export control laws and regulations, which might
 * include those applicable to Huawei LiteOS of U.S. and the country in which you are located.
 * Import, export and usage of Huawei LiteOS in any manner by you shall be in compliance with such
 * applicable export control laws and regulations.
 *---------------------------------------------------------------------------*/

#ifndef _LOS_SLPPE_H
#define _LOS_SLPPE_H
#include "los_config.h"
#ifdef LOS_RUNSTOP
#include "los_typedef.h"

//#define SLEEP_DEBUG

#ifdef SLEEP_DEBUG
unsigned int vote_status[3];
#endif
void los_SuppressTicksAndSleep(UINT32 xExpectedIdleTime);
#endif

typedef enum
{
    eAbortSleep = 0,        /* A task has been made ready or a context switch pended since portSUPPORESS_TICKS_AND_SLEEP() was called - abort entering a sleep mode. */
    eStandardSleep,         /* Enter a sleep mode that will not last any longer than the expected idle time. */
    eNoTasksWaitingTimeout  /* No tasks are waiting for a timeout so it is safe to enter a sleep mode that can only be exited by an external interrupt. */
} eSleepModeStatus;


/** The number of vetoes registered for disallowing the system clock from being stopped
 * @note Get the stop clock vetoes value.
 */
uint32 getStopClockVetoesValue(void);

/**Add a veto on RTOS stopping the system clocks
 * @note If there is a veto on stopping the system clocks then the tickless RTOS operation will not be able to go into a low power sleep.
 *       Many vetoes may be independently added or removed; one or more will prevent RTOS stopping the system clocks.
 *       This function may be called in an interrupt context
 *       This function is thread safe and may be called before or after the RTOS scheduler is started
 */
void tickless_add_stop_clocks_veto(void);

/**Remove a veto on RTOS stopping the system clocks
 * @note This function will not do anything if there are no vetoes to remove
 *       Many vetoes may be independently added or removed; one or more will prevent RTOS stopping the system clocks.
 *       This function may be called in an interrupt context
 *       This function is thread safe and may be called before or after the RTOS scheduler is started
 */
void tickless_remove_stop_clocks_veto(void);

#endif
