/*************************************INCLUDEs**************************************************/
#include "MeshHandler.h"
#include "BleService.h"
#include "FlashHandler.h"
/*************************************MACROS****************************************************/

#define RECIEVE_OPCODE_VISENSE          BT_MESH_MODEL_OP_3(0x0A, VISENSE_COMPANY_ID)
#define HISTORY_DATA_OPCODE_VISENSE     BT_MESH_MODEL_OP_3(0x0B, VISENSE_COMPANY_ID)
#define ROLE_STATUS_OPCODE              BT_MESH_MODEL_OP_3(0x0E, VISENSE_COMPANY_ID)
/*************************************TYPEDEFS ******************************************/
typedef enum __eNetworkRole{
    ROLE_SUPERVISOR = 0,
    NOTIFICATION_LIVE,
    NOTIFICATION_HISTORY,
} _eNetworkRole;
/*************************************GLOBAL VARIABLES********************************************/

static bool attention;
bool bServerBusy = false;
static struct bt_mesh_model sMeshModel;
bool bSupervisorConnected = false;
struct bt_mesh_msg_ctx sSupervisorCtx;
static uint8_t ucIdx = 0;
bool bSndStat = true;
uint16_t ulRxCount = 0;
uint16_t usHisCount = 0;
/*True if complete message send 
else false*/
static bool bServerPayloadSendStatus = false;
/*true if Uncomplete send else false complete send*/
static bool bUnCompleteSendStatus = false;
// static _eNetworkRole eNetworkRole = ROLE_SERVER;
static bool bLiveDataNotificationEnabled = false;
static bool bHistoryNotificationEnabled = false;
static uint16_t ulSupervisorAddr = 0x0000;
struct bt_mesh_send_cb *sMeshMsgSendCb = NULL;

static struct bt_mesh_model_pub pub_ctx = {
    .msg = NET_BUF_SIMPLE(BT_MESH_MODEL_BUF_LEN(RECIEVE_OPCODE_VISENSE,
                                                BT_MESH_RX_SDU_MAX)),
};


const struct bt_mesh_model_op _opcode_list[] = {
    { RECIEVE_OPCODE_VISENSE,    BT_MESH_LEN_MIN(0),    handle_message },
    { HISTORY_DATA_OPCODE_VISENSE,    BT_MESH_LEN_MIN(0),    HistoryDataHandle },
    {ROLE_STATUS_OPCODE,    BT_MESH_LEN_MIN(0),    role_handle_status },
    BT_MESH_MODEL_OP_END,
};

static const struct bt_mesh_health_srv_cb health_srv_cb = {
	.attn_on = attention_on,
	.attn_off = attention_off,
};

static struct bt_mesh_health_srv health_srv = {
	.cb = &health_srv_cb,
};
BT_MESH_HEALTH_PUB_DEFINE(health_pub, 0);
static struct bt_mesh_elem elements[] = {
    BT_MESH_ELEM(
        1,
        BT_MESH_MODEL_LIST(BT_MESH_MODEL_CFG_SRV,
                           BT_MESH_MODEL_HEALTH_SRV(&health_srv,
                                                    &health_pub)),
        BT_MESH_MODEL_LIST(BT_MESH_MODEL_VND_CB(VISENSE_COMPANY_ID
,                                                VISENSE_MODEL_ID,
                                                _opcode_list,
                                                &pub_ctx,
                                                NULL,
                                                NULL))
    ),
};
static const struct bt_mesh_comp comp = {
	.cid = VISENSE_COMPANY_ID,
	.elem = elements,
	.elem_count = ARRAY_SIZE(elements),
};
/**************************************FUNCTION DEFINITION*****************************************************/
static void attention_on(struct bt_mesh_model *mod)
{
	attention = true;
	//k_work_reschedule(&attention_blink_work, K_NO_WAIT);
}
static void attention_off(struct bt_mesh_model *mod)
{
	attention = false;
}
static const uint8_t *extract_msg(struct net_buf_simple *buf)
{
	buf->data[buf->len] = '\0';
    
	return net_buf_simple_pull_mem(buf, buf->len);
}

static int role_handle_status(struct bt_mesh_model *model, struct bt_mesh_msg_ctx *ctx,
			  struct net_buf_simple *buf)
{
    uint32_t *ulFlashIdx;
    size_t i;

    ulFlashIdx = GetFlashCounter();
    uint8_t uStatus = net_buf_simple_pull_u8(buf);
    

