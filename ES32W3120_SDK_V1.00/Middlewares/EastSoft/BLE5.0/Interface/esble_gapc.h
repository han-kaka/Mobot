#ifndef _ESBLE_GAPC_H_
#define _ESBLE_GAPC_H_

#include <stdbool.h>
#include "esble.h"

#define ESBLE_GAPC_INVALID_CONIDX						0xFF

typedef enum _esble_gapc_dev_info_enum						/* List of device info that should be provided by application. */
{
	ESBLE_GAPC_DEV_NAME,									/* Device Name. */

	ESBLE_GAPC_DEV_APPEARANCE,								/* Device Appearance Icon. */

	ESBLE_GAPC_DEV_SLV_PREF_PARAMS,							/* Device Slave preferred parameters. */

	ESBLE_GAPC_DEV_CTL_ADDR_RESOL,							/* Device Central address resolution. */

	ESBLE_GAPC_DEV_INFO_MAX,								/* maximum device info parameter. */
} esble_gapc_dev_info_enum;

typedef enum _esble_gapc_bond_enum							/* Bond event type. */
{
	ESBLE_GAPC_PAIRING_REQ,									/* Bond Pairing request. */

	ESBLE_GAPC_PAIRING_RSP,									/* Respond to Pairing request. */

	ESBLE_GAPC_PAIRING_SUCCEED,								/* Pairing Finished information. */

	ESBLE_GAPC_PAIRING_FAILED,								/* Pairing Failed information. */

	ESBLE_GAPC_TK_EXCH,										/* Used to retrieve pairing Temporary Key. */

	ESBLE_GAPC_IRK_EXCH,									/* Used for Identity Resolving Key exchange. */

	ESBLE_GAPC_CSRK_EXCH,									/* Used for Connection Signature Resolving Key exchange. */

	ESBLE_GAPC_LTK_EXCH,									/* Used for Long Term Key exchange. */

	ESBLE_GAPC_REPEATED_ATTEMPT,							/* Bond Pairing request issue, Repeated attempt. */

	ESBLE_GAPC_OOB_EXCH,									/* Out of Band - exchange of confirm and rand. */

	ESBLE_GAPC_NC_EXCH										/* Numeric Comparison - Exchange of Numeric Value. */
}esble_gapc_bond_enum;

typedef enum _esble_gapc_phy_option							/* Option for PHY configuration. */
{
	ESBLE_GAPC_PHY_OPT_LE_CODED_ALL_RATES	= (1 << 0),		/* No preference for rate used when transmitting on the LE Coded PHY. */

	ESBLE_GAPC_PHY_OPT_LE_CODED_500K_RATE	= (1 << 1),		/* 500kbps rate preferred when transmitting on the LE Coded PHY. */

	ESBLE_GAPC_PHY_OPT_LE_CODED_125K_RATE	= (1 << 2),		/* 125kbps  when transmitting on the LE Coded PHY. */
}esble_gapc_phy_option;

typedef struct _esble_gapc_dev_name_t
{
	uint16_t	length;

	uint8_t		*name;
} esble_gapc_dev_name_t;

typedef struct _esble_gapc_slv_pref_t
{
	uint16_t	con_intv_min;								/* Connection interval minimum. */

	uint16_t	con_intv_max;								/* Connection interval maximum. */

	uint16_t	slave_latency;								/* Slave latency. */

	uint16_t	conn_timeout;								/* Connection supervision timeout multiplier. */
} esble_gapc_slv_pref_t;

typedef struct _esble_gapc_ltk_t
{
	esble_gap_sec_key_t		ltk;							/* Long Term Key. */

	uint16_t				ediv;							/* Encryption Diversifier. */

	esble_rand_nb_t			randnb;							/* Random Number. */

	uint8_t					key_size;						/* Encryption key size (7 to 16). */
} esble_gapc_ltk_t;

typedef struct _esble_gapc_pairing_t
{
	uint8_t iocap;											/* IO capabilities (@see esble_gap_io_cap_enum). */

	uint8_t oob;											/* OOB information (@see esble_gap_oob_enum). */

	uint8_t auth;											/* Authentication (@see esble_gap_auth_enum). */

	uint8_t key_size;										/* Encryption key size (7 to 16). */

	uint8_t ikey_dist;										/* Initiator key distribution (@see esble_gap_kdist_enum). */

	uint8_t rkey_dist;										/* Responder key distribution (@see esble_gap_kdist_enum). */

	uint8_t sec_req;										/* Device security requirements (minimum security level). (@see esble_gap_sec_req_enum). */
} esble_gapc_pairing_t;

