/******************************************************************************
 * @brief    DMA Module PANIC Causes
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef DMA_PANIC_H_
#define DMA_PANIC_H_

/** @addtogroup DRIVER_CMSIS_DMA
 * @{
 * */

typedef enum
{
    PANIC_DMA_UNABLE_TO_CREATE_MUTEX,
    PANIC_DMA_UNABLE_TO_TAKE_MUTEX,
    PANIC_DMA_UNABLE_TO_GIVE_MUTEX,
    PANIC_DMA_MEMORY_ALLOCATION_FAILED,
    PANIC_DMA_UNSUPPORTED_TRANSFER_TYPE,
    PANIC_DMA_PERIPHERAL_WAITING_FOR_FINISH
} PANIC_ID_DMA;

/** @} end of group DRIVER_CMSIS_DMA */

#endif /* DMA_PANIC_H_ */
