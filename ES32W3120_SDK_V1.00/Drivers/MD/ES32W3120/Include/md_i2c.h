/**********************************************************************************
 *
 * @file    md_i2c.h
 * @brief   Header file of I2C module driver.
 *
 * @date    30 Apri 2021
 * @author  AE Team
 * @note
 *          Change Logs:
 *          Date            Author          Notes
 *          30 Apri 2021    yanght          the first version
 *
 * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 **********************************************************************************
 */

#ifndef __MD_I2C_H__
#define __MD_I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------ */
#include "md_utils.h"
#include "type.h"

/** 
  * @addtogroup Micro_Driver
  * @{
  */
/**
  * @defgroup MD_I2C I2C
  * @brief I2C micro driver
  * @{
  */
/**
  * @defgroup MD_I2C_Public_Macros I2C Public Macros
  * @{
  */
#define MD_I2C_ENABLE(x)  (SET_BIT((x)->CON1, I2C_CON1_PE_MSK))
#define MD_I2C_DISABLE(x) (CLEAR_BIT((x)->CON1, I2C_CON1_PE_MSK))
/**
  * @}
  */
/** @defgroup MD_I2C_Public_Types I2C Public Types
  * @{
  */
/**
  * @brief I2C Addressing Mode
  */
typedef enum {
	MD_I2C_ADDR_7BIT  = 0x0U,	/**< 7 bit address */
	MD_I2C_ADDR_10BIT = 0x1U,	/**< 10 bit address */
} md_i2c_addr_t;

/**
  * @brief I2C Dual Addressing Mode
  */
typedef enum {
	MD_I2C_DUALADDR_DISABLE = 0x0U,	/**< dual address is disable */
	MD_I2C_DUALADDR_ENABLE  = 0x1U,	/**< dual address is enable */
} md_i2c_dual_addr_t;

/**
  * @brief I2C General Call Addressing mode
  */
typedef enum {
	MD_I2C_GENERALCALL_DISABLE = 0x0U, 	/**< feneral call address is disable */
	MD_I2C_GENERALCALL_ENABLE  = 0x1U,	/**< feneral call address is enable */
} md_i2c_general_addr_t;

/**
  * @brief I2C Nostretch Mode
  */
typedef enum {
	MD_I2C_NOSTRETCH_DISABLE = 0x0U,	/**< Nostretch disable */
	MD_I2C_NOSTRETCH_ENABLE  = 0x1U,	/**< Nostretch enable */
} md_i2c_nostretch_t;

/**
  * @brief I2C Memory Address Size
  */
typedef enum {
	MD_I2C_MEMADD_SIZE_8BIT  = 0x8U,	/**< 8 bit memory address size */
	MD_I2C_MEMADD_SIZE_16BIT = 0x10U,	/**< 10 bit memory address size */
} md_i2c_addr_size_t;

/**
  * @brief I2C mode structure definition
  */
typedef enum {
	MD_I2C_MODE_NONE   = 0x0U,	/**< No I2C communication on going */
	MD_I2C_MODE_MASTER = 0x10U,	/**< I2C communication is in Master mode */
	MD_I2C_MODE_SLAVE  = 0x20U,	/**< I2C communication is in Slave mode */
	MD_I2C_MODE_MEM    = 0x40U,	/**< I2C communication is in Memory mode */
} md_i2c_mode_t;

/**
  * @brief I2C Clock
  */
typedef enum {
	MD_I2C_STANDARD_MODE_MAX_CLK     = 100000U, /**< Standard mode clock */
	MD_I2C_FAST_MODE_MAX_CLK         = 400000U,  /**< Fast mode clock */
	MD_I2C_EXTREME_FAST_MODE_MAX_CLK = 1000000U, /**< Extreme mode clock */
} md_i2c_clock_t;

/**
  * @brief I2C OAR2 Register
  */
typedef enum {
	MD_I2C_OAR2_ENDUAL = (1U << 0),	/**< ENDUAL BIT */
	MD_I2C_OAR2_ADD2   = (1U << 1),	/**< ADD2 BIT */
} md_i2c_oar2_t;

/**
  * @brief I2C peripherals module
  */
typedef enum {
	MD_I2C_MODULE_MASTER = (1U << 0),	/**< Master module */
	MD_I2C_MODULE_SLAVE  = (1U << 1),	/**< Slave module */
} md_i2c_module_t;


/**
 * @brief I2C Configuration Structure definition
 */
typedef struct {
	md_i2c_module_t module;			/**< Specifies the communication module */
	uint32_t clk_speed;                	/**< Specifies the clock frequency */
	uint32_t own_addr1;               	/**< Specifies the first device own address */
	md_i2c_addr_t addr_mode;		/**< Specifies addressing mode */
	md_i2c_dual_addr_t dual_addr;		/**< Specifies if dual addressing mode is selected */
	uint32_t own_addr2;               	/**< Specifies the second device own address */
	md_i2c_general_addr_t general_call;	/**< Specifies if general call mode is selected */
	md_i2c_nostretch_t no_stretch;     	/**< Specifies if nostretch mode is selected */
} md_i2c_init_t;
/**
  * @}
  */

/** @defgroup MD_I2C_Public_Functions I2C Public Functions
  * @{
  */
/** @defgroup MD_I2C_Public_Functions_Group2 CON1
  * @{
  */
