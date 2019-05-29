/******************************************************************************
 * @brief    libneul IO bank interface
 * Copyright (c) 2017 Huawei Technologies Co. Ltd
******************************************************************************/
#include "pmu_vdd_io.h"
#include "neul_error_types.h"

/** @addtogroup libNEUL_SYSTEM
 * @{
 * */

/**
 * Initialise IO banks to stored or default levels
 * Leave bank R2 on and bank L1 off
 * This should be called after os start.
 * @param   None.
 * @return   None.
 */
void io_bank_init(void);

/**
 * Turn on internal voltage regulator, to the pre-configured voltage on level,
 * for either bank R2 or bank L1
 * @param   bank IO bank to power internally
 * @return  success or error.
 */
NEUL_RET io_bank_turn_on(PMU_VDD_IO_BANK bank);

/**
 * Turn off internal voltage regulator for either bank R2 or bank L1.
 * @param   bank IO bank to turn off
 * @return  success or error.
 */
NEUL_RET io_bank_turn_off(PMU_VDD_IO_BANK bank);

/**
 * Set the pre-configured IO bank voltage on level to a different level to the default, either
 * stored in KV store or default.
 * Can only re-configure the voltage on level for bank R2 or bank L1.
 * This call must be used with extreme care, as incorrect use may damage
 * components connected to the bank.
 * Call io_bank_on() to apply the new voltage on level.
 * @param   bank IO bank to set on voltage level of
 * @param   level, voltage level to configure bank on voltage to.
 * @return  success or error.
 */
NEUL_RET io_bank_set_on_level(PMU_VDD_IO_BANK bank, PMU_VDD_IO_LEVEL level);

/**
 * Read IO bank state of bank R2 or bank L1
 * @param   bank IO bank to read voltage level of
 * @param   level, voltage level bank set to
 * @param   on true of bank is on
 * @return  success or error.
 */
NEUL_RET io_bank_get_status(PMU_VDD_IO_BANK bank, PMU_VDD_IO_LEVEL *level, bool *on);
/** @} end of group libNEUL_SYSTEM */
