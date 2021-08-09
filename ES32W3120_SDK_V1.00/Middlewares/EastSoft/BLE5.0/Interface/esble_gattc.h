#ifndef _ESBLE_GATTC_H_
#define _ESBLE_GATTC_H_

#include "esble.h"
#include <stdbool.h>
#include "esble_att.h"

/*****************************************************************************************************/
/**												下行命令											**/
/*****************************************************************************************************/

typedef enum _esble_gattc_cmd_enum
{
	ESBLE_GATTC_WRITE_CFM			= ESBLE_GATTC_BASE,
	ESBLE_GATTC_READ_CFM,
	ESBLE_GATTC_ATT_INFO_CFM,
	ESBLE_GATTC_EVENT_CFM,

	ESBLE_GATTC_MTU_EXCH_CMD,

	ESBLE_GATTC_DISC_ALL_SVC_CMD,
	ESBLE_GATTC_DISC_BY_UUID_SVC_CMD,
	ESBLE_GATTC_DISC_INCLUDED_SVC_CMD,
	ESBLE_GATTC_DISC_ALL_CHAR_CMD,
	ESBLE_GATTC_DISC_BY_UUID_CHAR_CMD,
	ESBLE_GATTC_DISC_DESC_CHAR_CMD,

	ESBLE_GATTC_READ_CMD,
	ESBLE_GATTC_READ_LONG_CMD,
	ESBLE_GATTC_READ_BY_UUID_CMD,
	ESBLE_GATTC_READ_MULTIPLE_CMD,

	ESBLE_GATTC_WRITE_CMD,
	ESBLE_GATTC_WRITE_NO_RESPONSE_CMD,
	ESBLE_GATTC_WRITE_SIGNED_CMD,
	ESBLE_GATTC_EXEC_WRITE_CMD,

	ESBLE_GATTC_REGISTER_CMD,
	ESBLE_GATTC_UNREGISTER_CMD,

	ESBLE_GATTC_SEND_NOTI_CMD,
	ESBLE_GATTC_SEND_IND_CMD,
	ESBLE_GATTC_SVC_CHANGED_CMD,

	ESBLE_GATTC_SDP_DISC_SVC_CMD,
	ESBLE_GATTC_SDP_DISC_SVC_ALL_CMD,
	ESBLE_GATTC_SDP_DISC_CANCEL_CMD,
} esble_gattc_cmd_enum;


typedef struct _esble_gattc_write_cfm_t
{
	uint8_t		conidx;

	uint16_t	handle;										/* Handle of the attribute written. */

	uint8_t		status;										/* Status of write command execution by upper layers. */
} esble_gattc_write_cfm_t;

typedef struct _esble_gattc_read_cfm_t
{
	uint8_t		conidx;

	uint16_t	handle;										/* Handle of the attribute read. */

	uint16_t	length;										/* Data length read. */

	uint8_t		status;										/* Status of read command execution by upper layers. */

	uint8_t		*value;										/* attribute data value. */
} esble_gattc_read_cfm_t;

typedef struct _esble_gattc_att_info_cfm_t
{
	uint8_t		conidx;

	uint16_t	handle;										/* Handle of the attribute. */

	uint16_t	length;										/* Current length of the attribute. */

	uint8_t		status;										/* use to know if it's possible to modify the attribute can contains authorization or application error code.. */
} esble_gattc_att_info_cfm_t;

typedef struct _esble_gattc_event_cfm_t
{
	uint8_t		conidx;

	uint16_t	handle;										/* Attribute handle. */
} esble_gattc_event_cfm_t;

typedef struct _esble_gattc_exc_mtu_cmd_t
{
	uint8_t		conidx;

	uint16_t		seq_num;								/* operation sequence number. */
} esble_gattc_exc_mtu_cmd_t;