/**
  * @brief  Enable SMBus Packet Error Calculation (PEC).
  * @param  I2Cx: I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_smbus_pec(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->CON1, I2C_CON1_PECEN_MSK);
}

/**
  * @brief  Disable SMBus Packet Error Calculation (PEC).
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_smbus_pec(I2C_TypeDef *I2Cx)
{
	CLEAR_BIT(I2Cx->CON1, I2C_CON1_PECEN_MSK);
}

/**
  * @brief  Check if SMBus Packet Error Calculation (PEC) is enabled or disabled.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_smbus_pec(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->CON1, I2C_CON1_PECEN_MSK) == (I2C_CON1_PECEN_MSK));
}

/**
  * @brief  Enable SMBus alert (Host or Device mode)
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_smbus_alert(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->CON1, I2C_CON1_ALERTEN_MSK);
}

/**
  * @brief  Disable SMBus alert (Host or Device mode)
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_smbus_alert(I2C_TypeDef *I2Cx)
{
	CLEAR_BIT(I2Cx->CON1, I2C_CON1_ALERTEN_MSK);
}

/**
  * @brief  Check if SMBus alert (Host or Device mode) is enabled or disabled.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_smbus_alert(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->CON1, I2C_CON1_ALERTEN_MSK) == (I2C_CON1_ALERTEN_MSK));
}

/**
  * @brief  Enable SMBus device slave address.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_smbus_slave_addr(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->CON1, I2C_CON1_SMBDEN_MSK);
}

/**
  * @brief  Disable SMBus device slave address.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_smbus_slave_addr(I2C_TypeDef *I2Cx)
{
	CLEAR_BIT(I2Cx->CON1, I2C_CON1_SMBDEN_MSK);
}

/**
  * @brief  Check if SMBus device slave address is enabled or disabled.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_smbus_slave_addr(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->CON1, I2C_CON1_SMBDEN_MSK) == (I2C_CON1_SMBDEN_MSK));
}

/**
  * @brief  Enable SMBus host device address.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_smbus_host_addr(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->CON1, I2C_CON1_SMBHEN_MSK);
}

/**
  * @brief  Disable SMBus host device address.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_smbus_host_addr(I2C_TypeDef *I2Cx)
{
	CLEAR_BIT(I2Cx->CON1, I2C_CON1_SMBHEN_MSK);
}

/**
  * @brief  Check if SMBus host device address is enabled or disabled.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_smbus_host_addr(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->CON1, I2C_CON1_SMBHEN_MSK) == (I2C_CON1_SMBHEN_MSK));
}

/**
  * @brief  Enable General Call.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_general_call(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->CON1, I2C_CON1_GCEN_MSK);
}

/**
  * @brief  Disable General Call.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_general_call(I2C_TypeDef *I2Cx)
{
	CLEAR_BIT(I2Cx->CON1, I2C_CON1_GCEN_MSK);
}

/**
  * @brief  Check if General Call is enabled or disabled.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_general_call(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->CON1, I2C_CON1_GCEN_MSK) == (I2C_CON1_GCEN_MSK));
}

/**
  * @brief  Enable I2C slave device scl stretch function.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_scl_stretch(I2C_TypeDef *I2Cx)
{
	CLEAR_BIT(I2Cx->CON1, I2C_CON1_NOSTRETCH_MSK);
}

/**
  * @brief  Disable I2C slave device scl stretch function.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_scl_stretch(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->CON1, I2C_CON1_NOSTRETCH_MSK);
}

/**
  * @brief  Check if is enabled I2C slave device scl stretch function.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_scl_stretch(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->CON1, I2C_CON1_NOSTRETCH_MSK) != (I2C_CON1_NOSTRETCH_MSK));
}

/** 
  * @brief  Enable I2C slave byte control function.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_slave_byte_control(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->CON1, I2C_CON1_SBC_MSK);
}

/**
  * @brief  Disable I2C slave byte control function.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_slave_byte_control(I2C_TypeDef *I2Cx)
{
	CLEAR_BIT(I2Cx->CON1, I2C_CON1_SBC_MSK);
}

/**
  * @brief  Check if is enabled I2C slave device byte control function.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_slave_byte_control(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->CON1, I2C_CON1_SBC_MSK) != (I2C_CON1_SBC_MSK));
}

/**
  * @brief  Enable DMA receive function.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_dma_receive(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->CON1, I2C_CON1_RXDMAEN_MSK);
}

/**
  * @brief  Disable DMA receive function.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_dma_receive(I2C_TypeDef *I2Cx)
{
	CLEAR_BIT(I2Cx->CON1, I2C_CON1_RXDMAEN_MSK);
}

/**
  * @brief  Check if is enable DMA receive function.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_dma_receive(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->CON1, I2C_CON1_RXDMAEN_MSK) != (I2C_CON1_RXDMAEN_MSK));
}

/**
  * @brief  Enable DMA transmit function.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_dma_transmit(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->CON1, I2C_CON1_TXDMAEN_MSK);
}

/**
  * @brief  Disable DMA transmit function.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_dma_transmit(I2C_TypeDef *I2Cx)
{
	CLEAR_BIT(I2Cx->CON1, I2C_CON1_TXDMAEN_MSK);
}

/**
  * @brief  Check if is enable DMA transmit function.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_dma_transmit(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->CON1, I2C_CON1_TXDMAEN_MSK) != (I2C_CON1_TXDMAEN_MSK));
}

/**
  * @brief  Set I2C digit filter timer.
  * @param  I2Cx I2C Instance.
  * @param  timer filter timer.
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_digit_filter(I2C_TypeDef *I2Cx, uint8_t timer)
{
	MODIFY_REG(I2Cx->CON1, I2C_CON1_DNF_MSK, timer << I2C_CON1_DNF_POSS);
}

/**
  * @brief  Get I2C digit filter timer.
  * @param  I2Cx I2C Instance.
  * @retval  timer filter timer.
  */
__STATIC_INLINE uint32_t md_i2c_get_digit_filter(I2C_TypeDef *I2Cx)
{
	return (READ_BITS(I2Cx->CON1, I2C_CON1_DNF_MSK, I2C_CON1_DNF_POSS));
}

/**
  * @brief  Enable I2C module.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_pe(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->CON1, I2C_CON1_PE_MSK);
}

/**
  * @brief  Disable I2C module.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_pe(I2C_TypeDef *I2Cx)
{
	CLEAR_BIT(I2Cx->CON1, I2C_CON1_PE_MSK);
}

/**
  * @brief  Check if i2c is enabled or disabled.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_pe(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->CON1, I2C_CON1_PE_MSK) == (I2C_CON1_PE_MSK));
}
/**
  * @}
  */
/** @defgroup MD_I2C_Public_Functions_Group3 CON2
  * @{
  */
/**
  * @brief  Get I2C acknowledge updata flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_get_ack_updata(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->CON2, I2C_CON2_ACK_UPD_MSK));
}

/**
  * @brief  Clear I2C acknowledge updata flag.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_clear_ack_updata(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->CON2, I2C_CON2_ACK_UPD_MSK);
}

/**
  * @brief  Enable I2C wait acknowledge function.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_holdack(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->CON2, I2C_CON2_HOLDACK_MSK);
}

/**
  * @brief  Disable I2C wait acknowledge function.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_holdack(I2C_TypeDef *I2Cx)
{
	CLEAR_BIT(I2Cx->CON2, I2C_CON2_HOLDACK_MSK);
}

/**
  * @brief  Check if the I2C wait acknowledge is enabled or disabled.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_holdack(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->CON2, I2C_CON2_HOLDACK_MSK) == (I2C_CON2_HOLDACK_MSK));
}

/**
  * @brief  Enable SMBus PEC transfer requests function.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_pec_byte(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->CON2, I2C_CON2_PECBYTE_MSK);
}

/**
  * @brief  Disable SMBus PEC transfer requests function.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_pec_byte(I2C_TypeDef *I2Cx)
{
	CLEAR_BIT(I2Cx->CON2, I2C_CON2_PECBYTE_MSK);
}

/**
  * @brief  Check if SMBus PEC transfer requests function is enabled or disabled.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_pec_byte(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->CON2, I2C_CON2_PECBYTE_MSK) == (I2C_CON2_PECBYTE_MSK));
}

/**
  * @brief  Enable I2C auto end function.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_auto_end(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->CON2, I2C_CON2_AUTOEND_MSK);
}

/**
  * @brief  Disable I2C auto end function.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_auto_end(I2C_TypeDef *I2Cx)
{
	CLEAR_BIT(I2Cx->CON2, I2C_CON2_AUTOEND_MSK);
}

/**
  * @brief  Check if I2C auto end function is enabled or disabled.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_auto_end(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->CON2, I2C_CON2_AUTOEND_MSK) == (I2C_CON2_AUTOEND_MSK));
}

/**
  * @brief  Enable I2C reload fuctions.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_reload(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->CON2, I2C_CON2_RELOAD_MSK);
}

/**
  * @brief  Disable I2C reload fuctions.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_reload(I2C_TypeDef *I2Cx)
{
	CLEAR_BIT(I2Cx->CON2, I2C_CON2_RELOAD_MSK);
}

/**
  * @brief  Check if I2C reload fuctions is enabled or disabled.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_reload(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->CON2, I2C_CON2_RELOAD_MSK) == (I2C_CON2_RELOAD_MSK));
}

/**
  * @brief  Set I2C transmit data length.
  * @param  I2Cx I2C Instance.
  * @param  length of transmit data.
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_transmit_length(I2C_TypeDef *I2Cx, uint32_t length)
{
	MODIFY_REG(I2Cx->CON2, I2C_CON2_NBYTES_MSK, length << I2C_CON2_NBYTES_POSS);
}

/**
  * @brief  Get I2C transmit data length.
  * @param  I2Cx I2C Instance.
  * @retval length of transmit data.
  */
