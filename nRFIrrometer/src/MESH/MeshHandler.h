/****************************INCLUDES*****************************************************/
#include <bluetooth/mesh/models.h>
// #include <zephyr/bluetooth/mesh/access.h>
#include <bluetooth/mesh/sensor_srv.h>
#include <zephyr/bluetooth/mesh.h>

/******************************MACROS*****************************************************/
#define VISENSE_COMPANY_ID    0x0059
#define VISENSE_MODEL_ID      0x000A
#define PRESSURE_SAMPLE       false
#define IRROMETER_SAMPLE      false
/******************************TYPEDEFS*****************************************************/


/****************************FUNCTION DECLERATION*****************************************************/

static int handle_message(struct bt_mesh_model *model,
                               struct bt_mesh_msg_ctx *ctx,
                               struct net_buf_simple *buf);
static int HistoryDataHandle(struct bt_mesh_model *model,
                               struct bt_mesh_msg_ctx *ctx,
                               struct net_buf_simple *buf);
static int relay_node_handle(struct bt_mesh_model *model, struct bt_mesh_msg_ctx *ctx,
			  struct net_buf_simple *buf);
static int role_handle_status(struct bt_mesh_model *model, struct bt_mesh_msg_ctx *ctx,
			  struct net_buf_simple *buf);

static void attention_off(struct bt_mesh_model *mod);
static void attention_on(struct bt_mesh_model *mod);
void sendAck(struct bt_mesh_msg_ctx *ctx, uint8_t status);
bool SendMeshPayloadToSupervisor(struct bt_mesh_msg_ctx *ctx);
void SendMeshPayloadToMaster(char *cMeshPayload, uint16_t unLen);

bool ModelPublish();
struct bt_mesh_model *GetMeshModel();

bool IsSupervisorConnected();
void SetSupervisorConnectedStatus(bool status);
bool IsSupervisorLiveNotifyEnable();
bool IsSupervisorHistoryNotifyEnable();

struct bt_mesh_msg_ctx *GetSupervisorCtx(void);
void SetSupervisorCtx(struct bt_mesh_msg_ctx *ctx);

bool SendLiveDataToSupervisor(uint8_t *pucBuffer, uint16_t unLength);

void MeshMsgSendStartCb(uint16_t duration, int err, void *cb_data);
void MeshMsgSendEndCb(int err, void *cb_data);