    if (!IsConnected() && uStatus)
    {
        for (i = 0; i < 3; i++)
        {
            if (uStatus & (1 << i))
            {
                switch (i)
                {
                    case ROLE_SUPERVISOR:
                        printk("\n\r Get Supervisor Waiting to enable notification \n\r");
                        bSupervisorConnected = true;
                        ulSupervisorAddr = ctx->addr;
                        break;
                    case NOTIFICATION_LIVE:
                        bLiveDataNotificationEnabled = true;
                        printk("\n\r Supervisor live notification enabled\n\r");
                        break;
                    case NOTIFICATION_HISTORY:
                        bHistoryNotificationEnabled = true;
                        SendMeshPayloadToSupervisor(ctx);
                        printk("\n\r Supervisor history notification enabled\n\r");
                        break;
                }
                
            }
            else
            {
                switch (i)
                {
                    if (ulSupervisorAddr == ctx->addr)
                    {
                        case ROLE_SUPERVISOR:
                            bSupervisorConnected = false;
                            printk("\n\r Supervisor disconnected\n\r");
                            break;
                        case NOTIFICATION_LIVE:
                            bLiveDataNotificationEnabled = false;
                            printk("\n\r Supervisor live notification disabled\n\r");
                            break;
                        case NOTIFICATION_HISTORY:
                            bHistoryNotificationEnabled = false;
                            printk("\n\r Supervisor history notification disabled\n\r");
                            break;
                    }
                    
                }
            }
            
        }
           
    }
    else 
    {
        if (ulSupervisorAddr == ctx->addr)
        {
            bLiveDataNotificationEnabled = false;
            bHistoryNotificationEnabled = false;
        }
        
        
    }

    return 0;
    

}

/**
 * @brief Handle message
 * @param model - model handle
 * @param ctx - context handle
 * @param buf - buffer received
 * @return int
*/
static int handle_message(struct bt_mesh_model *model, struct bt_mesh_msg_ctx *ctx,
			  struct net_buf_simple *buf)
{
    bServerBusy = true;
    uint32_t *pulFlashIdx = NULL;
    uint8_t uMeshPayloadFromServer[255] = {0};
    char *MeshPayload = NULL;

    pulFlashIdx = GetFlashCounter();
	MeshPayload = extract_msg(buf);
	printk("Paylaod From server...................................: %s\n",MeshPayload);
    printk("\n\r Received Paylod count : %d\n\r", ++ulRxCount);
    
    if (IsNotificationenabled())
    {
        SendMeshPayloadToMaster(MeshPayload, (uint16_t)strlen(MeshPayload));
    }
    else
    {
        if (strlen(MeshPayload) > WRITE_ALIGNMENT)
        {
            if (writeJsonToExternalFlash(MeshPayload, *pulFlashIdx, 256))
            {
                *pulFlashIdx = *pulFlashIdx + 1;
            }
            else
            {
                printk("\n\rERROR: MESH PAYLOAD WRITE TO EXTERNAL FLASH FAILED\n\r");
            }
        }
        else 
        {
            if (writeJsonToExternalFlash(MeshPayload, *pulFlashIdx, WRITE_ALIGNMENT))
            {
                *pulFlashIdx = *pulFlashIdx + 1;
            }
            else
            {
                printk("\n\rERROR: MESH PAYLOAD WRITE TO EXTERNAL FLASH FAILED\n\r");
            }
        }
        
    }

    return 0;
}
/**
 * @brief callback function for receiving history data
 * @param model - model handle
 * @param ctx - context handle
 * @param buf - buffer received
 * @return int
*/
static int HistoryDataHandle(struct bt_mesh_model *model, struct bt_mesh_msg_ctx *ctx,
			  struct net_buf_simple *buf)
{
    char *MeshPayload = NULL;

	MeshPayload = extract_msg(buf);
    printk("\n\r Received History Paylod : %s\n\r", MeshPayload);
    printk("\n\r Received History Paylod count : %d\n\r", ++usHisCount);
    SendServerHistoryDataToApp(MeshPayload, strlen(MeshPayload));
    
