/******************************************************************************
 * @brief    NEUL Basic Hi21XX definitions.
 * Include this file before including boudica_common.h
 * Copyright (c) 2015 NEUL LIMITED
******************************************************************************/


#ifndef LIB_COMMON_HEADERS_BOUDICA_DEFINITIONS_H_
#define LIB_COMMON_HEADERS_BOUDICA_DEFINITIONS_H_

/** @defgroup CMSIS CMSIS
 * CMSIS
 * @ingroup CMSIS
 * */

/** @defgroup CMSIS_CORE CMSIS Core
 * CMSIS_MISRA_Exceptions  MISRA-C:2004 Compliance Exceptions
  CMSIS violates the following MISRA-C:2004 rules:

   \li Required Rule 8.5, object/function definition in header file.<br>
     Function definitions in header files are used to allow 'inlining'.

   \li Required Rule 18.4, declaration of union type or object of union type: '{...}'.<br>
     Unions are used for effective representation of core registers.

   \li Advisory Rule 19.7, Function-like macro defined.<br>
     Function-like macros are used to allow more efficient code.
 * @ingroup CMSIS
 * */

/** @defgroup Cortex_M0
 * Cortex_M0
 * @ingroup CMSIS_CORE
 * */

/** @defgroup CMSIS_core_register CMSIS_core_register
 * CMSIS_core_register
 * @ingroup CMSIS_CORE
 * */

/** @defgroup CMSIS_CORE CMSIS_CORE
 * CMSIS_CORE
 * @ingroup CMSIS_CORE
 * */

/** @defgroup CMSIS_NVIC CMSIS_NVIC
 * CMSIS_NVIC
 * @ingroup CMSIS_CORE
 * */

/** @defgroup CMSIS_SCB CMSIS_SCB
 * CMSIS_SCB
 * @ingroup CMSIS_CORE
 * */

/** @defgroup CMSIS_SysTick CMSIS_SysTick
 * CMSIS_SysTick
 * @ingroup CMSIS_CORE
 * */

/** @defgroup CMSIS_core_base CMSIS_core_base
 * CMSIS_core_base
 * @ingroup CMSIS_CORE
 * */

/** @defgroup CMSIS_Core_FunctionInterface CMSIS_Core_FunctionInterface
 * CMSIS_Core_FunctionInterface
 * @ingroup CMSIS_CORE
 * */

/** @defgroup CMSIS_Core_NVICFunctions
 * CMSIS_Core_NVICFunctions
 * @ingroup CMSIS_CORE
 * */

/** @defgroup CMSIS_Core_SysTickFunctions CMSIS_Core_SysTickFunctions
 * CMSIS_Core_SysTickFunctions
 * @ingroup CMSIS_CORE
 * */

/** @defgroup CMSIS_Core_RegAccFunctions CMSIS_Core_RegAccFunctions
 * CMSIS_Core_RegAccFunctions
 * @ingroup CMSIS_CORE
 * */

/** @defgroup CMSIS_Core_InstructionInterface CMSIS_Core_InstructionInterface
 * CMSIS_Core_InstructionInterface
 * @ingroup CMSIS_CORE
 * */

/** @defgroup CMSIS_SIMD_intrinsics CMSIS_SIMD_intrinsics
 * CMSIS_SIMD_intrinsics
* @ingroup CMSIS_CORE
*/

// defined but not used - TODO Suppress
/** @defgroup CMSIS_glob_defs CMSIS_glob_defs
 * CMSIS_glob_defs
 * @ingroup CMSIS_CORE
 * */

/** @defgroup CMSIS_CoreDebug CMSIS_CoreDebug
 * CMSIS_CoreDebug
 * @ingroup CMSIS_CORE
 * */

/** @defgroup Hi21XX_Base Hi21XX Base Definitions
 * Hi21XX Base Definitions
 * @ingroup Hi21XX_Base
 * */

/** @defgroup HI21XX_ARMCORE Hi21XX ARM Core Specifics
 * Hi21XX ARM Core Application Core Specifics
 * @ingroup Hi21XX_Base
 * @{
 * */

#define SECURITY 0
#define PROTOCOL 1
#define APPS     2

/** @} end of group HI21XX_ARMCORE */

#endif /* LIB_COMMON_HEADERS_BOUDICA_DEFINITIONS_H_ */
