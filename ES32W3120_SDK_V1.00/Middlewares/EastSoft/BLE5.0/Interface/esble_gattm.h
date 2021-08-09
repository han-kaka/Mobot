#ifndef _ESBLE_GATTM_H_
#define _ESBLE_GATTM_H_

#include "esble.h"
#include "esble_att.h"


/*****************************************************************************************************/
/**												下行命令											**/
/*****************************************************************************************************/

typedef enum _esble_gattm_cmd_enum
{
	ESBLE_GATTM_ADD_SVC_REQ	= ESBLE_GATTM_BASE,

	ESBLE_GATTM_SVC_GET_PERMISSION_REQ,
	ESBLE_GATTM_SVC_SET_PERMISSION_REQ,

	ESBLE_GATTM_ATT_GET_PERMISSION_REQ,
	ESBLE_GATTM_ATT_SET_PERMISSION_REQ,

	ESBLE_GATTM_ATT_GET_VALUE_REQ,
	ESBLE_GATTM_ATT_SET_VALUE_REQ,

	ESBLE_GATTM_DESTROY_DB_REQ,
	ESBLE_GATTM_SVC_GET_LIST_REQ,
	ESBLE_GATTM_ATT_GET_INFO_REQ,
} esble_gattm_cmd_enum;


typedef struct _esble_gattm_att_desc_t
{
	uint16_t	suuid;										/* Attribute UUID (LSB First). */
	
	uint8_t		luuid[ESBLE_ATT_UUID_128_LEN];

	uint16_t	perm;										/* Attribute Permission (@see esble_attm_perm_mask). */

	/*
	* Attribute Extended permissions
	*
	* Extended Value permission bit field
	*
	*   15   14   13   12   11   10    9    8    7    6    5    4    3    2    1    0
	* +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
	* | RI |UUID_LEN |EKS |                       Reserved                            |
	* +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
	*
	* Bit [0-11] : Reserved
	* Bit [12]   : Encryption key Size must be 16 bytes
	* Bit [13-14]: UUID Length             (0 = 16 bits, 1 = 32 bits, 2 = 128 bits, 3 = RFU)
	* Bit [15]   : Trigger Read Indication (0 = Value present in Database, 1 = Value not present in Database)
	*/
	uint16_t	ext_perm;

	/*
	* Maximum length of the attribute
	*
	* Note:
	* For Included Services and Characteristic Declarations, this field contains targeted
	* handle.
	*
	* For Characteristic Extended Properties, this field contains 2 byte value
	*
	* Not used Client Characteristic Configuration and Server Characteristic Configuration,
	* this field is not used.
	*/
	uint16_t	max_len;
} esble_gattm_att_desc_t;

typedef struct _esble_gattm_add_svc_req_t
{
	uint8_t		idx;

	/*
	*    7    6    5    4    3    2    1    0
	* +----+----+----+----+----+----+----+----+
	* |SEC |UUID_LEN |DIS |  AUTH   |EKS | MI |
	* +----+----+----+----+----+----+----+----+
	*
	* Bit [0]  : Task that manage service is multi-instantiated (Connection index is conveyed)
	* Bit [1]  : Encryption key Size must be 16 bytes
	* Bit [2-3]: Service Permission      (0 = NO_AUTH, 1 = UNAUTH, 2 = AUTH, 3 = Secure Connect)
	* Bit [4]  : Disable the service
	* Bit [5-6]: UUID Length             (0 = 16 bits, 1 = 32 bits, 2 = 128 bits, 3 = RFU)
	* Bit [7]  : Secondary Service       (0 = Primary Service, 1 = Secondary Service)
	*/
	uint8_t		perm;

	uint8_t		nb_att;										/* Number of attributes. */

	uint16_t	suuid;										/* Service  UUID. */
	
	uint8_t		luuid[ESBLE_ATT_UUID_128_LEN];

	esble_gattm_att_desc_t *atts;							/* List of attribute description present in service. */
} esble_gattm_add_svc_req_t;

typedef struct _esble_gattm_svc_get_permission_req_t
{
	uint16_t	start_hdl;									/* Service start attribute handle. */
} esble_gattm_svc_get_permission_req_t;

typedef struct _esble_gattm_svc_set_permission_req_t
{
	uint16_t	start_hdl;									/* Service start attribute handle. */

	uint8_t		perm;										/* service permission. */
} esble_gattm_svc_set_permission_req_t;

