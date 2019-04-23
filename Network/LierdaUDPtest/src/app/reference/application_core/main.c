/******************************************************************************
 * @brief    Application Core Main function for Standard
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/
#include "platform.h"
#include "hal.h"
#include "neulfw.h"
#include "cmsis_rpc.h"
#include "cmsis_os2.h"
#include "hal_reboot.h"
#include "clocks.h"
#include "watchdog.h"
#include "uart.h"
#include "ipc.h"
#include "irmalloc.h"
#include "string.h"
#include "rtc.h"
#include "neul_socket.h"
#include "system_status.h"
#include "app_os_init.h"
#include "log_common.h"
#include "gpio.h"
#include "log_uart.h"
#include "aio_manager.h"
#include "neul_kv_storage.h"
#include "preserve.h"
#include "dma.h"
#include "lierda_app_main.h"
#include "LierdaUDPtest.h"

/**
 * protocol watchdog timeout RTOS_WDT_TIMEOUT_S is 20s
 * which is difined in NeulFreeRTOS.h
 * apps watchdog timeout should be longer than protocol
 */
#define  WDT_TIMEOUT_S     (30)

projcfg_data projcfg_userdata = {0};


void lierda_app_main(void);


void lierda_app_main(void)
{
	lierda_test_main();

}


void hw_init(void);
void hw_init(void)
{
    hal_cpu_init();
    hal_reboot_init();

    // Initialise malloc
    irmalloc_init_default();

    // Initialise the drivers used.
    gpio_init();
    rtc_init();
    system_status_init();
    ipc_init();

#ifndef DISABLE_WDT
    watchdog_init(clocks_get_core_clock()*WDT_TIMEOUT_S, true, true);
    watchdog_enable();
#endif

}


void main( int argc, int argv[] )
{
    UNUSED( argc );
    UNUSED( argv );

    preserve_init();
    hw_init();
    log_init();

    (void)osKernelInitialize();
    dma_init();
    uart_init();

    // Tell the logging logging consumer/writer to switch to using a mutex (requires RTOS init).
    log_init_after_rtos();
    log_uart_init_after_rtos(false);

    socket_init();


    // Set RPC Mailboxes up
    rpc_init();

    // Set the KV storage up
    neul_kv_init();

    (void) aio_manager_init();


    // Set the initialisation routine to run immediately as soon as RTOS starts
    // Note the cast, as uint32 and uint32_t are treated as different on some compilers.

    app_os_init(NULL, 0);

    (void)osKernelStart();
    return;
}
