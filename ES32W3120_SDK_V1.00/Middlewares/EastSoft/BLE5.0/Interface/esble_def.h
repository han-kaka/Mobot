#ifndef _ESBLE_DEF_H_
#define _ESBLE_DEF_H_

#include <stdint.h>

#define SVCALL(number, return_type, function) return_type __svc(number) function

#define ESBLE_GAP_BD_ADDR_LEN		(6)						/* BD address length. */

#define ESBLE_GAP_KEY_LEN			(16)					/* Key length. */

#define ESBLE_GAP_RAND_NB_LEN		(0x08)

#define ESBLE_GAP_ADV_DATA_MAX_LEN	(31)

#define ESBLE_GAP_EXT_ADV_DATA_MAX_LEN	(255)

#define ESBLE_GAP_ADV_FALG_LEN		(3)

#define ESBLE_GAP_P256_KEY_LEN		(0x20)

#define ESBLE_GAP_ADDR_PRAND_LEN	(3)

#define ESBLE_GAP_LE_CHNL_MAP_LEN	(0x05)					/* LE Channel map length. */

#define ESBLE_GAP_LE_FEATS_LEN		(0x08)					/* LE Feature Flags Length. */

#define ESBLE_GAP_CNX_INTERVAL_MIN	(6)						/* Connection interval min (N*1.250ms)*/

#define ESBLE_GAP_CNX_INTERVAL_MAX	(3200)					/*(0xC80)Connection interval Max (N*1.250ms)*/

#define ESBLE_GATT_MAX_SERVICE_CNT	(6)

#define ESBLE_GATT_MAX_CHAR_CNT		(6)

#define ESBLE_BIT(pos)				(1UL<<(pos))

#define ESBLE_MASTER_ROLE					0

#define ESBLE_SLAVE_ROLE					1

#define ESBLE_UNKNOWN_ROLE					0xFF

#define ESBLE_INVALID_ACTIDX				0xFF

#define ESBLE_CONNECTION_MAX				(CFG_CON)