    return 0;

}
/**
 * @brief callback function for send mesh message status
 * @param model - model
 * @return None
*/
static int update_handler(struct bt_mesh_model *model)
{
	struct net_buf_simple *buf = model->pub->msg;
    uint8_t uDeviceRole = 0;
	printk("update_handler\n");
	bt_mesh_model_msg_init(buf, ROLE_STATUS_OPCODE);
	
    if (IsConnected())
    {
        uDeviceRole = uDeviceRole | 1 << ROLE_SUPERVISOR;

        if (IsNotificationenabled() || IshistoryNotificationenabled()) 
        {
            if (IsNotificationenabled())
            {
                uDeviceRole = uDeviceRole | 1 << NOTIFICATION_LIVE;
            }
            if (IshistoryNotificationenabled())
            {
                uDeviceRole = uDeviceRole | 1 << NOTIFICATION_HISTORY;
            }
            
        } 
    }
    else
    {
        uDeviceRole = 0;
    }
    
    net_buf_simple_add_u8(buf, uDeviceRole);
	return 0;
}
/**
 * @brief get mesh model
 * @param None
 * @return model handler
*/

struct bt_mesh_model *GetMeshModel()
{
    // 
}

/**
 * @brief model handler initialization
 * @param None
 * @return mesh Node Composition 
*/
const struct bt_mesh_comp *model_handler_init(void)
{
    pub_ctx.update = update_handler;
    sMeshMsgSendCb->start = MeshMsgSendStartCb;
    sMeshMsgSendCb->end = MeshMsgSendEndCb;
	return &comp;
}

/**
 * @brief send ack over ble mesh
 * @param addr : address
 * @param opcode : opcode
 * @return None
 */
void sendAck(struct bt_mesh_msg_ctx *ctx, uint8_t uSensorStatus)
{
    struct net_buf_simple *msg = NET_BUF_SIMPLE(BT_MESH_TX_SDU_MAX);

    bt_mesh_model_msg_init(msg, HISTORY_DATA_OPCODE_VISENSE);
    // Build your status message payload
    net_buf_simple_add_u8(msg, uSensorStatus);

    // Send the status message back to the sender
    if (bt_mesh_model_send(elements->vnd_models, ctx, msg, NULL, NULL) != 0) 
    {
        printk("Failed to send status message\n");
    }
    else
    {
        printk("Sent status message\n");
    }
}   
/**
 * @brief send Node history payload to supervisor
 * @param ctx - supervisor context
 * 
*/
bool SendMeshPayloadToSupervisor(struct bt_mesh_msg_ctx *ctx)
{   
    bool bRetVal = false;
	bool bFullDataRead = false;
	char NotifyBuf[260];
	int nRetVal = 0;
	int uReadCount = 1;
	uint32_t *pulWritePos = NULL;
    uint32_t ulFlshIdx = 0;
    uint32_t uFlashCounter = 0;
    
    pulWritePos = GetFlashCounter();
    ulFlshIdx = *pulWritePos;
    bSndStat = false;


    printk("\n\rcontext net_idex is : %x",ctx->net_idx);
    printk("\n\rcontext app_idx is : %x",ctx->app_idx);
    printk("\n\rcontext addr is : %x",ctx->addr);
    printk("\n\rcontext send_rel is : %d",ctx->send_rel);
    ctx->send_rel = true;

	if (ucIdx > ulFlshIdx)
	{
		uFlashCounter = ucIdx - ulFlshIdx;
	}

    bUnCompleteSendStatus = true;
    if (bHistoryNotificationEnabled == false)
    {
        return bRetVal;
    }
    

	while(ucIdx <= NUMBER_OF_ENTRIES)
	{	
        struct net_buf_simple *msg = NET_BUF_SIMPLE(BT_MESH_TX_SDU_MAX);
        bt_mesh_model_msg_init(msg, HISTORY_DATA_OPCODE_VISENSE);
		if (!bHistoryNotificationEnabled)
		{
			break;
		}
		
		memset(NotifyBuf, 0, 260);
		uReadCount = readJsonFromExternalFlash(NotifyBuf, ucIdx, WRITE_ALIGNMENT);
		printk("\nId: %d, Ble_Stored_Data: %s\n",ucIdx, NotifyBuf);
		// if (uReadCount == true)
		// {
		// 	bFullDataRead = true;
		// 	break;
		// }
		if (NotifyBuf[0] != 0x7B)
		{
			bFullDataRead = true;
			break;
		}
		k_msleep(100);

		if (uReadCount > 0)
		{
            net_buf_simple_add_mem(msg, NotifyBuf, strlen(NotifyBuf));
            if (bt_mesh_model_send(elements->vnd_models, ctx, msg, NULL, NULL) != 0) 
            {
                printk("Failed to send  message\n");
                break;

            }
            else
            {   
                printk("Sent  message\n");

            } 
			if (nRetVal < 0)
			{
				printk("Notification failed%d\n\r",nRetVal);
			}
			
		}
		ucIdx++;
		uFlashCounter++;
		if (ucIdx == NUMBER_OF_ENTRIES)
		{
			ucIdx = 0;
		}
		if (ulFlshIdx > NUMBER_OF_ENTRIES )
		{
			bFullDataRead = true;
			break;	
		}
    }

    if (bFullDataRead == true) 
    {
        if(!EraseExternalFlash(SECTOR_COUNT))
        {
            printk("Flash erase failed!\n");
            return bRetVal;
        }
        printk("Flash Cleared");
        ucIdx = 0;
        bRetVal = true;
        bServerPayloadSendStatus = true;
        bUnCompleteSendStatus = false;
        *pulWritePos = 0;
    }
    bSndStat = true;
    return bRetVal;
    
      
}

