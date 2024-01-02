/**
 * @file BleService.c
 * @brief File containing Visense service related handling
 * @author
 * @see BleService.h
 * @date 27-09-2023
*/

/**************************** INCLUDES******************************************/
#include "BleService.h"
#include "JsonHandler.h"
#include "RtcHandler.h"
#include "nvs_flash.h"

/**************************** MACROS********************************************/
#define VND_MAX_LEN 247
/* Custom Service Variables */


/**************************** GLOBALS*******************************************/
static struct bt_uuid_128 sServiceUUID = BT_UUID_INIT_128(
	BT_UUID_CUSTOM_SERVICE_VAL);

static struct bt_uuid_128 sSensorChara = BT_UUID_INIT_128(
	BT_UUID_128_ENCODE(0xe0765908, 0x5d3b, 0x11ee, 0x8c99, 0x0242ac120002));

static struct bt_uuid_128 sConfigChara = BT_UUID_INIT_128(
	BT_UUID_128_ENCODE(0xe0765909, 0x5d3b, 0x11ee, 0x8c99, 0x0242ac120002));
static struct bt_uuid_128 sHistoryChara = BT_UUID_INIT_128(
	BT_UUID_128_ENCODE(0xe0766000, 0x5d3b, 0x11ee, 0x8c99, 0x0242ac120002));

static uint8_t ucSensorData[VND_MAX_LEN + 1] = {0x11,0x22,0x33, 0x44, 0x55};
static uint8_t ucConfigData2[VND_MAX_LEN + 1];
static bool bNotificationEnabled = false; 
static bool bConnected = false;
struct bt_conn *psConnHandle = NULL;
static bool hNotificationEnabled = false;
struct nvs_fs *FileSys;
static bool bConfigNotifyEnabled = false;
static bool bErased = false;
/*Read index from flash*/
uint32_t ulIdx = 0;



extern void SetPressureZero(uint32_t *ucbuffer);
extern void SetPressureMax(uint32_t *ucbuffer);
/****************************FUNCTION DEFINITION********************************/


/**
 * @brief Charcteristics Read callback
 * @param bt_conn - Connection handle
 * @param attr - GATT attributes
 * @param buf 
 * @param len 
 * @param offset
 * @return Length of the data read
*/
static ssize_t CharaRead(struct bt_conn *conn, const struct bt_gatt_attr *attr,
			void *buf, uint16_t len, uint16_t offset)
{
	const char *value = attr->user_data;

	return bt_gatt_attr_read(conn, attr, buf, len, offset, value,
				 strlen(value));
}

/**
 * @brief Charcteristics Write callback
 * @param bt_conn - Connection handle
 * @param attr - GATT attributes
 * @param buf 
 * @param len 
 * @param offset
 * @return Length of the data read
*/
static ssize_t CharaWrite(struct bt_conn *conn, const struct bt_gatt_attr *attr,
			 const void *buf, uint16_t len, uint16_t offset,
			 uint8_t flags)
{
	uint8_t *value = attr->user_data;
	uint32_t ucbuff = 0;

	if (offset + len > VND_MAX_LEN) {
		return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
	}

	memcpy(value + offset, buf, len);
	memcpy(ucConfigData2, value, len);

	if (ParseRxData(ucConfigData2, "PressureZero", len, &ucbuff))
	{
		if (len)
		{
			SetPressureZero(ucbuff);
		}
	}

	if (ParseRxData(ucConfigData2, "PressureMax", len, &ucbuff))
	{
		if (len)
	 	SetPressureMax(ucbuff);
	}

	if (ParseRxData(ucConfigData2, "TS", len, &ucbuff))
	{
		if (len)
		{
			SetRtcTime(ucbuff);
			printk("time:%lld\n\r",ucbuff);
		}
	}
	if(ParseRxData(ucConfigData2, "Sleep", len, &ucbuff))
	{
		if(len)
		{
			SetSleepTime(ucbuff);
			printk("sleep:%d\n\r",ucbuff);
		}
	}
	if (ParseRxData(ucConfigData2, "PressureMin", len, &ucbuff))
	{
		if (len)
		{
			SetPressureMin(ucbuff);
			printk("Pressure minimum:%d\n\r",ucbuff);
		}
	}
	
	return len;
}

/**
 * @brief Notification callback
 * @param attr - pointer to GATT attributes
 * @param value - Client Characteristic Configuration Values
 * @return None
*/
void BleSensorDataNotify(const struct bt_gatt_attr *attr, uint16_t value)
{
    if (value == BT_GATT_CCC_NOTIFY)
    {
        bNotificationEnabled = true;
    }
    else
    {
        bNotificationEnabled = false;
    }
}

uint8_t *GetConfigBuffer()
{
	return &ucConfigData2;
}

/**
 * @brief Notification callback for history
 * @param attr - pointer to GATT attributes
 * @param value - Client Characteristic Configuration Values
 * @return None
*/
void BleHistoryDataNotify(const struct bt_gatt_attr *attr, uint16_t value)
{
    if (value == BT_GATT_CCC_NOTIFY)
    {
        hNotificationEnabled = true;
    }
    
}
/**
 * @brief Notification callback for configuration
 * @param attr - pointer to GATT attributes
 * @param value - Client Characteristic Configuration Values
 * @return None
*/
void BleConfigDataNotify(const struct bt_gatt_attr *attr, uint16_t value)
{
	if (value == BT_GATT_CCC_NOTIFY)
	{
		bConfigNotifyEnabled = true;
	}
	
}

