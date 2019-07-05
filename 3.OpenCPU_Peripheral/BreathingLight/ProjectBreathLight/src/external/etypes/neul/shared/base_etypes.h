/******************************************************************************
 * @brief    BASE ETYPES
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/
#ifndef ETYPES_SHARED_BASE_ETYPES_H_
#define ETYPES_SHARED_BASE_ETYPES_H_

#include "neulfw.h"

typedef struct {
    uint8 value;
} uint8_es;


typedef struct {
    uint16 value;
} uint16_es;


typedef struct {
    uint32 value;
} uint32_es;


typedef struct {
    bool value;
} bool_es;


typedef uint8 generic_array_es;

typedef uint8 UNDETERMINED_SIZE_BUFFER[0];

typedef  ETYPES_ASCII UNDETERMINED_SIZE_STRING[0];


#endif /* ETYPES_SHARED_BASE_ETYPES_H_ */
