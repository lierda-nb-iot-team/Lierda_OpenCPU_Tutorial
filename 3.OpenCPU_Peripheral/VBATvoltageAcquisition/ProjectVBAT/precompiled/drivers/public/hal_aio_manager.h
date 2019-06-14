/******************************************************************************
 * @brief    Hi2115 AIO Manager Driver Header.
 * Copyright (c) 2017 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef HAL_AIO_MANAGER_H_
#define HAL_AIO_MANAGER_H_
#include "neulfw.h"
#include "platform_definitions.h"
#include "gpio_definitions.h"


/* ownership titles */
typedef enum {
   HAL_AIO_RESOURCE_FREE,
   HAL_AIO_RESOURCE_OWNER_APPS_CORE,
   HAL_AIO_RESOURCE_OWNER_PROTOCOL_CORE,
   HAL_AIO_RESOURCE_OWNER_UNKNOWN_ERROR,
}  HAL_AIO_RESOURCE_STATUS;


typedef enum
{
    HAL_MUXBUS_CONFIG_00,  /* bit field value for register */
    HAL_MUXBUS_CONFIG_01,
    HAL_MUXBUS_CONFIG_02,
    HAL_MUXBUS_CONFIG_03,
    HAL_MUXBUS_CONFIG_MUX0, /* indicates muxbus */
    HAL_MUXBUS_CONFIG_MUX1, /* indicates muxbus */
    HAL_MUXBUS_CONFIG_ALTIO, /* indicates muxbus */
    HAL_MUXBUS_CONFIG_NOT_SET
} HAL_MUXBUS_CONFIG;


// bit fields for the PMU configuration registers
#define HAL_AIO_DAC_EN_SHIFT                      (12)
#define HAL_AIO_DAC_SELECT_BUS_SHIFT              (13)
#define HAL_AIO_DAC_SELECT_BUS_MASK               (0x3)
#define HAL_AIO_DAC_SELECT_BUS_SHIFTED_MASK       (HAL_AIO_DAC_SELECT_BUS_MASK<<HAL_AIO_DAC_SELECT_BUS_SHIFT)

#define HAL_AIO_ADC_EN_SHIFT                       (0)
#define HAL_AIO_ADC_SELECT_BUS_SHIFT               (1)
#define HAL_AIO_ADC_SELECT_BUS_MASK                (0x3)
#define HAL_AIO_ADC_SELECT_BUS_SHIFTED_MASK        (HAL_AIO_ADC_SELECT_BUS_MASK<<HAL_AIO_ADC_SELECT_BUS_SHIFT)
#define HAL_AIO_ADC_CTRL_BITSET                    APP_CTRL2_BITSET
#define HAL_AIO_ADC_CTRL_BITCLR                    APP_CTRL2_BITCLR

#define HAL_AIO_CAPSW_EN_SHIFT                      (8)
#define HAL_AIO_CAPSW_SELECT_BUS_SHIFT              (10)
#define HAL_AIO_CAPSW_SELECT_BUS_MASK               (0x3)
#define HAL_AIO_CAPSW_SELECT_BUS_SHIFTED_MASK       (HAL_AIO_CAPSW_SELECT_BUS_MASK<<HAL_AIO_CAPSW_SELECT_BUS_SHIFT)

#define HAL_AIO_PIN_AIO0_SELECT_BUS_SHIFT           (0)
#define HAL_AIO_PIN_AIO0_SELECT_BUS_MASK            (0x1)
#define HAL_AIO_PIN_AIO0_SELECT_BUS_SHIFTED_MASK    (HAL_AIO_PIN_AIO0_SELECT_BUS_MASK<<HAL_AIO_PIN_AIO0_SELECT_BUS_SHIFT)

#define HAL_AIO_PIN_AIO1_SELECT_BUS_SHIFT           (1)
#define HAL_AIO_PIN_AIO1_SELECT_BUS_MASK            (0x1)
#define HAL_AIO_PIN_AIO1_SELECT_BUS_SHIFTED_MASK    (HAL_AIO_PIN_AIO1_SELECT_BUS_MASK<<HAL_AIO_PIN_AIO1_SELECT_BUS_SHIFT)

