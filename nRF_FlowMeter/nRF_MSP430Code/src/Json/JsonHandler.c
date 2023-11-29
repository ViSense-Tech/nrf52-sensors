/**
 * @file JsonHandler.c
 * @brief file containg functions for handling JSON
 * @author Adhil
 * @date  29-092023
 * @note
*/


/**************************************INCLUDES***************************/
#include "JsonHandler.h"
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

    bool bRetVal = false;

    if (*pcJsonHandle && pcKey && pcValue)
    {
        switch(JsondataType)
        {
            case NUMBER_INT: 
                         cJSON_AddNumberToObject(*pcJsonHandle, pcKey, *((uint32_t*)(pcValue)));
                         break;
            case NUMBER_FLOAT: 
                         cJSON_AddNumberToObject(*pcJsonHandle, pcKey, *((double*)(pcValue)));
                         break;
            case STRING: cJSON_AddStringToObject(*pcJsonHandle, pcKey, (char* )pcValue);
                         break;
            case OBJECT:    
                         break;
            case ARRAY:  cJSON *pcData = NULL;
                        pcData = cJSON_AddArrayToObject(*pcJsonHandle, "data");

                        if (pcData)
                        {
                            for (ucIndex = 0; ucIndex < ucLen; ucIndex++)
                            {
                                cJSON_AddItemToArray(pcData, cJSON_CreateNumber(*((uint16_t*)pcValue+ucIndex)));
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


bool ParseRxData(uint8_t *pData,const char *pckey, uint8_t ucLen, uint64_t *pucData)
{
    bool bRetVal = false;
    char cbuff[150];
    cJSON *RxData = NULL;

    if (pData && pckey && pucData)
    {
        if (pData[0] == FLOW_METER)
        {
            memcpy(cbuff ,pData+2, ucLen);
            cJSON *root = cJSON_Parse(cbuff);
            RxData = cJSON_GetObjectItem(root, pckey);
            if (RxData)
            {
                *pucData = (RxData->valuedouble);
                cJSON_Delete(root);
                bRetVal = true;
            }
        }

    }
    return bRetVal;
}
