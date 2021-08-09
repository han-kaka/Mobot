#ifndef _ESBLE_GAPM_H_
#define _ESBLE_GAPM_H_

#include "esble.h"

/*****************************************************************************************************/
/**												下行命令											**/
/*****************************************************************************************************/

typedef enum _esble_gapm_cmd_enum
{
	ESBLE_GAPM_RESET			= ESBLE_GAPM_BASE,
	ESBLE_GAPM_SET_DEV_CONF,

	ESBLE_GAPM_CREATE_ADV,
	ESBLE_GAPM_SET_ADV_DATA,
	ESBLE_GAPM_SET_SCAN_RSP_DATA,
	ESBLE_GAPM_ADV_START,
	ESBLE_GAPM_ADV_STOP,

	ESBLE_GAPM_CREATE_SCAN,
	ESBLE_GAPM_SCAN_START,
	ESBLE_GAPM_SCAN_STOP,

	ESBLE_GAPM_CREATE_INIT,
	ESBLE_GAPM_INIT_START,
	ESBLE_GAPM_INIT_STOP,

	ESBLE_GAPM_CREATE_PERIOD_SYNC,
	ESBLE_GAPM_SET_PERIOD_ADV_DATA,
	ESBLE_GAPM_PERIOD_SYNC_START,
	ESBLE_GAPM_PERIOD_SYNC_STOP,

	ESBLE_GAPM_STOP_ALL_ACTIVITIES,

	ESBLE_GAPM_DELETE_ACTIVITY,
	ESBLE_GAPM_DELETE_ALL_ACTIVITY,

	ESBLE_GAPM_GET_NB_ADV_SETS,
	ESBLE_GAPM_GET_DEV_ADV_TX_POWER,
	ESBLE_GAPM_GET_MAX_LE_ADV_DATA_LEN,
	ESBLE_GAPM_GET_PAL_SIZE,

	ESBLE_GAPM_SET_PAL,

	ESBLE_GAPM_USE_ENC_BLOCK,
	ESBLE_GAPM_GEN_RAND_NB,
	ESBLE_GAPM_SET_IRK,
	ESBLE_GAPM_GEN_DH_KEY,
	ESBLE_GAPM_GET_PUB_KEY,

	ESBLE_GAPM_GET_RAL_LOC_ADDR,
	ESBLE_GAPM_GET_RAL_PEER_ADDR,
	ESBLE_GAPM_RESOLV_ADDR,
	ESBLE_GAPM_GET_DEV_BDADDR,
	ESBLE_GAPM_GET_RAL_SIZE,
	ESBLE_GAPM_GEN_RAND_ADDR,
	ESBLE_GAPM_SET_RAL,

	ESBLE_GAPM_SET_CHANNEL_MAP,
	ESBLE_GAPM_GET_DEV_VERSION,
	ESBLE_GAPM_GET_DEV_TX_PWR,
	ESBLE_GAPM_GET_SUGGESTED_DFLT_LE_DATA_LEN,
	ESBLE_GAPM_GET_DEV_RF_PATH_COMP,
	ESBLE_GAPM_GET_MAX_LE_DATA_LEN,
	ESBLE_GAPM_SET_WL,
	ESBLE_GAPM_GET_WLIST_SIZE,
	ESBLE_GAPM_UNKNOWN_TASK_MSG,
	ESBLE_GAPM_RENEW_ADDR,
	ESBLE_GAPM_LE_TEST_RX_START,
	ESBLE_GAPM_LE_TEST_TX_START,
	ESBLE_GAPM_LE_TEST_STOP,
	ESBLE_GAPM_PLF_RESET,
	ESBLE_GAPM_DBG_GET_MEM_INFO,
	ESBLE_GAPM_LEPSM_REG,
	ESBLE_GAPM_LEPSM_UNREG,
} esble_gapm_cmd_enum;


typedef enum _esble_gapm_adv_type_enum						/* Type of advertising that can be created. */
{
	ESBLE_GAPM_ADV_TYPE_LEGACY	= 0,						/* Legacy advertising. */

	ESBLE_GAPM_ADV_TYPE_EXTENDED,							/* Extended advertising. */

	ESBLE_GAPM_ADV_TYPE_PERIODIC,							/* Periodic advertising. */
} esble_gapm_adv_type_enum;

typedef enum _esble_gapm_adv_prop_pos_enum					/* Advertising properties bit field bit positions. */
{
	ESBLE_GAPM_ADV_PROP_CONNECTABLE_POS		= 0,			/* Indicate that advertising is connectable, reception of CONNECT_REQ or AUX_CONNECT_REQ */
															/* PDUs is accepted. Not applicable for periodic advertising. */

	ESBLE_GAPM_ADV_PROP_SCANNABLE_POS,						/* Indicate that advertising is scannable, reception of SCAN_REQ or AUX_SCAN_REQ PDUs is accepted. */

	ESBLE_GAPM_ADV_PROP_DIRECTED_POS,						/* Indicate that advertising targets a specific device. Only apply in following cases: */
															/* - Legacy advertising: if connectable. */
															/* - Extended advertising: connectable or (non connectable and non discoverable). */

	ESBLE_GAPM_ADV_PROP_HDC_POS,							/* Indicate that High Duty Cycle has to be used for advertising on primary channel. */
															/* Apply only if created advertising is not an extended advertising. */

	ESBLE_GAPM_ADV_PROP_RESERVED_4_POS,						/* Bit 4 is reserved. */

	ESBLE_GAPM_ADV_PROP_ANONYMOUS_POS,						/* Enable anonymous mode. Device address won't appear in send PDUs. */
															/* Valid only if created advertising is an extended advertising. */

	ESBLE_GAPM_ADV_PROP_TX_PWR_POS,							/* Include TX Power in the extended header of the advertising PDU. */
															/* Valid only if created advertising is not a legacy advertising. */

	ESBLE_GAPM_ADV_PROP_PER_TX_PWR_POS,						/* Include TX Power in the periodic advertising PDU. */
															/* Valid only if created advertising is a periodic advertising. */

	ESBLE_GAPM_ADV_PROP_SCAN_REQ_NTF_EN_POS,				/* Indicate if application must be informed about received scan requests PDUs. */
} esble_gapm_adv_prop_pos_enum;

