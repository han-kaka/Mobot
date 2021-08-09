#ifndef _ESAPP_H_
#define _ESAPP_H_

#include <stdint.h>


#define ESAPP_ADV_CHMAP					(0x07)				/* Advertising channel map - 37, 38, 39. */
#define ESAPP_ADV_INT_MIN				(64)				/* Advertising minimum interval - 40ms (64*0.625ms). */
#define ESAPP_ADV_INT_MAX				(64)				/* Advertising maximum interval - 40ms (64*0.625ms). */

typedef struct
{
	uint8_t				role;
	uint16_t			conhdl;
	uint16_t			con_interval;
	uint16_t			con_latency;
	uint16_t			sup_to;
	uint8_t				clk_accuracy;
	esble_gap_bdaddr_t	peer_addr;
	esble_timer_t		upd_timer;
	esble_timer_param_t	upd_param;
} esapp_conn_instance_t;

void esapp_init(void);

void esapp_button(uint8_t value);


#endif
