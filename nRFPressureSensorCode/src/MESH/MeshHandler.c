/*************************************INCLUDEs**************************************************/
#include "MeshHandler.h"
#include "BleService.h"
#include "nvs_flash.h"
/*************************************MACROS****************************************************/
#define PRESSURE_SENSOR_STATUS           0x01
#define IRROMETER_SENSOR_STATUS          0x02
#define RELAY_NODE_STATUS                0x03
#define SUPERVISOR_STATUS                0x04

#define RECIEVE_OPCODE_VISENSE          BT_MESH_MODEL_OP_3(0x0A, VISENSE_COMPANY_ID)
#define IRROMETER_RX_OPCODE_VISENSE     BT_MESH_MODEL_OP_3(0x0B, VISENSE_COMPANY_ID)
#define RELAY_NODE_OPCODE               BT_MESH_MODEL_OP_3(0x0C, VISENSE_COMPANY_ID)
#define ACK_OPCODE_VISENSE              BT_MESH_MODEL_OP_3(0x0D, VISENSE_COMPANY_ID)
#define ROLE_STATUS_OPCODE              BT_MESH_MODEL_OP_3(0x0E, VISENSE_COMPANY_ID)

/*************************************GLOBAL VARIABLES********************************************/

static bool attention;
bool bServerBusy = false;
static struct bt_mesh_model sMeshModel;
bool bSupervisorConnected = false;
struct bt_mesh_msg_ctx sSupervisorCtx;
static uint8_t ucIdx = 0;
bool bSndStat = true;
uint16_t ulRxCount = 0;
/*True if complete message send 
else false*/
static bool bServerPayloadSendStatus = false;
/*true if Uncomplete send else false complete send*/
static bool bUnCompleteSendStatus = false;

static struct bt_mesh_model_pub pub_ctx = {
    .msg = NET_BUF_SIMPLE(BT_MESH_MODEL_BUF_LEN(RECIEVE_OPCODE_VISENSE,
                                                BT_MESH_RX_SDU_MAX)),
};


const struct bt_mesh_model_op _opcode_list[] = {
    { RECIEVE_OPCODE_VISENSE,    BT_MESH_LEN_MIN(0),    handle_message },
    { IRROMETER_RX_OPCODE_VISENSE,    BT_MESH_LEN_MIN(0),    irrometer_handle },
    {RELAY_NODE_OPCODE,    BT_MESH_LEN_MIN(0),    relay_node_handle },
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
	buf->data[buf->len - 1] = '\0';
	return net_buf_simple_pull_mem(buf, buf->len);
}

static int role_handle_status(struct bt_mesh_model *model, struct bt_mesh_msg_ctx *ctx,
			  struct net_buf_simple *buf)
{
    uint32_t *ulFlashIdx;

    ulFlashIdx = GetFlashCounter();
   #if 1
    if (!IsConnected())
    {
        uint8_t status = net_buf_simple_pull_u8(buf);
        printk("\nStatus: %d\n", status);
        if(status == SUPERVISOR_STATUS)
        {
            printk("INFO: CONNECTED TO SUPERVISOR\n");
            if (bSndStat)
            {
                SendMeshPayloadToSupervisor(ctx);
            }
                
        }
        else
        {
            printk("INFO: CHECKING SUPERVISOR STATUS\n");
            bSupervisorConnected = false;
        }
    }
    else
    {
        printk("INFO: ALREADY CONNECTED\n");
    }
#endif

}
static int relay_node_handle(struct bt_mesh_model *model, struct bt_mesh_msg_ctx *ctx,
			  struct net_buf_simple *buf)
{
// 
}

static int handle_message(struct bt_mesh_model *model, struct bt_mesh_msg_ctx *ctx,
			  struct net_buf_simple *buf)
{
#if 1
    bServerBusy = true;
    uint32_t *pulFlashIdx = NULL;
    uint8_t uMeshPayloadFromServer[255] = {0};
    // char *MeshPayload;

    pulFlashIdx = GetFlashCounter();
	// MeshPayload = extract_msg(buf);

    // memcpy(uMeshPayloadFromServer, MeshPayload, strlen(uMeshPayloadFromServer));

    char *MeshPayload;
	MeshPayload = extract_msg(buf);
	printk("Paylaod From server...................................: %s\n",MeshPayload);
    printk("\n\r Received Paylod count : %d\n\r", ++ulRxCount);
    
