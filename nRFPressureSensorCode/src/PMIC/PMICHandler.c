/**
 * @file    : RtcHandler.h 
 * @brief   : File containing functions for handling PMIC
 * @author  : Adhil
 * @date    : 08-12-2023
 * @note 
*/

/***************************************INCLUDES*********************************/
#include "PMICHandler.h"
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/sensor/npm1300_charger.h>
#include <zephyr/sys/printk.h>

#include "nrf_fuel_gauge.h"

/***************************************MACROS**********************************/



/***************************************TYPEDEFS*********************************/


/***************************************PRIVATE GLOBALS***************************/
static float max_charge_current;
static float term_charge_current;
static int64_t ref_time;

static const struct battery_model battery_model = 
{
    #include "battery_model.inc"
};

static const struct device *pDevHandle = DEVICE_DT_GET(DT_NODELABEL(npm1300_ek_charger));
/***************************************FUNCTION DECLARTAION*********************/

static int read_sensors(const struct device *pDevHandle, float *voltage, float *current, float *temp)
{
	struct sensor_value value;
	int ret;
	int retry =3;


	ret = sensor_sample_fetch(pDevHandle);
	if (ret < 0) 
	{
		return ret;
	}

	sensor_channel_get(pDevHandle, SENSOR_CHAN_GAUGE_VOLTAGE, &value);
	*voltage = (float)value.val1 + ((float)value.val2 / 1000000);

	sensor_channel_get(pDevHandle, SENSOR_CHAN_GAUGE_TEMP, &value);
	*temp = (float)value.val1 + ((float)value.val2 / 1000000);

	sensor_channel_get(pDevHandle, SENSOR_CHAN_GAUGE_AVG_CURRENT, &value);
	*current = (float)value.val1 + ((float)value.val2 / 1000000);

	return 0;
}

/**
 * 
*/
int PMICInit()
{
	struct sensor_value value;
	struct nrf_fuel_gauge_init_parameters parameters = { .model = &battery_model };
	int ret;
	int retry = 3;

	do
	{
		ret = read_sensors(pDevHandle, &parameters.v0, &parameters.i0, &parameters.t0);
		if (ret < 0) {
			printk("Init PMIC failed\n\r");
			retry--;
			k_msleep(10);
		}
		else{
			printk("\n\rInit PMIC success\n\r");
			break;
		}
	}
	while(retry > 0);

	/* Store charge nominal and termination current, needed for ttf calculation */
	sensor_channel_get(pDevHandle, SENSOR_CHAN_GAUGE_DESIRED_CHARGING_CURRENT, &value);
	max_charge_current = (float)value.val1 + ((float)value.val2 / 1000000);
	term_charge_current = max_charge_current / 10.f;

	nrf_fuel_gauge_init(&parameters, NULL);

	ref_time = k_uptime_get();

	return 0;
}

/**
 * @brief PMIC reading update
 * @param pfSOC : Percentage of battery level
 * @return rc : return code 0 for success
*/
int PMICUpdate(float *pfSOC)
{
	float voltage;
	float current;
	float temp;
	float soc;
	float tte;
	float ttf;
	float delta;
	int ret;
	int64_t uptime;

	ret = read_sensors(pDevHandle, &voltage, &current, &temp);
	if (ret < 0) 
	{
		printk("Error: Could not read from charger device\n");
		return ret;
	}
	delta = (float) k_uptime_delta(&ref_time) / 1000.f;

	soc = nrf_fuel_gauge_process(voltage, current, temp, delta, NULL);

	printk("V: %.3f, I: %.3f, T: %.2f, ", voltage, current, temp);
	printk("SoC: %.2f, TTE: %.0f\n", soc);
	*pfSOC = soc;

	return 0;
}

/**
 * @brief Get PMIC handle
 * @param None
 * @return PMIC handle
*/
struct device *GetPMICHandle()
{
    return pDevHandle;
}