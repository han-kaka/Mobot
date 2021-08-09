/*************************************************************************************************/
/*
Copyright	:	QingDao Eastsoft Communication Technology Co.,Ltd.
File Name	:
Description	:
Author		:	eastsoft
Version		:
Date		:
History		:	None
Note		:	None
*/
/*************************************************************************************************/

#include <string.h>

#include "sdk_conf.h"

#include "esble_gapm.h"
#include "esble_gapc.h"

#include "lib.h"
#include "lib_conf.h"

static lib_conf_env_t lib_conf_env;

/*****************************************************************************************************/
/**												外部接口											**/
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
void lib_conf_init(esble_gapm_set_dev_config_cmd_t *conf, lib_conf_finish_t finish)
{
	esble_gapm_set_dev_config_cmd_t *def;
	esble_bd_addr_t pub_addr = BLE_BD_ADDR;
	esble_bd_addr_t rnd_addr = BLE_RANDOM_ADDR;

	memset(&lib_conf_env, 0, sizeof(lib_conf_env));
	def = &lib_conf_env.conf;

	if (conf == NULL)
	{
		def->role					= BLE_CFG_ROLE;
		def->pub_addr = pub_addr;
		if(BLE_USE_RANDOM_ADDR)
		{
			def->rnd_addr = rnd_addr;
		}
		/* Privacy Config. */
//		def->renew_dur				= BLE_RENEW_DURATION;
//		def->addr					= addr;
//		conf->irk					= 0;
		def->privacy_cfg			= BLE_PRIVACY;
		/* Security Config. */
		def->pairing_mode			= BLE_PAIR_MODE;
		/* ATT Database Config. */
		def->gap_start_hdl			= 0;
		def->gatt_start_hdl		= 0;
		def->att_cfg				= 0;
		/* LE Data Length Extension. */
		def->sugg_max_tx_octets		= BLE_SUGG_MAX_TX_OCTETS;
		def->sugg_max_tx_time		= BLE_SUGG_MAX_TX_TIME;
		/* -------------- L2CAP Configuration -----------------*/
		def->max_mtu				= BLE_L2CAP_MAX_MTU;
		def->max_mps				= BLE_L2CAP_MAX_MPS;
		def->max_nb_lecb			= BLE_L2CAP_MAX_LECB_CONN;
		/* -------------- LE Audio Mode Supported -------------*/
		def->audio_cfg				= 0;
		/* -------------- LE PHY Management -------------------*/
		def->tx_pref_phy			= 0;
		def->rx_pref_phy			= 0;
		/* -------------- Miscellaneous 2 ---------------------*/
		def->tx_path_comp			= 0;
		def->rx_path_comp			= 0;
	}
	else
	{
		memcpy(def, conf, sizeof(esble_gapm_set_dev_config_cmd_t));
	}

	lib_conf_env.finish		= finish;
	lib_conf_env.is_busy	= true;

	esble_gapm_reset();
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
static void lib_conf_gapm_cmp(const esble_gapm_cmp_t *evt)
{
	switch(evt->cmd)
	{
		case ESBLE_GAPM_RESET:
		{
			if (evt->status == ESBLE_ERROR_NO_ERROR)
			{
				esble_gapm_set_dev_conf(&lib_conf_env.conf);
				break;
			}

			if (lib_conf_env.finish != NULL)
			{
				lib_conf_env.finish(evt->status);
			}
			break;
		}

		case ESBLE_GAPM_SET_DEV_CONF:
		{
			if (lib_conf_env.finish != NULL)
			{
				lib_conf_env.finish(evt->status);
			}
			break;
		}

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
static void lib_conf_gapc_dev_info_req_ind(const esble_gapc_dev_info_req_ind_t *ind)
{
	esble_gapc_dev_info_cfm_t cfm = {0};
	uint8_t name[BLE_DEV_LOCAL_NAME_LEN] = BLE_DEV_LOCAL_NAME;
	switch(ind->req)
	{
		case ESBLE_GAPC_DEV_NAME:
		{
			cfm.conidx				= ind->conidx;
			cfm.req					= ind->req;
			cfm.info.name.name		= name;
			cfm.info.name.length	= BLE_DEV_LOCAL_NAME_LEN;

			esble_gapc_dev_info_cfm(&cfm);
			break;
		}

		case ESBLE_GAPC_DEV_APPEARANCE:
		{
			cfm.conidx				= ind->conidx;
			cfm.req					= ind->req;
			cfm.info.appearance		= BLE_DEV_LOCAL_APPEARANCE;

			esble_gapc_dev_info_cfm(&cfm);
			break;
		}

		case ESBLE_GAPC_DEV_SLV_PREF_PARAMS:
		{
			cfm.conidx				= ind->conidx;
			cfm.req					= ind->req;
			if(BLE_ATT_SLV_PREF_CON_PAR_EN == 1)
			{
				cfm.info.slv_pref_params.con_intv_min	= BLE_DEV_SLV_PREF_CONN_MIN_INTV;
				cfm.info.slv_pref_params.con_intv_max	= BLE_DEV_SLV_PREF_CONN_MAX_INTV;
				cfm.info.slv_pref_params.slave_latency	= BLE_DEV_SLV_PREF_LATENCY;
				cfm.info.slv_pref_params.conn_timeout	= BLE_DEV_SLV_PREF_SUP_TO;
			}

			esble_gapc_dev_info_cfm(&cfm);
		}

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
static void lib_conf_gapc_set_dev_info_req_ind(const esble_gapc_set_dev_info_req_ind_t *ind)
{
	esble_gapc_set_dev_info_cfm_t cfm = {0};

	cfm.conidx 	= ind->conidx;
	cfm.req 	= ind->req;
	cfm.status 	= GAP_ERR_REJECTED;

	esble_gapc_set_dev_info_cfm(&cfm);

}

lib_hdl_tbl_t lib_conf_tbl[] = 
{
	{ESBLE_GAPM_CMP,					(void (*)(const void *evt))lib_conf_gapm_cmp},
	{ESBLE_GAPC_DEV_INFO_REQ_IND,		(void (*)(const void *evt))lib_conf_gapc_dev_info_req_ind},
	{ESBLE_GAPC_SET_DEV_INFO_REQ_IND,	(void (*)(const void *evt))lib_conf_gapc_set_dev_info_req_ind},
};

BLECB_REGI(lib_conf_tbl);