typedef struct _esble_gattm_att_get_permission_req_t
{
	uint16_t	handle;										/* Handle of the attribute. */
} esble_gattm_att_get_permission_req_t;


typedef struct _esble_gattm_att_set_permission_req_t
{
	uint16_t	handle;										/* Handle of the attribute. */

	uint16_t	perm;										/* Attribute permission. */

	uint16_t	ext_perm;									/* Extended Attribute permission. */
} esble_gattm_att_set_permission_req_t;

typedef struct _esble_gattm_att_get_value_req_t
{ 
	uint16_t	handle;										/* Handle of the attribute. */
} esble_gattm_att_get_value_req_t;

typedef struct _esble_gattm_att_set_value_req_t
{
	uint16_t	handle;										/* Handle of the attribute. */

	uint16_t	length;										/* Attribute value length. */

	uint8_t		*value;										/* Attribute value. */
} esble_gattm_att_set_value_req_t;

typedef struct _esble_gattm_destroy_db_req_t
{
	uint16_t	gap_hdl;									/* New Gap Start Handle. */

	uint16_t	gatt_hdl;									/* New Gatt Start Handle. */
} esble_gattm_destroy_db_req_t;

typedef struct _esble_gattm_att_get_info_req_t
{
	uint16_t	handle;										/* Attribute Handle. */
} esble_gattm_att_get_info_req_t;


SVCALL(ESBLE_GATTM_ADD_SVC_REQ, uint32_t, esble_gattm_add_svc_req(esble_gattm_add_svc_req_t *req));

SVCALL(ESBLE_GATTM_SVC_GET_PERMISSION_REQ, uint32_t, esble_gattm_svc_get_permission_req(esble_gattm_svc_get_permission_req_t *req));

SVCALL(ESBLE_GATTM_SVC_SET_PERMISSION_REQ, uint32_t, esble_gattm_svc_set_permission_req(esble_gattm_svc_set_permission_req_t *req));

SVCALL(ESBLE_GATTM_ATT_GET_PERMISSION_REQ, uint32_t, esble_gattm_att_get_permission_req(esble_gattm_att_get_permission_req_t *req));

SVCALL(ESBLE_GATTM_ATT_SET_PERMISSION_REQ, uint32_t, esble_gattm_att_set_permission_req(esble_gattm_att_set_permission_req_t *req));

SVCALL(ESBLE_GATTM_ATT_GET_VALUE_REQ, uint32_t, esble_gattm_att_get_value_req(esble_gattm_att_get_value_req_t *req));

SVCALL(ESBLE_GATTM_ATT_SET_VALUE_REQ, uint32_t, esble_gattm_att_set_value_req(esble_gattm_att_set_value_req_t *req));

SVCALL(ESBLE_GATTM_DESTROY_DB_REQ, uint32_t, esble_gattm_destroy_db_req(esble_gattm_destroy_db_req_t *req));

SVCALL(ESBLE_GATTM_SVC_GET_LIST_REQ, uint32_t, esble_gattm_svc_get_list_req(void *req));

SVCALL(ESBLE_GATTM_ATT_GET_INFO_REQ, uint32_t, esble_gattm_att_get_info_req(esble_gattm_att_get_info_req_t *req));



/*****************************************************************************************************/
/**												上行事件											**/
/*****************************************************************************************************/

typedef enum _esble_gattm_evt_enum
{
	ESBLE_GATTM_ADD_SVC_RSP	= ESBLE_GATTM_BASE,
	ESBLE_GATTM_SVC_GET_PERMISSION_RSP,
	ESBLE_GATTM_SVC_SET_PERMISSION_RSP,

	ESBLE_GATTM_ATT_GET_PERMISSION_RSP,
	ESBLE_GATTM_ATT_SET_PERMISSION_RSP,

	ESBLE_GATTM_ATT_GET_VALUE_RSP,
	ESBLE_GATTM_ATT_SET_VALUE_RSP,

	ESBLE_GATTM_DESTROY_DB_RSP,
	ESBLE_GATTM_SVC_GET_LIST_RSP,
	ESBLE_GATTM_ATT_GET_INFO_RSP,
} esble_gattm_evt_enum;