#define HAL_AIO_IDAC_SELECT_BUS_SHIFT               (24)
#define HAL_AIO_IDAC_SELECT_BUS_MASK                (0x3UL)
#define HAL_AIO_IDAC_SELECT_BUS_SHIFTED_MASK        (HAL_AIO_IDAC_SELECT_BUS_MASK<<HAL_AIO_IDAC_SELECT_BUS_SHIFT)

#define HAL_AIO_BUFREF_EN_SHIFT                     (25)
#define HAL_AIO_BUFREF_SELECT_BUS_SHIFT_MUX0        (16)
#define HAL_AIO_BUFREF_SELECT_BUS_SHIFT_MUX1        (20)
#define HAL_AIO_BUFREF_SELECT_BUS_SHIFT_ALTIO       (26)

#define HAL_AIO_VBATDIV_EN_SHIFT                     (27)
#define HAL_AIO_VBATDIV_SELECT_BUS_SHIFT_MUX0        (17)
#define HAL_AIO_VBATDIV_SELECT_BUS_SHIFT_MUX1        (21)

#define HAL_AIO_VDD_CORE_SELECT_BUS_SHIFT_MUX0        (18)
#define HAL_AIO_VDD_CORE_SELECT_BUS_SHIFT_MUX1        (22)

#define HAL_AIO_TEMPMON_EN_SHIFT                     (8)
#define HAL_AIO_TEMPMON_SELECT_BUS_SHIFT             (9)
#define HAL_AIO_TEMPMON_SELECT_BUS_MASK              (0x1UL)
#define HAL_AIO_TEMPMON_SELECT_BUS_SHIFTED_MASK      (HAL_AIO_TEMPMON_SELECT_BUS_MASK<<HAL_AIO_TEMPMON_SELECT_BUS_SHIFT)

#define HAL_AIO_COMP0_EN_SHIFT                     (10)
#define HAL_AIO_COMP0_SELECT_BUS_SHIFT             (11)
#define HAL_AIO_COMP0_SELECT_BUS_MASK              (0x1UL)
#define HAL_AIO_COMP0_SELECT_BUS_SHIFTED_MASK      (HAL_AIO_COMP0_SELECT_BUS_MASK<<HAL_AIO_COMP0_SELECT_BUS_SHIFT)

#define HAL_AIO_COMP1_EN_SHIFT                     (10)
#define HAL_AIO_COMP1_SELECT_BUS_SHIFT             (11)
#define HAL_AIO_COMP1_SELECT_BUS_MASK              (0x1UL)
#define HAL_AIO_COMP1_SELECT_BUS_SHIFTED_MASK      (HAL_AIO_COMP1_SELECT_BUS_MASK<<HAL_AIO_COMP1_SELECT_BUS_SHIFT)


// define the PIO mux sets for each of the ALT IO blocks
#define HAL_AIO_DAC_OUT_ALT_PIOS_LOWORD  ((1<<12)|(1<<14)|(1<<17)|(1<<19)) // 12, 14, 17, 19
#define HAL_AIO_DAC_OUT_ALT_PIOS_HIWORD  0x0000
#define HAL_AIO_DAC_OUT_ALT_PIOS_DIR GPIO_DIRECTION_OUTPUT

#define HAL_AIO_IDAC_OUT_ALT_PIOS_LOWORD ((1<<14)|(1<<16)|(1<<19)|(1<<21)) // 14, 16, 19, 21
#define HAL_AIO_IDAC_OUT_ALT_PIOS_HIWORD 0x0000
#define HAL_AIO_IDAC_OUT_ALT_PIOS_DIR GPIO_DIRECTION_OUTPUT

#define HAL_AIO_REF_OUT_ALT_PIOS_LOWORD  ((1<<12)|(1<<15)|(1<<17)|(1<<20)) // 12, 15, 17, 20
#define HAL_AIO_REF_OUT_ALT_PIOS_HIWORD  0x0000
#define HAL_AIO_REF_OUT_ALT_PIOS_DIR GPIO_DIRECTION_OUTPUT

#define HAL_AIO_ADC_IN_ALT_PIOS_LOWORD  ((1<<22)|(1<<23)|(1<<24)|(1<<25)|(1<<26)|(1<<27)|(1<<28)|(1<<29)|(1<<30)|(1UL<<31)) // 22-33
#define HAL_AIO_ADC_IN_ALT_PIOS_HIWORD  (1<<(0)|(1<<(33-32))) // do bit32 as (1<<(0)) same (32-32)  for lint,  and 33
#define HAL_AIO_ADC_IN_ALT_PIOS_DIR GPIO_DIRECTION_INPUT

