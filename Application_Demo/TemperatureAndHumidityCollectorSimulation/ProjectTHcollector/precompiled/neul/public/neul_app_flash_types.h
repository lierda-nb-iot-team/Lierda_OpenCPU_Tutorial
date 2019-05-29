/******************************************************************************
 * @brief    apps flash interface
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef SRC_LIB_FLASH_ALLOCATOR_PUBLIC_APP_FLASH_H_
#define SRC_LIB_FLASH_ALLOCATOR_PUBLIC_APP_FLASH_H_

/** @addtogroup libNEUL_APPFLASH
 * @{
 * */
typedef enum
{
    APP_FLASH_RET_OK,
    APP_FLASH_RET_ERROR,
    APP_FLASH_RET_NOT_ENOUGH_SPACE,
    APP_FLASH_RET_FLASH_ERROR,
    APP_FLASH_RET_ERASE_IN_PROGRESS
} APP_FLASH_RET;

/** @} end of group libNEUL_APPFLASH */

#endif /* SRC_LIB_FLASH_ALLOCATOR_PUBLIC_APP_FLASH_H_ */
