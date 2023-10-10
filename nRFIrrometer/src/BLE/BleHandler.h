/**
 * @file BleHandler.h
 * @author 
 * @brief
 * @date 27-09-2023
 * @see BleHandler.c
*/
#ifndef _BLE_HANDLER_H
#define _BLE_HANDLER_H

/**************************************INCLUDES******************************/
#include <stdbool.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>

/***************************************MACROS*******************************/
#define ADV_BUFF_SIZE           (200)

/**************************************TYPEDEFS******************************/

/*************************************FUNCTION DECLARATION*******************/
bool EnableBLE();
uint8_t *GetAdvBuffer();
int InitExtAdv(void);
int StartAdv(void);
int UpdateAdvData(void);
// bool BleStopAdvertise();

#endif