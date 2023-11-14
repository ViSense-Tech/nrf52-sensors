#include <zephyr/bluetooth/mesh.h>
#include <bluetooth/mesh/models.h>
#include <bluetooth/mesh/dk_prov.h>




const struct bt_mesh_comp *model_handler_init(void);
bool EnableBLE(bt_ready);
void bt_ready(int err);