typedef enum _esble_gapm_adv_prop_enum						/* Advertising properties bit field bit value. */
{
	ESBLE_GAPM_ADV_PROP_CONNECTABLE_BIT		= ESBLE_BIT(ESBLE_GAPM_ADV_PROP_CONNECTABLE_POS),		/* Indicate that advertising is connectable, reception of CONNECT_REQ or AUX_CONNECT_REQ. */
																									/* PDUs is accepted. Not applicable for periodic advertising. */

	ESBLE_GAPM_ADV_PROP_SCANNABLE_BIT		= ESBLE_BIT(ESBLE_GAPM_ADV_PROP_SCANNABLE_POS),			/* Indicate that advertising is scannable, reception of SCAN_REQ or AUX_SCAN_REQ PDUs is accepted. */

	ESBLE_GAPM_ADV_PROP_DIRECTED_BIT		= ESBLE_BIT(ESBLE_GAPM_ADV_PROP_DIRECTED_POS),			/* Indicate that advertising targets a specific device. Only apply in following cases: */
																									/* - Legacy advertising: if connectable. */
																									/* - Extended advertising: connectable or (non connectable and non discoverable). */

	ESBLE_GAPM_ADV_PROP_HDC_BIT				= ESBLE_BIT(ESBLE_GAPM_ADV_PROP_HDC_POS),				/* Indicate that High Duty Cycle has to be used for advertising on primary channel. */
																									/* Apply only if created advertising is not an extended advertising. */

	ESBLE_GAPM_ADV_PROP_RESERVED_4_BIT		= ESBLE_BIT(ESBLE_GAPM_ADV_PROP_RESERVED_4_POS),		/* Bit 4 is reserved. */

	ESBLE_GAPM_ADV_PROP_ANONYMOUS_BIT		= ESBLE_BIT(ESBLE_GAPM_ADV_PROP_ANONYMOUS_POS),			/* Enable anonymous mode. Device address won't appear in send PDUs. */
																									/* Valid only if created advertising is an extended advertising. */

	ESBLE_GAPM_ADV_PROP_TX_PWR_BIT			= ESBLE_BIT(ESBLE_GAPM_ADV_PROP_TX_PWR_POS),			/* Include TX Power in the extended header of the advertising PDU. */
																									/* Valid only if created advertising is not a legacy advertising. */

	ESBLE_GAPM_ADV_PROP_PER_TX_PWR_BIT		= ESBLE_BIT(ESBLE_GAPM_ADV_PROP_PER_TX_PWR_POS),		/* Include TX Power in the periodic advertising PDU. */
																									/* Valid only if created advertising is a periodic advertising. */

	ESBLE_GAPM_ADV_PROP_SCAN_REQ_NTF_EN_BIT	= ESBLE_BIT(ESBLE_GAPM_ADV_PROP_SCAN_REQ_NTF_EN_POS),	/* Indicate if application must be informed about received scan requests PDUs. */
} esble_gapm_adv_prop_enum;

typedef enum _esble_gapm_adv_disc_mode_enum					/* Advertising discovery mode. */
{
	ESBLE_GAPM_ADV_MODE_NON_DISC	= 0,					/* Mode in non-discoverable. */

	ESBLE_GAPM_ADV_MODE_GEN_DISC,							/* Mode in general discoverable. */

	ESBLE_GAPM_ADV_MODE_LIM_DISC,							/* Mode in limited discoverable. */

	ESBLE_GAPM_ADV_MODE_BEACON,								/* Broadcast mode without presence of AD_TYPE_FLAG in advertising data. */

	ESBLE_GAPM_ADV_MODE_MAX,
} esble_gapm_adv_disc_mode_enum;

typedef enum _esble_gapm_per_sync_type_enum					/* Periodic synchronization types. */
{
	ESBLE_GAPM_PER_SYNC_TYPE_GENERAL	= 0,				/* Do not use periodic advertiser list for synchronization. Use advertiser information provided */
															/* in the GAPM_ACTIVITY_START_CMD. */

	ESBLE_GAPM_PER_SYNC_TYPE_SELECTIVE,						/* Use periodic advertiser list for synchronization. */
} esble_gapm_per_sync_type_enum;

typedef enum _esble_gapm_phy_type_enum						/* PHY Type. */
{
	ESBLE_GAPM_PHY_TYPE_LE_1M	= 1,						/* LE 1M. */

	ESBLE_GAPM_PHY_TYPE_LE_2M,								/* LE 2M. */

	ESBLE_GAPM_PHY_TYPE_LE_CODED,							/* LE Coded. */
} esble_gapm_phy_type_enum;

typedef enum _esble_gapm_leg_adv_prop_enum																						/* Advertising properties configurations for legacy advertising. */
{
	ESBLE_GAPM_ADV_PROP_NON_CONN_NON_SCAN_MASK	= 0x0000,																		/* Non connectable non scannable advertising. */

	ESBLE_GAPM_ADV_PROP_BROADCAST_NON_SCAN_MASK	= ESBLE_GAPM_ADV_PROP_NON_CONN_NON_SCAN_MASK,									/* Broadcast non scannable advertising - Discovery mode must be Non Discoverable. */

	ESBLE_GAPM_ADV_PROP_NON_CONN_SCAN_MASK		= ESBLE_GAPM_ADV_PROP_SCANNABLE_BIT,											/* Non connectable scannable advertising. */

	ESBLE_GAPM_ADV_PROP_BROADCAST_SCAN_MASK		= ESBLE_GAPM_ADV_PROP_NON_CONN_SCAN_MASK,										/* Broadcast non scannable advertising - Discovery mode must be Non Discoverable. */

	ESBLE_GAPM_ADV_PROP_UNDIR_CONN_MASK			= ESBLE_GAPM_ADV_PROP_CONNECTABLE_BIT | ESBLE_GAPM_ADV_PROP_SCANNABLE_BIT,		/* Undirected connectable advertising. */

	ESBLE_GAPM_ADV_PROP_DIR_CONN_MASK			= ESBLE_GAPM_ADV_PROP_DIRECTED_BIT | ESBLE_GAPM_ADV_PROP_CONNECTABLE_BIT,		/* Directed connectable advertising. */

	ESBLE_GAPM_ADV_PROP_DIR_CONN_LDC_MASK		= ESBLE_GAPM_ADV_PROP_DIR_CONN_MASK,											/* Directed connectable with Low Duty Cycle. */

	ESBLE_GAPM_ADV_PROP_DIR_CONN_HDC_MASK		= ESBLE_GAPM_ADV_PROP_DIR_CONN_MASK | ESBLE_GAPM_ADV_PROP_HDC_BIT,				/* Directed connectable with High Duty Cycle. */
} esble_gapm_leg_adv_prop_enum;

typedef enum _esble_gapm_ext_adv_prop_enum																						/* Advertising properties configurations for extended advertising. */
{
	ESBLE_GAPM_EXT_ADV_PROP_NON_CONN_NON_SCAN_MASK	= 0x0000,																	/* Non connectable non scannable extended advertising. */

	ESBLE_GAPM_EXT_ADV_PROP_NON_CONN_SCAN_MASK		= ESBLE_GAPM_ADV_PROP_SCANNABLE_BIT,										/* Non connectable scannable extended advertising. */

	ESBLE_GAPM_EXT_ADV_PROP_NON_CONN_SCAN_DIR_MASK	= ESBLE_GAPM_ADV_PROP_SCANNABLE_BIT | ESBLE_GAPM_ADV_PROP_DIRECTED_BIT,		/* Non connectable scannable directed extended advertising. */

	ESBLE_GAPM_EXT_ADV_PROP_ANONYM_DIR_MASK			= ESBLE_GAPM_ADV_PROP_ANONYMOUS_BIT | ESBLE_GAPM_ADV_PROP_DIRECTED_BIT,		/* Non connectable anonymous directed extended advertising. */

	ESBLE_GAPM_EXT_ADV_PROP_UNDIR_CONN_MASK			= ESBLE_GAPM_ADV_PROP_CONNECTABLE_BIT,										/* Undirected connectable extended advertising. */

	ESBLE_GAPM_EXT_ADV_PROP_DIR_CONN_MASK			= ESBLE_GAPM_ADV_PROP_CONNECTABLE_BIT | ESBLE_GAPM_ADV_PROP_DIRECTED_BIT,	/* Directed connectable extended advertising. */
} esble_gapm_ext_adv_prop_enum;

typedef enum _esble_gapm_per_adv_prop_enum										/* Advertising properties configurations for periodic advertising. */
{
	ESBLE_GAPM_PER_ADV_PROP_UNDIR_MASK	= 0x0000,								/* Undirected periodic advertising. */

	ESBLE_GAPM_PER_ADV_PROP_DIR_MASK	= ESBLE_GAPM_ADV_PROP_DIRECTED_BIT,		/* Directed periodic advertising. */
} esble_gapm_per_adv_prop_enum;