__STATIC_INLINE uint32_t md_i2c_get_transmit_length(I2C_TypeDef *I2Cx)
{
	return (READ_BITS(I2Cx->CON2, I2C_CON2_NBYTES_MSK, I2C_CON2_NBYTES_POSS));
}

/**
  * @brief  Set I2C send NACK.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_nack(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->CON2, I2C_CON2_NACK_MSK);
}

/**
  * @brief  Get I2C NACK flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_get_nack(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->CON2, I2C_CON2_NACK_MSK));
}

/**
  * @brief  Set I2C send stop flag.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_stop(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->CON2, I2C_CON2_STOP_MSK);
}

/**
  * @brief  Get I2C stop flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_get_stop(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->CON2, I2C_CON2_STOP_MSK));
}

/**
  * @brief  Set I2C send start flag.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_start(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->CON2, I2C_CON2_START_MSK);
}

/**
  * @brief  Get I2C start flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_get_start(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->CON2, I2C_CON2_START_MSK));
}

/**
  * @brief  Enable i2c send 10-bit standard address header.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_standard_10_bit_header(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->CON2, I2C_CON2_HEAD10R_MSK);
}

/**
  * @brief  Disable i2c send 10-bit standard address header.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_standard_10_bit_header(I2C_TypeDef *I2Cx)
{
	CLEAR_BIT(I2Cx->CON2, I2C_CON2_HEAD10R_MSK);
}

/**
  * @brief  Check if is enabled send 10-bit standard address header.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_standard_10_bit_header(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->CON2, I2C_CON2_HEAD10R_MSK) == (I2C_CON2_HEAD10R_MSK));
}

/**
  * @brief  Enable 10-bit address mode.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_addr_10_bit(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->CON2, I2C_CON2_ADD10_MSK);
}

/**
  * @brief  Enable 7-bit address mode.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_addr_7_bit(I2C_TypeDef *I2Cx)
{
	CLEAR_BIT(I2Cx->CON2, I2C_CON2_ADD10_MSK);
}

/**
  * @brief  Check if is enabled 10-bit address mode.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_addr_10_bit(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->CON2, I2C_CON2_ADD10_MSK) == (I2C_CON2_ADD10_MSK));
}

/**
  * @brief  Enable i2c master read.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_master_read(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->CON2, I2C_CON2_RD_WRN_MSK);
}

/**
  * @brief  Enable i2c master write.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_master_write(I2C_TypeDef *I2Cx)
{
	CLEAR_BIT(I2Cx->CON2, I2C_CON2_RD_WRN_MSK);
}

/**
  * @brief  Check if is enabled master read.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_master_read(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->CON2, I2C_CON2_RD_WRN_MSK) == (I2C_CON2_RD_WRN_MSK));
}

/**
  * @brief  Set address 0:9 bit value.
  * @param  I2Cx I2C Instance.
  * @param  addr: address 0:9 bit value.
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_addr_0_9_bit(I2C_TypeDef *I2Cx, uint32_t addr)
{
	MODIFY_REG(I2Cx->CON2, I2C_CON2_SADD_MSK, (addr << I2C_CON2_SADD_POSS));
}

/**
  * @brief  Get address 0:9 bit value.
  * @param  I2Cx I2C Instance.
  * @retval address 0:9 bit value.
  */
__STATIC_INLINE uint32_t md_i2c_get_addr_0_9_bit(I2C_TypeDef *I2Cx)
{
	return (READ_BITS(I2Cx->CON2, I2C_CON2_SADD_MSK, I2C_CON2_SADD_POSS));
}
/**
  * @}
  */
/** @defgroup MD_I2C_Public_Functions_Group4 ADDR1
  * @{
  */
/**
  * @brief  Enable i2c own1 address.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_own1_address(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->ADDR1, I2C_ADDR1_OA1EN_MSK);
}

/**
  * @brief  Disable i2c own1 address.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_own1_address(I2C_TypeDef *I2Cx)
{
	CLEAR_BIT(I2Cx->ADDR1, I2C_ADDR1_OA1EN_MSK);
}

/**
  * @brief  Check if is enabled i2c own1 address.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_own1_address(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->ADDR1, I2C_ADDR1_OA1EN_MSK) == (I2C_ADDR1_OA1EN_MSK));
}

/**
  * @brief  Enable i2c own1 10_bit address.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_own1_10_bit_addr(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->ADDR1, I2C_ADDR1_OA1MODE_MSK);
}

/**
  * @brief  Enable i2c own1 7_bit address.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_own1_7_bit_addr(I2C_TypeDef *I2Cx)
{
	CLEAR_BIT(I2Cx->ADDR1, I2C_ADDR1_OA1MODE_MSK);
}

/**
  * @brief  Check if is enabled i2c own1 10_bit address.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_own1_10_bit_address(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->ADDR1, I2C_ADDR1_OA1MODE_MSK) == (I2C_ADDR1_OA1MODE_MSK));
}

/**
  * @brief  Set own1 address.
  * @param  I2Cx I2C Instance.
  * @param  addr of own1.
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_own1_addr(I2C_TypeDef *I2Cx, uint32_t addr)
{
	MODIFY_REG(I2Cx->ADDR1, I2C_ADDR1_OA1_MSK, (addr << I2C_ADDR1_OA1_POSS));
}

/**
  * @brief  Get own1 address.
  * @param  I2Cx I2C Instance.
  * @retval addr of own1.
  */
__STATIC_INLINE uint32_t md_i2c_get_own1_addr(I2C_TypeDef *I2Cx)
{
	return (READ_BITS(I2Cx->ADDR1, I2C_ADDR1_OA1_MSK, I2C_ADDR1_OA1_POSS));
}
/**
  * @}
  */
/** @defgroup MD_I2C_Public_Functions_Group5 ADDR2
  * @{
  */
/**
  * @brief  Enable i2c own2 address.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_own2_address(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->ADDR2, I2C_ADDR2_OA2EN_MSK);
}

/**
  * @brief  Disable i2c own2 address.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_own2_address(I2C_TypeDef *I2Cx)
{
	CLEAR_BIT(I2Cx->ADDR2, I2C_ADDR2_OA2EN_MSK);
}

/**
  * @brief  Check if is enabled i2c own2 address.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_own2_address(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->ADDR2, I2C_ADDR2_OA2EN_MSK) == (I2C_ADDR2_OA2EN_MSK));
}

/**
  * @brief  Set the own2 mask Address.
  * @param  I2Cx I2C Instance.
  * @param  own2mask mask value.
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_own2_mask_address(I2C_TypeDef *I2Cx, uint32_t own2mask)
{
	MODIFY_REG(I2Cx->ADDR2, I2C_ADDR2_OA2MSK_MSK, (own2mask << I2C_ADDR2_OA2MSK_POSS));
}

/**
  * @brief  Get the own2 mask Address.
  * @param  I2Cx I2C Instance.
  * @retval Own2 mask value.
  */
