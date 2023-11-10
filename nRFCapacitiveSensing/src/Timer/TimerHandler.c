/**
 * @file    : Capsense.c
 * @brief   : File containing functions related to capacitive sensing
 * @author  : Adhil
 * @date    : 09-11-2023
 * @note 
*/

/***************************************INCLUDES*********************************/
#include "TimerHandler.h"
#include "../CapSense/Capsense.h"
#include "../Common.h"
/***************************************MACROS**********************************/

/***************************************TYPEDEFS*********************************/

/***************************************GLOBALS*********************************/
nrfx_timer_t timer_inst = NRFX_TIMER_INSTANCE(1);
static _sCapSenseChannel *psCapSensechan = NULL;
/***************************************FUNCTION DECLARTAION*********************/

/***************************************FUNCTION DEFINITIONS*********************/
/**
 * @brief Timeout callback
 * @param eEventType : timer event type
 * @param pvContext  : Timer context
 * @return None
*/
static void TimerExpiredCallback(nrf_timer_event_t eEventType, void * pvContext)
{
    uint32_t ulTimerCount = 0;

    if(eEventType == NRF_TIMER_EVENT_COMPARE0)
    {
        ulTimerCount = nrfx_timer_capture(&timer_inst, NRF_TIMER_CC_CHANNEL0);
        FinalizeSampling(ulTimerCount, psCapSensechan);
    }
}

/**
 * @brief Initialise timer module
 * @param None
 * @return true for success
*/
bool InitTimer()
{
    nrfx_err_t status;
    bool bRetVal = false;
    (void)status;
    nrfx_timer_config_t config = NRFX_TIMER_DEFAULT_CONFIG;
    config.bit_width = NRF_TIMER_BIT_WIDTH_16;
    config.p_context = "TIMER1";

    status = nrfx_timer_init(&timer_inst, &config, TimerExpiredCallback);
    //NRFX_ASSERT(status == NRFX_SUCCESS);
    if (status  == NRFX_SUCCESS)
    {
        /* Creating variable desired_ticks to store the output of nrfx_timer_ms_to_ticks function */
        uint32_t desired_ticks = nrfx_timer_ms_to_ticks(&timer_inst, TIME_TO_WAIT_MS);

        /*
        * Setting the timer channel NRF_TIMER_CC_CHANNEL0 in the extended compare mode to stop the timer and
        * trigger an interrupt if internal counter register is equal to desired_ticks.
        */
        nrfx_timer_extended_compare(&timer_inst, NRF_TIMER_CC_CHANNEL0, desired_ticks,
                                    NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK, false);
        psCapSensechan = GetCapSenseChannel();

        bRetVal = true;
    }

    return bRetVal;
}

/**
 * @brief Read timer handle
 * @param None
 * @return pointer to timer handle
*/
nrfx_timer_t *GetTimerHandle()
{
    return &timer_inst;
}

/**
 * @brief Start timer for sampling
 * @param None
 * @return None
*/
void StartTimer()
{
    if (!nrfx_timer_is_enabled(&timer_inst))
    {
        nrfx_timer_enable(&timer_inst);
        printk("Timer running\n\r");
    }
}

/**
 * @brief Clear timer
 * @param None
 * @return None
*/
void ClearTimer()
{
    nrfx_timer_clear(&timer_inst);
}