typedef struct _esble_gapc_irk_t							/* Identity Resolving Key information. */
{
	esble_gap_sec_key_t		irk;							/* Identity Resolving Key. */

	esble_gap_bdaddr_t		addr;							/* Device BD Identity Address. */
}esble_gapc_irk_t;

typedef struct _esble_gapc_oob_t							/* Out of Band Information. */
{
	uint8_t		conf[ESBLE_GAP_KEY_LEN];					/* Confirm Value. */

	uint8_t		rand[ESBLE_GAP_KEY_LEN];					/* Random Number. */
}esble_gapc_oob_t;

typedef struct _esble_gapc_bond_auth_t						/* Authentication information. */
{
	uint8_t		info;										/* Authentication information (@see esble_gap_auth_enum). */

	bool		ltk_present;								/* LTK exchanged during pairing. */
}esble_gapc_bond_auth_t;

typedef struct _esble_gapc_nc_t								/* Numeric Comparison Data. */
{
	uint8_t		value[4];
}esble_gapc_nc_t;

typedef union _esble_gapc_bond_data_t
{
	esble_gapc_bond_auth_t		auth;						/* Authentication information (@see esble_gap_auth_enum) (if info = ESBLE_GAPC_PAIRING_SUCCEED)@trc_union parent.info == ESBLE_GAPC_PAIRING_SUCCEED. */

	uint8_t						reason;						/* Pairing failed reason  (if info = ESBLE_GAPC_PAIRING_FAILED) @trc_union parent.info == ESBLE_GAPC_PAIRING_FAILED. */

	esble_gapc_ltk_t			ltk;						/* Long Term Key information (if info = ESBLE_GAPC_LTK_EXCH) @trc_union parent.info == ESBLE_GAPC_LTK_EXCH. */

	esble_gapc_irk_t			irk;						/* Identity Resolving Key information (if info = ESBLE_GAPC_IRK_EXCH) @trc_union parent.info == ESBLE_GAPC_IRK_EXCH. */

	esble_gap_sec_key_t			csrk;						/* Connection Signature Resolving Key information (if info = ESBLE_GAPC_CSRK_EXCH) @trc_union parent.info == ESBLE_GAPC_CSRK_EXCH. */
}esble_gapc_bond_data_t;

typedef union _esble_gapc_bond_req_data_t					/* Identity Resolving Key information. */
{
	uint8_t					auth_req;						/* Authentication level (@see esble_gap_auth_enum) (if request = ESBLE_GAPC_PAIRING_REQ) @trc_union parent.request == ESBLE_GAPC_PAIRING_REQ. */

	uint8_t					key_size;						/* LTK Key Size (if request = ESBLE_GAPC_LTK_EXCH) @trc_union parent.request == ESBLE_GAPC_LTK_EXCH. */

	uint8_t					tk_type;						/* Device IO used to get TK(@see esble_gap_tk_type_enum) (if request = ESBLE_GAPC_TK_EXCH) @trc_union parent.request == ESBLE_GAPC_TK_EXCH. */

	esble_gapc_oob_t		oob_data;						/* Addition OOB Data for the OOB Conf and Rand values @trc_union parent.request == ESBLE_GAPC_OOB_EXCH. */

	esble_gapc_nc_t			nc_data;						/* Numeric Comparison Data @trc_union parent.request == ESBLE_GAPC_NC_EXCH. */
}esble_gapc_bond_req_data_t;

typedef union _esble_gapc_bond_cfm_data_t					/* Bond procedure information data @trc_ref esble_gapc_bond_enum. */
{
	esble_gapc_pairing_t	pairing_feat;					/* pairing Features (request = ESBLE_GAPC_PAIRING_RSP) @trc_union parent.request == ESBLE_GAPC_PAIRING_RSP. */

	esble_gapc_ltk_t		ltk;							/* LTK (request = ESBLE_GAPC_LTK_EXCH) @trc_union parent.request == ESBLE_GAPC_LTK_EXCH. */

	esble_gap_sec_key_t		csrk;							/* CSRK (request = ESBLE_GAPC_CSRK_EXCH) @trc_union parent.request == ESBLE_GAPC_CSRK_EXCH. */

	esble_gap_sec_key_t		tk;								/* TK (request = ESBLE_GAPC_TK_EXCH) @trc_union parent.request == ESBLE_GAPC_TK_EXCH. */

	esble_gapc_irk_t		irk;							/* IRK (request = ESBLE_GAPC_IRK_EXCH) @trc_union parent.request == ESBLE_GAPC_IRK_EXCH. */

	esble_gapc_oob_t		oob;							/* OOB Confirm and Random from the peer (request = ESBLE_GAPC_OOB_EXCH) @trc_union parent.request == ESBLE_GAPC_OOB_EXCH. */
} esble_gapc_bond_cfm_data_t;



