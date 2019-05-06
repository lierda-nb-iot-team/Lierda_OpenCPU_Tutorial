/******************************************************************************
 * @brief    Internal firmware log save module
 * Copyright (c) 2017 Huawei Technologies Co. Ltd
******************************************************************************/
#ifndef FLOG_H_
#define FLOG_H_

/** @addtogroup libNEUL_LOGREADER
 * @{
 * */

#include "neulfw.h"
#if defined(EXTERNAL_FLASH_LOG)
#include "eflash.h"
#endif

typedef enum
{
    FLOG_RET_OK,                /*!< FLOG READ/WRITE SUCCESS        */
    FLOG_RET_NO_DATA,           /*!< FLOG READ OVER ALL DATA        */
    FLOG_RET_ERROR,             /*!< FLOG READ/WRITE ERROR          */
    FLOG_RET_BAD_PARAMS,        /*!< FLOG READ/WRITE PARAM BAD      */
    FLOG_RET_NO_SPACE,          /*!< EFLOG NO FILTER WRITE SPACE / IFLOG WRITE BUFF IS FULL */
    FLOG_RET_UNINT_BUSY,        /*!< EFLOG READ/WRITE BUSY / IFLOG UNINIT */
    FLOG_RET_BLOCK_BAD,         /*!< EFLOG READ/WRITE HAVE BLOCK BAD */
    FLOG_RET_WIRTE_DISABLED,    /*!< IFLOG WRITE IS DISABLE          */
}FLOG_RET;

typedef enum
{
    FLOG_STATE_UNINIT,   /*!< EFLOG UNINIT          */
    FLOG_STATE_IDLE,     /*!< EFLOG READ/WRITE IDLE */
    FLOG_STATE_BUSY      /*!< EFLOG READ/WRITE BUSY */
}FLOG_STATE;

/**
 * flog init
 * @param  None
 * @return None
 */
FLOG_RET flog_init(void);

/**
 * FLOG    Deinit
 * @param  None
 * @return None
 */
void flog_deinit(void);

/**
 * @brief  Enable or disable iflog write, to avoid it affect FOTA, or other feature.
 * @param  write_enable true is enable iflog write, fales is disable iflog write
 * @return None
 */
void flog_set_write_enable(bool write_enable);

/**
 * Store log into flash
 * @param  buff               Log data buffer
 * @param  len                Log data length
 * @return FLOG_RET_OK        Write data OK
 *         FLOG_RET_BUSY      FLOG write busy now
 *         FLOG_RET_ERROR     Write error
 *         FLOG_RET_NO_SPACE  eflog no filter write space Or iflog write buff is full
 */
FLOG_RET flog_log_write(uint8* buff, uint16 len, bool is_exception_log);

/**
 * Read log from flash
 * @param  buff Log            From data buffer
 * @param  buff_size           Log data length
 * @return FLOG_RET_OK         Read data OK
 *         FLOG_RET_NO_DATA    No new data
 *         FLOG_RET_UNINT_BUSY eflog read busy now Or iflog uninit
 *         FLOG_RET_BLOCK_BAD  Flash have block bad
 *         FLOG_RET_ERROR      Read error
 * This function can not be used to interrupt the context!
 */
FLOG_RET flog_read(uint8* buff, uint16 buff_size, uint16* len);

/**
 * Delete all the saved logs
 * @param  None
 * @return None
 */
void flog_delete(void);

/**
 * When user finish the log dump,
 * reset the EFLOG_read_page to the first page
 * @param  None
 * @return None
 */
void flog_page_read_finish(void);

/**
 * @brief  Get write buff usable size
 * @param  None
 * @return Write buff usable size
 */
uint16 flog_get_available_size(void);

/** @} end of group libNEUL_LOGREADER */

#endif
