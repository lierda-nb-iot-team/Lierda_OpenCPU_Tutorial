/******************************************************************************
 * @brief    lwip arch/cc compatible header file
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef LWIP_SUPPORT_ARCH_CC_H_
#define LWIP_SUPPORT_ARCH_CC_H_

#include "neulfw.h"
#include "irmalloc.h"
#include <stdlib.h>
#include "lwip_support_log.h"

/** @addtogroup LWIP_SUPPORT
 * @{
 * */

#define LWIP_NO_STDINT_H 1
#define LWIP_NO_STDDEF_H 1

/**
 * Compiler hints for packing lwip's structures
 */
#define PACK_STRUCT_STRUCT NPACKED_STRUCT
#define PACK_STRUCT_BEGIN
#define PACK_STRUCT_END
#define PACK_STRUCT_FIELD(x) x
#define PACK_STRUCT_FLD_8(x) PACK_STRUCT_FIELD(x)
#define PACK_STRUCT_FLD_S(x) PACK_STRUCT_FIELD(x)

#define LWIP_PLATFORM_ASSERT(x) do {} while(0)

#define LWIP_PLATFORM_DIAG(x) do {  \
        lwip_support_log x; \
        } while(0)

#define U8_F "u"
#define U16_F "u"
#define U32_F "u"
#define X32_F "x"
#define X16_F "x"
#define S16_F "d"
#define S32_F "d"
#define SZT_F ""

#define BYTE_ORDER LITTLE_ENDIAN
#define LWIP_RAND() rand()

/** @} end of group LWIP_SUPPORT */

#endif /* LWIP_SUPPORT_ARCH_CC_H_ */