typedef enum _esble_gap_ad_type
{
	/// Flag
	ESBLE_GAP_AD_TYPE_FLAGS							= 0x01,//!< GAP_AD_TYPE_FLAGS
	/// Use of more than 16 bits UUID
	ESBLE_GAP_AD_TYPE_MORE_16_BIT_UUID				= 0x02,//!< GAP_AD_TYPE_MORE_16_BIT_UUID
	/// Complete list of 16 bit UUID
	ESBLE_GAP_AD_TYPE_COMPLETE_LIST_16_BIT_UUID		= 0x03,//!< GAP_AD_TYPE_COMPLETE_LIST_16_BIT_UUID
	/// Use of more than 32 bit UUD
	ESBLE_GAP_AD_TYPE_MORE_32_BIT_UUID				= 0x04,//!< GAP_AD_TYPE_MORE_32_BIT_UUID
	/// Complete list of 32 bit UUID
	ESBLE_GAP_AD_TYPE_COMPLETE_LIST_32_BIT_UUID		= 0x05,//!< GAP_AD_TYPE_COMPLETE_LIST_32_BIT_UUID
	/// Use of more than 128 bit UUID
	ESBLE_GAP_AD_TYPE_MORE_128_BIT_UUID				= 0x06,//!< GAP_AD_TYPE_MORE_128_BIT_UUID
	/// Complete list of 128 bit UUID
	ESBLE_GAP_AD_TYPE_COMPLETE_LIST_128_BIT_UUID	= 0x07,//!< GAP_AD_TYPE_COMPLETE_LIST_128_BIT_UUID
	/// Shortened device name
	ESBLE_GAP_AD_TYPE_SHORTENED_NAME				= 0x08,//!< GAP_AD_TYPE_SHORTENED_NAME
	/// Complete device name
	ESBLE_GAP_AD_TYPE_COMPLETE_NAME					= 0x09,//!< GAP_AD_TYPE_COMPLETE_NAME
	/// Transmit power
	ESBLE_GAP_AD_TYPE_TRANSMIT_POWER				= 0x0A,//!< GAP_AD_TYPE_TRANSMIT_POWER
	/// Class of device
	ESBLE_GAP_AD_TYPE_CLASS_OF_DEVICE				= 0x0D,//!< GAP_AD_TYPE_CLASS_OF_DEVICE
	/// Simple Pairing Hash C
	ESBLE_GAP_AD_TYPE_SP_HASH_C						= 0x0E,//!< GAP_AD_TYPE_SP_HASH_C
	/// Simple Pairing Randomizer
	ESBLE_GAP_AD_TYPE_SP_RANDOMIZER_R				= 0x0F,//!< GAP_AD_TYPE_SP_RANDOMIZER_R
	/// Temporary key value
	ESBLE_GAP_AD_TYPE_TK_VALUE						= 0x10,//!< GAP_AD_TYPE_TK_VALUE
	/// Out of Band Flag
	ESBLE_GAP_AD_TYPE_OOB_FLAGS						= 0x11,//!< GAP_AD_TYPE_OOB_FLAGS
	/// Slave connection interval range
	ESBLE_GAP_AD_TYPE_SLAVE_CONN_INT_RANGE			= 0x12,//!< GAP_AD_TYPE_SLAVE_CONN_INT_RANGE
	/// Require 16 bit service UUID
	ESBLE_GAP_AD_TYPE_RQRD_16_BIT_SVC_UUID			= 0x14,//!< GAP_AD_TYPE_RQRD_16_BIT_SVC_UUID
	/// Require 32 bit service UUID
	ESBLE_GAP_AD_TYPE_RQRD_32_BIT_SVC_UUID			= 0x1F,//!< GAP_AD_TYPE_RQRD_32_BIT_SVC_UUID
	/// Require 128 bit service UUID
	ESBLE_GAP_AD_TYPE_RQRD_128_BIT_SVC_UUID			= 0x15,//!< GAP_AD_TYPE_RQRD_128_BIT_SVC_UUID
	/// Service data 16-bit UUID
	ESBLE_GAP_AD_TYPE_SERVICE_16_BIT_DATA			= 0x16,//!< GAP_AD_TYPE_SERVICE_16_BIT_DATA
	/// Service data 32-bit UUID
	ESBLE_GAP_AD_TYPE_SERVICE_32_BIT_DATA			= 0x20,//!< GAP_AD_TYPE_SERVICE_32_BIT_DATA
	/// Service data 128-bit UUID
	ESBLE_GAP_AD_TYPE_SERVICE_128_BIT_DATA			= 0x21,//!< GAP_AD_TYPE_SERVICE_128_BIT_DATA
	/// Public Target Address
	ESBLE_GAP_AD_TYPE_PUB_TGT_ADDR					= 0x17,//!< GAP_AD_TYPE_PUB_TGT_ADDR
	/// Random Target Address
	ESBLE_GAP_AD_TYPE_RAND_TGT_ADDR					= 0x18,//!< GAP_AD_TYPE_RAND_TGT_ADDR
	/// Appearance
	ESBLE_GAP_AD_TYPE_APPEARANCE					= 0x19,//!< GAP_AD_TYPE_APPEARANCE
	/// Advertising Interval
	ESBLE_GAP_AD_TYPE_ADV_INTV						= 0x1A,//!< GAP_AD_TYPE_ADV_INTV
	/// LE Bluetooth Device Address
	ESBLE_GAP_AD_TYPE_LE_BT_ADDR					= 0x1B,//!< GAP_AD_TYPE_LE_BT_ADDR
	/// LE Role
	ESBLE_GAP_AD_TYPE_LE_ROLE						= 0x1C,//!< GAP_AD_TYPE_LE_ROLE
	/// Simple Pairing Hash C-256
	ESBLE_GAP_AD_TYPE_SPAIR_HASH					= 0x1D,//!< GAP_AD_TYPE_SPAIR_HASH
	/// Simple Pairing Randomizer R-256
	ESBLE_GAP_AD_TYPE_SPAIR_RAND					= 0x1E,//!< GAP_AD_TYPE_SPAIR_RAND
	/// 3D Information Data
	ESBLE_GAP_AD_TYPE_3D_INFO						= 0x3D,//!< GAP_AD_TYPE_3D_INFO

	/// Manufacturer specific data
	ESBLE_GAP_AD_TYPE_MANU_SPECIFIC_DATA			= 0xFF,//!< GAP_AD_TYPE_MANU_SPECIFIC_DATA
} esble_gap_ad_type;

