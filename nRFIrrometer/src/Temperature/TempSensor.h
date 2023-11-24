/**
 * @file    : TempSensor.h 
 * @brief   : File containing functions for handling temperature sensor
 * @author  : Adhil
 * @date    : 24-11-2023
 * @note 
*/

#ifndef _TEMP_SENSOR_H
#define _TEMP_SENSOR_H

/***************************************INCLUDES*********************************/
#include <zephyr/drivers/sensor.h>

/***************************************MACROS**********************************/
#define TEMPSENSOR_ERROR   (1<<5)
#define TEMPSENSOR_OK      ~(1<<5)
/***************************************TYPEDEFS**********************************/

/***************************************FUNCTION DECLARATION**********************/
bool ReadTemperatureFromDS18b20(double *pdTemperature);

#endif

