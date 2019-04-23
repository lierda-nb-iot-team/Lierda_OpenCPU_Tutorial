/******************************************************************************
 * @brief    Hi2115 AIO Manager Driver Header.
 * Copyright (c) 2017 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef AIO_MANAGER_H_
#define AIO_MANAGER_H_

#include "neulfw.h"
#include "platform_definitions.h"
#include "hal_aio_manager.h"



///*!< AIO MANAGER_RET */
typedef enum
{
    AIO_MANAGER_RET_OK,
    AIO_MANAGER_RET_CLAIM_ERROR,
    AIO_MANAGER_RET_FREE_ERROR,
    AIO_MANAGER_RET_CONNECT_RESOURCES_NOT_OWNED_ERROR,
    AIO_MANAGER_RET_CONNECT_INVALID_CROSSCONNECT_ERROR,
    AIO_MANAGER_RET_DISCONNECT_RESOURCES_NOT_OWNED_ERROR,
    AIO_MANAGER_RET_DISCONNECT_INVALID_MUXBUS_ERROR,
    AIO_MANAGER_RET_ALTIO_ERROR,
    AIO_MANAGER_RET_BAD_AIO_RESOURCE_ID_ERROR,
    AIO_MANAGER_RET_BAD_CONNECT_RESOURCE_ID_ERROR,
    AIO_MANAGER_RET_BAD_CONNECT_MUXBUS_ID_ERROR,
    AIO_MANAGER_RET_ALTIO_ID_ERROR,
    AIO_MANAGER_RET_ALTIO_INVALID_PIO_ERROR,
    AIO_MANAGER_RET_ALTIO_RESOURCES_NOT_OWNED_ERROR,
    AIO_MANAGER_RET_ALTIO_INVALID_ANALOG_FUNCTION_ERROR,
    AIO_MANAGER_RET_MUTEX_ERROR
} AIO_MANAGER_RET;

/* ownership titles */
typedef enum {
   AIO_RESOURCE_FREE,
   AIO_RESOURCE_OWNER_APPS_CORE,
   AIO_RESOURCE_OWNER_PROTOCOL_CORE,
   AIO_RESOURCE_OWNER_UNKNOWN_ERROR,
}  AIO_RESOURCES_STATUS;



// APP resource blocks
typedef enum {
    AIO_RESOURCE_AIO_PIN_0,             // 0   // the analogue i/o blocks
    AIO_RESOURCE_AIO_PIN_1,             // 1
    AIO_RESOURCE_DAC,                   // 2
    AIO_RESOURCE_IDAC,                  // 3
    AIO_RESOURCE_BUF_REF,               // 4
    AIO_RESOURCE_VBAT_DIV,              // 5
    AIO_RESOURCE_TEMP_MON,              // 6
    AIO_RESOURCE_ADC,                   // 7
    AIO_RESOURCE_COMP0,                 // 8
    AIO_RESOURCE_COMP1,                 // 9
    AIO_RESOURCE_CAP_SW,                // 10
    AIO_RESOURCE_VDD_CORE,              // 11  // for ADC trim function

    AIO_RESOURCE_BASE_INDEX_MUXBUSSES,  // 12
    AIO_RESOURCE_MUXBUS_0 = AIO_RESOURCE_BASE_INDEX_MUXBUSSES,
    AIO_RESOURCE_MUXBUS_1,              // 13
    AIO_RESOURCE_MUXBUS_2,              // 14

    AIO_RESOURCE_BASE_INDEX_ALTIO,      // 15
    AIO_RESOURCE_DAC_OUT_ALT = AIO_RESOURCE_BASE_INDEX_ALTIO,
    AIO_RESOURCE_IDAC_OUT_ALT,          // 16
    AIO_RESOURCE_REF_OUT_ALT,           // 17
    AIO_RESOURCE_ADC_IN_ALT,            // 18
    AIO_RESOURCE_COMP0_IN_ALT,          // 19
    AIO_RESOURCE_COMP1_IN_ALT,          // 20
    AIO_RESOURCE_CAP_SW_ALT,            // 21
    AIO_RESOURCE_COMP_EXT_REF_ALT,      // 22

    AIO_RESOURCE_MAX_NUMBER
} AIO_RESOURCE;

