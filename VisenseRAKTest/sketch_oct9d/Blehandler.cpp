/**
* @file   BleHandler.c
* @brief  Ble related functions handled here
* @author Adhil
* @date   09-10-2023
* @note
*/



/**************************************INCLUDES**************************************/
#include "BleHandler.hpp"


/************************************MACROS*****************************************/


/************************************GLOBALS****************************************/
//AdafruitBluefruit Bluefruit = AdafruitBluefruit();

static const uint8_t ucServiceUUid[] = {0x02, 0x00, 0x12, 0xac, 0x42, 0x02, 0x99, 0x8c, 0xee, 0x11, 0x74, 0x66, 0x10, 0xcd, 0xc5, 0x73};
static const uint8_t ucCharaUUid[] = {0x02, 0x00, 0x12, 0xac, 0x42, 0x02, 0x99, 0x8c, 0xee, 0x11, 0x74, 0x66, 0x12, 0xd0, 0xc5, 0x73};

BLEUuid ServiceUUID = BLEUuid(ucServiceUUid);
BLEUuid CharaUUID = BLEUuid(ucCharaUUid);

BLEService        VisenseService = BLEService(ServiceUUID);
BLECharacteristic VisenseSensor = BLECharacteristic(CharaUUID);

int32_t g_count = 0;
int32_t g_rssi = 0;
static bool bConnected = false;
static bool bCentalConnected = false;

/***********************************FUNCTION DEFINITION****************************/
static void ble_scan_callback(ble_gap_evt_adv_report_t *report);

static void PeripheralConnectCallback(uint16_t unConnHandle)
{
  bConnected = true;
}

static void PeripheralDisconnectcallback(uint16_t unConnHandle, uint8_t reason)
{
  bConnected = false;
}

static void CentralConnectCallback(uint16_t unConnhandle)
{
  bCentalConnected = true;
}

static void CentralDisconnectCallabck(uint16_t unConnHandle, uint8_t reason)
{
  bCentalConnected = false;
}

bool IsBleConnected()
{
  return bConnected;
}

bool IsCentalConnected()
{
  return bCentalConnected;
}

static void cccd_callback(uint16_t conn_hdl, BLECharacteristic* chr, uint16_t cccd_value)
{
    // Display the raw request packet
    Serial.print("CCCD Updated: ");
    //Serial.printBuffer(request->data, request->len);
    Serial.print(cccd_value);
    Serial.println("");

    // Check the characteristic this CCCD update is associated with in case
    // this handler is used for multiple CCCD records.
    if (chr->uuid == VisenseSensor.uuid) {
        if (chr->notifyEnabled(conn_hdl)) {
            Serial.println("Heart Rate Measurement 'Notify' enabled");
        } else {
            Serial.println("Heart Rate Measurement 'Notify' disabled");
        }
    }
}

/**
 * @brief  when the Bluetooth node scans that there is a Bluetooth broadcast with the prefix of ‘rak4630-’ around
 * and the RSSI of the Bluetooth broadcast is less than the set threshold value,
 * the light is on. On the contrary, the light is off.
 */
void ble_scan_callback(ble_gap_evt_adv_report_t *report)
{
    uint8_t len = 0;
    uint8_t buffer[32];
    char cBuffer[128];
    memset(buffer, 0, sizeof(buffer));

    /* Check for UUID128 Complete List */
   
    len = Bluefruit.Scanner.parseReportByType(report, BLE_GAP_AD_TYPE_COMPLETE_LOCAL_NAME, buffer, sizeof(buffer));
     Serial.println("Device found");
     //memcpy(cBuffer, report->data.p_data, report->data.len);
     // Serial.println(cBuffer);
     Serial.println((char*)buffer);
     //Serial.println(cBuffer);
    if (strncmp((char *)buffer, "VISENSE_TEST", strlen("VISENSE_TEST")) == 0)
    {
       // g_count++;
       // g_rssi += report->rssi;
        Serial.println("adv name matched");
        Serial.println((char *)buffer);
        Bluefruit.Central.connect(report);
        // if (g_count == MAX_COUNT_NUM)
        // {
        //     Serial.printf("===rssi: %d===\n", g_rssi / MAX_COUNT_NUM);
        //     if ((g_rssi / MAX_COUNT_NUM) >= AVERAGE_RSSI_VAL)
        //     {
        //         digitalWrite(LED_BUILTIN, HIGH);
        //     }
        //     else
        //     {
        //         digitalWrite(LED_BUILTIN, LOW);
        //     }
        //     g_count = 0;
        //     g_rssi = 0;
        // }
    }

    // For Softdevice v6: after received a report, scanner will be paused
    // We need to call Scanner resume() to continue scanning
    Bluefruit.Scanner.resume();
}

