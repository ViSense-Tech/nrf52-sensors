/**
 * @file    : RtcHandler.h 
 * @brief   : File containing functions for handling PMIC
 * @author  : Adhil
 * @date    : 08-12-2023
 * @note 
*/

#ifndef _PMIC_HANDLER_H
#define _PMIC_HANDLER_H

/***************************************INCLUDES*********************************/
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>

/***************************************MACROS**********************************/



/***************************************TYPEDEFS*********************************/


/***************************************FUNCTION DECLARTAION*********************/
int PMICInit();
int PMICUpdate(float *pfSOC);
struct device *GetPMICHandle();

#endif