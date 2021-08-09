#ifndef _LIB_CONF_H_
#define _LIB_CONF_H_

#include <stdbool.h>
#include "esble_gapm.h"

typedef void (*lib_conf_finish_t)(uint8_t err);

typedef struct _lib_conf_env_t
{
	bool							is_busy;
	esble_gapm_set_dev_config_cmd_t	conf;
	lib_conf_finish_t				finish;
} lib_conf_env_t;

void lib_conf_init(esble_gapm_set_dev_config_cmd_t *conf, lib_conf_finish_t finish);

#endif
