/******************************************************************************
 * @brief    lwip snmp compatible header file
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/
#ifndef LWIP_SUPPORT_ERR_H
#define LWIP_SUPPORT_ERR_H

#include "lwip/arch.h"
#include "lwip/opt.h"

/** @addtogroup LWIP_SUPPORT
 * @{
 * */

typedef s8_t err_t;

/** Definitions for error constants. */
typedef enum {

    ERR_OK         = 0,     /** Successful.                    */
    ERR_MEM        = -1,    /** Memory error.                  */
    ERR_BUF        = -2,    /** Buffer error.                  */
    ERR_TIMEOUT    = -3,    /** Timeout.                       */
    ERR_RTE        = -4,    /** Routing error.                 */
    ERR_INPROGRESS = -5,    /** Operation in progress          */
    ERR_VAL        = -6,    /** Illegal value.                 */
    ERR_WOULDBLOCK = -7,    /** Operation would block.         */
    ERR_USE        = -8,    /** Address in use.                */
    ERR_ALREADY    = -9,    /** Already connecting.            */
    ERR_ISCONN     = -10,   /** Connection already established.*/
    ERR_CONN       = -11,   /** No connection.                 */
    ERR_IF         = -12,   /** Interface error                */
    ERR_ABRT       = -13,   /** Connection aborted.            */
    ERR_RST        = -14,   /** Connection reset.              */
    ERR_CLSD       = -15,   /** Connection closed.             */
    ERR_ARG        = -16,   /** Illegal argument.              */
} err_enum_t;

/** @} end of group LWIP_SUPPORT */

#endif /* LWIP_SUPPORT_ERR_H */
