/******************************************************************************
 * @brief    CRT0 file used for starting up the rest of the code
 * Copyright (c) 2015 NEUL LIMITED
******************************************************************************/

        .syntax unified
        .cpu    cortex-m0
        .fpu    softvfp
        .thumb

        .weak hardware_init_hook
        .weak software_init_hook

/**@brief  Setup the stack used prior to RTOS
           Since it grows downward the stack_system is the first location is the highest address
           The first other usage should therefore be at stack_system + 4
           Should the stack overflow, there would be a hard fault in the core
 * @param  None
 * @retval : None
*/

        .section .stacks,"aw",%progbits

        .set    STACK_SIZE_SYSTEM, 0x00000400
        .align  2
        .global stack_system
        .type   stack_system, %object
        .size   stack_system, STACK_SIZE_SYSTEM
stack_system_end:
        .space  STACK_SIZE_SYSTEM-4
stack_system:
        .space  4

        
/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called.
 * @param  None
 * @retval : None
*/
        .section        .text.Reset_Handler,"ax",%progbits
        .weak           Reset_Handler
        .type           Reset_Handler, %function
        .thumb
        .func           Reset_Handler
Reset_Handler:


        /* Make sure SP is really at the start of the stack */
        ldr     r0, =stack_system
        msr     msp, r0

        /* Check Security core version number table for validity */
        /* The table is copied by the Security core to the beginning of SRAM for this core */
        ldr     r1, =__SYSTEM_STACK_BEGIN__
        ldr     r3, =__SYSTEM_STACK_END__
        ldr     r5, [r1, #0]          /* Security core version table content length.  r5 needs preserving for entirety of this routine */
        cmp     r5, #16               /* Assume anything over 16 words is invalid */
        bhi     .version_table_invalid

        ldr     r0, [r1, #4]          /* ~length */
        mvns    r0, r0
        cmp     r5, r0                /* Simple validation check to ensure we have a proper table and not just random numbers */
        beq     .version_table_valid

.version_table_invalid:
        ldr     r5, =#0               /* An invalid table, so set the length to zero */

.version_table_valid:
        cmp     r5, #0                /* Zero length Security core version table? */
        beq     .stack_fill

        /* Adjust start of prefill position so as not to overwrite Security core version table */
        mov     r0, r5
        adds    r0, #2                /* Add table header size to table content length */
        lsls    r0, r0, #2            /* Convert size in words to bytes */
        adds    r1, r0                /* Update prefill start position */

        /* Prefill the system stack with 0xefbeadde (or deafbeef in little endian) */
.stack_fill:
        subs    r3, r3, r1
        beq     .stack_fill_loop_end
        ldr     r2, =0xefbeadde
.stack_fill_loop:
        str     r2, [r1, #0]           /* Store the quad octet initialisation value in r2 into address in r1 */
        adds    r1, r1, #4             /* Increased address in r1 by a quad octet */
         subs    r3, r3, #4             /* Decrease the number of bytes to do by a quad octet */
        bgt     .stack_fill_loop       /* Keep going until it is all done */
.stack_fill_loop_end:

        /* Clear bss section */
        ldr     r1, =__bss_begin__
        ldr     r3, =__bss_end__
        subs    r3, r3, r1

        beq     .end_clear_bss_loop
        ldr     r2, =#00000000

.clear_bss_loop:
        strb    r2, [r1, #0]           /* Store the octet initialisation value in r2 into address in r1 */
        adds    r1, r1, #1             /* Increased address in r1 by an octet */
        subs    r3, r3, #1             /* Decrease the number of bytes to do by an octet */
        bgt     .clear_bss_loop        /* Keep going until it is all done */
.end_clear_bss_loop:

        /* setup .ramtext section */
        ldr     r1, =__ramtext_begin__
        ldr     r2, =__ramtext_load__
        ldr     r3, =__ramtext_size__
        cmp     r3, #0
        beq     .end_set_ramtext_loop

.set_ramtext_loop:
        ldrb    r4, [r2, #0]           /* Load the octet value into r4 from address in r2 */
        strb    r4, [r1, #0]           /* Store the octet value in r4 to address in r1 */
        adds    r2, r2, #1             /* Move onto next octet */
        adds    r1, r1, #1
        subs    r3, r3, #1             /* Decrease the number of bytes to do by an octet */
        bgt     .set_ramtext_loop      /* Keep going until it is all done */
.end_set_ramtext_loop:

        /* setup .data section */
        ldr     r1, =__data_begin__
        ldr     r2, =__data_load__
        ldr     r3, =__data_size__
        cmp     r3, #0
        beq     .end_set_data_loop

.set_data_loop:
        ldrb    r4, [r2, #0]           /* Load the octet value into r4 from address in r2 */
        strb    r4, [r1, #0]           /* Store the octet value in r4 to address in r1 */
        adds    r2, r2, #1             /* Move onto next octet */
        adds    r1, r1, #1
        subs    r3, r3, #1             /* Decrease the number of bytes to do by an octet */
        bgt     .set_data_loop              /* Keep going until it is all done */
.end_set_data_loop:

        /* Call init functions, if they exist */
        ldr     r3, =hardware_init_hook
        cmp     r3, #0
        beq     .hwinitdone
        mov     lr, pc
        mov     pc, r3
.hwinitdone:

        ldr     r3, =software_init_hook
        cmp     r3, #0
        beq     .swinitdone
        mov     lr, pc
        mov     pc, r3
.swinitdone:

        bl        reboot_notify_security_of_reboot    /* This function notifies the securty core we have rebooted */
                                                    /* Then blocks until it is safe for us to continue */
                                                
        /* Call the application's entry point.*/
        ldr     r1, =#0
        movs    r0, r5           /* argc = length, which will be zero for an invalid table */
        beq     .enter_main

        ldr     r1, =__SYSTEM_STACK_BEGIN__
        adds    r1, #8           /* argv[] at beginning of stack + 8, to skip over version table header */

.enter_main:
        bl      main
        bl      .

        .size  Reset_Handler, .-Reset_Handler
        .endfunc

