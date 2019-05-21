/******************************************************************************
 * @brief    Hi2115 Application Core Vector Table
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#include "vectors.h"

/**
 * Defined to be the highest ISR_VECTOR supported by the core
 */
#define ISR_VECTOR_MAX_SUPPORTED ISR_VECTOR_IRQ_23

/**
 * Initial system stack
 */
extern unsigned long stack_system;     //!< Located at the end of the system stack

//lint -esym(526, stack_system)
//lint -esym(526, IRQ_DMA_Handler)
//lint -esym(526, IRQ_COMP_Handler)
//lint -esym(526, IRQ_EDGE_Handler)
//lint -esym(526, IRQ_I2C1_Handler)
//lint -esym(526, IRQ_SECURITY1_Handler)
//lint -esym(526, IRQ_SWD_COMMS_Handler)
//lint -esym(526, Reset_Handler)
//lint -esym(526, PendSV_Handler)
//lint -esym(526, SVC_Handler)

/**
 * Mandatory application defined system start up routine
 */
extern void Reset_Handler( void );     //!< Reset handler, provides system start up

/**
 * Weak aliased system interrupt handlers
 */
void NMI_Handler( void )            __attribute__((weak, alias("isr_not_implemented")));
void HardFault_Handler( void )      __attribute__((weak, alias("isr_not_implemented")));
void SVC_Handler( void )            __attribute__((weak, alias("isr_not_implemented")));
void PendSV_Handler( void )         __attribute__((weak, alias("isr_not_implemented")));
void SysTick_Handler( void )        __attribute__((weak, alias("isr_not_implemented")));

/**
 * Weak aliased IRQ interrupt handlers
 */
void IRQ_RTC_Handler( void )        __attribute__((weak, alias("isr_not_implemented")));
void IRQ_TMR0_Handler( void )       __attribute__((weak, alias("isr_not_implemented")));
void IRQ_SECURITY0_Handler( void )  __attribute__((weak, alias("isr_not_implemented")));
void IRQ_PROTOCOL0_Handler( void )  __attribute__((weak, alias("isr_not_implemented")));
void IRQ_APPS0_Handler( void )      __attribute__((weak, alias("isr_not_implemented")));
void IRQ_GPIO_Handler( void )       __attribute__((weak, alias("isr_not_implemented")));
void IRQ_DMA_Handler( void )        __attribute__((weak, alias("isr_not_implemented")));
void IRQ_UART0_Handler( void )      __attribute__((weak, alias("isr_not_implemented")));
void IRQ_UART1_Handler( void )      __attribute__((weak, alias("isr_not_implemented")));
void IRQ_SSP0_Handler( void )       __attribute__((weak, alias("isr_not_implemented")));
void IRQ_SSP1_Handler( void )       __attribute__((weak, alias("isr_not_implemented")));
void IRQ_PWM0IN_Handler( void )     __attribute__((weak, alias("isr_not_implemented")));
void IRQ_PWM0OUT_Handler( void )    __attribute__((weak, alias("isr_not_implemented")));
void IRQ_PWM1IN_Handler( void )     __attribute__((weak, alias("isr_not_implemented")));
void IRQ_PWM1OUT_Handler( void )    __attribute__((weak, alias("isr_not_implemented")));
void IRQ_I2C0_Handler( void )        __attribute__((weak, alias("isr_not_implemented")));
void IRQ_LPUART_Handler( void )     __attribute__((weak, alias("isr_not_implemented")));
void IRQ_CAP_Handler( void )        __attribute__((weak, alias("isr_not_implemented")));
void IRQ_COMP_Handler( void )       __attribute__((weak, alias("isr_not_implemented")));
void IRQ_EDGE_Handler( void )       __attribute__((weak, alias("isr_not_implemented")));
void IRQ_I2C1_Handler( void )       __attribute__((weak, alias("isr_not_implemented")));
void IRQ_SECURITY1_Handler( void )  __attribute__((weak, alias("isr_not_implemented")));
void IRQ_UART2_Handler( void )      __attribute__((weak, alias("isr_not_implemented")));
void IRQ_SWD_COMMS_Handler( void )  __attribute__((weak, alias("isr_not_implemented")));

//lint -esym(528, isr_not_implemented)
/**
 * Default interrupt handler, used for when no specific handler has been implemented.
 * Needed for weak aliasing (an aliased function must have static linkage).
 */
