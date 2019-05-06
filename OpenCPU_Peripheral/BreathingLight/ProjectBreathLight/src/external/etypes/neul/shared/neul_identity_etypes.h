/******************************************************************************
 * @brief    NEUL IDENTITY ETYPES
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/
#ifndef ETYPES_SHARED_NEUL_IDENTITY_ETYPES_H_
#define ETYPES_SHARED_NEUL_IDENTITY_ETYPES_H_

#include "neulfw.h"

#define SERIALNUMBER_LENGTH                 16
#define IMEI_PACKED_LENGTH                   8

typedef struct {
    uint8 value[IMEI_PACKED_LENGTH];
} neul_identity_packed_imei_es;

typedef struct {
    uint8 value[SERIALNUMBER_LENGTH];
} neul_identity_serial_number_es;


#endif /* ETYPES_SHARED_NEUL_IDENTITY_ETYPES_H_ */