__STATIC_INLINE uint32_t md_i2c_get_own2_mask_address(I2C_TypeDef *I2Cx)
{
	return (READ_BITS(I2Cx->ADDR2, I2C_ADDR2_OA2MSK_MSK, I2C_ADDR2_OA2MSK_POSS));
}

/**
  * @brief  Set the own2 Address.
  * @param  I2Cx I2C Instance.
  * @param  OwnAddress2 This parameter must be a value between Min_Data=0 and Max_Data=0x7F.
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_own2_address(I2C_TypeDef *I2Cx, uint32_t OwnAddress2)
{
	MODIFY_REG(I2Cx->ADDR2, I2C_ADDR2_OA2_MSK, (OwnAddress2 << I2C_ADDR2_OA2_POSS));
}

/**
  * @brief  Get the 7bits Own Address2 value.
  * @param  I2Cx I2C Instance.
  * @retval Own Address2 value.
  */
__STATIC_INLINE uint32_t md_i2c_get_own2_address(I2C_TypeDef *I2Cx)
{
	return (READ_BITS(I2Cx->ADDR2, I2C_ADDR2_OA2_MSK, I2C_ADDR2_OA2_POSS));
}
/**
  * @}
  */
/** @defgroup MD_I2C_Public_Functions_Group6 TIMINGR
  * @{
  */
/**
  * @brief  Set i2c clock prescaler value.
  * @param  I2Cx I2C Instance.
  * @param  pres prescaler value.
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_clock_prescaler(I2C_TypeDef *I2Cx, uint32_t pres)
{
	MODIFY_REG(I2Cx->TIMINGR, I2C_TIMINGR_PRESC_MSK, pres << I2C_TIMINGR_PRESC_POSS);
}

/**
  * @brief  Get i2c clock prescaler value.
  * @param  I2Cx I2C Instance.
  * @retval clock prescaler value.
  */
__STATIC_INLINE uint32_t md_i2c_get_clock_prescaler(I2C_TypeDef *I2Cx)
{
	return (READ_BITS(I2Cx->TIMINGR, I2C_TIMINGR_PRESC_MSK, I2C_TIMINGR_PRESC_POSS));
}

/**
  * @brief  Set i2c clock delay time.
  * @param  I2Cx I2C Instance.
  * @param  time delay time.
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_clock_delay(I2C_TypeDef *I2Cx, uint32_t time)
{
	MODIFY_REG(I2Cx->TIMINGR, I2C_TIMINGR_SCLDEL_MSK, time << I2C_TIMINGR_SCLDEL_POSS);
}

/**
  * @brief  Get i2c clock delay time.
  * @param  I2Cx I2C Instance.
  * @retval clock delay value.
  */
__STATIC_INLINE uint32_t md_i2c_get_clock_delay(I2C_TypeDef *I2Cx)
{
	return (READ_BITS(I2Cx->TIMINGR, I2C_TIMINGR_SCLDEL_MSK, I2C_TIMINGR_SCLDEL_POSS));
}

/**
  * @brief  Set i2c data delay time.
  * @param  I2Cx I2C Instance.
  * @param  time delay time.
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_data_delay(I2C_TypeDef *I2Cx, uint32_t time)
{
	MODIFY_REG(I2Cx->TIMINGR, I2C_TIMINGR_SDADEL_MSK, time << I2C_TIMINGR_SDADEL_POSS);
}

/**
  * @brief  Get i2c clock delay time.
  * @param  I2Cx I2C Instance.
  * @retval data delay value.
  */
__STATIC_INLINE uint32_t md_i2c_get_data_delay(I2C_TypeDef *I2Cx)
{
	return (READ_BITS(I2Cx->TIMINGR, I2C_TIMINGR_SDADEL_MSK, I2C_TIMINGR_SDADEL_POSS));
}

/**
  * @brief  Set i2c clock high level time.
  * @param  I2Cx I2C Instance.
  * @param  time high level time.
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_clock_high_time(I2C_TypeDef *I2Cx, uint32_t time)
{
	MODIFY_REG(I2Cx->TIMINGR, I2C_TIMINGR_SCLH_MSK, time << I2C_TIMINGR_SCLH_POSS);
}

/**
  * @brief  Get i2c clock high level time.
  * @param  I2Cx I2C Instance.
  * @retval scl high level time.
  */
__STATIC_INLINE uint32_t md_i2c_get_clock_high_time(I2C_TypeDef *I2Cx)
{
	return (READ_BITS(I2Cx->TIMINGR, I2C_TIMINGR_SCLH_MSK, I2C_TIMINGR_SCLH_POSS));
}

/**
  * @brief  Set i2c clock low level time.
  * @param  I2Cx I2C Instance.
  * @param  time low level time.
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_clock_low_time(I2C_TypeDef *I2Cx, uint32_t time)
{
	MODIFY_REG(I2Cx->TIMINGR, I2C_TIMINGR_SCLL_MSK, time << I2C_TIMINGR_SCLL_POSS);
}

/**
  * @brief  Get i2c clock low level time.
  * @param  I2Cx I2C Instance.
  * @retval scl low level time.
  */
__STATIC_INLINE uint32_t md_i2c_get_clock_low_time(I2C_TypeDef *I2Cx)
{
	return (READ_BITS(I2Cx->TIMINGR, I2C_TIMINGR_SCLL_MSK, I2C_TIMINGR_SCLL_POSS));
}
/**
  * @}
  */
/** @defgroup MD_I2C_Public_Functions_Group7 TIMEOUTR
  * @{
  */
/**
  * @brief  Enable i2c clock stretch cumulation timeout function.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_texten(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TEXTEN_MSK);
}

/**
  * @brief  Disable i2c clock stretch cumulation timeout function.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_texten(I2C_TypeDef *I2Cx)
{
	CLEAR_BIT(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TEXTEN_MSK);
}

/**
  * @brief  Check if is enabled i2c clock stretch cumulation timeout function.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_texten(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TEXTEN_MSK) == (I2C_TIMEOUTR_TEXTEN_MSK));
}

/**
  * @brief  Set i2c bus timeout time.
  * @param  I2Cx I2C Instance.
  * @param  time timeout time.
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_bus_timeoutB_time(I2C_TypeDef *I2Cx, uint8_t time)
{
	MODIFY_REG(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TIMEOUTB_MSK, (time << I2C_TIMEOUTR_TIMEOUTB_POSS));
}

/**
  * @brief  Get i2c bus timeout time.
  * @param  I2Cx I2C Instance.
  * @retval timeout time.
  */
__STATIC_INLINE uint32_t md_i2c_get_bus_timeoutB_time(I2C_TypeDef *I2Cx)
{
	return (READ_BITS(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TIMEOUTB_MSK, I2C_TIMEOUTR_TIMEOUTB_POSS));
}

