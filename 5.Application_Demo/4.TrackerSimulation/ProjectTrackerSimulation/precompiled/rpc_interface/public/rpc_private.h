/******************************************************************************
 * @brief    RPC Interface Header
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef SRC_LIB_RPC_INTERFACE_PRIVATE_RPC_PRIVATE_H
#define SRC_LIB_RPC_INTERFACE_PRIVATE_RPC_PRIVATE_H

#include "rpc_auto_generated.h"
#include "platform_definitions.h"   //needed for CORES
#include "core.h"
#include "rpc_interface.h"
#include "neulfw.h"

#define MESSAGE_HEADER_SIZE        (sizeof(rpc_command_header) - 1)

#if (CORE == APPS) || (CORE == PROTOCOL)
#define MAX_RPC_MESSAGE_SIZE     (1700 + 32)  /* Magic 32 to allow for the sendto overhead of IP address, etc etc - FIXME !*/
#else
#define MAX_RPC_MESSAGE_SIZE     (170)
#endif

#define MESSAGE_BUFFER_LENGTH    (MAX_RPC_MESSAGE_SIZE + sizeof(rpc_command_header))

typedef void (*rpc_command_func)(CORES src_core, uint8 *params, uint16 param_length);
typedef void (*rpc_response_func)(CORES src_core, uint8 *params, uint16 param_length);

typedef struct
{
    uint16 command_length;
    uint16 rpc_command_id;
    bool is_command;    //if not a command then it is a response
} rpc_command_header;                //lint !e959    struct not aligned to 2 bytes

typedef union
{
    uint8 data[MESSAGE_BUFFER_LENGTH];
    rpc_command_header header;
} rpc_command;

/**
 * When receiving a command from a remote core, this structure stores the interface local data:
 */
typedef struct
{
    uint16 data_received;
    rpc_command cmd;
} rpc_transfer_command;

/**
 * When receiving a response from a remote core, this structure stores the interface local data:
 */
typedef struct
{
    uint16 data_received;            //!< The total amount of data received in this response
    rpc_command_header header;       //!< Command Header
    uint16 section_progress;         //!< How many bytes we have already processed in the current section
    uint8 current_section;           //!< Which section in the section list we are on
} rpc_transfer_response;             //lint !e959    struct not aligned to 2 bytes

/**
 * Contains the meta data for a single variable being got from another core
 */
typedef struct
{
    uint8  *dst_buffer;             //!< A pointer to the destination buffer
    uint16 *amount_being_sent;      //!< A pointer to a uint16 that store the amount of data we were sent (if variable)
    uint16  buffer_max;             //!< The maximum amount of data we can store in the buffer - for non-variable gets, this is the amount that will be written
} rpc_get_data_section;             //lint !e959    struct not aligned to 4 bytes

/**
 * When getting data from a remote core this structure tells the RPC Interface layer where
 * the list of 'get' values are, and how big that list is (reverse scatter-gather)
 */
typedef struct __attribute__((packed))
{
    rpc_get_data_section *sections;
    uint8 num_sections;
} rpc_get_data;                     //lint !e959    struct not aligned to 4 bytes

/**
 * When sending data this structure is used in a list to pass in the location
 * and lengths of the data to send
 */
typedef struct
{
    uint8 *data_location;
    uint16 data_length;
} rpc_scatter_gather;   //lint !e959    struct not aligned

/*
 * Command tables for the different cores
 */
extern const rpc_interface_internal_callback security_incomming_command_table[];
extern const rpc_interface_internal_callback protocol_incomming_command_table[];
extern const rpc_interface_internal_callback application_incomming_command_table[];

/*
 * The mailboxes used on the OS builds to yield
 */
extern rpc_interface_mailboxes rpc_mailboxes;

/**
 * Inits the handles for each of the cores
 */
void rpc_auto_generated_init(void);

/**
 * Gets a pointer to the current position of the data buffer, then moves the
 * pointer on by the given amount
 * @param buffer The data buffer
 * @param buffer_posistion The current position of the data buffer - this will get increased
 * @param amount The amount of buffer that we want
 * @return a uint8 pointer to buffer[buffer_position]
 */
uint8 *rpc_get_buffer(uint8 *buffer, uint16 *buffer_position, uint16 amount);

/**
 * Gets a int64 from the buffer in a bus aligned way
 * @param buffer The data buffer
 * @param buffer_posistion The buffer position this will get moved on 8 bytes
 * @return A int64
 */
int64 rpc_get_int64(uint8 *buffer, uint16 *buffer_position);

/**
 * Gets a int32 from the buffer in a bus aligned way
 * @param buffer The data buffer
 * @param buffer_posistion The buffer position this will get moved on 4 bytes
 * @return A int32
 */
int32 rpc_get_int32(uint8 *buffer, uint16 *buffer_position);

/**
 * Gets a int16 from the buffer in a bus aligned way
 * @param buffer The data buffer
 * @param buffer_posistion The buffer position this will get moved on 2 bytes
 * @return A int16
 */
int16 rpc_get_int16(const uint8 *buffer, uint16 *buffer_position);

/**
 * Gets a int8 from the buffer in a bus aligned way
 * @param buffer The data buffer
 * @param buffer_posistion The buffer position this will get moved on 1 byte
 * @return A int8
 */
int8 rpc_get_int8(const uint8 *buffer, uint16 *buffer_position);

/**
 * Sets a pointer to the receive info section
 * @param src The core we will receive from
 * @param info The info section
 */
void set_receive_info(CORES src, rpc_get_data *info);

/**
 * Inits a rpc_get_data_section
 * @param section Pointer to section
 * @param dst Pointer to the data store
 * @param max The max amount of data to store there
 * @param amount_written Pointer to a uint16 who will store the amount written there for variable sized fields
 */
void rpc_init_receive_section(rpc_get_data_section *section, uint8 *dst, uint16 max_size, uint16 *amount_written);

/**
 * Sends a rpc command to the specific core loops if the IPC is busy
 * @param dst_core The core to send to, cannot be ones self
 * @param command_id The rpc message ID
 */
void rpc_interface_scatter_send(CORES dst_core, uint16 command_id, bool is_command,
                                uint16 data_count, const rpc_scatter_gather *scattered_data);

#endif