typedef struct _esble_gattc_disc_cmd_t
{
	uint8_t		conidx;

	uint8_t		uuid_len;									/* UUID length. */

	uint16_t	seq_num;									/* operation sequence number. */

	uint16_t	start_hdl;									/* start handle range. */

	uint16_t	end_hdl;									/* end handle range. */

	uint8_t		*uuid;										/* UUID. */
} esble_gattc_disc_cmd_t;

typedef struct _esble_gattc_read_simple_t
{
	uint16_t	handle;										/* attribute handle. */

	uint16_t	offset;										/* start offset in data payload. */

	uint16_t	length;										/* Length of data to read (0 = read all). */
} esble_gattc_read_simple_t;

typedef struct _esble_gattc_read_by_uuid_t
{
	uint16_t	start_hdl;									/* Start handle. */

	uint16_t	end_hdl;									/* End handle. */

	uint8_t		uuid_len;									/* Size of UUID. */

	uint8_t		*uuid;										/* UUID value. */
} esble_gattc_read_by_uuid_t;

typedef struct _esble_gattc_read_multiple_t
{
	uint16_t	handle;										/* attribute handle. */

	uint16_t	len;										/* Known Handle length (shall be != 0). */
} esble_gattc_read_multiple_t;

typedef union _esble_gattc_read_req_t
{
	esble_gattc_read_simple_t	simple;						/* Simple read (GATTC_READ or GATTC_READ_LONG). */

	esble_gattc_read_by_uuid_t	by_uuid;					/* Read by UUID (GATTC_READ_BY_UUID). */

	esble_gattc_read_multiple_t	multiple[1];				/* Read Multiple short characteristic (GATTC_READ_MULTIPLE). */
} esble_gattc_read_req_t;

typedef struct _esble_gattc_read_cmd_t
{
	uint8_t		conidx;

	uint8_t		nb;											/* number of read (only used for multiple read). */

	uint16_t	seq_num;									/* operation sequence number. */

	esble_gattc_read_req_t	req;							/* request union according to read type. */
} esble_gattc_read_cmd_t;

typedef struct _esble_gattc_write_cmd_t
{
	uint8_t		conidx;

	bool		auto_execute;								/* Perform automatic execution. (if false, an ATT Prepare Write will be used this shall be use for reliable write.) */

	uint16_t	seq_num;									/* operation sequence number. */

	uint16_t	handle;										/* Attribute handle. */

	uint16_t	offset;										/* Write offset. */

	uint16_t	length;										/* Write length. */

	uint16_t	cursor;										/* Internal write cursor shall be initialized to 0. */

	uint8_t		*value;										/* Value to write. */
} esble_gattc_write_cmd_t;

typedef struct _esble_gattc_execute_write_cmd_t
{
	uint8_t		conidx;

	bool		execute;									/* [True = perform/False cancel] pending write operations. */

	uint16_t	seq_num;									/* operation sequence number. */
} esble_gattc_execute_write_cmd_t;

typedef struct _esble_gattc_reg_to_peer_evt_cmd_t
{
	uint8_t		conidx;

	uint16_t	seq_num;									/* operation sequence number. */

	uint16_t	start_hdl;									/* attribute start handle. */

	uint16_t	end_hdl;									/* attribute end handle. */
} esble_gattc_reg_to_peer_evt_cmd_t;

typedef struct _esble_gattc_send_evt_cmd_t
{
	uint8_t		conidx;

	uint16_t	seq_num;									/* operation sequence number. */

	uint16_t	handle;										/* characteristic handle. */

	uint16_t	length;										/* length of packet to send. */

	uint8_t		*value;										/* data value. */
} esble_gattc_send_evt_cmd_t;

typedef struct _esble_gattc_send_svc_changed_cmd_t
{
	uint8_t		conidx;

	uint16_t	seq_num;									/* operation sequence number. */

	uint16_t	svc_shdl;									/* Start of Affected Attribute Handle Range. */

	uint16_t	svc_ehdl;									/* End of Affected Attribute Handle Range. */
} esble_gattc_send_svc_changed_cmd_t;

enum {

    ESBLE_GATTC_SDP_DISC_SVC,								/* Search specific service*/