/*****************************************************************************************************/
/**												下行命令											**/
/*****************************************************************************************************/

typedef enum _esble_gapc_cmd_enum
{
	ESBLE_GAPC_DEV_INFO_CFM		= ESBLE_GAPC_BASE,
	ESBLE_GAPC_CONN_CFM,

	ESBLE_GAPC_DISCONN,
	ESBLE_GAPC_PARAM_UPD,
	ESBLE_GAPC_PARAM_UPDATE_CFM,
	ESBLE_GAPC_SET_PREF_SLV_LATENCY,
	ESBLE_GAPC_GET_CON_RSSI,
	ESBLE_GAPC_GET_CON_CNL_MAP,
	ESBLE_GAPC_ENCRYPT,
	ESBLE_GAPC_ENCRYPT_CFM,
	ESBLE_GAPC_SEC,
	ESBLE_GAPC_KEY_PRESS_NOTIF,
	ESBLE_GAPC_BOND,
	ESBLE_GAPC_BOND_CFM,
	ESBLE_GAPC_GET_ADDR_RESOL_SUPP,
	ESBLE_GAPC_GET_PEER_NAME,
	ESBLE_GAPC_GET_PEER_VERSION,
	ESBLE_GAPC_GET_PEER_FEATURES,
	ESBLE_GAPC_GET_PEER_APPEARANCE,
	ESBLE_GAPC_GET_PEER_SLV_PREF_PARAMS,
	ESBLE_GAPC_GET_PHY,
	ESBLE_GAPC_GET_CHAN_SEL_ALGO,
	ESBLE_GAPC_SET_DEV_INFO_CFM,
	ESBLE_GAPC_SET_LE_PING_TO,
	ESBLE_GAPC_GET_LE_PING_TO,
	ESBLE_GAPC_SIGN_PACKET,
	ESBLE_GAPC_SIGN_CHECK,
	ESBLE_GAPC_SET_PHY,
	ESBLE_GAPC_SET_LE_PKT_SIZE,
} esble_gapc_cmd_enum;

typedef struct _esble_gapc_dev_info_cfm_t
{
	uint8_t		conidx;

	uint8_t		req;

	union
	{
		esble_gapc_dev_name_t	name;
		uint16_t				appearance;
		esble_gapc_slv_pref_t	slv_pref_params;
		uint8_t					ctl_addr_resol;
	} info;
} esble_gapc_dev_info_cfm_t;

typedef struct _esble_gapc_conn_cfm_t
{
	uint8_t				conidx;

	esble_gap_sec_key_t	lcsrk;								/* Local CSRK value. */

	uint32_t			lsign_counter;						/* Local signature counter value. */

	esble_gap_sec_key_t	rcsrk;								/* Remote CSRK value. */

	uint32_t			rsign_counter;						/* Remote signature counter value. */

	uint8_t				auth;								/* Authentication (@see esble_gap_auth_enum). */

	uint8_t				svc_changed_ind_enable;				/* Service Changed Indication enabled. */

	bool				ltk_present;						/* LTK exchanged during pairing. */
} esble_gapc_conn_cfm_t;

typedef struct _esble_gapc_disconn_cmd_t					/* Request disconnection of current link command. */
{
	uint8_t reason;											/* Reason of disconnection. */
} esble_gapc_disconn_cmd_t;

typedef struct _esble_gapc_param_update_cmd_t				/* Perform update of connection parameters command. */
{
	uint8_t		conidx;

	uint8_t		pkt_id;										/* Internal parameter used to manage internally l2cap packet identifier for signaling. */

	uint16_t	intv_min;									/* Connection interval minimum. */

	uint16_t	intv_max;									/* Connection interval maximum. */

	uint16_t	latency;									/* Latency. */

	uint16_t	time_out;									/* Supervision timeout. */

	uint16_t	ce_len_min;									/* Minimum Connection Event Duration. */

	uint16_t	ce_len_max;									/* Maximum Connection Event Duration. */
} esble_gapc_param_upd_cmd_t;


