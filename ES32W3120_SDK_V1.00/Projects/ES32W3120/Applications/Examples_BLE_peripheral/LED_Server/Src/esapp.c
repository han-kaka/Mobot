/*************************************************************************************************/
/*
Copyright	:	QingDao Eastsoft Communication Technology Co.,Ltd.
File Name	:
Description	:
Author		:	eastsoft
Version		:	0.1
Date		:	20/09/17
History		:	None
Note		:	None
*/
/*************************************************************************************************/

#include <string.h>

#include "ald_conf.h"

#include "esble_comm.h"

#include "eslog_init.h"

#include "lib.h"
#include "lib_conf.h"
#include "lib_adv.h"
#include "lib_scan.h"
#include "lib_init.h"
#include "lib_db_discovery.h"

#include "esprf_led.h"
#include "esprf_led_c.h"
#include "esapp.h"

#include "sdk_conf.h"

#if BLE_LED_CLIENT
extern esprf_led_c_env_t g_esprf_led_c_env;
#endif //BLE_LED_CLIENT

extern uint8_t send_flag;

static lib_adv_t app_adv 		= {.adv_idx = ESBLE_INVALID_ACTIDX};
lib_scan_t app_scan 			= {.scan_idx = ESBLE_INVALID_ACTIDX};
lib_init_t app_init 			= {.init_idx = ESBLE_INVALID_ACTIDX};
lib_db_discovery_t app_db_disc 	= {.conn_idx = ESBLE_INVALID_ACTIDX};
bool auto_conn = false;
static esapp_conn_instance_t g_conn_instance[ESBLE_CONNECTION_MAX] = {{0}};;

lib_advdata_conn_intl_t g_slave_pref_conn_intval = { BLE_DEV_SLV_PREF_CONN_MIN_INTV, BLE_DEV_SLV_PREF_CONN_MAX_INTV};
uint8_t g_128_uuid_list[][128] = {LED_SERVER_UUID};//,LED_CHAR_UUIND};
lib_advdata_uuid_list_t g_incomplet_128bit_uuid = {sizeof(g_128_uuid_list)/128,&g_128_uuid_list[0][0]};

static void esapp_init_init(esble_gap_bdaddr_t peer_addr, bool creat);

/*****************************************************************************************************/
/**												Demo												**/
/*****************************************************************************************************/

/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
void esapp_gatt_write_ntf_ind(uint8_t conidx, uint16_t handle, uint16_t ntf_ind_cfg)
{
	esble_gattc_write_cmd_t cmd;
	uint8_t value[2];

	value[0] = ntf_ind_cfg&0xff;
	value[1] = (ntf_ind_cfg&0xff00)>>8;

	cmd.conidx = conidx;
	cmd.offset = 0;
	cmd.cursor = 0;
	cmd.handle = handle;
	cmd.length = 2;
	cmd.auto_execute = true;
	cmd.value = value;

	esble_gattc_write(&cmd);
}

/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
void esapp_led_c_evt_handler(esprf_led_c_env_t *p_led_c_evt)
{
	#if BLE_LED_CLIENT
	switch(p_led_c_evt->evt_type)
	{   
		case ESPRF_LED_C_EVT_DISCOVERY_COMPLETE:
			if(g_esprf_led_c_env.peer_db.button_cccd_handle != 0)
			{
				esapp_gatt_write_ntf_ind(g_esprf_led_c_env.conidx,
										g_esprf_led_c_env.peer_db.button_cccd_handle,
										LED_CFG_BUTTON_NTF);
			}
			break;
		case ESPRF_LED_C_EVT_BUTTON_NOTIFICATION:
		{
			esble_gattc_write_cmd_t cmd;
			static uint8_t value = 1;

			cmd.conidx = p_led_c_evt->conidx;
			cmd.cursor = 0;
			cmd.offset = 0;
			cmd.handle = g_esprf_led_c_env.peer_db.led_value_handle;
			cmd.length = 1;
			value ^= 0x01;
			cmd.value  = &value;
			cmd.auto_execute = true;

			esble_gattc_write(&cmd);
		}
			break;
		default:
			break;
	}
	#endif //BLE_LED_CLIENT
}

