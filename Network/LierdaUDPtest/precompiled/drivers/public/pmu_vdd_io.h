/******************************************************************************
 * @brief    Hi2115 PMU VDD IO DRIVER HEADER FILE
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef PMU_VDD_IO_H_
#define PMU_VDD_IO_H_

#include "platform_definitions.h"
#include "pmu_vdd_io_etypes.h"

/** @defgroup NONOS_DRIVERS_PMU Hi21XX non-OS PMU Driver
 * Hi21XX non-OS PMU Driver
 * @ingroup NONOS_DRIVERS
 * @{
 * */

/**
 * Sets the internal VDD_IO power regulator for a VDD_IO bank
 * @note Set an internal regulator to PMU_VDD_IO_LEVEL_OFF to save power or when supplying VDD_IO power externally
 * @param bank The VDD_IO bank
 * @param level The voltage level to configure an internal VDD_IO regulator
 * @return The previous voltage level
 */
PMU_VDD_IO_LEVEL pmu_vdd_io_set_level( PMU_VDD_IO_BANK bank, PMU_VDD_IO_LEVEL level );

/**
 * Get current voltage level of the internal VDD_IO power regulator for a VDD_IO bank
 * @param bank The VDD_IO bank
 * @return The current voltage level
 */
PMU_VDD_IO_LEVEL pmu_vdd_io_get_level( PMU_VDD_IO_BANK bank );

/**
 * Get the VDD_IO bank a particular PIN is assigned to
 * @param pin The PIN
 * @return The assigned VDD_IO_BANK
 */
PMU_VDD_IO_BANK pmu_vdd_io_get_bank( PIN pin );

/** @} end of NONOS_DRIVERS_PMU */

#endif  // PMU_VDD_IO_H_
