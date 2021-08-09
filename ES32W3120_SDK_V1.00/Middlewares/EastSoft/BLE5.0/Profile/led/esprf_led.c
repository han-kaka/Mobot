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
#include "sdk_conf.h"
#if BLE_LED_SERVER
#include <string.h>

#include "esble_gapc.h"
#include "esble_gattm.h"
#include "esble_gattc.h"

#include "lib.h"

#include "esprf_led.h"


static esprf_led_app_hdl_t esprf_led_app_hdl;
static esprf_led_env_t esprf_led_env;

/*****************************************************************************************************/
/**												数据库定义											**/
/*****************************************************************************************************/

/// Full LED Database Description - Used to add attributes into the database
static esble_gattm_att_desc_t led_att_db[LED_IDX_NB] =
{
	// LED Service Declaration
	[LED_IDX_SVC]				= {ESBLE_ATT_DECL_PRIMARY_SERVICE, {0}, ESBLE_PERM(RD, ENABLE), 0, 0},

	// LED Characteristic Declaration
	[LED_IDX_LED_CHAR]			= {ESBLE_ATT_DECL_CHARACTERISTIC, {0}, ESBLE_PERM(RD, ENABLE), 0, 0},
	// LED Characteristic Value
	[LED_IDX_LED_VAL]			= {0, LED_CHAR_UUIND, ESBLE_PERM(RD, ENABLE) | ESBLE_PERM(WRITE_REQ, ENABLE), ESBLE_PERM(RI, ENABLE) | ESBLE_PERM(UUID_LEN, UUID_128), LED_VALUE_MAX_LEN},

	// BUTTON Characteristic Declaration
	[LED_IDX_BUTTON_CHAR]		= {ESBLE_ATT_DECL_CHARACTERISTIC, {0}, ESBLE_PERM(RD, ENABLE), 0, 0},
	// BUTTON Characteristic Value
	[LED_IDX_BUTTON_VAL]		= {0, BUTTON_CHAR_UUIND, ESBLE_PERM(NTF, ENABLE), ESBLE_PERM(RI, ENABLE) | ESBLE_PERM(UUID_LEN, UUID_128), 0},
	// Client Characteristic Configuration Descriptor
	[LED_IDX_BUTTON_IND_CFG]	= {ESBLE_ATT_DESC_CLIENT_CHAR_CFG, {0}, ESBLE_PERM(RD, ENABLE)| ESBLE_PERM(WRITE_REQ, ENABLE), 0, 0},
};


/*****************************************************************************************************/
/**												Internal Hdl										**/
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
static uint8_t esprf_led_update_ntf_ind_cfg(uint8_t conidx, uint8_t cfg, uint16_t valid_val, uint16_t value)
{
	uint8_t status = GAP_ERR_NO_ERROR;

	if((value != valid_val) && (value != PRF_CLI_STOP_NTFIND))
	{
		status = PRF_APP_ERROR;
	}
	else if (value == valid_val)
	{
		esprf_led_env.ntf_ind |= cfg;
	}
	else
	{
		esprf_led_env.ntf_ind &= ~cfg;
	}

	if(status == GAP_ERR_NO_ERROR)
	{
		if (esprf_led_app_hdl.ntf_ind != NULL)
		{
			esprf_led_app_hdl.ntf_ind(conidx, esprf_led_env.ntf_ind);
		}
	}

	return (status);
}


