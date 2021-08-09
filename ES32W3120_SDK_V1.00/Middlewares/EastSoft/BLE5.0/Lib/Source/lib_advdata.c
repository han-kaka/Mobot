/*************************************************************************************************/
/*
Copyright	:	QingDao Eastsoft Communication Technology Co.,Ltd.
File Name	:
Description	:
Author		:	eastsoft
Version		:
Date		:
History		:	None
Note		:	None
*/
/*************************************************************************************************/

#include <string.h>

#include "sdk_conf.h"
#include "esble_def.h"
#include "esble_error.h"
#include "esble_att.h"
#include "lib_advdata.h"

// Types of LE Bluetooth Device Address AD type
#define AD_TYPE_BLE_DEVICE_ADDR_TYPE_PUBLIC 0UL
#define AD_TYPE_BLE_DEVICE_ADDR_TYPE_RANDOM 1UL


/**@brief Function for encoding a uint16 value.
 *
 * @param[in]   value            Value to be encoded.
 * @param[out]  p_encoded_data   Buffer where the encoded data is to be written.
 *
 * @return      Number of bytes written.
 */
static uint8_t uint16_encode(uint16_t value, uint8_t * p_encoded_data)
{
    p_encoded_data[0] = (uint8_t) ((value & 0x00FF) >> 0);
    p_encoded_data[1] = (uint8_t) ((value & 0xFF00) >> 8);
    return sizeof(uint16_t);
}

