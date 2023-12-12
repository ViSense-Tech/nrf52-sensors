/**
 * @file    : RtcHandler.h 
 * @brief   : File containing functions for handling RTC 
 * @author  : Adhil
 * @date    : 04-10-2023
 * @note 
*/

#ifndef _RTC_HANDLER_H
#define _RTC_HANDLER_H

/***************************************INCLUDES*********************************/
#include <time.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/devicetree.h>

/***************************************MACROS**********************************/



/***************************************TYPEDEFS*********************************/


/***************************************FUNCTION DECLARTAION*********************/
bool InitRtc();
bool GetCurrenTimeInEpoch(long long *pllCurrEpoch);
void SetRtcTime(uint64_t ullTimestamp);
bool GetTimeUpdateStatus(void);
void SetTimeUpdateStatus(bool bStatus);
struct device *GetI2Chandle();
void printCurrentTime();
void SetCurrentTime(long long llEpochNow);
bool GetCurrentTime( long long *pllEpochCurrent);
void UpdateCurrentTime();
#endif