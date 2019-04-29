/******************************************************************************
 * @brief    LOG SAVE MODULE
 * Copyright (c) 2017 NEUL LIMITED
******************************************************************************/
#ifndef EFLOG_H_
#define EFLOG_H_

#include "neulfw.h"

/** @addtogroup libNEUL_LOGREADER
 * @{
 * */

typedef enum
{
    EFLOG_RET_OK,                /*!< FLOG READ/WRITE SUCCESS        */
    EFLOG_RET_NO_DATA,           /*!< FLOG READ OVER ALL DATA        */
    EFLOG_RET_ERROR,             /*!< FLOG READ/WRITE ERROR          */
    EFLOG_RET_BAD_PARAMS,        /*!< FLOG READ/WRITE PARAM BAD      */
    EFLOG_RET_NO_FILTER_SPACE,   /*!< FLOG NO FILTER WRITE SPACE     */
    EFLOG_RET_BUSY,              /*!< FLOG READ/WRITE BUSY           */
    EFLOG_RET_BLOCK_BAD,         /*!< FLOG READ/WRITE HAVE BLOCK BAD */
}EFLOG_RET;

/**
 * eflog    Init
 * @param  None
 * @return None
 */
void eflog_init(void);

/**
 * EFLOG    Deinit
 * @param  None
 * @return None
 */
void eflog_deinit(void);

/**
 * Store   Log                Into Flash/SD Card
 * @param  buff               Log Data Buffer
 * @param  len                Log Data Length
 * @return EFLOG_RET_OK        Write Data OK
 *         EFLOG_RET_BUSY      EFLOG Write Busy Now
 *         EFLOG_RET_ERROR     Write Error
 */
EFLOG_RET eflog_log_write(uint8* buff, uint16 len, bool is_exception_log);

/**
 * Read    Log Into           Flash/SD Card
 * @param  buff Log           From Data Buffer
 * @param  buff_size          Log Data Length
 * @return EFLOG_RET_OK        Read Data OK
 *         EFLOG_RET_NO_DATA   No New Data
 *         EFLOG_RET_BUSY      EFLOG Read Busy Now
 *         EFLOG_RET_BLOCK_BAD Flash Have Block Bad
 *         EFLOG_RET_ERROR     Read Error
 * This function can not be used to interrupt the context!
 */
EFLOG_RET eflog_read(uint8* buff, uint16 buff_size, uint16* len);

/**
 * Delete all the saved logs
 * @param  None
 * @return None
 */
void eflog_delete(void);

/**
 * When user finish the log dump,
 * reset the EFLOG_read_page to the first page
 * @param  None
 * @return None
 */
void eflog_page_read_finish(void);

/** @} end of group libNEUL_LOGREADER */

#endif
