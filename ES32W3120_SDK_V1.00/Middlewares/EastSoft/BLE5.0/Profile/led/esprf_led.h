#ifndef _ESPRF_HT_H_
#define _ESPRF_HT_H_

#include <stdint.h>
#include <stdbool.h>

#define LED_VALUE_MAX_LEN				(1)
#define LED_IND_NTF_CFG_MAX_LEN			(2)

#define LED_SERVER_UUID					{0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10, 0x11, 0x012 ,0x13, 0x14, 0x15, 0x16}
#define LED_CHAR_UUIND					{0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xA0, 0xA1, 0x0A2 ,0xA3, 0xA4, 0xA5, 0xA6}
#define BUTTON_CHAR_UUIND				{0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xB0, 0xB1, 0x0B2 ,0xB3, 0xB4, 0xB5, 0xB6}

#define ESPRF_LED_IDX(handle)			((handle < esprf_led_env.svc_hdl) ? LED_IDX_NB : (handle - esprf_led_env.svc_hdl + LED_IDX_SVC))
#define ESPRF_LED_HANDLE(idx)			(esprf_led_env.svc_hdl + idx)

typedef enum _prf_cli_conf									/* Possible values for setting client configuration characteristics. */
{

	PRF_CLI_STOP_NTFIND	= 0x0000,							/* Stop notification/indication. */

	PRF_CLI_START_NTF,										/* Start notification. */

	PRF_CLI_START_IND,										/* Start indication. */
} prf_cli_conf;

typedef enum _led_att_db_list
{
	LED_IDX_SVC,

	LED_IDX_LED_CHAR,
	LED_IDX_LED_VAL,

	LED_IDX_BUTTON_CHAR,
	LED_IDX_BUTTON_VAL,
	LED_IDX_BUTTON_IND_CFG,

	LED_IDX_NB,
} led_att_db_list;

typedef enum _led_ntf_ind_cfg								/* Notification and indication configuration. */
{
	LED_CFG_BUTTON_NTF	= (1 << 0),							/* Stable measurement interval indication enabled. */
} led_ntf_ind_cfg;

typedef void (*esprf_hdl)(const void *evt);

typedef struct _esprf_hdl_tbl_t
{
	uint8_t		id;
	esprf_hdl	hdl;
} esprf_hdl_tbl_t;

typedef struct _esprf_led_app_hdl_t
{
	void	(*add_svc)(uint8_t status);
	void	(*ntf_ind)(uint8_t conidx, uint32_t ntf_ind);
	void	(*led_write_req)(uint8_t conidx, uint8_t value);
} esprf_led_app_hdl_t;

typedef struct _esprf_led_env_t
{
	uint8_t		conidx;
	uint16_t	svc_hdl;
	uint16_t	end_hdl;
	uint32_t	ntf_ind;

	uint8_t		led_value;

} esprf_led_env_t;


void esprf_led_init(esprf_led_app_hdl_t *app_hdl, uint8_t led_init_value);

int esprf_led_button_send(uint8_t button_value);

int esprf_led_write_req_cfm(uint8_t conidx, uint8_t status, uint8_t new_value);

#endif