/*************************************************************************************************/
/*
	Function	: lib_advdata_encode_addr
	Description	:格式化设备地址，设备地址共7个字节，低六个字节为设备地址
				第7个字节的bit[0]=1表示为random addr,bit[1]=0表示为public addr
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
static esble_err lib_advdata_encode_addr(uint8_t *p_encoded_data, uint16_t *p_offset, uint16_t max_size)
{
	esble_err err_code = ESBLE_ERROR_NO_ERROR;
	
	// Check for buffer overflow.
	if (((*p_offset) + LIB_ADVDATA_AD_TYPE_BLE_DEVICE_ADDR_SIZE) > max_size)
	{
		return ESBLE_ERROR_DATA_SIZE;
	}
	
	esble_bd_addr_t		pub_addr = BLE_BD_ADDR;
	esble_bd_addr_t		rnd_addr = BLE_RANDOM_ADDR;
	
	// Encode LE Bluetooth Device Address.
	p_encoded_data[*p_offset]  = (uint8_t)(LIB_ADVDATA_AD_TYPE_FIELD_SIZE +
                                               LIB_ADVDATA_AD_TYPE_BLE_DEVICE_ADDR_DATA_SIZE);
	*p_offset                 += LIB_ADVDATA_AD_LENGTH_FIELD_SIZE;
	p_encoded_data[*p_offset]  = ESBLE_GAP_AD_TYPE_LE_BT_ADDR;
	*p_offset                 += LIB_ADVDATA_AD_TYPE_FIELD_SIZE;
	
	if(BLE_USE_RANDOM_ADDR)
	{
		memcpy(&p_encoded_data[*p_offset],rnd_addr.addr,ESBLE_GAP_BD_ADDR_LEN);
		*p_offset                 += ESBLE_GAP_BD_ADDR_LEN;
		p_encoded_data[*p_offset] = AD_TYPE_BLE_DEVICE_ADDR_TYPE_RANDOM;
	}
	else
	{
		memcpy(&p_encoded_data[*p_offset],pub_addr.addr,ESBLE_GAP_BD_ADDR_LEN);
		*p_offset                 += ESBLE_GAP_BD_ADDR_LEN;
		p_encoded_data[*p_offset] = AD_TYPE_BLE_DEVICE_ADDR_TYPE_PUBLIC;
	}
	
	 *p_offset += LIB_ADVDATA_AD_TYPE_BLE_DEVICE_ADDR_TYPE_SIZE;
	
	return err_code;
}

/*************************************************************************************************/
/*
	Function	:lib_advdata_encode_appearance
	Description	:格式化appearance，两个字节
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
static esble_err lib_advdata_encode_appearance(uint8_t *p_encoded_data, uint16_t *p_offset, uint16_t max_size)
{
	esble_err err_code = ESBLE_ERROR_NO_ERROR;
	uint16_t   appearance = BLE_DEV_LOCAL_APPEARANCE;
	
	// Check for buffer overflow.
	if (((*p_offset) + LIB_ADVDATA_AD_TYPE_APPEARANCE_SIZE) > max_size)
	{
		return ESBLE_ERROR_DATA_SIZE;
	}

	// Encode Length, AD Type and Appearance.
	p_encoded_data[*p_offset]  = (uint8_t)(LIB_ADVDATA_AD_TYPE_FIELD_SIZE + LIB_ADVDATA_AD_TYPE_APPEARANCE_DATA_SIZE);
	*p_offset                 += LIB_ADVDATA_AD_LENGTH_FIELD_SIZE;
	p_encoded_data[*p_offset]  = ESBLE_GAP_AD_TYPE_APPEARANCE;
	*p_offset                 += LIB_ADVDATA_AD_TYPE_FIELD_SIZE;
	*p_offset                 += uint16_encode(appearance, &p_encoded_data[*p_offset]);
	
	return err_code;
}

/*************************************************************************************************/
/*
	Function	: lib_advdata_encode_txpower
	Description	: 格式化TX_POWER数据，共1个数据字节
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
static esble_err lib_advdata_encode_txpower(uint8_t tx_power, uint8_t *p_encoded_data, uint16_t *p_offset, uint16_t max_size)
{
		esble_err err_code = ESBLE_ERROR_NO_ERROR;
	
	// Check for buffer overflow.
	if (((*p_offset) + LIB_ADVDATA_AD_TYPE_TX_POWER_LEVEL_SIZE) > max_size)
	{
		return ESBLE_ERROR_DATA_SIZE;
	}

	// Encode TX Power Level.
	p_encoded_data[*p_offset]  = (uint8_t)(LIB_ADVDATA_AD_TYPE_FIELD_SIZE +
                                                  LIB_ADVDATA_AD_TYPE_TX_POWER_LEVEL_DATA_SIZE);
	*p_offset                 += LIB_ADVDATA_AD_LENGTH_FIELD_SIZE;
	p_encoded_data[*p_offset]  = ESBLE_GAP_AD_TYPE_TRANSMIT_POWER;
	*p_offset                 += LIB_ADVDATA_AD_TYPE_FIELD_SIZE;
	p_encoded_data[*p_offset]  = tx_power;
	*p_offset                 += LIB_ADVDATA_AD_TYPE_TX_POWER_LEVEL_DATA_SIZE;
	
	return err_code;
}

/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
static esble_err lib_advdata_encode_uuid_list(lib_advdata_uuid_list_t *p_uuid_list,
											  uint8_t                  adv_type,
											  uint8_t                  uuid_size,
											  uint8_t                  * p_encoded_data,
											  uint16_t                 * p_offset,
											  uint16_t                 max_size)
{
	uint8_t  i;
	uint32_t data_size;
	data_size = p_uuid_list->number * uuid_size;

	// Check parameter consistency.
	if (p_uuid_list->list == NULL)
	{
		return ESBLE_ERROR_INVALID_PARAM;
	}

	// Check for buffer overflow.
	if (((*p_offset) + LIB_ADVDATA_AD_DATA_OFFSET + data_size) > max_size)
	{
		return ESBLE_ERROR_DATA_SIZE;
	}

	// There is only 1 byte intended to encode length which is (data_size + AD_TYPE_FIELD_SIZE)
	if (data_size > (0x00FF - LIB_ADVDATA_AD_TYPE_FIELD_SIZE))
	{
		return ESBLE_ERROR_DATA_SIZE;
	}

	// Encode Length and AD Type.
	p_encoded_data[*p_offset]  = (uint8_t)(LIB_ADVDATA_AD_TYPE_FIELD_SIZE + data_size);
	*p_offset                 += LIB_ADVDATA_AD_LENGTH_FIELD_SIZE;
	p_encoded_data[*p_offset]  = adv_type;
	*p_offset                 += LIB_ADVDATA_AD_TYPE_FIELD_SIZE;

	for (i = 0; i < p_uuid_list->number; i++)
	{
		// Encode service UUID.
		memcpy(&p_encoded_data[*p_offset], p_uuid_list->list, data_size);
		*p_offset += data_size;
	}
	return ESBLE_ERROR_NO_ERROR;
}

/*************************************************************************************************/
/*
	Function	: lib_advdata_conn_int_check
	Description	: 检查参数的有效性
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
static esble_err lib_advdata_conn_int_check(const lib_advdata_conn_intl_t *slave_conn_intl)
{
	
	// check for the range validity of the values
	if ( (slave_conn_intl->max_conn_intl < ESBLE_GAP_CNX_INTERVAL_MIN || slave_conn_intl->max_conn_intl > ESBLE_GAP_CNX_INTERVAL_MAX) ||
		 (slave_conn_intl->min_conn_intl < ESBLE_GAP_CNX_INTERVAL_MIN || slave_conn_intl->min_conn_intl > ESBLE_GAP_CNX_INTERVAL_MAX) ||
		 (slave_conn_intl->max_conn_intl < slave_conn_intl->min_conn_intl) )
	{
		return ESBLE_ERROR_INVALID_PARAM;
	}

	return ESBLE_ERROR_NO_ERROR;
}

/*************************************************************************************************/
/*
	Function	:lib_advdata_encode_slave_conn_intl
	Description	:格式化从机连接参数，共四个字节，连接间隔最小值和连接间隔最大值
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
static esble_err lib_advdata_encode_slave_conn_intl(lib_advdata_conn_intl_t *slave_conn_intl, uint8_t *p_encoded_data, uint16_t *p_offset, uint16_t max_size)
{
	esble_err err_code = ESBLE_ERROR_NO_ERROR;
	
		// Check for buffer overflow.
	if (((*p_offset) + LIB_ADVDATA_AD_TYPE_CONN_INT_SIZE) > max_size)
	{
		return ESBLE_ERROR_DATA_SIZE;
	}

	// Check parameters.
	err_code = lib_advdata_conn_int_check(slave_conn_intl);
		if(err_code != ESBLE_ERROR_NO_ERROR)
		{
			return err_code;
		}
	
	// Encode Length and AD Type.
	p_encoded_data[*p_offset]  = (uint8_t)(LIB_ADVDATA_AD_TYPE_FIELD_SIZE + LIB_ADVDATA_AD_TYPE_CONN_INT_DATA_SIZE);
	*p_offset                 += LIB_ADVDATA_AD_LENGTH_FIELD_SIZE;
	p_encoded_data[*p_offset]  = ESBLE_GAP_AD_TYPE_SLAVE_CONN_INT_RANGE;
	*p_offset                 += LIB_ADVDATA_AD_TYPE_FIELD_SIZE;

	// Encode Minimum and Maximum Connection Intervals.
	*p_offset += uint16_encode(slave_conn_intl->min_conn_intl, &p_encoded_data[*p_offset]);
	*p_offset += uint16_encode(slave_conn_intl->max_conn_intl, &p_encoded_data[*p_offset]);

	return err_code;
}

/*************************************************************************************************/
/*
	Function	:lib_advdata_encode_man_data
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
static esble_err lib_advdata_encode_man_data(lib_advdata_manu_data_t *man_data, uint8_t *p_encoded_data, uint16_t *p_offset, uint16_t max_size)
{
	uint32_t data_size = LIB_ADVDATA_AD_TYPE_MANUF_SPEC_DATA_ID_SIZE + man_data->data_len;

	// Check for buffer overflow.
	if (((*p_offset) + LIB_ADVDATA_AD_DATA_OFFSET + data_size) > max_size)
	{
		return ESBLE_ERROR_DATA_SIZE;
	}

	// There is only 1 byte intended to encode length which is (data_size + LIB_ADVDATA_AD_TYPE_FIELD_SIZE)
	if (data_size > (0x00FF - LIB_ADVDATA_AD_TYPE_FIELD_SIZE))
	{
		return ESBLE_ERROR_DATA_SIZE;
	}

	// Encode Length and AD Type.
	p_encoded_data[*p_offset]  = (uint8_t)(LIB_ADVDATA_AD_TYPE_FIELD_SIZE + data_size);
	*p_offset                 += LIB_ADVDATA_AD_LENGTH_FIELD_SIZE;
	p_encoded_data[*p_offset]  = ESBLE_GAP_AD_TYPE_MANU_SPECIFIC_DATA;
	*p_offset                 += LIB_ADVDATA_AD_TYPE_FIELD_SIZE;

	// Encode Company Identifier.
	*p_offset += uint16_encode(man_data->company_id, &p_encoded_data[*p_offset]);

	// Encode additional manufacturer specific data.
	if (man_data->data_len > 0)
	{
		if (man_data->data == NULL)
		{
			return ESBLE_ERROR_INVALID_PARAM;
        }
		memcpy(&p_encoded_data[*p_offset], man_data->data, man_data->data_len);
		*p_offset += man_data->data_len;
	}

	return ESBLE_ERROR_NO_ERROR;
}

/*************************************************************************************************/
/*
	Function	: lib_advdata_encode_svc_data
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
static esble_err lib_advdata_encode_svc_data(const lib_advdata_t *p_advdata, uint8_t *p_encoded_data, uint16_t *p_offset, uint16_t max_size)
{
	uint8_t i;

	// Check parameter consistency.
	if (p_advdata->svc_data_list == NULL)
	{
		return ESBLE_ERROR_INVALID_PARAM;
	}

	for (i = 0; i < p_advdata->svc_data_number; i++)
	{
		lib_advdata_svc_data_t * p_service_data;
		uint32_t                     data_size;

		p_service_data = &p_advdata->svc_data_list[i];

		switch(p_service_data->uuid_type)
		{
			case LIB_ADVDATA_UUID_16:
			{
				// For now implemented for 16-bit UUIDs
				data_size      = ESBLE_ATT_UUID_16_LEN + p_service_data->data_len;

				// Check for buffer overflow.
				if (((*p_offset) + LIB_ADVDATA_AD_DATA_OFFSET + data_size) > max_size)
				{
					return ESBLE_ERROR_DATA_SIZE;
				}

				// There is only 1 byte intended to encode length which is (data_size + LIB_ADVDATA_AD_TYPE_FIELD_SIZE)
				if (data_size > (0x00FF - LIB_ADVDATA_AD_TYPE_FIELD_SIZE))
				{
					return ESBLE_ERROR_DATA_SIZE;
				}

				// Encode Length and AD Type.
				 p_encoded_data[*p_offset]  = (uint8_t)(LIB_ADVDATA_AD_TYPE_FIELD_SIZE + data_size);
				*p_offset                 += LIB_ADVDATA_AD_LENGTH_FIELD_SIZE;
				p_encoded_data[*p_offset]  = ESBLE_GAP_AD_TYPE_SERVICE_16_BIT_DATA;
				*p_offset                 += LIB_ADVDATA_AD_TYPE_FIELD_SIZE;
				
				// Encode service 16-bit UUID.
				memcpy(&p_encoded_data[*p_offset], p_service_data->uuid, ESBLE_ATT_UUID_16_LEN);
				*p_offset += ESBLE_ATT_UUID_16_LEN;

				// Encode additional service data.
				if (p_service_data->data_len > 0)
				{
					if (p_service_data->data == NULL)
					{
						return ESBLE_ERROR_INVALID_PARAM;
					}
					memcpy(&p_encoded_data[*p_offset], p_service_data->data, p_service_data->data_len);
					*p_offset += p_service_data->data_len;
				}
				break;
			}
			case LIB_ADVDATA_UUID_32:
			{
				// For now implemented for 32-bit UUIDs
				data_size      = ESBLE_ATT_UUID_32_LEN + p_service_data->data_len;

				// Check for buffer overflow.
				if (((*p_offset) + LIB_ADVDATA_AD_DATA_OFFSET + data_size) > max_size)
				{
					return ESBLE_ERROR_DATA_SIZE;
				}

				// There is only 1 byte intended to encode length which is (data_size + LIB_ADVDATA_AD_TYPE_FIELD_SIZE)
				if (data_size > (0x00FF - LIB_ADVDATA_AD_TYPE_FIELD_SIZE))
				{
					return ESBLE_ERROR_DATA_SIZE;
				}

				// Encode Length and AD Type.
				 p_encoded_data[*p_offset]  = (uint8_t)(LIB_ADVDATA_AD_TYPE_FIELD_SIZE + data_size);
				*p_offset                 += LIB_ADVDATA_AD_LENGTH_FIELD_SIZE;
				p_encoded_data[*p_offset]  = ESBLE_GAP_AD_TYPE_SERVICE_32_BIT_DATA;
				*p_offset                 += LIB_ADVDATA_AD_TYPE_FIELD_SIZE;
				
				// Encode service 32-bit UUID.
				memcpy(&p_encoded_data[*p_offset], p_service_data->uuid, ESBLE_ATT_UUID_32_LEN);
				*p_offset += ESBLE_ATT_UUID_32_LEN;

				// Encode additional service data.
				if (p_service_data->data_len > 0)
				{
					if (p_service_data->data == NULL)
					{
						return ESBLE_ERROR_INVALID_PARAM;
					}
					memcpy(&p_encoded_data[*p_offset], p_service_data->data, p_service_data->data_len);
					*p_offset += p_service_data->data_len;
				}
				break;
			}
			case LIB_ADVDATA_UUID_128:
			{
				// For now implemented for 128-bit UUIDs
				data_size      = ESBLE_ATT_UUID_128_LEN + p_service_data->data_len;

				// Check for buffer overflow.
				if (((*p_offset) + LIB_ADVDATA_AD_DATA_OFFSET + data_size) > max_size)
				{
					return ESBLE_ERROR_DATA_SIZE;
				}

				// There is only 1 byte intended to encode length which is (data_size + LIB_ADVDATA_AD_TYPE_FIELD_SIZE)
				if (data_size > (0x00FF - LIB_ADVDATA_AD_TYPE_FIELD_SIZE))
				{
					return ESBLE_ERROR_DATA_SIZE;
				}

				// Encode Length and AD Type.
				 p_encoded_data[*p_offset]  = (uint8_t)(LIB_ADVDATA_AD_TYPE_FIELD_SIZE + data_size);
				*p_offset                 += LIB_ADVDATA_AD_LENGTH_FIELD_SIZE;
				p_encoded_data[*p_offset]  = ESBLE_GAP_AD_TYPE_SERVICE_128_BIT_DATA;
				*p_offset                 += LIB_ADVDATA_AD_TYPE_FIELD_SIZE;
				
				// Encode service 128-bit UUID.
				memcpy(&p_encoded_data[*p_offset], p_service_data->uuid, ESBLE_ATT_UUID_128_LEN);
				*p_offset += ESBLE_ATT_UUID_128_LEN;

				// Encode additional service data.
				if (p_service_data->data_len > 0)
				{
					if (p_service_data->data == NULL)
					{
						return ESBLE_ERROR_INVALID_PARAM;
					}
					memcpy(&p_encoded_data[*p_offset], p_service_data->data, p_service_data->data_len);
					*p_offset += p_service_data->data_len;
				}
				break;
			}

			default:
			{
				return ESBLE_ERROR_INVALID_PARAM;
			}
		}
	}

	return ESBLE_ERROR_NO_ERROR;
}

/*************************************************************************************************/
/*
	Function	:lib_advdata_encode_name
	Description	:将用户设置的设备名称格式化为广播数据包标准格式
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
static esble_err lib_advdata_encode_name(const lib_advdata_t *data, uint8_t *p_encoded_data, uint16_t *p_offset, uint16_t max_size)
{
	const char name[] = BLE_DEV_LOCAL_NAME;
	uint32_t                     data_size;

	switch(data->name_type)
	{
		case LIB_ADVDATA_SHORT_NAME:
		{
			if ((data->short_name_len == 0) || (data->short_name_len > BLE_DEV_LOCAL_NAME_LEN))
			{
				return ESBLE_ERROR_INVALID_PARAM;
			}

			data_size = LIB_ADVDATA_AD_DATA_OFFSET + data->short_name_len;

			// Check for buffer overflow.
			if (((*p_offset) + data_size) > max_size)
			{
				return ESBLE_ERROR_DATA_SIZE;
			}
	
			// Encode Length, AD Type and name.
			p_encoded_data[*p_offset]  = (uint8_t)(LIB_ADVDATA_AD_TYPE_FIELD_SIZE + data->short_name_len);
			*p_offset                 += LIB_ADVDATA_AD_LENGTH_FIELD_SIZE;
			p_encoded_data[*p_offset]  = ESBLE_GAP_AD_TYPE_SHORTENED_NAME;
			*p_offset                 += LIB_ADVDATA_AD_TYPE_FIELD_SIZE;
			memcpy(&p_encoded_data[*p_offset], name, data->short_name_len);
			*p_offset                 += data->short_name_len;

			break;
		}

		case LIB_ADVDATA_FULL_NAME:
		{
			data_size = LIB_ADVDATA_AD_DATA_OFFSET + BLE_DEV_LOCAL_NAME_LEN;

			// Check for buffer overflow.
			if (((*p_offset) + data_size) > max_size)
			{
				return ESBLE_ERROR_DATA_SIZE;
			}
	
			// Encode Length, AD Type and name.
			p_encoded_data[*p_offset]  = (uint8_t)(LIB_ADVDATA_AD_TYPE_FIELD_SIZE + strlen(name));
			*p_offset                 += LIB_ADVDATA_AD_LENGTH_FIELD_SIZE;
			p_encoded_data[*p_offset]  = ESBLE_GAP_AD_TYPE_COMPLETE_NAME;
			*p_offset                 += LIB_ADVDATA_AD_TYPE_FIELD_SIZE;
			memcpy(&p_encoded_data[*p_offset], name, strlen(name));
			*p_offset                 += BLE_DEV_LOCAL_NAME_LEN;
			break;
		}

		default:
		{
			return ESBLE_ERROR_INVALID_PARAM;
		}
	}

	return ESBLE_ERROR_NO_ERROR;
}

esble_err lib_advdata_encode(lib_advdata_t const * const p_advdata,
                              uint8_t             * const p_encoded_data,
                              uint16_t            * const p_len)
{
	esble_err err_code = ESBLE_ERROR_NO_ERROR;
	uint16_t   max_size = *p_len;
	*p_len = 0;

	// Encode LE Bluetooth Device Address
	if (p_advdata->include_addr)
	{
		err_code = lib_advdata_encode_addr(p_encoded_data, p_len, max_size);
		if(err_code != ESBLE_ERROR_NO_ERROR)
		{
			return err_code;
		}
	}

	// Encode appearance.
	if (p_advdata->include_appearance)
	{
		err_code = lib_advdata_encode_appearance(p_encoded_data, p_len, max_size);
		if(err_code != ESBLE_ERROR_NO_ERROR)
		{
			return err_code;
		}
	}

	// Encode TX power level.
	if (p_advdata->tx_power != NULL)
	{
		err_code = lib_advdata_encode_txpower(*p_advdata->tx_power,
                                               p_encoded_data,
                                               p_len,
                                               max_size);
		if(err_code != ESBLE_ERROR_NO_ERROR)
		{
			return err_code;
		}
	}

	// Encode incomplete 16 bit uuid list.
	if (p_advdata->incomplete_16bit_uuid_list != NULL)
	{
		err_code = lib_advdata_encode_uuid_list(p_advdata->incomplete_16bit_uuid_list,
												ESBLE_GAP_AD_TYPE_MORE_16_BIT_UUID,
												ESBLE_ATT_UUID_16_LEN,
												p_encoded_data,
												p_len,
												max_size);
		if(err_code != ESBLE_ERROR_NO_ERROR)
		{
			return err_code;
		}
	}

	// Encode complete 16 bit uuid list.
	if (p_advdata->complete_16bit_uuid_list != NULL)
	{
		err_code = lib_advdata_encode_uuid_list(p_advdata->complete_16bit_uuid_list,
												ESBLE_GAP_AD_TYPE_COMPLETE_LIST_16_BIT_UUID,
												ESBLE_ATT_UUID_16_LEN,
												p_encoded_data,
												p_len,
												max_size);
		if(err_code != ESBLE_ERROR_NO_ERROR)
		{
			return err_code;
		}
	}

	// Encode solicitation 16 bit uuid list.
	if (p_advdata->solicitation_16bit_uuid_list != NULL)
	{
		err_code = lib_advdata_encode_uuid_list(p_advdata->solicitation_16bit_uuid_list,
												ESBLE_GAP_AD_TYPE_RQRD_16_BIT_SVC_UUID,
												ESBLE_ATT_UUID_16_LEN,
												p_encoded_data,
												p_len,
												max_size);
		if(err_code != ESBLE_ERROR_NO_ERROR)
		{
			return err_code;
		}
	}

	// Encode incomplete 32 bit uuid list.
	if (p_advdata->incomplete_32bit_uuid_list != NULL)
	{
		err_code = lib_advdata_encode_uuid_list(p_advdata->incomplete_32bit_uuid_list,
												ESBLE_GAP_AD_TYPE_MORE_32_BIT_UUID,
												ESBLE_ATT_UUID_32_LEN,
												p_encoded_data,
												p_len,
												max_size);
		if(err_code != ESBLE_ERROR_NO_ERROR)
		{
			return err_code;
		}
	}

	// Encode complete 32 bit uuid list.
	if (p_advdata->complete_32bit_uuid_list != NULL)
	{
		err_code = lib_advdata_encode_uuid_list(p_advdata->complete_32bit_uuid_list,
												ESBLE_GAP_AD_TYPE_COMPLETE_LIST_32_BIT_UUID,
												ESBLE_ATT_UUID_32_LEN,
												p_encoded_data,
												p_len,
												max_size);
		if(err_code != ESBLE_ERROR_NO_ERROR)
		{
			return err_code;
		}
	}

	// Encode solicitation 32 bit uuid list.
	if (p_advdata->solicitation_32bit_uuid_list != NULL)
	{
		err_code = lib_advdata_encode_uuid_list(p_advdata->solicitation_32bit_uuid_list,
												ESBLE_GAP_AD_TYPE_RQRD_32_BIT_SVC_UUID,
												ESBLE_ATT_UUID_32_LEN,
												p_encoded_data,
												p_len,
												max_size);
		if(err_code != ESBLE_ERROR_NO_ERROR)
		{
			return err_code;
		}
	}

		// Encode incomplete 128 bit uuid list.
	if (p_advdata->incomplete_128bit_uuid_list != NULL)
	{
		err_code = lib_advdata_encode_uuid_list(p_advdata->incomplete_128bit_uuid_list,
												ESBLE_GAP_AD_TYPE_MORE_128_BIT_UUID,
												ESBLE_ATT_UUID_128_LEN,
												p_encoded_data,
												p_len,
												max_size);
		if(err_code != ESBLE_ERROR_NO_ERROR)
		{
			return err_code;
		}
	}

	// Encode complete 128 bit uuid list.
	if (p_advdata->complete_128bit_uuid_list != NULL)
	{
		err_code = lib_advdata_encode_uuid_list(p_advdata->complete_128bit_uuid_list,
												ESBLE_GAP_AD_TYPE_COMPLETE_LIST_128_BIT_UUID,
												ESBLE_ATT_UUID_128_LEN,
												p_encoded_data,
												p_len,
												max_size);
		if(err_code != ESBLE_ERROR_NO_ERROR)
		{
			return err_code;
		}
	}

	// Encode solicitation 128 bit uuid list.
	if (p_advdata->solicitation_128bit_uuid_list != NULL)
	{
		err_code = lib_advdata_encode_uuid_list(p_advdata->solicitation_128bit_uuid_list,
												ESBLE_GAP_AD_TYPE_RQRD_128_BIT_SVC_UUID,
												ESBLE_ATT_UUID_128_LEN,
												p_encoded_data,
												p_len,
												max_size);
		if(err_code != ESBLE_ERROR_NO_ERROR)
		{
			return err_code;
		}
	}

	// Encode Slave Connection Interval Range.
	if (p_advdata->slave_conn_intl != NULL)
	{
		err_code = lib_advdata_encode_slave_conn_intl(p_advdata->slave_conn_intl, p_encoded_data, p_len, max_size);
		if(err_code != ESBLE_ERROR_NO_ERROR)
		{
			return err_code;
		}
	}

	// Encode Manufacturer Specific Data.
	if (p_advdata->man_data != NULL)
	{
		err_code = lib_advdata_encode_man_data(p_advdata->man_data,
                                              p_encoded_data,
                                              p_len,
                                              max_size);
		if(err_code != ESBLE_ERROR_NO_ERROR)
		{
			return err_code;
		}
	}

	// Encode Service Data.
	if (p_advdata->svc_data_number > 0)
	{
		err_code = lib_advdata_encode_svc_data(p_advdata, p_encoded_data, p_len, max_size);
		if(err_code != ESBLE_ERROR_NO_ERROR)
		{
			return err_code;
		}
	}

	// Encode name.
	if (p_advdata->name_type != LIB_ADVDATA_NO_NAME)
	{
		err_code = lib_advdata_encode_name(p_advdata, p_encoded_data, p_len, max_size);
		if(err_code != ESBLE_ERROR_NO_ERROR)
		{
			return err_code;
		}
	}

	return err_code;
}

/*************************************************************************************************/
/*
	Function	:lib_advdata_search
	Description	: 查找指定AD类型的数据
	Input		:
	Output		:指定AD类型数据在encoded_data中的offset
	Return		:指定AD类型数据的长度
	Notes		:
*/
/*************************************************************************************************/
uint16_t lib_advdata_search(uint8_t const * p_encoded_data, uint16_t data_len, uint16_t *p_offset, uint8_t ad_type)
{
	if ((data_len < LIB_ADVDATA_AD_DATA_OFFSET) || (p_encoded_data == NULL) || (p_offset == NULL))
	{
		return 0;
	}

	uint16_t i = 0;

	while (((i < *p_offset) || (p_encoded_data[i + 1] != ad_type)) && (i < data_len))
	{
		// Jump to next data.
		i += (p_encoded_data[i] + 1);
	}

	if (i >= data_len)
	{
		return 0;
	}
	else
	{
		uint16_t offset = i + 2;
		uint16_t len    = p_encoded_data[i] - 1;
		if ((offset + len) > data_len)
		{
			// Malformed. Extends beyond provided data.
			return 0;
		}
		*p_offset = offset;
		return len;
	}
}
/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
uint8_t * lib_advdata_decode(uint8_t * p_encoded_data, uint16_t data_len, uint8_t ad_type)
{
	uint16_t offset = 0;
	uint16_t len = lib_advdata_search(p_encoded_data, data_len, &offset, ad_type);

	if(len == 0)
	{
		return NULL;
	}
	else
	{
		return &p_encoded_data[offset];
	}
}