/**
 * 
 * @brief send live payload to master
 * @param cMeshPayload - payload
 * @param unLen - length of payload
 * @return None
*/
void SendMeshPayloadToMaster(char *cMeshPayload, uint16_t unLen)
{
    VisenseSensordataNotify(cMeshPayload, unLen);
}
/**
 * @brief check if supervisor is connected
 * @return true if connected else false
*/
bool IsSupervisorConnected()
{
    return bSupervisorConnected;
}

/**
 * @brief check if supervisor Notifies for live data
 * @return true if connected else false
*/
bool IsSupervisorLiveNotifyEnable()
{
    return bLiveDataNotificationEnabled;
}

/**
 * @brief check if supervisor Notifies for History data
 * @return true if connected else false
*/
bool IsSupervisorHistoryNotifyEnable()
{
    return bHistoryNotificationEnabled;
}

/**
 * @brief set supervisor connected status
 * @param status : true if connected else false  
 * @return None
*/
void SetSupervisorConnectedStatus(bool status)
{
    bSupervisorConnected = status;
}
/**
 * @brief get supervisor context
 * @return address of context
*/
struct bt_mesh_msg_ctx *GetSupervisorCtx(void)
{
    return &sSupervisorCtx;
}

/**
 * @brief set supervisor context
 * @param ctx : context
 * @return None
*/
void SetSupervisorCtx(struct bt_mesh_msg_ctx *ctx)
{
    sSupervisorCtx = *ctx;
}

/**
 * @brief send live data to supervisor
 * @param pucBuffer : buffer
 * @param unLength : length
 * @return true for success
*/
bool SendLiveDataToSupervisor(uint8_t *pucBuffer, uint16_t unLength)
{
    bool bRetVal = false;
    struct bt_mesh_msg_ctx sSuprvisrCtx = {0};
    char cLiveData[260] = {0};
    
     uint32_t *uFlashIdx = NULL;
     printk("\n\rLength of the live data %d", unLength);

    memset(cLiveData, 0, 260);
   
    
    uFlashIdx = GetFlashCounter();
    struct net_buf_simple *msg = NET_BUF_SIMPLE(BT_MESH_TX_SDU_MAX);
    bt_mesh_model_msg_init(msg, RECIEVE_OPCODE_VISENSE); 
    sSuprvisrCtx.addr = ulSupervisorAddr;
    do
    {
        printk("\n\rSupervisor Address is %d\n\r", sSuprvisrCtx.addr);

        if (pucBuffer)
        {
            strncpy(cLiveData, pucBuffer, strlen(pucBuffer));
            net_buf_simple_add_mem(msg, cLiveData, strlen(cLiveData));
        }
        if (bt_mesh_model_send(elements->vnd_models, &sSuprvisrCtx, msg, sMeshMsgSendCb, NULL) != 0) 
        {
            printk("Failed to send  message\n");
            if(writeJsonToExternalFlash(pucBuffer, *uFlashIdx, WRITE_ALIGNMENT))
            {
                *uFlashIdx = *uFlashIdx + 1;
            }
            break;

        }
        else
        {   
            printk("Sent Live data to supervisor %s\n,", pucBuffer);
            bRetVal = true;

        } 
    } while (0);
    return bRetVal;
    
}

/**
 * @brief send start callback
 * @param duration : The duration of the full transmission
 * @param err : Error occurring during sending
 * @param cb_data : data
 * @return None
*/
void MeshMsgSendStartCb(uint16_t duration, int err, void *cb_data)
{
    printk("MEsh message send start duration %d\n", duration);
}

/**
 * @brief send end callback
 * @param err : Error occurring during sending
 * @param cb_data : data
 * @return None
*/
void MeshMsgSendEndCb(int err, void *cb_data)
{
    printk("MEsh message send end\n");
}