typedef struct _esble_gattm_add_svc_rsp_t
{
	uint16_t	start_hdl;									/* Start handle of allocated service in attribute database. */


    uint8_t uuid[ESBLE_ATT_UUID_128_LEN];							/* Service  UUID */

	uint8_t uuid_len;										/* UUID length*/

	uint8_t		status;										/* Return status of service allocation in attribute database. */
} esble_gattm_add_svc_rsp_t;

typedef struct _esble_gattm_svc_get_permission_rsp_t
{
	uint16_t	start_hdl;									/* Service start attribute handle. */

	uint8_t		perm;										/* service permission. */

	uint8_t		status;										/* Return status. */
} esble_gattm_svc_get_permission_rsp_t;

typedef struct _esble_gattm_svc_set_permission_rsp_t
{
	uint16_t	start_hdl;									/* Service start attribute handle. */

	uint8_t		status;										/* Return status. */
} esble_gattm_svc_set_permission_rsp_t;

typedef struct _esble_gattm_att_get_permission_rsp_t
{
	uint16_t	handle;										/* Handle of the attribute. */

	uint16_t	perm;										/* Attribute permission. */

	uint16_t	ext_perm;									/* Extended Attribute permission. */

	uint8_t		status;										/* Return status. */
}esble_gattm_att_get_permission_rsp_t;

typedef struct _esble_gattm_att_set_permission_rsp_t
{
	uint16_t	handle;										/* Handle of the attribute. */

	uint8_t	status;											/* Return status. */
} esble_gattm_att_set_permission_rsp_t;

typedef struct _esble_gattm_att_get_value_rsp_t
{
	uint16_t	handle;										/* Handle of the attribute. */

	uint16_t	length;										/* Attribute value length. */

	uint8_t		status;										/* Return status. */

	uint8_t		*value;										/* Attribute value. */
} esble_gattm_att_get_value_rsp_t;

typedef struct _esble_gattm_att_set_value_rsp_t
{
	uint16_t	handle;										/* Handle of the attribute. */

	uint8_t		status;										/* Return status. */
} esble_gattm_att_set_value_rsp_t;

typedef struct _esble_gattm_destroy_db_rsp_t
{
	uint8_t		status;										/* Return status. */
} esble_gattm_destroy_db_rsp_t;

typedef struct _esble_gattm_svc_info_t
{
	uint16_t	start_hdl;									/* Service start handle. */

	uint16_t	end_hdl;									/* Service end handle. */

	uint16_t	task_id;									/* Service task_id. */

	uint8_t		perm;										/* Service permission. */
} esble_gattm_svc_info_t;

typedef struct _esble_gattm_svc_get_list_rsp_t
{
    uint8_t status;											/* Return status. */

    uint8_t nb_svc;											/* Number of services. */

    esble_gattm_svc_info_t	*svc;							/* Array of information about services. */
} esble_gattm_svc_get_list_rsp_t;

typedef struct _esble_gattm_att_get_info_rsp
{
	uint8_t		status;										/* Return status. */

	uint8_t		uuid_len;									/* UUID Length. */

	uint16_t	handle;										/* Attribute Handle. */

	uint16_t	perm;										/* Attribute Permissions. */

	uint16_t	ext_perm;									/* Extended Attribute permission. */

	uint8_t		uuid[ESBLE_ATT_UUID_128_LEN]; 				/* UUID value. */
} esble_gattm_att_get_info_rsp_t;


typedef struct _esble_gattm_evt_t
{
	union
	{
		esble_gattm_add_svc_rsp_t				add_svc_rsp;
		esble_gattm_svc_get_permission_rsp_t	svc_get_permission_rsp;
		esble_gattm_svc_set_permission_rsp_t	svc_set_permission_rsp;
		esble_gattm_att_get_permission_rsp_t	att_get_permission_rsp;
		esble_gattm_att_set_permission_rsp_t	att_set_permission_rsp;
		esble_gattm_att_get_value_rsp_t			att_get_value_rsp;
		esble_gattm_att_set_value_rsp_t			att_set_value_rsp;
		esble_gattm_destroy_db_rsp_t			destroy_db_rsp;
		esble_gattm_svc_get_list_rsp_t			svc_get_list_rsp;
		esble_gattm_att_get_info_rsp_t			att_get_info_rsp;
	} param;
} esble_gattm_evt_t;


typedef void (*esble_gattm_cb_t)(esble_gattm_evt_enum id, const esble_gattm_evt_t *evt);

#endif

