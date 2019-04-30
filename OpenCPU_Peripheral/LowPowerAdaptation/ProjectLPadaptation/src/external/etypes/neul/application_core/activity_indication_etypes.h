/******************************************************************************
 * @brief    ACTIVITY INDICATION ETYPES
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/
#ifndef ETYPES_APPLICATION_CORE_ACTIVITY_INDICATION_ETYPES_H_
#define ETYPES_APPLICATION_CORE_ACTIVITY_INDICATION_ETYPES_H_

#include "neulfw.h"

#define MAX_INDICATION_DELAY_CONFIG_LEN          4
#define MAX_INDICATION_DELAY_CONFIG_LEN_PLUS_1   5   // MAX_INDICATION_DELAY_CONFIG_LEN + 1

// size checks
CASSERT(MAX_INDICATION_DELAY_CONFIG_LEN_PLUS_1 == (MAX_INDICATION_DELAY_CONFIG_LEN + 1), activity_indication_etypes_h);

typedef uint8 activity_indication_delay_milliseconds_t[MAX_INDICATION_DELAY_CONFIG_LEN_PLUS_1];


#endif /* ETYPES_APPLICATION_CORE_ACTIVITY_INDICATION_ETYPES_H_ */
