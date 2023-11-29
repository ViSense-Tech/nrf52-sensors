/**
 * @file    : Capsense.h
 * @brief   : File containing functions related to  capacitivity sensing timer
 * @author  : Adhil
 * @date    : 09-11-2023
 * @note 
*/

/***************************************INCLUDES*********************************/
#include <nrfx_timer.h>

/***************************************MACROS**********************************/
#define TIME_TO_WAIT_MS 1000UL

/***************************************TYPEDEFS*********************************/

/***************************************GLOBALS*********************************/

/***************************************FUNCTION DECLARTAION*********************/
nrfx_timer_t *GetTimerHandle();
bool InitTimer();
void StartTimer();
void ClearTimer();
