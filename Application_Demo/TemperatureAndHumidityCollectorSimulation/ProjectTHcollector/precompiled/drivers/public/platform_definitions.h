/******************************************************************************
 * @brief    Hi2115 Platform Definitions
 * Copyright (c) 2016 NEUL LIMITED
 ******************************************************************************/

#ifndef PLATFORM_DEFINITIONS_H_
#define PLATFORM_DEFINITIONS_H_

#include "platform_types.h"

/** @defgroup BASE_DEFS Hi21XX Base Definitions
 * Hi21XX Base Definitions
 * @ingroup Hi21XX_Base
 * @{
 * */

/* This is needed in Security and Protocol Core */
#define NVCONFIG_RF_HEADER_SIZE_IN_BYTES    (16)
#define NVCONFIG_RF_MAX_FLASH_SIZE_IN_BYTES ((16*1024) - NVCONFIG_RF_HEADER_SIZE_IN_BYTES)

/** PINS Fixed in the Chip Used for Codeloader */
#define CHIP_FIXED_RX_PIN        PIN_13
#define CHIP_FIXED_TX_PIN        PIN_18


/** @} end of group BASE_DEFS */


#endif /* PLATFORM_DEFINITIONS_H_ */