    ESBLE_GATTC_SDP_DISC_SVC_ALL,							/* Search for all services*/

    ESBLE_GATTC_SDP_DISC_CANCEL,							/* Cancel Service Discovery Procedure*/
};

typedef struct _esble_gattc_sdp_svc_disc_cmd_t
{
	uint8_t		conidx;

	uint8_t		operation;									/* GATT Request Type*/

	uint8_t		uuid_len;									/* Service UUID Length. */

	uint16_t	seq_num;									/* operation sequence number. */

	uint16_t	start_hdl;									/* Search start handle. */

	uint16_t	end_hdl;									/* Search end handle. */

	uint8_t		uuid[ESBLE_ATT_UUID_128_LEN];				/* Service UUID. */
} esble_gattc_sdp_svc_disc_cmd_t;


SVCALL(ESBLE_GATTC_WRITE_CFM, uint32_t, esble_gattc_write_cfm(esble_gattc_write_cfm_t *cfm));

SVCALL(ESBLE_GATTC_READ_CFM, uint32_t, esble_gattc_read_cfm(esble_gattc_read_cfm_t *cfm));

SVCALL(ESBLE_GATTC_ATT_INFO_CFM, uint32_t, esble_gattc_att_info_cfm(esble_gattc_att_info_cfm_t *cmd));

SVCALL(ESBLE_GATTC_EVENT_CFM, uint32_t, esble_gattc_event_cfm(esble_gattc_event_cfm_t *cmd));

SVCALL(ESBLE_GATTC_MTU_EXCH_CMD, uint32_t, esble_gattc_mtu_exch_cmd(esble_gattc_exc_mtu_cmd_t *cmd));

SVCALL(ESBLE_GATTC_DISC_ALL_SVC_CMD, uint32_t, esble_gattc_disc_all_svc_cmd(esble_gattc_disc_cmd_t *cmd));

SVCALL(ESBLE_GATTC_DISC_BY_UUID_SVC_CMD, uint32_t, esble_gattc_disc_by_uuid_svc_cmd(esble_gattc_disc_cmd_t *cmd));

SVCALL(ESBLE_GATTC_DISC_INCLUDED_SVC_CMD, uint32_t, esble_gattc_disc_included_svc_cmd(esble_gattc_disc_cmd_t *cmd));

SVCALL(ESBLE_GATTC_DISC_ALL_CHAR_CMD, uint32_t, esble_gattc_disc_all_char_cmd(esble_gattc_disc_cmd_t *cmd));

SVCALL(ESBLE_GATTC_DISC_BY_UUID_CHAR_CMD, uint32_t, esble_gattc_disc_by_uuid_char_cmd(esble_gattc_disc_cmd_t *cmd));

SVCALL(ESBLE_GATTC_DISC_DESC_CHAR_CMD, uint32_t, esble_gattc_disc_desc_char_cmd(esble_gattc_disc_cmd_t *cmd));

SVCALL(ESBLE_GATTC_READ_CMD, uint32_t, esble_gattc_read(esble_gattc_read_cmd_t *cmd));

SVCALL(ESBLE_GATTC_READ_LONG_CMD, uint32_t, esble_gattc_read_long(esble_gattc_read_cmd_t *cmd));

SVCALL(ESBLE_GATTC_READ_BY_UUID_CMD, uint32_t, esble_gattc_read_by_uuid(esble_gattc_read_cmd_t *cmd));

SVCALL(ESBLE_GATTC_READ_MULTIPLE_CMD, uint32_t, esble_gattc_read_multiple(esble_gattc_read_cmd_t *cmd));

SVCALL(ESBLE_GATTC_WRITE_CMD, uint32_t, esble_gattc_write(esble_gattc_write_cmd_t *cmd));

SVCALL(ESBLE_GATTC_WRITE_NO_RESPONSE_CMD, uint32_t, esble_gattc_write_no_response(esble_gattc_write_cmd_t *cmd));

