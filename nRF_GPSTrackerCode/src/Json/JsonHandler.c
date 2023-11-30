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

 _sFenceData sFenceData[6] = {0};


_sFenceData *GetFenceTable()
{
    return &sFenceData;
}

 void SetFenceTable(_sFenceData *sFenceTable)
 {
     memcpy(&sFenceData, sFenceTable, sizeof(sFenceTable));
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
            cJSON_AddNumberToObject(*pcJsonHandle, pcKey, *((double *)(pcValue)));
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

bool ParseRxData(uint8_t *pData, const char *pckey, uint16_t ucLen, uint64_t *pucData)
{
    // const char *cbuff = "{\"cc\": 4, \"lt\": [10.05567067533764, 10.05667067133764, 10.05567067137764, 10.05567067133564] }";

    bool bRetVal = false;
    char cbuff[150] = {0};
    cJSON *RxData = NULL;
    //printk("inside ParseRxData- ucLen= %d\n\r", ucLen);
    if (ucLen >= 150)
    {
        return bRetVal;
    }
    if (pData && pckey && pucData)
    {
        // if (pData[0] == 0x01)
        if (1)     //length check
        {

            // memcpy(cbuff ,pData+2, ucLen);
            cJSON *root = cJSON_Parse(pData + 2);
            if (root != NULL)
            {
                printk("cjson parse");
                RxData = cJSON_GetObjectItem(root, pckey);
                // printk("json get obj");
                if (RxData)
                {
                    *pucData = (RxData->valuedouble);
                    cJSON_Delete(root);
                    bRetVal = true;
                }
            }
            else
            {
                printk("root null \n\r");
            }
        }
    }
    return bRetVal;
}

bool ParseArray(uint8_t *pData, const char *pckey, uint16_t ucLen, char *pucData)
{
    bool bRetVal = false;
    char *cbuff = NULL;
    // char LocData[6][20];
    cJSON *RxData = NULL;
    int arraySize;
    printk("1 inParseArray\n\r");
    if (pData && pckey)
    {

        // if (pData[0] == 0x01) {
        // memcpy(cbuff, pData + 2, ucLen);
        cJSON *root = cJSON_Parse(pData + 2);
        printk("2,cjson parseed y\n");
        if (root != NULL)
        {
            RxData = cJSON_GetObjectItem(root, pckey);
            printk("cjson get obj\n");
            

            if (cJSON_IsArray(RxData))
            {
                printk("parsed item is an array..\n\r");
                arraySize = cJSON_GetArraySize(RxData);
                printk("array size %d\n", arraySize);
                for (int i = 0; i < arraySize; i++)
                {
                    cJSON *arrayItem = cJSON_GetArrayItem(RxData, i);
                    if (arrayItem != NULL)
                    {
                        //  pucData[i] = arrayItem->valuedouble;
                        bRetVal = true;
                        memcpy(pucData, (arrayItem->valuestring), strlen(arrayItem->valuestring));

                        pucData = pucData + (strlen(arrayItem->valuestring));
                        *pucData = ',';
                        pucData++;

                        // printk("\n\rParsed data :%f",pucData[i]);
                    }
                }
            }

            // bRetVal = true;
            //  }
            cJSON_Delete(root); // Free the cJSON structure
        }
        // }
    }

    return bRetVal;
}