    if (IsNotificationenabled())
    {
        SendMeshPayloadToMaster(MeshPayload);
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
        else if (writeJsonToExternalFlash(MeshPayload, *pulFlashIdx, WRITE_ALIGNMENT))
        {
            *pulFlashIdx = *pulFlashIdx + 1;
        }
        else
        {
            printk("\n\rERROR: MESH PAYLOAD WRITE TO EXTERNAL FLASH FAILED\n\r");
        }
        
    }
#endif
    // bServerBusy = true;
    // char *MeshPayload;
	// MeshPayload = extract_msg(buf);
	// printk("Paylaod From server...................................: %s\n",MeshPayload);
	// return 0;
}
static int irrometer_handle(struct bt_mesh_model *model, struct bt_mesh_msg_ctx *ctx,
			  struct net_buf_simple *buf)
{
// 
}
/**
 * @brief callback function for send mesh message
 * @param model - model
 * @return None
*/
static int update_handler(struct bt_mesh_model *model)
{
	struct net_buf_simple *buf = model->pub->msg;
	printk("update_handler\n");
	bt_mesh_model_msg_init(buf, ROLE_STATUS_OPCODE);
	
	
	if(IsConnected())
	{
		printk("\n\rRole : SUPERVISOR");
        net_buf_simple_add_u8(buf, SUPERVISOR_STATUS);
		// bSensorStatus = false;
	}
	else
	{
        net_buf_simple_add_u8(buf, PRESSURE_SENSOR_STATUS);
		printk("\n\rRole : SERVER");
		//k_msleep(10000);
	}

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

const struct bt_mesh_comp *model_handler_init(void)
{
    pub_ctx.update = update_handler;
	return &comp;
}

void SendMeshPayload(void)
{
    uint32_t *pulFlashIdx;
    pulFlashIdx = GetFlashCounter();
    if(IshistoryNotificationenabled() && IsConnected())
    {
        printk("In history notif\n\r");
        if (VisenseHistoryDataNotify(*pulFlashIdx))
        {
            *pulFlashIdx = 0;
        } 
    }    
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

    bt_mesh_model_msg_init(msg, IRROMETER_RX_OPCODE_VISENSE);
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
    
    // BT_MESH_MODEL_BUF_DEFINE(msg, RECIEVE_OPCODE_VISENSE, 256);
    
    pulWritePos = GetFlashCounter();
    ulFlshIdx = *pulWritePos;
    bSndStat = false;

    printk("\n\rcontext net_idex is : %x",ctx->net_idx);
    printk("\n\rcontext app_idx is : %x",ctx->app_idx);
    printk("\n\rcontext addr is : %x",ctx->addr);
    printk("\n\rcontext send_rel is : %d",ctx->send_rel);
    ctx->send_rel = true;

	// if (ucIdx > ulFlshIdx)
	// {
	// 	uFlashCounter = ucIdx - ulFlshIdx;
	// }

    bUnCompleteSendStatus = true;

	while(ucIdx <= NUMBER_OF_ENTRIES)
	{	
        struct net_buf_simple *msg = NET_BUF_SIMPLE(BT_MESH_TX_SDU_MAX);
        bt_mesh_model_msg_init(msg, RECIEVE_OPCODE_VISENSE);
		// if (!IsConnected())
		// {
		// 	break;
		// }
		
		memset(NotifyBuf, 0, 260);
		uReadCount = readJsonFromExternalFlash(NotifyBuf, ucIdx, WRITE_ALIGNMENT);
        // strcpy(NotifyBuf, "{Test for mesh}");

		printk("\nId: %d, Ble_Stored_Data: %s\n",ucIdx, NotifyBuf);
		// if (uReadCount == true)
		// {
		// 	bFullDataRead = true;
		// 	break;
		// }
		if (NotifyBuf[0] != 0x7B)
		{
			// bFullDataRead = true;
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
		// uFlashCounter++;
		if (ucIdx == NUMBER_OF_ENTRIES)
		{
			ucIdx = 0;
		}
		if (ulFlshIdx > NUMBER_OF_ENTRIES )
		{
			bFullDataRead = true;
			break;	
		}
        // net_buf_simple_remove_mem(&msg, msg.len);
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
void SendMeshPayloadToMaster(char *cMeshPayload)
{
    VisenseSensordataNotify(cMeshPayload, ADV_BUFF_SIZE);
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