typedef enum _esble_gap_pkt_pld_type_enum					/* Packet Payload type for test mode. */
{
	ESBLE_GAP_PKT_PLD_PRBS9,								/* PRBS9 sequence "11111111100000111101..." (in transmission order). */

	ESBLE_GAP_PKT_PLD_REPEATED_11110000,					/* Repeated "11110000" (in transmission order). */

	ESBLE_GAP_PKT_PLD_REPEATED_10101010,					/* Repeated "10101010" (in transmission order). */

	ESBLE_GAP_PKT_PLD_PRBS15,								/* PRBS15 sequence. */

	ESBLE_GAP_PKT_PLD_REPEATED_11111111,					/* Repeated "11111111" (in transmission order) sequence. */

	ESBLE_GAP_PKT_PLD_REPEATED_00000000,					/* Repeated "00000000" (in transmission order) sequence. */

	ESBLE_GAP_PKT_PLD_REPEATED_00001111,					/* Repeated "00001111" (in transmission order) sequence. */

	ESBLE_GAP_PKT_PLD_REPEATED_01010101,					/* Repeated "01010101" (in transmission order) sequence. */
}esble_gap_pkt_pld_type_enum;

typedef enum _esble_gap_test_phy_enum						/* Enumeration of TX/RX PHY used for Test Mode. */
{
	ESBLE_GAP_TEST_PHY_1MBPS		= 1,					/* LE 1M PHY (TX or RX). */

	ESBLE_GAP_TEST_PHY_2MBPS		= 2,					/* LE 2M PHY (TX or RX). */

	ESBLE_GAP_TEST_PHY_CODED		= 3,					/* LE Coded PHY (RX Only). */

	ESBLE_GAP_TEST_PHY_125KBPS		= 3,					/* LE Coded PHY with S=8 data coding (TX Only). */

	ESBLE_GAP_TEST_PHY_500KBPS		= 4,					/* LE Coded PHY with S=2 data coding (TX Only). */
}esble_gap_test_phy_enum;

typedef enum _esble_gap_modulation_idx_enum					/* Modulation index. */
{
	ESBLE_GAP_MODULATION_STANDARD,							/* Assume transmitter will have a standard modulation index. */

	ESBLE_GAP_MODULATION_STABLE,							/* Assume transmitter will have a stable modulation index. */
}esble_gap_modulation_idx_enum;

typedef enum _esble_role_enum
{
	ESBLE_ROLE_NONE			= 0x00,												/* No role set yet. */

	ESBLE_ROLE_OBSERVER		= 0x01,												/* Observer role. */

	ESBLE_ROLE_BROADCASTER	= 0x02,												/* Broadcaster role. */

	ESBLE_ROLE_CENTRAL		= (0x04 | ESBLE_ROLE_OBSERVER),						/* Master/Central role. */

	ESBLE_ROLE_PERIPHERAL	= (0x08 | ESBLE_ROLE_BROADCASTER),					/* Peripheral/Slave role. */

	ESBLE_ROLE_ALL			= (ESBLE_ROLE_CENTRAL | ESBLE_ROLE_PERIPHERAL),		/* Device has all role, both peripheral and central. */
} esble_role_enum;

typedef enum _esble_pairing_mode_enum
{
	ESBLE_PAIRING_DISABLE					= 0,			/* No pairing authorized. */

	ESBLE_PAIRING_LEGACY					= (1 << 0),		/* Legacy pairing Authorized. */

	ESBLE_PAIRING_SEC_CON					= (1 << 1),		/* Secure Connection pairing Authorized. */

	ESBLE_GAPM_PAIRING_FORCE_P256_KEY_GEN	= (1<<7),		/* Force re-generation of P256 private and public keys. */
} esble_pairing_mode_enum;

