#ifndef _LIB_SCAN_H_
#define _LIB_SCAN_H_

#include <stdint.h>

#include "esble_gapm.h"
#include "lib_advdata.h"
#include "sdk_conf.h"
#include "esble_att.h"


#define N_AD_TYPES									2

#define LIB_BLE_SCAN_NAME_FILTER       (0x01) /* Filters the device name. */
#define LIB_BLE_SCAN_UUID_FILTER       (0x02) /* Filters the UUID. */
#define LIB_BLE_SCAN_ALL_FILTER        (0x03) /* Uses the combination of all filters. */

typedef struct
{
	uint8_t		uuid_len;
	uint8_t		uuid[ESBLE_ATT_UUID_128_LEN];
} lib_ble_uuid_t;

#if (BLE_SCAN_FILTER_ENABLE == 1)
#if (BLE_SCAN_NAME_CNT > 0)
typedef struct
{
	char    target_name[BLE_SCAN_NAME_CNT][BLE_SCAN_NAME_MAX_LEN]; /* Names that the main application will scan for, and that will be advertised by the peripherals. */
	uint8_t name_cnt;                                              /* Name filter counter. */
	bool    name_filter_enabled;                                   /* Flag to inform about enabling or disabling this filter. */
} lib_ble_scan_name_filter_t;
#endif

#if (BLE_SCAN_UUID_CNT > 0)
typedef struct
{
	lib_ble_uuid_t uuid[BLE_SCAN_UUID_CNT]; /**< UUIDs that the main application will scan for, and that will be advertised by the peripherals. */
	uint8_t    uuid_cnt;                    /**< UUID filter counter. */
	bool       uuid_filter_enabled;         /**< Flag to inform about enabling or disabling this filter. */
} lib_ble_scan_uuid_filter_t;
#endif

typedef struct
{
#if (BLE_SCAN_NAME_CNT > 0)
	lib_ble_scan_name_filter_t name_filter; /**< Name filter data. */
#endif
#if (BLE_SCAN_UUID_CNT > 0)
	lib_ble_scan_uuid_filter_t uuid_filter; /**< UUID filter data. */
#endif
	bool all_filters_mode;                              /**< Filter mode. If true, all set filters must be matched to generate an event.*/
} lib_ble_scan_filters_t;
#endif // BLE_SCAN_FILTER_ENABLE

typedef struct
{
    uint8_t name_filter_match       : 1; /**< Set to 1 if name filter is matched. */
    uint8_t uuid_filter_match       : 1; /**< Set to 1 if uuid filter is matched. */
} lib_ble_scan_filter_match;

typedef struct _lib_gapm_ext_adv_report_ind_t 
{
	const esble_gapm_ext_adv_report_ind_t	*ind;
	lib_ble_scan_filter_match				filter_match;
	bool									use_whitelist;
	bool									is_filter_match;
}lib_gapm_ext_adv_report_ind_t;

typedef struct _lib_scan_t
{
	struct _lib_scan_t				*next;

	uint8_t							scan_idx;

#if (BLE_SCAN_FILTER_ENABLE == 1)
	lib_ble_scan_filters_t			scan_filters;
#endif
	bool							connect_if_match;

	esble_gapm_create_scan_cmd_t	cmd;
	esble_gapm_scan_param_t			scan_param;

	struct
	{
		void	(*lib_scan_create_evt)(struct _lib_scan_t *scan, uint8_t status);
		void	(*lib_scan_start_evt)(struct _lib_scan_t *scan, uint8_t status);
		void	(*lib_scan_stop_evt)(struct _lib_scan_t *scan, uint8_t reason);
		void	(*lib_adv_report_ind)(struct _lib_gapm_ext_adv_report_ind_t *ind);
	} hdl;
} lib_scan_t;

typedef struct _lib_scan_init_t
{
	esble_gapm_create_scan_cmd_t	cmd;
	esble_gapm_scan_param_t			scan_param;

	struct
	{
		void	(*lib_scan_create_evt)(struct _lib_scan_t *scan, uint8_t status);
		void	(*lib_scan_start_evt)(struct _lib_scan_t *scan, uint8_t status);
		void	(*lib_scan_stop_evt)(struct _lib_scan_t *scan, uint8_t reason);
		void	(*lib_adv_report_ind)(struct _lib_gapm_ext_adv_report_ind_t *ind);
	} hdl;
} lib_scan_init_t;

extern lib_scan_t app_scan;

esble_err lib_ble_scan_name_filter_add(lib_scan_t * const p_scan_ctx,
                                               char           const * p_name);

esble_err lib_ble_scan_uuid_filter_add(lib_scan_t * const p_scan_ctx,
                                               lib_ble_uuid_t     const * p_uuid);

esble_err lib_ble_scan_filters_enable(lib_scan_t * const p_scan_ctx,
										uint8_t			 filter_mode);

esble_err lib_ble_scan_filters_disable(lib_scan_t * const p_scan_ctx,
										uint8_t			 filter_mode);

void lib_ble_scan_set_match_conn_mode(lib_scan_t * const p_scan_ctx, bool match_conn);

void lib_ble_scan_filters_set_match_all_mode(lib_scan_t * const p_scan_ctx, bool match_all);

esble_err lib_scan_init(lib_scan_t *lib_scan, lib_scan_init_t *init);

int lib_scan_start(lib_scan_t *lib_scan);

int lib_scan_stop(lib_scan_t *lib_scan);


#endif
