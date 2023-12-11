/**
 * @file    : SystemHandler.c
 * @brief   : File containing functions related to sleep/power management
 * @author  : Adhil
 * @date    : 01-11-2023
 * @note 
*/

/***************************************INCLUDES*********************************/
#include "Systemhandler.h"
#include "AdcHandler.h"
#include "BleHandler.h"


/***************************************MACROS**********************************/

/***************************************TYPEDEFS*********************************/

/***************************************GLOBALS*********************************/
const struct gpio_dt_spec sSleepStatusLED = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);
bool bSleepTimeSet = false;
uint32_t ulSleepTime = SLEEP_TIME; 
static uint32_t ulDiagnosticData = 0;

/***************************************FUNCTION DECLARTAION*********************/

/***************************************FUNCTION DEFINITION*********************/
/**
 * @brief function to add json object to json
 * @param pcJsonHandle - Json object handle
 * @param pcKey - Key name
 * @param pcValue - value
 * @param ucLen - value length
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
 * @param nDuration - time interval keeping device in sleep.
 * @return None
*/
void EnterSleepMode(int nDuration)
{
    struct device *pAdc = NULL;
    struct gpio_dt_spec *psSensorExcitePin1 = NULL;
    struct gpio_dt_spec *psSensorExcitePin2 = NULL; 

    pAdc = GetADCdevice();
    psSensorExcitePin1 = GetExcitePin1();
    psSensorExcitePin2 = GetExcitePin2();
    pm_device_action_run(pAdc, PM_DEVICE_ACTION_SUSPEND);
    pm_device_action_run(psSensorExcitePin1, PM_DEVICE_ACTION_SUSPEND);
    pm_device_action_run(psSensorExcitePin2, PM_DEVICE_ACTION_SUSPEND);
    BleStopAdv();
    gpio_pin_set(sSleepStatusLED.port, sSleepStatusLED.pin, 1);
    printk("INFO: Entering Sleep for %dseconds\n\r", nDuration);
    k_sleep(K_SECONDS(nDuration));
}

/**
 * @brief function for exiting sleep mode
 * @return none
*/
void ExitSleepMode()
{
    struct device *pAdc = NULL;
    struct gpio_dt_spec *psSensorExcitePin1 = NULL;
    struct gpio_dt_spec *psSensorExcitePin2 = NULL;

    printk("Exiting Sleep\n\r");
    pAdc = GetADCdevice();
    StartAdv();
    psSensorExcitePin1 = GetExcitePin1();
    psSensorExcitePin2 = GetExcitePin2();
    pm_device_action_run(pAdc, PM_DEVICE_ACTION_RESUME);
    pm_device_action_run(psSensorExcitePin1, PM_DEVICE_ACTION_RESUME);
    pm_device_action_run(psSensorExcitePin2, PM_DEVICE_ACTION_RESUME);
    gpio_pin_set(sSleepStatusLED.port, sSleepStatusLED.pin, 0);
}

/**
 * @brief Setting Sleep time
 * @param ulTime - buffer for setting sleep time
 * @return void
*/
void SetSleepTime(uint32_t ulTime)
{
    ulSleepTime = ulTime;
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
 * @brief  Get diagnostic data
 * @param  None
 * @return pointer to the diagnostic data
*/
uint32_t *GetDiagData()
{
    return &ulDiagnosticData;
}