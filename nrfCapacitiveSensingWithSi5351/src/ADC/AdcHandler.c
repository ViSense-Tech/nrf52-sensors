/**
 * @file    : AdcHandler.c
 * @brief   : File containing ADC related functions
 * @author  : Adhil
 * @date    : 30-10-2023
 * @note    :
*/

/***************************************INCLUDES*********************************/
#include "AdcHandler.h"
#include <string.h>

/***************************************MACROS*********************************/
#define PRESSURE_SAMPLE_COUNT   10

/***************************************GLOBALS*********************************/
 struct device *pAdc = NULL;

/***************************************FUNCTION DEFINITIONS********************/
/**
 * @brief  This function is to read raw adc value
 * @param  None 
 * @return uint16_t - ADC result
*/
uint16_t AnalogRead(void)
{
    nrfx_err_t status;
    uint32_t sample_value;

    status = nrfx_saadc_buffer_set(&sample_value, 1);
    NRFX_ASSERT(status == NRFX_SUCCESS);
    status = nrfx_saadc_mode_trigger();
    NRFX_ASSERT(status == NRFX_SUCCESS);

    return sample_value;
}

/**
 * @brief function to initialize adc
 * @return void
*/
void InitADC()
{
    nrfx_err_t status;
    status = nrfx_saadc_init(NRFX_SAADC_DEFAULT_CONFIG_IRQ_PRIORITY);
    NRFX_ASSERT(status == NRFX_SUCCESS);

    nrfx_saadc_channel_t saadc_channel = 
    {
        .channel_config = 
        {
            .resistor_p        = NRF_SAADC_RESISTOR_DISABLED,
            .resistor_n        = NRF_SAADC_RESISTOR_DISABLED,
            .gain              = NRF_SAADC_GAIN1_6,
            .reference         = NRF_SAADC_REFERENCE_VDD4,
            .acq_time          = NRF_SAADC_ACQTIME_10US,
            .mode              = NRF_SAADC_MODE_SINGLE_ENDED,
            .burst             = NRF_SAADC_BURST_DISABLED,
        },
        .pin_p             = NRF_SAADC_INPUT_AIN1,
        .pin_n             = NRF_SAADC_INPUT_DISABLED,
        .channel_index     = 1
    };

    status = nrfx_saadc_channel_config(&saadc_channel);
    NRFX_ASSERT(status == NRFX_SUCCESS);
    
    uint32_t channels_mask = nrfx_saadc_channels_configured_get();
    status = nrfx_saadc_simple_mode_set(channels_mask,
                                        NRF_SAADC_RESOLUTION_10BIT,
                                        NRF_SAADC_OVERSAMPLE_DISABLED,
                                        NULL);
    NRFX_ASSERT(status == NRFX_SUCCESS);
}

#if 0

/**
 * @brief   Reading pressure value
 * @param   unPressureresult : Pressure result 
 * @param   unPressureRaw    : Raw adc value
 * @return  true for success
*/
bool GetPressureReading(uint16_t *unPressureResult, uint32_t *unPressureRaw)
{
    uint16_t unAdcSample = 0;
    uint16_t unPressureSample = 0;
    uint8_t count = 0;
    *unPressureRaw = 0;
    *unPressureResult = 0;
    
    for (uint8_t i = 0; i < PRESSURE_SAMPLE_COUNT; i++)
    {
        
        unAdcSample = AnalogRead();

        if (unAdcSample > pressureZero && pressureZero > 0 && unAdcSample < ADC_MAX_VALUE)
        {
            unPressureSample += ((unAdcSample)-(pressureZero))*(pressuretransducermaxPSI)/(pressureMax-pressureZero);
            count++;
            *unPressureRaw += unAdcSample;   
        }
        k_msleep(100);
    }
    if (count == 0)
    {
        if (unAdcSample > 1023)
        {
            *unPressureRaw = 0; 
        }
        else
        {
            *unPressureRaw = unAdcSample;
        }

        return false;
    }
    else
    {
        *unPressureRaw = *unPressureRaw/count;
        *unPressureResult = unPressureSample/count;
        return true;
    }
}

/**
 * @brief Get pressure zero threshold
 * @param None
 * @return pressure zero threshold
*/
uint32_t GetPressureZero()
{
    return pressureZero;
}

/**
 * @brief Get pressure max threshold
 * @param None
 * @return pressure max threshold
*/
uint32_t GetPressureMax()
{
    return pressureMax;
}

/**
 * @brief Check if pressure zero value is set via ble
 * @param None
 * @return Pressure zero status
*/
bool IsPressureZeroSet()
{
    return bPressureZeroSet;
}

/**
 * @brief Check if pressure max is set
 * @param None
 * @return pressure max status
*/
bool IsPressureMaxSet()
{
    return bPressureMaxSet;
}

/**
 * @brief Set pressure zero status
 * @param bStatus : Status to set
 * @return None
*/
void SetPressureZeroSetStatus(bool bStatus)
{
    bPressureZeroSet = bStatus;
}

/**
 * @brief Set pressure max status
 * @param bStatus : status to set
 * @return None
*/
void SetPressureMaxSetStatus(bool bStatus)
{
    bPressureMaxSet = bStatus;
}

/**
 * @brief Get ADC device handle
 * @param None
 * @return ADC device
*/
struct device *GetADCHandle()
{
    pAdc = device_get_binding("arduino_adc");
    return pAdc;
}

/**
 * @brief Set pressure min
 * @param unPressureVal : pressure value
 * @return None
*/
void SetPressureMin(uint16_t unPressureVal)
{
    unPressureMin = unPressureVal;
    bPressureMinSet = true;
}

/**
 * @brief Get pressure min
 * @param None
 * @return pressure min
*/
uint16_t GetPressureMin()
{
    return unPressureMin;
}

/**
 * @brief Check if pressure min is set
 * @param None
 * @return pressure min status
*/
bool IsPressureMinSet()
{
    return bPressureMinSet;
}

/**
 * @brief Set pressure min status
 * @param bStatus : status to set
 * @return None
*/
void SetPressureMinSetStatus(bool bStatus)
{
    bPressureMinSet = bStatus;
}
#endif