// muxbus indexes
typedef enum {
    AIO_MUXBUS_0,                  // first are the shared, double-ended mux busses
    AIO_MUXBUS_1,
    AIO_MUXBUS_2,

    AIO_MUXBUS_BASE_INDEX_ALT,
    AIO_MUXBUS_AIO_DAC_OUT_ALT = AIO_MUXBUS_BASE_INDEX_ALT,
    AIO_MUXBUS_AIO_IDAC_OUT_ALT,  // the following are single ended, AIO block specific busses
    AIO_MUXBUS_AIO_REF_OUT_ALT,   //  one end can be selected to a specific 'APP' block
    AIO_MUXBUS_AIO_ADC_IN_ALT,    //  the other end is fixed to a specific ALT-IO block
    AIO_MUXBUS_AIO_COMP0_IN_ALT,
    AIO_MUXBUS_AIO_COMP1_IN_ALT,
    AIO_MUXBUS_AIO_CAP_SW_ALT,
    AIO_MUXBUS_COMP_EXT_REF_ALT,

    AIO_MUXBUS_MAX_NUMBER
} AIO_MUXBUS;


// defining these synonyms, allows the mux switch table to be defined as NL-002282
typedef enum {
    /* AIO_RESOURCE_DAC_OUT_ALT */      APP_BIDIR_ALT_0 = AIO_RESOURCE_DAC_OUT_ALT - AIO_RESOURCE_BASE_INDEX_ALTIO,         //lint !e656 !e778  Compatible enums, and equal to 0.
    /* AIO_RESOURCE_IDAC_OUT_ALT */     APP_BIDIR_ALT_2 = AIO_RESOURCE_IDAC_OUT_ALT - AIO_RESOURCE_BASE_INDEX_ALTIO,        //lint !e656 Compatible enums
    /* AIO_RESOURCE_REF_OUT_ALT */      APP_BIDIR_ALT_3 = AIO_RESOURCE_REF_OUT_ALT - AIO_RESOURCE_BASE_INDEX_ALTIO,         //lint !e656 Compatible enums
    /* AIO_RESOURCE_ADC_OUT_ALT */      APP_ADC_ALT = AIO_RESOURCE_ADC_IN_ALT - AIO_RESOURCE_BASE_INDEX_ALTIO,              //lint !e656 Compatible enums
    /* AIO_RESOURCE_COMP0_IN_ALT */     APP_COMP_ALT0 = AIO_RESOURCE_COMP0_IN_ALT - AIO_RESOURCE_BASE_INDEX_ALTIO,          //lint !e656 Compatible enums
    /* AIO_RESOURCE_COMP1_IN_ALT */     APP_COMP_ALT1 = AIO_RESOURCE_COMP1_IN_ALT - AIO_RESOURCE_BASE_INDEX_ALTIO,          //lint !e656 Compatible enums
    /* AIO_RESOURCE_CAP_SW_ALT */       APP_BIDIR_ALT_1 = AIO_RESOURCE_CAP_SW_ALT - AIO_RESOURCE_BASE_INDEX_ALTIO,          //lint !e656 Compatible enums
    /* AIO_RESOURCE_COMP_EXT_REF_ALT */ APP_BIDIR_ALT_4 = AIO_RESOURCE_COMP_EXT_REF_ALT - AIO_RESOURCE_BASE_INDEX_ALTIO     //lint !e656 Compatible enums
} ANALOG_FUNCTION; //lint !e656 !e778  Compatible enums, and equal to 0.

typedef struct {
    uint8 switch_0;
    uint8 switch_1;
} SWITCH_CHOICE;



typedef struct {
    uint32 BITS_31_0;
    uint32 BITS_63_32;
    uint8 dir;
} ALTIO_PIO_INFO;

typedef struct {
    HAL_MUXBUS_CONFIG aio_pin_0;
    HAL_MUXBUS_CONFIG aio_pin_1;
    HAL_MUXBUS_CONFIG idac;
    HAL_MUXBUS_CONFIG buf_ref;
    HAL_MUXBUS_CONFIG vbat_div;
    HAL_MUXBUS_CONFIG vdd_core;
} DEFERRED_MUX_SELECT_CONFIG;


