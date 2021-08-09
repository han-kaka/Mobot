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

#include "lib.h"
#include "lib_list.h"
#include "lib_adv.h"

LIST(lib_adv_idle_list);
LIST(lib_adv_create_list);
LIST(lib_adv_set_adv_data_list);
LIST(lib_adv_set_scan_rsp_list);

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
static void lib_adv_forward_create(uint8_t status)
{
	lib_adv_t *p, *temp;

	if (status == ESBLE_ERROR_NO_ERROR)
	{
		return;
	}

//	__disable_irq();
	p = lib_list_pop(lib_adv_create_list);
//	__enable_irq();

	temp = lib_list_head(lib_adv_create_list);
	if (temp != NULL)
	{
		esble_gapm_create_adv(&temp->cmd);
	}

	if ((p != NULL) && (p->hdl.lib_adv_create_evt != NULL))
	{
		p->hdl.lib_adv_create_evt(p, status);
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
static void lib_adv_forward_create_ind(const esble_gapm_create_actv_ind_t *ind)
{
	lib_adv_t *p, *temp;
	esble_gapm_adv_data_t cmd;

//	__disable_irq();
	p = lib_list_pop(lib_adv_create_list);
//	__enable_irq();

	temp = lib_list_head(lib_adv_create_list);
	if (temp != NULL)
	{
		esble_gapm_create_adv(&temp->cmd);
	}

	if (p == NULL)
	{
		return;
	}

	p->adv_idx = ind->actv_idx;

	if (p->enc_adv_data_len > 0)
	{
//		__disable_irq();
		lib_list_add(lib_adv_set_adv_data_list, p);
		temp = lib_list_head(lib_adv_set_adv_data_list);
//		__enable_irq();

		if (p == temp)
		{
			cmd.adv_idx				= p->adv_idx;
			cmd.data				= p->enc_adv_data;
			cmd.length				= p->enc_adv_data_len;
			esble_gapm_set_adv_data(&cmd);
		}
	}
	else if (p->enc_scan_rsp_len > 0)
	{
//		__disable_irq();
		lib_list_add(lib_adv_set_scan_rsp_list, p);
		temp = lib_list_head(lib_adv_set_scan_rsp_list);
//		__enable_irq();

		if (p == temp)
		{
			cmd.adv_idx				= p->adv_idx;
			cmd.data				= p->enc_scan_rsp;
			cmd.length				= p->enc_scan_rsp_len;
			esble_gapm_set_scan_rsp_data(&cmd);
		}
	}
	else
	{
//		__disable_irq();
		lib_list_add(lib_adv_idle_list, p);
		if (p->hdl.lib_adv_set_adv_data_evt != NULL)
		{
			p->hdl.lib_adv_set_adv_data_evt(p, ESBLE_ERROR_NO_ERROR);
		}
//		__enable_irq();
	}

	if (p->hdl.lib_adv_create_evt != NULL)
	{
		p->hdl.lib_adv_create_evt(p, ESBLE_ERROR_NO_ERROR);
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
static void lib_adv_forward_set_adv_data(uint8_t status)
{
	lib_adv_t *p, *temp;
	esble_gapm_adv_data_t cmd;

//	__disable_irq();
	p = lib_list_pop(lib_adv_set_adv_data_list);
//	__enable_irq();

	temp = lib_list_head(lib_adv_set_adv_data_list);
	if (temp != NULL)
	{
		cmd.adv_idx				= temp->adv_idx;
		cmd.data				= temp->enc_adv_data;
		cmd.length				= temp->enc_adv_data_len;
		esble_gapm_set_adv_data(&cmd);
	}

	if (p == NULL)
	{
		return;
	}

	p->enc_adv_data_len = 0;

	if (status != ESBLE_ERROR_NO_ERROR)
	{
		if (p->hdl.lib_adv_set_adv_data_evt != NULL)
		{
			p->hdl.lib_adv_set_adv_data_evt(p, status);
		}
		return;
	}

	if (p->enc_scan_rsp_len > 0)
	{
//		__disable_irq();
		lib_list_add(lib_adv_set_scan_rsp_list, p);
		temp = lib_list_head(lib_adv_set_scan_rsp_list);
//		__enable_irq();

		if (p == temp)
		{
			cmd.adv_idx				= p->adv_idx;
			cmd.data				= p->enc_scan_rsp;
			cmd.length				= p->enc_scan_rsp_len;
			esble_gapm_set_scan_rsp_data(&cmd);
		}
	}
	else
	{
//		__disable_irq();
		lib_list_add(lib_adv_idle_list, p);
//		__enable_irq();
		if (p->hdl.lib_adv_set_adv_data_evt != NULL)
		{
			p->hdl.lib_adv_set_adv_data_evt(p, ESBLE_ERROR_NO_ERROR);
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
static void lib_adv_forward_set_scan_rsp(uint8_t status)
{
	lib_adv_t *p, *temp;
	esble_gapm_adv_data_t cmd;

//	__disable_irq();
	p = lib_list_pop(lib_adv_set_scan_rsp_list);
//	__enable_irq();

	temp = lib_list_head(lib_adv_set_scan_rsp_list);
	if (temp != NULL)
	{
		cmd.adv_idx				= temp->adv_idx;
		cmd.data				= temp->enc_adv_data;
		cmd.length				= temp->enc_adv_data_len;
		esble_gapm_set_scan_rsp_data(&cmd);
	}

	if (p == NULL)
	{
		return;
	}

	p->enc_scan_rsp_len = 0;

	if (status != ESBLE_ERROR_NO_ERROR)
	{
		if (p->hdl.lib_adv_set_adv_data_evt != NULL)
		{
			p->hdl.lib_adv_set_adv_data_evt(p, status);
		}
		return;
	}

	if (p->enc_adv_data_len > 0)
	{
//		__disable_irq();
		lib_list_add(lib_adv_set_adv_data_list, p);
		temp = lib_list_head(lib_adv_set_adv_data_list);
//		__enable_irq();

		if (p == temp)
		{
			cmd.adv_idx				= p->adv_idx;
			cmd.data				= p->enc_adv_data;
			cmd.length				= p->enc_adv_data_len;
			esble_gapm_set_adv_data(&cmd);
		}
	}
	else
	{
//		__disable_irq();
		lib_list_add(lib_adv_idle_list, p);
		if (p->hdl.lib_adv_set_adv_data_evt != NULL)
		{
			p->hdl.lib_adv_set_adv_data_evt(p, ESBLE_ERROR_NO_ERROR);
		}
//		__enable_irq();
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
static void lib_adv_gapm_cmp(const esble_gapm_cmp_t *evt)
{
	switch(evt->cmd)
	{
		case ESBLE_GAPM_CREATE_ADV:
		{
			lib_adv_forward_create(evt->status);
			break;
		}

		case ESBLE_GAPM_SET_ADV_DATA:
		{
			lib_adv_forward_set_adv_data(evt->status);
			break;
		}

		case ESBLE_GAPM_SET_SCAN_RSP_DATA:
		{
			lib_adv_forward_set_scan_rsp(evt->status);
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
static void lib_adv_start_ind(const esble_gapm_start_actv_ind_t *ind)
{
	lib_adv_t *p;

	for (p = lib_list_head(lib_adv_idle_list); p != NULL; p = p->next)
	{
		if (p->adv_idx != ind->actv_idx)
		{
			continue;
		}

		if (p->hdl.lib_adv_start_evt != NULL)
		{
			p->hdl.lib_adv_start_evt(p, ind->status);
			return;
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
static void lib_adv_stop_ind(const esble_gapm_stop_actv_ind_t *ind)
{
		lib_adv_t *p;

	for (p = lib_list_head(lib_adv_idle_list); p != NULL; p = p->next)
	{
		if (p->adv_idx != ind->actv_idx)
		{
			continue;
		}

		if (p->hdl.lib_adv_stop_evt != NULL)
		{
			p->hdl.lib_adv_stop_evt(p, ind->reason, ind->per_adv_stop);
			return;
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
esble_err lib_adv_init(lib_adv_t *lib_adv, lib_adv_init_t *init)
{
	esble_err ret;
	lib_adv_t *p;

	if ((lib_adv == NULL) || (init == NULL))
	{
		return ESBLE_ERROR_INVALID_PARAM;
	}

	memset(lib_adv, 0, sizeof(lib_adv_t));

	lib_adv->adv_idx	= ESBLE_INVALID_ACTIDX;
	memcpy(&lib_adv->hdl, &init->hdl, sizeof(lib_adv->hdl));

	memcpy(&lib_adv->cmd, &init->cmd, sizeof(esble_gapm_create_adv_cmd_t));

	if(init->cmd.adv_param.type == ESBLE_GAPM_ADV_TYPE_EXTENDED)
	{
		lib_adv->enc_adv_data_len	= ESBLE_GAP_EXT_ADV_DATA_MAX_LEN;
		lib_adv->enc_scan_rsp_len	= ESBLE_GAP_EXT_ADV_DATA_MAX_LEN;
	}
	else
	{
		lib_adv->enc_adv_data_len	= ESBLE_GAP_ADV_DATA_MAX_LEN;
		lib_adv->enc_scan_rsp_len	= ESBLE_GAP_ADV_DATA_MAX_LEN;
	}

	ret = lib_advdata_encode(&init->adv_data, lib_adv->enc_adv_data, &lib_adv->enc_adv_data_len);
	if (ret != ESBLE_ERROR_NO_ERROR)
	{
		return ret;
	}

	ret = lib_advdata_encode(&init->scan_rsp_data, lib_adv->enc_scan_rsp, &lib_adv->enc_scan_rsp_len);
	if (ret != ESBLE_ERROR_NO_ERROR)
	{
		return ret;
	}

//	__disable_irq();
	lib_list_add(lib_adv_create_list, lib_adv);
	p = lib_list_head(lib_adv_create_list);
//	__enable_irq();

	if (p == lib_adv)
	{
		esble_gapm_create_adv(&p->cmd);
	}

	return ESBLE_ERROR_NO_ERROR;
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
int lib_adv_start(lib_adv_t *lib_adv, uint16_t duration, uint8_t max_adv_evt)
{
	esble_gapm_adv_start_cmd_t cmd;

	if (lib_list_search(lib_adv_idle_list, lib_adv) == false)
	{
		return -1;
	}

	cmd.adv_idx		= lib_adv->adv_idx;
	cmd.duration	= duration;
	cmd.max_adv_evt	= max_adv_evt;
	esble_gapm_adv_start(&cmd);

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
int lib_adv_stop(lib_adv_t *lib_adv)
{
	esble_gapm_adv_stop_cmd_t cmd;

	if (lib_list_search(lib_adv_idle_list, lib_adv) == false)
	{
		return -1;
	}

	cmd.adv_idx = lib_adv->adv_idx;
	esble_gapm_adv_stop(&cmd);

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
esble_err lib_adv_set_data(lib_adv_t *lib_adv, lib_advdata_t *adv_data, lib_advdata_t *scan_rsp_data)
{
	esble_err ret;
	lib_adv_t *p;
	esble_gapm_adv_data_t cmd;

	if (lib_list_search(lib_adv_idle_list, lib_adv) == false)
	{
		return ESBLE_ERROR_INVALID_PARAM;
	}

	if ((adv_data == NULL) && (scan_rsp_data == NULL))
	{
		return ESBLE_ERROR_INVALID_PARAM;
	}

	lib_adv->enc_adv_data_len = sizeof(lib_adv->enc_adv_data);
	lib_adv->enc_scan_rsp_len = sizeof(lib_adv->enc_scan_rsp);

	if (adv_data != NULL)
	{
		ret = lib_advdata_encode(adv_data, lib_adv->enc_adv_data, &lib_adv->enc_adv_data_len);
		if (ret != ESBLE_ERROR_NO_ERROR)
		{
			return ret;
		}
	}

	if (scan_rsp_data != NULL)
	{
		ret = lib_advdata_encode(scan_rsp_data, lib_adv->enc_scan_rsp, &lib_adv->enc_scan_rsp_len);
		if (ret != ESBLE_ERROR_NO_ERROR)
		{
			return ret;
		}
	}

//	__disable_irq();
	lib_list_remove(lib_adv_idle_list, lib_adv);

	if (lib_adv->enc_adv_data_len > 0)
	{
		lib_list_add(lib_adv_set_adv_data_list, lib_adv);
		p = lib_list_head(lib_adv_set_adv_data_list);
		
//		__enable_irq();

		if (p == lib_adv)
		{
			cmd.adv_idx				= p->adv_idx;
			cmd.data				= p->enc_adv_data;
			cmd.length				= p->enc_adv_data_len;
			esble_gapm_set_adv_data(&cmd);
		}
	}
	else
	{
		lib_list_add(lib_adv_set_scan_rsp_list, lib_adv);
		p = lib_list_head(lib_adv_set_scan_rsp_list);
		
//		__enable_irq();

		if (p == lib_adv)
		{
			cmd.adv_idx				= p->adv_idx;
			cmd.data				= p->enc_adv_data;
			cmd.length				= p->enc_adv_data_len;
			esble_gapm_set_scan_rsp_data(&cmd);
		}
	}

	return ESBLE_ERROR_NO_ERROR;
}


lib_hdl_tbl_t lib_adv_tbl[] = 
{
	{ESBLE_GAPM_CMP,				(void (*)(const void *evt))lib_adv_gapm_cmp},
	{ESBLE_GAPM_CREATE_ADV_IND,		(void (*)(const void *evt))lib_adv_forward_create_ind},
	{ESBLE_GAPM_START_ADV_IND,		(void (*)(const void *evt))lib_adv_start_ind},
	{ESBLE_GAPM_STOP_ADV_IND,		(void (*)(const void *evt))lib_adv_stop_ind},
};

BLECB_REGI(lib_adv_tbl);
