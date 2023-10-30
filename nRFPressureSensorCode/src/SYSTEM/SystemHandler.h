/**
 * @file    : TimeHandler.h 
 * @brief   : File containing functions for handling RTC 
 * @author  : Adhil
 * @date    : 30-10-2023
 * @note 
*/
#ifndef _SYSTEM_HANDLER_H
#define _SYSTEM_HANDLER_H

/***************************************INCLUDES*********************************/
#include <zephyr/pm/pm.h>
#include <zephyr/pm/device.h>

/***************************************MACROS**********************************/
#define ALIVE_TIME         10 //Time the device will be active after a sleep time(in seconds)
#define SLEEP_TIME         30
#define TICK_RATE          32768

/***************************************TYPEDEFS*********************************/

/***************************************FUNCTION DECLARTAION*********************/
bool SetPMState();
void EnterSleepMode(int nDuration);
void ExitSleepMode();
void SetSleepTime(uint32_t ucbuffer);
bool IsSleepTimeSet();
void SetSleepTimeSetStataus(bool bStatus);
uint32_t GetSleepTime();

#endif