/**
 * @brief Init the AIO Manager
 * @param None
 * @return success AIO_MANAGER_RET_OK
 */
AIO_MANAGER_RET aio_manager_init(void);
/**
 * @brief claim ownership of resource blocks for the calling core
 * @param list of resource IDs
 * @param number of resource IDs in the list parameter
 * @return success or fail  AIO_MANAGER_RET
 */
AIO_MANAGER_RET aio_manager_claim_resource(AIO_RESOURCE* resource_block_list, uint8 number_of_blocks );
/**
 * @brief release ownership of resource blocks for the calling core
 * @param list of resource IDs
 * @param number of resource IDs in the list parameter
 * @return success or fail  AIO_MANAGER_RET
 */
AIO_MANAGER_RET aio_manager_free_resource(AIO_RESOURCE* resource_block_list, uint8 number_of_blocks);
/**
 * @brief connect a resource block to a muxbus
 * @param resource ID
 * @param muxbus ID
 * @return success or fail  AIO_MANAGER_RET
 */
AIO_MANAGER_RET aio_manager_connect_analog_resource_to_muxbus(AIO_RESOURCE resource_block, AIO_MUXBUS connect_muxbus);

/**
 * @brief disconnect a resource block to a muxbus
 * @param resource ID
 * @param muxbus ID
 * @return success or fail  AIO_MANAGER_RET
 */
AIO_MANAGER_RET aio_manager_disconnect_analog_resource_from_muxbus(AIO_RESOURCE resource_block, AIO_MUXBUS connect_muxbus );


/**
 * @brief select pio for altio block input/ouput
 * @param resource ID
 * @param PIO number
 * @return success or fail  AIO_MANAGER_RET
 */
AIO_MANAGER_RET aio_manager_altio_connect_pio(AIO_RESOURCE altio_resource_block, PIN pio_number );
/**
 * @brief disconnect pio from altio resource block
 * @param resource ID
 * @param PIO number
 * @return success
 */
AIO_MANAGER_RET aio_manager_altio_disconnect_pio(AIO_RESOURCE altio_resource_block, uint16 pio_number );

/**
 * @brief claim ownership of the resource block for the calling core (handler function)
 * @param list of resource IDs
 * @param number of resource IDs in the list parameter
 * @return success or fail  AIO_MANAGER_RET
 */

AIO_MANAGER_RET aio_manager_claim_resource_internal(CORES core, AIO_RESOURCE* resource_block_list, uint8 number_of_blocks );
/**
 * @brief claim ownership of the resource block for the calling core (handler function)
 * @param list of resource IDs
 * @param number of resource IDs in the list parameter
 * @return success or fail  AIO_MANAGER_RET
 */
AIO_MANAGER_RET aio_manager_free_resource_internal(CORES core, AIO_RESOURCE* resource_block_list, uint8 number_of_blocks);

/**
 * @brief Init the AIO Manager image stati
 * @param None
 * @return success AIO_MANAGER_RET_OK
 */
AIO_MANAGER_RET aio_manager_image_init(void);


// AIO-Manager owns the en/dis-able() function for each APP block
/**
 * @brief enable the DAC block
 * @param None
 * @return None
 */
void aio_manager_dac_enable(void);
/**
 * @brief disable the DAC block
 * @param None
 * @return None
 */
void aio_manager_dac_disable(void);
/**
 * @brief enable the ADC block
 * @param None
 * @return None
 */
void aio_manager_adc_enable(void);
/**
 * @brief disable the ADC block
 * @param None
 * @return None
 */
void aio_manager_adc_disable(void);
/**
 * @brief enable the AIO0 block
 * @param None
 * @return None
 */
void aio_manager_aio_pin0_enable(void);
/**
 * @brief disable the AIO0 block
 * @param None
 * @return None
 */
void aio_manager_aio_pin0_disable(void);
/**
 * @brief enable the AIO1 block
 * @param None
 * @return None
 */
void aio_manager_aio_pin1_enable(void);
/**
 * @brief disable the AIO1 block
 * @param None
 * @return None
 */
