/**
 * @file    : TempSensor.c 
 * @brief   : File containing functions for handling temperature sensor
 * @author  : Adhil
 * @date    : 24-11-2023
 * @note 
*/

/***************************************INCLUDES*********************************/
#include "../Common.h"
#include "TempSensor.h"


/***************************************MACROS***********************************/

/***************************************TYPEDEFS**********************************/

/***************************************FUNCTION DECLARATION**********************/
static struct device *GetTempSensorHandle(void);
/***************************************FUNCTION DEFINITION***********************/
/**
 * @brief Get temperature sensor handle
 * @param None
 * @return Temperature sensor handle
*/
static struct device *GetTempSensorHandle(void)
{
	const struct device *const psTempSensor = DEVICE_DT_GET_ANY(maxim_ds18b20);

	if (psTempSensor == NULL) 
    {
		/* No such node, or the node does not have status "okay". */
		printk("\nError: no device found.\n");
		return NULL;
	}

	if (!device_is_ready(psTempSensor)) 
    {
		printk("\nError: Device \"%s\" is not ready; "
		       "check the driver initialization logs for errors.\n",
		       psTempSensor->name);
		return NULL;
	}

	printk("Found device \"%s\", getting sensor data\n", psTempSensor->name);
	return psTempSensor;
}

/**
 * @brief Read temperature data from sensor
 * @param pdTemperature : To store temperature data
 * @return true for success
 * 
*/
bool ReadTemperatureFromDS18b20(double *pdTemperature)
{
    char cBuffer[50] = {0};
    bool bRetVal = false;
    struct sensor_value sTemperature;
    struct device *psDevice = NULL;
    uint32_t *pDiagData;

    do
    {
        psDevice = GetTempSensorHandle();
        pDiagData = GetDiagData();

        if (psDevice == NULL)
        {
            printk("ERR: Didnt get TempSensor handle\n\r");
            break;
        }
        else
        {
            if (pdTemperature)
            {
                sensor_sample_fetch(psDevice);
                if(sensor_channel_get(psDevice, SENSOR_CHAN_AMBIENT_TEMP, &sTemperature))
                {
                    *pDiagData = *pDiagData | TEMPSENSOR_ERROR;
                }
                else
                {
                    *pDiagData = *pDiagData & TEMPSENSOR_OK;
                }
                sprintf(cBuffer, "%d.%06d", sTemperature.val1, sTemperature.val2);
                printk("temp:%s\n\r", cBuffer);
                *pdTemperature = atof(cBuffer);
                printk("Temp: %f\n\r", *pdTemperature);
                bRetVal = true;
            }
        }

    } while(0);

    return bRetVal;
}