#define HAL_AIO_COMP0_IN_ALT_PIOS_LOWORD ((1<<22)|(1<<24)|(1<<26)|(1<<28)|(1<<30)) // 22, 24, 26, 28, 30, 32
#define HAL_AIO_COMP0_IN_ALT_PIOS_HIWORD (1<<(0)) // do bit32 as (1<<(0)) same (32-32)  for lint
#define HAL_AIO_COMP0_IN_ALT_PIOS_DIR GPIO_DIRECTION_INPUT

#define HAL_AIO_COMP_EXT_REF_ALT_PIOS_LOWORD  ((1<<13)|(1<<16)|(1<<18)|(1<<21)) // 13, 16, 18, 21
#define HAL_AIO_COMP_EXT_REF_ALT_PIOS_HIWORD  0x0000
#define HAL_AIO_COMP_EXT_REF_ALT_PIOS_DIR GPIO_DIRECTION_INPUT

#define HAL_AIO_COMP1_IN_ALT_PIOS_LOWORD ((1<<23)|(1<<25)|(1<<27)|(1<<29)|(1UL<<31)) // 23, 25, 27, 29, 31, 33
#define HAL_AIO_COMP1_IN_ALT_PIOS_HIWORD (1<<(33-32)) // 33
#define HAL_AIO_COMP1_IN_ALT_PIOS_DIR GPIO_DIRECTION_INPUT

#define HAL_AIO_CAP_SW_ALT_PIOS_LOWORD   ((1<<13)|(1<<15)|(1<<18)|(1<<20)) // 13, 15, 18, 20
#define HAL_AIO_CAP_SW_ALT_PIOS_HIWORD   0x0000
#define HAL_AIO_CAP_SW_ALT_PIOS_DIR GPIO_DIRECTION_OUTPUT

#define HAL_AIO_COMP_EXT_REF_PIOS_LOWORD   ((1<<13)|(1<<16)|(1<<18)|(1<<21)) // 13, 16, 18, 21
#define HAL_AIO_COMP_EXT_REF_PIOS_HIWORD   0x0000
#define HAL_AIO_COMP_EXT_REF_PIOS_DIR GPIO_DIRECTION_INPUT



//typedef struct {
//    uint32 BITS_31_0;
//    uint32 BITS_63_32;
//} HAL_ALTIO_PIO_INFO; ;



//HAL_AIO_MANAGER_RET hal_aio_manager_configure_alt_io(alt_io_resource_block, pio_number);


// AIO-Manager contains en/dis-able function for each Analog IO block
/**
 * @brief enable DAC block
 * @param None
 * @return None
 */
void hal_aio_manager_dac_enable(void);
/**
 * @brief disable DAC block
 * @param None
 * @return None
 */
void hal_aio_manager_dac_disable(void);
/**
 * @brief enable ADC block
 * @param None
 * @return None
 */
void hal_aio_manager_adc_enable(void);
/**
 * @brief disable ADC block
 * @param None
 * @return None
 */
void hal_aio_manager_adc_disable(void);
/**
 * @brief enable AIO pin 0
 * @param None
 * @return None
 */
void hal_aio_manager_aio_pin0_enable(void);
/**
 * @brief disable AIO pin 0
 * @param None
 * @return None
 */
void hal_aio_manager_aio_pin0_disable(void);
/**
 * @brief enable AIO pin 1
 * @param None
 * @return None
 */
void hal_aio_manager_aio_pin1_enable(void);
/**
 * @brief disable AIO pin 1
 * @param None
 * @return None
 */
void hal_aio_manager_aio_pin1_disable(void);
/**
 * @brief enable IDAC block
 * @param None
 * @return None
 */
void hal_aio_manager_idac_enable(uint8);
/**
 * @brief disable IDAC block
 * @param None
 * @return None
 */
void hal_aio_manager_idac_disable(void);
/**
 * @brief enable Buffered REF
 * @param None
 * @return None
 */
void hal_aio_manager_buf_ref_enable(void);
/**
 * @brief disable Buffered REF
 * @param None
 * @return None
 */
