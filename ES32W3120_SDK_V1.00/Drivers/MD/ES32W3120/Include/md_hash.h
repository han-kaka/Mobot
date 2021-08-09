/**********************************************************************************
 *
 * @file    md_hash.h
 * @brief   HASH MD driver header file.
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

#ifndef __MD_HASH_H__
#define __MD_HASH_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/** @addtogroup Micro_Driver
  * @{
  */
/** @addtogroup MD_HASH 
  * @{
  */
/* Includes -------------------------------------------------------------------*/
#include "md_utils.h"

/* Exported Variables -------------------------------------------------------- */

/* Exported Constants -------------------------------------------------------- */

/* Exported Types ------------------------------------------------------------ */

/* Public typedef -------------------------------------------------------------*/
/** @defgroup Public_Types Public Types
  * @{
  */
typedef struct
{
    uint32_t mode;   /*!< select hash or sha256 */
    uint32_t length; /*!< the length of message with byte */
    uint8_t datatyp; /*!< the type of input: no change, halfword change, byte change, bit change */
    uint8_t outtyp;  /*!< the type of output: big endian, little endian */
    uint8_t dmaen;
} hashctx_stt_t;

/**
  * @brief  The mode of hash
  */
typedef enum
{
    HASH_SM3    = 0,  /*!< select SM3 */
    HASH_SHA256 = 1,  /*!< select SHA256 */
} hash_type_mod_t;

/**
  * @brief  The mode of input
  */
typedef enum
{
    HASH_DATA_W  = 0,  /*!< no change */
    HASH_DATA_HW = 1,  /*!< halfword change */
    HASH_DATA_BY = 2,  /*!< byte change */
    HASH_DATA_BI = 3,  /*!< bite change */
} hash_type_data_t;

/**
  * @brief  The mode of input
  */
typedef enum
{
    HASH_DMA_DISABLE  = 0,  /*!< dma disable */
    HASH_DMA_ENABLE = 1,    /*!< dma enable */
} hash_dma_enable_t;

/**
  * @brief  The mode of input
  */
typedef enum
{
    HASH_OUT_L = 1,   /*!< little endian */
    HASH_OUT_B = 0,   /*!< big endian */
} hash_type_out_t;

typedef enum
{
    IRQ_DISABLE = 0,   /*!< interrupt disable */
    IRQ_ENABLE = 1,    /*!< interrupt enable */
} hash_interrupt_t;
/**
  * @}
  */
 
/* Public variables -----------------------------------------------------------*/

/* Exported Functions -------------------------------------------------------- */

/** @defgroup Public_Functions Public Functions
  * @{
  */
/** @defgroup Public_Functions_Group2 STATUS
  * @{
  */

/**
  * @brief  Input hash message
  * @param  data
  * @retval None
  */
__STATIC_INLINE void md_hash_input_message(uint32_t data)
{
    WRITE_REG(HASH->DIN, data);
}

/**
  * @brief  Enable HASH
  * @retval None
  */
__STATIC_INLINE void md_hash_enable_hash(void)
{
    SET_BIT(HASH->CTRL, HASH_CTRL_EN_MSK);
}

/**
  * @brief  Disable HASH
  * @retval None
  */
__STATIC_INLINE void md_hash_disable_hash(void)
{
    CLEAR_BIT(HASH->CTRL, HASH_CTRL_EN_MSK);
}

/**
  * @brief  Check if HASH is enabled
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_hash_is_enabled(void)
{
    return READ_BITS(HASH->CTRL, HASH_CTRL_EN_MSK, HASH_CTRL_EN_POS);
}

/**
  * @brief  Enable HASH interrupt
  * @retval None
  */
__STATIC_INLINE void md_hash_enable_it(void)
{
    SET_BIT(HASH->CTRL, HASH_CTRL_INTEN_MSK);
}

/**
  * @brief  Disable HASH interrupt
  * @retval None
  */
__STATIC_INLINE void md_hash_disable_it(void)
{
    CLEAR_BIT(HASH->CTRL, HASH_CTRL_INTEN_MSK);
}

