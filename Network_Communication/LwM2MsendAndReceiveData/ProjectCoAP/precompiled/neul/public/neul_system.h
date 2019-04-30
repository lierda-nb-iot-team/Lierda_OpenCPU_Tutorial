/******************************************************************************
 * @brief    System Functions for Hi21XX
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef LIB_NEUL_SYSTEM_H_
#define LIB_NEUL_SYSTEM_H_

#include "neul_error_types.h"
#include "reboot.h"
#include "neul_system_types.h"

/** @defgroup LIBNEUL Hi21XX libNEUL Interface
 * Hi21XX libNeul System API
 * @ingroup LIBNEUL
 * @{
 * */

/** @} end of group libNEUL_SYSTEM */

/** @defgroup libNEUL_SYSTEM Hi21XX libNEUL System
 * Hi21XX libNeul System API
 * @ingroup LIBNEUL
 * @{
 * */

/** Request that the system reboots. The system will reboot when safe.
 */
void request_reboot (REBOOT_CAUSE reason);

/** Return chipinfo structure
 * @param chipinfo pointer to ue_chipinfo_t to be filled in
 * @return success or error
 */
NEUL_RET get_chipinfo(ue_chipinfo_t *chipinfo);

/** Return temperature coefficient
 * @param temp_coedff pointer to take temperature coefficient (mV)
 * @return success or error
 */
NEUL_RET get_chip_temp_coefficient(uint16 *temp_coeff);

/**
 * @brief get a random number by hardware
 * @param pointer to buffer for the random number of at least random_request_len bytes.
 * @param length of random number requested in bytes
 * @return success or failure
 */
NEUL_RET get_random(uint8 *random, uint16 random_request_len);

/**
 *@brief prepare for powerdown
*/
void prepare_for_powerdown(void);

/** @} end of group libNEUL_SYSTEM */

#endif /* LIB_NEUL_SYSTEM_H_ */
