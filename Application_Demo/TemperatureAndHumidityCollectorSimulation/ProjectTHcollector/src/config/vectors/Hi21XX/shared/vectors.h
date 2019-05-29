/******************************************************************************
 * @brief    Hi21XX Vector Table Definitions
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef VECTORS_H_
#define VECTORS_H_

/** @defgroup CONFIG_VECTORS Hi21XX Interrupt Vectors
 * Hi21XX Interrupt Vectors
 * @ingroup Hi21XX_Base
 * @{
 * */

/**
 * Interrupt vector identifiers
 */
typedef enum
{
    ISR_VECTOR_STACK      = 0,    //!< Main stack pointer (MSP)
    ISR_VECTOR_RESET,             //!< Reset vector, for system start up
    ISR_VECTOR_NMI,               //!< Non-maskable interrupt vector
    ISR_VECTOR_HARD_FAULT,        //!< Hard fault vector
    ISR_VECTOR_SVC        = 11,   //!< Supervisior call vector
    ISR_VECTOR_PEND_SV    = 14,   //!< Pendable service call vector
    ISR_VECTOR_SYS_TICK,          //!< System tick timer vector
    ISR_VECTOR_IRQ_0      = 16,   //!< Interrupt request 0 vector
    ISR_VECTOR_IRQ_1,             //!< Interrupt request 1 vector
    ISR_VECTOR_IRQ_2,             //!< Interrupt request 2 vector
    ISR_VECTOR_IRQ_3,             //!< Interrupt request 3 vector
    ISR_VECTOR_IRQ_4,             //!< Interrupt request 4 vector
    ISR_VECTOR_IRQ_5,             //!< Interrupt request 5 vector
    ISR_VECTOR_IRQ_6,             //!< Interrupt request 6 vector
    ISR_VECTOR_IRQ_7,             //!< Interrupt request 7 vector
    ISR_VECTOR_IRQ_8,             //!< Interrupt request 8 vector
    ISR_VECTOR_IRQ_9,             //!< Interrupt request 9 vector
    ISR_VECTOR_IRQ_10,            //!< Interrupt request 10 vector
    ISR_VECTOR_IRQ_11,            //!< Interrupt request 11 vector
    ISR_VECTOR_IRQ_12,            //!< Interrupt request 12 vector
    ISR_VECTOR_IRQ_13,            //!< Interrupt request 13 vector
    ISR_VECTOR_IRQ_14,            //!< Interrupt request 14 vector
    ISR_VECTOR_IRQ_15,            //!< Interrupt request 15 vector
    ISR_VECTOR_IRQ_16,            //!< Interrupt request 16 vector
    ISR_VECTOR_IRQ_17,            //!< Interrupt request 17 vector
    ISR_VECTOR_IRQ_18,            //!< Interrupt request 18 vector
    ISR_VECTOR_IRQ_19,            //!< Interrupt request 19 vector
    ISR_VECTOR_IRQ_20,            //!< Interrupt request 20 vector
    ISR_VECTOR_IRQ_21,            //!< Interrupt request 21 vector
    ISR_VECTOR_IRQ_22,            //!< Interrupt request 22 vector
    ISR_VECTOR_IRQ_23,            //!< Interrupt request 23 vector
    ISR_VECTOR_MAX_NUMBER         //!< Indicates the maximum number of interrupts supported
} ISR_VECTOR;

/**
 * Prototype for interrupt handler functions
 */
typedef void(*ISR_FUNCTION)(void);

/** @} end of group CONFIG_VECTORS */

#endif  // VECTORS_H_
