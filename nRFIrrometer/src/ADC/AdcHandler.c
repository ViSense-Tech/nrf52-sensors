/**
 * @file    : AdcHandler.c
 * @brief   : File containing functions for handling ADC
 * @author  : Adhil
 * @date    : 01-11-2023
 * @note 
*/

/***************************************INCLUDES*********************************/
#include "AdcHandler.h"
#include "Common.h"
/***************************************MACROS**********************************/

/***************************************TYPEDEFS*********************************/

/***************************************GLOBALS*********************************/
const int Rx = 10000;
const float default_TempC = 24.0;
const long open_resistance = 35000;
const long short_resistance = 200;
const long short_CB = 240, open_CB = 255;
const float SupplyV = 3.3;
const float cFactor = 1.1;
int  nAdcValueFwdBias = 0;
int  nAdcValueRvrsBias = 0;
const struct device *pAdc = NULL;
const struct gpio_dt_spec sSensorExcitePin1 = GPIO_DT_SPEC_GET(DT_ALIAS(testpin0), gpios);
const struct gpio_dt_spec sSensorExcitePin2 = GPIO_DT_SPEC_GET(DT_ALIAS(testpin1), gpios);
/***************************************FUNCTION DECLARTAION*********************/

/***************************************FUNCTION DEFINITIONS*********************/
/**
 * @brief Get ADC device handle
 * @param None
 * @return ADC handle
*/
struct device *GetADCdevice(void)
{
    pAdc = device_get_binding("arduino_adc");
    return pAdc;
}

/**
 * @brief Getting Excite gpio pin for forward bias supply
 * @param None
 * @return Gpio pin to provide supply in forward direction
*/
struct gpio_dt_spec *GetExcitePin1()
{
    return &sSensorExcitePin1;
}

/**
 * @brief Getting Excite gpio pin for forward bias supply
 * @param None
 * @return Gpio pin to provide supply in reverse direction
*/
struct gpio_dt_spec *GetExcitePin2()
{
    return &sSensorExcitePin2;
}

/**
 * @brief Read adc value in forward bias
 * @param None
 * @return ADC reading in positive polarity
*/
int GetADCReadingInForwardBias()
{
    return nAdcValueFwdBias;
}

/**
 * @brief Read adc value in forward bias
 * @param None
 * @return ADC reading in negative polarity
*/
int GetADCReadingInReverseBias()
{
    return nAdcValueRvrsBias;
}

/**
 * @brief ADC event handler
 * @param p_event : SAADC Events
 * @note Not used for now ADC readings are by polling method if
 *       we are using interrupt or any other SAADC events which will
 *       be happening here.
*/
static int saadc_callback(nrfx_saadc_evt_t const * p_event) 
{
    // Handle SAADC events here if needed.
}

/**
 * @brief calaculating irrometer resistamce
 * @return Resistance value
 * @return None
*/
float readWMsensor(void)
{
    float SenVWM1 = (nAdcValueFwdBias / 1024.0) * SupplyV;
    float SenVWM2 = (nAdcValueRvrsBias / 1024.0) * SupplyV;

    printk("Sensor Voltage A: %f V\n", SenVWM1);
    printk("Sensor Voltage B: %f V\n", SenVWM2);

    double WM_ResistanceA = (Rx * (SupplyV - SenVWM1) / SenVWM1);
    double WM_ResistanceB = (Rx * SenVWM2) / (SupplyV - SenVWM2);

    return (WM_ResistanceA + WM_ResistanceB) / 2.0;
}

/**
 * @brief Calculating CB value 
 * @param res: resistance value calculated
 * @param TC:soil temperature
 * @param CF
 * @return CB value
*/
int CalculateCBvalue(int res, float TC, float cF)
{  

	int WM_CB;
	float resK = res / 1000.0;
	float tempD = 1.00 + 0.018 * (TC - 24.00);

    /*if Watermark sesnsor resistance is greater than 550ohms we are sensing 
    moisture content but not too saturated soil */
	if (res > 550.00)
    { 
		if (res > 8000.00)
        { 
            /*CB value calculation if resistance is above 8 k ohms*/
			WM_CB = (-2.246 - 5.239 * resK * (1 + .018 * (TC - 24.00)) - .06756 * resK * resK * (tempD * tempD)) * cF;
		}
        else if (res > 1000.00)
        {
            /*CB value calculation if resistance is above 1 k ohms*/
			WM_CB = (-3.213 * resK - 4.093) / (1 - 0.009733 * resK - 0.01205 * (TC)) * cF ;
		}
        else
        {
            /*CB value calculation if resistance is below 1 k ohms*/
			WM_CB = (resK * 23.156 - 12.736) * tempD;
		}
	} 
    else
    { 
		if (res > 300.00)
        {
        /*If resitance is calculated is more near to short resistance threshold 200 ohms
        take CB as 0*/

			WM_CB = 0.00;
		}
		if (res < 300.00 && res >= short_resistance)
        {
            /*If resistance is reaching short resitance raise fault CB
            240*/
			WM_CB = short_CB;
			printk("Sensor Short WM \n");
		}
	}
	if (res >= open_resistance || res==0)
    {
        /*If resistance is greater than open resistance threshold take CB as 255
        for fault code indicating sensor is not connected or it is faulty*/        
		WM_CB = open_CB;
	}

    if (WM_CB > 255)
    {
        WM_CB = 255;
    }
	
	return WM_CB;
}