typedef struct _esble_gapc_param_update_cfm_t				/*Master confirm or not that parameters proposed by slave are accepted or not*/
{
	uint8_t		conidx;

	bool accept;											/*True to accept slave connection parameters, False else.*/

	uint16_t ce_len_min;									/*Minimum Connection Event Duration*/

	uint16_t ce_len_max;									/*Maximum Connection Event Duration*/
}esble_gapc_param_update_cfm_t;

typedef struct _esble_gapc_set_pref_slv_latency_cmd_t		/* Set the preferred slave latency (for slave only, with RW controller). */
{
	uint8_t		conidx;

	uint16_t latency;										/* Preferred latency that the controller should use on a connection (in number of connection events). */
} esble_gapc_set_pref_slv_latency_cmd_t;

typedef struct _esble_gapc_encrypt_cmd_t					/* Start Encryption command procedure. */
{
	uint8_t				conidx;

	esble_gapc_ltk_t	ltk;								/* Long Term Key information. */
} esble_gapc_encrypt_cmd_t;

typedef struct _esble_gapc_encrypt_cfm_t					/* Confirm requested Encryption information. */
{
	uint8_t				conidx;

	uint8_t				found;								/* Indicate if a LTK has been found for the peer device. */

	esble_gap_sec_key_t	ltk;								/* Long Term Key. */

	uint8_t				key_size;							/* LTK Key Size. */
} esble_gapc_encrypt_cfm_t;

typedef struct _esble_gapc_sec_cmd_t						/* Start Security Request command procedure. */
{
	uint8_t				conidx;

	uint8_t				auth;								/* Authentication level (@see esble_gap_auth_enum). */
} esble_gapc_sec_cmd_t;

typedef struct _esble_gapc_key_press_notif_cmd_t			/* Request to inform the remote device when keys have been entered or erased. */
{
	uint8_t			conidx;

	uint8_t			notification_type;						/* notification type. */
} esble_gapc_key_press_notif_cmd_t;


typedef struct _esble_gapc_bond_cmd_t						/* Start Bonding command procedure. */
{
	uint8_t					conidx;

	esble_gapc_pairing_t	pairing;						/* Pairing information. */
} esble_gapc_bond_cmd_t;

typedef struct _esble_gapc_bond_cfm_t						/* Confirm requested bond information. */
{
	uint8_t						conidx;

	uint8_t						request;					/* Bond request type (@see esble_gapc_bond_enum). */

	uint8_t						accept;						/* Request accepted. */

	esble_gapc_bond_cfm_data_t	data;						/* Bond procedure information data. */
} esble_gapc_bond_cfm_t;

typedef struct _esble_gapc_set_dev_info_cfm_t				/* Local device accept or reject device info modification. */
{
	uint8_t						conidx;

	uint8_t						req;						/* Requested information.ESBLE_GAPC_DEV_NAME: Device Name.ESBLE_GAPC_DEV_APPEARANCE: Device Appearance Icon */

	uint8_t						status;						/* Request accepted. */
} esble_gapc_set_dev_info_cfm_t;

typedef struct _esble_gapc_set_le_ping_to_cmd_t
{
	uint8_t				conidx;

	uint16_t			timeout;							/* Authenticated payload timeout. */
} esble_gapc_set_le_ping_to_cmd_t;

typedef struct _esble_gapc_get_le_ping_to_cmd_t
{
	uint8_t				conidx;

	uint16_t			timeout;							/* Authenticated payload timeout. */
} esble_gapc_get_le_ping_to_cmd_t;

typedef struct _esble_gapc_sign_cmd_t
{
	uint8_t				conidx;

	uint16_t			byte_len;							/* Data PDU length (Bytes). */

	uint8_t				*msg;								/* Data PDU + SignCounter if generation, Data PDU + SignCounter + MAC if verification. */
} esble_gapc_sign_cmd_t;

typedef struct _esble_gapc_set_phy_cmd_t					/* Set the PHY configuration for current active link. */
{
	uint8_t				conidx;

	uint8_t				tx_phy;								/* Supported LE PHY for data transmission (@see enum esble_gap_phy_enum). */

	uint8_t				rx_phy;								/* Supported LE PHY for data reception (@see enum esble_gap_phy_enum). */

	uint8_t				phy_opt;							/* PHY options (@see enum esble_gapc_phy_option). */
} esble_gapc_set_phy_cmd_t;