static void isr_not_implemented( void )
{
    // An infinite loop, preserving the system state for examination by a debugger
    while( 1 )  //lint !e716
    {
    }
}

/**
 * The interrupt vector table
 */
//lint -esym(714, isr_vector_table)
const ISR_FUNCTION isr_vector_table[ ISR_VECTOR_MAX_SUPPORTED + 1 ]  __attribute__((section(".isr_vector"))) =
{
    [ ISR_VECTOR_STACK ]      = (ISR_FUNCTION)&stack_system,    //lint !e740 !e611 Main Stack Pointer (MSP)
    [ ISR_VECTOR_RESET ]      = Reset_Handler,                  //!< Reset Vector
    [ ISR_VECTOR_NMI ]        = NMI_Handler,                    //!< Non-Maskable Interrupt
    [ ISR_VECTOR_HARD_FAULT ] = HardFault_Handler,              //!< Hard Fault Interrupt
    [ ISR_VECTOR_SVC ]        = SVC_Handler,                    //!< Supervisor Call Interrupt
    [ ISR_VECTOR_PEND_SV ]    = PendSV_Handler,                 //!< Pendable Service Call Interrupt
    [ ISR_VECTOR_SYS_TICK ]   = SysTick_Handler,                //!< System Tick Interrupt
    [ ISR_VECTOR_IRQ_0 ]      = IRQ_RTC_Handler,                //!< RTC Interrupt
    [ ISR_VECTOR_IRQ_1 ]      = IRQ_TMR0_Handler,               //!< Timer Interrupt
    [ ISR_VECTOR_IRQ_2 ]      = IRQ_SECURITY0_Handler,          //!< From Security Interrupt
    [ ISR_VECTOR_IRQ_3 ]      = IRQ_PROTOCOL0_Handler,          //!< From Protocol Interrupt
    [ ISR_VECTOR_IRQ_4 ]      = IRQ_APPS0_Handler,              //!< Core Self Interrupt
    [ ISR_VECTOR_IRQ_5 ]      = IRQ_GPIO_Handler,               //!< GPIO Interrupt
    [ ISR_VECTOR_IRQ_6 ]      = IRQ_DMA_Handler,                //!< DMA Interrupt
    [ ISR_VECTOR_IRQ_7 ]      = IRQ_UART0_Handler,              //!< UART0 Interrupt
    [ ISR_VECTOR_IRQ_8 ]      = IRQ_UART1_Handler,              //!< UART1 Interrupt
    [ ISR_VECTOR_IRQ_9 ]      = IRQ_SSP0_Handler,               //!< SPI0 Interrupt
    [ ISR_VECTOR_IRQ_10 ]     = IRQ_SSP1_Handler,               //!< SPI1 Interrupt
    [ ISR_VECTOR_IRQ_11 ]     = IRQ_PWM0IN_Handler,             //!< PW0 Inner Interrupt
    [ ISR_VECTOR_IRQ_12 ]     = IRQ_PWM0OUT_Handler,            //!< PW0 Outer Interrupt
    [ ISR_VECTOR_IRQ_13 ]     = IRQ_PWM1IN_Handler,             //!< PW1 Inner Interrupt
    [ ISR_VECTOR_IRQ_14 ]     = IRQ_PWM1OUT_Handler,            //!< PW1 Outer Interrupt
    [ ISR_VECTOR_IRQ_15 ]     = IRQ_I2C0_Handler,                //!< I2C0 Interrupt
    [ ISR_VECTOR_IRQ_16 ]     = IRQ_LPUART_Handler,             //!< Low Power UART Interrupt
    [ ISR_VECTOR_IRQ_17 ]     = IRQ_CAP_Handler,                //!< CAP Interrupt
    [ ISR_VECTOR_IRQ_18 ]     = IRQ_COMP_Handler,               //!< COMP Interrupt
    [ ISR_VECTOR_IRQ_19 ]     = IRQ_EDGE_Handler,               //!< EDGE Interrupt
    [ ISR_VECTOR_IRQ_20 ]     = IRQ_I2C1_Handler,               //!< I2C1 Interrupt
    [ ISR_VECTOR_IRQ_21 ]     = IRQ_SECURITY1_Handler,          //!< From Security Interrupt
    [ ISR_VECTOR_IRQ_22 ]     = IRQ_UART2_Handler,              //!< UART2 Interrupt
    [ ISR_VECTOR_IRQ_23 ]     = IRQ_SWD_COMMS_Handler,          //!< SWD Pulse Interrupt
};//lint !e785