SVCALL(ESBLE_GATTC_WRITE_SIGNED_CMD, uint32_t, esble_gattc_write_signed(esble_gattc_write_cmd_t *cmd));

SVCALL(ESBLE_GATTC_EXEC_WRITE_CMD, uint32_t, esble_gattc_exec_write(esble_gattc_execute_write_cmd_t *cmd));

SVCALL(ESBLE_GATTC_REGISTER_CMD, uint32_t, esble_gattc_register(esble_gattc_reg_to_peer_evt_cmd_t *cmd));

SVCALL(ESBLE_GATTC_UNREGISTER_CMD, uint32_t, esble_gattc_unregister(esble_gattc_reg_to_peer_evt_cmd_t *cmd));

SVCALL(ESBLE_GATTC_SEND_NOTI_CMD, uint32_t, esble_gattc_send_notf(esble_gattc_send_evt_cmd_t *cmd));

SVCALL(ESBLE_GATTC_SEND_IND_CMD, uint32_t, esble_gattc_send_ind(esble_gattc_send_evt_cmd_t *cmd));

SVCALL(ESBLE_GATTC_SVC_CHANGED_CMD, uint32_t, esble_gattc_svc_changed_cmd(esble_gattc_send_svc_changed_cmd_t *cmd));

SVCALL(ESBLE_GATTC_SDP_DISC_SVC_CMD, uint32_t, esble_gattc_sdp_disc_svc_cmd(esble_gattc_sdp_svc_disc_cmd_t *cmd));

SVCALL(ESBLE_GATTC_SDP_DISC_SVC_ALL_CMD, uint32_t, esble_gattc_sdp_disc_svc_all_cmd(esble_gattc_sdp_svc_disc_cmd_t *cmd));

SVCALL(ESBLE_GATTC_SDP_DISC_CANCEL_CMD, uint32_t, esble_gattc_sdp_disc_cancel_cmd(esble_gattc_sdp_svc_disc_cmd_t *cmd));

/*****************************************************************************************************/
/**												上行事件											**/
/*****************************************************************************************************/

typedef enum _esble_gattc_evt_enum
{
	ESBLE_GATTC_CMP_EVT				= ESBLE_GATTC_BASE,

	ESBLE_GATTC_MTU_CHANGED_IND,

	ESBLE_GATTC_DISC_SVC_IND,
	ESBLE_GATTC_DISC_SVC_INCL_IND,
	ESBLE_GATTC_DISC_CHAR_IND,
	ESBLE_GATTC_DISC_CHAR_DESC_IND,

	ESBLE_GATTC_READ_IND,

	ESBLE_GATTC_EVENT_IND,
	ESBLE_GATTC_EVENT_REQ_IND,

	ESBLE_GATTC_SVC_CHANGED_CFG_IND,

	ESBLE_GATTC_READ_REQ_IND,

	ESBLE_GATTC_WRITE_REQ_IND,

	ESBLE_GATTC_ATT_INFO_REQ_IND,

	ESBLE_GATTC_SDP_SVC_IND,

	ESBLE_GATTC_TRANSACTION_TO_ERROR_IND,

	ESBLE_GATTC_CLIENT_RTX_IND,
	ESBLE_GATTC_SERVER_RTX_IND,
} esble_gattc_evt_enum;


enum esble_gattc_sdp_att_type
{

    ESBLE_GATTC_SDP_NONE,							/* No Attribute Information*/

    ESBLE_GATTC_SDP_INC_SVC,						/* Included Service Information*/

    ESBLE_GATTC_SDP_ATT_CHAR,						/* Characteristic Declaration*/

    ESBLE_GATTC_SDP_ATT_VAL,						/* Attribute Value*/

    ESBLE_GATTC_SDP_ATT_DESC,						/* Attribute Descriptor*/
};

typedef struct _esble_gattc_cmp_evt_t
{
	uint8_t					conidx;

	esble_gattc_cmd_enum	cmd;							/* GATT request type. */

	uint8_t					status;							/* Status of the request. */

	uint16_t				seq_num;						/* operation sequence number - provided when operation is started. */
} esble_gattc_cmp_evt_t;

