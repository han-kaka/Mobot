#ifndef _LIB_DB_DISCOVERY_H_
#define _LIB_DB_DISCOVERY_H_

#include <stdint.h>
#include <stdbool.h>

#include "esble_gattc.h"
#include "sdk_conf.h"

typedef struct _lib_gattc_sdp_svc_ind_t
{
	uint8_t		uuid_len;
	
	uint8_t		uuid[ESBLE_ATT_UUID_128_LEN];						/* Service UUID. */
	
	uint16_t	start_hdl;									/* Service start handle. */
	
	uint16_t	end_hdl;									/* Service end handle. */
	
	union _esble_gattc_sdp_att_info_t	info[ESBLE_GATT_MAX_CHAR_CNT];	/* attribute information present in the service (length = end_hdl - start_hdl). */
} lib_gattc_sdp_svc_ind_t;

typedef struct _lib_db_discovery_t
{
	uint8_t							conn_idx;
	bool							disc_finished;
	uint8_t 						srv_cnt;

	lib_gattc_sdp_svc_ind_t			srv_info[ESBLE_GATT_MAX_SERVICE_CNT];

	esble_gattc_sdp_svc_disc_cmd_t cmd;
	struct
	{
		void	(*lib_db_discovery_evt)(uint8_t conn_idx, uint8_t svc_cnt, lib_gattc_sdp_svc_ind_t *srv_ind);
		void	(*lib_db_discovery_error_evt)(uint8_t conn_idx, uint8_t operation, uint8_t status);
	} hdl;
} lib_db_discovery_t;

typedef struct _lib_db_discovery_init_t
{
	esble_gattc_sdp_svc_disc_cmd_t cmd;
struct
	{
		void	(*lib_db_discovery_evt)(uint8_t conn_idx, uint8_t svc_cnt, lib_gattc_sdp_svc_ind_t *srv_ind);
		void	(*lib_db_discovery_error_evt)(uint8_t conn_idx, uint8_t operation, uint8_t status);
	} hdl;
} lib_db_discovery_init_t;

extern lib_db_discovery_t app_db_disc;

esble_err lib_db_discovery_init(lib_db_discovery_t *lib_db_discovery, lib_db_discovery_init_t *init);


#endif