/**
  * @brief  Check if HASH interrupt is enabled
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_hash_it_is_enabled(void)
{
    return READ_BITS(HASH->CTRL, HASH_CTRL_INTEN_MSK, HASH_CTRL_INTEN_POS);
}

/**
  * @brief  Enable HASH DMA
  * @retval None
  */
__STATIC_INLINE void md_hash_enable_dma(void)
{
    SET_BIT(HASH->CTRL, HASH_CTRL_DMAEN_MSK);
}

/**
  * @brief  Disable HASH DMA
  * @retval None
  */
__STATIC_INLINE void md_hash_disable_dma(void)
{
    CLEAR_BIT(HASH->CTRL, HASH_CTRL_DMAEN_MSK);
}

/**
  * @brief  Check if HASH DMA is enabled
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_hash_dma_is_enabled(void)
{
    return READ_BITS(HASH->CTRL, HASH_CTRL_DMAEN_MSK, HASH_CTRL_DMAEN_POS);
}

/**
  * @brief  Select HASH arithmetic type
  * @param  sel: HASH arithmetic type
  * @retval None
  */
__STATIC_INLINE void md_hash_sel_arithmetic(uint32_t sel)
{
    MODIFY_REG(HASH->CTRL, HASH_CTRL_ALGO_MSK, sel << HASH_CTRL_ALGO_POSS);
}

/**
  * @brief  Get HASH arithmetic type
  * @retval Status:
  *         - 00: SM3
  *         - 01: SHA256
  */
__STATIC_INLINE uint32_t md_hash_get_arithmetic(void)
{
    return READ_BITS(HASH->CTRL, HASH_CTRL_ALGO_MSK, HASH_CTRL_ALGO_POSS);
}

/**
  * @brief  Select HASH out type
  * @param  sel: HASH out type
  * @retval None
  */
__STATIC_INLINE void md_hash_sel_out_type(uint32_t sel)
{
    MODIFY_REG(HASH->CTRL, HASH_CTRL_OUTTYP_MSK, sel << HASH_CTRL_OUTTYP_POS);
}

/**
  * @brief  Get HASH HASH out type
  * @retval Status:
  *         - 0: Big-enndian
  *         - 1: Little-endian
  */
__STATIC_INLINE uint32_t md_hash_get_out_type(void)
{
    return READ_BITS(HASH->CTRL, HASH_CTRL_OUTTYP_MSK, HASH_CTRL_OUTTYP_POS);
}

/**
  * @brief  Select HASH data type
  * @param  sel: HASH out type
  * @retval None
  */
__STATIC_INLINE void md_hash_sel_data_type(uint32_t sel)
{
    MODIFY_REG(HASH->CTRL, HASH_CTRL_DATATYP_MSK, sel << HASH_CTRL_DATATYP_POSS);
}

/**
  * @brief  Get HASH HASH data type
  * @retval Status:
  *         - 00: 32bit, without exchange
  *         - 01: 16bit, half-word exchange
  *         - 10: 8bit, byte exchange
  *         - 11: 1bit, bit exchange
  */
__STATIC_INLINE uint32_t md_hash_get_outtype(void)
{
    return READ_BITS(HASH->CTRL, HASH_CTRL_DATATYP_MSK, HASH_CTRL_DATATYP_POSS);
}

/**
  * @brief  Enable HASH arithmetic trigger
  * @retval None
  */
__STATIC_INLINE void md_hash_enable_trig(void)
{
    SET_BIT(HASH->CTRL, HASH_CTRL_TRIG_MSK);
}

/**
  * @brief  Disable HASH arithmetic trigger
  * @retval None
  */
__STATIC_INLINE void md_hash_disable_trig(void)
{
    CLEAR_BIT(HASH->CTRL, HASH_CTRL_TRIG_MSK);
}

/**
  * @brief  Check if HASH trigger is enabled
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_hash_trig_is_enabled(void)
{
    return READ_BITS(HASH->CTRL, HASH_CTRL_TRIG_MSK, HASH_CTRL_TRIG_POS);
}

/**
  * @brief  Clear single HASH done flag
  * @retval None
  */
__STATIC_INLINE void md_hash_clr_flag_done(void)
{
    SET_BIT(HASH->STAT, HASH_STAT_RND_DONE_MSK);
}

