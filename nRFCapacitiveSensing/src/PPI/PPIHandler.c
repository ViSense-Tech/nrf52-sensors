/**
 * @file    : Capsense.c
 * @brief   : File containing functions related to PPI
 * @author  : Adhil
 * @date    : 09-11-2023
 * @note 
*/

/***************************************INCLUDES*********************************/
#include "PPIHandler.h"
#include "../Timer/TimerHandler.h"
#include "../Comparator/CompHandler.h"
#include "../Common.h"
/***************************************MACROS**********************************/

/***************************************TYPEDEFS*********************************/

/***************************************GLOBALS*********************************/

static nrf_ppi_channel_t channel;
/***************************************FUNCTION DECLARTAION*********************/

/***************************************FUNCTION DEFINITIONS*********************/

/**
 * @brief Initialise PPI module
 * @param None
 * @return true for success
*/
bool InitPPI()
{
    nrfx_err_t err;
    nrfx_timer_t *psTimer = NULL;
    bool bRetVal = false;
	// /* Configure endpoints of the channel so that comparator event is
	//  * connected with the timer task. 
	//  */

    psTimer = GetTimerHandle();

    if (psTimer)
    {
        /* Allocate a (D)PPI channel. */
        do
        {
            err = nrfx_ppi_channel_alloc(&channel);

            if (err != NRFX_SUCCESS) 
            {
                printk("ERR: (D)PPI channel 1 allocation error: %08x", err);
                break;
            }

            nrfx_gppi_channel_endpoints_setup(channel,
                                nrfx_comp_event_address_get(NRF_COMP_EVENT_UP),
                                nrfx_timer_task_address_get(psTimer, NRF_TIMER_TASK_CAPTURE0));

            bRetVal = true;

        } while (0);

    }		

    return bRetVal;							  
}

/**
 * @brief Enable PPI channels
 * @param None
 * @return true for success
*/
bool EnablePPIChannels()
{
    nrfx_err_t err;
    bool bRetVal = false;

    /* Enable (D)PPI channel. */
#if defined(DPPI_PRESENT)
	err = nrfx_dppi_channel_enable(channel);
#else
	err = nrfx_ppi_channel_enable(channel);
#endif
  
    if (err != NRFX_SUCCESS) 
    {
        printk("Failed to enable (D)PPI channel, error: %08x", err);
    }

    bRetVal = true;

    return bRetVal;
}