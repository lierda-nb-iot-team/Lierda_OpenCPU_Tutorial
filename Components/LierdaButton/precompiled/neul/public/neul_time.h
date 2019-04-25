/******************************************************************************
 * @brief Basic time Management Functions for Hi21XX
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef LIB_NEUL_TIME_H_
#define LIB_NEUL_TIME_H_

#include "neulfw.h"
#include "platform_definitions.h"   //needed for CORES
#include "neul_radio_types.h"

/** @defgroup libNEUL_TIME Hi21XX libNEUL Time
 * Hi21XX libNeul Time API
 * @ingroup LIBNEUL
 * @{
 * */

/**
 * @brief time zone reporting callback
 */
typedef void (*neul_set_time_zone_reporting)(void);

/**
 * @brief Set time zone reporting when time zone changed.
 * @param reporting_set_callback callback for reporting
 */
void set_time_zone_reporting(neul_set_time_zone_reporting reporting_set_callback);

/**
 * @brief set system time, need to set time update mode to TIME_UPDATE_MODE_LOCAL first
 * @param current_time current time to set, unit is ms
 * @param time_zone expressed in quarters of an hour, between the local time and GMT; range -96...+96
 * @param daylight_saving_time daylight saving time, uint is 1 hour
 * @param updated_time_fields updated time field flags for current_time, time_zone, daylight_saving_time
 * @return NEUL_RET
 */
NEUL_RET set_system_time_from_apps(uint64 current_time, int8 time_zone, uint8 daylight_saving_time, uint8 updated_time_fields);

/**
 * @brief set time update mode
 * @param time_update_mode time update mode to set
 * @return NEUL_RET_ERROR_RPC or NEUL_RET_OK
 */
NEUL_RET set_time_update_mode(TIME_UPDATE_MODE time_update_mode);

/**
 * @brief get time update mode
 * @param network_time_update_mode time update mode to get
 * @return NEUL_RET_ERROR_RPC or NEUL_RET_OK
 */
NEUL_RET get_time_update_mode(TIME_UPDATE_MODE *time_update_mode);

/** @} end of group libNEUL_TIME */

#endif /* LIB_NEUL_TIME_H_ */
