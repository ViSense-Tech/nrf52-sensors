/**
 * @file    : Capsense.c
 * @brief   : File containing functions related to capacitive sensing
 * @author  : Adhil
 * @date    : 09-11-2023
 * @note 
*/

/***************************************INCLUDES*********************************/
#include "../Timer/TimerHandler.h"
#include "../Comparator/CompHandler.h"
#include "../PPI/PPIHandler.h"
#include "Capsense.h"
/***************************************MACROS**********************************/

/***************************************TYPEDEFS*********************************/

/***************************************GLOBALS*********************************/
_sCapSenseChannel sCapSenseChannel = {0};
CapSenseCallback CapCb  = 0;
static bool bTouchSense = false;
const struct gpio_dt_spec sGpio = GPIO_DT_SPEC_GET(DT_ALIAS(testpin0), gpios);
/***************************************FUNCTION DECLARTAION*********************/

/***************************************FUNCTION DEFINITIONS*********************/
/**
 * @brief Set touch sense status
 * @param bStatus : status of touch
 * @return None 
*/
void SetTouchSense(bool bStatus)
{
    bTouchSense = bStatus;
}

/**
 * @brief Get touch sense status
 * @param None
 * @return status of touch occured
*/
bool GetTouchSenseStatus()
{
    return bTouchSense;
}

/**
 * @brief Read Capsense channel info
 * @param None
 * @return Capsense channel info
*/
_sCapSenseChannel *GetCapSenseChannel()
{
    return &sCapSenseChannel;
}

/**
 * @brief Initiate sampling
 * @param None
 * @return None
*/
static void InitiateSampling()
{
    gpio_pin_set(sGpio.port, sGpio.pin, 1);
    StartComparator();
}

/**
 * @brief Sampling algorithm for the touch sense
 * @param psCapSenseChannel : cap sense channel info
 * @param ulTimerCount : timer count sample captured
 * @return None
*/
static void AnalyzeSample(_sCapSenseChannel *psCapSenseChannel, uint32_t ulTimerCount)
{
    static bool bThresholdCrossed = false;

    if (psCapSenseChannel)
    {
        psCapSenseChannel->ulValue = ulTimerCount;

        if (psCapSenseChannel->ulValue > psCapSenseChannel->ulValMax)
        {
            psCapSenseChannel->ulValMax = psCapSenseChannel->ulValue;
        }

        if (psCapSenseChannel->ulValue < psCapSenseChannel->ulValMin)
        {
            psCapSenseChannel->ulValMin = psCapSenseChannel->ulValue;
        }

        if (psCapSenseChannel->ulAvgcounter < INITIAL_CALIBRATION_TIME)
        {
            bThresholdCrossed = false;
        }
        else
        {
            printk("Sample: %d\n\r", psCapSenseChannel->ulValue);
            printk("Threshold: %d\n\r", psCapSenseChannel->ulAvg+HIGH_AVG_THRESHOLD);
            bThresholdCrossed = (psCapSenseChannel->ulValue > (psCapSenseChannel->ulAvg + HIGH_AVG_THRESHOLD));
        }

        psCapSenseChannel->ulRollingAvg = (psCapSenseChannel->ulRollingAvg * (ROLLING_AVG_FACTOR-1) + (psCapSenseChannel->ulValue * ROLLING_AVG_FACTOR))/ROLLING_AVG_FACTOR;
        psCapSenseChannel->ulAvgcounter++;
      
        psCapSenseChannel->ulAvgInt += psCapSenseChannel->ulValue;
        psCapSenseChannel->ulAvg = psCapSenseChannel->ulAvgInt / psCapSenseChannel->ulAvgcounter;

        if (psCapSenseChannel->ulAvgcounter > 1000)
        {
            psCapSenseChannel->ulAvgcounter /= 2;
            psCapSenseChannel->ulAvgInt /= 2;
        }

        psCapSenseChannel->ulValDebounceMsk = (psCapSenseChannel->ulValDebounceMsk << 1) | (bThresholdCrossed ? 1 : 0);

        if (psCapSenseChannel->ulValDebounceMsk == 0)
        {
            printk("INFO: Wait...Touch sense is calibrating\n\r");
        }

        if (psCapSenseChannel->bPressed && ((psCapSenseChannel->ulValDebounceMsk & DEBOUNCE_ITER_MASK) == 0))
        {
            psCapSenseChannel->bPressed = false;
        }

        if (!psCapSenseChannel->bPressed && ((psCapSenseChannel->ulValDebounceMsk & DEBOUNCE_ITER_MASK) == DEBOUNCE_ITER_MASK))
        {
            psCapSenseChannel->bPressed = true;
            
        }
    }
}

/**
 * @brief Sampling get done after calling this function
 * @param ulTimerCount : Captured sample at timer expired or comparator event
 * @return None
*/
void FinalizeSampling(uint32_t ulTimerCount, _sCapSenseChannel *psCapSenseChannel)
{
    if (psCapSenseChannel)
    {
        gpio_pin_set(sGpio.port, sGpio.pin, 0);
        AnalyzeSample(psCapSenseChannel, ulTimerCount);

        if (psCapSenseChannel->bPressed)
        {
           SetTouchSense(true);
        }
    }
}

/**
 * @brief Initialise Capacitive sense module
 * @param psCapSenseChannel : Capsense channel
 * @param psCapSenseConfig  : Capsense configurations
 * @return true for success 
*/
bool CapSenseInit(_sCapSenseConfig *psCapSenseConfig)
{
    bool bRetVal = false;

    if (psCapSenseConfig)
    {
        do
        {
            gpio_pin_configure_dt(&sGpio, GPIO_OUTPUT_LOW);

            if (!InitTimer())
            {
                printk("ERR: Initialising timer failed\n\r");
                break;
            }

            if (!InitComparator())
            {
                printk("ERR: Initialising comparator failed\n\r");
                break;
            }

            if (!InitPPI())
            {
                printk("ERR: Initialising PPI failed\n\r");
                break;
            }

            sCapSenseChannel.ulInputPin = psCapSenseConfig->ulInput;
            sCapSenseChannel.ulOutputPin = psCapSenseConfig->ulOutput;
            sCapSenseChannel.ulRollingAvg = 400 * ROLLING_AVG_FACTOR;
            sCapSenseChannel.ulAvg = 0xFFFF;
            sCapSenseChannel.ulAvgcounter = sCapSenseChannel.ulAvgInt = 0;
            sCapSenseChannel.ulValDebounceMsk = 0;
            sCapSenseChannel.ulValMax = 0;
            sCapSenseChannel.ulValMin = 0xFFFF;
            sCapSenseChannel.ulChannelNum = 0;  

            if (!EnablePPIChannels())
            {
                printk("ERR: Enable PPI channels failed\n\r");
                break;
            }

            bRetVal = true;

        }while (0);
    }

    return bRetVal;
}

/**
 * @brief Set capcitive sensor events
 * @param Callback : Event handler capacitive sensing evnts
 * @return true for success
*/
bool CapSenseSetCallback(CapSenseCallback Callback)
{
    CapCb = Callback;
}

/**
 * @brief Capasitive sensing sampling process
 * @param None
 * @return true for success
*/
bool CapsenseSample(void)
{
    ClearTimer();
    StartTimer();
    InitiateSampling();
}