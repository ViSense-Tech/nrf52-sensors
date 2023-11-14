/*************************************INCLUDEs**************************************************/
#include "mesh_handler.h"
#include "BleService.h"
#include "nvs_flash.h"
/*************************************MACROS****************************************************/

#define RECIEVE_OPCODE_VISENSE          BT_MESH_MODEL_OP_3(0x0A, VISENSE_COMPANY_ID)
#define IRROMETER_RX_OPCODE_VISENSE     BT_MESH_MODEL_OP_3(0x0B, VISENSE_COMPANY_ID)
#define RELAY_NODE_OPCODE               BT_MESH_MODEL_OP_3(0x0C, VISENSE_COMPANY_ID)

/*************************************GLOBAL VARIABLES********************************************/
static bool attention;
static uint32_t uFlashIdx = 0;
static struct bt_mesh_model_pub pub_ctx = {
    .msg = NET_BUF_SIMPLE(BT_MESH_MODEL_BUF_LEN(RECIEVE_OPCODE_VISENSE,
                                                BT_MESH_RX_SDU_MAX)),
};


const struct bt_mesh_model_op _opcode_list[] = {
    { RECIEVE_OPCODE_VISENSE,    BT_MESH_LEN_MIN(0),    handle_message },
    { IRROMETER_RX_OPCODE_VISENSE,    BT_MESH_LEN_MIN(0),    irrometer_handle },
    {RELAY_NODE_OPCODE,    BT_MESH_LEN_MIN(0),    relay_node_handle },
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
                                                NULL,
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

static int relay_node_handle(struct bt_mesh_model *model, struct bt_mesh_msg_ctx *ctx,
			  struct net_buf_simple *buf)
{
    printk("relay node message\n");
    char *msgg;
    msgg = extract_msg(buf);
    
    printk("relay node message is : %s\n",msgg);
	return 0;

}

static int handle_message(struct bt_mesh_model *model, struct bt_mesh_msg_ctx *ctx,
			  struct net_buf_simple *buf)
{
	bool bRetVal = false;
    char cBuffer[100];
	char *msgg;
    msgg = extract_msg(buf);
    memset(cBuffer, 0, 100);
    memcpy(cBuffer, msgg, strlen(msgg));
    if(writeJsonToExternalFlash(cBuffer, uFlashIdx, WRITE_ALIGNMENT))
    {
        // NO OP
    }
    k_msleep(50);
    // memset(cBuffer, 0, 100);
    if (readJsonFromExternalFlash(cBuffer, uFlashIdx, WRITE_ALIGNMENT))
    {
        printk("\n\rId: %d, Stored_Data: %s\n",uFlashIdx, cBuffer);
    }
    printk("\n\rpressure message: %s\n",msgg);
    uFlashIdx++;
	return 0;
}
static int irrometer_handle(struct bt_mesh_model *model, struct bt_mesh_msg_ctx *ctx,
			  struct net_buf_simple *buf)
{
	bool bRetVal = false;
	char *msgg;
    msgg = extract_msg(buf);
    bRetVal = writeJsonToExternalFlash(msgg, uFlashIdx, sizeof(msgg));
    printk("irrometer message: %s\n",msgg);
	return 0;
}



const struct bt_mesh_comp *model_handler_init(void)
{
	return &comp;
}

void SendMeshPayload(void)
{
    if(IshistoryNotificationenabled() && IsConnected())
    {
        printk("In history notif\n\r");
        if (VisenseHistoryDataNotify(uFlashIdx))
        {
            uFlashIdx = 0;
        } 
    }    
}