/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
#if BLE_LED_CLIENT
static void esapp_led_c_err_handler(uint8_t err_code)
{
	switch(err_code)
	{
		case GAP_ERR_TIMEOUT:
		{
		}
		break;
		default:
			break;
	}
}
#endif //BLE_LED_CLIENT

/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
static void esapp_handle_error(esble_err err_code)
{
	switch(err_code)
	{
		case ESBLE_ERROR_DATA_SIZE:
			break;
		case ESBLE_ERROR_NO_MEM:
			break;
		default:
			break;
	}
}

/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
static void esapp_add_svc_finish(uint8_t status)
{
	assert_param(status == ESBLE_ERROR_NO_ERROR);
}

/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
#if BLE_LED_SERVER
static void esapp_led_write_req(uint8_t conidx, uint16_t length, uint8_t *value)
{
	esprf_led_write_req_cfm(conidx, ATT_ERR_NO_ERROR, value[0]);
	
	esapp_button(length, value);
	
	ES_LOG_PRINT("receive data len:%d, data:", length);
	for(uint16_t i=0; i<length; i++) 
	{
		ES_LOG_PRINT("%.2x", value[i]);
	}
	ES_LOG_PRINT("\n");
	
//	if(20 == length && 0xc4 == value[2] && 0x01 == value[3]) {
		send_flag = 1;
//	}
	
//	if (value)
//	{
//		ald_gpio_write_pin(GPIOA, GPIO_PIN_11, 0);
//	}
//	else
//	{
//		ald_gpio_write_pin(GPIOA, GPIO_PIN_11, 1);
//	}
}
#endif //BLE_LED_SERVER

/*****************************************************************************************************/
/**												Adv Hdl												**/
/*****************************************************************************************************/

/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
static void esapp_create_adv_evt(lib_adv_t *adv, uint8_t status)
{
	assert_param(status == ESBLE_ERROR_NO_ERROR);
}

/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
static void esapp_set_adv_data_evt(lib_adv_t *adv, uint8_t status)
{
	assert_param(status == ESBLE_ERROR_NO_ERROR);

	lib_adv_start(adv, 0, 0);
}

/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
static void esapp_gapm_start_adv_evt(lib_adv_t *adv, uint8_t status)
{
	ald_gpio_write_pin(GPIOA, GPIO_PIN_7, 0);
}

/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
static void esapp_gapm_stop_adv_evt(lib_adv_t *adv, uint8_t reason, uint8_t per_adv_stop)
{
	ald_gpio_write_pin(GPIOA, GPIO_PIN_7, 1);
}

/*****************************************************************************************************/
/**												Scan Hdl												**/
/*****************************************************************************************************/

/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
static void esapp_create_scan_evt(lib_scan_t *scan, uint8_t status)
{
	assert_param(status == ESBLE_ERROR_NO_ERROR);
}

/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
static void esapp_start_scan_evt(lib_scan_t *scan, uint8_t status)
{
	ald_gpio_write_pin(GPIOA, GPIO_PIN_7, 0);
}

/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
static void esapp_stop_scan_evt(lib_scan_t *scan, uint8_t reason)
{
	ald_gpio_write_pin(GPIOA, GPIO_PIN_7, 1);

	if(auto_conn)
	{
		esble_gapm_create_init(&app_init.cmd); //create init
		auto_conn = false;
	}
}

/*****************************************************************************************************/
/**												Init Hdl												**/
/*****************************************************************************************************/

/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
static void esapp_create_init_evt(lib_init_t *init, uint8_t status)
{
	assert_param(status == ESBLE_ERROR_NO_ERROR);
}

/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
static void esapp_gapm_start_init_evt(lib_init_t *init, uint8_t status)
{
	ald_gpio_write_pin(GPIOA, GPIO_PIN_7, 0);
}