/**
  * @brief  Enable i2c timeout function.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_timeouten(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TIMEOUTEN_MSK);
}

/**
  * @brief  Disable i2c timeout function.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_timeouten(I2C_TypeDef *I2Cx)
{
	CLEAR_BIT(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TIMEOUTEN_MSK);
}

/**
  * @brief  Check if is enabled i2c timeout function.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_timeouten(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TIMEOUTEN_MSK) == (I2C_TIMEOUTR_TIMEOUTEN_MSK));
}

/**
  * @brief  Enable i2c idle state timeout detect function.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_idle_timeout(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TIDLE_MSK);
}

/**
  * @brief  Enable i2c scl low state detect function.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_scl_low_timeout(I2C_TypeDef *I2Cx)
{
	CLEAR_BIT(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TIDLE_MSK);
}

/**
  * @brief  Check if is enabled i2c idle state timeout detect function
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_idle_timeout(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TIDLE_MSK) == (I2C_TIMEOUTR_TIDLE_MSK));
}

/**
  * @brief  Set i2c bus timeout time.
  * @param  I2Cx I2C Instance.
  * @param  time timeout time.
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_bus_timeoutA_time(I2C_TypeDef *I2Cx, uint8_t time)
{
	MODIFY_REG(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TIMEOUTA_MSK, (time << I2C_TIMEOUTR_TIMEOUTA_POSS));
}

/**
  * @brief  Get i2c bus timeout time.
  * @param  I2Cx I2C Instance.
  * @retval timeout time.
  */
__STATIC_INLINE uint32_t md_i2c_get_bus_timeoutA_time(I2C_TypeDef *I2Cx)
{
	return (READ_BITS(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TIMEOUTA_MSK, I2C_TIMEOUTR_TIMEOUTA_POSS));
}
/**
  * @}
  */
/** @defgroup MD_I2C_Public_Functions_Group8 STAT
  * @{
  */
/**
  * @brief  Get slave module matched address.
  * @param  I2Cx I2C Instance.
  * @retval matched address.
  */
__STATIC_INLINE uint32_t md_i2c_get_addr_match(I2C_TypeDef *I2Cx)
{
	return (READ_BITS(I2Cx->STAT, I2C_STAT_ADDCODE_MSK, I2C_STAT_ADDCODE_POSS));
}

/**
  * @brief  Get slave module write.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_write(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->STAT, I2C_STAT_DIR_MSK) != (I2C_STAT_DIR_MSK));
}

/**
  * @brief  Get slave module read.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_read(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->STAT, I2C_STAT_DIR_MSK) == (I2C_STAT_DIR_MSK));
}

/**
  * @brief  Get bus busy flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_busy(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->STAT, I2C_STAT_BUSY_MSK) == (I2C_STAT_BUSY_MSK));
}

/**
  * @brief  Get transmit and reload complete flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_tcr(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->STAT, I2C_STAT_TCR_MSK) == (I2C_STAT_TCR_MSK));
}

/**
  * @brief  Get transmit complete flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_tc(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->STAT, I2C_STAT_TC_MSK) == (I2C_STAT_TC_MSK));
}

/**
  * @brief  Get receive fifo exceed thread flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_rxth(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->STAT, I2C_STAT_RXTH_MSK) == (I2C_STAT_RXTH_MSK));
}

/**
  * @brief  Get receive fifo underflow flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_rxud(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->STAT, I2C_STAT_RXUD_MSK) == (I2C_STAT_RXUD_MSK));
}

/**
  * @brief  Get receive fifo overflow flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_rxov(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->STAT, I2C_STAT_RXOV_MSK) == (I2C_STAT_RXOV_MSK));
}

/**
  * @brief  Get receive fifo empty flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_rxe(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->STAT, I2C_STAT_RXE_MSK) == (I2C_STAT_RXE_MSK));
}

/**
  * @brief  Get receive fifo full flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_rxf(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->STAT, I2C_STAT_RXF_MSK) == (I2C_STAT_RXF_MSK));
}

/**
  * @brief  Get transmit fifo exceed thread flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_txth(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->STAT, I2C_STAT_TXTH_MSK) == (I2C_STAT_TXTH_MSK));
}

/**
  * @brief  Get transmit fifo underflow flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_txud(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->STAT, I2C_STAT_TXUD_MSK) == (I2C_STAT_TXUD_MSK));
}

/**
  * @brief  Get transmit fifo overflow flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_txov(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->STAT, I2C_STAT_TXOV_MSK) == (I2C_STAT_TXOV_MSK));
}

/**
  * @brief  Get transmit fifo empty flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_txe(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->STAT, I2C_STAT_TXE_MSK) == (I2C_STAT_TXE_MSK));
}

/**
  * @brief  Get transmit fifo full flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_txf(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->STAT, I2C_STAT_TXF_MSK) == (I2C_STAT_TXF_MSK));
}
/**
  * @}
  */
/** @defgroup MD_I2C_Public_Functions_Group9 FCON
  * @{
  */
/**
  * @brief  Set i2c receive FIFO thread value.
  * @param  I2Cx I2C Instance.
  * @param  num thread value.
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_receive_fifo_thread(I2C_TypeDef *I2Cx, uint8_t num)
{
	MODIFY_REG(I2Cx->FCON, I2C_FCON_RXFTH_MSK, (num << I2C_FCON_RXFTH_POSS));
}

/**
  * @brief  Get i2c receive FIFO thread value.
  * @param  I2Cx I2C Instance.
  * @retval timeout time.
  */
__STATIC_INLINE uint32_t md_i2c_get_receive_fifo_thread(I2C_TypeDef *I2Cx)
{
	return (READ_BITS(I2Cx->FCON, I2C_FCON_RXFTH_MSK, I2C_FCON_RXFTH_POSS));
}

/**
  * @brief  Set i2c receive FIFO reset.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_receive_fifo_reset(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->FCON, I2C_FCON_RXFRST_MSK);
}

/**
  * @brief  Get i2c receive FIFO state.
  * @param  I2Cx I2C Instance.
  * @retval receive FIFO reset.
  */
__STATIC_INLINE uint32_t md_i2c_get_receive_fifo_reset(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->FCON, I2C_FCON_RXFRST_MSK));
}

/**
  * @brief  Get i2c receive FIFO data level.
  * @param  I2Cx I2C Instance.
  * @retval receive FIFO data level.
  */
__STATIC_INLINE uint32_t md_i2c_get_receive_fifo_level(I2C_TypeDef *I2Cx)
{
	return (READ_BITS(I2Cx->FCON, I2C_FCON_RXFLV_MSK, I2C_FCON_RXFLV_POSS));
}

/**
  * @brief  Set i2c transmit FIFO thread value.
  * @param  I2Cx I2C Instance.
  * @param  num thread value.
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_transmit_fifo_thread(I2C_TypeDef *I2Cx, uint8_t num)
{
	MODIFY_REG(I2Cx->FCON, I2C_FCON_TXFTH_MSK, (num << I2C_FCON_TXFTH_POSS));
}

/**
  * @brief  Get i2c transmit FIFO thread value.
  * @param  I2Cx I2C Instance.
  * @retval timeout time.
  */
__STATIC_INLINE uint32_t md_i2c_get_transmit_fifo_thread(I2C_TypeDef *I2Cx)
{
	return (READ_BITS(I2Cx->FCON, I2C_FCON_TXFTH_MSK, I2C_FCON_TXFTH_POSS));
}

/**
  * @brief  Set i2c transmit FIFO reset.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_transmit_fifo_reset(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->FCON, I2C_FCON_TXFRST_MSK);
}

/**
  * @brief  Get i2c transmit FIFO state.
  * @param  I2Cx I2C Instance.
  * @retval transmit FIFO reset.
  */
