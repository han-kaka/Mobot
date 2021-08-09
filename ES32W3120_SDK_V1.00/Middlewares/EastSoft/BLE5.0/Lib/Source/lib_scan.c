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
#include "lib_scan.h"

/*****************************************************************************************************/
/**												外部接口											**/
/*****************************************************************************************************/
#if (BLE_SCAN_NAME_CNT > 0)
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
static bool lib_adv_name_compare(esble_gapm_ext_adv_report_ind_t const * p_adv_report,
                             lib_scan_t     const * const p_scan_ctx)
{
    lib_ble_scan_name_filter_t const * p_name_filter = &p_scan_ctx->scan_filters.name_filter;
    uint8_t                            counter       =
        p_scan_ctx->scan_filters.name_filter.name_cnt;
    uint8_t  index;
    uint8_t const *p_parsed_name;
	uint16_t name_offset,data_len,name_len;

	name_len 	= 0;
	name_offset = 0;

    data_len = p_adv_report->length;
	name_len = lib_advdata_search(p_adv_report->data,
                                  data_len, &name_offset,
                                  ESBLE_GAP_AD_TYPE_COMPLETE_NAME);

	if( (name_offset != 0) && (name_len != 0))
	{
		p_parsed_name = &p_adv_report->data[name_offset];

		// Compare the name found with the name filter.
		for (index = 0; index < counter; index++)
		{
			if( (name_len == strlen(p_name_filter->target_name[index])) 
				&& (memcmp(&p_name_filter->target_name[index], p_parsed_name, name_len) == 0))
			{
				return true;
			}
		}
	}

    return false;
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
esble_err lib_ble_scan_name_filter_add(lib_scan_t * const p_scan_ctx,
                                               char           const * p_name)
{
    uint8_t   index;
    uint8_t * counter  = &p_scan_ctx->scan_filters.name_filter.name_cnt;
    uint8_t   name_len = strlen(p_name);

    // Check the name length.
    if ((name_len == 0) || (name_len > BLE_SCAN_NAME_MAX_LEN))
    {
        return ESBLE_ERROR_DATA_SIZE;
    }

    // If no memory for filter.
    if (*counter >= BLE_SCAN_NAME_CNT)
    {
        return ESBLE_ERROR_NO_MEM;
    }

    // Check for duplicated filter.
    for (index = 0; index < BLE_SCAN_NAME_CNT; index++)
    {
        if (!strcmp(p_scan_ctx->scan_filters.name_filter.target_name[index], p_name))
        {
            return ESBLE_ERROR_NO_ERROR;
        }
    }

    // Add name to filter.
    memcpy(p_scan_ctx->scan_filters.name_filter.target_name[(*counter)++],
           p_name,
           strlen(p_name));

    return ESBLE_ERROR_NO_ERROR;
}


#endif // BLE_SCAN_NAME_CNT

#if (BLE_SCAN_UUID_CNT > 0)
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
static bool adv_uuid_compare(esble_gapm_ext_adv_report_ind_t const * const p_adv_report,
                             lib_scan_t           const * const p_scan_ctx)
{
    lib_ble_scan_uuid_filter_t const * p_uuid_filter    = &p_scan_ctx->scan_filters.uuid_filter;
    bool const                         all_filters_mode = p_scan_ctx->scan_filters.all_filters_mode;
    uint8_t const                      counter          =
        p_scan_ctx->scan_filters.uuid_filter.uuid_cnt;
    uint8_t  index;
    uint16_t data_len,uuid_offset,uuid_len,uuid_len_compared;
    uint8_t  ad_type[N_AD_TYPES],uuid_match_cnt = 0;
	uint8_t const * p_parsed_uuid;
	uint8_t	const *uuid_compared;

	uuid_len 	= 0;

    data_len = p_adv_report->length;

    for (index = 0; index < counter; index++)
    {
		switch(p_uuid_filter->uuid[index].uuid_len)
		{
			case ESBLE_ATT_UUID_16_LEN:
				ad_type[0] =  ESBLE_GAP_AD_TYPE_MORE_16_BIT_UUID;
				ad_type[1] = ESBLE_GAP_AD_TYPE_COMPLETE_LIST_16_BIT_UUID;
				break;
			case ESBLE_ATT_UUID_32_LEN:
				ad_type[0] =  ESBLE_GAP_AD_TYPE_MORE_32_BIT_UUID;
				ad_type[1] = ESBLE_GAP_AD_TYPE_COMPLETE_LIST_32_BIT_UUID;
				break;
			case ESBLE_ATT_UUID_128_LEN:
				ad_type[0] =  ESBLE_GAP_AD_TYPE_MORE_128_BIT_UUID;
				ad_type[1] = ESBLE_GAP_AD_TYPE_COMPLETE_LIST_128_BIT_UUID;
				break;
			default:
			return false;
		}
		for (uint8_t i = 0; (i < N_AD_TYPES) && (uuid_len == 0); i++)
		{
          	uuid_offset = 0;
			uuid_len = lib_advdata_search(p_adv_report->data,
									  data_len,
									  &uuid_offset,
									  ad_type[i]);
			if(uuid_len != 0)
			{
				break;
			}
		}
		if(uuid_len == 0)
		{
			return false;
		}
		p_parsed_uuid 		= &p_adv_report->data[uuid_offset];
		uuid_compared 		= p_uuid_filter->uuid[index].uuid;
		uuid_len_compared 	= p_uuid_filter->uuid[index].uuid_len;

		// Verify if any UUID matches the given UUID.
		for (uint16_t list_offset = 0; list_offset < uuid_len; list_offset += p_uuid_filter->uuid[index].uuid_len)
		{
			if (memcmp(&p_parsed_uuid[list_offset], uuid_compared, uuid_len_compared) == 0)
			{
				uuid_match_cnt++;
				// In the normal filter mode, only one UUID is needed to match.
				if (!all_filters_mode)
				{
					return true;
				}
			}
			else if (all_filters_mode)
			{
				return false;
			}
		}
    }
    // In the multifilter mode, all UUIDs must be found in the advertisement packets.
    if ((all_filters_mode && (uuid_match_cnt == counter)) ||
        ((!all_filters_mode) && (uuid_match_cnt > 0)))
    {
        return true;
    }

    return false;
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
esble_err lib_ble_scan_uuid_filter_add(lib_scan_t * const p_scan_ctx,
                                               lib_ble_uuid_t     const * p_uuid)
{
    lib_ble_uuid_t * p_uuid_filter = p_scan_ctx->scan_filters.uuid_filter.uuid;
    uint8_t    * p_counter     = &p_scan_ctx->scan_filters.uuid_filter.uuid_cnt;
    uint8_t      index;

    // If no memory.
    if (*p_counter >= BLE_SCAN_UUID_CNT)
    {
        return ESBLE_ERROR_NO_MEM;
    }

    // Check for duplicated filter.
    for (index = 0; index < BLE_SCAN_UUID_CNT; index++)
    {
        if ((p_uuid_filter[index].uuid_len == p_uuid->uuid_len) 
			&& (memcmp(p_uuid_filter[index].uuid, p_uuid->uuid, p_uuid->uuid_len) == 0))
        {
            return ESBLE_ERROR_NO_ERROR;
        }
    }

    // Add UUID to the filter.
    p_uuid_filter[(*p_counter)++] = *p_uuid;

    return ESBLE_ERROR_NO_ERROR;
}

#endif // NRF_BLE_SCAN_UUID_CNT

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
esble_err lib_ble_scan_filters_enable(lib_scan_t * const p_scan_ctx,
										uint8_t			 filter_mode)
{
	if(p_scan_ctx == NULL)
	{
		return ESBLE_ERROR_INVALID_PARAM;
	}
	
	//check filter_mode is correct or not
	if((!(filter_mode & LIB_BLE_SCAN_NAME_FILTER)) && 
		(!(filter_mode & LIB_BLE_SCAN_UUID_FILTER)))
	{
		return ESBLE_ERROR_INVALID_PARAM;
	}

	#if (BLE_SCAN_NAME_CNT > 0)
	if(filter_mode & LIB_BLE_SCAN_NAME_FILTER)
	{
		p_scan_ctx->scan_filters.name_filter.name_filter_enabled = true;
	}
	#endif //BLE_SCAN_NAME_CNT > 0

	#if (BLE_SCAN_UUID_CNT > 0)
	if(filter_mode & LIB_BLE_SCAN_UUID_FILTER)
	{
		p_scan_ctx->scan_filters.uuid_filter.uuid_filter_enabled = true;
	}
	#endif //BLE_SCAN_UUID_CNT > 0

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
esble_err lib_ble_scan_filters_disable(lib_scan_t * const p_scan_ctx,
										uint8_t			 filter_mode)
{
	if(p_scan_ctx == NULL)
	{
		return ESBLE_ERROR_INVALID_PARAM;
	}

	//check filter_mode is correct or not
	if((!(filter_mode & LIB_BLE_SCAN_NAME_FILTER)) && 
		(!(filter_mode & LIB_BLE_SCAN_UUID_FILTER)))
	{
		return ESBLE_ERROR_INVALID_PARAM;
	}

	#if (BLE_SCAN_NAME_CNT > 0)
	if(filter_mode & LIB_BLE_SCAN_NAME_FILTER)
	{
		p_scan_ctx->scan_filters.name_filter.name_filter_enabled = false;
	}
	#endif //BLE_SCAN_NAME_CNT > 0

	#if (BLE_SCAN_UUID_CNT > 0)
	if(filter_mode & LIB_BLE_SCAN_UUID_FILTER)
	{
		p_scan_ctx->scan_filters.uuid_filter.uuid_filter_enabled = false;
	}
	#endif //BLE_SCAN_UUID_CNT > 0

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
void lib_ble_scan_filters_set_match_all_mode(lib_scan_t * const p_scan_ctx, bool match_all)
{
	p_scan_ctx->scan_filters.all_filters_mode = match_all;
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
void lib_ble_scan_set_match_conn_mode(lib_scan_t * const p_scan_ctx, bool match_conn)
{
	p_scan_ctx->connect_if_match = match_conn;
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
static bool is_whitelist_used(lib_scan_t const * const p_scan_ctx)
{
	if((p_scan_ctx->scan_param.type == ESBLE_GAPM_SCAN_TYPE_SEL_OBSERVER) ||
		(p_scan_ctx->scan_param.type == ESBLE_GAPM_SCAN_TYPE_SEL_CONN_DISC))
	{
		return true;
	}

	return false;
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
esble_err lib_scan_init(lib_scan_t *lib_scan, lib_scan_init_t *init)
{

	if ((lib_scan == NULL) || (init == NULL))
	{
		return ESBLE_ERROR_INVALID_PARAM;
	}


	lib_scan->scan_idx	= 0xFF;
	memcpy(&lib_scan->hdl, &init->hdl, sizeof(lib_scan->hdl));

	memcpy(&lib_scan->cmd, &init->cmd, sizeof(esble_gapm_create_scan_cmd_t));

	memcpy(&lib_scan->scan_param, &init->scan_param, sizeof(esble_gapm_scan_param_t));

	esble_gapm_create_scan(&lib_scan->cmd);

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
int lib_scan_start(lib_scan_t *lib_scan)
{
	esble_gapm_scan_start_cmd_t cmd;

	cmd.scan_idx		= lib_scan->scan_idx;
	cmd.scan_param = lib_scan->scan_param;
	esble_gapm_scan_start(&cmd);

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
int lib_scan_stop(lib_scan_t *lib_scan)
{
	esble_gapm_scan_stop_cmd_t cmd;

	cmd.scan_idx = lib_scan->scan_idx;
	esble_gapm_scan_stop(&cmd);

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
static void lib_scan_forward_create_ind(const esble_gapm_create_actv_ind_t *ind)
{
	lib_scan_t *p;
	p = &app_scan;

	p->scan_idx = ind->actv_idx;

	if (p->hdl.lib_scan_create_evt != NULL)
	{
		p->hdl.lib_scan_create_evt(p, ESBLE_ERROR_NO_ERROR);
	}
	lib_scan_start(p);
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
static void lib_scan_gapm_cmp(const esble_gapm_cmp_t *evt)
{
	switch(evt->cmd)
	{
		case ESBLE_GAPM_CREATE_SCAN:
		{
			if(evt->status != ESBLE_ERROR_NO_ERROR)
			{
			}
			break;
		}
		case ESBLE_GAPM_SCAN_STOP:
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
static void lib_scan_start_ind(const esble_gapm_start_actv_ind_t *ind)
{
	lib_scan_t *p;
	p = &app_scan;
	if (p->hdl.lib_scan_start_evt != NULL)
	{
		p->hdl.lib_scan_start_evt(p, ind->status);
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
static void lib_scan_stop_ind(const esble_gapm_stop_actv_ind_t *ind)
{
	lib_scan_t *p;
	p = &app_scan;

	if (p->hdl.lib_scan_stop_evt != NULL)
	{
		p->hdl.lib_scan_stop_evt(p, ind->reason);
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
static void lib_ext_adv_report_ind(const esble_gapm_ext_adv_report_ind_t *ind)
{
	lib_gapm_ext_adv_report_ind_t app_adv_report;

	#if (BLE_SCAN_FILTER_ENABLE == 1)
	uint8_t filter_cnt 			= 0;
	uint8_t match_filter_cnt 	= 0;
	#endif //BLE_SCAN_FILTER_ENABLE

	memset(&app_adv_report, 0, sizeof(app_adv_report));
	app_adv_report.ind = ind;

	//if use whitelist, do not check the filters and return
	if(is_whitelist_used(&app_scan))
	{
		app_adv_report.use_whitelist = true;
		app_scan.hdl.lib_adv_report_ind(&app_adv_report);
		return;
	}

	#if (BLE_SCAN_FILTER_ENABLE == 1)
	bool const all_filter_mode	= app_scan.scan_filters.all_filters_mode;
	bool is_filter_matched		= false;

	#if (BLE_SCAN_NAME_CNT > 0)
	bool const name_filter_enabled = app_scan.scan_filters.name_filter.name_filter_enabled;
	//check name filter
	if(name_filter_enabled)
	{
		filter_cnt++;
		if(lib_adv_name_compare(ind, &app_scan))
		{
			match_filter_cnt++;

			app_adv_report.filter_match.name_filter_match = true;
			is_filter_matched = true;
		}
	}
	#endif //BLE_SCAN_NAME_CNT

	#if (BLE_SCAN_UUID_CNT > 0)
	bool const uuid_filter_enabled = app_scan.scan_filters.uuid_filter.uuid_filter_enabled;
	//check uuid filter
	if(uuid_filter_enabled)
	{
		filter_cnt++;
		if(adv_uuid_compare(ind, &app_scan))
		{
			match_filter_cnt++;

			app_adv_report.filter_match.uuid_filter_match = true;
			is_filter_matched = true;
		}
	}
	#endif //BLE_SCAN_UUID_CNT

	if(((all_filter_mode) && (match_filter_cnt == filter_cnt)) ||
		((!all_filter_mode) && is_filter_matched))
	{
		app_adv_report.is_filter_match = true;
	}
	else
	{
		app_adv_report.is_filter_match = false;
	}

	app_scan.hdl.lib_adv_report_ind(&app_adv_report);
	return;

	#endif //BLE_SCAN_FILTER_ENABLE
}


lib_hdl_tbl_t lib_scan_tbl[] = 
{
	{ESBLE_GAPM_CMP,				(void (*)(const void *evt))lib_scan_gapm_cmp},
	{ESBLE_GAPM_CREATE_SCAN_IND,	(void (*)(const void *evt))lib_scan_forward_create_ind},
	{ESBLE_GAPM_START_SCAN_IND,		(void (*)(const void *evt))lib_scan_start_ind},
	{ESBLE_GAPM_STOP_SCAN_IND,		(void (*)(const void *evt))lib_scan_stop_ind},
	{ESBLE_GAPM_EXT_ADV_REPORT_IND,	(void (*)(const void *evt))lib_ext_adv_report_ind},
};

BLECB_REGI(lib_scan_tbl);