typedef enum _esble_gapm_adv_filter_policy_enum				/* Advertising filter policy. */
{
	ESBLE_GAPM_ADV_ALLOW_SCAN_ANY_CON_ANY	= 0x00,			/* Allow both scan and connection requests from anyone. */

	ESBLE_GAPM_ADV_ALLOW_SCAN_WLST_CON_ANY,					/* Allow both scan req from White List devices only and connection req from anyone. */

	ESBLE_GAPM_ADV_ALLOW_SCAN_ANY_CON_WLST,					/* Allow both scan req from anyone and connection req from White List devices only. */

	ESBLE_GAPM_ADV_ALLOW_SCAN_WLST_CON_WLST,				/* Allow scan and connection requests from White List devices only. */
} esble_gapm_adv_filter_policy_enum;

typedef enum _esble_gapm_adv_report_info_enum				/* Advertising report information. */
{
	GAPM_REPORT_INFO_REPORT_TYPE_MASK	= 0x07,				/* Report Type. */

	GAPM_REPORT_INFO_COMPLETE_BIT		= (1 << 3),			/* Report is complete. */

	GAPM_REPORT_INFO_CONN_ADV_BIT		= (1 << 4),			/* Connectable advertising. */

	GAPM_REPORT_INFO_SCAN_ADV_BIT		= (1 << 5),			/* Scannable advertising. */

	GAPM_REPORT_INFO_DIR_ADV_BIT		= (1 << 6),			/* Directed advertising. */
}esble_gapm_adv_report_info_enum;

typedef struct _esble_gapm_set_dev_config_cmd_t
{
	uint8_t				role;								/* Device Role: Central, Peripheral, Observer, Broadcaster or All roles. */
	esble_bd_addr_t		pub_addr;							/* Public address */
	esble_bd_addr_t		rnd_addr;							/* Random address. */

	/* -------------- Privacy Config ----------------------*/
	uint16_t			renew_dur;							/* Duration before regenerate device address when privacy is enabled. - in seconds. */

	esble_bd_addr_t		addr;								/* Provided own static private random address. */

	esble_gap_sec_key_t	irk;								/* Device IRK used for resolvable random BD address generation (LSB first). */

	uint8_t				privacy_cfg;						/* Privacy configuration bit field (@see enum gapm_priv_cfg for bit signification). */

	/* -------------- Security Config ---------------------*/
	uint8_t				pairing_mode;						/* Pairing mode authorized (@see enum esble_pairing_mode_enum). */

	/* -------------- ATT Database Config -----------------*/
	uint16_t			gap_start_hdl;						/* GAP service start handle. */

	uint16_t			gatt_start_hdl;						/* GATT service start handle. */

	uint16_t			att_cfg;							/* Attribute database configuration (@see enum esgapm_att_cfg_flag). */

	/* -------------- LE Data Length Extension ------------*/
	uint16_t			sugg_max_tx_octets;					/* Suggested value for the Controller's maximum transmitted number of payload octets to be used. */

	uint16_t			sugg_max_tx_time;					/* Suggested value for the Controller's maximum packet transmission time to be used. */

	/* -------------- L2CAP Configuration -----------------*/
	uint16_t			max_mtu;							/* Maximal MTU acceptable for device. */

	uint16_t			max_mps;							/* Maximal MPS Packet size acceptable for device. */

	uint8_t				max_nb_lecb;						/* Maximum number of LE Credit based connection that can be established. */

	/* -------------- LE Audio Mode Supported -------------*/
	uint16_t			audio_cfg;							/* LE Audio Mode Configuration (@see gapm_audio_cfg_flag). */

	/* -------------- LE PHY Management -------------------*/
	uint8_t				tx_pref_phy;						/* Preferred LE PHY for data transmission (@see enum gap_phy). */

	uint8_t				rx_pref_phy;						/* Preferred LE PHY for data reception (@see enum gap_phy). */

	/* -------------- Miscellaneous 2 ---------------------*/
	uint16_t			tx_path_comp;						/* RF TX Path Compensation value (from -128dB to 128dB, unit is 0.1dB). */

	uint16_t			rx_path_comp;						/* RF RX Path Compensation value (from -128dB to 128dB, unit is 0.1dB). */
} esble_gapm_set_dev_config_cmd_t;


typedef struct _esble_gapm_adv_prim_cfg_t					/* Configuration for advertising on primary channel. */
{
	uint32_t	adv_intv_min;								/* Minimum advertising interval (in unit of 625us). Must be greater than 20ms. */

	uint32_t	adv_intv_max;								/* Maximum advertising interval (in unit of 625us). Must be greater than 20ms. */

	uint8_t		chnl_map;									/* Bit field indicating the channel mapping. */

	uint8_t		phy;										/* Indicate on which PHY primary advertising has to be performed (@see enum esble_gapm_phy_type_enum). */
															/* Note that LE 2M PHY is not allowed and that legacy advertising only support LE 1M PHY. */
} esble_gapm_adv_prim_cfg_t;

typedef struct _esble_gapm_adv_second_cfg_t					/* Configuration for advertising on secondary channel. */
{
	uint8_t		max_skip;									/* Maximum number of advertising events the controller can skip before sending the AUX_ADV_IND packets. */
															/* 0 means that AUX_ADV_IND PDUs shall be sent prior each advertising events. */

	uint8_t		phy;										/* Indicate on which PHY secondary advertising has to be performed (@see enum esble_gapm_phy_type_enum). */

	uint8_t		adv_sid;									/* Advertising SID. */
} esble_gapm_adv_second_cfg_t;

typedef struct _esble_gapm_adv_period_cfg_t					/* Configuration for periodic advertising. */
{
	uint16_t	adv_intv_min;								/* Minimum advertising interval (in unit of 1.25ms). Must be greater than 20ms. */

	uint16_t	adv_intv_max;								/* Maximum advertising interval (in unit of 1.25ms). Must be greater than 20ms. */
} esble_gapm_adv_period_cfg_t;

typedef struct _esble_gapm_create_adv_param_t
{

	uint8_t						type;						/* Advertising type (@see enum esble_gapm_adv_type_enum). */

	uint8_t						disc_mode;					/* Discovery mode (@see enum esble_gapm_adv_disc_mode). */

	uint16_t					prop;						/* Bit field value provided advertising properties (@see enum esble_gapm_adv_prop for bit signification). */

	int8_t						max_tx_pwr;					/* Maximum power level at which the advertising packets have to be transmitted(between -127 and 126 dBm). */

	uint8_t						filter_pol;					/* Advertising filtering policy (@see enum esble_gapm_adv_filter_policy_enum). */

	esble_gap_bdaddr_t			peer_addr;					/* Peer address configuration (only used in case of directed advertising). */

	esble_gapm_adv_prim_cfg_t	prim_cfg;					/* Configuration for primary advertising. */

	esble_gapm_adv_second_cfg_t	second_cfg;					/* Configuration for secondary advertising (valid only if advertising type is GAPM_ADV_TYPE_EXTENDED or GAPM_ADV_TYPE_PERIODIC). */

	esble_gapm_adv_period_cfg_t	period_cfg;					/* Configuration for periodic advertising (valid only if advertising type or GAPM_ADV_TYPE_PERIODIC). */
} esble_gapm_create_adv_param_t;

