/******************************************************************************
 * @brief    AUTOGENERATED KEY IDS: APPS_BASE_KEYS
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef APPS_BASE_KEYS_H_
#define APPS_BASE_KEYS_H_

/** @addtogroup KV_IDS
 * @{
 * */

typedef enum {
    BASE_KEYID_DEPRECATED_DO_NOT_USE = 0,                    /**< key_id = 0x0000 = 0
                                                                  description = Key BASE_KEYID_DEPRECATED_DO_NOT_USE description
                                                                  status = deprecated
                                                                  structure = UNDETERMINED_SIZE_BUFFER    */
    BASE_KEYID_SPI_CLK_PIN = 1,                              /**< key_id = 0x0001 = 1
                                                                  description = Key BASE_KEYID_SPI_CLK_PIN description
                                                                  status = alive
                                                                  structure = PIN    */
    BASE_KEYID_SPI_MISO_PIN = 2,                             /**< key_id = 0x0002 = 2
                                                                  description = Key BASE_KEYID_SPI_MISO_PIN description
                                                                  status = alive
                                                                  structure = PIN    */
    BASE_KEYID_SPI_MOSI_PIN = 3,                             /**< key_id = 0x0003 = 3
                                                                  description = Key BASE_KEYID_SPI_MOSI_PIN description
                                                                  status = alive
                                                                  structure = PIN    */
    BASE_KEYID_SPI_MEM_CS_PIN = 4,                           /**< key_id = 0x0004 = 4
                                                                  description = Key BASE_KEYID_SPI_MEM_CS_PIN description
                                                                  status = alive
                                                                  structure = PIN    */
    BASE_KEYID_FIXED_PINS = 5,                               /**< key_id = 0x0005 = 5
                                                                  description = Key BASE_KEYID_FIXED_PINS description
                                                                  status = alive
                                                                  structure = pin_map_buffer_t    */
    BASE_KEYID_MANUFACTURER_IDENTIFIER = 6,                  /**< key_id = 0x0006 = 6
                                                                  description = Key BASE_KEYID_MANUFACTURER_IDENTIFIER description
                                                                  status = alive
                                                                  structure = UNDETERMINED_SIZE_STRING    */
    BASE_KEYID_MANUFACTURER_MODEL_IDENTIFIER = 7,            /**< key_id = 0x0007 = 7
                                                                  description = Key BASE_KEYID_MANUFACTURER_MODEL_IDENTIFIER description
                                                                  status = alive
                                                                  structure = UNDETERMINED_SIZE_STRING    */
    BASE_KEYID_ACTIVITY_INDICATION_PIN = 8,                  /**< key_id = 0x0008 = 8
                                                                  description = Key BASE_KEYID_ACTIVITY_INDICATION_PIN description
                                                                  status = alive
                                                                  structure = PIN    */
    BASE_KEYID_ACTIVITY_INDICATION_DELAY_MILLISECONDS = 9,   /**< key_id = 0x0009 = 9
                                                                  description = Key BASE_KEYID_ACTIVITY_INDICATION_DELAY_MILLISECONDS description
                                                                  status = alive
                                                                  structure = activity_indication_delay_milliseconds_t    */
    BASE_KEYID_VDD_IO_BANK_R2 = 10,                          /**< key_id = 0x000A = 10
                                                                  description = Key BASE_KEYID_VDD_IO_BANK_R2 description
                                                                  status = alive
                                                                  structure = PMU_VDD_IO_LEVEL    */
    BASE_KEYID_VDD_IO_BANK_L1 = 11,                          /**< key_id = 0x000B = 11
                                                                  description = Key BASE_KEYID_VDD_IO_BANK_L1 description
                                                                  status = alive
                                                                  structure = PMU_VDD_IO_LEVEL    */
    BASE_KEYID_I2C_SCL_PIN = 12,                             /**< key_id = 0x000C = 12
                                                                  description = Key BASE_KEYID_I2C_SCL_PIN description
                                                                  status = alive
                                                                  structure = PIN    */
    BASE_KEYID_I2C_SDA_PIN = 13,                             /**< key_id = 0x000D = 13
                                                                  description = Key BASE_KEYID_I2C_SDA_PIN description
                                                                  status = alive
                                                                  structure = PIN    */
    BASE_KEYID_PRIMARY_UART_CTS_PIN = 14,                    /**< key_id = 0x000E = 14
                                                                  description = Key BASE_KEYID_PRIMARY_UART_CTS_PIN description
                                                                  status = deprecated
                                                                  structure = PIN    */
    BASE_KEYID_PRIMARY_UART_RTS_PIN = 15,                    /**< key_id = 0x000F = 15
                                                                  description = Key BASE_KEYID_PRIMARY_UART_RTS_PIN description
                                                                  status = deprecated
                                                                  structure = PIN    */
    BASE_KEYID_UART_0_CONFIG = 16,                           /**< key_id = 0x0010 = 16
                                                                  description = Define the pins used for UART 0
                                                                  status = alive
                                                                  structure = uart_pin_configuration    */
    BASE_KEYID_UART_1_CONFIG = 17,                           /**< key_id = 0x0011 = 17
                                                                  description = Define the pins used for UART 1
                                                                  status = alive
                                                                  structure = uart_pin_configuration    */
} BASE_KV_IDS;


/** @} end of group KV_IDS */

#endif /* APPS_BASE_KEYS_H_ */