/**
* @brief  Visense service setup
* @param  None
* @return None
*/
void SetupViseneService(void)
{
  VisenseService.begin();
  VisenseSensor.setProperties(CHR_PROPS_NOTIFY);
  VisenseSensor.setPermission(SECMODE_OPEN, SECMODE_NO_ACCESS);
  VisenseSensor.setFixedLen(247);
  VisenseSensor.setCccdWriteCallback(cccd_callback);  // Optionally capture CCCD updates
  VisenseSensor.begin();
  uint8_t hrmdata[2] = { 0x20, 0x40 }; // Set the characteristic to use 8-bit values, with the sensor connected and detected
  VisenseSensor.write(hrmdata, 2);
}


/**
* @brief  Enable BLE device
* @param  None
* @return true for success
*/
bool BleEnable()
{
  uint8_t mac[6] = {0};
  char deviceName[16] = {0};
  bool bRetVal = true;
      // Initialize Bluefruit with max concurrent connections as Peripheral = 1, Central = 1
    // SRAM usage required by SoftDevice will increase with number of connections
  Bluefruit.begin(1, 1);
  Bluefruit.setTxPower(4); // Check bluefruit.h for supported values
  Bluefruit.getAddr(mac);
  
  sprintf(deviceName, "RAK4630-%2X%2X%2X", mac[0], mac[1], mac[2]);
  Bluefruit.setName(deviceName);
  return bRetVal;
}

/**
* @brief  Setup scanner in BLE
* @param  None
* @return true for success
*/
bool SetupScan()
{
    /* Start Central Scanning
  * - Enable auto scan if disconnected
  * - Interval = 100 ms, window = 80 ms
  * - Filter only accept bleuart service
  * - Don't use active scan
  * - Start(timeout) with timeout = 0 will scan forever (until connected)
  */
  // Bluefruit.Central.setConnectCallback(CentralConnectCallback);
  // Bluefruit.Central.setDisconnectCallback(CentralDisconnectCallabck);
  Bluefruit.Scanner.setRxCallback(ble_scan_callback);
 // Bluefruit.Scanner.checkReportForService()
  Bluefruit.Scanner.restartOnDisconnect(true);
  //Bluefruit.Scanner.filterRssi(-80);      // Only invoke callback for devices with RSSI >= -80 dBm
  Bluefruit.Scanner.setInterval(160, 80); // in units of 0.625 ms
  Bluefruit.Scanner.useActiveScan(true);  // Request scan response data
  Bluefruit.Scanner.start(0);             // 0 = Don't stop scanning after n seconds

  return true;
}

/**
   @brief start BLE advertisement
*/
void BleStartAdvertising(void)
{
    // Advertising packet
    Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
    Bluefruit.Advertising.addTxPower();
    
    Bluefruit.Advertising.addName();
    Bluefruit.Advertising.addService(VisenseService);
    /* Start Advertising
    * - Enable auto advertising if disconnected
    * - Interval:  fast mode = 20 ms, slow mode = 152.5 ms
    * - Timeout for fast mode is 30 seconds
    * - Start(timeout) with timeout = 0 will advertise forever (until connected)
    *
    * For recommended advertising interval
    * https://developer.apple.com/library/content/qa/qa1931/_index.html
    */

    Bluefruit.Periph.setConnectCallback(PeripheralConnectCallback);
    Bluefruit.Periph.setDisconnectCallback(PeripheralDisconnectcallback);

    Bluefruit.Advertising.restartOnDisconnect(true);
    Bluefruit.Advertising.setInterval(32, 244); // in unit of 0.625 ms
    Bluefruit.Advertising.setFastTimeout(30);   // number of seconds in fast mode
    Bluefruit.Advertising.start(0);             // 0 = Don't stop advertising after n seconds
}

bool BleSensorNotifydata(uint8_t *pucBuffer, uint16_t unLength)
{
  bool bRetVal = false;

  if (pucBuffer)
  {
   if (VisenseSensor.notify(pucBuffer, unLength))
   {
      bRetVal = true;
   }
  }

  return bRetVal;
}

