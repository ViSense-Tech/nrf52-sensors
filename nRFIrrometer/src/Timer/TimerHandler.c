/**
 * @file    : TimeHandler.c
 * @brief   : File containing functions for handling timer functions
 * @author  : Adhil
 * @date    : 30-10-2023
 * @note 
*/
/***************************************INCLUDES*********************************/
#include "TimerHandler.h"
#include "RtcHandler.h"

/***************************************MACROS**********************************/
#define PERIOD          1000
#define TIMER_INST_IDX  1

/***************************************TYPEDEFS*********************************/

struct device *pRTC = NULL;

/***************************************FUNCTION DECLARTAION*********************/
/**
 * @brief Function for handling TIMER driver events.
 *
 * @param[in] event_type Timer event.
 * @param[in] p_context  General purpose parameter set during initialization of
 *                       the timer. This parameter can be used to pass
 *                       additional information to the handler function, for
 *                       example, the timer ID.
 */
static void TimerExpiredCb(nrf_timer_event_t event_type, void * p_context)
{
    if(event_type == NRF_TIMER_EVENT_COMPARE0)
    {
        /*For test only will remove the following line*/
        if (device_is_ready(pRTC))
        {
            UpdateCurrentTime();
        }
    }
}

/**
 * @brief Initialise timer
 * @param None
 * @return None
*/
void InitTimer()
{
    nrfx_err_t status;

    pRTC = GetI2Chandle();
    nrfx_timer_t sTimer0 = NRFX_TIMER_INSTANCE(TIMER_INST_IDX);
    nrfx_timer_config_t config = NRFX_TIMER_DEFAULT_CONFIG;


    config.bit_width = NRF_TIMER_BIT_WIDTH_32;
    config.p_context = "TIMER1";

    status = nrfx_timer_init(&sTimer0, &config, TimerExpiredCb);
    NRFX_ASSERT(status == NRFX_SUCCESS);

#if defined(__ZEPHYR__)
    IRQ_DIRECT_CONNECT(NRFX_IRQ_NUMBER_GET(NRF_TIMER_INST_GET(TIMER_INST_IDX)), IRQ_PRIO_LOWEST,
                       NRFX_TIMER_INST_HANDLER_GET(TIMER_INST_IDX), 0);
#endif

    nrfx_timer_clear(&sTimer0);

    /* Creating variable desired_ticks to store the output of nrfx_timer_ms_to_ticks function */
    uint32_t desired_ticks = nrfx_timer_ms_to_ticks(&sTimer0, PERIOD);

    /*
     * Setting the timer channel NRF_TIMER_CC_CHANNEL0 in the extended compare mode to stop the timer and
     * trigger an interrupt if internal counter register is equal to desired_ticks.
     */
    nrfx_timer_extended_compare(&sTimer0, NRF_TIMER_CC_CHANNEL0, desired_ticks,
                                NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK, true);

    nrfx_timer_enable(&sTimer0);
}