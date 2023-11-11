/**************************************INCLUDES***********************************************************/
#include "mesh_handler.h"

/*************************************MACROS****************************************************/
#define IRROMETER_OPCODE_VISENSE BT_MESH_MODEL_OP_3(0x0B, VISENSE_COMPANY_ID)
#define SEND_OPCODE_VISENSE BT_MESH_MODEL_OP_3(0x0A, VISENSE_COMPANY_ID)

#define IRROMETER_OPCODE_VISENSE_LEN    BT_MESH_LEN_MIN(0)
#define SEND_OPCODE_VISENSE_LEN    BT_MESH_LEN_MIN(0)


/*************************************GLOBAL VARIABLES****************************************************/
static bool attention;
char *cJson = NULL;
static struct bt_mesh_model_pub pub_ctx = {
    .msg = NET_BUF_SIMPLE(BT_MESH_MODEL_BUF_LEN(IRROMETER_OPCODE_VISENSE,
                                                BT_MESH_TX_SDU_MAX)),
};
static struct net_buf_simple pub_msg;


const struct bt_mesh_model_op _opcode_list[] = {
	 { IRROMETER_OPCODE_VISENSE, IRROMETER_OPCODE_VISENSE_LEN, handle_message_send },
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
        BT_MESH_MODEL_LIST(BT_MESH_MODEL_VND_CB(VISENSE_COMPANY_ID,
                                                VISENSE_MODEL_ID,
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

static struct bt_mesh_model_pub pub_ctx;

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
/**
 * @brief function for extract message
 * @param buf - buffer
 * @return Address of message buffer
*/
static const uint8_t *extract_msg(struct net_buf_simple *buf)
{
	buf->data[buf->len - 1] = '\0';
	return net_buf_simple_pull_mem(buf, buf->len);
}



static void handle_message_send(struct bt_mesh_model *model,
                                  struct bt_mesh_msg_ctx *ctx,
                                  struct net_buf_simple *buf)
{
    printk("inside handle message");// handle for status message
}
void GetMeshPayload(char *cJsonPaylod)
{
	//  cJson = cJsonPaylod;
}

static int update_handler(struct bt_mesh_model *model)
{
	char msg[] = "{irrometer message}";
	struct net_buf_simple *buf = model->pub->msg;
	// printk("Inside update handler%s\n",cJson);
	bt_mesh_model_msg_init(buf, IRROMETER_OPCODE_VISENSE);
	if (msg != NULL)
	{
		k_sleep(K_MSEC(100));
		printk("cMeshPayLoad: %s\n", msg);
		net_buf_simple_add_mem(buf, msg, strnlen(msg, MESSAGE_SET_MAXLEN));
	}
	
	net_buf_simple_add_u8(buf, '\0');
    memset(cJson, 0, MESSAGE_SET_MAXLEN);
	return 0;
}
static int model_init(struct bt_mesh_model *model)
{
	pub_ctx.update = update_handler;
    return 0;
}

const struct bt_mesh_comp *model_handler_init(void)
{
	model_init(&elements->vnd_models);
	return &comp;
}