#ifndef _ESBLE_COMM_H_
#define _ESBLE_COMM_H_

#include "esble.h"
#include "esble_gapm.h"
#include "esble_gapc.h"
#include "esble_gattm.h"
#include "esble_gattc.h"


/*****************************************************************************************************/
/**												ÏÂÐÐÃüÁî											**/
/*****************************************************************************************************/

#define ESBLE_TIMER_STRU_SIZE		11

typedef enum
{
	ESBLE_INIT				= ESBLE_COMM_BASE,

	ESBLE_MSDELAY,

	ESBLE_TIMER_INIT,
	ESBLE_TIMER_START,
	ESBLE_TIMER_STOP,
	ESBLE_TIMER_SET,
} esble_comm_cmd_enum;


typedef enum _esble_timer_flag_enum
{
	ESBLE_TIMER_FLAG_ONE_SHOT		= 0x0,					/* one shot timer */
	ESBLE_TIMER_FLAG_PERIODIC		= 0x2,					/* periodic timer */
} esble_timer_flag_enum;

typedef struct
{
	esble_gapm_cb_t					gapm_cb;
	esble_gapc_cb_t					gapc_cb;
	esble_gattm_cb_t				gattm_cb;
	esble_gattc_cb_t				gattc_cb;
} esble_cb_func_t;

typedef struct _esble_timer_t
{
	uint32_t	size[ESBLE_TIMER_STRU_SIZE];
} esble_timer_t;

typedef struct _esble_timer_param_t
{
	void 							(*timeout_hdl)(void *arg);
	void							*arg;
	uint32_t						ms;
	uint8_t							flag;					/* @see esble_timer_flag_enum. */
} esble_timer_param_t;


SVCALL(ESBLE_INIT, uint32_t, esble_init(uint32_t clk, uint32_t *ram_base, esble_cb_func_t *cb));

SVCALL(ESBLE_MSDELAY, uint32_t, esble_msdelay(uint32_t ms));

SVCALL(ESBLE_TIMER_INIT, uint32_t, esble_timer_init(esble_timer_t *timer,
													esble_timer_param_t *param));

SVCALL(ESBLE_TIMER_START, uint32_t, esble_timer_start(esble_timer_t *timer));

SVCALL(ESBLE_TIMER_STOP, uint32_t, esble_timer_stop(esble_timer_t *timer));

SVCALL(ESBLE_TIMER_SET, uint32_t, esble_timer_set(esble_timer_t *timer, uint32_t ms));

#endif
