/******************************************************************************
 * @brief    Update Functions for Hi21XX
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef LIB_NEUL_UPDATE_TYPES_H_
#define LIB_NEUL_UPDATE_TYPES_H_

#include "neul_error_types.h"
#include "neul_update_etypes.h"
#include <stdint.h>

/** @addtogroup libNEUL_UPDATE
 * @{
 * */

typedef enum
{
    NEUL_UPDATE_RET_OK,
    NEUL_UPDATE_RET_DOWNLOADING,
    NEUL_UPDATE_RET_VALIDATING,
    NEUL_UPDATE_RET_UPGRADING,
    NEUL_UPDATE_RET_ERROR
} NEUL_UPDATE_RET;

#define UPDATE_ALL_AVAILABLE_SIZE   UINT32_MAX

/** @} end of group libNEUL_UPDATE */

#endif /* LIB_NEUL_UPDATE_TYPES_H_ */
