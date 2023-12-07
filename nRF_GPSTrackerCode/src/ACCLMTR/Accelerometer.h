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
#define ACCLMTR_DATAY0_REG          0x34
#define ACCLMTR_DATAZ0_REG          0x36
#define ACCLMTR_READ_FAILED         (1 << 2)
#define ACCLMTR_READ_OK             ~(1 << 2)
/***************************TYPEDEFS********************************/
typedef struct __sAcclData
{
    uint32_t unAccX;
    uint32_t unAccY;
    uint32_t unAccZ;
}_sAcclData;

/***************************FUNCTION DECLARATION*********************/
bool InitAcclerometer();
bool ReadFromAccelerometer(_sAcclData *psAcclData);

#endif

//EOF