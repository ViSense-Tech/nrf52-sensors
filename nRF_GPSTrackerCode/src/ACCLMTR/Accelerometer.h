/**
 * @file    Accelerometer.h
 * @brief   Accelerometer related functions are handled here
 * @author  Adhil
 * @date    17-10-2023
 * @see     Accelerometer.c
*/
#ifndef _ACCELEROMETER_H
#define _ACCELEROMETER_H

/***************************INCLUDES*********************************/
#include <stdint.h>
#include <stdbool.h>

/***************************MACROS**********************************/
#define ACCLMTR_DEV_ADDR            0x53
#define ACCLMTR_POWER_CTL_REG       0x2D
#define ACCLMTR_DATA_FORMAT_REG     0x31
#define ACCLMTR_DATAX0_REG          0x32
/***************************TYPEDEFS********************************/
typedef struct __sAcclData
{
    uint16_t unAccX;
    uint16_t unAccY;
    uint16_t unAccZ;
}_sAcclData;

/***************************FUNCTION DECLARATION*********************/
bool InitAcclerometer();
bool ReadFromAccelerometer(_sAcclData *psAcclData);

#endif

//EOF