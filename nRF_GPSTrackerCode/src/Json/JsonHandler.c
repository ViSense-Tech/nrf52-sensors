/**
 * @file JsonHandler.c
 * @brief file containg functions for handling JSON
 * @author Adhil
 * @date  29-092023
 * @note
 */

/**************************************INCLUDES***************************/
#include "JsonHandler.h"
#include <string.h>
/**************************************MACROS*****************************/

/**************************************TYPEDEFS***************************/

/***********************************FUNCTION DEFINITION*******************/

 _sFenceData sFenceData[6] = {0};

/**
 * @brief  : Get Fence table
 * @param  : None
 * @return : Fence Table
*/
_sFenceData *GetFenceTable()
{
    return &sFenceData;
}

/**
 * @brief : Set Fence data table
 * @param : sFenceTable : Fence data table
 * @return : None
 * 
*/
void SetFenceTable(_sFenceData *sFenceTable)
{
    memcpy(&sFenceData, sFenceTable, sizeof(sFenceData));
}

/**
 * @brief function to add json object to json
 * @param pcJsonHandle - Json object handle
 * @param pcKey - Key name
 * @param pcValue - value
 * @param ucLen - value length
 * @return true or false
 */
bool AddItemtoJsonObject(cJSON **pcJsonHandle, _eJsonDataType JsondataType, const char *pcKey,
                         void *pcValue, uint8_t ucLen)
{
    uint8_t ucIndex = 0;

    bool bRetVal = false;

    if (*pcJsonHandle && pcKey && pcValue)
    {
        switch (JsondataType)
        {
        case FLOAT:
            cJSON_AddNumberToObject(*pcJsonHandle, pcKey, *((float *)(pcValue)));
            break;
        case NUMBER:
            cJSON_AddNumberToObject(*pcJsonHandle, pcKey, *((int *)(pcValue)));
            break;
        case STRING:
            cJSON_AddStringToObject(*pcJsonHandle, pcKey, (char *)pcValue);
            break;
        case OBJECT:
            break;
        case ARRAY:
            cJSON *pcData = NULL;
            pcData = cJSON_AddArrayToObject(*pcJsonHandle, "data");

            if (pcData)
            {
                for (ucIndex = 0; ucIndex < ucLen; ucIndex++)
                {
                    cJSON_AddItemToArray(pcData, cJSON_CreateNumber(*((uint16_t *)pcValue + ucIndex)));
                }
            }
            break;
        default:
            break;
        }
        bRetVal = true;
    }

    return bRetVal;
}

/**
 * @brief   : parse json data 
 * @param   : pData   : Receieved byte array
 *            pckey   : key value to parse
 *            ucLen   : length of data
 *            pucData : buffer to store parsed data
 * @return  : true for success
*/
bool ParseRxData(uint8_t *pData, const char *pckey, uint16_t ucLen, uint64_t *pucData)
{
    bool bRetVal = false;
    char cbuff[350] = {0}; /*We can write more than 247 bytes of data
                            if MTU size is adjusted, and in Tracker firmware
                            we have updated the MTU size to receive more than 247 bytes
                            configurations written via BLE is beyond 247bytes
                            updated the buff size to receive more than 247 bytes */
    cJSON *RxData = NULL;
    
    if (pData && pckey && pucData)
    {
        if (pData[0])     //length check
        {
            printf("%s\n\r", (char *)pData+3); 
            cJSON *root = cJSON_Parse(pData + 3); /*Updated index of buffer to 3 because we are receiving more
                                                    than 247 bytes to store length of payload we might require
                                                    2 bytes. So updated index of payload to 3. This change is only 
                                                    in Speed Tracker due to large config data size.*/
            if (root != NULL)
            {
                RxData = cJSON_GetObjectItem(root, pckey);
                if (RxData)
                {
                    *pucData = (RxData->valuedouble);
                    cJSON_Delete(root);
                    bRetVal = true;
                }
            }
            else
            {
                printk("ERR: parse failed\n\r");
            }
        }
    }
    return bRetVal;
}

/**
 * @brief   : parse json array
 * @param   : pData   : Receieved byte array
 *            pckey   : key value to parse
 *            ucLen   : length of data
 *            pucData : buffer to store parsed data
 * @return  : true for success
*/
bool ParseArray(uint8_t *pData, const char *pckey, uint16_t ucLen, char *pucData)
{
    bool bRetVal = false;
    char *cbuff = NULL;
    cJSON *RxData = NULL;
    int arraySize;

    if (pData && pckey)
    {

        cJSON *root = cJSON_Parse(pData + 3); /*See comment on line 115*/

        if (root != NULL)
        {
            RxData = cJSON_GetObjectItem(root, pckey);

            if (cJSON_IsArray(RxData))
            {
                arraySize = cJSON_GetArraySize(RxData);

                for (int i = 0; i < arraySize; i++)
                {
                    cJSON *arrayItem = cJSON_GetArrayItem(RxData, i);
                    if (arrayItem != NULL)
                    {
                        bRetVal = true;
                        memcpy(pucData, (arrayItem->valuestring), strlen(arrayItem->valuestring));

                        pucData = pucData + (strlen(arrayItem->valuestring));
                        *pucData = ',';
                        pucData++;

                    }
                }
            }

            bRetVal = true;
            cJSON_Delete(root); // Free the cJSON structure
        }
    }

    return bRetVal;
}

