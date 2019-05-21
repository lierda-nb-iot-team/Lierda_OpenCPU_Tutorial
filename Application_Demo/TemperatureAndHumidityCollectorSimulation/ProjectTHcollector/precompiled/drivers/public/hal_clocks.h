/******************************************************************************
 * @brief    BOUDICA SECURITY HAL CLOCKS MODULE HEADER
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef SRC_DRIVERS_BOUDICA_HAL_SECURITY_HAL_CLOCKS_H_
#define SRC_DRIVERS_BOUDICA_HAL_SECURITY_HAL_CLOCKS_H_

#include "neulfw.h"
#include "core.h"
#include "platform.h"


/** @defgroup DRIVER_HAL_CLOCK Hi211X HAL Clock Driver
 * HAL CLOCK Driver
 * @ingroup DRIVER_HAL
 * @{
 * */

#define CLK_GATE_DIVIDE_RATIO_MASK          0xFF
#define HAL_CLOCKS_GATE_DIVIDE_RATIO(x)     ( (uint32) ( x )  & CLK_GATE_DIVIDE_RATIO_MASK )
#define CLK_FREQ_NREFCLKS_REFERENCE_MASK    0xFFFF
#define CLK_FREQ_DAC_CONTROL_WORD_MASK      0xFF

/**
 * Get the divide ratio for the system clock
 * @return divide ratio for the system clock
 */
uint8 hal_clocks_system_get_divide_ratio ( void );

/**
 * Get the divide ratio for the modem clock
 * @return divide ratio for the modem clock
 */
uint8 hal_clocks_modem_get_divide_ratio ( void );

/**
 * Get the divide ratio for the radio clock
 * @return divide ratio for the radio clock
 */
uint8 hal_clocks_radio_get_divide_ratio ( void );

/**
 * Get the control word for the clock hardware control system
 * @return control word for the clock hardware control system
 */
uint8 hal_clocks_ring_oscillator_get_control_word ( void );
/**
 * Get the number of cycles to count the ring clocks
 * @return reference clock cycles to count ring oscillator cycles over.
 */
uint16 hal_clocks_ring_oscillator_get_average_period ( void );

/**
 * Set the high limit for the hardware clock control.
 * @return high target for the ring oscillator clock count over the reference clock periods defined
 */
uint32 hal_clocks_ring_oscillator_get_high_target ( void );

/**
 * Get the low limit for the hardware clock control.
 * @return low target for the ring oscillator clock count over the reference clock periods defined
 */
uint32 hal_clocks_ring_oscillator_get_low_target ( void );

/**
 * Get the last count of ring oscillator cycles on the period defined for the reference clock.
 * @return number of cycles
 */
uint32 hal_clocks_ring_oscillator_get_clock_cycles_in_last_period ( void );

/**
 * Core clock mid value.
 * @return Core clock mid value in Hz
 * @note This function has been included so other hal modules could request for a clock reference.
 * The result of this function will only match the clock when the hardware control is active and the clock is stable.
 */
uint32 hal_clocks_get_core_clock_mid_value (void);

/**
 * Set the high limit for the hardware clock control. When the clock is above this count over
 * the periods set for the reference clock it will be corrected.
 * @param target high target for the ring oscillator clock count over the reference clock periods defined
 */
void  hal_clocks_ring_oscillator_set_high_target ( uint32 target );

/**
 * Set the low limit for the hardware clock control. When the clock is bellow this count over
 * the periods set for the reference clock it will be corrected.
 * @param target high target for the ring oscillator clock count over the reference clock periods defined
 */
void  hal_clocks_ring_oscillator_set_low_target ( uint32 target );

/**
 * Set the divide ratio for the system clock
 * @param ratio divide ratio for the system clock
 */
void  hal_clocks_system_set_divide_ratio ( uint8 ratio );

/** @} end of group DRIVER_HAL_CLOCKS */

#endif /* SRC_DRIVERS_BOUDICA_HAL_SECURITY_HAL_CLOCKS_H_ */
