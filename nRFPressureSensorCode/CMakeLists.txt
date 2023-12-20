cmake_minimum_required(VERSION 3.20.0)

# Handle custom boilerplate, if defined
if(DEFINED CUSTOM_BOILERPLATE)
    include(${CUSTOM_BOILERPLATE})
    return()
endif()
set(BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(COMMON_PATH "C:/ncs/v2.4.2/modules/hal/nordic/nrfx/samples/common")
include(${COMMON_PATH}/common.cmake)

GET_DEVICE_CONFIG_FILES(${BOARD} boards)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(nrfx_example)

target_sources(app PRIVATE src/main.c 
                           src/Json/cJSON.c
                           src/Json/Jsonhandler.c
                           src/BLE/BleHandler.c
						   src/BLE/BleService.c
                           src/RTC/RtcHandler.c
                           src/ADC/AdcHandler.c
                           src/NVS/nvs_flash.c
                           src/SYSTEM/SystemHandler.c
                           src/Timer/Timerhandler.c
                           "C:/ncs/v2.4.2/modules/hal/nordic/nrfx/samples/src/nrfx_saadc/common/saadc_examples_common.c")
target_include_directories(app PRIVATE src/Json 
                                       src/BLE
                                       src/RTC
                                       src/ADC
                                       src/NVS
                                       src/SYSTEM
                                       src/Timer
                                       ${COMMON_PATH} "C:/ncs/v2.4.2/modules/hal/nordic/nrfx/samples/src/nrfx_saadc/common")