/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
static void esapp_gapm_stop_init_evt(lib_init_t *init, uint8_t reason)
{
	ald_gpio_write_pin(GPIOA, GPIO_PIN_7, 1);
}
/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
static void esapp_adv_report_ind(struct _lib_gapm_ext_adv_report_ind_t *ind)
{
	const bool auto_con_match = app_scan.connect_if_match;
	const esble_gapm_ext_adv_report_ind_t *adv_ind = ind->ind;

	if(auto_con_match && ind->is_filter_match)
	{
		esapp_init_init(adv_ind->trans_addr, false);
		lib_scan_stop(&app_scan); //stop scan before initing initiator
		auto_conn = true;
	}

}

/*****************************************************************************************************/
/**												外部接口											**/
/*****************************************************************************************************/
static void esapp_adv_init(void)
{
	esble_err err_code;
	lib_adv_init_t init;
	memset(&init, 0, sizeof(init));

	init.cmd.own_addr_type						= ESBLE_STATIC_ADDR;
	init.cmd.adv_param.type						= ESBLE_GAPM_ADV_TYPE_LEGACY;
	init.cmd.adv_param.prop						= ESBLE_GAPM_ADV_PROP_UNDIR_CONN_MASK;
	init.cmd.adv_param.filter_pol				= ESBLE_GAPM_ADV_ALLOW_SCAN_ANY_CON_ANY;
	init.cmd.adv_param.prim_cfg.chnl_map		= ESAPP_ADV_CHMAP;
	init.cmd.adv_param.prim_cfg.phy				= ESBLE_GAPM_PHY_TYPE_LE_1M;
	init.cmd.adv_param.max_tx_pwr				= BLE_ADV_PAR_TXPWR;

	init.cmd.adv_param.disc_mode				= ESBLE_GAPM_ADV_MODE_GEN_DISC;
	init.cmd.adv_param.prim_cfg.adv_intv_min	= ESAPP_ADV_INT_MIN;
	init.cmd.adv_param.prim_cfg.adv_intv_max	= ESAPP_ADV_INT_MAX;

	init.adv_data.name_type						= LIB_ADVDATA_FULL_NAME;
//	init.adv_data.include_addr					= true;
//	init.adv_data.include_appearance			= true;
//	init.adv_data.slave_conn_intl				= &g_slave_pref_conn_intval;
//	init.adv_data.incomplete_128bit_uuid_list	= &g_incomplet_128bit_uuid;
	
	init.scan_rsp_data.incomplete_128bit_uuid_list	= &g_incomplet_128bit_uuid;

	init.hdl.lib_adv_create_evt					= esapp_create_adv_evt;
	init.hdl.lib_adv_set_adv_data_evt			= esapp_set_adv_data_evt;
	init.hdl.lib_adv_start_evt					= esapp_gapm_start_adv_evt;
	init.hdl.lib_adv_stop_evt					= esapp_gapm_stop_adv_evt;

	err_code = lib_adv_init(&app_adv, &init);
	if(err_code != ESBLE_ERROR_NO_ERROR)
	{
		esapp_handle_error(err_code);
	}
}