typedef struct _esble_gapc_set_le_pkt_size_cmd_t			/* LE Set Data Length Command. */
{
	uint8_t				conidx;

	uint16_t			tx_octets;								/* Preferred maximum number of payload octets that the local Controller should include in a single Link Layer Data Channel PDU. */

	uint16_t			tx_time;								/* Preferred maximum number of microseconds that the local Controller should use to transmit a single Link Layer Data Channel PDU. */
} esble_gapc_set_le_pkt_size_cmd_t;


SVCALL(ESBLE_GAPC_DEV_INFO_CFM, uint32_t, esble_gapc_dev_info_cfm(esble_gapc_dev_info_cfm_t *cfm));

SVCALL(ESBLE_GAPC_CONN_CFM, uint32_t, esble_gapc_conn_cfm(esble_gapc_conn_cfm_t *cfm));

SVCALL(ESBLE_GAPC_DISCONN, uint32_t, esble_gapc_disconn(esble_gapc_disconn_cmd_t *cmd));

SVCALL(ESBLE_GAPC_PARAM_UPD, uint32_t, esble_gapc_param_upd(esble_gapc_param_upd_cmd_t *cmd));

SVCALL(ESBLE_GAPC_PARAM_UPDATE_CFM, uint32_t, esble_gapc_param_upd_cfm(esble_gapc_param_update_cfm_t *cfm));

SVCALL(ESBLE_GAPC_SET_PREF_SLV_LATENCY, uint32_t, esble_gapc_set_pref_slv_latency(esble_gapc_set_pref_slv_latency_cmd_t *cmd));

SVCALL(ESBLE_GAPC_GET_CON_RSSI, uint32_t, esble_gapc_get_con_rssi(void));

SVCALL(ESBLE_GAPC_GET_CON_CNL_MAP, uint32_t, esble_gapc_get_con_cnl_map(void));

SVCALL(ESBLE_GAPC_ENCRYPT, uint32_t, esble_gapc_encrypt(esble_gapc_encrypt_cmd_t *cmd));

SVCALL(ESBLE_GAPC_ENCRYPT_CFM, uint32_t, esble_gapc_encrypt_cfm(esble_gapc_encrypt_cfm_t *cfm));

SVCALL(ESBLE_GAPC_SEC, uint32_t, esble_gapc_sec(esble_gapc_sec_cmd_t *cmd));

SVCALL(ESBLE_GAPC_KEY_PRESS_NOTIF, uint32_t, esble_gapc_key_press_notif(esble_gapc_key_press_notif_cmd_t *cmd));

SVCALL(ESBLE_GAPC_BOND, uint32_t, esble_gapc_bond(esble_gapc_bond_cmd_t *cmd));

SVCALL(ESBLE_GAPC_BOND_CFM, uint32_t, esble_gapc_bond_cfm(esble_gapc_bond_cfm_t *cfm));

SVCALL(ESBLE_GAPC_GET_ADDR_RESOL_SUPP, uint32_t, esble_gapc_get_addr_resol_supp(void));

SVCALL(ESBLE_GAPC_GET_PEER_NAME, uint32_t, esble_gapc_get_peer_name(void));

SVCALL(ESBLE_GAPC_GET_PEER_VERSION, uint32_t, esble_gapc_get_peer_version(void));

SVCALL(ESBLE_GAPC_GET_PEER_FEATURES, uint32_t, esble_gapc_get_peer_features(void));

SVCALL(ESBLE_GAPC_GET_PEER_APPEARANCE, uint32_t, esble_gapc_get_peer_appearance(void));

SVCALL(ESBLE_GAPC_GET_PEER_SLV_PREF_PARAMS, uint32_t, esble_gapc_get_peer_slv_pref_params(void));

SVCALL(ESBLE_GAPC_GET_PHY, uint32_t, esble_gapc_get_phy(void));

SVCALL(ESBLE_GAPC_GET_CHAN_SEL_ALGO, uint32_t, esble_gapc_get_chan_sel_algo(void));

SVCALL(ESBLE_GAPC_SET_DEV_INFO_CFM, uint32_t, esble_gapc_set_dev_info_cfm(esble_gapc_set_dev_info_cfm_t *cfm));

SVCALL(ESBLE_GAPC_SET_LE_PING_TO, uint32_t, esble_gapc_set_le_ping_to(esble_gapc_set_le_ping_to_cmd_t *cmd));

