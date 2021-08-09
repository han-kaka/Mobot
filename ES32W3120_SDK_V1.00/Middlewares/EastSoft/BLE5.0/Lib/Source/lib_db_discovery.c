/*************************************************************************************************/
/*
Copyright	:	
File Name	:
Description	:
Author		:	
Version		:
Date		:
History		:	None
Note		:	None
*/
/*************************************************************************************************/

#include <string.h>

#include "lib.h"
#include "sdk_conf.h"
#include "lib_db_discovery.h"

/*****************************************************************************************************/
/**												外部接口											**/
/*****************************************************************************************************/
static uint32_t lib_min(uint32_t a, uint32_t b)
{
    return a < b ? a : b;
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
esble_err lib_db_discovery_init(lib_db_discovery_t *lib_db_discovery, lib_db_discovery_init_t *init)
{
	if((lib_db_discovery == NULL) || (init == NULL))
	{
		return ESBLE_ERROR_INVALID_PARAM;
	}

	lib_db_discovery->conn_idx = ESBLE_INVALID_ACTIDX;
	lib_db_discovery->disc_finished = false;
	lib_db_discovery->srv_cnt = 0;
	memcpy(&lib_db_discovery->cmd, &init->cmd, sizeof(esble_gattc_sdp_svc_disc_cmd_t));
	memcpy(&lib_db_discovery->hdl, &init->hdl, sizeof(lib_db_discovery->hdl));

	memset(&lib_db_discovery->srv_info, 0, sizeof(lib_db_discovery->srv_info));

	switch(init->cmd.operation)
	{
		case ESBLE_GATTC_SDP_DISC_SVC:
			esble_gattc_sdp_disc_svc_cmd(&lib_db_discovery->cmd);
			break;
		case ESBLE_GATTC_SDP_DISC_SVC_ALL:
			esble_gattc_sdp_disc_svc_all_cmd(&lib_db_discovery->cmd);
			break;
		case ESBLE_GATTC_SDP_DISC_CANCEL:
			esble_gattc_sdp_disc_cancel_cmd(&lib_db_discovery->cmd);
			break;
		default:
			break;
	}
	return ESBLE_ERROR_NO_ERROR;
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
static void lib_db_disc_gattc_cmp(const esble_gattc_cmp_evt_t *evt)
{
	switch(evt->cmd)
	{
		case ESBLE_GATTC_SDP_DISC_SVC_ALL_CMD:
		{
			app_db_disc.disc_finished = true;
			if(app_db_disc.hdl.lib_db_discovery_evt != NULL)
			{
				app_db_disc.hdl.lib_db_discovery_evt(evt->conidx, app_db_disc.srv_cnt, &app_db_disc.srv_info[0]);
			}
		}
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
static void lib_gattc_disc_svc_ind(const esble_gattc_disc_svc_ind_t *evt)
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
static void lib_gattc_sdp_svc_ind(const esble_gattc_sdp_svc_ind_t *evt)
{
	uint8_t i,char_cnt;

	i = app_db_disc.srv_cnt;
	char_cnt = lib_min(evt->end_hdl - evt->start_hdl,ESBLE_GATT_MAX_CHAR_CNT);
	app_db_disc.conn_idx = evt->conidx;
	app_db_disc.srv_cnt++;

	lib_gattc_sdp_svc_ind_t *p_sdp_svc_ind;
	p_sdp_svc_ind = &app_db_disc.srv_info[i];
	p_sdp_svc_ind->start_hdl = evt->start_hdl;
	p_sdp_svc_ind->end_hdl = evt->end_hdl;
	p_sdp_svc_ind->uuid_len = evt->uuid_len;
	memcpy(p_sdp_svc_ind->uuid, evt->uuid, evt->uuid_len);

	for(uint8_t j = 0; j < char_cnt; j++)
	{
		p_sdp_svc_ind->info[j].att_type = evt->info[j].att_type;
		switch(evt->info[j].att_type)
		{
			case ESBLE_GATTC_SDP_INC_SVC:
			{
				esble_gattc_sdp_include_svc_t *p_sdp_include_svc_ind;
				p_sdp_include_svc_ind = &p_sdp_svc_ind->info[j].inc_svc;
				p_sdp_include_svc_ind->att_type = ESBLE_GATTC_SDP_INC_SVC;
				p_sdp_include_svc_ind->start_hdl = evt->info[j].inc_svc.start_hdl;
				p_sdp_include_svc_ind->end_hdl = evt->info[j].inc_svc.end_hdl;
				p_sdp_include_svc_ind->uuid_len = evt->info[j].inc_svc.uuid_len;
				memcpy(p_sdp_include_svc_ind->uuid, evt->info[j].inc_svc.uuid, p_sdp_include_svc_ind->uuid_len);
			}
			break;
			case ESBLE_GATTC_SDP_ATT_CHAR:
			{
				esble_gattc_sdp_att_char_t *p_sdp_att_char_ind;
				p_sdp_att_char_ind = &p_sdp_svc_ind->info[j].att_char;
				p_sdp_att_char_ind->att_type = ESBLE_GATTC_SDP_ATT_CHAR;
				p_sdp_att_char_ind->handle = evt->info[j].att_char.handle;
				p_sdp_att_char_ind->prop = evt->info[j].att_char.prop;
			}
				break;
			case ESBLE_GATTC_SDP_ATT_VAL:
			case ESBLE_GATTC_SDP_ATT_DESC:
			{
				esble_gattc_sdp_att_t *p_sdp_att_ind;
				p_sdp_att_ind = &p_sdp_svc_ind->info[j].att;
				p_sdp_att_ind->att_type = evt->info[j].att.att_type;
				p_sdp_att_ind->uuid_len = evt->info[j].att.uuid_len;
				memcpy(p_sdp_att_ind->uuid, evt->info[j].att.uuid, p_sdp_att_ind->uuid_len);
			}
				break;
			default:
				break;
		}
	}
}

 lib_hdl_tbl_t lib_db_disc_tbl[] = 
{
	{ESBLE_GATTC_CMP_EVT,		(void (*)(const void *evt))lib_db_disc_gattc_cmp},
	{ESBLE_GATTC_DISC_SVC_IND,	(void (*)(const void *evt))lib_gattc_disc_svc_ind},
	{ESBLE_GATTC_SDP_SVC_IND,	(void (*)(const void *evt))lib_gattc_sdp_svc_ind},
};

BLECB_REGI(lib_db_disc_tbl);
