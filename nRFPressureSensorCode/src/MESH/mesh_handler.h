/****************************INCLUDES*****************************************************/
#include <bluetooth/mesh/models.h>
// #include <zephyr/bluetooth/mesh/access.h>
#include <bluetooth/mesh/sensor_srv.h>
#include <zephyr/bluetooth/mesh.h>

/******************************MACROS*****************************************************/
#define VISENSE_COMPANY_ID    0x0059
#define VISENSE_MODEL_ID      0x000A
/******************************TYPEDEFS*****************************************************/

/****************************FUNCTION DECLERATION*****************************************************/

static int handle_message(struct bt_mesh_model *model,
                               struct bt_mesh_msg_ctx *ctx,
                               struct net_buf_simple *buf);
static int irrometer_handle(struct bt_mesh_model *model,
                               struct bt_mesh_msg_ctx *ctx,
                               struct net_buf_simple *buf);
static int relay_node_handle(struct bt_mesh_model *model, struct bt_mesh_msg_ctx *ctx,
			  struct net_buf_simple *buf);

static void attention_off(struct bt_mesh_model *mod);
static void attention_on(struct bt_mesh_model *mod);
void SendMeshPayload(void);
void sendAck(struct bt_mesh_msg_ctx *ctx, uint8_t status);