/*****************************************************************************************************/
/**												Cmd Hdl												**/
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
static void esprf_led_add_svc(void)
{
	uint8_t svc_uuid[ESBLE_ATT_UUID_128_LEN] = LED_SERVER_UUID;
	esble_gattm_add_svc_req_t req = {0};

	req.idx		= 0;

	req.nb_att	= LED_IDX_NB;

	ESBLE_PERM_SET(req.perm, SVC_UUID_LEN, ESBLE_PERM_UUID_128);

	memcpy(req.luuid, svc_uuid, ESBLE_ATT_UUID_128_LEN);
	req.atts	= led_att_db;

	esble_gattm_add_svc_req(&req);
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
void esprf_led_init(esprf_led_app_hdl_t *app_hdl, uint8_t led_init_value)
{
	memset(&esprf_led_env, 0, sizeof(esprf_led_env));
	esprf_led_env.led_value = led_init_value;

	memcpy(&esprf_led_app_hdl, app_hdl, sizeof(esprf_led_app_hdl));
	esprf_led_add_svc();
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
int esprf_led_button_send(uint8_t button_value)
{
	uint8_t value[LED_VALUE_MAX_LEN] = {0};
	esble_gattc_send_evt_cmd_t cmd;

	if ((esprf_led_env.ntf_ind & LED_CFG_BUTTON_NTF) == 0)
	{
		return 0;
	}

	cmd.conidx	= esprf_led_env.conidx;
	cmd.handle	= ESPRF_LED_HANDLE(LED_IDX_BUTTON_VAL);
	cmd.length	= LED_VALUE_MAX_LEN;
	value[0]	= button_value;
	cmd.value	= value;

	esble_gattc_send_notf(&cmd);
	return 0;
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
int esprf_led_write_req_cfm(uint8_t conidx, uint8_t status, uint8_t new_value)
{
	esble_gattc_write_cfm_t cfm;

	cfm.conidx	= conidx;
	cfm.handle	= ESPRF_LED_HANDLE(LED_IDX_LED_VAL);
	cfm.status	= status;

	if (status == ATT_ERR_NO_ERROR)
	{
		esprf_led_env.led_value = new_value;
	}

	esble_gattc_write_cfm(&cfm);

	return 0;
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
static void esprf_led_gapc_conn_req_ind(const esble_gapc_conn_req_ind_t *evt)
{
	esprf_led_env.conidx = evt->conidx;
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
static void esprf_led_gattm_add_svc_rsp_hdl(const esble_gattm_add_svc_rsp_t *evt)
{
	uint8_t svc_uuid[ESBLE_ATT_UUID_128_LEN] = LED_SERVER_UUID;

	if(memcmp(evt->uuid, svc_uuid, evt->uuid_len) == 0)
	{
		if (evt->status == ESBLE_ERROR_NO_ERROR)
		{
			esprf_led_env.svc_hdl = evt->start_hdl;
			esprf_led_env.end_hdl = evt->start_hdl + LED_IDX_NB - 1;
		}

		if (esprf_led_app_hdl.add_svc != NULL)
		{
			esprf_led_app_hdl.add_svc(evt->status);
		}
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
static void esprf_led_gattc_cmp_hdl(const esble_gattc_cmp_evt_t *evt)
{
	/* add multi conn */
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
static void esprf_led_gattc_write_req_ind_hdl(const esble_gattc_write_req_ind_t *ind)
{
	uint8_t led_value;
	uint16_t ntf_ind;
	uint8_t status = ATT_ERR_NO_ERROR;

	// to check if message should be handled
	if((ind->handle < esprf_led_env.svc_hdl) || (ind->handle > esprf_led_env.end_hdl))
    {
        return;
    }

	// to check if confirmation message should be send
	bool send_cfm = true;

	// retrieve handle information
	uint8_t att_idx = ESPRF_LED_IDX(ind->handle);

	switch(att_idx)
	{
		case LED_IDX_LED_VAL:
		{
			if(ind->length != LED_VALUE_MAX_LEN)
			{
				status = PRF_ERR_UNEXPECTED_LEN;
				break;
			}

			led_value = ind->value[0];
			if (led_value == esprf_led_env.led_value)
			{
				break;
			}
			
			send_cfm = false;
			if (esprf_led_app_hdl.led_write_req != NULL)
			{
				esprf_led_app_hdl.led_write_req(ind->conidx, ind->value[0]);
			}

		}break;

		case LED_IDX_BUTTON_IND_CFG:
		{
			if(ind->length != LED_IND_NTF_CFG_MAX_LEN)
			{
				status = PRF_ERR_UNEXPECTED_LEN;
				break;
			}

			memcpy(&ntf_ind, ind->value, sizeof(uint16_t));
			status = esprf_led_update_ntf_ind_cfg(ind->conidx, LED_CFG_BUTTON_NTF, PRF_CLI_START_NTF, ntf_ind);
		}break;
	}


	if(send_cfm)
	{
		//Send write response
		esble_gattc_write_cfm_t cfm;

		cfm.conidx	= ind->conidx;
		cfm.handle	= ind->handle;
		cfm.status	= status;
		esble_gattc_write_cfm(&cfm);
	}

	return;
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
static void esprf_led_gattc_read_req_ind_hdl(const esble_gattc_read_req_ind_t *ind)
{
	uint8_t value[LED_IND_NTF_CFG_MAX_LEN];
	uint8_t value_size = 0;
	uint8_t status = ATT_ERR_NO_ERROR;

	// to check if message should be handled
	if((ind->handle < esprf_led_env.svc_hdl) || (ind->handle > esprf_led_env.end_hdl))
    {
        return;
    }

	// retrieve handle information
	uint8_t att_idx = ESPRF_LED_IDX(ind->handle);

	switch(att_idx)
	{
		case LED_IDX_LED_VAL:
		{
			value_size	= LED_VALUE_MAX_LEN;
			value[0]	= esprf_led_env.led_value;
		}break;

		case LED_IDX_BUTTON_IND_CFG:
		{
			value_size = LED_IND_NTF_CFG_MAX_LEN;
			uint16_t temp = ((esprf_led_env.ntf_ind & LED_CFG_BUTTON_NTF) != 0) ? PRF_CLI_START_NTF : PRF_CLI_STOP_NTFIND;
			memcpy(value, &temp, sizeof(uint16_t));
		}break;

		default:
		{
			status = ATT_ERR_REQUEST_NOT_SUPPORTED;
		}break;
	}

	// Send data to peer device
	esble_gattc_read_cfm_t cfm;
	cfm.conidx	= ind->conidx;
	cfm.handle	= ind->handle;
	cfm.status	= status;
	cfm.length	= value_size;
	cfm.value	= value;

	esble_gattc_read_cfm(&cfm);
}


lib_hdl_tbl_t esprf_led_hdl_tbl[] =
{
	{ESBLE_GAPC_CONN_REQ_IND,	(esprf_hdl)esprf_led_gapc_conn_req_ind},

	{ESBLE_GATTM_ADD_SVC_RSP,	(esprf_hdl)esprf_led_gattm_add_svc_rsp_hdl},

	{ESBLE_GATTC_CMP_EVT,		(esprf_hdl)esprf_led_gattc_cmp_hdl},
	{ESBLE_GATTC_WRITE_REQ_IND,	(esprf_hdl)esprf_led_gattc_write_req_ind_hdl},
	{ESBLE_GATTC_READ_REQ_IND,	(esprf_hdl)esprf_led_gattc_read_req_ind_hdl},
};

BLECB_REGI(esprf_led_hdl_tbl);
#endif //BLE_LED_SERVER
