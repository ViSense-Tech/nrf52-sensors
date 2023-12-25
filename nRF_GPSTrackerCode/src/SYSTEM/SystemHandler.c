/**
 * @file    : SystemHandler.c
 * @brief   : File containing System related functions(sleep/power management)
 * @author  : Adhil
 * @date    : 30-10-2023
 * @note    :
*/

/***************************************INCLUDES*********************************/

#include "RtcHandler.h"
#include "SystemHandler.h"
#include "BleHandler.h"

/***************************************MACROS*********************************/

/***************************************GLOBALS*********************************/ 
const struct gpio_dt_spec sSleepStatusLED = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);
bool bSleepTimeSet = false;
uint32_t ulSleepTime = SLEEP_TIME; 
uint16_t usDiagnosticData = 0;

/***************************************FUNCTION DEFINITIONS********************/
/*
 * @brief Setting Power management policy
 * @param void
 * @return true or false
*/
bool SetPMState()
{
    bool bRetVal = false;

    struct pm_state_info info =
    {
        .exit_latency_us  = 0,
        .min_residency_us = 0,
        .state            = PM_STATE_SUSPEND_TO_RAM,
        .substate_id      = 0,
    };

    bRetVal = pm_state_force(0, &info);
    return bRetVal;
}

/**
 * @brief function for entering sleep mode
 * @param nDuration - Duration for sleep
 * @return none
*/
void EnterSleepMode(int nDuration)
{
    /*Need to add other functions also currently stopping ble 
    advertisement when entering sleep*/
    BleStopAdvertise();
    gpio_pin_set(sSleepStatusLED.port, sSleepStatusLED.pin, 1);
    k_sleep(K_SECONDS(nDuration));

}

/**
 * @brief function for exiting sleep mode
 * @return none
*/
void ExitSleepMode()
{
    /*Need to add other functions that is waking up another peripherals 
    currently starting advertisement after exiting  sleep*/
    StartAdvertising();
}

/**
 * @brief Setting Sleep time
 * @param ucbuffer - buffer for setting sleep time
 * @return void
*/
void SetSleepTime(uint32_t ucbuffer)
{
    ulSleepTime = ucbuffer;
    bSleepTimeSet = true;
}

/**
 * @brief Check if sleep time is set
 * @param None
 * @return true for success
*/
bool IsSleepTimeSet()
{
    return bSleepTimeSet;
}

/**
 * @brief Setting sleep time status
 * @param bStatus : Sleep set status
 * @return None
*/
void SetSleepTimeSetStataus(bool bStatus)
{
    bSleepTimeSet = bStatus;
}

/**
 * @brief Get sleep time
 * @param None
 * @return sleep time
*/
uint32_t GetSleepTime()
{
    return ulSleepTime;
}

/**
 * @brief Get diagnostics data
 * @param None
 * @return Diagnostics value
*/
uint32_t *GetDiagnosticData()
{
    return &usDiagnosticData;
}