static void esapp_scan_init(void)
{
	esble_err err_code;
	#if (BLE_SCAN_FILTER_ENABLE == 1)
	lib_ble_uuid_t target_uuid[] = {{ESBLE_ATT_UUID_128_LEN, LED_SERVER_UUID}};
	static const char target_name[] = "ES32W3120-LED";
	#endif //BLE_SCAN_FILTER_ENABLE
	lib_scan_init_t init_scan;

	memset(&init_scan, 0, sizeof(init_scan));
	memset(&app_scan, 0, sizeof(app_scan));

	init_scan.cmd.own_addr_type					= ESBLE_STATIC_ADDR;
	init_scan.scan_param.type					= ESBLE_GAPM_SCAN_TYPE_OBSERVER;
	init_scan.scan_param.prop					= ESBLE_GAPM_SCAN_PROP_PHY_1M_BIT;
	init_scan.scan_param.dup_filt_pol			= 0;
	init_scan.scan_param.scan_param_1m.scan_intv= 0x40;
	init_scan.scan_param.scan_param_1m.scan_wd 	= 0x20;
	init_scan.scan_param.duration				= 0;
	init_scan.scan_param.period					= 0;

	init_scan.hdl.lib_scan_create_evt			= esapp_create_scan_evt;
	init_scan.hdl.lib_scan_start_evt			= esapp_start_scan_evt;
	init_scan.hdl.lib_scan_stop_evt				= esapp_stop_scan_evt;
	init_scan.hdl.lib_adv_report_ind			= esapp_adv_report_ind;

	#if (BLE_SCAN_FILTER_ENABLE == 1)

	#if (BLE_SCAN_NAME_CNT > 0)
	if (strlen(target_name) != 0)
	{
		err_code = lib_ble_scan_name_filter_add(&app_scan, target_name);
		if(err_code != ESBLE_ERROR_NO_ERROR)
		{
			esapp_handle_error(err_code);
		}
		else
		{
			err_code = lib_ble_scan_filters_enable(&app_scan, LIB_BLE_SCAN_NAME_FILTER);
			if(err_code != ESBLE_ERROR_NO_ERROR)
			{
				esapp_handle_error(err_code);
			}
		}
	}
	#endif //BLE_SCAN_NAME_CNT > 0

	#if (BLE_SCAN_UUID_CNT > 0)

	uint8_t uuid_cnt = sizeof(target_uuid)/sizeof(target_uuid[0]); /*number of filter uuid*/

	for(uint8_t i = 0; i < uuid_cnt; i++)
	{
		err_code = lib_ble_scan_uuid_filter_add(&app_scan, &target_uuid[i]);
		if(err_code != ESBLE_ERROR_NO_ERROR)
		{
			esapp_handle_error(err_code);
		}
	}
	
	if(err_code == ESBLE_ERROR_NO_ERROR)
	{
		err_code = lib_ble_scan_filters_enable(&app_scan, LIB_BLE_SCAN_UUID_FILTER);
		if(err_code != ESBLE_ERROR_NO_ERROR)
		{
			esapp_handle_error(err_code);
		}
	}
	#endif //(BLE_SCAN_UUID_CNT > 0)

	lib_ble_scan_set_match_conn_mode(&app_scan, true);
	lib_ble_scan_filters_set_match_all_mode(&app_scan, false);

	#endif //BLE_SCAN_FILTER_ENABLE

	lib_scan_init(&app_scan, &init_scan);
}

static void esapp_init_init(esble_gap_bdaddr_t peer_addr, bool creat)
{
	esble_err err_code;
	lib_init_init_t init;
	memset(&init, 0, sizeof(init));

	init.cmd.own_addr_type		 = ESBLE_STATIC_ADDR;

	init.init_param.type		 = ESBLE_GAPM_INIT_TYPE_DIRECT_CONN_EST;
	init.init_param.prop		 = ESBLE_GAPM_INIT_PROP_1M_BIT;
	init.init_param.conn_to		 = BLE_INIT_PAR_CONN_TO;
	init.init_param.scan_param_1m.scan_intv		= BLE_INIT_PAR_SCAN_PARAM_1M_SCAN_INTV;
	init.init_param.scan_param_1m.scan_wd		= BLE_INIT_PAR_SCAN_PARAM_1M_SCAN_WD;
	init.init_param.scan_param_coded.scan_intv	= BLE_INIT_PAR_SCAN_PARAM_CODED_SCAN_INTV;
	init.init_param.scan_param_coded.scan_wd	= BLE_INIT_PAR_SCAN_PARAM_CODED_SCAN_WD;
	init.init_param.conn_param_1m.conn_intv_min	= BLE_INIT_PAR_CONN_PARAM_1M_CONN_INTV_MIN;
	init.init_param.conn_param_1m.conn_intv_max	= BLE_INIT_PAR_CONN_PARAM_1M_CONN_INTV_MAX;
	init.init_param.conn_param_1m.conn_latency	= BLE_INIT_PAR_CONN_PARAM_1M_CONN_LATENCY;
	init.init_param.conn_param_1m.supervision_to= BLE_INIT_PAR_CONN_PARAM_1M_SUPERVISION_TO;
	init.init_param.conn_param_1m.ce_len_min	= BLE_INIT_PAR_CONN_PARAM_1M_CE_LEN_MIN;
	init.init_param.conn_param_1m.ce_len_max	= BLE_INIT_PAR_CONN_PARAM_1M_CE_LEN_MAX;
	init.init_param.peer_addr					= peer_addr;

	init.hdl.lib_init_create_evt = esapp_create_init_evt;
	init.hdl.lib_init_start_evt	 = esapp_gapm_start_init_evt;
	init.hdl.lib_init_stop_evt 	 = esapp_gapm_stop_init_evt;

	err_code = lib_init_init(&app_init, &init, creat);
	if(err_code != ESBLE_ERROR_NO_ERROR)
	{
		esapp_handle_error(err_code);
	}
}

