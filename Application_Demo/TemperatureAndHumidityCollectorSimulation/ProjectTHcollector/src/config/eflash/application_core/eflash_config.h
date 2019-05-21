/******************************************************************************
 * @brief    Default memory configurations
 * Copyright (c) 2015 NEUL LIMITED
******************************************************************************/
#ifndef EFLASH_CONFIG_H_
#define EFLASH_CONFIG_H_

/*****************************************************
 *  user can not adjust address and length of system *
 * |---------------------------------------------    *
 * |       system zone      |     user zone     |    * 
 * |---------------------------------------------    *
 * |  OTA_PACKAGE  |  FLOG  |    user define    |    *
 * |---------------------------------------------    *
 * |  0x00100000   | 0x2000 |    0x000FE000     |    *
 * |---------------------------------------------    *
 *****************************************************/

#define OTA_PACKAGE_BASE_ADDR         (0x00000000)
#define OTA_PACKAGE_MAX_SIZE          (0x00100000)
#define FLOG_BASE_ADDR                (0x00100000)
#define FLOG_MAX_SIZE                 (0x00002000)

#endif
