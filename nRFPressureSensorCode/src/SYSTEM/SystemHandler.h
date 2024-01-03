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
#define ALIVE_TIME              30 //Time the device will be active after a sleep time(in seconds)
#define SLEEP_TIME              30
#define TICK_RATE               32768
#define LIVEDATA_TIMESLOT       TICK_RATE/10
#define HISTORYDATA_TIMESLOT    TICK_RATE/10
//#define PMIC_ENABLED //Uncomment this line to enable PMIC functionality

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