/**
 * @brief Initialize the GPIO pins for exciting the irrometer sensor
 * @param None
 * @return None
*/
void InitIrroMtrExcitingPins(void)
{
    gpio_pin_configure_dt(&sSensorExcitePin1, GPIO_OUTPUT_LOW);
    gpio_pin_configure_dt(&sSensorExcitePin2, GPIO_OUTPUT_LOW);
}

/**
 * @brief function to initialize adc
 * @param eAdcChannel : ADC channel to use
 * @param nChannelIdx : Channel index 
 * @return None
*/
void InitAdc(nrf_saadc_input_t eAdcChannel, int nChannelIdx)
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
            .gain              = NRF_SAADC_GAIN1_4,
            .reference         = NRF_SAADC_REFERENCE_VDD4,
            .acq_time          = NRF_SAADC_ACQTIME_10US,
            .mode              = NRF_SAADC_MODE_SINGLE_ENDED,
            .burst             = NRF_SAADC_BURST_DISABLED,
        },
        .pin_p             = eAdcChannel,
        .pin_n             = NRF_SAADC_INPUT_DISABLED,
        .channel_index     = nChannelIdx
    };

    status = nrfx_saadc_channel_config(&saadc_channel);
    NRFX_ASSERT(status == NRFX_SUCCESS);
    
    uint32_t channels_mask = nrfx_saadc_channels_configured_get();
    status = nrfx_saadc_simple_mode_set(channels_mask,
                                        NRF_SAADC_RESOLUTION_10BIT,
                                        NRF_SAADC_OVERSAMPLE_DISABLED,
                                        NULL);
    NRFX_ASSERT(status == NRFX_SUCCESS);

    k_sleep(K_MSEC(100)); 

}

/**
 * @brief  This function is to read raw adc value
 * @param  None 
 * @return float - ADC result
*/
float AnalogRead(void)
{

    nrfx_err_t status;
    nrf_saadc_value_t sample_value;

    status = nrfx_saadc_buffer_set(&sample_value, 1);
    NRFX_ASSERT(status == NRFX_SUCCESS);
    
    status = nrfx_saadc_mode_trigger();
    NRFX_ASSERT(status == NRFX_SUCCESS);

    return sample_value;
}

/**
 * @brief Get ADC reading
 * @param Sensor excitation pins
 * @return ADC readout
*/
int GetAdcResult(struct gpio_dt_spec *psExcitingGpio)
{
    int16_t AdcReadValue ;

    if (!device_is_ready(psExcitingGpio->port)) 
    {
        printk("Error: %s device not ready\n", psExcitingGpio->port->name);
        return -1;
    }
    gpio_pin_set(psExcitingGpio->port, psExcitingGpio->pin, 1);
    k_sleep(K_USEC(90)); 

    AdcReadValue = AnalogRead();

    gpio_pin_set(psExcitingGpio->port, psExcitingGpio->pin, 0);
    k_sleep(K_MSEC(100)); 

    
    return AdcReadValue;
}

/**
 * @brief Read from ADC cahnnel
 * @param eAdcChannel - ADC channel used
 * @param nChannelIdx - Channel index needs to be used
 * @param pnWM_CB - CB value 
 * @return true for success
*/
bool ReadFromADC(nrf_saadc_input_t eAdcChannel, int nChannelIdx, int *pnWM_CB)
{
    bool bRetVal = false;
    float WM_Resistance = 0.0;

    if (pnWM_CB)
    {
        InitAdc(eAdcChannel, nChannelIdx);
        k_msleep(50);
        nAdcValueFwdBias = GetAdcResult(&sSensorExcitePin1);
        if (nAdcValueFwdBias < ADC_READING_LOWER || nAdcValueFwdBias > ADC_READING_UPPER)
        {
            nAdcValueFwdBias = 0;
        }
        k_msleep(50);
        printk("Reading A1: %d\n", nAdcValueFwdBias);

        nAdcValueRvrsBias = GetAdcResult(&sSensorExcitePin2);
        if (nAdcValueRvrsBias < ADC_READING_LOWER || nAdcValueRvrsBias > ADC_READING_UPPER)
        {
           nAdcValueRvrsBias = 0;
        }        
        printk("Reading A2: %d\n", nAdcValueRvrsBias);
        
        WM_Resistance = readWMsensor();
        printk("WM Resistance(Ohms): %d\n", (int)WM_Resistance);
        *pnWM_CB = CalculateCBvalue((int)WM_Resistance, default_TempC, cFactor);
        printk("WM1(cb/kPa): %d\n", abs(*pnWM_CB));
        bRetVal = true;
    }

    return bRetVal;
}