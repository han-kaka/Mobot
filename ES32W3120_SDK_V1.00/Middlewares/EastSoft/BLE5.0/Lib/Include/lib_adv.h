#ifndef _LIB_ADV_H_
#define _LIB_ADV_H_

#include <stdint.h>

#include "esble_gapm.h"
#include "lib_advdata.h"

typedef struct _lib_adv_t
{
	struct _lib_adv_t				*next;

	uint8_t							adv_idx;

	esble_gapm_create_adv_cmd_t		cmd;
	uint8_t							enc_adv_data[ESBLE_GAP_EXT_ADV_DATA_MAX_LEN];
	uint16_t							enc_adv_data_len;
	uint8_t							enc_scan_rsp[ESBLE_GAP_EXT_ADV_DATA_MAX_LEN];
	uint16_t							enc_scan_rsp_len;

	struct
	{
		void	(*lib_adv_create_evt)(struct _lib_adv_t *adv, uint8_t status);
		void	(*lib_adv_set_adv_data_evt)(struct _lib_adv_t *adv, uint8_t status);
		void	(*lib_adv_start_evt)(struct _lib_adv_t *adv, uint8_t status);
		void	(*lib_adv_stop_evt)(struct _lib_adv_t *adv, uint8_t reason, uint8_t per_adv_stop);
	} hdl;
} lib_adv_t;

typedef struct _lib_adv_init_t
{
	esble_gapm_create_adv_cmd_t		cmd;
	lib_advdata_t					adv_data;
	lib_advdata_t					scan_rsp_data;

	struct
	{
		void	(*lib_adv_create_evt)(lib_adv_t *adv, uint8_t status);
		void	(*lib_adv_set_adv_data_evt)(lib_adv_t *adv, uint8_t status);
		void	(*lib_adv_start_evt)(lib_adv_t *adv, uint8_t status);
		void	(*lib_adv_stop_evt)(lib_adv_t *adv, uint8_t reason, uint8_t per_adv_stop);
	} hdl;
} lib_adv_init_t;

esble_err lib_adv_init(lib_adv_t *lib_adv, lib_adv_init_t *init);

int lib_adv_start(lib_adv_t *lib_adv, uint16_t duration, uint8_t max_adv_evt);

int lib_adv_stop(lib_adv_t *lib_adv);

esble_err lib_adv_set_data(lib_adv_t *lib_adv, lib_advdata_t *adv_data, lib_advdata_t *scan_rsp_data);

#endif
