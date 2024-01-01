
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
/* Custom Service Variables */
#define VND_MAX_LEN 300  /*We can write more than 247 bytes of data
                            if MTU size is adjusted, and in Tracker firmware
                            we have updated the MTU size to receive more than 247 bytes
                            configurations written via BLE is beyond 247bytes
                            updated the buff size to receive more than 247 bytes */


/**************************** GLOBALS*******************************************/
static struct bt_uuid_128 sServiceUUID = BT_UUID_INIT_128(
	BT_UUID_CUSTOM_SERVICE_VAL);

static struct bt_uuid_128 sSensorChara = BT_UUID_INIT_128(
	BT_UUID_128_ENCODE(0x1f1e5e42, 0x98ad, 0x11ee, 0xb9d1, 0x0242ac120002));

static struct bt_uuid_128 sConfigChara = BT_UUID_INIT_128(
	BT_UUID_128_ENCODE(0x1f1e5f96, 0x98ad, 0x11ee, 0xb9d1, 0x0242ac120002));
static struct bt_uuid_128 sHistoryChara = BT_UUID_INIT_128(
	BT_UUID_128_ENCODE(0x1f1e60b8, 0x98ad, 0x11ee, 0xb9d1, 0x0242ac120002));

static uint8_t ucSensorData[VND_MAX_LEN + 1] = {0x11, 0x22, 0x33, 0x44, 0x55};
static uint8_t ucConfigData[VND_MAX_LEN + 1];
static bool bNotificationEnabled = false;
static bool bConnected = false;
struct bt_conn *psConnHandle = NULL;
static bool hNotificationEnabled = false;
struct nvs_fs *FileSys;
static bool bConfigNotifyEnabled = false;
static bool bFenceStatus = false;
// static int ucCoordCount;
static bool bConfig = false;
static bool bErased = false; 
static uint16_t usPayloadLen = 0;

/*Read index from flash*/
uint32_t ucIdx = 0;
bool bFenceLat = false;
bool bFenceLon = false;

/****************************FUNCTION DECLARATION********************************/
static void ParseFenceCoordinate(char *pcKey);

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
 * @brief Parse latitudes and longitudes array from JSON payload
 * @param pcKey : key specifying lat or lon
 * @return None
*/
static void ParseFenceCoordinate(char *pcKey)
{
	char *cSplitStr = NULL;
	char ucbuff[300];
	double dLat = 0.0;
	uint8_t ucIdx = 0;

	_sConfigData *psConfigData = NULL;
	/*parsing array of strings */
	psConfigData = GetConfigData();

	if (!psConfigData)
	{
		printk("ERR: Got invalid configuration\n\r");
		return;
	}

	if (ParseArray(ucConfigData, pcKey, usPayloadLen, ucbuff)) // for lattitude
	{
		printk("INFO: Parsing coordinate success\n\r");
	}

	ucIdx = 0;

	if (0 == strcmp(pcKey, "lat"))
	{
		cSplitStr = strtok(ucbuff, ",");
		while (cSplitStr != NULL)
		{
			dLat = atof(cSplitStr);
			memcpy(&psConfigData->FenceData[ucIdx].dLatitude, &dLat, sizeof(double));
			ucIdx++;
			cSplitStr = strtok(NULL, ",");
		}

		bFenceLat = true;                 //lat array parse sucess flag
	}
	else if (0 == strcmp(pcKey, "lon"))
	{
		cSplitStr = strtok(ucbuff, ",");

		while (cSplitStr != NULL)
		{
			dLat = atof(cSplitStr);
			memcpy(&psConfigData->FenceData[ucIdx].dLongitude, &dLat, sizeof(double));
			ucIdx++;
			cSplitStr = strtok(NULL, ",");
		}

		bFenceLon = true;		
	}

	printk("Fence update success\n\r");
}

/**
 * @brief Parse latitudes and longitudes for fence table
 * @param None
 * @return None
*/
void ParseFenceData()
{
	ParseFenceCoordinate("lat");
	k_msleep(100);
	ParseFenceCoordinate("lon");
	printk("INFO: All fence data parsed\n\r");
}