typedef enum _esble_own_addr_enum							/* Own BD address source of the device. */
{
	ESBLE_STATIC_ADDR,										/* Public or Private Static Address according to device address configuration. */

	ESBLE_GEN_RSLV_ADDR,									/* Generated resolvable private random address. */

	ESBLE_GEN_NON_RSLV_ADDR,								/* Generated non-resolvable private random address. */
} esble_own_addr_enum;

typedef enum _esble_gapm_scan_type							/* Scanning Types*/
{
	ESBLE_GAPM_SCAN_TYPE_GEN_DISC = 0,						/* General discovery*/

	ESBLE_GAPM_SCAN_TYPE_LIM_DISC,							/* Limited discovery*/

	ESBLE_GAPM_SCAN_TYPE_OBSERVER,							/* Observer*/

	ESBLE_GAPM_SCAN_TYPE_SEL_OBSERVER,						/* Selective observer*/

	ESBLE_GAPM_SCAN_TYPE_CONN_DISC,							/* Connectable discovery*/

	ESBLE_GAPM_SCAN_TYPE_SEL_CONN_DISC,						/* Selective connectable discovery*/
}esble_gapm_scan_type;

typedef enum _esble_gapm_scan_prop							/* Scanning properties bit field bit value*/
{
	ESBLE_GAPM_SCAN_PROP_PHY_1M_BIT			= (1 << 0),		/* Scan advertisement on the LE 1M PHY*/

	ESBLE_GAPM_SCAN_PROP_PHY_CODED_BIT		= (1 << 1),		/* Scan advertisement on the LE Coded PHY*/

	ESBLE_GAPM_SCAN_PROP_ACTIVE_1M_BIT		= (1 << 2),		/* Active scan on LE 1M PHY (Scan Request PDUs may be sent)*/

	ESBLE_GAPM_SCAN_PROP_ACTIVE_CODED_BIT	= (1 << 3),		/* Active scan on LE Coded PHY (Scan Request PDUs may be sent)*/

	ESBLE_GAPM_SCAN_PROP_ACCEPT_RPA_BIT		= (1 << 4),		/* Accept directed advertising packets if we use a RPA and target address cannot be solved by the controller*/

	ESBLE_GAPM_SCAN_PROP_FILT_TRUNC_BIT		= (1 << 5),		/* Filter truncated advertising or scan response reports*/
}esble_gapm_scan_prop;

typedef enum _esble_gapm_init_type							/* Initiating Types*/
{
	ESBLE_GAPM_INIT_TYPE_DIRECT_CONN_EST	= 0,			/* Direct connection establishment, establish a connection with an indicated device*/

	ESBLE_GAPM_INIT_TYPE_AUTO_CONN_EST,						/* Automatic connection establishment, establish a connection with all devices whose address is
																present in the white list*/

	ESBLE_GAPM_INIT_TYPE_NAME_DISC,							/* Name discovery, Establish a connection with an indicated device in order to read content of its
																Device Name characteristic. Connection is closed once this operation is stopped.*/
}esble_gapm_init_type;

typedef enum _esble_gapm_init_prop							/* Initiating Properties*/
{
	ESBLE_GAPM_INIT_PROP_1M_BIT			= (1 << 0),			/* Scan connectable advertisements on the LE 1M PHY. Connection parameters for the LE 1M PHY are provided*/

	ESBLE_GAPM_INIT_PROP_2M_BIT			= (1 << 1),			/* Connection parameters for the LE 2M PHY are provided*/

	ESBLE_GAPM_INIT_PROP_CODED_BIT		= (1 << 2),			/* Scan connectable advertisements on the LE Coded PHY. Connection parameters for the LE Coded PHY are provided*/
}esble_gapm_init_prop;

typedef enum _esble_phy_enum								/* Bit field use to select the preferred TX or RX LE PHY. 0 means no preferences. */
{
	ESBLE_PHY_ANY		= 0x00,								/* No preferred PHY. */

	ESBLE_PHY_LE_1MBPS	= (1 << 0),							/* LE 1M PHY preferred for an active link. */

	ESBLE_PHY_LE_2MBPS	= (1 << 1),							/* LE 2M PHY preferred for an active link. */

	ESBLE_PHY_LE_CODED	= (1 << 2),							/* LE Coded PHY preferred for an active link. */
} esble_phy_enum;

