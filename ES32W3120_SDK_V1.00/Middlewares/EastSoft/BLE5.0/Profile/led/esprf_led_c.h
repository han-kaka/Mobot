#ifndef _ESPRF_LED_C_H_
#define _ESPRF_LED_C_H_

#include <stdint.h>
#include <stdbool.h>
#include "lib_db_discovery.h"
#include "esprf_led.h"

typedef void (*esprf_led_c_hdl)(const void *evt);

/**@brief LED Client event type. */
typedef enum
{
    ESPRF_LED_C_EVT_DISCOVERY_COMPLETE = 1,  /* Event indicating that the LED Service was discovered at the peer. */
    ESPRF_LED_C_EVT_BUTTON_NOTIFICATION         /* Event indicating that a notification of the LED Value characteristic was received from the peer. */
} esprf_led_c_evt_type_t;

typedef struct _esprf_led_c_db_t
{
	uint16_t led_value_handle;				/*Handle of the LED Value characteristic*/
	uint16_t button_value_handle;			/*Handle of the Button Value characteristic*/
	uint16_t button_cccd_handle;			/*Handle of the CCCD of the BUTTON Value characteristic*/
}esprf_led_c_db_t;

typedef struct _esprf_led_c_value_t
{
	uint16_t led_value;
	uint8_t button_value;
}esprf_led_c_value_t;

typedef struct _esprf_led_c_env_s esprf_led_c_env_t;

typedef void(* esprf_led_c_evt_handler_t) (esprf_led_c_env_t *p_led_c_evt);

typedef void(* esprf_led_c_error_handler_t) (uint8_t err_code);

struct _esprf_led_c_env_s
{
	uint8_t					conidx;
	esprf_led_c_evt_type_t	evt_type;
	uint16_t				svc_start_hdl;
	uint16_t				svc_end_hdl;

	esprf_led_c_db_t	peer_db;		/*Handles related to the LED, found on the peer device. This is filled if the evt_type is @ref ESPRF_LED_C_EVT_DISCOVERY_COMPLETE.*/
	esprf_led_c_value_t led_value;				/*LED Value received. This is filled if the evt_type is @ref ESPRF_LED_C_EVT_HRM_NOTIFICATION. */

	struct
	{
		esprf_led_c_evt_handler_t 	evt_handler;
		esprf_led_c_error_handler_t err_handler;
	}hdl;
};

typedef struct _esprf_led_c_app_hdl_t
{
	esprf_led_c_evt_handler_t 	evt_handler;
	esprf_led_c_error_handler_t err_handler;
}esprf_led_c_app_hdl_t;

void esprf_led_c_on_db_disc_handler(uint8_t conn_idx, lib_gattc_sdp_svc_ind_t *srv_ind);

void esprf_led_c_init(esprf_led_c_app_hdl_t *led_c_app_init);
#endif
