/******************************************************************************
 * @brief    aio pin driver
 * Copyright (c) 2017 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef DRIVERS_CMSIS_AIO_PIN_H_
#define DRIVERS_CMSIS_AIO_PIN_H_

/** @defgroup DRIVER_CMSIS_AIO_PIN Hi211X CMSIS AIO Pin Driver
 * CMSIS AIO pin Driver: AIO Pin Driver
 * @ingroup DRIVER_CMSIS
 * @{
 * */
typedef enum {
    AIO_PIN_RET_OK,
    AIO_PIN_RET_ERROR,
} AIO_PIN_RET;

typedef enum {
    AIO_PIN_0,
    AIO_PIN_1,
    AIO_PIN_MAX
} AIO_PIN;

/**
 * @brief Initialises the vbat driver
 * @param pin to init
 */
AIO_PIN_RET aio_pin_init(AIO_PIN pin);

/**
 * @brief Deinitialises the vbat driver
 * @param pin to deinit
 */
AIO_PIN_RET aio_pin_deinit(AIO_PIN pin);

/** @} end of group DRIVER_CMSIS_VBAT */

#endif // DRIVER_CMSIS_AIO_PIN
