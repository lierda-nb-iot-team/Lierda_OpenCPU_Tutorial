/**************************************************************************//**
 * @file     Hi21XX.h
 * @brief    CMSIS Cortex-M0 Core Peripheral Access Layer Header File for
 *           Device Hi21XX Apps
 * @version  V3.10
 * @date     23. November 2012
 *
 * @note
 *
 ******************************************************************************/
/* Copyright (c) 2012 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/

/** @defgroup HI21XX_ARMCORE_APPS Hi21XX ARM Core Application Core Specifics
 * Hi21XX ARM Core Application Core Specifics
 * @ingroup Hi21XX_Base
 * @{
 * */

#include "neulfw.h"
#ifndef HI21XX_APPS_H
#define HI21XX_APPS_H

#ifdef __cplusplus
 extern "C" {
#endif


/******************************************************************************/
/*                Processor and Core Peripherals                              */
/******************************************************************************/

/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
 */

typedef enum IRQn
{
/******  Cortex-M0 Processor Exceptions Numbers ***************************************************/
  Thread_mode                   = -16,      /*!<  0 Thread mode                                   */
  NonMaskableInt_IRQn           = -14,      /*!<  2 Non Maskable Interrupt                        */
  HardFault_IRQn                = -13,      /*!<  3 Hard Fault Interrupt                          */
  SVCall_IRQn                   = -5,       /*!< 11 SV Call Interrupt                             */
  PendSV_IRQn                   = -2,       /*!< 14 Pend SV Interrupt                             */
  SysTick_IRQn                  = -1,       /*!< 15 System Tick Interrupt                         */

/******  Device Specific Interrupt Numbers ********************************************************/
  RTC_IRQn                      = 0,        /*!< RTC Interrupt                                    */
  Timer_IRQn                    = 1,        /*!< Timer Interrupt                                  */
  Security_IRQn                 = 2,        /*!< From Security Interrupt                          */
  Protocol_IRQn                 = 3,        /*!< From Protocol Interrupt                          */
  Apps_IRQn                     = 4,        /*!< Core Self Interrupt                              */
  GPIO_IRQn                     = 5,        /*!< GPIO Interrupt                                   */
  DMA_IRQn                      = 6,        /*!< DMA Interrupt                                    */
  UART0_IRQn                    = 7,        /*!< UART0 Interrupt                                  */
  UART1_IRQn                    = 8,        /*!< UART1 Interrupt                                  */
  SSP0_IRQn                     = 9,        /*!< SPI0 Interrupt                                   */
  SSP1_IRQn                     = 10,       /*!< SPI1 Interrupt                                   */
  PWM0_Inner_IRQn               = 11,       /*!< PW0 Inner Interrupt                              */
  PWM0_Outer_IRQn               = 12,       /*!< PW0 Outer Interrupt                              */
  PWM1_Inner_IRQn               = 13,       /*!< PW1 Inner Interrupt                              */
  PWM1_Outer_IRQn               = 14,       /*!< PW1 Outer Interrupt                              */
  I2C0_IRQn                     = 15,       /*!< I2C0 Interrupt                                   */
  LPUART_IRQn                   = 16,       /*!< Low Power UART Interrupt                         */
  CAP_IRQn                      = 17,       /*!< CAP Interrupt                                    */
  COMP_IRQn                     = 18,       /*!< COMP Interrupt                                   */
  EDGE_IRQn                     = 19,       /*!< EDGE Interrupt                                   */
  I2C1_IRQn                     = 20,       /*!< I2C1 Interrupt                                   */
  Security1_IRQn                = 21,       /*!< From Security Interrupt                          */
  UART2_IRQn                    = 22,       /*!< UART2 Interrupt                                  */
  Pulse_SWD_IRQn                = 23,       /*!< SWD Pulse Interrupt                              */

} IRQn_Type;


/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */

/* Configuration of the Cortex-M# Processor and Core Peripherals */
#define __CM0_REV                 0x0000    /*!< Core Revision r2p1                               */
#define __NVIC_PRIO_BITS          2         /*!< Number of Bits used for Priority Levels          */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used     */
#define __MPU_PRESENT             0         /*!< MPU present or not                               */
#define __FPU_PRESENT             0        /*!< FPU present or not                                */

#include <core_cm0.h>                       /* Cortex-M# processor and core peripherals */
/* "system_boudica_apps.h" not created because Initialization is done in code  */


/******************************************************************************/
/*                Device Specific Peripheral registers structures             */
/******************************************************************************/

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/*------------- DMA -----------------------------*/
#define DMA_CHANS (4)

typedef enum
{
    DMA_PERIPHERAL_MEMORY = 0,
    DMA_PERIPHERAL_LP_UART_TX = 1,
    DMA_PERIPHERAL_LP_UART_RX,
    DMA_PERIPHERAL_UART0_TX,
    DMA_PERIPHERAL_UART0_RX,
    DMA_PERIPHERAL_UART1_TX,
    DMA_PERIPHERAL_UART1_RX,
    DMA_PERIPHERAL_UART2_TX,
    DMA_PERIPHERAL_UART2_RX,
    DMA_PERIPHERAL_SSP0_TX,
    DMA_PERIPHERAL_SSP0_RX,
    DMA_PERIPHERAL_SSP1_TX,
    DMA_PERIPHERAL_SSP1_RX,
    DMA_PERIPHERAL_PWM0,
    DMA_PERIPHERAL_PWM1,
    DMA_PERIPHERAL_BIST_ADC,
    DMA_PERIPHERAL_MAX_NUM
} DMA_PERIPHERAL;

// DMA registers
typedef struct
{
    uint32 DMA_STATUS;
    uint32 DMA_CFG;
    uint32 CTRL_BASE_PTR;
    uint32 ALT_CTRL_BASE_PTR;
    uint32 DMA_WAITONREQ_STATUS;
    uint32 CHNL_SW_REQEST;
    uint32 CHNL_USEBURST_SET;
    uint32 CHNL_USEBURST_CLR;
    uint32 CHNL_REQ_MASK_SET;
    uint32 CHNL_REQ_MASK_CLR;
    uint32 CHNL_ENABLE_SET;
    uint32 CHNL_ENABLE_CLR;
    uint32 CHNL_PRI_ALT_SET;
    uint32 CHNL_PRI_ALT_CLR;
    uint32 CHNL_PRIORITY_SET;
    uint32 CHNL_PRIORITY_CLR;
    uint32 res0;
    uint32 res1;
    uint32 res2;
    uint32 ERR_CLR;
}dma_ctrl_t;

typedef struct
{
    uint32 PerID0;
    uint32 PerID1;
    uint32 PerID2;
    uint32 PerID3;
    uint32 PCeID0;
    uint32 PCeID1;
    uint32 PCeID2;
    uint32 PCeID3;
}dma_id_t;

// Channel Control structure
typedef struct
{
    uint32 SrcEndAddr;
    uint32 DestEndAddr;
    volatile uint32 Ctrl;
    uint32 Empty;
}dma_ch_ctrl_t;


#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif


/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/
/* ToDo: add here your device peripherals base addresses
         following is an example for timer                                    */

// Added in a separate file

/******************************************************************************/
/*                         Peripheral declaration                             */
/******************************************************************************/
/* ToDo: add here your device peripherals pointer definitions
         following is an example for timer                                    */



/* DMA Defines */
#define DMA_BASE_ADDR                       0x40005000
#define DMA_CONTROLLER_ENABLE_MASK          (0x1)
#define DMA_CTRL_STAT_DONE_MASK(ch)         (0x1UL << (ch))
#define DMA_CTRL_STAT_SINGLE_REQ_MASK(ch)   (0x1UL << ((ch) + 4))
#define DMA_CTRL_STAT_BURST_REQ_MASK(ch)    (0x1UL << ((ch) + 8))
#define DMA_CTRL_STAT_ACTIVE_MASK(ch)       (0x1UL << ((ch) + 12))
#define DMA_CTRL_STAT_ERROR_MASK            (0x1UL << 16)

/* SSP Defines */
#define SSP0_BASE 0x4000C000
#define SSP1_BASE 0x4000D000

/* UART Defines */
#define UART0_BASE 0x40008000
#define UART1_BASE 0x40009000
#define UART2_BASE 0x4000A000

/* I2C Defines */
#define I2C0_BASE 0x4000404C
#define I2C1_BASE 0x400040A8


/*@}*/ /* end of group Boudica_Apps_Definitions */

#define CLKEN_REG_SSP0_MASK  (1 << 0)
#define CLKEN_REG_SSP1_MASK  (1 << 1)
#define CLKEN_REG_DMA_MASK   (1 << 2)
#define CLKEN_REG_I2C0_MASK  (1 << 3)
#define CLKEN_REG_I2C1_MASK  (1 << 4)
#define CLKEN_REG_PWM_MASK   (1 << 5)

#ifdef __cplusplus
}
#endif

 /** @} end of group HI21XX_ARMCORE_APPS */

#endif  /* HI21XX_APPS_H */