static void esapp_conf_finish(uint8_t err)
{

	assert_param(err == ESBLE_ERROR_NO_ERROR);

	#if BLE_LED_SERVER
	esprf_led_app_hdl_t hdl = {0};

	hdl.add_svc			= esapp_add_svc_finish;
	hdl.led_write_req	= esapp_led_write_req;

	esprf_led_init(&hdl, 0);
	#endif //BLE_LED_SERVER

	#if BLE_LED_CLIENT
	esprf_led_c_app_hdl_t led_c_hdl = {0};
	led_c_hdl.evt_handler = esapp_led_c_evt_handler;
	led_c_hdl.err_handler = esapp_led_c_err_handler;
	esprf_led_c_init(&led_c_hdl);
	#endif //BLE_LED_CLIENT

	esapp_adv_init();
//	esapp_scan_init();
}

/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
//static void esapp_db_disc_handler(esble_gattc_evt_enum opera, const void *ind)
//{
//	if(ind == NULL)
//		return;

//	switch(opera)
//	{
//		case ESBLE_GATTC_SDP_SVC_IND:
//			break;

//		case ESBLE_GATTC_DISC_CHAR_DESC_IND:
//			break;

//		default:
//			break;
//	}
//}

/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
static void	esapp_db_discovery_evt_handler(uint8_t conn_idx, uint8_t svc_cnt, lib_gattc_sdp_svc_ind_t *srv_ind)
{
	#if BLE_LED_CLIENT
	uint8_t svc_uuid[] = LED_SERVER_UUID;
	for(uint8_t i = 0; i < svc_cnt; i++)
	{
		if(memcmp(srv_ind[i].uuid, svc_uuid, sizeof(svc_uuid)) == 0)
		{
			esprf_led_c_on_db_disc_handler(conn_idx, &srv_ind[i]);
			break;
		}
	}
	#endif //BLE_LED_CLIENT
}

/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
static void	esapp_db_discovery_error_evt_handler(uint8_t conn_idx, uint8_t operation, uint8_t status)
{
}

/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
static void esapp_db_discovery_init(uint8_t conidx)
{
	lib_db_discovery_init_t disc_init;

	memset(&disc_init, 0, sizeof(lib_db_discovery_init_t));
	disc_init.cmd.conidx = conidx;
	disc_init.cmd.operation = ESBLE_GATTC_SDP_DISC_SVC_ALL;
	disc_init.cmd.start_hdl = ESBLE_ATT_1ST_REQ_START_HDL;
	disc_init.cmd.end_hdl = ESBLE_ATT_1ST_REQ_END_HDL;
	disc_init.cmd.seq_num = rand();

	disc_init.hdl.lib_db_discovery_evt = esapp_db_discovery_evt_handler;
	disc_init.hdl.lib_db_discovery_error_evt = esapp_db_discovery_error_evt_handler;

	lib_db_discovery_init(&app_db_disc, &disc_init);
}