SVCALL(ESBLE_GAPC_GET_LE_PING_TO, uint32_t, esble_gapc_get_le_ping_to(void));

SVCALL(ESBLE_GAPC_SIGN_PACKET, uint32_t, esble_gapc_sign_packet(esble_gapc_sign_cmd_t *cmd));

SVCALL(ESBLE_GAPC_SIGN_CHECK, uint32_t, esble_gapc_sign_check(esble_gapc_sign_cmd_t *cmd));

SVCALL(ESBLE_GAPC_SET_PHY, uint32_t, esble_gapc_set_phy(esble_gapc_set_phy_cmd_t *cmd));

SVCALL(ESBLE_GAPC_SET_LE_PKT_SIZE, uint32_t, esble_gapc_set_le_pkt_size(esble_gapc_set_le_pkt_size_cmd_t *cmd));


/*****************************************************************************************************/
/**												上行事件											**/
/*****************************************************************************************************/

typedef enum _esble_gapc_evt_enum
{
	ESBLE_GAPC_CMP				= ESBLE_GAPC_BASE,
	ESBLE_GAPC_DEV_INFO_REQ_IND,
	ESBLE_GAPC_CONN_REQ_IND,
	ESBLE_GAPC_DISCONN_IND,
	ESBLE_GAPC_PARAM_UPD_TO_IND,
	ESBLE_GAPC_PARAM_UPD_IND,
	ESBLE_GAPC_PARAM_UPD_REQ_IND,
	ESBLE_GAPC_CON_RSSI_IND,
	ESBLE_GAPC_CON_CNL_MAP_IND,
	ESBLE_GAPC_ENCRYPT_IND,
	ESBLE_GAPC_ENCRYPT_REQ_IND,
	ESBLE_GAPC_SEC_IND,
	ESBLE_GAPC_KEY_PRESS_NOTIF_IND,
	ESBLE_GAPC_SIGN_CNT_IND,
	ESBLE_GAPC_SMP_REP_ATTEMPTS_TIMER_IND,
	ESBLE_GAPC_SMP_TO_TIMER_IND,
	ESBLE_GAPC_BOND_IND,
	ESBLE_GAPC_BOND_REQ_IND,
	ESBLE_GAPC_PEER_VERSION_IND,
	ESBLE_GAPC_PEER_FEATURES_IND,
	ESBLE_GAPC_PEER_ATT_INFO_IND,
	ESBLE_GAPC_LE_PHY_IND,
	ESBLE_GAPC_CHAN_SEL_ALGO_IND,
	ESBLE_GAPC_SET_DEV_INFO_REQ_IND,
	ESBLE_GAPC_LE_PING_TO_IND,
	ESBLE_GAPC_LE_PING_TO_VAL_IND,
	ESBLE_GAPC_SIGN_IND,
	ESBLE_GAPC_LE_PKT_SIZE_IND,
	
} esble_gapc_evt_enum;

typedef struct _esble_gapc_dev_info_req_ind_t				/* Peer device request local device info such as name, appearance or slave preferred parameters. */
{
	uint8_t		conidx;
	uint8_t		req;										/* Requested information. */
} esble_gapc_dev_info_req_ind_t;

typedef struct _esble_gapc_conn_req_ind_t					/* Indicate that a connection has been established. */
{
	uint8_t			conidx;

	uint16_t		conhdl;									/* Connection handle. */

	uint8_t			role;									/*Device role - 0=Master/ 1=Slave*/

	uint16_t		con_interval;							/* Connection interval. */

	uint16_t		con_latency;							/* Connection latency. */

	uint16_t		sup_to;									/* Link supervision timeout. */

	uint8_t			clk_accuracy;							/* Clock accuracy. */

	uint8_t			peer_addr_type;							/* Peer address type. */

	esble_bd_addr_t	peer_addr;								/* Peer BT address. */
} esble_gapc_conn_req_ind_t;

typedef struct _esble_gapc_disconn_ind_t					/* Indicate that a link has been disconnected. */
{
	uint8_t		conidx;

	uint16_t	conhdl;										/* Connection handle. */

	uint8_t		reason;										/* Reason of disconnection. */
} esble_gapc_disconn_ind_t;

typedef struct _esble_gapc_param_upd_ind_t					/* Connection parameters updated indication. */
{
	uint8_t		conidx;

	uint16_t	con_interval;								/* Connection interval value. */

	uint16_t	con_latency;								/* Connection latency value. */

	uint16_t	sup_to;										/* Supervision timeout. */
} esble_gapc_param_upd_ind_t;