typedef struct _esble_gattc_mtu_changed_ind_t
{
	uint8_t		conidx;

	uint16_t	mtu;										/* Exchanged MTU value. */

	uint16_t	seq_num;									/* operation sequence number. */
} esble_gattc_mtu_changed_ind_t;

typedef struct _esble_gattc_disc_svc_ind_t
{
	uint8_t		conidx;

	uint16_t	start_hdl;									/* start handle. */

	uint16_t	end_hdl;									/* end handle. */

	uint8_t		uuid_len;									/* UUID length. */

	uint8_t		*uuid;										/* service UUID. */
} esble_gattc_disc_svc_ind_t;

typedef struct _esble_gattc_disc_svc_incl_ind_t
{
	uint8_t		conidx;
	
	uint16_t	attr_hdl;									/* element handle. */
	
	uint16_t	start_hdl;									/* start handle. */
	
	uint16_t	end_hdl;									/* end handle. */
	
	uint8_t		uuid_len;									/* UUID length. */
	
	uint8_t		*uuid;										/* included service UUID. */
} esble_gattc_disc_svc_incl_ind_t;

typedef struct _esble_gattc_disc_char_ind_t
{
	uint8_t		conidx;

	int16_t		attr_hdl;									/* database element handle. */

	uint16_t	pointer_hdl;								/* pointer attribute handle to UUID. */

	uint8_t		prop;										/* properties. */

	uint8_t		uuid_len;									/* UUID length. */

	uint8_t		*uuid;										/* characteristic UUID. */
} esble_gattc_disc_char_ind_t;

typedef struct _esble_gattc_disc_char_desc_ind_t
{
	uint8_t		conidx;

	int16_t		attr_hdl;									/* database element handle. */

	uint8_t		uuid_len;									/* UUID length. */

	uint8_t		*uuid;										/* Descriptor UUID. */
} esble_gattc_disc_char_desc_ind_t;

typedef struct _esble_gattc_read_ind_t
{
	uint8_t		conidx;

	uint16_t	handle;										/* Attribute handle. */

	uint16_t offset;										/* Read offset. */

	uint16_t length;										/* Read length. */

	uint8_t *value;											/* Handle value. */
} esble_gattc_read_ind_t;

typedef struct _esble_gattc_event_ind_t
{
	uint8_t		conidx;

	uint8_t		type;										/* Event Type. */

	uint16_t	length;										/* Data length. */

	uint16_t	handle;										/* Attribute handle. */

	uint8_t		*value;										/* Event Value. */
} esble_gattc_event_ind_t;

typedef struct _esble_gattc_svc_changed_cfg_t
{
	uint8_t		conidx;

	uint16_t ind_cfg;										/* Current value of the Client Characteristic Configuration descriptor for the Service Changed characteristic. */
} esble_gattc_svc_changed_cfg_t;

typedef struct _esble_gattc_read_req_ind_t
{
	uint8_t		conidx;

	uint16_t	handle;										/* Handle of the attribute that has to be read. */
} esble_gattc_read_req_ind_t;

typedef struct _esble_gattc_write_req_ind_t
{
	uint8_t		conidx;

	uint16_t	handle;										/* Handle of the attribute that has to be written. */

	uint16_t	offset;										/* offset at which the data has to be written. */

	uint16_t	length;										/* Data length to be written. */

	uint8_t		*value;										/* Data to be written in attribute database. */
} esble_gattc_write_req_ind_t;

typedef struct _esble_gattc_att_info_req_ind_t
{
	uint8_t		conidx;

	uint16_t	handle;										/* Handle of the attribute for which info are requested. */
} esble_gattc_att_info_req_ind_t;

typedef struct _esble_gattc_sdp_att_char_t
{

	uint8_t		att_type;									/* Attribute Type. */

	uint8_t		prop;										/* Value property. */

	uint16_t	handle;										/* Value Handle. */
} esble_gattc_sdp_att_char_t;