/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
void esapp_init(void)
{
	for(uint8_t i = 0; i < ESBLE_CONNECTION_MAX; i++)
	{
		g_conn_instance[i].role = ESBLE_UNKNOWN_ROLE;
	}

	lib_conf_init(NULL, esapp_conf_finish);
}

/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
void esapp_button(uint16_t length, uint8_t *value)
{
	#if BLE_LED_SERVER
	esprf_led_button_send(length, value);
	#endif //BLE_LED_SERVER
}


/*****************************************************************************************************/
/**												Evt Hdl												**/
/*****************************************************************************************************/

/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
static void esapp_conn_param_upd_to(void *param_upd)
{
	esble_gapc_param_upd_cmd_t *param = (esble_gapc_param_upd_cmd_t *)param_upd;
	esble_gapc_param_upd(param);
}
/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
static void esapp_gapc_conn_req_ind(const esble_gapc_conn_req_ind_t *ind)
{
	esble_gapc_conn_cfm_t cfm = {0};
	uint8_t role,conidx;
	conidx 	= ind->conidx;
	role	= ind->role;

	if(conidx < ESBLE_CONNECTION_MAX)
	{
		g_conn_instance[conidx].conhdl 				= ind->conhdl;
		g_conn_instance[conidx].role 				= ind->role;
		g_conn_instance[conidx].con_interval 		= ind->con_interval;
		g_conn_instance[conidx].con_latency 		= ind->con_latency;
		g_conn_instance[conidx].clk_accuracy 		= ind->clk_accuracy;
		g_conn_instance[conidx].sup_to 				= ind->sup_to;
		g_conn_instance[conidx].peer_addr.addr_type = ind->peer_addr_type;
		g_conn_instance[conidx].peer_addr.addr 		= ind->peer_addr;
	}

	if (conidx == ESBLE_GAPC_INVALID_CONIDX)
	{
		if(app_adv.adv_idx != ESBLE_INVALID_ACTIDX)
		{
			lib_adv_start(&app_adv, 0, 0);
			return;
		}
		if(app_scan.scan_idx != ESBLE_INVALID_ACTIDX)
		{
			lib_scan_start(&app_scan);
			return;
		}
		if(app_init.init_idx != ESBLE_INVALID_ACTIDX)
		{
			lib_init_start(&app_init);
			return;
		}
	}

	cfm.conidx = ind->conidx;
	cfm.auth = ESBLE_GAP_AUTH_REQ_NO_MITM_NO_BOND;
	esble_gapc_conn_cfm(&cfm);

	ald_gpio_write_pin(GPIOA, GPIO_PIN_8, 0);
	ald_gpio_write_pin(GPIOA, GPIO_PIN_7, 1);


	if(role == ESBLE_SLAVE_ROLE)						/*set timer for connection parameters update*/
	{
		esble_gapc_param_upd_cmd_t param_upd;

		param_upd.conidx = conidx;
		param_upd.pkt_id = rand();
		param_upd.intv_min = BLE_INIT_PAR_CONN_PARAM_1M_CONN_INTV_MIN*2;
		param_upd.intv_max = BLE_INIT_PAR_CONN_PARAM_1M_CONN_INTV_MAX*2;
		param_upd.latency = BLE_INIT_PAR_CONN_PARAM_1M_CONN_LATENCY*2;
		param_upd.time_out = BLE_INIT_PAR_CONN_PARAM_1M_SUPERVISION_TO*2;
		param_upd.ce_len_min = BLE_INIT_PAR_CONN_PARAM_1M_CE_LEN_MIN*2;
		param_upd.ce_len_max = BLE_INIT_PAR_CONN_PARAM_1M_CE_LEN_MAX*2;
		esble_gapc_param_upd(&param_upd);
		
//		g_conn_instance[conidx].upd_param.arg = (void *)&param_upd;
//		g_conn_instance[conidx].upd_param.timeout_hdl = esapp_conn_param_upd_to;
//		g_conn_instance[conidx].upd_param.ms = 1000;
//		g_conn_instance[conidx].upd_param.flag = ESBLE_TIMER_FLAG_ONE_SHOT;

//		esble_timer_init(&g_conn_instance[conidx].upd_timer, &g_conn_instance[conidx].upd_param);
//		esble_timer_start(&g_conn_instance[conidx].upd_timer);

	}
	else if(role == ESBLE_MASTER_ROLE)					/*Exchange MTU*/
	{
		esble_gattc_exc_mtu_cmd_t cmd;
		cmd.conidx = ind->conidx;

		esble_gattc_mtu_exch_cmd(&cmd);
	}
}

