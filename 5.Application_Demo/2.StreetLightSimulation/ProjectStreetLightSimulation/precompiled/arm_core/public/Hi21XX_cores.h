/******************************************************************************
 * @brief    NEUL Hi21XX common definitions
 * Copyright (c) 2015 NEUL LIMITED
******************************************************************************/

#ifndef LIB_COMMON_HEADERS_HI21XX_CORES_H_
#define LIB_COMMON_HEADERS_HI21XX_CORES_H_

/** @addtogroup HI21XX_ARMCORE
 * @{
 * */
#define CORE APPS
#if !defined(CORE)
#error   You must define one core before including Hi21XX_cores.h
#endif
#include "Hi21XX.h"
#include "reg_map.h"
#include "Hi21XX_common_peripherals.h"
#include "core_cm0.h"
#include "core_cmFunc.h"
#include "core_cmInstr.h"
#include "core_cmSimd.h"

 /** @} end of group HI21XX_ARMCORE */

#endif /* LIB_COMMON_HEADERS_HI21XX_CORES_H_ */
