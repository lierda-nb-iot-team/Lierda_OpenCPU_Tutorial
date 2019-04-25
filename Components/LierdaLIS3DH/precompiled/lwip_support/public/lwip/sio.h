/******************************************************************************
 * @brief    lwip sio compatible header file
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef LWIP_SUPPORT_SIO_H
#define LWIP_SUPPORT_SIO_H

#include "lwip/arch.h"
#include "lwip/opt.h"

/** @addtogroup LWIP_SUPPORT
 * @{
 * */

typedef void * sio_fd_t;

/** Opens a serial device for communication
 * @param  device number
 * @return serial device descriptor or NULL
 */
sio_fd_t sio_open(u8_t devnum);

/** Read from a serial device
 * @param  serial device descriptor
 * @param  pointer to recv buffer
 * @param  maximum length (in bytes) of recv buffer
 * @return number of bytes receive
 */
u32_t sio_read(sio_fd_t fd, u8_t *data, u32_t len);

/** Send a single character to a serial device
 * @param character to send
 * @param serial device descriptor
 */
void sio_send(u8_t c, sio_fd_t fd);

/** Write to a serial device
 * @param serial device descriptor
 * @param pointer to data to send
 * @param length of data to send
 * @return number of bytes sent
 */
u32_t sio_write(sio_fd_t fd, u8_t *data, u32_t len);

/** @} end of group LWIP_SUPPORT */

#endif /* LWIP_SUPPORT_SIO_H */
