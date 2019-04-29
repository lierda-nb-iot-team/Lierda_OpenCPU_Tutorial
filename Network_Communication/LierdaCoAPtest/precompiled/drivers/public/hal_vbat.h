/******************************************************************************
 * @brief    Hi2115 VBAT HAL interface.
 * Copyright (c) 2017 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef HAL_VBAT_H_
#define HAL_VBAT_H_

#include "core.h"
//TODO: Doxygen groups stuff?


/**
 * @brief Enables resistive divider from VBAT for test mux
 * @param None
 * @param None
 */
void hal_vbat_enable_div(void);

/**
 * @brief Enables resistive divider from VBAT for test mux
 * @param None
 * @param None
 */
void hal_vbat_disable_div(void);

#endif
