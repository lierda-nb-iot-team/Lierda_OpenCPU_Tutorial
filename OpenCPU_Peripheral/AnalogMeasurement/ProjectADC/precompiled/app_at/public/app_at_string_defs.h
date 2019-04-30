/******************************************************************************
 * @brief    BOUDICA  AT string defs PRIVATE DEFINITIONS
 * Copyright (c) 2016-2018 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef  APP_AT_STRING_DEFS_H_
#define  APP_AT_STRING_DEFS_H_

/** @addtogroup libNEUL_APP_AT_INT
 * @{
 * */

#define APP_AT_STR_OK                 "OK"
#define APP_AT_STR_PIN                "+NUSIM: PIN REQUIRED"
#define APP_AT_STR_PUK                "+NUSIM: PUK REQUIRED"
#define APP_AT_STR_PUK_BLOCKED        "+NUSIM: PUK BLOCKED"
#define APP_AT_STR_ERROR              "ERROR"

#define AT_CMD_CR                     '\r'
#define AT_CMD_LF                     '\n'
#define AT_CMD_WHITE_SPACE            ' '
#define AT_CMD_END_MARK               '\0'
#define AT_CMD_EQUAL_MARK             '='
#define AT_CMD_QUESTION_MARK          '?'
#define AT_CMD_DOUBLE_QUOTATION       '\"'
#define AT_CMD_PARAM_SEPARATOR        ','
#define AT_CMD_SEPARATOR              ';'

#define AT_CMD_PREFIX                 "AT"
#define AT_CMD_PREFIX_LEN             2

/** @} end of group libNEUL_APP_AT_INT */

#endif