__STATIC_INLINE uint32_t md_i2c_get_transmit_fifo_reset(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->FCON, I2C_FCON_TXFRST_MSK));
}

/**
  * @brief  Get i2c transmit FIFO data level.
  * @param  I2Cx I2C Instance.
  * @retval transmit FIFO data level.
  */
__STATIC_INLINE uint32_t md_i2c_get_transmit_fifo_level(I2C_TypeDef *I2Cx)
{
	return (READ_BITS(I2Cx->FCON, I2C_FCON_TXFLV_MSK, I2C_FCON_TXFLV_POSS));
}
/**
  * @}
  */
/** @defgroup MD_I2C_Public_Functions_Group10 PECR
  * @{
  */
/**
  * @brief  Get receive pec register value.
  * @param  I2Cx I2C Instance.
  * @retval receive data.
  */
__STATIC_INLINE uint32_t md_i2c_get_rx_reg_pec(I2C_TypeDef *I2Cx)
{
	return (READ_BITS(I2Cx->PECR, I2C_PECR_PEC_MSK, I2C_PECR_PEC_POSS));
}
/**
  * @}
  */
/** @defgroup MD_I2C_Public_Functions_Group11 RXDATA
  * @{
  */
/**
  * @brief  Get receive register value.
  * @param  I2Cx I2C Instance.
  * @retval receive data.
  */
__STATIC_INLINE uint32_t md_i2c_get_rx_reg_data(I2C_TypeDef *I2Cx)
{
	return (READ_BITS(I2Cx->RXDATA, I2C_RXDATA_RXDATA_MSK, I2C_RXDATA_RXDATA_POSS));
}
/**
  * @}
  */
/** @defgroup MD_I2C_Public_Functions_Group12 TXDATA
  * @{
  */
/**
  * @brief  Set transmit register value.
  * @param  I2Cx I2C Instance.
  * @param  data transmit value.
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_tx_reg_data(I2C_TypeDef *I2Cx, uint8_t data)
{
	MODIFY_REG(I2Cx->TXDATA, I2C_TXDATA_TXDATA_MSK, data << I2C_TXDATA_TXDATA_POSS);
}
/**
  * @}
  */
/** @defgroup MD_I2C_Public_Functions_Group13 IER
  * @{
  */
/**
  * @brief  Enable TX fifo empty interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_it_txe(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IER, I2C_IER_TXEIE_MSK);
}

/**
  * @brief  Enable TX fifo overflow interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_it_txov(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IER, I2C_IER_TXOVIE_MSK);
}

/**
  * @brief  Enable TX fifo underflow interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_it_txud(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IER, I2C_IER_TXUDIE_MSK);
}

/**
  * @brief  Enable TX fifo low than thread interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_it_txth(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IER, I2C_IER_TXTHIE_MSK);
}

/**
  * @brief  Enable rx fifo full interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_it_rxf(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IER, I2C_IER_RXFIE_MSK);
}

/**
  * @brief  Enable rx fifo overflow interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_it_rxov(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IER, I2C_IER_RXOVIE_MSK);
}

/**
  * @brief  Enable rx fifo underflow interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_it_rxud(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IER, I2C_IER_RXUDIE_MSK);
}

/**
  * @brief  Enable rx fifo low than thread interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_it_rxth(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IER, I2C_IER_RXTHIE_MSK);
}

/**
  * @brief  Enable i2c transmit complete interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_it_tc(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IER, I2C_IER_TCIE_MSK);
}

/**
  * @brief  Enable i2c transmit and reload complete interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_it_tcr(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IER, I2C_IER_TCRIE_MSK);
}

/**
  * @brief  Enable i2c addr matched interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_it_addr(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IER, I2C_IER_ADDRIE_MSK);
}

/**
  * @brief  Enable i2c nack interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_it_nack(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IER, I2C_IER_NACKIE_MSK);
}

/**
  * @brief  Enable i2c stop interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_it_stop(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IER, I2C_IER_STOPIE_MSK);
}

/**
  * @brief  Enable i2c bus error interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_it_berr(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IER, I2C_IER_BERRIE_MSK);
}

/**
  * @brief  Enable i2c lost arbitration interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_it_arlo(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IER, I2C_IER_ARLOIE_MSK);
}

/**
  * @brief  Enable i2c pec error interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_it_pece(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IER, I2C_IER_PECEIE_MSK);
}

/**
  * @brief  Enable i2c timeout interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_it_tout(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IER, I2C_IER_TOUTIE_MSK);
}

/**
  * @brief  Enable i2c SMBus alert interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_it_alert(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IER, I2C_IER_ALERTIE_MSK);
}
/**
  * @}
  */
/** @defgroup MD_I2C_Public_Functions_Group14 IDR
  * @{
  */
/**
  * @brief  Disable TX fifo empty interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_it_txe(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IDR, I2C_IDR_TXEID_MSK);
}

/**
  * @brief  Disable TX fifo overflow interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_it_txov(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IDR, I2C_IDR_TXOVID_MSK);
}

/**
  * @brief  Disable TX fifo underflow interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_it_txud(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IDR, I2C_IDR_TXUDID_MSK);
}

/**
  * @brief  Disable TX fifo low than thread interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_it_txth(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IDR, I2C_IDR_TXTHID_MSK);
}

/**
  * @brief  Disable rx fifo full interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_it_rxf(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IDR, I2C_IDR_RXFID_MSK);
}

/**
  * @brief  Disable rx fifo overflow interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_it_rxov(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IDR, I2C_IDR_RXOVID_MSK);
}

/**
  * @brief  Disable rx fifo underflow interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_it_rxud(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IDR, I2C_IDR_RXUDID_MSK);
}

/**
  * @brief  Disable rx fifo low than thread interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_it_rxth(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IDR, I2C_IDR_RXTHID_MSK);
}

/**
  * @brief  Disable i2c transmit complete interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_it_tc(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IDR, I2C_IDR_TCID_MSK);
}

/**
  * @brief  Disable i2c transmit and reload complete interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_it_tcr(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IDR, I2C_IDR_TCRID_MSK);
}

/**
  * @brief  Disable i2c addr matched interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_it_addr(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IDR, I2C_IDR_ADDRID_MSK);
}

/**
  * @brief  Disable i2c nack interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_it_nack(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IDR, I2C_IDR_NACKID_MSK);
}

/**
  * @brief  Disable i2c stop interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_it_stop(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IDR, I2C_IDR_STOPID_MSK);
}

/**
  * @brief  Disable i2c bus error interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_it_berr(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IDR, I2C_IDR_BERRID_MSK);
}

/**
  * @brief  Disable i2c lost arbitration interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_it_arlo(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IDR, I2C_IDR_ARLOID_MSK);
}

/**
  * @brief  Disable i2c pec error interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_it_pece(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IDR, I2C_IDR_PECEID_MSK);
}

/**
  * @brief  Disable i2c timeout interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_it_tout(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IDR, I2C_IDR_TOUTID_MSK);
}

/**
  * @brief  Disable i2c SMBus alert interrupt.
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_it_alert(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->IDR, I2C_IDR_ALERTID_MSK);
}
/**
  * @}
  */
