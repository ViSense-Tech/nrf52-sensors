/**
 * @file main.c
 * @brief Main function
 * @date 2023-09-27
 * @author Jeslin
 * @note  This is a test code for Irrometer.
*/


/*******************************INCLUDES****************************************/
#include <zephyr/pm/pm.h>
#include <zephyr/pm/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>
#include <nrfx_example.h>
#include <saadc_examples_common.h>
#include <nrfx_saadc.h>
#include <nrfx_log.h>
#include <stdlib.h>
#include <stdio.h>
#include "Json/cJSON.h"
#include "BleHandler.h"
#include "BleService.h"
#include "JsonHandler.h"
#include "RtcHandler.h"

/*******************************MACROS****************************************/
//#define SLEEP_ENABLE  //Uncomment this line to enable sleep functionality
#define ADC_READING_LOWER  0
#define ADC_READING_UPPER  1024
#define ALIVE_TIME         10 //Time the device will be active after a sleep time(in seconds)
#define SLEEP_TIME         30
#define TICK_RATE          32768
#define TIME_STAMP_ERROR   (1<<1)
#define TIME_STAMP_OK      ~(1<<1)

/*******************************GLOBAL VARIABLES********************************/
int  sAdcReadValue1 = 0;
int  sAdcReadValue2 = 0;

const int Rx = 10000;
const float default_TempC = 24.0;
const long open_resistance = 35000;
const long short_resistance = 200;
const long short_CB = 240, open_CB = 255;
const float SupplyV = 3.3;
const float cFactor = 1.1;
cJSON *pcData = NULL;
const struct device *pAdc = NULL;
const struct gpio_dt_spec sSensorPwSpec1 = GPIO_DT_SPEC_GET(DT_ALIAS(testpin0), gpios);
const struct gpio_dt_spec sSensorPwSpec2 = GPIO_DT_SPEC_GET(DT_ALIAS(testpin1), gpios);
const struct gpio_dt_spec sSleepStatusLED = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);
const struct device *psUartHandle = DEVICE_DT_GET(DT_NODELABEL(uart0));



/*******************************FUNCTION DEFINITIONS********************************/

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
int GetAdcResult( const struct gpio_dt_spec *excite_pin_spec)
{
    int16_t AdcReadValue ;
    if (!device_is_ready(excite_pin_spec->port)) {
        printk("Error: %s device not ready\n", excite_pin_spec->port->name);
        return -1;
    }
    gpio_pin_set(excite_pin_spec->port, excite_pin_spec->pin, 1);
    k_sleep(K_MSEC(30)); 

    AdcReadValue = AnalogRead();

    gpio_pin_set(excite_pin_spec->port, excite_pin_spec->pin, 0);
    k_sleep(K_MSEC(30000)); 

    
    return AdcReadValue;
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

	if (res > 550.00)
    { 
		if (res > 8000.00)
        { 
			WM_CB = (-2.246 - 5.239 * resK * (1 + .018 * (TC - 24.00)) - .06756 * resK * resK * (tempD * tempD)) * cF;
		}
        else if (res > 1000.00)
        {
			WM_CB = (-3.213 * resK - 4.093) / (1 - 0.009733 * resK - 0.01205 * (TC)) * cF ;
		}
        else
        {
			WM_CB = (resK * 23.156 - 12.736) * tempD;
		}
	} 
    else
    {
		if (res > 300.00)
        {
			WM_CB = 0.00;
		}
		if (res < 300.00 && res >= short_resistance)
        {
			WM_CB = short_CB;
			printk("Sensor Short WM \n");
		}
	}
	if (res >= open_resistance || res==0)
    {
		WM_CB = open_CB;
	}

    if (WM_CB > 255)
    {
        WM_CB = 255;
    }
	
	return WM_CB;
}

/**
 * @brief calaculating irrometer resistamce
 * @return Resistance value
 * @return None
*/
float readWMsensor(void)
{
    /*Here only measuring resistance from single side only and avoiding ac short pulse method
    and using currently is dc short pulse method*/
    
    float SenVWM1 = (sAdcReadValue1 / 1024.0) * SupplyV;
    //float SenVWM2 = (sAdcReadValue2 / 1024.0) * SupplyV;

    printk("Sensor Voltage A: %f V\n", SenVWM1);
    //printk("Sensor Voltage B: %f V\n", SenVWM2);

    double WM_ResistanceA = (Rx * (SupplyV - SenVWM1) / SenVWM1);
    //double WM_ResistanceB = (Rx * SenVWM2) / (SupplyV - SenVWM2);

    //return (WM_ResistanceA + WM_ResistanceB) / 2.0;
    return WM_ResistanceA;
}

/**
 * @brief ADC event handler
*/
void saadc_callback(nrfx_saadc_evt_t const * p_event) 
{
    // Handle SAADC events here if needed.
}

