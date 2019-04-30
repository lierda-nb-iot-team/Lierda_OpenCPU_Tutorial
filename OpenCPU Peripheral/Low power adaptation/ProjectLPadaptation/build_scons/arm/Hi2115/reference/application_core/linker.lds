/******************************************************************************
 * @brief    LDS file setting the memory and code locations
 * Copyright (c) 2015 NEUL LIMITED
******************************************************************************/
/******************************************************************************
 * @brief    Default memory configurations
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/
/* Each core sees RAM starting at the same relative location */
/* 64K for APPS core. */
/*------------------------------------------------------------------------------------------------------------------------*/
/* Application Area Flash Defines */
/* Maximum Application Area allocatable FLASH space pages below minimum NV region*/
/* Maximum Application Area allocatable FLASH space in bytes */
/* Apps core - can be reduced to give more space to KV, system etc */
/* Make the last alias region the logging one*/
/*
 * ******************* PERIPHERAL MANAGER *******************
 * The Peripheral Manager is a section of memory mapped registers that are addressable by all cores.
 * It provides means to claim and configure the various peripherals provided.
 * There are 40 PIOs provided by the Hi2115.  Each PIO can be mapped to a different function.
 * The register maps for each PIO are ordered consecutively in the address space, with each PIO allocated 16 32-bit words
 */
/* Reserved for System Status. */
/* Used to load functions in RAM or not for ROM builds */
OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(Reset_Handler)
/* FLASH sector size is 2K */
/* make this table consistent with the configuration given by the security core */
MEMORY
{
    VECTORS : ORIGIN = 0, LENGTH = 192
    /* FLASH Version Information */
    FLASH_VERSION : ORIGIN = ( 0 + 192 ), LENGTH = 84
    FLASH_PROGRAM : ORIGIN = ( ( ( 0 + 192 ) ) + ( 84 ) ), LENGTH = ( ( ((44) * 8192) ) - ( 192 + 84) )
    /* AC_RAM_LENGTH is total RAM available, including area reserved at the top for IPC Mailboxes. */
    SRAM : ORIGIN = (0x01000000), LENGTH = 0x10000 - (256) - ((32))
    SYSTEM_STATUS : ORIGIN = ((0x01000000) + 0x10000 - (256) - (32)), LENGTH = ((32))
    IPC_MAILBOX : ORIGIN = ((0x01000000) + 0x10000 - (256)), LENGTH = (256)
    /* Peripheral Manager register map */
    PERIPHERALS : ORIGIN = (0x40001000), LENGTH = (40 * 64)
}
SECTIONS
{
    /* Vectors */
    . = 0;
    startup :
    {
        KEEP (*(.isr_vector))
    } > VECTORS
    .version_str :
    {
        . = ALIGN(4);
        KEEP (*(.flash_version))
    } > FLASH_VERSION
    /* Code and const data */
    .text :
    {
        . = ALIGN(4);
        *(.text)
        *(.text*)
        *(.rodata)
        *(.rodata*)
        KEEP (*(.gdb_debug))
        . = ALIGN(4);
    } > FLASH_PROGRAM
    /* exidx and extab are debugging information to allow the unwinding of the
     * stack. See the "backtrace" module. exidx appears to be generated even if we
     * don't ask for full unwinding information (with the -funwind-tables option to
     * the compiler), so was present before backtracing was added. */
    .ARM.exidx :
    {
        __exidx_start = .;
        *(.ARM.exidx*)
        __exidx_end = .;
    } > FLASH_PROGRAM
    .ARM.extab :
    {
        *(.ARM.extab*)
    } > FLASH_PROGRAM
    __RAM_BEGIN__ = ORIGIN(SRAM);
    __RAM_SIZE__ = LENGTH(SRAM);
    /* Stack in SRAM at lowest addresses */
    .stacks (NOLOAD):
    {
        __SYSTEM_STACK_BEGIN__ = .;
        KEEP(*(.stacks))
        __SYSTEM_STACK_END__ = .;
    } > SRAM
    __SYSTEM_STACK_SIZE__ = __SYSTEM_STACK_END__ - __SYSTEM_STACK_BEGIN__;
    /* Code relocated into RAM */
    .ramtext :
    {
        . = ALIGN(4);
        __ramtext_load__ = LOADADDR(.ramtext);
        __ramtext_begin__ = .;
        *(.ramtext)
        *(.ramtext*)
        . = ALIGN(4);
        __ramtext_end__ = .;
    } > SRAM AT > FLASH_PROGRAM
    __ramtext_size__ = __ramtext_end__ - __ramtext_begin__;
    /* Initialised data */
    .data :
    {
        FILL(0xFF)
        __data_load__ = LOADADDR(.data);
        __data_begin__ = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        __data_end__ = .;
    } > SRAM AT > FLASH_PROGRAM
    __data_size__ = __data_end__ - __data_begin__;
    /* Uninitialised data */
    .bss (NOLOAD):
    {
        . = ALIGN(4);
        __bss_begin__ = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end__ = . ;
    } > SRAM
    __bss_size__ = __bss_end__ - __bss_begin__;
    /* Like Uninitialised data, but we don't want to 0 it. Stores backtrace among other things. */
    .preserve (NOLOAD):
    {
        . = ALIGN(4);
        *(preserve)
    } > SRAM
        /* The internal heap uses whatever RAM space remains and so must be the last section for SRAM in the linker script. */
    .heap (NOLOAD):
    {
        . = ALIGN(4);
        __INTHEAP_BEGIN__ = ABSOLUTE(.);
        __INTHEAP_SIZE__ = (ORIGIN(SRAM) + LENGTH(SRAM)) - __INTHEAP_BEGIN__;
    } > SRAM
    /* The System Status Area is under the IPC mailboxes */
    .sys_status (NOLOAD) :
    {
        . = ALIGN(4);
        __sys_status_start__ = .;
        *(.sys_status)
        *(.sys_status*)
        __sys_status_end__ = .;
    } > SYSTEM_STATUS
    /* The IPC mailboxes are at the top of the RAM */
    .ipc_mailbox (NOLOAD):
    {
        . = ALIGN(4);
        __ipc_mailbox_start__ = .;
        *(.ipc_mailbox)
        *(.ipc_mailbox*)
        __ipc_mailbox_end__ = .;
    } > IPC_MAILBOX
    /* Peripheral Manager */
    .peripherals (NOLOAD) :
    {
        *(.peripherals*)
    } > PERIPHERALS
}
