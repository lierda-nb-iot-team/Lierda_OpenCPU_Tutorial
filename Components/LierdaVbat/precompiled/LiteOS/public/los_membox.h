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

#include "los_config.h"

#define BOX_ALIGN_8                   0x80000000
/*----------------------------------------------------------------------------
 *      Global Functions
 *---------------------------------------------------------------------------*/

/**
 * @ingroup los_membox
 * Define whether to check the address validity
 */
#if (LOSCFG_BASE_MEM_NODE_INTEGRITY_CHECK == YES)
#define LOS_MEMBOX_CHECK
#endif

typedef struct tagMemBoxCB
{
#if (LOSCFG_BASE_MEM_NODE_INTEGRITY_CHECK == YES)
    UINT32 uwMemCheck;
#endif
    UINT32  uwMaxBlk;
    UINT32  uwBlkCnt;
    UINT32  uwBlkSize;                  /* Memory block size                       */
}OS_MEMBOX_S;

typedef OS_MEMBOX_S * OS_MEMBOX_S_P;

#ifdef LOS_MEMBOX_CHECK
#define LOS_MEMBOX_MAGIC_SIZE    4
#else
#define LOS_MEMBOX_MAGIC_SIZE    0
#endif

extern UINT32    LOS_MemboxInit   (VOID *pBoxMem, UINT32 uwBoxSize, UINT32 uwBlkSize);
extern VOID *LOS_MemboxAlloc  (VOID *pBoxMem);
extern UINT32   LOS_MemboxFree   (VOID *pBoxMem, VOID *pBox);
extern VOID LOS_MemboxClr (VOID *pBoxMem, VOID *pBox);
//extern  UINT32 LOS_LDREX(volatile UINT32 *uwAddr);
//UINT32 LOS_STREX(UINT32 uwValue, volatile UINT32 *puwAddr);
//VOID LOS_CLREX(VOID);

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
