
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
#include "GPSHandler.h"
#include <stdio.h>
#include <stdlib.h>
#include "SystemHandler.h"
#include "nvs_flash.h"
#include "RtcHandler.h"

/**************************** MACROS********************************************/
#define VND_MAX_LEN 300
/* Custom Service Variables */
#define BT_UUID_CUSTOM_SERVICE_VAL \
	BT_UUID_128_ENCODE(0xe076567e, 0x5d3b, 0x11ee, 0x8c99, 0x0242ac120002)

/**************************** GLOBALS*******************************************/
static struct bt_uuid_128 sServiceUUID = BT_UUID_INIT_128(
	BT_UUID_CUSTOM_SERVICE_VAL);

static struct bt_uuid_128 sSensorChara = BT_UUID_INIT_128(
	BT_UUID_128_ENCODE(0xe0765908, 0x5d3b, 0x11ee, 0x8c99, 0x0242ac120002));

static struct bt_uuid_128 sConfigChara = BT_UUID_INIT_128(
	BT_UUID_128_ENCODE(0xe0765909, 0x5d3b, 0x11ee, 0x8c99, 0x0242ac120002));
static struct bt_uuid_128 sHistoryChara = BT_UUID_INIT_128(
	BT_UUID_128_ENCODE(0xe0766000, 0x5d3b, 0x11ee, 0x8c99, 0x0242ac120002));

