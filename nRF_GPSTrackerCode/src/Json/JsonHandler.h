/**
 * @file JsonHandler.h
 * @brief file containg functions for handling JSON
 * @author Adhil
 * @date  29-092023
 * @note
*/

#ifndef _JSON_HANDLER_H
#define _JSON_HANDLER_H

/**************************************INCLUDES***************************/
#include <stdint.h>
#include <stdbool.h>
#include "cJSON.h"
/**************************************MACROS*****************************/

/**************************************TYPEDEFS***************************/
typedef enum __eJsonDataType
{
    FLOAT,
    NUMBER,
    STRING,
    ARRAY,
    OBJECT,
}_eJsonDataType;


typedef struct __sFenceData
{
    double dLatitude;
    double dLongitude;
}_sFenceData;

/***********************************FUNCTION DECLARATION******************/

bool AddItemtoJsonObject(cJSON **pcJsonHandle, _eJsonDataType JsondataType, const char *pcKey, 
                    void *pcValue, uint8_t ucLen);
bool ParseRxData(uint8_t *pData,const char *pckey, uint16_t ucLen, uint64_t *pucData);
bool ParseArray(uint8_t *pData,const char *pckey, uint16_t ucLen, char *pucData);


#endif