/**
 * @file    : AdcHandler.h 
 * @brief   : File containing functions for handling ADC
 * @author  : Adhil
 * @date    : 01-11-2023
 * @note 
*/

#ifndef _ADC_HANDLER_H
#define _ADC_HANDLER_H

/***************************************INCLUDES*********************************/
#include <nrfx_example.h>
#include <saadc_examples_common.h>
#include <nrfx_saadc.h>
#include "Common.h"

/***************************************MACROS**********************************/
#define ADC_READING_LOWER  0
#define ADC_READING_UPPER  1024

/***************************************TYPEDEFS*********************************/

/***************************************FUNCTION DECLARTAION*********************/
void InitAdc(nrf_saadc_input_t eAdcChannel, int nChannelIdx);
void InitIrroMtrExcitingPins(void);
float AnalogRead(void);
int GetAdcResult(struct gpio_dt_spec *psExcitingGpio);
bool ReadFromADC(uint8_t ucMuxChannel, int *pnWM_CB);
int CalculateCBvalue(int res, float TC, float cF);
struct device *GetADCdevice(void);
int GetADCReadingInForwardBias(void);
int GetADCReadingInReverseBias(void);
struct gpio_dt_spec *GetExcitePin2();
struct gpio_dt_spec *GetExcitePin1();

#endif