typedef enum _esble_gap_auth_mask_enum						/* Authentication mask. */
{
	ESBLE_GAP_AUTH_NONE			= 0,						/* No Flag set. */

	ESBLE_GAP_AUTH_BOND			= (1 << 0),					/* Bond authentication. */

	ESBLE_GAP_AUTH_MITM			= (1 << 2),					/* Man In the middle protection. */

	ESBLE_GAP_AUTH_SEC_CON		= (1 << 3),					/* Secure Connection. */

	ESBLE_GAP_AUTH_KEY_NOTIF	= (1 << 4),					/* Key Notification. */
} esble_gap_auth_mask_enum;

typedef enum _esble_gap_auth_enum
{
	ESBLE_GAP_AUTH_REQ_NO_MITM_NO_BOND	= (ESBLE_GAP_AUTH_NONE),							/* No MITM No Bonding. */

	ESBLE_GAP_AUTH_REQ_NO_MITM_BOND		= (ESBLE_GAP_AUTH_BOND),							/* No MITM Bonding. */

	ESBLE_GAP_AUTH_REQ_MITM_NO_BOND		= (ESBLE_GAP_AUTH_MITM),							/* MITM No Bonding. */

	ESBLE_GAP_AUTH_REQ_MITM_BOND		= (ESBLE_GAP_AUTH_MITM | ESBLE_GAP_AUTH_BOND),		/* MITM and Bonding. */

	ESBLE_GAP_AUTH_REQ_SEC_CON_NO_BOND	= (ESBLE_GAP_AUTH_SEC_CON),							/* SEC_CON and No Bonding. */

	ESBLE_GAP_AUTH_REQ_SEC_CON_BOND		= (ESBLE_GAP_AUTH_SEC_CON | ESBLE_GAP_AUTH_BOND),	/* SEC_CON and Bonding. */

	ESBLE_GAP_AUTH_REQ_LAST,

	ESBLE_GAP_AUTH_REQ_MASK				= 0x1F,				/* Mask of  authentication features without reserved flag. */
} esble_gap_auth_enum;

typedef enum _esble_gap_rnd_addr_type_enum
{
	ESBLE_GAP_STATIC_ADDR		= 0xC0,

	ESBLE_GAP_NON_RSLV_ADDR		= 0x00,

	ESBLE_GAP_RSLV_ADDR			= 0x40,
} esble_gap_rnd_addr_type_enum;

typedef enum _esble_gap_io_cap_enum							/* IO Capability Values. */
{
	ESBLE_GAP_IO_CAP_DISPLAY_ONLY 	= 0x00,					/* Display Only. */

	ESBLE_GAP_IO_CAP_DISPLAY_YES_NO,						/* Display Yes No. */

	ESBLE_GAP_IO_CAP_KB_ONLY,								/* Keyboard Only. */

	ESBLE_GAP_IO_CAP_NO_INPUT_NO_OUTPUT,					/* No Input No Output. */

	ESBLE_GAP_IO_CAP_KB_DISPLAY,							/* Keyboard Display. */

	ESBLE_GAP_IO_CAP_LAST
} esble_gap_io_cap_enum;

typedef enum _esble_gap_tk_type_enum						/* TK Type. */
{
	ESBLE_GAP_TK_OOB = 0x00,								/* TK get from out of band method. */

	ESBLE_GAP_TK_DISPLAY,									/* TK generated and shall be displayed by local device. */

	ESBLE_GAP_TK_KEY_ENTRY									/* TK shall be entered by user using device keyboard. */
} esble_gap_tk_type_enum;

typedef enum _esble_gap_oob_enum							/* OOB Data Present Flag Values. */
{
	ESBLE_GAP_OOB_AUTH_DATA_NOT_PRESENT = 0x00,				/* OOB Data not present. */

	ESBLE_GAP_OOB_AUTH_DATA_PRESENT,						/* OOB data present. */

	ESBLE_GAP_OOB_AUTH_DATA_LAST
} esble_gap_oob_enum;

