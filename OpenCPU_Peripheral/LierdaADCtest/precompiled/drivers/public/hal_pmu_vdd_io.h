/******************************************************************************
 * @brief    Hi21XX HAL PMU VDD IO DRIVER INTERFACE
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef HAL_PMU_VDD_IO_H_
#define HAL_PMU_VDD_IO_H_

#include "platform_definitions.h"

/** @defgroup DRIVER_HAL_VDD_IO Hi211X HAL PIO VDD IO Driver
 * HAL PIO VDD IO Driver
 * @ingroup DRIVER_HAL
 * @{
 * */

/**
 * Defines the different VDD_IO banks available
 */
typedef enum
{
    HAL_PMU_VDD_IO_BANK_R1 = 0,    //!< VDD_IO_R1 (IO_LIN_CTRL 3:0,   PIO0-PIO9)
    HAL_PMU_VDD_IO_BANK_R2 = 1,    //!< VDD_IO_R2 (IO_LIN_CTRL 7:4,   PIO10-PIO21, SWD, RSTB, TEST_EN)
    HAL_PMU_VDD_IO_BANK_L2 = 2,    //!< VDD_IO_L2 (IO_LIN_CTRL 11:8,  PIO34-PIO39)
    HAL_PMU_VDD_IO_BANK_L1 = 3,    //!< VDD_IO_L1 (IO_LIN_CTRL 15:12, PIO22-PIO33)
    HAL_PMU_VDD_IO_BANK_MAX,       //!< Used to indicate the max VDD_IO bank that can be addressed
    HAL_PMU_VDD_IO_BANK_UNKNOWN = HAL_PMU_VDD_IO_BANK_MAX    //!< Use to indicate that the VDD_IO bank is not recognised
} HAL_PMU_VDD_IO_BANK;

/**
 * Defines the different VDD_IO voltage regulator levels
 */
typedef enum
{
    HAL_PMU_VDD_IO_LEVEL_1V5  = 0,    //!< Set internal VDD_IO regulator to 1.5V
    HAL_PMU_VDD_IO_LEVEL_1V8  = 1,    //!< Set internal VDD_IO regulator to 1.8V
    HAL_PMU_VDD_IO_LEVEL_2V1  = 2,    //!< Set internal VDD_IO regulator to 2.1V
    HAL_PMU_VDD_IO_LEVEL_2V4  = 3,    //!< Set internal VDD_IO regulator to 2.4V
    HAL_PMU_VDD_IO_LEVEL_2V7  = 4,    //!< Set internal VDD_IO regulator to 2.7V
    HAL_PMU_VDD_IO_LEVEL_3V0  = 5,    //!< Set internal VDD_IO regulator to 3.0V
    HAL_PMU_VDD_IO_LEVEL_3V3  = 6,    //!< Set internal VDD_IO regulator to 3.3V
    HAL_PMU_VDD_IO_LEVEL_VBAT = 7,    //!< Bypass internal VDD_IO regulator and drive from VBAT
    HAL_PMU_VDD_IO_LEVEL_OFF,         //!< Used to indicate that an internal VDD_IO regulator is turned off
    HAL_PMU_VDD_IO_LEVEL_MAX,         //!< Used to check for the max level that can be set
    HAL_PMU_VDD_IO_LEVEL_UNKNOWN = HAL_PMU_VDD_IO_LEVEL_MAX,   //!< Used to indicate that the level is unknown
} HAL_PMU_VDD_IO_LEVEL;

/**
 * Enables and configures the internal VDD_IO power regulator for a VDD_IO bank
 * @param bank The VDD_IO bank to enable
 * @param level The voltage level to configure an internal VDD_IO regulator
 */
void hal_pmu_enable_vdd_io( HAL_PMU_VDD_IO_BANK bank, HAL_PMU_VDD_IO_LEVEL level );

/**
 * Disables the internal VDD_IO power regulator for a VDD_IO bank
 * @note Disable an internal regulator to save power or when supplying VDD_IO power externally
 * @param bank The VDD_IO bank to disable
 */
void hal_pmu_disable_vdd_io( HAL_PMU_VDD_IO_BANK bank );

/**
 * Get current voltage level of the internal VDD_IO power regulator for a VDD_IO bank
 * @param bank The VDD_IO bank
 * @return The current VDD_IO voltage level
 */
HAL_PMU_VDD_IO_LEVEL hal_pmu_get_vdd_io( HAL_PMU_VDD_IO_BANK bank );

/**
 * Get the VDDI_IO ban a particular PIO is assigned to
 * @param pin The PIN
 * @return The assigned HAL_PMU_VDD_IO_BANK
 */
HAL_PMU_VDD_IO_BANK hal_pmu_get_vdd_io_bank( PIN pin );

/** @} end of group DRIVER_HAL_VDD_IO */

#endif  // HAL_PMU_H_