void hal_aio_manager_buf_ref_disable(void);
/**
 * @brief enable VBAT DIV
 * @param None
 * @return None
 */
void hal_aio_manager_vbat_div_enable(void);
/**
 * @brief disable VBAT DIV
 * @param None
 * @return None
 */
void hal_aio_manager_vbat_div_disable(void);
/**
 * @brief enable TEMP MON
 * @param None
 * @return None
 */
void hal_aio_manager_temp_mon_enable(void);
/**
 * @brief disable TEMP MON
 * @param None
 * @return None
 */
void hal_aio_manager_temp_mon_disable(void);
/**
 * @brief enable COMP 0
 * @param None
 * @return None
 */
void hal_aio_manager_comp0_enable(void);
/**
 * @brief disable COMP 0
 * @param None
 * @return None
 */
void hal_aio_manager_comp0_disable(void);
/**
 * @brief enable COMP 1
 * @param None
 * @return None
 */
void hal_aio_manager_comp1_enable(void);
/**
 * @brief disable COMP 1
 * @param None
 * @return None
 */
void hal_aio_manager_comp1_disable(void);
/**
 * @brief enable CAP SW
 * @param None
 * @return None
 */
void hal_aio_manager_cap_sw_enable(void);
/**
 * @brief disable CAP SW
 * @param None
 * @return None
 */
void hal_aio_manager_cap_sw_disable(void);


// muxbus selection
/**
 * @brief Connect DAC resource using sel_mux
 * @param bit field value for control register
 * @return None
 */
void hal_aio_manager_dac_muxbus_connect(HAL_MUXBUS_CONFIG sel_mux);
/**
 * @brief Connect ADC resource using sel_mux
 * @param bit field value for control register
 * @return None
 */
void hal_aio_manager_adc_muxbus_connect(HAL_MUXBUS_CONFIG sel_mux);
/**
 * @brief Connect TEMP MON resource using sel_mux
 * @param bit field value for control register
 * @return None
 */
void hal_aio_manager_temp_mon_muxbus_connect(HAL_MUXBUS_CONFIG sel_mux);
/**
 * @brief Connect COMP0 resource using sel_mux
 * @param bit field value for control register
 * @return None
 */
void hal_aio_manager_comp0_muxbus_connect(HAL_MUXBUS_CONFIG sel_mux);
/**
 * @brief Connect COMP1 resource using sel_mux
 * @param bit field value for control register
 * @return None
 */
void hal_aio_manager_comp1_muxbus_connect(HAL_MUXBUS_CONFIG sel_mux);
/**
 * @brief Connect CAP SW resource using sel_mux
 * @param bit field value for control register
 * @return None
 */
void hal_aio_manager_cap_sw_muxbus_connect(HAL_MUXBUS_CONFIG sel_mux);
/**
 * @brief Connect Buffered REF resource using sel_mux
 * @param bit field value for control register
 * @return None
 */
void hal_aio_manager_buf_ref_muxbus_connect(HAL_MUXBUS_CONFIG sel_mux);
/**
 * @brief Connect VBAT DIV resource using sel_mux
 * @param bit field value for control register
 * @return None
 */
void hal_aio_manager_vbat_div_muxbus_connect(HAL_MUXBUS_CONFIG sel_mux);

/**
 * @brief disconnect Buffered REF resource from sel_mux
 * @param bit field value for control register
 * @return None
 */
void hal_aio_manager_buf_ref_muxbus_disconnect(HAL_MUXBUS_CONFIG sel_mux);
/**
 * @brief disonnect VBAT DIV resource using sel_mux
 * @param bit field value for control register
 * @return None
 */
void hal_aio_manager_vbat_div_muxbus_disconnect(HAL_MUXBUS_CONFIG sel_mux);

/**
 * @brief Connect VDD CORE resource using sel_mux
 * @param bit field value for control register
 * @return None
 */
void hal_aio_manager_vdd_core_muxbus_connect(HAL_MUXBUS_CONFIG sel_mux);
/**
 * @brief Disconnect VDD CORE resource using sel_mux
 * @param bit field value for control register
 * @return None
 */
void hal_aio_manager_vdd_core_muxbus_disconnect(HAL_MUXBUS_CONFIG sel_mux);

#endif  /*HAL_AIO_MANAGER_H_*/
