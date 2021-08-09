#ifndef _ESPRF_HT_H_
#define _ESPRF_HT_H_

#include <stdint.h>
#include <stdbool.h>

#define HTPT_MEAS_INTV_DFLT_MIN			(0x0001)
#define HTPT_MEAS_INTV_DFLT_MAX			(0x000A)

#define HTPT_TEMP_MEAS_MAX_LEN			(13)
#define HTPT_TEMP_TYPE_MAX_LEN			(1)
#define HTPT_MEAS_INTV_MAX_LEN			(2)
#define HTPT_MEAS_INTV_RANGE_MAX_LEN	(4)
#define HTPT_IND_NTF_CFG_MAX_LEN		(2)

#define HTPT_TEMP_MEAS_MASK				(0x000F)
#define HTPT_TEMP_TYPE_MASK				(0x0030)
#define HTPT_INTM_TEMP_MASK				(0x01C0)
#define HTPT_MEAS_INTV_MASK				(0x0600)
#define HTPT_MEAS_INTV_CCC_MASK			(0x0800)
#define HTPT_MEAS_INTV_VALID_RGE_MASK	(0x1000)

#define HTPT_TEMP_MEAS_ATT_NB			(4)
#define HTPT_TEMP_TYPE_ATT_NB			(2)
#define HTPT_INTERM_MEAS_ATT_NB			(3)
#define HTPT_MEAS_INTV_ATT_NB			(2)
#define HTPT_MEAS_INTV_CCC_ATT_NB		(1)
#define HTPT_MEAS_INTV_RNG_ATT_NB		(1)

#define HTP_OUT_OF_RANGE_ERR_CODE		(0x80)

#define ESPRF_HT_IDX(handle)			((handle < esprf_ht_env.svc_hdl) ? HTS_IDX_NB : (handle - esprf_ht_env.svc_hdl + HTS_IDX_SVC))
#define ESPRF_HT_HANDLE(idx)			(esprf_ht_env.svc_hdl + idx)

typedef enum _hts_att_db_list
{
	HTS_IDX_SVC,

	HTS_IDX_TEMP_MEAS_CHAR,
	HTS_IDX_TEMP_MEAS_VAL,
	HTS_IDX_TEMP_MEAS_IND_CFG,

	HTS_IDX_TEMP_TYPE_CHAR,
	HTS_IDX_TEMP_TYPE_VAL,

	HTS_IDX_INTERM_TEMP_CHAR,
	HTS_IDX_INTERM_TEMP_VAL,
	HTS_IDX_INTERM_TEMP_CFG,

	HTS_IDX_MEAS_INTV_CHAR,
	HTS_IDX_MEAS_INTV_VAL,
	HTS_IDX_MEAS_INTV_CFG,
	HTS_IDX_MEAS_INTV_VAL_RANGE,

	HTS_IDX_NB,
} hts_att_db_list;

typedef enum _htp_temp_flag									/* Temperature Measurement Flags field bit values. */
{
	HTP_FLAG_CELSIUS			= 0x00,						/* Temperature Units Flag - Celsius. */

	HTP_FLAG_FAHRENHEIT,									/* Temperature Units Flag - Fahrenheit. */

	HTP_FLAG_TIME,											/* Time Stamp Flag. */

	HTP_FLAG_TYPE				= 0x04,						/* Temperature Type Flag. */
} htp_temp_flag;

typedef enum _htp_temp_type									/* Temperature Type Description. */
{
	HTP_TYPE_ARMPIT						= 0x01,				/* Armpit. */

	HTP_TYPE_BODY						= 0x02,				/* Body (general). */

	HTP_TYPE_EAR						= 0x03,				/* Ear (usually ear lobe). */

	HTP_TYPE_FINGER						= 0x04,				/* Finger. */

	HTP_TYPE_GASTRO_INTESTINAL_TRACT	= 0x05,				/* Gastro-intestinal Tract. */

	HTP_TYPE_MOUTH						= 0x06,				/* Mouth. */

	HTP_TYPE_RECTUM						= 0x07,				/* Rectum. */

	HTP_TYPE_TOE						= 0x08,				/* Toe. */

	HTP_TYPE_TYMPANUM					= 0x09,				/* Tympanum (ear drum). */
} htp_temp_type;

typedef enum _prf_cli_conf									/* Possible values for setting client configuration characteristics. */
{

	PRF_CLI_STOP_NTFIND	= 0x0000,							/* Stop notification/indication. */

	PRF_CLI_START_NTF,										/* Start notification. */

	PRF_CLI_START_IND,										/* Start indication. */
} prf_cli_conf;

typedef enum _htpt_ntf_ind_cfg								/* Notification and indication configuration. */
{
	HTPT_CFG_STABLE_MEAS_IND	= (1 << 0),					/* Stable measurement interval indication enabled. */

	HTPT_CFG_INTERM_MEAS_NTF	= (1 << 1),					/* Intermediate measurement notification enabled. */

	HTPT_CFG_MEAS_INTV_IND		= (1 << 2),					/* Measurement interval indication. */
} htpt_ntf_ind_cfg;


typedef void (*esprf_hdl)(const void *evt);

typedef struct _esprf_hdl_tbl_t
{
	uint8_t		id;
	esprf_hdl	hdl;
} esprf_hdl_tbl_t;

typedef struct _esprf_ht_app_hdl_t
{
	void	(*meas_intv_chg_req_ind)(uint8_t conidx, uint16_t meas_intv);
	void	(*ntf_ind)(uint8_t conidx, uint32_t ntf_ind);
} esprf_ht_app_hdl_t;

typedef struct _esprf_ht_env_t
{
	uint8_t		conidx;
	uint16_t	svc_hdl;

	uint16_t	meas_intv;									/* Current Measure interval. */

	uint16_t	meas_intv_min;								/* measurement interval range min. */

	uint16_t	meas_intv_max;								/* measurement interval range max. */

	uint8_t		temp_type;									/* Temperature Type Value. */
	uint32_t	ntf_ind;
} esprf_ht_env_t;

/*
 * date and time structure
 * size = 7 bytes
 */
typedef struct _esprf_date_time_t							/* Time profile information. */
{
	uint16_t	year;										/* year time element. */

	uint8_t		month;										/* month time element. */

	uint8_t		day;										/* day time element. */

	uint8_t		hour;										/* hour time element. */

	uint8_t		min;										/* minute time element. */

	uint8_t		sec;										/* second time element. */
} esprf_date_time_t;

typedef struct _esprf_ht_temp_meas_t						/* Temperature Measurement Value Structure. */
{
	uint32_t			temp;								/* Temperature value. */

	esprf_date_time_t	time_stamp;							/* Time stamp. */

	uint8_t				flags;								/* Flag (@see enum htp_temp_flag). */

	uint8_t				type;								/* Type (@see enum htp_temp_type). */
} esprf_ht_temp_meas_t;


void esprf_ht_init(esprf_ht_app_hdl_t *app_hdl,
					uint16_t meas_intv_min, uint16_t meas_intv_max,
					uint8_t temp_type);

void esprf_ht_add_svc(void);

int esprf_ht_temp_send(esprf_ht_temp_meas_t temp_meas, bool stable_meas);

int esprf_ht_meas_intv_chg_cfm(uint8_t conidx, uint8_t status);

void esprf_ht_def_cb_hdl(uint8_t id, const void *evt);

#endif
