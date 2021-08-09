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
#include "lib_init.h"

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
esble_err lib_init_init(lib_init_t *lib_init, lib_init_init_t *init, bool creat)
{

	if ((lib_init == NULL) || (init == NULL))
	{
		return ESBLE_ERROR_INVALID_PARAM;
	}


	lib_init->init_idx	= 0xFF;
	memcpy(&lib_init->hdl, &init->hdl, sizeof(lib_init->hdl));

	memcpy(&lib_init->cmd, &init->cmd, sizeof(esble_gapm_create_init_cmd_t));

	memcpy(&lib_init->init_param, &init->init_param, sizeof(esble_gapm_init_param_t));

	if(creat == true)
	{
		esble_gapm_create_init(&lib_init->cmd);
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
int lib_init_start(lib_init_t *lib_init)
{
	esble_gapm_init_start_cmd_t cmd;

	cmd.init_idx	= lib_init->init_idx;
	cmd.init_param 	= lib_init->init_param;
	esble_gapm_init_start(&cmd);

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
int lib_init_stop(lib_init_t *lib_init)
{
	esble_gapm_init_stop_cmd_t cmd;

	cmd.init_idx = lib_init->init_idx;
	esble_gapm_init_stop(&cmd);

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
static void lib_init_forward_create_ind(const esble_gapm_create_actv_ind_t *ind)
{
	lib_init_t *p;
	p = &app_init;

	p->init_idx = ind->actv_idx;

	if (p->hdl.lib_init_create_evt != NULL)
	{
		p->hdl.lib_init_create_evt(p, ESBLE_ERROR_NO_ERROR);
	}
	lib_init_start(p);
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
static void lib_init_gapm_cmp(const esble_gapm_cmp_t *evt)
{
	switch(evt->cmd)
	{
		case ESBLE_GAPM_CREATE_INIT:
		{
			if(evt->status != ESBLE_ERROR_NO_ERROR)
			{
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
static void lib_init_start_ind(const esble_gapm_start_actv_ind_t *ind)
{
	lib_init_t *p;
	p = &app_init;
	if (p->hdl.lib_init_start_evt != NULL)
	{
		p->hdl.lib_init_start_evt(p, ind->status);
		return;
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
static void lib_init_stop_ind(const esble_gapm_stop_actv_ind_t *ind)
{
	lib_init_t *p;
	p = &app_init;

	if (p->hdl.lib_init_stop_evt != NULL)
	{
		p->hdl.lib_init_stop_evt(p, ind->reason);
		return;
	}
}

lib_hdl_tbl_t lib_init_tbl[] = 
{
	{ESBLE_GAPM_CMP,				(void (*)(const void *evt))lib_init_gapm_cmp},
	{ESBLE_GAPM_CREATE_INIT_IND,	(void (*)(const void *evt))lib_init_forward_create_ind},
	{ESBLE_GAPM_START_INIT_IND,		(void (*)(const void *evt))lib_init_start_ind},
	{ESBLE_GAPM_STOP_INIT_IND,		(void (*)(const void *evt))lib_init_stop_ind},
};

BLECB_REGI(lib_init_tbl);