/* VSENCE SERVICE DEFINITION*/
/**
 * @note Service registration and chara adding.
 * @paragraph Below service has one chara with a notify permission.
*/
BT_GATT_SERVICE_DEFINE(VisenseService,
    BT_GATT_PRIMARY_SERVICE(&sServiceUUID),
    BT_GATT_CHARACTERISTIC(&sSensorChara.uuid,
                BT_GATT_CHRC_NOTIFY,
                BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
                CharaRead, CharaWrite, ucSensorData),
	BT_GATT_CCC(BleSensorDataNotify, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
	BT_GATT_CHARACTERISTIC(&sConfigChara.uuid,
					BT_GATT_CHRC_READ | BT_GATT_CHRC_WRITE,
						BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
						CharaRead,CharaWrite,ucConfigData2),
   BT_GATT_CCC(BleConfigDataNotify, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
   BT_GATT_CHARACTERISTIC(&sHistoryChara.uuid,
                BT_GATT_CHRC_NOTIFY ,
                BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
                CharaRead, CharaWrite, ucSensorData),
   BT_GATT_CCC(BleHistoryDataNotify, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE)
);

/**
 * @brief Set file pointer
 * @param fs : file pointer structure
 * @return None
*/
void SetFileSystem(struct nvs_fs *fs)
{
	FileSys = fs;
}

/**
 * @brief Connect callabcak
*/
static void connected(struct bt_conn *conn, uint8_t err)
{

	if (err) 
    {
		printk("Connection failed (err 0x%02x)\n", err);
	} 
    else 
    {
		bt_conn_le_data_len_update(conn, BT_LE_DATA_LEN_PARAM_MAX);
		bConnected = true;
	}
}

/**
 * @brief Disconnect callback
*/
static void disconnected(struct bt_conn *conn, uint8_t reason)
{
	bConnected = false;
	printk("Disconnected (reason 0x%02x)\n", reason);
}

/**
 * @note Callback definitions for connection
*/
BT_CONN_CB_DEFINE(conn_callbacks) = {
	.connected = connected,
	.disconnected = disconnected,
};
/**
 * @brief Sending Config data as notification
 * @param pucConfigData - Data to notify
 * @param unLen - Length of data to notify
 * @return 0 in case of success or negative value in case of error
*/
int VisenseConfigDataNotify(uint8_t *pucCongigData, uint16_t unLen)
{
	int RetVal = 0;
	if(pucCongigData)
	{
		RetVal = bt_gatt_notify(NULL, &VisenseService.attrs[5],
								pucCongigData, unLen);
	}
	return RetVal;
}

/**
 * @brief Sending sensor data as notification
 * @param pucSensorData - Data to notify
 * @param unLen - length of data to notify
 * @return 0 in case of success or negative value in case of error
*/
int VisenseSensordataNotify(uint8_t *pucSensorData, uint16_t unLen)
{
	int nRetVal = 0;

    if (pucSensorData)
    {
	    nRetVal = bt_gatt_notify(NULL, &VisenseService.attrs[1], 
                                pucSensorData, unLen);
    }

	return nRetVal;
}

/**
 * @brief 	History data notification 
 * @param 	len : length of data
 * @return 	true for success
*/
bool VisenseHistoryDataNotify(uint32_t ulWritePos)  //history
{
	bool bRetVal = false;
	bool bFullDataRead = false;
	char NotifyBuf[NOTIFY_BUFFER_SIZE];
	int nRetVal = 0;
	uint32_t uFlashCounter = 0;
	if (ulIdx > ulWritePos)
	{
		uFlashCounter = ulIdx - ulWritePos;
	}

	do
	{	
		if (!IsConnected())
		{			
			bErased = false;
			break;
		}
		
		memset(NotifyBuf, '\0', NOTIFY_BUFFER_SIZE);
		nRetVal = readJsonFromExternalFlash(NotifyBuf, ulIdx, WRITE_ALIGNMENT);
		printk("\nId: %d, Ble_Stored_Data: %s\n",ulIdx, NotifyBuf);
		if (NotifyBuf[0] != 0x7B)
		{
			bFullDataRead = true;
			break;
		}
		k_msleep(100);

		if (nRetVal)
		{
			nRetVal = bt_gatt_notify(NULL, &VisenseService.attrs[8], 
			NotifyBuf, strlen(NotifyBuf));
			if (nRetVal < 0)
			{
				printk("Notification failed%d\n\r",nRetVal);
			}
			
		}
		ulIdx++;
		uFlashCounter++;
		if (ulIdx == NUMBER_OF_ENTRIES)
		{
			ulIdx = 0;
		}
		if (uFlashCounter > NUMBER_OF_ENTRIES )
		{
			bFullDataRead = true;
			break;	
		}
		
		
		// bRetVal = true;
	} while(0);
	
	//hNotificationEnabled = false;     //history callback set 
	if (bFullDataRead == true) 
	{
		if (bErased)
		{
			if(!EraseExternalFlash(SECTOR_COUNT))
			{
				printk("Flash erase failed!\n");
				return bRetVal;
			}
			printk("Flash Cleared");
		}

		ulIdx = 0;
		bRetVal = true;
	}
	
	return bRetVal;
}

/**
 * @brief Check if history notification is enabled
 * @param None
 * @return notification status
*/
bool IshistoryNotificationenabled()
{
    return hNotificationEnabled;
}

/**
 * @brief Check if notification is enabled
 * @param None
 * @return returns if notifications is enabled or not.
*/
bool IsNotificationenabled()
{
    return bNotificationEnabled;
}

bool IsConfigNotifyEnabled()
{
	return bConfigNotifyEnabled;
}
/**
 * @brief Check if the device connected
 * @param None
 * @return returns the device is connected or not
*/
bool IsConnected()
{
	return bConnected;
}