void aio_manager_aio_pin1_disable(void);
/**
 * @brief enable the IDAC block
 * @param None
 * @return None
 */
void aio_manager_idac_enable(void);
/**
 * @brief disable the IDAC block
 * @param None
 * @return None
 */
void aio_manager_idac_disable(void);
/**
 * @brief enable the Buffered REF block
 * @param None
 * @return None
 */
void aio_manager_buf_ref_enable(void);
/**
 * @brief disable the Buffered REF block
 * @param None
 * @return None
 */
void aio_manager_buf_ref_disable(void);
/**
 * @brief enable the VBAT DIV block
 * @param None
 * @return None
 */
void aio_manager_vbat_div_enable(void);
/**
 * @brief disable the VBAT DIV block
 * @param None
 * @return None
 */
void aio_manager_vbat_div_disable(void);
/**
 * @brief enable the VDD CORE block
 * @param None
 * @return None
 */
void aio_manager_vdd_core_enable(void);
/**
 * @brief disable the VDD CORE block
 * @param None
 * @return None
 */
void aio_manager_vdd_core_disable(void);
/**
 * @brief enable the TEMP MON block
 * @param None
 * @return None
 */
void aio_manager_temp_mon_enable(void);
/**
 * @brief disable the TEMP MON block
 * @param None
 * @return None
 */
void aio_manager_temp_mon_disable(void);
/**
 * @brief enable the COMP0 block
 * @param None
 * @return None
 */
void aio_manager_comp0_enable(void);
/**
 * @brief disable the COMP0 block
 * @param None
 * @return None
 */
void aio_manager_comp0_disable(void);
/**
 * @brief enable the COMP1 block
 * @param None
 * @return None
 */
void aio_manager_comp1_enable(void);
/**
 * @brief disable the COMP1 block
 * @param None
 * @return None
 */
void aio_manager_comp1_disable(void);
/**
 * @brief enable the CAP SW block
 * @param None
 * @return None
 */
void aio_manager_cap_sw_enable(void);
/**
 * @brief disable the CAP SW block
 * @param None
 * @return None
 */
void aio_manager_cap_sw_disable(void);


// internal aio_manager functions
/**
 * @brief internal handler, connect a resource block to a muxbus
 * @param resource ID
 * @param muxbus ID
 * @return success or fail  AIO_MANAGER_RET
 */
AIO_MANAGER_RET aio_manager_muxbus_cross_connect(AIO_RESOURCE app_resource_id, AIO_MUXBUS connect_muxbus );

/**
 * @brief internal handler, disconnect a resource block from a muxbus
 * @param resource ID
 * @param muxbus ID
 * @return None
 */
AIO_MANAGER_RET aio_manager_muxbus_disconnect(AIO_RESOURCE app_resource_id, AIO_MUXBUS connect_muxbus);

/**
 * @brief internal handler, check if PIOn can connect to the altio muxor
 * @param altio resource ID
 * @param PIOn
 * @param pointer to a GPIO_DIRECTION
 * @return  AIO_MANAGER_RET_OK or AIO_MANAGER_RET_BAD_ALTIO_PIO_ERROR
 */
AIO_MANAGER_RET altio_pio_definitions(AIO_RESOURCE altio, PIN pio, GPIO_DIRECTION *dir);

/**
 * @brief internal handler, configure altio multiplexor for PIOn
 * @param altio resource ID
 * @param PIOn
 * @param GPIO_DIRECTION
 * @return  AIO_MANAGER_RET_OK or AIO_MANAGER_RET_BAD_ALTIO_PIO_ERROR
 */
AIO_MANAGER_RET aio_manager_altio_configure_mux_for_pio(ANALOG_FUNCTION analog_function, PIN connect_pio );


/**
 * @brief return pointer to the resource status table
 * @param None
 * @return AIO_RESOURCES_STATUS*
 */
AIO_RESOURCES_STATUS *aio_manager_get_status_table(void);
/**
 * @brief return pointer to the deferred enable table
 * @param None
 * @return DEFERRED_MUX_SELECT_CONFIG*
 */
DEFERRED_MUX_SELECT_CONFIG *aio_manager_get_deferred_mux_select_config(void);

#endif  /*AIO_MANAGER_H_*/