typedef struct _esble_gapm_create_adv_cmd_t
{
	uint8_t							own_addr_type;			/* Own address type (@see enum esble_own_addr_enum). */

	esble_gapm_create_adv_param_t	adv_param;				/* Advertising parameters (optional, shall be present only if operation is GAPM_CREATE_ADV_ACTIVITY). */
															/* For prop parameter, @see enum gapm_leg_adv_prop, @see enum esble_gapm_ext_adv_prop_enum and @see enum esble_gapm_per_adv_prop_enum for help. */
} esble_gapm_create_adv_cmd_t;

typedef struct _esble_gapm_adv_data_t
{
	uint8_t		adv_idx;									/* Adv identifier. */

	uint16_t	length;										/* Data length. */

	uint8_t		*data;										/* Data. */
} esble_gapm_adv_data_t;

typedef struct _esble_gapm_adv_start_cmd_t
{
	uint8_t		adv_idx; 									/* Adv identifier. */

	uint16_t	duration;									/* Advertising duration (in unit of 10ms). 0 means that advertising continues until the host disable it. */

	uint8_t		max_adv_evt;								/* Maximum number of extended advertising events the controller shall attempt to send prior to terminating the extending advertising. */
															/* Valid only if extended advertising. */
} esble_gapm_adv_start_cmd_t;

typedef struct _esble_gapm_adv_stop_cmd_t					/* Stop an Adv. */
{
	uint8_t		adv_idx;  									/* Adv identifier. */
} esble_gapm_adv_stop_cmd_t;

typedef struct _esble_gapm_create_scan_cmd_t
{
	uint8_t		own_addr_type;								/* Own address type (@see enum esble_own_addr_enum). */
} esble_gapm_create_scan_cmd_t;

typedef struct _esble_gapm_scan_wd_op_param_t 
{
    uint16_t 	scan_intv;									/* Scan interval. */
    uint16_t 	scan_wd; 									/* Scan window. */
}esble_gapm_scan_wd_op_param_t;

typedef struct _esble_gapm_scan_param_t
{
	uint8_t							type; 					/* Type of scanning to be started (@see enum esble_gapm_scan_type) */

	uint8_t							prop;					/* Properties for the scan procedure (@see enum esble_gapm_scan_prop for bit signification)*/

	uint8_t							dup_filt_pol;			/* Duplicate packet filtering policy*/

	uint8_t							rsvd;					/* Reserved for future use*/

	esble_gapm_scan_wd_op_param_t	scan_param_1m;			/* Scan window opening parameters for LE 1M PHY*/

	esble_gapm_scan_wd_op_param_t	scan_param_coded;		/* Scan window opening parameters for LE Coded PHY*/

	uint16_t						duration;				/*  Scan duration (in unit of 10ms). 0 means that the controller will scan continuously until
																reception of a stop command from the application*/

	uint16_t						period;					/* Scan period (in unit of 1.28s). Time interval betweem two consequent starts of a scan duration
																by the controller. 0 means that the scan procedure is not periodic*/
}esble_gapm_scan_param_t;

typedef struct _esble_gapm_scan_start_cmd_t
{
	uint8_t						scan_idx;					/* Scan identifier. */

	esble_gapm_scan_param_t		scan_param;					/* Scan parameters */
} esble_gapm_scan_start_cmd_t;

typedef struct _esble_gapm_scan_stop_cmd_t					/* Stop a Scan Activity. */
{
	uint8_t		scan_idx; 									/* Scan identifier. */
} esble_gapm_scan_stop_cmd_t;

typedef struct _esble_gapm_create_init_cmd_t
{
	uint8_t			own_addr_type;							/* Own address type (@see enum esble_own_addr_enum). */
} esble_gapm_create_init_cmd_t;

typedef struct _esble_gapm_conn_param_t						/* Connection parameters*/
{
	uint16_t			conn_intv_min;						/* Minimum value for the connection interval (in unit of 1.25ms). Shall be less than or equal to
																conn_intv_max value. Allowed range is 7.5ms to 4s.*/

	uint16_t			conn_intv_max;						/* Maximum value for the connection interval (in unit of 1.25ms). Shall be greater than or equal to
																conn_intv_min value. Allowed range is 7.5ms to 4s.*/

	uint16_t			conn_latency;						/* Slave latency. Number of events that can be missed by a connected slave device*/

	uint16_t			supervision_to;						/* Link supervision timeout (in unit of 10ms). Allowed range is 100ms to 32s*/

	uint16_t			ce_len_min;							/* Recommended minimum duration of connection events (in unit of 625us)*/

	uint16_t			ce_len_max;							/* Recommended maximum duration of connection events (in unit of 625us)*/
}esble_gapm_conn_param_t;

typedef struct _esble_gapm_init_param_t						/* Initiating parameters*/
{
	uint8_t								type;				/* Initiating type (@see enum esble_gapm_init_type)*/

	uint8_t								prop;				/* Properties for the initiating procedure (@see enum esble_gapm_init_prop for bit signification)*/

	uint16_t							conn_to;			/* Timeout for automatic connection establishment (in unit of 10ms). Cancel the procedure if not all
																indicated devices have been connected when the timeout occurs. 0 means there is no timeout*/

	esble_gapm_scan_wd_op_param_t		scan_param_1m;		/* Scan window opening parameters for LE 1M PHY*/

	esble_gapm_scan_wd_op_param_t		scan_param_coded;	/* Scan window opening parameters for LE Coded PHY*/

	esble_gapm_conn_param_t				conn_param_1m;		/* Connection parameters for LE 1M PHY*/

	esble_gapm_conn_param_t				conn_param_2m;		/* Connection parameters for LE 2M PHY*/

	esble_gapm_conn_param_t				conn_param_coded;	/* Connection parameters for LE Coded PHY*/

	esble_gap_bdaddr_t					peer_addr;			/* Address of peer device in case white list is not used for connection*/
}esble_gapm_init_param_t;

typedef struct _esble_gapm_init_start_cmd_t
{
	uint8_t						init_idx;					/* Init identifier. */

	esble_gapm_init_param_t		init_param;					/* Init parameters */
} esble_gapm_init_start_cmd_t;

typedef struct _esble_gapm_init_stop_cmd_t					/* Stop init actv. */
{
	uint8_t			init_idx;								/* Init identifier. */
} esble_gapm_init_stop_cmd_t;

typedef struct _esble_gapm_create_period_sync_cmd_t
{
	uint8_t			own_addr_type;							/* Own address type (@see enum esble_own_addr_enum). */
} esble_gapm_create_period_sync_cmd_t;

typedef struct _esble_gapm_set_period_adv_data_cmd_t
{
	uint8_t			adv_idx;								/* Adv identifier. */

	uint16_t		length;									/* Data length. */

	uint8_t			*data;									/* Data. */
} esble_gapm_set_period_adv_data_cmd_t;

typedef struct _esble_gapm_period_sync_start_cmd_t
{
	uint8_t		per_sync_idx;								/* Adv identifier. */

	uint16_t skip;											/*Number of periodic advertising that can be skipped after a successful receive. Maximum authorized value is 499*/

	uint16_t sync_to;										/*Synchronization timeout for the periodic advertising (in unit of 10ms between 100ms and 163.84s)*/

	uint8_t type;											/*Periodic synchronization type*/

	uint8_t rsvd;											/*Reserved for future use*/

	esble_gap_bdaddr_t addr;								/*Advertiser address information*/

	uint8_t adv_sid;										/*Advertising SID*/
} esble_gapm_period_sync_start_cmd_t;

