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

#include "esble_gapc.h"
#include "esble_gattm.h"
#include "esble_gattc.h"

#include "esprf_ht.h"


static esprf_ht_app_hdl_t esprf_ht_app_hdl;
static esprf_ht_env_t esprf_ht_env;

/*****************************************************************************************************/
/**												数据库定义											**/
/*****************************************************************************************************/

/// Full HTS Database Description - Used to add attributes into the database
static esble_gattm_att_desc_t htpt_att_db[HTS_IDX_NB] =
{
	// Health Thermometer Service Declaration
	[HTS_IDX_SVC]					= {ESBLE_ATT_DECL_PRIMARY_SERVICE, {0}, ESBLE_PERM(RD, ENABLE), 0, 0},

	// Temperature Measurement Characteristic Declaration
	[HTS_IDX_TEMP_MEAS_CHAR]		= {ESBLE_ATT_DECL_CHARACTERISTIC, {0}, ESBLE_PERM(RD, ENABLE), 0, 0},
	// Temperature Measurement Characteristic Value
	[HTS_IDX_TEMP_MEAS_VAL]			= {ESBLE_ATT_CHAR_TEMPERATURE_MEAS, {0}, ESBLE_PERM(IND, ENABLE), ESBLE_PERM(RI, ENABLE), 0},
	// Temperature Measurement Characteristic - Client Characteristic Configuration Descriptor
	[HTS_IDX_TEMP_MEAS_IND_CFG]		= {ESBLE_ATT_DESC_CLIENT_CHAR_CFG, {0}, ESBLE_PERM(RD, ENABLE)|ESBLE_PERM(WRITE_REQ, ENABLE), 0, 0},

	// Temperature Type Characteristic Declaration
	[HTS_IDX_TEMP_TYPE_CHAR]		= {ESBLE_ATT_DECL_CHARACTERISTIC, {0}, ESBLE_PERM(RD, ENABLE), 0, 0},
	// Temperature Type Characteristic Value
	[HTS_IDX_TEMP_TYPE_VAL]			= {ESBLE_ATT_CHAR_TEMPERATURE_TYPE, {0}, ESBLE_PERM(RD, ENABLE), ESBLE_PERM(RI, ENABLE), 0},

	// Intermediate Measurement Characteristic Declaration
	[HTS_IDX_INTERM_TEMP_CHAR]		= {ESBLE_ATT_DECL_CHARACTERISTIC, {0}, ESBLE_PERM(RD, ENABLE), 0, 0},
	// Intermediate Measurement Characteristic Value
	[HTS_IDX_INTERM_TEMP_VAL]		= {ESBLE_ATT_CHAR_INTERMED_TEMPERATURE, {0}, ESBLE_PERM(NTF, ENABLE), ESBLE_PERM(RI, ENABLE), 0},
	// Intermediate Measurement Characteristic - Client Characteristic Configuration Descriptor
	[HTS_IDX_INTERM_TEMP_CFG]		= {ESBLE_ATT_DESC_CLIENT_CHAR_CFG, {0}, ESBLE_PERM(RD, ENABLE)|ESBLE_PERM(WRITE_REQ, ENABLE), 0, 0},

	// Measurement Interval Characteristic Declaration
	[HTS_IDX_MEAS_INTV_CHAR]		= {ESBLE_ATT_DECL_CHARACTERISTIC, {0}, ESBLE_PERM(RD, ENABLE), 0, 0},
	// Measurement Interval Characteristic Value
	[HTS_IDX_MEAS_INTV_VAL]			= {ESBLE_ATT_CHAR_MEAS_INTERVAL, {0}, ESBLE_PERM(RD, ENABLE)| ESBLE_PERM(WRITE_COMMAND, ENABLE), ESBLE_PERM(RI, ENABLE), HTPT_MEAS_INTV_MAX_LEN},
	// Measurement Interval Characteristic - Client Characteristic Configuration Descriptor
	[HTS_IDX_MEAS_INTV_CFG]			= {ESBLE_ATT_DESC_CLIENT_CHAR_CFG, {0}, ESBLE_PERM(RD, ENABLE)|ESBLE_PERM(WRITE_REQ, ENABLE), 0, 0},
	// Measurement Interval Characteristic - Valid Range Descriptor
	[HTS_IDX_MEAS_INTV_VAL_RANGE]	= {ESBLE_ATT_DESC_VALID_RANGE, {0}, ESBLE_PERM(RD, ENABLE), ESBLE_PERM(RI, ENABLE), 0},
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
static uint8_t esprf_ht_update_ntf_ind_cfg(uint8_t conidx, uint8_t cfg, uint16_t valid_val, uint16_t value)
{
	uint8_t status = GAP_ERR_NO_ERROR;

	if((value != valid_val) && (value != PRF_CLI_STOP_NTFIND))
	{
		status = PRF_APP_ERROR;
	}
	else if (value == valid_val)
	{
		esprf_ht_env.ntf_ind |= cfg;
	}
	else
	{
		esprf_ht_env.ntf_ind &= ~cfg;
	}

	if(status == GAP_ERR_NO_ERROR)
	{
		if (esprf_ht_app_hdl.ntf_ind != NULL)
		{
			esprf_ht_app_hdl.ntf_ind(conidx, esprf_ht_env.ntf_ind);
		}
	}

	return (status);
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
static uint8_t esprf_pack_date_time(uint8_t *packed_date, const esprf_date_time_t* date_time)
{
	memcpy(packed_date, &date_time->year, sizeof(uint16_t));
	*(packed_date + 2) = date_time->month;
	*(packed_date + 3) = date_time->day;
	*(packed_date + 4) = date_time->hour;
	*(packed_date + 5) = date_time->min;
	*(packed_date + 6) = date_time->sec;

	return 7;
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
static uint8_t htpt_pack_temp_value(uint8_t *packed_temp, esprf_ht_temp_meas_t temp_meas)
{
	uint8_t cursor = 0;

	*(packed_temp + cursor) = temp_meas.flags;
	cursor += 1;

	memcpy(packed_temp + cursor, &temp_meas.temp, sizeof(uint32_t));
	cursor += 4;

	//Time Flag Set
	if ((temp_meas.flags & HTP_FLAG_TIME) == HTP_FLAG_TIME)
	{
		cursor += esprf_pack_date_time(packed_temp + cursor, &(temp_meas.time_stamp));
	}

	//Type flag set
	if ((temp_meas.flags & HTP_FLAG_TYPE) == HTP_FLAG_TYPE)
	{
		*(packed_temp + cursor) = temp_meas.type;
		cursor += 1;
	}

	//Clear unused packet data
	if(cursor < HTPT_TEMP_MEAS_MAX_LEN)
	{
		memset(packed_temp + cursor, 0, (HTPT_TEMP_MEAS_MAX_LEN - cursor));
	}

	return cursor;
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
static void esprf_ht_gapc_conn_req_ind(const esble_gapc_conn_req_ind_t *evt)
{
	esprf_ht_env.conidx = evt->conidx;
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
static void esprf_ht_gattm_add_svc_rsp_hdl(const esble_gattm_add_svc_rsp_t *evt)
{
	if (evt->status == ESBLE_ERROR_NO_ERROR)
	{
		esprf_ht_env.svc_hdl = evt->start_hdl;
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
static void esprf_ht_gattc_cmp_hdl(const esble_gattc_cmp_evt_t *evt)
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
static void esprf_ht_gattc_write_req_ind_hdl(const esble_gattc_write_req_ind_t *ind)
{
	uint8_t status = ATT_ERR_NO_ERROR;

	// to check if confirmation message should be send
	bool send_cfm = true;

	// retrieve handle information
	uint8_t att_idx = ESPRF_HT_IDX(ind->handle);

	if(ind->length != HTPT_MEAS_INTV_MAX_LEN)
	{
		status = PRF_ERR_UNEXPECTED_LEN;
	}
	else
	{
		switch(att_idx)
		{
			case HTS_IDX_MEAS_INTV_VAL:
			{
				uint16_t meas_intv;
				memcpy(&meas_intv, ind->value, sizeof(uint16_t));

				// check measurement length validity
				if((meas_intv >= esprf_ht_env.meas_intv_min) 
					&& (meas_intv <= esprf_ht_env.meas_intv_max))
				{
					send_cfm = false;
					if (esprf_ht_app_hdl.meas_intv_chg_req_ind != NULL)
					{
						esprf_ht_app_hdl.meas_intv_chg_req_ind(ind->conidx, meas_intv);
					}
				}
				else
				{
					// value not in expected range
					status = HTP_OUT_OF_RANGE_ERR_CODE;
				}
			}break;

			case HTS_IDX_TEMP_MEAS_IND_CFG:
			{
				uint16_t ntf_ind;
				memcpy(&ntf_ind, ind->value, sizeof(uint16_t));
				status = esprf_ht_update_ntf_ind_cfg(ind->conidx, HTPT_CFG_STABLE_MEAS_IND, PRF_CLI_START_IND, ntf_ind);
			}break;

			case HTS_IDX_INTERM_TEMP_CFG:
			{
				uint16_t ntf_ind;
				memcpy(&ntf_ind, ind->value, sizeof(uint16_t));
				status = esprf_ht_update_ntf_ind_cfg(ind->conidx, HTPT_CFG_INTERM_MEAS_NTF, PRF_CLI_START_NTF, ntf_ind);
			}break;

			case HTS_IDX_MEAS_INTV_CFG:
			{
				uint16_t ntf_ind;
				memcpy(&ntf_ind, ind->value, sizeof(uint16_t));
				status = esprf_ht_update_ntf_ind_cfg(ind->conidx, HTPT_CFG_MEAS_INTV_IND, PRF_CLI_START_IND, ntf_ind);
			}break;

			default:
			{
				status = ATT_ERR_REQUEST_NOT_SUPPORTED;
			}break;
		}
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
static void esprf_ht_gattc_read_req_ind_hdl(const esble_gattc_read_req_ind_t *ind)
{
	uint8_t value[HTPT_MEAS_INTV_RANGE_MAX_LEN];
	uint8_t value_size = 0;
	uint8_t status = ATT_ERR_NO_ERROR;

	// retrieve handle information
	uint8_t att_idx = ESPRF_HT_IDX(ind->handle);

	switch(att_idx)
	{
		case HTS_IDX_MEAS_INTV_VAL:
		{
			value_size = HTPT_MEAS_INTV_MAX_LEN;
			memcpy(value, &esprf_ht_env.meas_intv, HTPT_MEAS_INTV_MAX_LEN);
		}break;

		case HTS_IDX_MEAS_INTV_VAL_RANGE:
		{
			value_size = HTPT_MEAS_INTV_RANGE_MAX_LEN;
			memcpy(value, &esprf_ht_env.meas_intv_min, sizeof(uint16_t));
			memcpy(value + sizeof(uint16_t), &esprf_ht_env.meas_intv_max, sizeof(uint16_t));
		}break;

		case HTS_IDX_TEMP_MEAS_IND_CFG:
		{
			value_size = HTPT_IND_NTF_CFG_MAX_LEN;
			uint16_t temp = ((esprf_ht_env.ntf_ind & HTPT_CFG_STABLE_MEAS_IND) != 0) ? PRF_CLI_START_IND : PRF_CLI_STOP_NTFIND;
			memcpy(value, &temp, sizeof(uint16_t));
		}break;

		case HTS_IDX_INTERM_TEMP_CFG:
		{
			value_size = HTPT_IND_NTF_CFG_MAX_LEN;
			uint16_t temp = ((esprf_ht_env.ntf_ind & HTPT_CFG_INTERM_MEAS_NTF) != 0) ? PRF_CLI_START_NTF : PRF_CLI_STOP_NTFIND;
			memcpy(value, &temp, sizeof(uint16_t));
		}break;

		case HTS_IDX_MEAS_INTV_CFG:
		{
			value_size = HTPT_IND_NTF_CFG_MAX_LEN;
			uint16_t temp = ((esprf_ht_env.ntf_ind & HTPT_CFG_MEAS_INTV_IND) != 0) ? PRF_CLI_START_IND : PRF_CLI_STOP_NTFIND;
			memcpy(value, &temp, sizeof(uint16_t));
		}break;

		case HTS_IDX_TEMP_TYPE_VAL:
		{
			value_size	= HTPT_TEMP_TYPE_MAX_LEN;
			value[0]	= esprf_ht_env.temp_type;
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


static esprf_hdl_tbl_t esprf_ht_hdl_tbl[] =
{
	{ESBLE_GAPC_CONN_REQ_IND,	(esprf_hdl)esprf_ht_gapc_conn_req_ind},

	{ESBLE_GATTM_ADD_SVC_RSP,	(esprf_hdl)esprf_ht_gattm_add_svc_rsp_hdl},

	{ESBLE_GATTC_CMP_EVT,		(esprf_hdl)esprf_ht_gattc_cmp_hdl},
	{ESBLE_GATTC_WRITE_REQ_IND,	(esprf_hdl)esprf_ht_gattc_write_req_ind_hdl},
	{ESBLE_GATTC_READ_REQ_IND,	(esprf_hdl)esprf_ht_gattc_read_req_ind_hdl},
};


/*****************************************************************************************************/
/**												Cmd Hdl												**/
/*****************************************************************************************************/

/*************************************************************************************************/
/*
	Function	:
	Description	:	Evt入口
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
void esprf_ht_def_cb_hdl(uint8_t id, const void *evt)
{
	uint32_t i;

	for (i = 0; i < sizeof(esprf_ht_hdl_tbl) / sizeof(esprf_ht_hdl_tbl[0]); i++)
	{
		if (esprf_ht_hdl_tbl[i].id == id)
		{
			esprf_ht_hdl_tbl[i].hdl((const void *)evt);
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
void esprf_ht_init(esprf_ht_app_hdl_t *app_hdl, 
					uint16_t meas_intv_min, uint16_t meas_intv_max,
					uint8_t temp_type)
{
	memset(&esprf_ht_env, 0, sizeof(esprf_ht_env));
	memcpy(&esprf_ht_app_hdl, app_hdl, sizeof(esprf_ht_app_hdl_t));
	esprf_ht_env.meas_intv_min	= meas_intv_min;
	esprf_ht_env.meas_intv_max	= meas_intv_max;
	esprf_ht_env.temp_type		= temp_type;
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
void esprf_ht_add_svc(void)
{
	esble_gattm_add_svc_req_t req = {0};

	req.idx		= 0;

	req.nb_att	= HTS_IDX_NB;
	req.suuid	= ESBLE_ATT_SVC_HEALTH_THERMOM;
	req.atts	= htpt_att_db;

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
int esprf_ht_temp_send(esprf_ht_temp_meas_t temp_meas, bool stable_meas)
{
	uint8_t value[HTPT_TEMP_MEAS_MAX_LEN] = {0};
	esble_gattc_send_evt_cmd_t cmd;

	cmd.conidx	= esprf_ht_env.conidx;
	cmd.handle	= (stable_meas) ? ESPRF_HT_HANDLE(HTS_IDX_TEMP_MEAS_VAL) : ESPRF_HT_HANDLE(HTS_IDX_INTERM_TEMP_VAL);
	cmd.length	= htpt_pack_temp_value(value, temp_meas);
	cmd.value	= value;

	if (stable_meas)
	{
		esble_gattc_send_ind(&cmd);
	}
	else
	{
		esble_gattc_send_notf(&cmd);
	}

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
int esprf_ht_meas_intv_chg_cfm(uint8_t conidx, uint8_t status)
{
	esble_gattc_write_cfm_t cfm;

	cfm.conidx	= conidx;
	cfm.handle	= ESPRF_HT_HANDLE(HTS_IDX_MEAS_INTV_VAL);
	cfm.status	= status;

	esble_gattc_write_cfm(&cfm);

	return 0;
}