typedef struct _esble_gattc_sdp_include_svc_t
{
	uint8_t		att_type;									/* Attribute Type. GATTC_SDP_INC_SVC: Included Service Information. */

	uint8_t		uuid_len;									/* Included service UUID Length. */

	uint8_t		uuid[ESBLE_ATT_UUID_128_LEN];				/* Included Service UUID. */

	uint16_t	start_hdl;									/* Included service Start Handle. */

	uint16_t	end_hdl;									/* Included service End Handle. */
} esble_gattc_sdp_include_svc_t;

typedef struct _esble_gattc_sdp_att_t
{
	uint8_t		att_type;									/* Attribute Type. GATTC_SDP_ATT_VAL: Attribute Value. GATTC_SDP_ATT_DESC: Attribute Descriptor */

	uint8_t		uuid_len;									/* Attribute UUID Length. */

	uint8_t		uuid[ESBLE_ATT_UUID_128_LEN];				/* Attribute UUID. */
} esble_gattc_sdp_att_t;

typedef union _esble_gattc_sdp_att_info_t
{
	uint8_t		att_type;									/* Attribute Type. */

	esble_gattc_sdp_att_char_t		att_char;				/* Information about attribute characteristic, @trc_union att_type == GATTC_SDP_ATT_CHAR. */

	esble_gattc_sdp_include_svc_t	inc_svc;				/* Information about included service, @trc_union att_type == GATTC_SDP_INC_SVC. */

	esble_gattc_sdp_att_t			att;					/* Information about attribute, @trc_union att_type == GATTC_SDP_ATT_VAL or att_type == GATTC_SDP_ATT_DESC. */
} esble_gattc_sdp_att_info_t;

typedef struct _esble_gattc_sdp_svc_ind_t					/* Service Discovery indicate that a service has been found. */
{
	uint8_t		conidx;

	uint8_t		uuid_len;

	uint8_t		uuid[ESBLE_ATT_UUID_128_LEN];				/* Service UUID. */

	uint16_t	start_hdl;									/* Service start handle. */

	uint16_t	end_hdl;									/* Service end handle. */

	esble_gattc_sdp_att_info_t	*info;						/* attribute information present in the service (length = end_hdl - start_hdl). */
} esble_gattc_sdp_svc_ind_t;

typedef struct _esble_gattc_client_rtx_ind_t
{
	uint8_t		conidx;

	void const	*param;
} esble_gattc_client_rtx_ind_t;

typedef struct _esble_gattc_server_rtx_ind_t
{
	uint8_t		conidx;

	void const	*param;
} esble_gattc_server_rtx_ind_t;


typedef struct _esble_gattc_evt_t
{
	union
	{
		esble_gattc_cmp_evt_t				cmp_evt;
		esble_gattc_mtu_changed_ind_t		mtu_changed_ind;
		esble_gattc_disc_svc_ind_t			disc_svc_ind;
		esble_gattc_disc_svc_incl_ind_t		disc_svc_incl_ind;
		esble_gattc_disc_char_ind_t			disc_char_ind;
		esble_gattc_disc_char_desc_ind_t	disc_char_desc_ind;
		esble_gattc_read_ind_t				read_ind;
		esble_gattc_event_ind_t				event_ind;
		esble_gattc_svc_changed_cfg_t		svc_changed_cfg;
		esble_gattc_read_req_ind_t			read_req_ind;
		esble_gattc_write_req_ind_t			write_req_ind;
		esble_gattc_att_info_req_ind_t		att_info_req_ind;
		esble_gattc_sdp_svc_ind_t			sdp_svc_ind;
		esble_gattc_client_rtx_ind_t		client_rtx_ind;
		esble_gattc_server_rtx_ind_t		server_rtx_ind;
	} param;
} esble_gattc_evt_t;


typedef void (*esble_gattc_cb_t)(esble_gattc_evt_enum id, const esble_gattc_evt_t *evt);

#endif