typedef struct _esble_gapm_period_sync_stop_cmd_t			/* Stop a per sync act. */
{
	uint8_t		per_sync_idx;								/* Persync identifier. */
} esble_gapm_period_sync_stop_cmd_t;

typedef struct _esble_gapm_delet_actv_cmd_t					/* delete actv. */
{
	uint8_t			actv_idx;								/*Activity identifier*/
} esble_gapm_delet_actv_cmd_t;

typedef struct _esble_gapm_period_adv_addr_cfg_t			/* Periodic advertising information*/
{
	esble_gap_bdaddr_t		addr;							/* Advertiser address information*/

	uint8_t					adv_sid;						/* Advertising SID*/
} esble_gapm_period_adv_addr_cfg_t;

typedef struct _esble_gapm_set_pal_cmd_t					/* Set content of periodic advertiser list command*/
{
	uint8_t size;											/* Number of entries to be added in the list. 0 means that list content has to be cleared*/

	esble_gapm_period_adv_addr_cfg_t *pal_info;				/* List of entries to be added in the list*/
} esble_gapm_set_pal_cmd_t;

typedef struct _esble_gapm_use_enc_block_cmd_t
{
	uint8_t		operand_1[ESBLE_GAP_KEY_LEN];				/* Operand 1*/

	uint8_t		operand_2[ESBLE_GAP_KEY_LEN];				/* Operand 2*/
} esble_gapm_use_enc_block_cmd_t;

typedef struct _esble_gapm_set_irk_cmd_t					/* Set new IRK*/
{
	uint8_t		key[ESBLE_GAP_KEY_LEN];						/* Device IRK used for resolvable random BD address generation (LSB first)*/
} esble_gapm_set_irk_cmd_t;

typedef struct _esble_gapm_gen_dh_key_cmd_t
{
	uint8_t		operand_1[ESBLE_GAP_P256_KEY_LEN];			/* Operand 1*/

	uint8_t		operand_2[ESBLE_GAP_P256_KEY_LEN];			/* Operand 2*/
} esble_gapm_gen_dh_key_cmd_t;

typedef struct _esble_gapm_get_pub_key_cmd_t
{
	uint8_t renew;											/* 1 to renew, 0 to read current value*/
} esble_gapm_get_pub_key_cmd_t;

typedef struct _esble_gapm_get_ral_loc_addr_cmd_t			/* Read local address*/
{
	esble_gap_bdaddr_t		loc_identity;					/* local device identity*/
} esble_gapm_get_ral_loc_addr_cmd_t;

typedef struct _esble_gapm_get_ral_peer_addr_cmd_t			/* Read peer address*/
{
	esble_gap_bdaddr_t		peer_identity;					/* peer device identity*/
} esble_gapm_get_ral_peer_addr_cmd_t;

typedef struct _esble_gapm_resolv_addr_cmd_t				/* Resolve Address command*/
{
	uint8_t					nb_key;							/* Number of provided IRK (sahlle be > 0)*/

	esble_bd_addr_t			addr;							/* Resolvable random address to solve*/

	esble_gap_sec_key_t		*irk;							/* Array of IRK used for address resolution (MSB -> LSB)*/
} esble_gapm_resolv_addr_cmd_t;

typedef struct _esble_gapm_gen_rand_addr_cmd_t				/* Generate a random address.*/
{
	uint8_t			prand[ESBLE_GAP_ADDR_PRAND_LEN];		/* Dummy parameter used to store the prand part of the address*/

	uint8_t			rnd_type;								/* Random address type @see esble_gap_rnd_addr_type_enum. */
} esble_gapm_gen_rand_addr_cmd_t;

typedef struct _esble_gap_ral_dev_info_t					/* Resolving list device information*/
{
	esble_gap_bdaddr_t		addr;							/* Device identity*/

	uint8_t					priv_mode;						/* Privacy Mode*/

	uint8_t					peer_irk[ESBLE_GAP_KEY_LEN];	/* Peer IRK*/

	uint8_t					local_irk[ESBLE_GAP_KEY_LEN];	/* Local IRK*/
}esble_gap_ral_dev_info_t;

typedef struct _esble_gapm_set_ral_cmd_t					/* Set content of resolving list command (common part)*/
{
	uint8_t						size;						/* Number of entries to be added in the list. 0 means that list content has to be cleared*/

	esble_gap_ral_dev_info_t	*ral_info;					/* List of entries to be added in the list*/
} esble_gapm_set_ral_cmd_t;

typedef struct _esble_gapm_set_channel_map_cmd_t			/* Set device channel map. */
{
	esble_le_chnl_map_t		chmap;							/* Channel map. */
}esble_gapm_set_channel_map_cmd_t;

typedef struct _esble_gapm_list_set_cmd_t					/* Set content of either white list or resolving list or periodic advertiser list command (common part). */
{
	uint8_t			size;									/* Number of entries to be added in the list. 0 means that list content has to be cleared. */
}esble_gapm_list_set_cmd_t;

typedef struct _esble_gapm_list_set_wl_cmd_t					/* Set content of white list */
{
	uint8_t			size;									/* Number of entries to be added in the list. 0 means that list content has to be cleared. */
	esble_gap_bdaddr_t *wl_info;			/*List of entries to be added in the list.*/
}esble_gapm_list_set_wl_cmd_t;

typedef struct _esble_gapm_renew_addr_cmd_t					/* Request to renew all currently used random private addresses (non-resolvable or resolvable).For internal use only. */
{
	uint8_t			actv_idx;								/* Activity index, used by GAPM ADDR state machine in order to remind for which activitya new address has been generated. */

	uint8_t			init_scan_actv_idx;						/* Index of first created initiating/scanning for which address has been renewed,any initiating/scanning met after shall use the same address if it uses a random address. */
}esble_gapm_renew_addr_cmd_t;

typedef struct _esble_gapm_le_test_mode_ctrl_cmd_t			/* Control LE Test Mode command. */
{
	uint8_t			channel;								/* Tx or Rx Channel (Range 0x00 to 0x27). */

	uint8_t			tx_data_length;							/* Length in bytes of payload data in each packet (only valid for TX mode, range 0x00-0xFF). */

	uint8_t			tx_pkt_payload;							/* Packet Payload type (only valid for TX mode @see enum esble_gap_pkt_pld_type_enum). */

	uint8_t			phy;									/* Test PHY rate (@see enum esble_gap_test_phy_enum). */

	uint8_t			modulation_idx;							/* Modulation Index (only valid for RX mode @see enum esble_gap_modulation_idx_enum). */
}esble_gapm_le_test_mode_ctrl_cmd_t;

typedef struct _esble_gapm_lepsm_reg_cmd_t
{
	uint16_t	le_psm;									/* LE Protocol/Service Multiplexer. */

	uint16_t	app_task;								/* Application task number. */

	uint8_t		sec_lvl;								/* Security level.bit[0-1]: Security level requirement (0=NO_AUTH, 1=UNAUTH, 2=AUTH, 3=SEC_CON).bit[2]  : Encryption Key Size length must have 16 bytes.bit[7]  : Does the application task is multi-instantiated or not. */
} esble_gapm_lepsm_reg_cmd_t;

typedef struct _esble_gapm_lepsm_unreg_cmd_t
{
	uint16_t	le_psm;									/* LE Protocol/Service Multiplexer. */
} esble_gapm_lepsm_unreg_cmd_t;

SVCALL(ESBLE_GAPM_RESET, uint32_t, esble_gapm_reset(void));

