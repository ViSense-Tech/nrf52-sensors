#include <stdbool.h>
#include <bluetooth/mesh/dk_prov.h>
#include "MeshService.h"




bool EnableBLE(void)
{
    int nError = 0;
    bool bRetVal = false;

    nError = bt_enable(bt_ready);

	if (!nError) 
    {
        bRetVal = true;
	}
    else
    {
		printk("Bluetooth init failed (err %d)\n", nError);
    }

    return bRetVal;
}
void bt_ready(int err)
{
	if (err) {
		printk("Bluetooth init failed (err %d)\n", err);
		return;
	}

	printk("Bluetooth initialized\n");

	 dk_leds_init();
	// dk_buttons_init(NULL);
	const struct bt_mesh_prov *prov = bt_mesh_dk_prov_init();
	err = bt_mesh_init(prov, model_handler_init());
	if (err) {
		printk("Initializing mesh failed (err %d)\n", err);
		return;
	}

	if (IS_ENABLED(CONFIG_SETTINGS)) {
		settings_load();
	}

	/* This will be a no-op if settings_load() loaded provisioning info */
	bt_mesh_prov_enable(BT_MESH_PROV_ADV | BT_MESH_PROV_GATT);

	printk("Mesh initialized\n");
}