typedef struct _esble_gapc_param_upd_req_ind_t				/* Request of updating connection parameters indication. */
{
	uint8_t		conidx;

	uint16_t	intv_min;									/* Connection interval minimum. */

	uint16_t	intv_max;									/* Connection interval maximum. */

	uint16_t	latency;									/* Latency. */

	uint16_t time_out;										/* Supervision timeout. */
} esble_gapc_param_upd_req_ind_t;

typedef struct _esble_gapc_con_rssi_ind_t					/* Indication of ongoing connection RSSI. */
{
	uint8_t		conidx;

	int8_t		rssi;										/* RSSI value. */
} esble_gapc_con_rssi_ind_t;

typedef struct _esble_gapc_con_cnl_map_ind_t				/* Indication of ongoing connection Channel Map. */
{
	uint8_t					conidx;
	
	esble_le_chnl_map_t		ch_map;							/* channel map value. */
} esble_gapc_con_cnl_map_ind_t;

typedef struct _esble_gapc_encrypt_ind_t					/* Encryption information indication message. */
{
	uint8_t			conidx;

	uint8_t			auth;									/* Authentication  level (@see esble_gap_auth_enum). */
} esble_gapc_encrypt_ind_t;

typedef struct _esble_gapc_encrypt_req_ind_t				/* Encryption requested by peer device indication message. */
{
	uint8_t				conidx;

	uint16_t			ediv;								/* Encryption Diversifier. */

	esble_rand_nb_t		rand_nb;							/* Random Number. */
} esble_gapc_encrypt_req_ind_t;

typedef struct _esble_gapc_sec_ind_t						/* Security requested by peer device indication message. */
{
	uint8_t		conidx;

	uint8_t		auth;										/* Authentication level (@see esble_gap_auth_enum). */
} esble_gapc_sec_ind_t;

typedef struct _esble_gapc_key_press_notif_ind_t			/* Indication that a KeyPress has been performed on the peer device. */
{
	uint8_t		conidx;

	uint8_t		notification_type;							/* notification type. */
} esble_gapc_key_press_notif_ind_t;

typedef struct _esble_gapc_sign_cnt_ind_t					/* Indicate the current sign counters to the application. */
{
	uint8_t		conidx;

	uint32_t	local_sign_counter;							/* Local SignCounter value. */

	uint32_t	peer_sign_counter;							/* Peer SignCounter value. */
} esble_gapc_sign_cnt_ind_t;

typedef struct _esble_gapc_bond_ind_t						/* Bonding information indication message. */
{
	uint8_t					conidx;

	uint8_t					info;							/* Bond information type (@see esble_gapc_bond_enum). */

	esble_gapc_bond_data_t	data;							/* Bond procedure information data.*/
} esble_gapc_bond_ind_t;

typedef struct _esble_gapc_bond_req_ind_t					/* Bonding requested by peer device indication message. */
{
	uint8_t						conidx;

	uint8_t						request;					/* Bond request type (@see esble_gapc_bond_enum). */

	esble_gapc_bond_req_data_t	data;						/* Bond procedure requested information data. */
} esble_gapc_bond_req_ind_t;

typedef struct _esble_gapc_peer_version_ind_t				/* Indication of peer version info. */
{
	uint8_t						conidx;

	uint16_t					compid;						/* Manufacturer name. */

	uint16_t					lmp_subvers;				/* LMP subversion. */

	uint8_t						lmp_vers;					/* LMP version. */
} esble_gapc_peer_version_ind_t;

typedef struct _esble_gapc_peer_features_ind_t				/* Indication of peer features info. */
{
	uint8_t				conidx;

	uint8_t				features[ESBLE_GAP_LE_FEATS_LEN];	/* 8-byte array for LE features. */
} esble_gapc_peer_features_ind_t;

typedef struct _esble_gapc_peer_att_info_ind_t				/* Peer device attribute DB info such as Device Name, Appearance or Slave Preferred Parameters. */
{
	uint8_t						conidx;

	uint8_t						req;						/* Requested information. */

	uint16_t					handle;						/* Attribute handle. */

	union
	{
		esble_gapc_dev_name_t	name;						/* Device name. */
		uint16_t				appearance;					/* Appearance Icon. */
		esble_gapc_slv_pref_t	slv_pref_params;			/* Slave preferred parameters. */
		uint8_t					ctl_addr_resol;				/* Central address resolution. */
	} info;
} esble_gapc_peer_att_info_ind_t;

