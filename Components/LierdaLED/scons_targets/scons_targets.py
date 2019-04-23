#===============================================================================
# @brief    Scons Target Definitions File
# Copyright (c) 2017 NEUL LIMITED
#===============================================================================
# 
import os
import copy
from EnvironmentUtils import BuildType


target_arm_sdk_standard_2115_LiteOS = {
    'platform':         'Hi2115',
    'chip':             'Hi2115',
    'core':             'application_core',
    'image_slot':       'apps_a',
    'type':             BuildType.ARM,
    'memory_config':    'standard',
    'application':      'standard',
    'additional_src':   ['rdk', 'customer'],
    'os':               'LiteOS',
    'drivers_set':      'LiteOS',
    'optimisation':     '-Os',
    'unwind':           'off',
    'stackdump':        'on',
    'defines':          [],
    # Apart from the rpc_interface and neul_XXX modules, other modules can be removed to save Application core space.
    'support_libs':     [ 'panic',
                          'rpc_interface',
                          'log',
                          'log_reader',
                          'ota',
                          'neul_kv_storage',
                          'neul',
                          'neul_network',
                          'neul_utils',
                          'activity_indication',
                          'iflog',
                          'aio_functions',
                          'lwip_support',
                          #'ppp',    #PPP lib is about 21KB.
                          'app_at',
                          'app_at_module_production',
                          'logical_channel',
                          'backtrace',   #To enable backtrace, need set 'unwind': 'on'. backtrace increase the application bin file size by 10%.
                        ],
    'support_libs_whole': ['build_version'],
    'defines':          ['UART_DRIVER_CONFIG_USE_VETOS_IN_STEAD_OF_TIMERS']
}

target_arm_rdk_reference_2115_LiteOS = {
    'platform':         'Hi2115',
    'chip':             'Hi2115',
    'core':             'application_core',
    'image_slot':       'apps_a',
    'type':             BuildType.ARM,
    'memory_config':    'standard',
    'application':      'reference',
    'additional_src':   ['rdk', 'customer'],
    'os':               'LiteOS',
    'drivers_set':      'LiteOS',
    'optimisation':     '-Os',
    'unwind':           'on',   #Enable backtrace
    'stackdump':        'off',
    'defines':          [],
    # Apart from the rpc_interface and neul_XXX modules, other modules can be removed to save Application core space.
    'precompiled_libs': [ 'app_at',
                          'activity_indication',
                          'aio_functions',
                          'app_at_module_production',
                          'backtrace',
                          'panic',
                          'rpc_interface',
                          'log',
                          'log_reader',
                          'ota',
                          'neul',
                          'neul_network',
                          'neul_kv_storage',
                          'neul_utils',
                          'iflog',
                          'logical_channel',
                          'ppp',
                          'nlibc',
                          'preserve',
                          'arm_core',
                          'lwip_support',
                          'app_at_ref',
                          'mbedtls',
                          'dns',
                          'lwm2m',
                          'coap',
                          'build_version',
                          'irmalloc',
                          'drivers',
                          'LiteOS',
                          'cmsis',
                          'peripheral_drivers',
                          'lierda_gps',
                          'lierdaModuleStatus',
                          'lierdalib',
                          'lierda_sensor',

                        ],
    'support_libs':     [ #'panic',
                          #'rpc_interface',
                          #'log',
                          #'log_reader',
                          #'ota',
                          #'neul_kv_storage',
                          #'neul',
                          #'neul_network',
                          #'neul_utils',
                          #'activity_indication',
                          #'iflog',
                          #'aio_functions',
                          #'lwip_support',
                          #'ppp',    #PPP lib is about 21KB.
                          #'app_at',
                          #'app_at_module_production',
                          #'logical_channel',
                          #'backtrace',   #To enable backtrace, need set 'unwind': 'on'. backtrace increase the application bin file size by 10%.
                        ],
    'support_libs_whole': [#'build_version',
                           #'..\\app\\reference\\application_core\\ref_lib\\mbedtls',
                           #'..\\app\\reference\\application_core\\ref_lib\\libcoap',
                           #'..\\app\\reference\\application_core\\ref_lib\\lwm2m',
                           #'..\\app\\reference\\application_core\\ref_lib\\app_at_ref',
                           #'..\\app\\reference\\application_core\\ref_lib\\dns',
                          ],
    'defines':          ['UART_DRIVER_CONFIG_USE_VETOS_IN_STEAD_OF_TIMERS',
                         'LIBLWM2M', 
                         'LIBLIBCOAP',
                         'LIBAPP_AT_REF',
                         'Enable_LiteOS',
                         'DTLS',
                         'ENABLE_LOG_UPLOAD',
                         'LWM2M_APPDATA_STD',
                         'LWM2M_LOG_EVENT_STD',
                        ]
}

#===============================================================================
# Target names
#===============================================================================

# Target names to call by scons target=target_name
firmware_configs = {
    'std-2115-LiteOS':          target_arm_sdk_standard_2115_LiteOS,
    'ref-2115-LiteOS':          target_arm_rdk_reference_2115_LiteOS,
}

# Alias names, group several targets under an alias
aliases = {
    'all':                      firmware_configs.keys(),
    'std-2115':                 ['std-2115-LiteOS'],
    'ref-2115':                 ['ref-2115-LiteOS']
}


