#ifndef _LIB_ADVDATA_H_
#define _LIB_ADVDATA_H_

#include <stdint.h>
#include <stdbool.h>

#define LIB_ADVDATA_AD_LENGTH_FIELD_SIZE               1UL                                         /* Advertising Data and Scan Response format contains 1 octet for the length. */
#define LIB_ADVDATA_AD_TYPE_FIELD_SIZE                 1UL                                         /* Advertising Data and Scan Response format contains 1 octet for the AD type. */
#define LIB_ADVDATA_AD_DATA_OFFSET                     (LIB_ADVDATA_AD_LENGTH_FIELD_SIZE + LIB_ADVDATA_AD_TYPE_FIELD_SIZE) /* Offset for the AD data field of the Advertising Data and Scan Response format. */

#define LIB_ADVDATA_AD_TYPE_BLE_DEVICE_ADDR_TYPE_SIZE  1UL                                 /* Data size (in octets) of the Address type of the LE Bluetooth Device Address AD type. */
#define LIB_ADVDATA_AD_TYPE_BLE_DEVICE_ADDR_DATA_SIZE  (ESBLE_GAP_BD_ADDR_LEN + \
                                            LIB_ADVDATA_AD_TYPE_BLE_DEVICE_ADDR_TYPE_SIZE) /* Data size (in octets) of the LE Bluetooth Device Address AD type. */
#define LIB_ADVDATA_AD_TYPE_BLE_DEVICE_ADDR_SIZE       (LIB_ADVDATA_AD_DATA_OFFSET + \
                                            LIB_ADVDATA_AD_TYPE_BLE_DEVICE_ADDR_DATA_SIZE) /* Size (in octets) of the LE Bluetooth Device Address AD type. */
#define LIB_ADVDATA_AD_TYPE_APPEARANCE_DATA_SIZE       2UL                                 /* Data size (in octets) of the Appearance AD type. */
#define LIB_ADVDATA_AD_TYPE_APPEARANCE_SIZE            (LIB_ADVDATA_AD_DATA_OFFSET + \
                                            LIB_ADVDATA_AD_TYPE_APPEARANCE_DATA_SIZE)      /* Size (in octets) of the Appearance AD type. */
#define LIB_ADVDATA_AD_TYPE_TX_POWER_LEVEL_DATA_SIZE   1UL                                 /* Data size (in octets) of the TX Power Level AD type. */
#define LIB_ADVDATA_AD_TYPE_TX_POWER_LEVEL_SIZE        (LIB_ADVDATA_AD_DATA_OFFSET + \
                                            LIB_ADVDATA_AD_TYPE_TX_POWER_LEVEL_DATA_SIZE)  /* Size (in octets) of the TX Power Level AD type. */
#define LIB_ADVDATA_AD_TYPE_CONN_INT_DATA_SIZE         4UL                                 /* Data size (in octets) of the Slave Connection Interval Range AD type. */
#define LIB_ADVDATA_AD_TYPE_CONN_INT_SIZE              (LIB_ADVDATA_AD_DATA_OFFSET + \
                                            LIB_ADVDATA_AD_TYPE_CONN_INT_DATA_SIZE)        /* Data size (in octets) of the Slave Connection Interval Range AD type. */
#define LIB_ADVDATA_AD_TYPE_MANUF_SPEC_DATA_ID_SIZE    2UL                                 /* Size (in octets) of the Company Identifier Code, which is a part of the Manufacturer Specific Data AD type. */
#define LIB_ADVDATA_AD_TYPE_SERV_DATA_16BIT_UUID_SIZE  2UL                                 /* Size (in octets) of the 16-bit UUID, which is a part of the Service Data AD type. */

#define LIB_ADVDATA__MATCH_FULL_NAME       0xff

typedef enum _lib_advdata_name_type_t
{
	LIB_ADVDATA_NO_NAME			= 0x00,
	LIB_ADVDATA_SHORT_NAME,
	LIB_ADVDATA_FULL_NAME,
} lib_advdata_name_type_t;

typedef enum _lib_advdata_uuid_type_t
{
	LIB_ADVDATA_UUID_16			= 0,
	LIB_ADVDATA_UUID_32,
	LIB_ADVDATA_UUID_128,
} lib_advdata_uuid_type_t;

typedef struct _lib_advdata_uuid_list_t
{
	uint8_t					number;
	uint8_t					*list;
} lib_advdata_uuid_list_t;

typedef struct _lib_advdata_conn_intl_t
{
	uint16_t				min_conn_intl;
	uint16_t				max_conn_intl;
} lib_advdata_conn_intl_t;

typedef struct _lib_advdata_svc_data_t
{
	lib_advdata_uuid_type_t	uuid_type;
	uint8_t					*uuid;

	uint8_t					data_len;
	uint8_t					*data;
} lib_advdata_svc_data_t;

typedef struct _lib_advdata_manu_data_t
{
	uint16_t				company_id;
	uint8_t					data_len;
	uint8_t					*data;
} lib_advdata_manu_data_t;


typedef struct _lib_advdata_t
{
	lib_advdata_name_type_t		name_type;
	uint8_t						short_name_len;
	bool						include_appearance;
	bool						include_addr;
	int8_t						*tx_power;

	lib_advdata_uuid_list_t		*incomplete_16bit_uuid_list;
	lib_advdata_uuid_list_t		*complete_16bit_uuid_list;
	lib_advdata_uuid_list_t		*solicitation_16bit_uuid_list;
	lib_advdata_uuid_list_t		*incomplete_32bit_uuid_list;
	lib_advdata_uuid_list_t		*complete_32bit_uuid_list;
	lib_advdata_uuid_list_t		*solicitation_32bit_uuid_list;
	lib_advdata_uuid_list_t		*incomplete_128bit_uuid_list;
	lib_advdata_uuid_list_t		*complete_128bit_uuid_list;
	lib_advdata_uuid_list_t		*solicitation_128bit_uuid_list;

	lib_advdata_conn_intl_t		*slave_conn_intl;

	uint8_t						svc_data_number;
	lib_advdata_svc_data_t		*svc_data_list;

	lib_advdata_manu_data_t		*man_data;
} lib_advdata_t;

typedef struct _lib_advdata_tlv_t
{
	uint8_t		len;
	uint8_t		type;
	uint8_t		*value;
} lib_advdata_tlv_t;

esble_err lib_advdata_encode(lib_advdata_t const * const p_advdata,
                              uint8_t             * const p_encoded_data,
                              uint16_t            * const p_len);

uint16_t lib_advdata_search(uint8_t const * p_encoded_data, uint16_t data_len, uint16_t *p_offset, uint8_t ad_type);

uint8_t * lib_advdata_decode(uint8_t * p_encoded_data, uint16_t data_len, uint8_t ad_type);

#endif