/** @defgroup MD_I2C_Public_Functions_Group15 IVS
  * @{
  */
/**
  * @brief  Check if the TX fifo empty interrupt is enabled or disabled.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_it_txe(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IVS, I2C_IVS_TXEIV_MSK) == (I2C_IVS_TXEIV_MSK));
}

/**
  * @brief  Check if the TX fifo overflow interrupt is enabled or disabled.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_it_txov(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IVS, I2C_IVS_TXOVIV_MSK) == (I2C_IVS_TXOVIV_MSK));
}

/**
  * @brief  Check if the TX fifo underflow interrupt is enabled or disabled.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_it_txud(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IVS, I2C_IVS_TXUDIV_MSK) == (I2C_IVS_TXUDIV_MSK));
}

/**
  * @brief  Check if the TX fifo low than thread interrupt is enabled or disabled.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_it_txth(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IVS, I2C_IVS_TXTHIV_MSK) == (I2C_IVS_TXTHIV_MSK));
}

/**
  * @brief  Check if the rx fifo full interrupt is enabled or disabled.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_it_rxf(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IVS, I2C_IVS_RXFIV_MSK) == (I2C_IVS_RXFIV_MSK));
}

/**
  * @brief  Check if the rx fifo overflow interrupt is enabled or disabled.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_it_rxov(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IVS, I2C_IVS_RXOVIV_MSK) == (I2C_IVS_RXOVIV_MSK));
}

/**
  * @brief  Check if the rx fifo underflow interrupt is enabled or disabled.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_it_rxud(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IVS, I2C_IVS_RXUDIV_MSK) == (I2C_IVS_RXUDIV_MSK));
}

/**
  * @brief  Check if the rx fifo low than thread interrupt is enabled or disabled.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_it_rxth(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IVS, I2C_IVS_RXTHIV_MSK) == (I2C_IVS_RXTHIV_MSK));
}

/**
  * @brief  Check if the transmit complete interrupt is enabled or disabled.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_it_tc(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IVS, I2C_IVS_TCIV_MSK) == (I2C_IVS_TCIV_MSK));
}

/**
  * @brief  Check if the transmit and reload complete interrupt is enabled or disabled.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_it_tcr(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IVS, I2C_IVS_TCRIV_MSK) == (I2C_IVS_TCRIV_MSK));
}

/**
  * @brief  Check if the addr matched interrupt is enabled or disabled.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_it_addr(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IVS, I2C_IVS_ADDRIV_MSK) == (I2C_IVS_ADDRIV_MSK));
}

/**
  * @brief  Check if the nack interrupt is enabled or disabled.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_it_nack(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IVS, I2C_IVS_NACKIV_MSK) == (I2C_IVS_NACKIV_MSK));
}

/**
  * @brief  Check if the stop interrupt is enabled or disabled.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_it_stop(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IVS, I2C_IVS_STOPIV_MSK) == (I2C_IVS_STOPIV_MSK));
}

/**
  * @brief  Check if the bus error interrupt is enabled or disabled.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_it_berr(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IVS, I2C_IVS_BERRIV_MSK) == (I2C_IVS_BERRIV_MSK));
}

/**
  * @brief  Check if the lost arbitration interrupt is enabled or disabled.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_it_arlo(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IVS, I2C_IVS_ARLOIV_MSK) == (I2C_IVS_ARLOIV_MSK));
}

/**
  * @brief  Check if the pec error interrupt is enabled or disabled.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_it_pece(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IVS, I2C_IVS_PECEIV_MSK) == (I2C_IVS_PECEIV_MSK));
}

/**
  * @brief  Check if the timeout interrupt is enabled or disabled.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_it_tout(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IVS, I2C_IVS_TOUTIV_MSK) == (I2C_IVS_TOUTIV_MSK));
}

/**
  * @brief  Check if the SMBus alert interrupt is enabled or disabled.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_it_alert(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IVS, I2C_IVS_ALERTIV_MSK) == (I2C_IVS_ALERTIV_MSK));
}
/**
  * @}
  */
/** @defgroup MD_I2C_Public_Functions_Group16 RIF
  * @{
  */
/**
  * @brief  Get tx fifo empty interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_txe(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->RIF, I2C_RIF_TXERI_MSK) == (I2C_RIF_TXERI_MSK));
}

/**
  * @brief  Get TX fifo overflow interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_txov(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->RIF, I2C_RIF_TXOVRI_MSK) == (I2C_RIF_TXOVRI_MSK));
}

/**
  * @brief  Get TX fifo underflow interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_txud(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->RIF, I2C_RIF_TXUDRI_MSK) == (I2C_RIF_TXUDRI_MSK));
}

/**
  * @brief  Get TX fifo low than thread interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_txth(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->RIF, I2C_RIF_TXTHRI_MSK) == (I2C_RIF_TXTHRI_MSK));
}

/**
  * @brief  Get rx fifo full interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_rxf(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->RIF, I2C_RIF_RXFRI_MSK) == (I2C_RIF_RXFRI_MSK));
}

/**
  * @brief  Get rx fifo overflow interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_rxov(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->RIF, I2C_RIF_RXOVRI_MSK) == (I2C_RIF_RXOVRI_MSK));
}

/**
  * @brief  Get rx fifo underflow interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_rxud(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->RIF, I2C_RIF_RXUDRI_MSK) == (I2C_RIF_RXUDRI_MSK));
}

/**
  * @brief  Get rx fifo low than thread interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_rxth(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->RIF, I2C_RIF_RXTHRI_MSK) == (I2C_RIF_RXTHRI_MSK));
}

/**
  * @brief  Get transmit complete interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_tc(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->RIF, I2C_RIF_TCRI_MSK) == (I2C_RIF_TCRI_MSK));
}

/**
  * @brief  Get transmit and reload complete interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_tcr(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->RIF, I2C_RIF_TCRRI_MSK) == (I2C_RIF_TCRRI_MSK));
}


/**
  * @brief  Get addr matched interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_addr(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->RIF, I2C_RIF_ADDRRI_MSK) == (I2C_RIF_ADDRRI_MSK));
}

/**
  * @brief  Get nack interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_nack(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->RIF, I2C_RIF_NACKRI_MSK) == (I2C_RIF_NACKRI_MSK));
}

/**
  * @brief  Get stop interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_stop(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->RIF, I2C_RIF_STOPRI_MSK) == (I2C_RIF_STOPRI_MSK));
}

/**
  * @brief  Get bus error interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_berr(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->RIF, I2C_RIF_BERRRI_MSK) == (I2C_RIF_BERRRI_MSK));
}

/**
  * @brief  Get lost arbitration interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_arlo(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->RIF, I2C_RIF_ARLORI_MSK) == (I2C_RIF_ARLORI_MSK));
}

/**
  * @brief  Get pec error interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_pece(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->RIF, I2C_RIF_PECERI_MSK) == (I2C_RIF_PECERI_MSK));
}

/**
  * @brief  Get timeout interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_tout(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->RIF, I2C_RIF_TOUTRI_MSK) == (I2C_RIF_TOUTRI_MSK));
}

/**
  * @brief  Get SMBus alert interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_alert(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->RIF, I2C_RIF_ALERTRI_MSK) == (I2C_RIF_ALERTRI_MSK));
}
/**
  * @}
  */
