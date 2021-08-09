#ifndef _ES_BLE_H_
#define _ES_BLE_H_

#include "esble_error.h"
#include "esble_def.h"

typedef enum _esble_base_enum
{
	ESBLE_COMM_BASE		= 0x00,
	ESBLE_GAPM_BASE		= 0x10,
	ESBLE_GAPC_BASE		= 0x50,
	ESBLE_GATTM_BASE	= 0x70,
	ESBLE_GATTC_BASE	= 0x80,
} esble_base_enum;

#endif