/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
static void esapp_gapc_disconn_ind(const esble_gapc_disconn_ind_t *ind)
{
	if(g_conn_instance[ind->conidx].role == ESBLE_SLAVE_ROLE)
	{
		lib_adv_start(&app_adv, 0, 0);
	}
	else if(g_conn_instance[ind->conidx].role == ESBLE_MASTER_ROLE)
	{
		lib_init_start(&app_init);
	}

	send_flag = 0;
	ald_gpio_write_pin(GPIOA, GPIO_PIN_8, 1);
}

/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
static void esapp_gapc_param_upd_req_ind(const esble_gapc_param_upd_req_ind_t *ind)
{
	esble_gapc_param_update_cfm_t cfm = {0};
	uint8_t conidx = ind->conidx;

	cfm.conidx = conidx;
	esble_gapm_conn_param_t *init_conn_param = &app_init.init_param.conn_param_1m;
	if((ind->intv_max < init_conn_param->conn_intv_min) || (ind->intv_min > init_conn_param->conn_intv_max)
		|| (ind->latency > init_conn_param->conn_latency))
	{
		cfm.accept = false;
	}
	else
	{
		cfm.accept = true;
		cfm.ce_len_min = init_conn_param->ce_len_min;
		cfm.ce_len_max = init_conn_param->conn_intv_max;
	}
	esble_gapc_param_upd_cfm(&cfm);
}

/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
static void esapp_gapc_param_upd_ind(const esble_gapc_param_upd_ind_t *ind)
{
	uint8_t conidx = ind->conidx;

	if(g_conn_instance[conidx].role != ESBLE_UNKNOWN_ROLE)
	{
		g_conn_instance[conidx].con_interval 	= ind->con_interval;
		g_conn_instance[conidx].con_latency 	= ind->con_latency;
		g_conn_instance[conidx].sup_to 			= ind->sup_to;
	}
}

/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
static void esapp_gattc_cmp(const esble_gattc_cmp_evt_t *evt)
{
	switch(evt->cmd)
	{
		case ESBLE_GATTC_MTU_EXCH_CMD:
		{
			if(evt->status == ATT_ERR_NO_ERROR)
			{
				esapp_db_discovery_init(evt->conidx); /*Start discover service*/
			}
		}
			break;
		default:
			break;
	}
}

lib_hdl_tbl_t esapp_hdl_tbl[] =
{
	{ESBLE_GATTC_CMP_EVT,			(void (*)(const void *evt))esapp_gattc_cmp},

	{ESBLE_GAPC_CONN_REQ_IND,		(void (*)(const void *evt))esapp_gapc_conn_req_ind},
	{ESBLE_GAPC_DISCONN_IND,		(void (*)(const void *evt))esapp_gapc_disconn_ind},

	{ESBLE_GAPC_PARAM_UPD_REQ_IND,	(void (*)(const void *evt))esapp_gapc_param_upd_req_ind},
	{ESBLE_GAPC_PARAM_UPD_IND,		(void (*)(const void *evt))esapp_gapc_param_upd_ind},


};

BLECB_REGI(esapp_hdl_tbl);