SVCALL(ESBLE_GAPM_SET_DEV_CONF, uint32_t, esble_gapm_set_dev_conf(esble_gapm_set_dev_config_cmd_t *cmd));

SVCALL(ESBLE_GAPM_CREATE_ADV, uint32_t, esble_gapm_create_adv(esble_gapm_create_adv_cmd_t *cmd));

SVCALL(ESBLE_GAPM_SET_ADV_DATA, uint32_t, esble_gapm_set_adv_data(esble_gapm_adv_data_t *cmd));

SVCALL(ESBLE_GAPM_SET_SCAN_RSP_DATA, uint32_t, esble_gapm_set_scan_rsp_data(esble_gapm_adv_data_t *cmd));

SVCALL(ESBLE_GAPM_ADV_START, uint32_t, esble_gapm_adv_start(esble_gapm_adv_start_cmd_t *cmd));

SVCALL(ESBLE_GAPM_ADV_STOP, uint32_t, esble_gapm_adv_stop(esble_gapm_adv_stop_cmd_t *cmd));

SVCALL(ESBLE_GAPM_CREATE_SCAN, uint32_t, esble_gapm_create_scan(esble_gapm_create_scan_cmd_t *cmd));

SVCALL(ESBLE_GAPM_SCAN_START, uint32_t, esble_gapm_scan_start(esble_gapm_scan_start_cmd_t *cmd));

SVCALL(ESBLE_GAPM_SCAN_STOP, uint32_t, esble_gapm_scan_stop(esble_gapm_scan_stop_cmd_t *cmd));

SVCALL(ESBLE_GAPM_CREATE_INIT, uint32_t, esble_gapm_create_init(esble_gapm_create_init_cmd_t *cmd));

SVCALL(ESBLE_GAPM_INIT_START, uint32_t, esble_gapm_init_start(esble_gapm_init_start_cmd_t *cmd));

SVCALL(ESBLE_GAPM_INIT_STOP, uint32_t, esble_gapm_init_stop(esble_gapm_init_stop_cmd_t *cmd));

SVCALL(ESBLE_GAPM_CREATE_PERIOD_SYNC, uint32_t, esble_gapm_create_period_sync(esble_gapm_create_period_sync_cmd_t *cmd));

SVCALL(ESBLE_GAPM_SET_PERIOD_ADV_DATA, uint32_t, esble_gapm_set_period_adv_data(esble_gapm_set_period_adv_data_cmd_t *cmd));

SVCALL(ESBLE_GAPM_PERIOD_SYNC_START, uint32_t, esble_gapm_period_sync_start(esble_gapm_period_sync_start_cmd_t *cmd));

SVCALL(ESBLE_GAPM_PERIOD_SYNC_STOP, uint32_t, esble_gapm_period_sync_stop(esble_gapm_period_sync_stop_cmd_t *cmd));

SVCALL(ESBLE_GAPM_STOP_ALL_ACTIVITIES, uint32_t, esble_gapm_stop_all_acts(void));

SVCALL(ESBLE_GAPM_DELETE_ACTIVITY, uint32_t, esble_gapm_delete_actv(esble_gapm_delet_actv_cmd_t *cmd));

SVCALL(ESBLE_GAPM_DELETE_ALL_ACTIVITY, uint32_t, esble_gapm_delete_all_actv(void));

SVCALL(ESBLE_GAPM_GET_NB_ADV_SETS, uint32_t, esble_gapm_get_nb_adv_sets(void));

SVCALL(ESBLE_GAPM_GET_DEV_ADV_TX_POWER, uint32_t, esble_gapm_get_dev_adv_tx_power_sets(void));

SVCALL(ESBLE_GAPM_GET_MAX_LE_ADV_DATA_LEN, uint32_t, esble_gapm_get_max_le_adv_data_len(void));

SVCALL(ESBLE_GAPM_GET_PAL_SIZE, uint32_t, esble_gapm_get_pal_size(void));

SVCALL(ESBLE_GAPM_SET_PAL, uint32_t, esble_gapm_set_pal(esble_gapm_set_pal_cmd_t *cmd));

SVCALL(ESBLE_GAPM_USE_ENC_BLOCK, uint32_t, esble_gapm_use_enc_block(esble_gapm_use_enc_block_cmd_t *cmd));

SVCALL(ESBLE_GAPM_GEN_RAND_NB, uint32_t, esble_gapm_gen_rand_nb(void));

SVCALL(ESBLE_GAPM_SET_IRK, uint32_t, esble_gapm_set_irk(esble_gapm_set_irk_cmd_t *cmd));

SVCALL(ESBLE_GAPM_GEN_DH_KEY, uint32_t, esble_gapm_gen_dh_key(esble_gapm_gen_dh_key_cmd_t *cmd));

SVCALL(ESBLE_GAPM_GET_PUB_KEY, uint32_t, esble_gapm_get_pub_key(esble_gapm_get_pub_key_cmd_t *cmd));

SVCALL(ESBLE_GAPM_GET_RAL_LOC_ADDR, uint32_t, esble_gapm_get_ral_loc_addr(esble_gapm_get_ral_loc_addr_cmd_t *cmd));

SVCALL(ESBLE_GAPM_GET_RAL_PEER_ADDR, uint32_t, esble_gapm_get_ral_peer_addr(esble_gapm_get_ral_peer_addr_cmd_t *cmd));

SVCALL(ESBLE_GAPM_RESOLV_ADDR, uint32_t, esble_gapm_resolv_addr(esble_gapm_resolv_addr_cmd_t *cmd));

SVCALL(ESBLE_GAPM_GET_DEV_BDADDR, uint32_t, esble_gapm_get_dev_bdaddr(void));

SVCALL(ESBLE_GAPM_GET_RAL_SIZE, uint32_t, esble_gapm_get_ral_size(void));

SVCALL(ESBLE_GAPM_GEN_RAND_ADDR, uint32_t, esble_gapm_gen_rand_addr(esble_gapm_gen_rand_addr_cmd_t *cmd));

SVCALL(ESBLE_GAPM_SET_RAL, uint32_t, esble_gapm_set_ral(esble_gapm_set_ral_cmd_t *cmd));

SVCALL(ESBLE_GAPM_SET_CHANNEL_MAP, uint32_t, esble_gapm_set_channel_map(esble_gapm_set_channel_map_cmd_t *cmd));

SVCALL(ESBLE_GAPM_GET_DEV_VERSION, uint32_t, esble_gapm_get_dev_version(void));

SVCALL(ESBLE_GAPM_GET_DEV_TX_PWR, uint32_t, esble_gapm_get_dev_tx_pwr(void));

SVCALL(ESBLE_GAPM_GET_SUGGESTED_DFLT_LE_DATA_LEN, uint32_t, esble_gapm_get_suggested_dflt_le_data_len(void));

SVCALL(ESBLE_GAPM_GET_DEV_RF_PATH_COMP, uint32_t, esble_gapm_get_dev_rf_path_comp(void));

SVCALL(ESBLE_GAPM_GET_MAX_LE_DATA_LEN, uint32_t, esble_gapm_get_max_le_data_len(void));

SVCALL(ESBLE_GAPM_SET_WL, uint32_t, esble_gapm_set_wl(esble_gapm_list_set_wl_cmd_t *cmd));

SVCALL(ESBLE_GAPM_GET_WLIST_SIZE, uint32_t, esble_gapm_get_wlist_size(void));

SVCALL(ESBLE_GAPM_UNKNOWN_TASK_MSG, uint32_t, esble_gapm_unknown_task_msg(void));