/**
  * @brief  Get single HASH done flag
  * @retval Status:
  *         - 0: Undone
  *         - 1: Done
  */
__STATIC_INLINE uint32_t md_hash_get_flag_done(void)
{
    return READ_BITS(HASH->STAT, HASH_STAT_RND_DONE_MSK, HASH_STAT_RND_DONE_POS);
}

/**
  * @brief  Get HASH used fifo
  * @retval Number: used fifo amount
  */
__STATIC_INLINE uint32_t md_hash_get_used_fifo(void)
{
    return READ_BITS(HASH->STAT, HASH_STAT_USEDFIFO_MSK, HASH_STAT_USEDFIFO_POSS);
}

/**
  * @brief  Get HASH GRP_number
  * @retval Number: GRP number
  */
__STATIC_INLINE uint32_t md_hash_get_grpnum(void)
{
    return READ_BITS(HASH->STAT, HASH_STAT_GRPNUM_MSK, HASH_STAT_GRPNUM_POSS);
}

/**
  * @brief  Get HASH result0
  * @retval Value: HASH result
  */
__STATIC_INLINE uint32_t md_hash_get_result0(void)
{
    return READ_BITS(HASH->RES0, HASH_RES0_RES0_MSK, HASH_RES0_RES0_POSS);
}

/**
  * @brief  Get HASH result1
  * @retval Value: HASH result
  */
__STATIC_INLINE uint32_t md_hash_get_result1(void)
{
    return READ_BITS(HASH->RES1, HASH_RES1_RES1_MSK, HASH_RES1_RES1_POSS);
}

/**
  * @brief  Get HASH result2
  * @retval Value: HASH result
  */
__STATIC_INLINE uint32_t md_hash_get_result2(void)
{
    return READ_BITS(HASH->RES2, HASH_RES2_RES2_MSK, HASH_RES2_RES2_POSS);
}

/**
  * @brief  Get HASH result3
  * @retval Value: HASH result
  */
__STATIC_INLINE uint32_t md_hash_get_result3(void)
{
    return READ_BITS(HASH->RES3, HASH_RES3_RES3_MSK, HASH_RES3_RES3_POSS);
}

/**
  * @brief  Get HASH result4
  * @retval Value: HASH result
  */
__STATIC_INLINE uint32_t md_hash_get_result4(void)
{
    return READ_BITS(HASH->RES4, HASH_RES4_RES4_MSK, HASH_RES4_RES4_POSS);
}

/**
  * @brief  Get HASH result5
  * @retval Value: HASH result
  */
__STATIC_INLINE uint32_t md_hash_get_result5(void)
{
    return READ_BITS(HASH->RES5, HASH_RES5_RES5_MSK, HASH_RES5_RES5_POSS);
}

/**
  * @brief  Get HASH result6
  * @retval Value: HASH result
  */
__STATIC_INLINE uint32_t md_hash_get_result6(void)
{
    return READ_BITS(HASH->RES6, HASH_RES6_RES6_MSK, HASH_RES6_RES6_POSS);
}

/**
  * @brief  Get HASH result7
  * @retval Value: HASH result
  */
__STATIC_INLINE uint32_t md_hash_get_result7(void)
{
    return READ_BITS(HASH->RES7, HASH_RES7_RES7_MSK, HASH_RES7_RES7_POSS);
}

/* Public variables -----------------------------------------------------------*/


/* Public functions prototypes ------------------------------------------------*/

md_status_t hash_init(hashctx_stt_t *hashctx);
md_status_t hash_append(hashctx_stt_t *hashctx, const uint8_t *inputbuffer);
md_status_t hash_finish(uint8_t *outputbuffer, uint8_t otyp);

/* HASH function prototypes */

void HASH_Output(uint32_t *Output);
/**
  * @}
  */
/**
  * @}
  */
/* Exported Macros ----------------------------------------------------------- */
/** @defgroup Public_Macros Public Macros
  * @{
  */
#define HASHFINISH   *(uint32_t *)0x20000F00
#define DMA_FINISH   *(uint32_t *)0x20000F04
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
#endif /* __cplusplus */

#endif /* __MD_HASH_H__ */

/******************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
