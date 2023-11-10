/**
 * @file    : Capsense.c
 * @brief   : File containing functions related to comparator
 * @author  : Adhil
 * @date    : 09-11-2023
 * @note 
*/

/***************************************INCLUDES*********************************/
#include "CompHandler.h"
#include "../Timer/TimerHandler.h"
#include "../CapSense/Capsense.h"
#include "../Common.h"
/***************************************MACROS**********************************/
#define COMP_LPCOMP_IRQn	19
/***************************************TYPEDEFS*********************************/

/***************************************GLOBALS*********************************/
static _sCapSenseChannel *psCapSenseChan = NULL;
static nrfx_timer_t *psTimer = NULL;

/***************************************FUNCTION DECLARTAION*********************/

/***************************************FUNCTION DEFINITIONS*********************/

/**
 * @brief Comparator ISR
 * @param Comparator event
 * @return None
*/
void comparator_handler(nrf_comp_event_t event)
{
    uint32_t ulTimerCount = 0;

	if(event == NRF_COMP_EVENT_UP)
	{
        ulTimerCount = nrfx_timer_capture(psTimer, NRF_TIMER_CC_CHANNEL0);
        FinalizeSampling(ulTimerCount, psCapSenseChan);
	}
}

/**
 * @brief Comparator Initialisation
 * @param None
 * @return true for success
*/
bool InitComparator()
    {
        nrfx_err_t err;
        bool bRetVal = false;

        nrfx_comp_pin_select(NRF_COMP_INPUT_2);
        nrfx_comp_config_t  comp_config = NRFX_COMP_DEFAULT_CONFIG(NRF_COMP_INPUT_2);

        err = nrfx_comp_init(&comp_config, comparator_handler);

        if (err != NRFX_SUCCESS) 
        {
            return bRetVal;
        }

        bRetVal = true;
        /* Connect COMP_IRQ to nrfx_comp_irq_handler */
        IRQ_CONNECT(COMP_LPCOMP_IRQn,
                4,
                nrfx_isr, nrfx_comp_irq_handler, 0);

        psCapSenseChan = GetCapSenseChannel();
        psTimer = GetTimerHandle();

      return bRetVal;      
}

/**
 * @brief Start Comparator module
 * @param None
 * @return None
*/
void StartComparator(void)
{
    nrfx_comp_start(( NRFX_COMP_EVT_EN_UP_MASK /*| NRFX_COMP_EVT_EN_DOWN_MASK */),  
                    (NRFX_COMP_SHORT_STOP_AFTER_UP_EVT /* | NRFX_COMP_SHORT_STOP_AFTER_DOWN_EVT */));	
}
