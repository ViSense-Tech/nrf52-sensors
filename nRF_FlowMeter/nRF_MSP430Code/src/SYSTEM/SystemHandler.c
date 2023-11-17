/**
 * @file    : SystemHandler.c
 * @brief   : File containing System related functions(sleep/power management)
 * @author  : Adhil
 * @date    : 30-10-2023
 * @note    :
*/

/***************************************INCLUDES*********************************/
#include "SystemHandler.h"
#include "RtcHandler.h"

/***************************************MACROS*********************************/

/***************************************GLOBALS*********************************/ 
const struct gpio_dt_spec sSleepStatusLED = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);
bool bSleepTimeSet = false;
uint32_t ulSleepTime = SLEEP_TIME; 

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
    /*Need to routine when entering sleep*/
    // struct device *pAdc = NULL;

    // pAdc = GetADCHandle();
    // pm_device_action_run(pAdc, PM_DEVICE_ACTION_SUSPEND);
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
    /*Need to rotine after a sleep*/
    // struct device *pAdc = NULL;

    // // pAdc = GetADCHandle();

    // // if (pAdc)
    // // {    
    // //     pm_device_action_run(pAdc, PM_DEVICE_ACTION_RESUME);
    // //     gpio_pin_set(sSleepStatusLED.port, sSleepStatusLED.pin, 0);
    // // }
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