static uint8_t ucSensorData[VND_MAX_LEN + 1] = {0x11, 0x22, 0x33, 0x44, 0x55};
static uint8_t ucConfigData2[VND_MAX_LEN + 1];
static bool bNotificationEnabled = false;
static bool bConnected = false;
struct bt_conn *psConnHandle = NULL;
static bool hNotificationEnabled = false;
struct nvs_fs *FileSys;
static bool bConfigNotifyEnabled = false;
static bool bFenceStatus = false;
/*Read index from flash*/
uint8_t ucIdx = 0;
bool bFenceLat = false;
bool bFenceLon = false;



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
	char ucbuff[1024];
	_sFenceData *psFenceData = NULL;
	uint32_t ucbuff2;
	double dBuf = 0.0;
	uint16_t uPayloadLen = 0;
	uint8_t ucIdx = 0;
	char *cSplitStr = NULL;

	static uint8_t coordcount;
	double latitudeArray[4];

	if (offset + len > VND_MAX_LEN)
	{

		return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
	}

	memcpy(value + offset, buf, len);

	memcpy(ucConfigData2, value, len);
	uPayloadLen = ucConfigData2[1];
	printk("Written Data: %s\n\r", (char *)value);
	printk("len%d\n", len);
	printk("payl%d\n", uPayloadLen);
	memset(ucbuff, 0, 150);

	/*coordinate count*/

	if (ParseRxData(ucConfigData2, "cc", len, &ucbuff2))
	{
		if (len)
		{
			printk("..cc:%d\n\r", ucbuff2);
			
		}
	}
	else
	{
		printk("failed read cc\n");
	}

	/*SoG value max threshold */

	if (ParseRxData(ucConfigData2, "Speed", len, &ucbuff2))
	{
		if (len)
		{
			SetSogMax(ucbuff2);
			printk("..smax:%d\n\r", ucbuff2);
		
		}
	}
	else
	{
		printk("failed read smax\n");
	}
	/*timestamp */
	if (ParseRxData(ucConfigData2, "TS", len, &ucbuff2))
	{
		if (len)
		{
			SetRtcTime(ucbuff2);
			printk("..ts:%d\n\r", ucbuff2);
		}
	}
	else
	{
		printk("failed read ts\n");
	}

	/*sleeptime */

	if (ParseRxData(ucConfigData2, "Sleep", len, &ucbuff2))
	{
		if (len)
		{
			SetSleepTime(ucbuff2);
			printk(".st:%d\n\r", ucbuff2);
		}
	}
	else
	{
		printk("failed read ts\n");
	}

	/*parsing array of strings */
	if (ParseArray(ucConfigData2, "lat", len, ucbuff)) // for lattitude
	{
		printk("ParseArray\n");
		printk("\n\rlat: %s", ucbuff);
		psFenceData = GetFenceTable();
		cSplitStr = strtok(ucbuff, ",");
		while (cSplitStr != NULL)
		{
			psFenceData->dLatitude = atof(cSplitStr);
			psFenceData++;
			cSplitStr = strtok(NULL, ",");
		}

		bFenceLat = true;                 //lat array parse sucess flag
	}
	else
	{
		printk("Failed to read lt\n");
	}

	if (ParseArray(ucConfigData2, "lon", len, ucbuff)) // for longitude
	{
		printk("ParseArray\n");
		printk("\n\rlon: %s", ucbuff);
		psFenceData = GetFenceTable(); //!
		cSplitStr = strtok(ucbuff, ",");
		while (cSplitStr != NULL)
		{

			psFenceData->dLongitude = atof(cSplitStr);
			psFenceData++;
			cSplitStr = strtok(NULL, ",");
		}
		bFenceLon = true;
	}

	if (bFenceLat && bFenceLon)
	{
		bFenceStatus = true;
	}

	psFenceData = GetFenceTable();
	for (ucIdx = 0; ucIdx < 4; ucIdx++)
	{
		printk("Lat[%d]: %lf Lon[%d]: %lf\n\r", ucIdx, psFenceData->dLatitude, ucIdx, psFenceData->dLongitude);
		psFenceData++;
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
											  BT_GATT_CHRC_NOTIFY | BT_GATT_CHRC_WRITE,
											  BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
											  CharaRead, CharaWrite, ucConfigData2),
					   BT_GATT_CCC(BleConfigDataNotify, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
					   BT_GATT_CHARACTERISTIC(&sHistoryChara.uuid,
											  BT_GATT_CHRC_NOTIFY,
											  BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
											  CharaRead, CharaWrite, ucSensorData),
					   BT_GATT_CCC(BleHistoryDataNotify, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE));

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
	if (pucCongigData)
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
bool IsConfigLat()
{
	return bFenceLat;
}
bool IsConfigLon()
{
	return bFenceLon;
}
//#if 0
/**
 * @brief 	History data notification 
 * @param 	len : length of data
 * @return 	true for success
*/
bool VisenseHistoryDataNotify(uint32_t ulWritePos)  //history
{
	bool bRetVal = false;
	bool bFullDataRead = false;
	char NotifyBuf[WRITE_ALIGNMENT];
	int nRetVal = 0;
	int uReadCount = 0;
	uint8_t uFlashCounter = 0;
	if (ucIdx > ulWritePos)
	{
		uFlashCounter = ucIdx - ulWritePos;
	}

	while(ucIdx <= NUMBER_OF_ENTRIES)
	{	
		if (!IsConnected())
		{
			break;
		}
		
		memset(NotifyBuf, 0, WRITE_ALIGNMENT);
		uReadCount = readJsonFromExternalFlash(NotifyBuf, ucIdx, WRITE_ALIGNMENT);
		printk("\nId: %d, Ble_Stored_Data: %s\n",ucIdx, NotifyBuf);

		if (NotifyBuf[0] != 0x7B)
		{
			bFullDataRead = true;
			break;
		}
		
		k_msleep(100);

		if (1)
		{
			nRetVal = bt_gatt_notify(NULL, &VisenseService.attrs[8], 
			NotifyBuf,256);
			if (nRetVal < 0)
			{
				printk("Notification failed%d\n\r",nRetVal);
			}
			
		}
		ucIdx++;
		uFlashCounter++;
		if (ucIdx == NUMBER_OF_ENTRIES)
		{
			ucIdx = 0;
		}
		if (uFlashCounter > NUMBER_OF_ENTRIES )
		{
			bFullDataRead = true;
			break;	
		}
		
	}
	
	hNotificationEnabled = false;     //history callback set 
	if (bFullDataRead == true) 
	{
		if(!EraseExternalFlash(SECTOR_COUNT))
		{
			printk("Flash erase Failed");
		}
		printk("Flash Cleared");
		ucIdx = 0;
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

/**
 * @brief  : Check config chara notification enabled
 * @param  : None
 * @return : notification stataus
*/
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

/**
 * @brief  : Fence coordinate set status
 * @param  : status : fence latitudes set status
 * @return : None
*/
void SetConfigChangeLat(bool status)
{
	bFenceLat = status;
}

/**
 * @brief  : Fence coordinate set status
 * @param  : status : fence longitudes set status
 * @return : None
*/
void SetConfigChangeLon(bool status)
{
	bFenceLon = status;
}

/**
 * @brief check if fence is configured
 * @param none
 * @return bFenceStatus : true if configured false for else
*/
bool IsFenceConfigured()
{
    return bFenceStatus;
}
/**
 * @brief Set Fence config status
 * @param bStatus : fence set status
 * @return None
*/
void SetFenceConfigStatus(bool bStatus)
{
    bFenceStatus = bStatus;
}