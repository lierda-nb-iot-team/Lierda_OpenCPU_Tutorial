/******************************************************************************
 * @brief    Internal firmware log save module
 * Copyright (c) 2017 Huawei Technologies Co. Ltd
******************************************************************************/
#ifndef LIB_IFLOG_IFLOG_H_
#define LIB_IFLOG_IFLOG_H_

#include "neulfw.h"

/** @defgroup libNEUL_IFLOG Hi21XX Internal Flash Logging
 * Hi21XX Internal Flash Logging
 * @ingroup HI21XX_MODULES
 * @{
 * */

#define IFLOG_MAGIC      (0xcafe)
#define IFLOG_BUFF_SIZE  (256)
#define FORCE_4_ALIGNMENT(value)    ((value)&(~(0x03ul)))

typedef struct
{
    uint16 magic;
    volatile uint16 w_index;
    volatile uint16 r_index;
    uint16 buff_size;
    uint8  buff[IFLOG_BUFF_SIZE];
}__attribute__ ((aligned (4))) iflog_cache_root;

typedef enum
{
    IFLOG_RET_OK,                 /*!< IFLOG READ/WRITE SUCCESS        */
    IFLOG_RET_NO_DATA,            /*!< IFLOG READ OVER ALL DATA        */
    IFLOG_RET_ERROR,              /*!< IFLOG READ/WRITE ERROR          */
    IFLOG_RET_BAD_PARAMS,         /*!< IFLOG READ/WRITE PARAM BAD      */
    IFLOG_RET_NO_SPACE,           /*!< IFLOG WRITE BUFF IS FULL        */
    IFLOG_RET_UNINIT,             /*!< IFLOG UNINIT                    */
    IFLOG_RET_WRITE_DISABLED = 7, /*!< IFLOG WRITE IS DISABLE          */
}IFLOG_RET;

/**
 * @brief  Iflog init
 * @param  None
 * @return IFLOG_RET_OK     init success
 *         IFLOG_RET_ERROR  init fail
 */
IFLOG_RET iflog_init(void);

/**
 * @brief  Enable or disable iflog write, to avoid it affect FOTA, or other feature.
 * @param  write_enable true is enable iflog write, fales is disable iflog write
 * @return None
 */
void iflog_set_write_enable(bool write_enable);

/**
 * @brief  Store log into iflash
 * @param  buff               Log data buffer
 * @param  len                Log data length
 * @return IFLOG_RET_OK         Write data OK
 *         IFLOG_RET_ERROR      Write error
 *         IFLOG_RET_UNINIT     iflog uninit
 *         IFLOG_RET_BAD_PARAMS Bad params
 *         IFLOG_RET_NO_SPACE   iflog write buff full
 */
IFLOG_RET iflog_write(uint8* buff, uint16 len);

/**
 * @brief  Form iflash read log
 * @param  buff               Log data buffer
 * @param  len                Read log data length
 * @return IFLOG_RET_OK         Read data OK
 *         IFLOG_RET_ERROR      Read error
 *         IFLOG_RET_UNINIT     iflog uninit
 *         IFLOG_RET_BAD_PARAMS Bad params
 *         IFLOG_RET_NO_DATA    iflog read over all buff
 */
IFLOG_RET iflog_read(uint8 * buff, uint16 buff_size, uint16 * len);

/**
 * @brief  Get write buff usable size
 * @param  None
 * @return Write buff usable size
 */
uint16 iflog_get_available_size(void);

/** @} end of group libNEUL_BUILDVERSION */

#endif // LIB_IFLOG_IFLOG_H_