SVCALL(ESBLE_GAPM_RENEW_ADDR, uint32_t, esble_gapm_renew_addr(esble_gapm_renew_addr_cmd_t *cmd));

SVCALL(ESBLE_GAPM_LE_TEST_RX_START, uint32_t, esble_gapm_le_test_rx_start(esble_gapm_le_test_mode_ctrl_cmd_t *cmd));

SVCALL(ESBLE_GAPM_LE_TEST_TX_START, uint32_t, esble_gapm_le_test_tx_start(esble_gapm_le_test_mode_ctrl_cmd_t *cmd));

SVCALL(ESBLE_GAPM_LE_TEST_STOP, uint32_t, esble_gapm_le_test_stop(esble_gapm_le_test_mode_ctrl_cmd_t *cmd));

SVCALL(ESBLE_GAPM_PLF_RESET, uint32_t, esble_gapm_plf_reset(void));

SVCALL(ESBLE_GAPM_DBG_GET_MEM_INFO, uint32_t, esble_gapm_dbg_get_mem_info(void));

SVCALL(ESBLE_GAPM_LEPSM_REG, uint32_t, esble_gapm_lepsm_reg(esble_gapm_lepsm_reg_cmd_t *cmd));

SVCALL(ESBLE_GAPM_LEPSM_UNREG, uint32_t, esble_gapm_lepsm_unreg(esble_gapm_lepsm_unreg_cmd_t *cmd));

/*****************************************************************************************************/
/**												上行事件											**/
/*****************************************************************************************************/

typedef enum _esble_gapm_evt_enum
{
	ESBLE_GAPM_CMP		= ESBLE_GAPM_BASE,
	ESBLE_GAPM_CREATE_ADV_IND,
	ESBLE_GAPM_START_ADV_IND,
	ESBLE_GAPM_STOP_ADV_IND,

	ESBLE_GAPM_CREATE_SCAN_IND,
	ESBLE_GAPM_START_SCAN_IND,
	ESBLE_GAPM_STOP_SCAN_IND,

	ESBLE_GAPM_CREATE_PER_SYNC_IND,
	ESBLE_GAPM_START_PER_SYNC_IND,
	ESBLE_GAPM_STOP_PER_SYNC_IND,

	ESBLE_GAPM_CREATE_INIT_IND,
	ESBLE_GAPM_START_INIT_IND,
	ESBLE_GAPM_STOP_INIT_IND,

	ESBLE_GAPM_STOP_ALL_IND,

	ESBLE_GAPM_NB_ADV_SETS_IND,
	ESBLE_GAPM_DEV_ADV_TX_POWER_IND,
	ESBLE_GAPM_MAX_ADV_DATA_LEN_IND,
	ESBLE_GAPM_EXT_ADV_REPORT_IND,
	ESBLE_GAPM_LIST_SIZE_IND,

	ESBLE_GAPM_USE_ENC_BLOCK_IND,
	ESBLE_GAPM_GEN_RAND_NB_IND,
	ESBLE_GAPM_GEN_DH_KEY_IND,
	ESBLE_GAPM_PUB_KEY_IND,

	ESBLE_GAPM_RAL_LOC_ADDR_IND,
	ESBLE_GAPM_RAL_PEER_ADDR_IND,
	ESBLE_GAPM_ADDR_SOLVED_IND,
	ESBLE_GAPM_DEV_BDADDR_IND,

	ESBLE_GAPM_DEV_VERSION_IND,
	ESBLE_GAPM_DEV_TX_PWR_IND,
	ESBLE_GAPM_SUGG_DFLT_DATA_LEN_IND,
	ESBLE_GAPM_DEV_RF_PATH_COMP_IND,
	ESBLE_GAPM_MAX_DATA_LEN_IND,

	ESBLE_GAPM_UNKNOWN_TASK_IND,
	ESBLE_GAPM_ADDR_RENEW_TO_IND,
	ESBLE_GAPM_AUTO_CONN_TO_IND,
	ESBLE_GAPM_LE_TEST_END_IND,
	ESBLE_GAPM_DBG_MEM_INFO_IND,
	ESBLE_GAPM_PEER_NAME_IND,
} esble_gapm_evt_enum;


typedef struct _esble_gapm_cmp_t
{
	esble_gapm_cmd_enum	cmd;

	uint8_t				status;
} esble_gapm_cmp_t;

typedef struct _esble_gapm_create_actv_ind_t
{
	uint8_t				actv_idx;						/* Activity identifier. */
	uint8_t				tx_pwr;							/* Selected TX power for advertising activity*/
} esble_gapm_create_actv_ind_t;

typedef struct _esble_gapm_start_actv_ind_t
{
	uint8_t				actv_idx;						/* Activity identifier. */

	uint8_t				status;							/* Status of Activity start. */
} esble_gapm_start_actv_ind_t;

typedef struct _esble_gapm_stop_actv_ind_t				/* Indicate that an activity has been stopped. */
{
	uint8_t				actv_idx;						/* Activity identifier. */

	uint8_t				reason;							/* Activity stop reason. */

	uint8_t				per_adv_stop;					/* In case of periodic advertising, indicate if periodic advertising has been stopped. */
} esble_gapm_stop_actv_ind_t;

typedef struct _esble_gapm_nb_adv_sets_ind_t
{
	uint8_t				nb_adv_sets;					/* Number of available advertising sets. */
} esble_gapm_nb_adv_sets_ind_t;

typedef struct _esble_gapm_dev_adv_tx_power_ind_t
{
	int8_t				power_lvl;						/* Advertising channel Tx power level. */
} esble_gapm_dev_adv_tx_power_ind_t;

typedef struct _esble_gapm_max_le_adv_data_len_ind_t	/* Maximum advertising data length indication event*/
{
	uint16_t length;									/* Maximum advertising data length supported by controller*/
} esble_gapm_max_le_adv_data_len_ind_t;

typedef struct _esble_gapm_ext_adv_report_ind_t
{
	uint8_t					actv_idx;					/* Activity identifier. */

	uint8_t					info;						/* Bit field providing information about the received report (@see enum esble_gapm_adv_report_info_enum). */

	esble_gap_bdaddr_t		trans_addr;					/* Transmitter device address. */

	esble_gap_bdaddr_t		target_addr;				/* Target address (in case of a directed advertising report). */

	int8_t					tx_pwr;						/* TX power (in dBm). */

	int8_t					rssi;						/* RSSI (between -127 and +20 dBm). */

	uint8_t					phy_prim;					/* Primary PHY on which advertising report has been received. */

	uint8_t					phy_second;					/* Secondary PHY on which advertising report has been received. */

	uint8_t					adv_sid;					/* Advertising SID,Valid only for periodic advertising report. */

	uint16_t				period_adv_intv;			/* Periodic advertising interval (in unit of 1.25ms, min is 7.5ms).Valid only for periodic advertising report. */

	uint16_t				length;						/* Report length. */

	uint8_t					data[];						/* Report. */
} esble_gapm_ext_adv_report_ind_t;

typedef struct _esble_gapm_list_size_ind_t				/* List Size indication event. */
{
	uint8_t		size;									/* List size. */
} esble_gapm_list_size_ind_t;

typedef struct _esble_gapm_use_enc_block_ind_t
{
	uint8_t		result[ESBLE_GAP_KEY_LEN];				/* Result (16 bytes). */
} esble_gapm_use_enc_block_ind_t;

