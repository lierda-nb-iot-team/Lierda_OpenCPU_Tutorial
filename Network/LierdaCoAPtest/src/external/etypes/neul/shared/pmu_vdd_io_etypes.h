/******************************************************************************
 * @brief    PMU VDD IO ETYPES
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/
#ifndef ETYPES_SHARED_PMU_VDD_IO_ETYPES_H_
#define ETYPES_SHARED_PMU_VDD_IO_ETYPES_H_

#include "neulfw.h"

/** @addtogroup NONOS_DRIVERS_PMU
 * @{
 * */

/**
 * Defines the different VDD_IO banks available
 */
typedef enum ETYPES_ENUM_HOLDER_TYPE(U8)
{
    PMU_VDD_IO_BANK_R1 = 0,    //!< VDD_IO_R1
    PMU_VDD_IO_BANK_R2 = 1,    //!< VDD_IO_R2
    PMU_VDD_IO_BANK_L2 = 2,    //!< VDD_IO_L2
    PMU_VDD_IO_BANK_L1 = 3,    //!< VDD_IO_L1
    PMU_VDD_IO_BANK_UNKNOWN = 4   //!< Use to indicate that the VDD_IO bank is not recognised
}
PMU_VDD_IO_BANK;

#define PMU_VDD_IO_BANK_MAX     PMU_VDD_IO_BANK_UNKNOWN // Used to indicate the max VDD_IO bank that can be addressed


/**
 * Defines the different VDD_IO voltage regulator levels
 */
typedef enum ETYPES_ENUM_HOLDER_TYPE(U8)
{
    PMU_VDD_IO_LEVEL_1V5  = 0,    //!< Set internal VDD_IO regulator to 1.5V
    PMU_VDD_IO_LEVEL_1V8  = 1,    //!< Set internal VDD_IO regulator to 1.8V
    PMU_VDD_IO_LEVEL_2V1  = 2,    //!< Set internal VDD_IO regulator to 2.1V
    PMU_VDD_IO_LEVEL_2V4  = 3,    //!< Set internal VDD_IO regulator to 2.4V
    PMU_VDD_IO_LEVEL_2V7  = 4,    //!< Set internal VDD_IO regulator to 2.7V
    PMU_VDD_IO_LEVEL_3V0  = 5,    //!< Set internal VDD_IO regulator to 3.0V
    PMU_VDD_IO_LEVEL_3V3  = 6,    //!< Set internal VDD_IO regulator to 3.3V
    PMU_VDD_IO_LEVEL_VBAT = 7,    //!< Bypass internal VDD_IO regulator and drive from VBAT
    PMU_VDD_IO_LEVEL_OFF  = 8,         //!< Used to indicate that an internal VDD_IO regulator is turned off
    PMU_VDD_IO_LEVEL_UNKNOWN = 9,   //!< Used to indicate that the level is unknown
}
PMU_VDD_IO_LEVEL;

#define PMU_VDD_IO_LEVEL_MAX  PMU_VDD_IO_LEVEL_UNKNOWN  // Used to check for the max level that can be set


/** @} end of group NONOS_DRIVERS_PMU */


#endif /* ETYPES_SHARED_PMU_VDD_IO_ETYPES_H_ */
