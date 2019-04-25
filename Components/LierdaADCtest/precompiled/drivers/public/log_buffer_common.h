/******************************************************************************
 * @brief    LOG BUFFER COMMON DEFINITIONS
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef SRC_LIB_LOG_PRIVATE_LOG_BUFFER_COMMON_H_
#define SRC_LIB_LOG_PRIVATE_LOG_BUFFER_COMMON_H_

/** @addtogroup NONOS_DRIVERS_LOG
 * @{
 * */

typedef uint8 log_kv_t;
typedef uint8 log_module_id_t;
typedef uint16 log_message_id_t;

/**
 * @brief Log message information header.
 */
typedef struct
{
    log_kv_t            kv;              /**< contains 2-bit core field and 1-bit class in the most significant bits, and message verbosity in least significant 3 bits. Middle 2 bits are reserved set to 0. */
    log_module_id_t     module;          /**< module space to enumerate upto 256 modules */
    log_message_id_t    message_id;      /**< unique per core/class */
    uint16              length;          /**< length on bytes of the log message */
} __attribute__((packed)) log_message_header_t; //lint !e959 It will always be copied as uint8 from to the buffer

//lint -esym(755,LOG_KV_VERBOSITY_MASK)
//lint -esym(755,LOG_KV_SET_VERBOSITY)
//lint -esym(755,LOG_KV_CLASS_SHIFT)
//lint -esym(755,LOG_KV_CLASS_MASK)
//lint -esym(755,LOG_KV_SET_CLASS)
//lint -esym(755,LOG_KV_CORE_SHIFT)
//lint -esym(755,LOG_KV_CORE_MASK)
//lint -esym(755,LOG_KV_SET_CORE)
//lint -esym(755,LOG_KV_SET_FLAGS)
//lint -esym(755,LOG_KV_FLAGS_SHIFT)
//lint -esym(755,LOG_KV_FLAGS_MASK)

#define LOG_KV_VERBOSITY_MASK       0x3
#define LOG_KV_SET_VERBOSITY(x)     ((x) & LOG_KV_VERBOSITY_MASK)
#define LOG_KV_CLASS_SHIFT          5
#define LOG_KV_CLASS_MASK           1
#define LOG_KV_SET_CLASS(x)         (((x) & LOG_KV_CLASS_MASK) << LOG_KV_CLASS_SHIFT)
#define LOG_KV_CORE_SHIFT           6
#define LOG_KV_CORE_MASK            0x3
#define LOG_KV_SET_CORE(x)          (((x) & LOG_KV_CORE_MASK) << LOG_KV_CORE_SHIFT)

#define LOG_KV_FLAGS_SHIFT          3
#define LOG_KV_FLAGS_MASK           0x03
#define LOG_KV_SET_FLAGS(x)         (((x) & LOG_KV_FLAGS_MASK) << LOG_KV_FLAGS_SHIFT)

/** LOG KV CLASS */
typedef enum
{
    LOG_KV_CLASS_SYSTEM = 0, //!< LOG KV CLASS SYSTEM
    LOG_KV_CLASS_CUSTOM      //!< LOG KV CLASS CUSTOM
} LOG_KV_CLASS;

/** LOG VERBOSITY */
typedef enum
{  
    LOG_VERBOSITY_VERBOSE = 0,     //!< LOG VERBOSITY VERBOSE
    LOG_VERBOSITY_NORMAL,      //!< LOG VERBOSITY NORMAL
    LOG_VERBOSITY_WARNING,     //!< LOG VERBOSITY WARNING
    LOG_VERBOSITY_ERROR,       //!< LOG VERBOSITY ERROR
} log_verbosity_t;

typedef enum
{
    LOG_FLAGS_NONE       = 0,
    LOG_FLAGS_XLOG       = 0x01,
    LOG_FLAGS_DEBUGLOG   = 0x02,
    LOG_FLAGS_RESTRICTED = 0x04,
} log_flags_t;

/**
 * @brief Log message information header.
 */
typedef struct {
    uint32 time_us;                   /**< time when the logging was generated */
    log_message_header_t msg_header;  /**< log message header */
}  __attribute__((packed)) log_buffer_header; //lint !e959 It will always be copied as uint8 from to the buffer


/** @} end of NONOS_DRIVERS_LOG */

#endif /* SRC_LIB_LOG_PRIVATE_LOG_BUFFER_COMMON_H_ */
