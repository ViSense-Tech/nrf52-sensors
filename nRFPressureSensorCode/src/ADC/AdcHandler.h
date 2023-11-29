/**
 * @file    : AdcHandler.h 
 * @brief   : File containing functions for handling ADC
 * @author  : Adhil
 * @date    : 30-10-2023
 * @note 
*/

#ifndef _ADC_HANDLER_H
#define _ADC_HANDLER_H

/***************************************INCLUDES*********************************/
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/devicetree.h>
#include <saadc_examples_common.h>
#include <nrfx_saadc.h>

/***************************************MACROS**********************************/
#define ADC_MAX_VALUE           1023

/***************************************TYPEDEFS*********************************/

/***************************************FUNCTION DECLARTAION*********************/
uint16_t AnalogRead(void);
void SetPressureZero(uint32_t ucbuffer);
void SetPressureMax(uint32_t ucbuffer);
void InitADC();
bool GetPressureReading(uint16_t *unPressureResult, uint32_t *unPressureRaw);
uint32_t GetPressureZero();
uint32_t GetPressureMax();
void SetPressureZero(uint32_t ulPressure);
void SetPressureMax(uint32_t ulPressure);
bool IsPressureZeroSet();
bool IsPressureMaxSet();
void SetPressureZeroSetStatus(bool bStatus);
void SetPressureMaxSetStatus(bool bStatus);
struct device *GetADCHandle();
void SetPressureMin(uint16_t unPressureVal);
uint16_t GetPressureMin();
bool IsPressureMinSet();
void SetPressureMinSetStatus(bool bStatus);

#endif