/**
 * @brief function to initialize adc
 * @param ADC channel
 * @return void
*/
static void InitAdc(nrf_saadc_input_t eAdcChannel, int nChannelIdx)
{
    nrfx_err_t status;
    status = nrfx_saadc_init(NRFX_SAADC_DEFAULT_CONFIG_IRQ_PRIORITY);
    NRFX_ASSERT(status == NRFX_SUCCESS);

    nrfx_saadc_channel_t saadc_channel = {
        .channel_config = {
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
 * @brief function to add json object to json
 * @param pcJsonHandle - Json object handle
 * @param pcKey - Key name
 * @param pcValue - value
 * @param ucLen - value length
 * @return true or false
*/

static bool SetPMState()
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
static void EnterSleepMode(int nDuration)
{
    pm_device_action_run(pAdc, PM_DEVICE_ACTION_SUSPEND);
    pm_device_action_run(&sSensorPwSpec1, PM_DEVICE_ACTION_SUSPEND);
    pm_device_action_run(&sSensorPwSpec2, PM_DEVICE_ACTION_SUSPEND);
    BleStopAdv();
    gpio_pin_set(sSleepStatusLED.port, sSleepStatusLED.pin, 1);
    k_sleep(K_SECONDS(nDuration));
}

/**
 * @brief function for exiting sleep mode
 * @return none
*/
static void ExitSleepMode()
{
    pm_device_action_run(pAdc, PM_DEVICE_ACTION_RESUME);
    pm_device_action_run(&sSensorPwSpec1, PM_DEVICE_ACTION_RESUME);
    pm_device_action_run(&sSensorPwSpec2, PM_DEVICE_ACTION_RESUME);
    gpio_pin_set(sSleepStatusLED.port, sSleepStatusLED.pin, 0);
}

/**
 * @brief Read from ADC cahnnel
 * @param eAdcChannel - ADC channel used
 * @param nChannelIdx - Channel index needs to be used
 * @param pnWM_CB - CB value 
 * @return true for success
*/
static bool ReadFromADC(nrf_saadc_input_t eAdcChannel, int nChannelIdx, int *pnWM_CB)
{
    bool bRetVal = false;
    float WM_Resistance = 0.0;

    if (pnWM_CB)
    {
        InitAdc(eAdcChannel, nChannelIdx);
        k_msleep(50);
        sAdcReadValue1 = GetAdcResult(&sSensorPwSpec1);
        if (sAdcReadValue1 < ADC_READING_LOWER || sAdcReadValue1 > ADC_READING_UPPER)
        {
            sAdcReadValue1 = 0;
        }
        k_msleep(50);
        printk("Reading A1: %d\n", sAdcReadValue1);

        /*Commented here for testing the CB value and will remove or update here once the
        CB measurement issue fixed*/

        // sAdcReadValue2 = GetAdcResult(&sSensorPwSpec2);
        // if (sAdcReadValue2 < ADC_READING_LOWER || sAdcReadValue1 > ADC_READING_UPPER)
        // {
        //    sAdcReadValue2 = 0;
        // }        
        // printk("Reading A2: %d\n", sAdcReadValue2);
        
        WM_Resistance = readWMsensor();
        printk("WM Resistance(Ohms): %d\n", (int)WM_Resistance);
        *pnWM_CB = CalculateCBvalue((int)WM_Resistance, default_TempC, cFactor);
        printk("WM1(cb/kPa): %d\n", abs(*pnWM_CB));
        bRetVal = true;
    }

    return bRetVal;
}

/**
 * @brief Main function
*/
int main(void)
{
    nrfx_err_t status;
    int Ret;
    char cbuffer[20] = {0};
    char *cJsonBuffer = NULL;
    cJSON *pMainObject = NULL;
    uint8_t *pucAdvBuffer = NULL;
    int nCBValue = 0;
    cJSON *pSensorObj = NULL;
    long long llEpochNow = 0;
    int64_t Timenow =0;
    int32_t diagnostic_data = 0; 

    InitRtc();
    gpio_pin_configure_dt(&sSensorPwSpec1, GPIO_OUTPUT_LOW);
    gpio_pin_configure_dt(&sSensorPwSpec2, GPIO_OUTPUT_LOW);
    pucAdvBuffer = GetAdvBuffer();
    Ret = bt_enable(NULL);
	if (Ret) 
    {
		printk("Bluetooth init failed (err %d)\n", Ret);
		return 0;
	}
    Ret = InitExtAdv();
	if (Ret) 
    {
		printk("Advertising failed to create (err %d)\n", Ret);
		return 0;
	}
    Ret = StartAdv();
    if(Ret)
    {
        printk("Advertising failed to start (err %d)\n", Ret);
        return 0;
    }
    
     while (1) 
     {
        #ifdef SLEEP_ENABLE
        Timenow = sys_clock_tick_get();

        while(sys_clock_tick_get() - Timenow < (ALIVE_TIME * TICK_RATE))
        {
        #endif    
            if (GetTimeUpdateStatus())
            {
                InitRtc();
                SetTimeUpdateStatus(false);
            }

            pMainObject = cJSON_CreateObject();

            if (GetCurrenTimeInEpoch(&llEpochNow))
            {
                printk("CurrentEpochTime=%llu\n\r", llEpochNow);
                diagnostic_data = diagnostic_data & TIME_STAMP_OK;
            }
            else
            {
                llEpochNow = 0; 
                printk("Read RTC time failed\n\rCheck RTC chip is connected\n\r");
                diagnostic_data = diagnostic_data | TIME_STAMP_ERROR;
            }

            if (ReadFromADC(NRF_SAADC_INPUT_AIN1, 1,  &nCBValue))
            {
                memset(cbuffer, '\0', sizeof(cbuffer));
                sprintf(cbuffer,"CB=%d", abs(nCBValue));
                printk("Data:%s\n", cbuffer);
                pSensorObj=cJSON_AddObjectToObject(pMainObject, "S1");
                AddItemtoJsonObject(&pSensorObj, NUMBER, "ADC1", &sAdcReadValue1, sizeof(uint16_t));
                AddItemtoJsonObject(&pSensorObj, NUMBER, "ADC2", &sAdcReadValue2, sizeof(uint16_t));
                AddItemtoJsonObject(&pSensorObj, STRING, "CB", (uint8_t*)cbuffer, (uint8_t)strlen(cbuffer)); 
                nrfx_saadc_uninit();
            }

            /*Commented here for measuring only from one sensor which also will be updated finally
            after fixing the measurement of CB value issue*/

            // if (ReadFromADC(NRF_SAADC_INPUT_AIN2, 2,  &nCBValue))
            // {
            //     memset(cbuffer, '\0', sizeof(cbuffer));
            //     sprintf(cbuffer,"CB=%d", abs(nCBValue));
            //     printk("Data:%s\n", cbuffer);
            //     pSensorObj=cJSON_AddObjectToObject(pMainObject, "S2");
            //     AddItemtoJsonObject(&pSensorObj, NUMBER, "ADC1", &sAdcReadValue1, sizeof(uint16_t));
            //     AddItemtoJsonObject(&pSensorObj, NUMBER, "ADC2", &sAdcReadValue2, sizeof(uint16_t));
            //     AddItemtoJsonObject(&pSensorObj, STRING, "CB", (uint8_t*)cbuffer, (uint8_t)strlen(cbuffer)); 
            //     nrfx_saadc_uninit();        
            // }

            // if (ReadFromADC(NRF_SAADC_INPUT_AIN4, 4, &nCBValue))
            // {
            //         memset(cbuffer, '\0', sizeof(cbuffer));
            //     sprintf(cbuffer,"CB=%d", abs(nCBValue));
            //     printk("Data:%s\n", cbuffer);
            //     pSensorObj=cJSON_AddObjectToObject(pMainObject, "S3");
            //     AddItemtoJsonObject(&pSensorObj, NUMBER, "ADC1", &sAdcReadValue1, sizeof(uint16_t));
            //     AddItemtoJsonObject(&pSensorObj, NUMBER, "ADC2", &sAdcReadValue2, sizeof(uint16_t));
            //     AddItemtoJsonObject(&pSensorObj, STRING, "CB", (uint8_t*)cbuffer, (uint8_t)strlen(cbuffer)); 
            //     nrfx_saadc_uninit();
            // }
            AddItemtoJsonObject(&pMainObject, NUMBER, "TS", &llEpochNow, sizeof(long long));
            AddItemtoJsonObject(&pMainObject, NUMBER, "DIAG", &diagnostic_data, sizeof(uint32_t));
            cJsonBuffer = cJSON_Print(pMainObject);
            memset(cbuffer,0 , sizeof(cbuffer));

            pucAdvBuffer[2] = 0x02;
            pucAdvBuffer[3] = (uint8_t)strlen(cJsonBuffer);
            memcpy(pucAdvBuffer+4, cJsonBuffer, strlen(cJsonBuffer));

            printk("JSON:\n%s\n", cJsonBuffer);


            if(IsNotificationenabled())
            {
                VisenseSensordataNotify(pucAdvBuffer+2, ADV_BUFF_SIZE);
            }
            else
            {
                UpdateAdvData();
                StartAdv();
            }

            memset(pucAdvBuffer, 0, ADV_BUFF_SIZE);
            cJSON_Delete(pMainObject);
            cJSON_free(cJsonBuffer);

            #ifndef SLEEP_ENABLE 
            k_sleep(K_MSEC(1000));
            #endif
        #ifdef SLEEP_ENABLE
        }
        #endif

        #ifdef SLEEP_ENABLE
         EnterSleepMode(SLEEP_TIME);
         ExitSleepMode();
        #endif
     }
}
    
