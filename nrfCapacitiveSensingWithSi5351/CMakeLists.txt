# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

set(COMMON_PATH "C:/ncs/v2.4.2/modules/hal/nordic/nrfx/samples/common")
 
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(nrf_5351)

target_include_directories(app PRIVATE  src/ADC
                                        src/FreqGenerator
)
                                        
target_sources(app PRIVATE  
                            src/FreqGenerator/FreqGenerator.c
                            src/ADC/ADCHandler.c
                            src/main.c)