/** @defgroup MD_I2C_Public_Functions_Group17 IFM
  * @{
  */
/**
  * @brief  Mask tx fifo empty interrupt.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_mask_it_txe(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IFM, I2C_IFM_TXEFM_MSK) == I2C_IFM_TXEFM_MSK);
}

/**
  * @brief  Mask TX fifo overflow interrupt.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_mask_it_txov(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IFM, I2C_IFM_TXOVFM_MSK) == I2C_IFM_TXOVFM_MSK);
}

/**
  * @brief  Mask TX fifo underflow interrupt.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_mask_it_txud(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IFM, I2C_IFM_TXUDFM_MSK) == I2C_IFM_TXUDFM_MSK);
}

/**
  * @brief  Mask TX fifo low than thread interrupt.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_mask_it_txth(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IFM, I2C_IFM_TXTHFM_MSK) == I2C_IFM_TXTHFM_MSK);
}

/**
  * @brief  Mask rx fifo full interrupt.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_mask_it_rxf(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IFM, I2C_IFM_RXFFM_MSK) == I2C_IFM_RXFFM_MSK);
}

/**
  * @brief  Mask rx fifo overflow interrupt.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_mask_it_rxov(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IFM, I2C_IFM_RXOVFM_MSK) == I2C_IFM_RXOVFM_MSK);
}

/**
  * @brief  Mask rx fifo underflow interrupt.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_mask_it_rxud(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IFM, I2C_IFM_RXUDFM_MSK) == I2C_IFM_RXUDFM_MSK);
}

/**
  * @brief  Mask rx fifo low than thread interrupt.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_mask_it_rxth(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IFM, I2C_IFM_RXTHFM_MSK) == I2C_IFM_RXTHFM_MSK);
}

/**
  * @brief  Mask transmit complete interrupt.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_mask_it_tc(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IFM, I2C_IFM_TCFM_MSK) == I2C_IFM_TCFM_MSK);
}

/**
  * @brief  Mask transmit and reload complete interrupt.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_mask_it_tcr(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IFM, I2C_IFM_TCRFM_MSK) == I2C_IFM_TCRFM_MSK);
}

/**
  * @brief  Mask addr matched interrupt.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_mask_it_addr(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IFM, I2C_IFM_ADDRFM_MSK) == I2C_IFM_ADDRFM_MSK);
}

/**
  * @brief  Mask nack interrupt.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_mask_it_nack(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IFM, I2C_IFM_NACKFM_MSK) == I2C_IFM_NACKFM_MSK);
}

/**
  * @brief  Mask stop interrupt.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_mask_it_stop(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IFM, I2C_IFM_STOPFM_MSK) == I2C_IFM_STOPFM_MSK);
}

/**
  * @brief  Mask bus error interrupt.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_mask_it_berr(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IFM, I2C_IFM_BERRFM_MSK) == I2C_IFM_BERRFM_MSK);
}

/**
  * @brief  Mask lost arbitration interrupt.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_mask_it_arlo(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IFM, I2C_IFM_ARLOFM_MSK) == I2C_IFM_ARLOFM_MSK);
}

/**
  * @brief  Mask pec error interrupt.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_mask_it_pece(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IFM, I2C_IFM_PECEFM_MSK) == I2C_IFM_PECEFM_MSK);
}

/**
  * @brief  Mask timeout interrupt.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_mask_it_tout(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IFM, I2C_IFM_TOUTFM_MSK) == I2C_IFM_TOUTFM_MSK);
}

/**
  * @brief  Mask SMBus alert interrupt.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_mask_it_alert(I2C_TypeDef *I2Cx)
{
	return (READ_BIT(I2Cx->IFM, I2C_IFM_ALERTFM_MSK) == I2C_IFM_ALERTFM_MSK);
}
/**
  * @}
  */
/** @defgroup MD_I2C_Public_Functions_Group18 ICR
  * @{
  */
/**
  * @brief  Clear tx fifo empty interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_i2c_clear_flag_txe(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->ICR, I2C_ICR_TXEIC_MSK);
}

/**
  * @brief  Clear TX fifo overflow interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_i2c_clear_flag_txov(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->ICR, I2C_ICR_TXOVIC_MSK);
}

/**
  * @brief  Clear TX fifo underflow interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_i2c_clear_flag_txud(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->ICR, I2C_ICR_TXUDIC_MSK);
}

/**
  * @brief  Clear TX fifo low than thread interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_i2c_clear_flag_txth(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->ICR, I2C_ICR_TXTHIC_MSK);
}

/**
  * @brief  Clear rx fifo full interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_i2c_clear_flag_rxf(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->ICR, I2C_ICR_RXFIC_MSK);
}

/**
  * @brief  Clear rx fifo overflow interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_i2c_clear_flag_rxov(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->ICR, I2C_ICR_RXOVIC_MSK);
}

/**
  * @brief  Clear rx fifo underflow interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_i2c_clear_flag_rxud(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->ICR, I2C_ICR_RXUDIC_MSK);
}

/**
  * @brief  Clear rx fifo low than thread interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_i2c_clear_flag_rxth(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->ICR, I2C_ICR_RXTHIC_MSK);
}

/**
  * @brief  Clear transmit complete interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_i2c_clear_flag_tc(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->ICR, I2C_ICR_TCIC_MSK);
}

/**
  * @brief  Clear transmit and reload complete interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_i2c_clear_flag_tcr(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->ICR, I2C_ICR_TCRIC_MSK);
}

/**
  * @brief  Clear addr matched interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_i2c_clear_flag_addr(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->ICR, I2C_ICR_ADDRIC_MSK);
}

/**
  * @brief  Clear nack interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_i2c_clear_flag_nack(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->ICR, I2C_ICR_NACKIC_MSK);
}

/**
  * @brief  Clear stop interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_i2c_clear_flag_stop(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->ICR, I2C_ICR_STOPIC_MSK);
}

/**
  * @brief  Clear bus error interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_i2c_clear_flag_berr(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->ICR, I2C_ICR_BERRIC_MSK);
}

/**
  * @brief  Clear lost arbitration interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_i2c_clear_flag_arlo(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->ICR, I2C_ICR_ARLOIC_MSK);
}

/**
  * @brief  Clear pec error interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_i2c_clear_flag_pece(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->ICR, I2C_ICR_PECEIC_MSK);
}

/**
  * @brief  Clear timeout interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_i2c_clear_flag_tout(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->ICR, I2C_ICR_TOUTIC_MSK);
}

/**
  * @brief  Clear SMBus alert interrupt flag.
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void md_i2c_clear_flag_alert(I2C_TypeDef *I2Cx)
{
	SET_BIT(I2Cx->ICR, I2C_ICR_ALERTIC_MSK);
}
/**
  * @}
  */
/** @defgroup MD_I2C_Public_Functions_Group1 Initialization
  * @{
  */
extern md_status_t md_i2c_init(I2C_TypeDef *I2Cx, md_i2c_init_t *init);
void md_i2c_struct_init(md_i2c_init_t *init);
/**
  * @}
  */
/**
  * @}
  */
/**
  * @}
  */
/**
  * @}
  */
#ifdef __cplusplus
}
#endif

#endif

/******************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