/**
 * @brief Parsing received data
 * @param None
 * @return None
*/
void ParseRcvdData()
{
	uint32_t ucbuff2;
	usPayloadLen = ucConfigData[1] << 8 | ucConfigData[2];
	
	if (ParseRxData(ucConfigData, "cc", usPayloadLen, &ucbuff2))
	{
	
		printk("cc:%d\n\r", ucbuff2);
		SetFenceCoordCount(ucbuff2);
	}
	else
	{
		printk("failed read cc\n");
	}

	/*SoG value max threshold */

	if (ParseRxData(ucConfigData, "Speed", usPayloadLen, &ucbuff2))
	{
		SetSogMax(ucbuff2);
		printk("smax:%d\n\r", ucbuff2);
	}
	else
	{
		printk("failed read smax\n");
	}
	/*timestamp */
	if (ParseRxData(ucConfigData, "TS", usPayloadLen, &ucbuff2))
	{
		SetRtcTime(ucbuff2);
		printk("ts:%d\n\r", ucbuff2);
	}
	else
	{
		printk("failed read ts\n");
	}

	/*sleeptime */

	if (ParseRxData(ucConfigData, "Sleep", usPayloadLen, &ucbuff2))
	{
		SetSleepTime(ucbuff2);
		printk("sleep:%d\n\r", ucbuff2);
	}
	else
	{
		printk("failed read ts\n");
	}
}

/**
 * @brief Setting Config Status 
 * @param bStatus : Config set status
 * @return None
*/
void SetConfigStatus(bool bStatus)
{
	bConfig = bStatus;
	if (!bConfig)
	{
		memset(ucConfigData, 0, sizeof(ucConfigData));
	}
	else
	{
		printk("INFO:Config Set\n\r");
	}
}

bool GetConfigStatus()
{
	return bConfig;
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
	printk("INFO:Offset = %d\n\r", offset);

	if (offset + len > VND_MAX_LEN)
	{

		return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
	}

	memcpy(ucConfigData, buf, len);
	SetConfigStatus(true);

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
											  CharaRead, CharaWrite, ucSensorData),
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
 * @brief MTU exchange callback
 * @param conn 	  : Connection handle
 * @param att_err : Error code on MTU exchange
 * @param params  : Exchange params
 * @return None
*/
static void MTUExchangeCb(struct bt_conn *conn, uint8_t att_err,
    					struct bt_gatt_exchange_params *params)
{
    if (att_err)
    {
        printk("\n\rERR:MTU exchange returned with error code %d\n\r", att_err);
    }
    else
    {
        printk("\n\rINFO:MTU sucessfully set to %d\n\r", CONFIG_BT_L2CAP_TX_MTU);
    }
}

/**
 * @brief Initiate MTU exchange from peripheral side
 * @param conn  : connection handle
 * @return None
*/
static void InitiateMTUExcahnge(struct bt_conn *conn)
{
    int err;
    static struct bt_gatt_exchange_params exchange_params;
    exchange_params.func = MTUExchangeCb;

    err = bt_gatt_exchange_mtu(conn, &exchange_params);
    if (err)
    {
        printk("\n\rERR:MTU exchange failed (err %d)\n\r", err);
    }
    else
    {
        printk("\n\rINFO:MTU exchange pending ...\n\r");
    }
}

/**
 * @brief Connect callabcak
 * @param conn : Connection handle
 * @param err  : error code/return code on connection
 * @return None
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

	InitiateMTUExcahnge(conn);
}

/**
 * @brief Disconnect callback
 * @param conn   : Connection handle
 * @param reason : return code on disconnection
 * @return None
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
	uint32_t uFlashCounter = 0;

	if (ucIdx > ulWritePos)
	{
		uFlashCounter = ucIdx - ulWritePos;
	}

	do
	{	
		if (!IsConnected())
		{
			bErased = false;
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
		
	} while (0);
	
	if (bFullDataRead == true ) 
	{
		if (!bErased)
		{
			if(!EraseExternalFlash(SECTOR_COUNT))
			{
				printk("Flash erase Failed");
			}
			else
			{
				bErased = true;
			}
			printk("Flash Cleared");
		}


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

/**
 * @brief Setting coordinate count
 * @param ucCount : Coordinate count
 * @return None
*/
void SetFenceCoordCount(int ucCount)
{
	_sConfigData *psConfigData = NULL;

	psConfigData = GetConfigData();

	if (psConfigData)
	{
		psConfigData->nCoordCount = ucCount;
	}
}

/**
 * @brief Get coordinate count
 * @param None
 * @return Fence coordinate count
*/
int GetCoordCount()
{
	_sConfigData *psConfigData = NULL;
	int nCoordCount = 0;

	psConfigData = GetConfigData();

	if (psConfigData)
	{
		nCoordCount = psConfigData->nCoordCount;
	}
	else
	{
		printk("ERR: Getting  coord count from config failed\n\r");
	}
	
	return nCoordCount;
}