# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(uart_echo_bot)

target_include_directories(app PRIVATE src/Uart
                                        src/BLE
                                        src/Json
                                        src/RTC
                                        src/SYSTEM
                                        src/Timer
                                        src/PMIC
                                        src/Flash)
                                        
target_sources(app PRIVATE  src/Uart/UartHandler.c
                            src/BLE/BleHandler.c
                            src/BLE/BleService.c
                            src/Json/cJSON.c
                            src/Json/Jsonhandler.c
                            src/RTC/RtcHandler.c
                            src/SYSTEM/SystemHandler.c
                            src/Timer/TimerHandler.c
                            src/Flash/FlashHandler.c
                            src/PMIC/PMICHandler.c
                            src/main.c)
