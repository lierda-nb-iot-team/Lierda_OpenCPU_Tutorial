/******************************************************************************
 * @brief    ETYPES
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef __ETYPES_H
#define __ETYPES_H

#ifndef NEULFW_H
#error "Please include etypes.h via neulfw.h"
#endif


#define ETYPES_ENUM_HOLDER_TYPE(y)     y // Enum holding type
#define ETYPES_ASCII   ASCII

/** Integer type big enough to hold a data pointer. */
typedef U32      uintptr;

typedef S8       int8;
typedef S16      int16;
typedef S32      int32;

typedef U8       uint8;
typedef U16      uint16;
typedef U32      uint32;

typedef BOOL8    bool;

#endif/* __ETYPES_H */

