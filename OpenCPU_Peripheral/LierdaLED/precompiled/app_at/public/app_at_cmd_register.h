/******************************************************************************
 * @brief    NEULLIB REGISTER NEW AT COMMAND INTERFACE
 * Copyright (c) 2017 Huawei Technologies Co. Ltd
******************************************************************************/
#ifndef APP_AT_CMD_REGISTER_H
#define APP_AT_CMD_REGISTER_H
#include "app_at.h"

/** @addtogroup libNEUL_APP_AT_MOD_API
 * @{
 * */
struct AT_CMD_CB_node
{
    AT_CMD_CB_s at_cmd_cb;
    struct AT_CMD_CB_node* next;
};

/**
 * @Get registered at cmd table address.
 * @return The address of registerable at cmd table
 */
struct AT_CMD_CB_node * at_get_registered_cmd_table_address(void);

/**
 * @register new at cmd .
 * @param at_cmd_cb the pointer of the at cmd param,at_cmd_cb.cmd_str should always using '+'as first char.should
            not include '=','?',';',or will not parse correctly.
 * @return The result of register, successful: true, fail:false
 */
bool at_cmd_register(const AT_CMD_CB_s* at_cmd_cb);

/** @} end of group libNEUL_APP_AT_MOD_API */

#endif
