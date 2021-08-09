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
#if BLE_LED_CLIENT
#include <string.h>

#include "esble_gapc.h"
#include "esble_gattm.h"
#include "esble_gattc.h"

#include "lib.h"

#include "esprf_led_c.h"

esprf_led_c_env_t g_esprf_led_c_env = {.conidx = ESBLE_INVALID_ACTIDX};

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
void esprf_led_c_init(esprf_led_c_app_hdl_t *led_c_app_init)
{
	memcpy(&g_esprf_led_c_env.hdl, led_c_app_init, sizeof(g_esprf_led_c_env.hdl));
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
void esprf_led_c_on_db_disc_handler(uint8_t conn_idx, lib_gattc_sdp_svc_ind_t *srv_ind)
{
	g_esprf_led_c_env.conidx 	= conn_idx;
	g_esprf_led_c_env.evt_type 	= ESPRF_LED_C_EVT_DISCOVERY_COMPLETE;

	g_esprf_led_c_env.svc_start_hdl = srv_ind->start_hdl;
	g_esprf_led_c_env.svc_end_hdl	= srv_ind->end_hdl;

	g_esprf_led_c_env.peer_db.led_value_handle 		= srv_ind->start_hdl + LED_IDX_LED_VAL;
	g_esprf_led_c_env.peer_db.button_value_handle 	= srv_ind->start_hdl + LED_IDX_BUTTON_VAL;
	g_esprf_led_c_env.peer_db.button_cccd_handle 	= srv_ind->start_hdl + LED_IDX_BUTTON_IND_CFG;

	if(g_esprf_led_c_env.hdl.evt_handler)
	{
		g_esprf_led_c_env.hdl.evt_handler(&g_esprf_led_c_env);
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
	if(evt->conidx == g_esprf_led_c_env.conidx)
	{
		switch(evt->cmd)
		{
			case ESBLE_GATTC_WRITE_CMD:
			if(evt->status != ATT_ERR_NO_ERROR)
			{
				if(g_esprf_led_c_env.hdl.err_handler)
				{
					g_esprf_led_c_env.hdl.err_handler(evt->status);
				}
			}
				break;
			default:
				break;
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
static void esprf_led_gattc_notify_hdl(const esble_gattc_event_ind_t *evt)
{
	if(evt->handle == g_esprf_led_c_env.peer_db.button_value_handle)
	{
		g_esprf_led_c_env.conidx = evt->conidx;
		g_esprf_led_c_env.evt_type = ESPRF_LED_C_EVT_BUTTON_NOTIFICATION;
		g_esprf_led_c_env.led_value.button_value = evt->value[0];
		if(g_esprf_led_c_env.hdl.evt_handler)
		{
			g_esprf_led_c_env.hdl.evt_handler(&g_esprf_led_c_env);
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
static void esprf_led_gattc_read_ind(const esble_gattc_read_ind_t *evt)
{
	if((evt->conidx == g_esprf_led_c_env.conidx) && (evt->handle == g_esprf_led_c_env.peer_db.led_value_handle))
	{
	}
}

lib_hdl_tbl_t esprf_led_c_hdl_tbl[] =
{
	{ESBLE_GATTC_CMP_EVT,		(esprf_led_c_hdl)esprf_led_gattc_cmp_hdl},
	{ESBLE_GATTC_EVENT_IND,		(esprf_led_c_hdl)esprf_led_gattc_notify_hdl},
	{ESBLE_GATTC_READ_IND,		(esprf_led_c_hdl)esprf_led_gattc_read_ind},

};

BLECB_REGI(esprf_led_c_hdl_tbl);
#endif //BLE_LED_CLIENT

