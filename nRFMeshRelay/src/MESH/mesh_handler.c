/**************************************INCLUDES***********************************************************/
#include "mesh_handler.h"

/*************************************MACROS****************************************************/
#define SEND_OPCODE_VISENSE BT_MESH_MODEL_OP_3(0x0A, VISENSE_COMPANY_ID)
#define IRROMETER_OPCODE_VISENSE BT_MESH_MODEL_OP_3(0x0B, VISENSE_COMPANY_ID)
#define RELAY_NODE_OPCODE BT_MESH_MODEL_OP_3(0x0C, VISENSE_COMPANY_ID)

#define SEND_OPCODE_VISENSE_LEN    BT_MESH_LEN_MIN(0)
#define IRROMETER_OPCODE_VISENSE_LEN    BT_MESH_LEN_MIN(0)
#define RELAY_NODE_OPCODE_LEN    BT_MESH_LEN_MIN(0)


/*************************************GLOBAL VARIABLES****************************************************/
static bool attention;
bool bRelayStatus = false;
bool bSensorStatus = false;

char *cJson = NULL;
/*Initialise a publish context for the model.*/
static struct bt_mesh_model_pub pub_ctx = {
    .msg = NET_BUF_SIMPLE(BT_MESH_MODEL_BUF_LEN(SEND_OPCODE_VISENSE,
                                                BT_MESH_TX_SDU_MAX)),
};
static struct net_buf_simple pub_msg;

/*Initialise the opcode list*/
const struct bt_mesh_model_op _opcode_list[] = {
    { IRROMETER_OPCODE_VISENSE, IRROMETER_OPCODE_VISENSE_LEN, handle_message_receive },
	{ SEND_OPCODE_VISENSE, SEND_OPCODE_VISENSE_LEN , handle_message_send },
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
/**
 * @brief callback function for mesh health service 
 * @param mod - model
 * @return None
*/
static void attention_on(struct bt_mesh_model *mod)
{
	attention = true;
	//k_work_reschedule(&attention_blink_work, K_NO_WAIT);
}
/**
 * @brief callback function for mesh health service
 * @param mod - model
 * @return None
*/
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
/**
 * @brief callback function for receive message from mesh
 * @param model - model
 * @param ctx - context
 * @param buf - buffer
 * @return None
*/
static void handle_message_receive(struct bt_mesh_model *model,
                                  struct bt_mesh_msg_ctx *ctx,
                                  struct net_buf_simple *buf)
{
	// int err;
	// char *msg = NULL;
	// msg = extract_msg(buf);
	// BT_MESH_MODEL_BUF_DEFINE(buf, RELAY_NODE_OPCODE, RELAY_NODE_OPCODE_LEN);
	// struct net_buf_simple *buff = elements->vnd_models->pub->msg;
	//  bt_mesh_model_msg_init(buff, RELAY_NODE_OPCODE	);

	// net_buf_simple_add_mem(buff, msg, strnlen(msg, MESSAGE_SET_MAXLEN));
	// net_buf_simple_add_u8(buff, '\0');
	// err = bt_mesh_model_publish(elements->vnd_models);
	// if (err)
	// {
	// 	printk("Unable to send relay message%d\n",err);
	// }
	// else
	// {
	 	printk("relay message sent \n");
	// }
	
	// return 0;
}
/**
 * @brief callback function for receive message from mesh
 * @param model - model
 * @param ctx - context
 * @param buf - buffer
 * @return None
*/
static void handle_message_send(struct bt_mesh_model *model,
                                  struct bt_mesh_msg_ctx *ctx,
                                  struct net_buf_simple *buf)
{
// 
}
/**
 * @brief function for set mesh payload
 * @param cJsonPaylod - payload
 * @return None
*/
void SetMeshPayload(char *cJsonPaylod)
{
	 cJson = cJsonPaylod;
}
/**
 * @brief callback function for send mesh message
 * @param model - model
 * @return None
*/
static int update_handler(struct bt_mesh_model *model)
{
	// bSensorStatus = true;
	struct net_buf_simple *buf = model->pub->msg;
	printk("update_handler\n");
	bt_mesh_model_msg_init(buf, SEND_OPCODE_VISENSE);
	if (cJson != NULL)
	{
		printk("cMeshPayLoad: %s\n", cJson);
		net_buf_simple_add_mem(buf, cJson, strnlen(cJson, MESSAGE_SET_MAXLEN));

	}
	
	net_buf_simple_add_u8(buf, '\0');
    memset(cJson, 0, MESSAGE_SET_MAXLEN);

	return 0;

}
/**
 * @brief function for initialise mesh publish callback
 * @param model - model
 * @return None
*/
static int model_init(struct bt_mesh_model *model)
{
	pub_ctx.update = update_handler;
    return 0;
}
/**
 * @brief function for initialise mesh model
 * @param None
 * @return None
*/
const struct bt_mesh_comp *model_handler_init(void)
{
	model_init(elements->vnd_models);
	return &comp;
}
