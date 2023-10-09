
/**
* @file   
* @brief  Application related functions
* @author Adhil
* @date   09-10-2023
* @note
*/
#include "BleHandler.hpp"

#define MAX_COUNT_NUM (5)
#define AVERAGE_RSSI_VAL (-40)

// Dummy data in notification
uint8_t ucData[128] = {0x00, 0x01, 0x02, 0x03, 0x04};

void setup() 
{
  // put your setup code here, to run once:
    Serial.begin(115200);

    BleEnable();
    SetupScan();
    Serial.println("Scanning ...");
    SetupViseneService();
    // Set up and start advertising
    BleStartAdvertising();
}

void loop() 
{
  if (IsBleConnected())
  {
    BleSensorNotifydata(ucData, sizeof(ucData));
    ucData[2]++;
  }

  if (IsCentalConnected())
  {
    Serial.println("Central Role connected to Visense nRF");
  }
}
