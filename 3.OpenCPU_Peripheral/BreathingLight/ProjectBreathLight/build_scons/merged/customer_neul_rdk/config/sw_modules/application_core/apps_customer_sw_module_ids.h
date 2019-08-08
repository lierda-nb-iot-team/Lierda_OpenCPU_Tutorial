/******************************************************************************
 * @brief    AUTOGENERATED SOFTWARE MODULES: APPS_CUSTOMER_SW_MODULE_IDS
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef APPS_CUSTOMER_SW_MODULE_IDS_H_
#define APPS_CUSTOMER_SW_MODULE_IDS_H_

/** @addtogroup SOFTWARE_MODULES
 * @{
 * */

/**
 *  Keyspace is divded:
 *  - 8-bit module id (256 modules)
 *    - module ids 0-127: Neul/Huawei
 *    - module ids 128-255: customer configurable
 *  - 8-bit per-module key (maximum of 256 keys) per module key values are managed within the module
 */
typedef enum {
    APPS_SW_MODULE_LCGMR = 134,/**< module_id = 0x0086 = 134
                                    module_name = LCGMR
                                    module_description = Module LCGMR description    */
} APPS_CUSTOMER_SW_MODULE_IDS;


/** @} end of group SOFTWARE_MODULES */

#endif /* APPS_CUSTOMER_SW_MODULE_IDS_H_ */