typedef struct _esble_gapc_le_phy_ind_t						/* Indication of peer features info. */
{
	uint8_t				conidx;

	uint8_t				tx_phy;								/* LE PHY for data transmission (@see enum esble_gap_phy_enum). */

	uint8_t				rx_phy;								/* LE PHY for data reception (@see enum esble_gap_phy_enum). */
} esble_gapc_le_phy_ind_t;

typedef struct _esble_gapc_chan_sel_algo_ind_t
{
	uint8_t				conidx;

	uint8_t				chan_sel_algo;						/* Used channel selection algorithm. */
} esble_gapc_chan_sel_algo_ind_t;

typedef struct _esble_gapc_set_dev_info_req_ind_t			/* Peer device request to modify local device info such as name or appearance. */
{
	uint8_t				conidx;

	uint8_t				req;								/* Requested information.ESBLE_GAPC_DEV_NAME: Device Name.ESBLE_GAPC_DEV_APPEARANCE: Device Appearance Icon. */

	union
	{
		esble_gapc_dev_name_t	name;						/* Device name. */
		uint16_t				appearance;					/* Appearance Icon. */
	} info;
} esble_gapc_set_dev_info_req_ind_t;

typedef struct _esble_gapc_le_ping_to_val_ind_t				/* Indication of LE Ping. */
{
	uint8_t				conidx;

	uint16_t			timeout;							/* Authenticated payload timeout. */
} esble_gapc_le_ping_to_val_ind_t;

typedef struct _esble_gapc_sign_ind_t
{
	uint8_t				conidx;

	uint16_t			byte_len;							/* Data PDU length (Bytes). */

	uint8_t				*signed_msg;						/* Data PDU + SignCounter + MAC. */
} esble_gapc_sign_ind_t;

typedef struct _esble_gapc_le_pkt_size_ind_t				/* LE Set Data Length Indication. */
{
	uint8_t				conidx;

	uint16_t			max_tx_octets;						/* The maximum number of payload octets in TX. */

	uint16_t			max_tx_time;						/* The maximum time that the local Controller will take to TX. */

	uint16_t			max_rx_octets;						/* The maximum number of payload octets in RX. */

	uint16_t			max_rx_time;						/* The maximum time that the local Controller will take to RX. */
} esble_gapc_le_pkt_size_ind_t;

typedef struct _esble_gapc_evt_t
{
	union
	{
		esble_gapc_dev_info_req_ind_t		dev_info_req_ind;
		esble_gapc_conn_req_ind_t			conn_req_ind;
		esble_gapc_disconn_ind_t			disconn_ind;
		esble_gapc_param_upd_ind_t			param_upd_ind;
		esble_gapc_param_upd_req_ind_t		param_upd_req_ind;
		esble_gapc_con_rssi_ind_t			con_rssi_ind;
		esble_gapc_con_cnl_map_ind_t		con_cnl_map_ind;
		esble_gapc_encrypt_ind_t			encrypt_ind;
		esble_gapc_encrypt_req_ind_t		encrypt_req_ind;
		esble_gapc_sec_ind_t				sec_ind;
		esble_gapc_key_press_notif_ind_t	key_press_notif_ind;
		esble_gapc_sign_cnt_ind_t			sign_cnt_ind;
		esble_gapc_bond_ind_t				bond_ind;
		esble_gapc_bond_req_ind_t			bond_req_ind;
		esble_gapc_peer_version_ind_t		peer_version_ind;
		esble_gapc_peer_features_ind_t		peer_features_ind;
		esble_gapc_peer_att_info_ind_t		peer_att_info_ind;
		esble_gapc_le_phy_ind_t				le_phy_ind;
		esble_gapc_chan_sel_algo_ind_t		chan_sel_algo_ind;
		esble_gapc_set_dev_info_req_ind_t	set_dev_info_req_ind;
		esble_gapc_le_ping_to_val_ind_t		le_ping_to_val_ind;
		esble_gapc_sign_ind_t				sign_ind;
		esble_gapc_le_pkt_size_ind_t		le_pkt_size_ind;
	} param;
} esble_gapc_evt_t;


typedef void (*esble_gapc_cb_t)(esble_gapc_evt_enum id, const esble_gapc_evt_t *evt);

#endif
