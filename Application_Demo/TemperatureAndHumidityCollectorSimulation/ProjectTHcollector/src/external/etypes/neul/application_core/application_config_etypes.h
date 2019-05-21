/******************************************************************************
 * @brief    APPLICATION CONFIG ETYPES
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/
#ifndef ETYPES_APPLICATION_CORE_APPLICATION_CONFIG_ETYPES_H_
#define ETYPES_APPLICATION_CORE_APPLICATION_CONFIG_ETYPES_H_


#include "neulfw.h"

#define PIN_MAP_BYTES         5
#define PIN_STATE_BYTES       5
#define PIN_MAP_BUFFER_SIZE   10

// size checks
CASSERT(PIN_MAP_BUFFER_SIZE == (PIN_MAP_BYTES + PIN_STATE_BYTES), application_config_etypes_h);

typedef uint8 pin_map_buffer_t[PIN_MAP_BUFFER_SIZE];


#endif /* ETYPES_APPLICATION_CORE_APPLICATION_CONFIG_ETYPES_H_ */
