#ifndef _LIB_INIT_H_
#define _LIB_INIT_H_

#include <stdint.h>
#include <stdbool.h>

#include "esble_gapm.h"
#include "sdk_conf.h"

typedef struct _lib_init_t
{
	struct _lib_init_t				*next;

	uint8_t							init_idx;

	esble_gapm_create_init_cmd_t	cmd;
	esble_gapm_init_param_t			init_param;

	struct
	{
		void	(*lib_init_create_evt)(struct _lib_init_t *init, uint8_t status);
		void	(*lib_init_start_evt)(struct _lib_init_t *init, uint8_t status);
		void	(*lib_init_stop_evt)(struct _lib_init_t *init, uint8_t reason);
	} hdl;
} lib_init_t;

typedef struct _lib_init_init_t
{
	esble_gapm_create_init_cmd_t	cmd;
	esble_gapm_init_param_t			init_param;

	struct
	{
		void	(*lib_init_create_evt)(struct _lib_init_t *init, uint8_t status);
		void	(*lib_init_start_evt)(struct _lib_init_t *init, uint8_t status);
		void	(*lib_init_stop_evt)(struct _lib_init_t *init, uint8_t reason);
	} hdl;
} lib_init_init_t;

extern lib_init_t app_init;

esble_err lib_init_init(lib_init_t *lib_init, lib_init_init_t *init, bool creat);

int lib_init_start(lib_init_t *lib_init);

int lib_init_stop(lib_init_t *lib_init);


#endif
