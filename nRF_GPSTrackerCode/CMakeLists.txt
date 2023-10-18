# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(uart_echo_bot)

target_include_directories(app PRIVATE src/GPS
                                        src/LCD
                                        src/ACCLMTR
                                        src/BLE
                                        src/Json)
                                        
target_sources(app PRIVATE  src/GPS/GPSHandler.c
                            src/LCD/LCDHandler.c
                            src/ACCLMTR/Accelerometer.c
                            src/BLE/BleHandler.c
                            src/BLE/BleService.c
                            src/Json/cJSON.c
                            src/Json/Jsonhandler.c
                            src/main.c)