typedef struct _esble_gapm_gen_rand_nb_ind_t
{
	uint8_t		nb[ESBLE_GAP_RAND_NB_LEN];				/* 8-byte array for random number. */
} esble_gapm_gen_rand_nb_ind_t;

typedef struct _esble_gapm_gen_dh_key_ind_t
{
	uint8_t		result[ESBLE_GAP_P256_KEY_LEN];			/* Result (32 bytes). */
} esble_gapm_gen_dh_key_ind_t;

typedef struct _esble_gapm_pub_key_ind_t
{
	uint8_t		pub_key_x[ESBLE_GAP_P256_KEY_LEN];		/* X coordinate. */

	uint8_t		pub_key_y[ESBLE_GAP_P256_KEY_LEN];		/* Y coordinate. */
} esble_gapm_pub_key_ind_t;

typedef struct _esble_gapm_ral_addr_ind_t				/* Resolving Address indication event. */
{
	esble_gap_bdaddr_t		addr;						/* Resolving List address. */
} esble_gapm_ral_addr_ind_t;

typedef struct _esble_gapm_addr_solved_ind_t
{
	esble_bd_addr_t			addr;						/* Resolvable random address solved. */

	esble_gap_sec_key_t		irk;						/* IRK that correctly solved the random address. */
} esble_gapm_addr_solved_ind_t;

typedef struct _esble_gapm_dev_bdaddr_ind_t				/* Local device BD Address indication event. */
{
	esble_gap_bdaddr_t		addr;						/* Local device address information. */

	uint8_t					actv_idx;					/* Activity index. */
} esble_gapm_dev_bdaddr_ind_t;

typedef struct _esble_gapm_dev_version_ind_t			/* Local device version indication event. */
{
	uint8_t			hci_ver;							/* HCI version. */

	uint8_t			lmp_ver;							/* LMP version. */

	uint8_t			host_ver;							/* Host version. */

	uint16_t		hci_subver;							/* HCI revision. */

	uint16_t		lmp_subver;							/* LMP subversion. */

	uint16_t		host_subver;						/* Host revision. */

	uint16_t		manuf_name;							/* Manufacturer name. */
} esble_gapm_dev_version_ind_t;

typedef struct _esble_gapm_dev_tx_pwr_ind_t				/* Indicate the transmit powers supported by the controller. */
{
	int8_t			min_tx_pwr;							/* Minimum TX power. */

	int8_t			max_tx_pwr;							/* Maximum TX power. */
} esble_gapm_dev_tx_pwr_ind_t;

typedef struct _esble_gapm_sugg_dflt_data_len_ind_t		/* Indicates suggested default data length. */
{
	uint16_t	suggted_max_tx_octets;					/* Host's suggested value for the Controller's maximum transmitted number of payload octets. */

	uint16_t	suggted_max_tx_time;					/* Host's suggested value for the Controller's maximum packet transmission time. */
} esble_gapm_sugg_dflt_data_len_ind_t;

typedef struct _esble_gapm_dev_rf_path_comp_ind_t		/* Indicate the RF path compensation values. */
{
	uint16_t	tx_path_comp;							/* RF TX path compensation. */

	uint16_t	rx_path_comp;							/* RF RX path compensation. */
} esble_gapm_dev_rf_path_comp_ind_t;

typedef struct _esble_gapm_max_data_len_ind_t			/* Indicates maximum data length. */
{
	uint16_t	suppted_max_tx_octets;					/* Maximum number of payload octets that the local Controller supports for transmission. */

	uint16_t	suppted_max_tx_time;					/* Maximum time, in microseconds, that the local Controller supports for transmission. */

	uint16_t	suppted_max_rx_octets;					/* Maximum number of payload octets that the local Controller supports for reception. */

	uint16_t	suppted_max_rx_time;					/* Maximum time, in microseconds, that the local Controller supports for reception. */
} esble_gapm_max_data_len_ind_t;

typedef struct _esble_gapm_unknown_task_ind_t			/* Indicate that a message has been received on an unknown task. */
{
	uint16_t	msg_id;									/* Message identifier. */

	uint16_t	task_id;								/* Task identifier. */
} esble_gapm_unknown_task_ind_t;

typedef struct _esble_gapm_le_test_end_ind_t			/* Indicate end of test mode event. */
{
	uint16_t	nb_packet_received;						/* Number of received packets. */
} esble_gapm_le_test_end_ind_t;

typedef struct _esble_gapm_profile_added_ind_t			/* Inform that profile task has been added. */
{
	uint16_t		prf_task_id;						/* Profile task identifier. */

	uint16_t		prf_task_nb;						/* Profile task number allocated. */

	uint16_t		start_hdl;							/* Service start handle,Only applies for services - Ignored by collectors. */
} esble_gapm_profile_added_ind_t;

typedef struct _esble_gapm_dbg_mem_info_ind_t			/* Indication containing information about memory usage. */
{
	uint32_t		max_mem_used;						/* peak of memory usage measured. */

	uint16_t		mem_used[ESBLE_KE_MEM_BLOCK_MAX];	/* memory size currently used into each heaps. */
} esble_gapm_dbg_mem_info_ind_t;

typedef struct _esble_gapm_peer_name_ind_t				/* Name of peer device indication. */
{
	esble_bd_addr_t		addr;							/* peer device bd address. */

	uint8_t				addr_type;						/* peer device address type. */

	uint8_t				name_len;						/* peer device name length. */

	uint8_t				*name;							/* peer device name. */
} esble_gapm_peer_name_ind_t;

typedef struct _esble_gapm_evt_t
{
	union
	{
		esble_gapm_cmp_t								gapm_cmp;
		esble_gapm_create_actv_ind_t					create_actv;
		esble_gapm_start_actv_ind_t						start_actv;
		esble_gapm_stop_actv_ind_t						stop_actv;
		esble_gapm_nb_adv_sets_ind_t					nb_adv_sets;
		esble_gapm_dev_adv_tx_power_ind_t				dev_adv_tx_power;
		esble_gapm_max_le_adv_data_len_ind_t			max_le_adv_data_len;
		esble_gapm_ext_adv_report_ind_t					ext_adv_report;
		esble_gapm_list_size_ind_t						list_size;
		esble_gapm_use_enc_block_ind_t					use_enc_block;
		esble_gapm_gen_rand_nb_ind_t					gen_rand_nb;
		esble_gapm_gen_dh_key_ind_t						gen_dh_key;
		esble_gapm_pub_key_ind_t						pub_key;
		esble_gapm_ral_addr_ind_t						ral_addr;
		esble_gapm_addr_solved_ind_t					addr_solved;
		esble_gapm_dev_bdaddr_ind_t						dev_bdaddr;
		esble_gapm_dev_version_ind_t					dev_version;
		esble_gapm_dev_tx_pwr_ind_t						dev_tx_pwr;
		esble_gapm_sugg_dflt_data_len_ind_t				sugg_dflt_data_len;
		esble_gapm_dev_rf_path_comp_ind_t				dev_rf_path_comp;
		esble_gapm_max_data_len_ind_t					max_data_len;
		esble_gapm_unknown_task_ind_t					unknown_task;
		esble_gapm_le_test_end_ind_t					le_test_end;
		esble_gapm_profile_added_ind_t					profile_added;
		esble_gapm_dbg_mem_info_ind_t					dbg_mem_info;
		esble_gapm_peer_name_ind_t						peer_name;
	} param;
} esble_gapm_evt_t;


typedef void (*esble_gapm_cb_t)(esble_gapm_evt_enum id, const esble_gapm_evt_t *evt);

#endif