typedef enum _esble_gap_kdist_enum							/* Key Distribution Flags. */
{
	ESBLE_GAP_KDIST_NONE		= 0x00,						/* No Keys to distribute. */

	ESBLE_GAP_KDIST_ENCKEY		= (1 << 0),					/* Encryption key in distribution. */

	ESBLE_GAP_KDIST_IDKEY		= (1 << 1),					/* IRK (ID key)in distribution. */

	ESBLE_GAP_KDIST_SIGNKEY		= (1 << 2),					/* CSRK(Signature key) in distribution. */

	ESBLE_GAP_KDIST_LINKKEY		= (1 << 3),					/* LTK in distribution. */

	ESBLE_GAP_KDIST_LAST		= (1 << 4)
} esble_gap_kdist_enum;

typedef enum _esble_gap_sec_req_enum						/* Security Defines. */
{
	ESBLE_GAP_NO_SEC = 0x00,								/* No security (no authentication and encryption). */

	ESBLE_GAP_SEC1_NOAUTH_PAIR_ENC,							/* Unauthenticated pairing with encryption. */

	ESBLE_GAP_SEC1_AUTH_PAIR_ENC,							/* Authenticated pairing with encryption. */

	ESBLE_GAP_SEC2_NOAUTH_DATA_SGN,							/* Unauthenticated pairing with data signing. */

	ESBLE_GAP_SEC2_AUTH_DATA_SGN,							/* Authentication pairing with data signing. */

	ESBLE_GAP_SEC1_SEC_CON_PAIR_ENC,						/* Secure Connection pairing with encryption. */
} esble_gap_sec_req_enum;

typedef enum _esble_gap_phy_enum							/* Bit field use to select the preferred TX or RX LE PHY. 0 means no preferences. */
{
	ESBLE_GAP_PHY_ANY				= 0x00,					/* No preferred PHY. */

	ESBLE_GAP_PHY_LE_1MBPS			= (1 << 0),				/* LE 1M PHY preferred for an active link. */

	ESBLE_GAP_PHY_LE_2MBPS			= (1 << 1),				/* LE 2M PHY preferred for an active link. */

	ESBLE_GAP_PHY_LE_CODED			= (1 << 2),				/* LE Coded PHY preferred for an active link. */
} esble_gap_phy_enum;

enum _ESBLE_KE_MEM_HEAP										/* Kernel memory heaps types. */
{
	ESBLE_KE_MEM_ENV,										/* Kernel memory heaps types. */

	#if (BLE_HOST_PRESENT)

	ESBLE_KE_MEM_ATT_DB,									/* Memory allocated for Attribute database. */

	#endif // (BLE_HOST_PRESENT)

	ESBLE_KE_MEM_KE_MSG,									/* Memory allocated for kernel messages. */

	ESBLE_KE_MEM_NON_RETENTION,								/* Non Retention memory block. */

	ESBLE_KE_MEM_BLOCK_MAX,
};


typedef struct _esble_bd_addr_t
{
	uint8_t  addr[ESBLE_GAP_BD_ADDR_LEN];					/* 6-byte array address valu. */
} esble_bd_addr_t;

typedef struct _esble_gap_sec_key_t							/* Generic Security key structure. */
{
	uint8_t key[ESBLE_GAP_KEY_LEN];							/* Key value MSB -> LSB. */
} esble_gap_sec_key_t;

typedef struct _esble_le_chnl_map_t
{
	uint8_t		map[ESBLE_GAP_LE_CHNL_MAP_LEN];				/* 6-byte array address valu. */
} esble_le_chnl_map_t;

typedef struct _esble_rand_nb_t
{
	uint8_t		nb[ESBLE_GAP_RAND_NB_LEN];					/* 8-byte array for random number. */
} esble_rand_nb_t;

typedef struct _esble_gap_bdaddr_t							/* Address information about a device address. */
{
	esble_bd_addr_t		addr;								/* BD Address of device. */

	uint8_t				addr_type;							/* Address type of the device 0=public/1=private random. */
} esble_gap_bdaddr_t;

#endif
