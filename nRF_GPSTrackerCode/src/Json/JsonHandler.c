/**
 * @file JsonHandler.c
 * @brief file containg functions for handling JSON
 * @author Adhil
 * @date  29-092023
 * @note
 */

/**************************************INCLUDES***************************/
#include "JsonHandler.h"
#include "nvs_flash.h"
#include <string.h>
/**************************************MACROS*****************************/

/**************************************TYPEDEFS***************************/

/***********************************FUNCTION DEFINITION*******************/




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
    cJSON *pcData = NULL;

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

            pcData = cJSON_AddArrayToObject(*pcJsonHandle, pcKey);

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
    cJSON *RxData = NULL;
    cJSON *root = NULL;
    
    if (pData && pckey && pucData)
    {
        if (pData[0])     //length check
        {
            printf("%s\n\r", (char *)pData+3); 
            root = cJSON_Parse(pData + 3); 
            
            if (root != NULL)
            {
                RxData = cJSON_GetObjectItem(root, pckey);
                if (RxData)
                {
                    *pucData = (RxData->valuedouble);
                    bRetVal = true;
                }
            }
            else
            {
                printk("ERR: parse failed\n\r");
            }

            cJSON_DeleteItemFromObject(RxData, pckey);
            cJSON_Delete(root);
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
    cJSON *RxData = NULL;
    cJSON *arrayItem = NULL;
    cJSON *root = NULL;
    int arraySize;

    if (pData && pckey && pucData)
    {
        root = cJSON_Parse(&pData[3]);

        if (root != NULL)
        {

            RxData = cJSON_GetObjectItem(root, pckey);

            if (RxData && cJSON_IsArray(RxData))
            {

                arraySize = cJSON_GetArraySize(RxData);

                for (int i = 0; i < arraySize; i++)
                {
                    arrayItem = cJSON_GetArrayItem(RxData, i);
                    if (arrayItem != NULL)
                    {
                        bRetVal = true;
                        memcpy(pucData, (arrayItem->valuestring), strlen(arrayItem->valuestring));

                        pucData = pucData + (strlen(arrayItem->valuestring));
                        *pucData = ',';
                        pucData++;
                    }
                    cJSON_DeleteItemFromArray(arrayItem, i);
                }
                
            }

            cJSON_DeleteItemFromObject(RxData, pckey);
            bRetVal = true;
        }
    }

    cJSON_Delete(root); // Free the cJSON structure
    return bRetVal;
}

