/**
 * @file    : Common.h 
 * @brief   : File containing common headers version 
 * @author  : Adhil
 * @date    : 30-10-2023
 * @note 
*/

#ifndef _COMMON_H
#define _COMMON_H

/***************************************INCLUDES*********************************/
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>
#include <nrfx_example.h>
#include <nrfx_log.h>
#include <stdlib.h>
#include <stdio.h>
#include <zephyr/sys/reboot.h>

/***************************************MACROS**********************************/
#define VISENSE_PRESSURE_SENSOR_FIRMWARE_VERSION     0.0.1
#define VISENSE_PRESSURE_SENSOR_FEATURES             "" 

#endif