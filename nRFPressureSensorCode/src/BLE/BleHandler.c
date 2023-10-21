/**
 * @file Blehandler.c
 * @author
 * @brief
 * @date
 * 
*/

/***********************************INCLUDES**************************/
#include "BleHandler.h"

/************************************MACROS***************************/
#define DEVICE_NAME             CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN         (sizeof(DEVICE_NAME) - 1)

/************************************GLOBALS**************************/
static struct bt_le_ext_adv *adv;

uint8_t ucAdVertsingBuffer[ADV_BUFF_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00};

static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN)
	//BT_DATA(BT_DATA_MANUFACTURER_DATA, ucAdVertsingBuffer, ADV_BUFF_SIZE)
};

/**********************************FUNCTION DEFINITION****************/

/**
 * @brief  This function isfor Enabling BLE
 * @param  None 
 * @return True for success
*/
bool EnableBLE()
{
    int nError = 0;
    bool bRetVal = false;

    nError = bt_enable(NULL);

	if (!nError) 
    {
        bRetVal = true;
	}
    else
    {
		printk("Bluetooth init failed (err %d)\n", nError);
    }

    return bRetVal;
}

/**
 * @brief function to initialize extended advertising
 * @return nRetVal - 0 for success
*/
#ifdef EXTENDED_ADV
int InitExtendedAdv(void)
{
	int nRetVal = 0;
	struct bt_le_adv_param param =
		BT_LE_ADV_PARAM_INIT(BT_LE_ADV_OPT_CONNECTABLE |
				     BT_LE_ADV_OPT_EXT_ADV,
				     BT_GAP_ADV_FAST_INT_MIN_2,
				     BT_GAP_ADV_FAST_INT_MAX_2,
				     NULL);

	nRetVal = bt_le_ext_adv_create(&param, NULL, &adv);
	do
    {
        if (nRetVal) 
        {
		    printk("Failed to create advertiser set (err %d)\n", nRetVal);
		    break;
	    }

	    printk("Created adv: %p\n", adv);
	    nRetVal = bt_le_ext_adv_set_data(adv, ad,ARRAY_SIZE(ad), NULL, 0);

	    if (nRetVal) 
        {
	    	printk("Failed to set advertising data (err %d)\n", nRetVal);
	    	break;
	    }

    } while(0);
    
	return nRetVal;
}
#else
int InitAdv(void)
{

	int nError = 0;
    	struct bt_le_adv_param param =
		BT_LE_ADV_PARAM_INIT(BT_LE_ADV_OPT_CONNECTABLE |
				     BT_LE_ADV_OPT_USE_NAME,
				     BT_GAP_ADV_FAST_INT_MIN_2,
				     BT_GAP_ADV_FAST_INT_MAX_2,
				     NULL);
        	int err;

	printk("Bluetooth initialized\n");

	err = bt_le_adv_start(&param, ad, ARRAY_SIZE(ad), NULL, 0);
	if (err) {
		printk("Advertising failed to init (err %d)\n", err);
		return;
	}            

    return nError;
}
#endif

/**
 * @brief function to start advertising
 * @return nError - 0 for success
*/
int StartAdvertising(void)
{
	int nError = 0;
#ifdef EXTENDED_ADV
	nError = bt_le_ext_adv_start(adv, NULL);

	if (nError) 
    {
		printk("Failed to start advertising set (err %d)\n", nError);
	}
    else
    {
        printk("Advertiser %p set started\n", adv);
    }
#else

	nError = bt_le_adv_start(BT_LE_ADV_CONN, ad, ARRAY_SIZE(ad), NULL, 0);
	if (nError) 
    {
		printk("Advertising failed to start (err %d)\n", nError);
	}

#endif
    return nError;
}


/**
 * @brief function to update advertising data
 * @return nError - 0 for success
*/
int UpdateAdvertiseData(void)
{
    int nError = 0; 
    nError = bt_le_ext_adv_stop(adv);

    do
    {
        if (nError) 
        {
            printk("Failed to stop advertising (err %d)\n", nError);
            break;
        }
        nError = bt_le_ext_adv_set_data(adv, ad, ARRAY_SIZE(ad), NULL, 0);
        
        if (nError) 
        {
            printk("Failed to set advertising data (err %d)\n", nError);
            break;
        }
    } while (0);

    return nError;
    
}

/**
 * @brief Getting advertising buffer 
 * @param None
 * @return address of advertising buffer
*/
uint8_t *GetAdvertisingBuffer()
{
    return ucAdVertsingBuffer;
}

bool BleStopAdvertise()
{
    int nError = 0;
    bool bRetVal = false;

    nError = bt_le_ext_adv_stop(adv);

 	if (!nError) 
    {
        bRetVal = true;
	}
    else
    {
		printk("Bluetooth init failed (err %d)\n", nError);
    }

    return bRetVal;
}