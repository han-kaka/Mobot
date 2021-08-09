/**********************************************************************************
 *
 * @file    md_crypt.h
 * @brief   Header file of CRYPT module driver.
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


#ifndef __MD_CRYPT_H__
#define __MD_CRYPT_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------ */

#include "md_utils.h"

/* Exported Types ------------------------------------------------------------ */

/* Exported Macros ----------------------------------------------------------- */

#define PLAIN_LEN 60
#define AADATA_LEN 20
#define GHASH_LEN ((AADATA_LEN%16)?(AADATA_LEN/16+1)*16:AADATA_LEN)+((PLAIN_LEN % 16)? (PLAIN_LEN/16+1)*16:PLAIN_LEN)+16

/** @addtogroup Micro_Driver
  * @{
  */
/** @defgroup MD_CRYPT CRYPT
  * @brief CRYPT micro driver
  * @{
  */
/**
  * @defgroup MD_CRYPT_Public_Types Public Types
  * @{
  */
/**
  * @brief CRYPT keys of tdes
  */
typedef enum
{
    MD_CRYPT_TDES_KEY_2 = 0x0U, /**< 2 key for des */
    MD_CRYPT_TDES_KEY_3 = 0x800U,   /**< 3 key for des */
} md_crypt_tdes_key_t;

/**
  * @brief FIFO order of CRYPT
  */
typedef enum
{
    MD_CRYPT_FIFO_ORDER_0 = 0x0U,       /**< Byte0 is first */
    MD_CRYPT_FIFO_ORDER_3 = 0x2000U,    /**< Byte3 is first */
} md_crypt_fifo_order_t;

/**
  * @brief CRYPT data type
  */
typedef enum
{
    MD_CRYPT_TYPE_32 = 0x0U,    /**< 32-bits */
    MD_CRYPT_TYPE_16 = 0x100U,  /**< 16-bits */
    MD_CRYPT_TYPE_8  = 0x200U,  /**< 8-bits */
    MD_CRYPT_TYPE_1  = 0x300U,  /**< 1-bits */
} md_crypt_type_t;

/**
  * @brief select the mode of CRYPT
  */
typedef enum
{
    MD_CRYPT_MODE_ECB = 0x0U,   /**< Mode ECB */
    MD_CRYPT_MODE_CBC = 0x10U,  /**< Mode CBC */
    MD_CRYPT_MODE_CTR = 0x20U,  /**< Mode CTR */
    MD_CRYPT_MODE_GCM = 0x30U,  /**< Mode GCM */
} md_crypt_mode_t;

/**
  * @brief Standard of CRYPT
  */
typedef enum
{
    MD_CRYPT_STANDARD_AES = 0x0U,   /**< AES */
    MD_CRYPT_STANDARD_DES = 0x1U,   /**< DES */
} md_crypt_std_t;

/**
  * @brief CRYPT direction choose
  */
typedef enum
{
    MD_CRYPT_SEL_DECRYPT = 0x0U,    /**< Decrypt */
    MD_CRYPT_SEL_ENCRYPT = 0x2U,    /**< Encrypt */
} md_crypt_sel_t;

/** @brief crypt fifo type definition
  */
typedef enum
{
    FIFO_DATA0 = 0,  /*!< DATA0/RES0 first */
    FIFO_DATA3 = 1,  /*!< DATA3/RES3 first */
} cryp_fifo_type_t;

/** @brief crypt encrypt definition
  */
typedef enum
{
    CRYPT_ENCRYPT = 1,  /* crypt encrypt */
    CRYPT_DECRYPT = 0,  /* decrypt */
} cryp_encrypt_decrypt_t;

/** @brief crypt mode definition
  */
typedef enum
{
    CRYPT_ECB = 0,  /*!< ecb */
    CRYPT_CBC = 1,  /*!< cbc */
    CRYPT_CTR = 2,  /*!< ctr */
    CRYPT_GCM = 3,  /*!< gcm */
} cryp_ecb_cbc_ctr_t;

/** @brief crypt dma enable definition
  */
typedef enum
{
    DMA_DISABLE = 0, /*!< dma disable */
    DMA_WRITE = 1,   /*!< dma crypt write */
    DMA_READ = 2,    /*!< dma crypt read */
} cryp_dma_en_t;


/** @brief crypt key size definition
  */
typedef enum
{
    CRYPT_KEY64 = 8,    /*!< DES 64 bit */
    CRYPT_KEY128 = 16,  /*!< AES/SM4/TDES 128 bit */
    CRYPT_KEY192 = 24,  /*!< AES/TDES 192 bit */
    CRYPT_KEY256 = 32,  /*!< AES 256 bit */
} cryp_keymode_t;

/** @brief crypt select definition
  */
typedef enum
{
    CRYPT_AES = 0,   /*!< AES */
    CRYPT_DES = 2,   /*!< DES */
    CRYPT_SM4 = 1,   /*!< SM4 */
} cryp_algorithm_t;


/**
  * @brief CRYPT init structure definition
  */
typedef struct
{
    md_crypt_std_t standard;    /**< Standard select */
    md_crypt_mode_t mode;       /**< CRYPT mode */
    md_crypt_type_t type;       /**< Data type select */
    md_crypt_fifo_order_t order;    /**< FIFO orders */
    md_crypt_sel_t encs;        /**< Encrypt or Decrypt*/
} md_crypt_init_t;

/** @ingroup AES context structure
  */
typedef struct
{
    uint8_t    fifoen;          /*!< FIFO enable. */
    uint8_t    ftype;           /*!< DATA0/RES0 first or DATA3/RES3 first. */
    uint8_t    dmaen;           /*!< DMA enable. */
    uint8_t    encry_decry;     /*!< encrypt or decrypt. */
    uint8_t    algori;          /*!< AES/DES/TDES/SM4. */
    uint8_t    mode;            /*!< ecb/cbc/ctr/gcm. */
    int32_t    ivsize;          /*!< Size of the Initialization Vector in bytes. */
    uint32_t   iv[4];           /*!< Temporary result/IV. */
    uint32_t   keysize;         /*!< Key length in bit: 128/192/256. */
    uint32_t   key[8];          /*!< AES key. */
} cryptctx_stt_t;

/** @ingroup Structure used only for AES-GCM.
  */
typedef struct
{
    uint8_t    fifoen;          /*!< FIFO enable*/
    uint8_t    ftype;           /*!< DATA0/RES0 first or DATA3/RES3 first */
    uint8_t    dmaen;           /*!< DMA enable */
    uint8_t    encry_decry;     /*!< encrypt or decrypt */
    uint8_t    mode;            /*!< ecb/cbc/ctr/gcm */
    int32_t    ivsize;          /*!< Size of the Initialization Vector in bytes. This must be set by the caller prior to calling Init */
    uint32_t   iv[4];           /*!< This is the current IV value.*/
    int32_t    keysize;         /*!< AES Key length in bytes. This must be set by the caller prior to calling Init */
    uint32_t   key[8];          /*!< AES key */
    uint8_t    tag[16];         /*!< Pointer to Authentication TAG. This value must be set in decryption, and this TAG will be verified */
    int32_t    aadsize;         /*!< Additional authenticated data size. For internal use. */
} aesgcmctx_stt_t;

/** @brief ECB structure
  */
typedef struct
{
    uint8_t input[16]; /*!< input data of AES in ECB mode*/
    uint8_t output[16];/*!< output data of AES in ECB mode*/
} cryp_gcm_ecb_t;

/** @brief GHASG structure
  */
typedef struct
{
    uint8_t input[GHASH_LEN]; /*!< input data of HASH */
    uint8_t output[16];       /*!< output data of HASH */
} cryp_gcm_hash_t;
/**
  * @}
  */

/* Public variables -----------------------------------------------------------*/
/** @defgroup Public_Macors Public Macors
  * @{
  */
#define AES_FINISH         *(uint32_t *)0x20001F00    /** wait aes finish */
#define MULTH_FINISH       *(uint32_t *)0x20001F04    /** wait aes gcm finish */
#define SM4_FINISH         *(uint32_t *)0x20001F08    /** wait aes finish */
#define DES_FINISH         *(uint32_t *)0x20001F0C    /** wait aes finish */
#define DMA_FINISH         *(uint32_t *)0x20002000    /** wait dma finish */
#define AESBUSY_TIMEOUT    0x00010000                 /** check aes is or not overtime */
/**
  * @}
  */
/* Exported Variables -------------------------------------------------------- */

/* Exported Constants -------------------------------------------------------- */

/* Exported Functions -------------------------------------------------------- */

/** @defgroup MD_CRYPT_Public_Functions Public Functions
  * @{
  */
/** @defgroup MD_CRYPT_Public_Functions_Group2 DATA
  * @{
  */
/**
  * @brief  set DATA0
  * @param  CRYPTx: CRYPT Peripheral
  * @param  data: This parameter can be 0~0xFFFFFFFF
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_data0(CRYPT_TypeDef *CRYPTx, uint32_t data)
{
    WRITE_REG(CRYPTx->DATA0, data);
}

/**
  * @brief  Get DATA0
  * @param  CRYPTx: CRYPT Peripheral
  * @retval data0
  */
__STATIC_INLINE uint32_t md_crypt_get_data0(CRYPT_TypeDef *CRYPTx)
{
    return READ_REG(CRYPTx->DATA0);
}

/**
  * @brief  set DATA1
  * @param  CRYPTx: CRYPT Peripheral
  * @param  data: This parameter can be 0~0xFFFFFFFF
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_data1(CRYPT_TypeDef *CRYPTx, uint32_t data)
{
    WRITE_REG(CRYPTx->DATA1, data);
}

/**
  * @brief  Get DATA1
  * @param  CRYPTx: CRYPT Peripheral
  * @retval data1
  */
__STATIC_INLINE uint32_t md_crypt_get_data1(CRYPT_TypeDef *CRYPTx)
{
    return READ_REG(CRYPTx->DATA1);
}

/**
  * @brief  set DATA2
  * @param  CRYPTx: CRYPT Peripheral
  * @param  data: This parameter can be 0~0xFFFFFFFF
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_data2(CRYPT_TypeDef *CRYPTx, uint32_t data)
{
    WRITE_REG(CRYPTx->DATA2, data);
}

/**
  * @brief  Get DATA2
  * @param  CRYPTx: CRYPT Peripheral
  * @retval data2
  */
__STATIC_INLINE uint32_t md_crypt_get_data2(CRYPT_TypeDef *CRYPTx)
{
    return READ_REG(CRYPTx->DATA2);
}

/**
  * @brief  set DATA3
  * @param  CRYPTx: CRYPT Peripheral
  * @param  data: This parameter can be 0~0xFFFFFFFF
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_data3(CRYPT_TypeDef *CRYPTx, uint32_t data)
{
    WRITE_REG(CRYPTx->DATA3, data);
}

/**
  * @brief  Get DATA3
  * @param  CRYPTx: CRYPT Peripheral
  * @retval data3
  */
__STATIC_INLINE uint32_t md_crypt_get_data3(CRYPT_TypeDef *CRYPTx)
{
    return READ_REG(CRYPTx->DATA3);
}
/**
  * @}
  */
/** @defgroup MD_CRYPT_Public_Functions_Group3 KEY
  * @{
  */
/**
  * @brief  set KEY0
  * @param  CRYPTx: CRYPT Peripheral
  * @param  key: This parameter can be 0~0xFFFFFFFF
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_key0(CRYPT_TypeDef *CRYPTx, uint32_t key)
{
    WRITE_REG(CRYPTx->KEY0, key);
}

/**
  * @brief  Get KEY0
  * @param  CRYPTx: CRYPT Peripheral
  * @retval key0
  */
__STATIC_INLINE uint32_t md_crypt_get_key0(CRYPT_TypeDef *CRYPTx)
{
    return READ_REG(CRYPTx->KEY0);
}

/**
  * @brief  set KEY1
  * @param  CRYPTx: CRYPT Peripheral
  * @param  key: This parameter can be 0~0xFFFFFFFF
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_key1(CRYPT_TypeDef *CRYPTx, uint32_t key)
{
    WRITE_REG(CRYPTx->KEY1, key);
}

/**
  * @brief  Get KEY1
  * @param  CRYPTx: CRYPT Peripheral
  * @retval key1
  */
__STATIC_INLINE uint32_t md_crypt_get_key1(CRYPT_TypeDef *CRYPTx)
{
    return READ_REG(CRYPTx->KEY1);
}

/**
  * @brief  set KEY2
  * @param  CRYPTx: CRYPT Peripheral
  * @param  key: This parameter can be 0~0xFFFFFFFF
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_key2(CRYPT_TypeDef *CRYPTx, uint32_t key)
{
    WRITE_REG(CRYPTx->KEY2, key);
}

/**
  * @brief  Get KEY2
  * @param  CRYPTx: CRYPT Peripheral
  * @retval key2
  */
__STATIC_INLINE uint32_t md_crypt_get_key2(CRYPT_TypeDef *CRYPTx)
{
    return READ_REG(CRYPTx->KEY2);
}

/**
  * @brief  set KEY3
  * @param  CRYPTx: CRYPT Peripheral
  * @param  key: This parameter can be 0~0xFFFFFFFF
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_key3(CRYPT_TypeDef *CRYPTx, uint32_t key)
{
    WRITE_REG(CRYPTx->KEY3, key);
}

/**
  * @brief  Get KEY3
  * @param  CRYPTx: CRYPT Peripheral
  * @retval key3
  */
__STATIC_INLINE uint32_t md_crypt_get_key3(CRYPT_TypeDef *CRYPTx)
{
    return READ_REG(CRYPTx->KEY3);
}

/**
  * @brief  set KEY4
  * @param  CRYPTx: CRYPT Peripheral
  * @param  key: This parameter can be 0~0xFFFFFFFF
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_key4(CRYPT_TypeDef *CRYPTx, uint32_t key)
{
    WRITE_REG(CRYPTx->KEY4, key);
}

/**
  * @brief  Get KEY4
  * @param  CRYPTx: CRYPT Peripheral
  * @retval key4
  */
__STATIC_INLINE uint32_t md_crypt_get_key4(CRYPT_TypeDef *CRYPTx)
{
    return READ_REG(CRYPTx->KEY4);
}

/**
  * @brief  set KEY5
  * @param  CRYPTx: CRYPT Peripheral
  * @param  key: This parameter can be 0~0xFFFFFFFF
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_key5(CRYPT_TypeDef *CRYPTx, uint32_t key)
{
    WRITE_REG(CRYPTx->KEY5, key);
}

/**
  * @brief  Get KEY5
  * @param  CRYPTx: CRYPT Peripheral
  * @retval key5
  */
__STATIC_INLINE uint32_t md_crypt_get_key5(CRYPT_TypeDef *CRYPTx)
{
    return READ_REG(CRYPTx->KEY5);
}

/**
  * @brief  set KEY6
  * @param  CRYPTx: CRYPT Peripheral
  * @param  key: This parameter can be 0~0xFFFFFFFF
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_key6(CRYPT_TypeDef *CRYPTx, uint32_t key)
{
    WRITE_REG(CRYPTx->KEY6, key);
}

/**
  * @brief  Get KEY6
  * @param  CRYPTx: CRYPT Peripheral
  * @retval key6
  */
__STATIC_INLINE uint32_t md_crypt_get_key6(CRYPT_TypeDef *CRYPTx)
{
    return READ_REG(CRYPTx->KEY6);
}

/**
  * @brief  set KEY7
  * @param  CRYPTx: CRYPT Peripheral
  * @param  key: This parameter can be 0~0xFFFFFFFF
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_key7(CRYPT_TypeDef *CRYPTx, uint32_t key)
{
    WRITE_REG(CRYPTx->KEY7, key);
}

/**
  * @brief  Get KEY7
  * @param  CRYPTx: CRYPT Peripheral
  * @retval key7
  */
__STATIC_INLINE uint32_t md_crypt_get_key7(CRYPT_TypeDef *CRYPTx)
{
    return READ_REG(CRYPTx->KEY7);
}
/**
  * @}
  */
/** @defgroup MD_CRYPT_Public_Functions_Group4 IV
  * @{
  */
/**
  * @brief  set IV0
  * @param  CRYPTx: CRYPT Peripheral
  * @param  iv: This parameter can be 0~0xFFFFFFFF
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_iv0(CRYPT_TypeDef *CRYPTx, uint32_t iv)
{
    WRITE_REG(CRYPTx->IV0, iv);
}

/**
  * @brief  Get IV0
  * @param  CRYPTx: CRYPT Peripheral
  * @retval iv0
  */
__STATIC_INLINE uint32_t md_crypt_get_iv0(CRYPT_TypeDef *CRYPTx)
{
    return READ_REG(CRYPTx->IV0);
}

/**
  * @brief  set IV1
  * @param  CRYPTx: CRYPT Peripheral
  * @param  iv: This parameter can be 0~0xFFFFFFFF
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_iv1(CRYPT_TypeDef *CRYPTx, uint32_t iv)
{
    WRITE_REG(CRYPTx->IV1, iv);
}

/**
  * @brief  Get IV1
  * @param  CRYPTx: CRYPT Peripheral
  * @retval iv1
  */
__STATIC_INLINE uint32_t md_crypt_get_iv1(CRYPT_TypeDef *CRYPTx)
{
    return READ_REG(CRYPTx->IV1);
}

/**
  * @brief  set IV2
  * @param  CRYPTx: CRYPT Peripheral
  * @param  iv: This parameter can be 0~0xFFFFFFFF
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_iv2(CRYPT_TypeDef *CRYPTx, uint32_t iv)
{
    WRITE_REG(CRYPTx->IV2, iv);
}

/**
  * @brief  Get IV2
  * @param  CRYPTx: CRYPT Peripheral
  * @retval iv2
  */
__STATIC_INLINE uint32_t md_crypt_get_iv2(CRYPT_TypeDef *CRYPTx)
{
    return READ_REG(CRYPTx->IV2);
}

/**
  * @brief  set IV3
  * @param  CRYPTx: CRYPT Peripheral
  * @param  iv: This parameter can be 0~0xFFFFFFFF
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_iv3(CRYPT_TypeDef *CRYPTx, uint32_t iv)
{
    WRITE_REG(CRYPTx->IV3, iv);
}

/**
  * @brief  Get IV3
  * @param  CRYPTx: CRYPT Peripheral
  * @retval iv3
  */
__STATIC_INLINE uint32_t md_crypt_get_iv3(CRYPT_TypeDef *CRYPTx)
{
    return READ_REG(CRYPTx->IV3);
}
/**
  * @}
  */
/** @defgroup MD_CRYPT_Public_Functions_Group5 RES
  * @{
  */
/**
  * @brief  Get RESULT0
  * @param  CRYPTx: CRYPT Peripheral
  * @retval Result0
  */
__STATIC_INLINE uint32_t md_crypt_get_result0(CRYPT_TypeDef *CRYPTx)
{
    return READ_REG(CRYPTx->RES0);
}

/**
  * @brief  Get RESULT1
  * @param  CRYPTx: CRYPT Peripheral
  * @retval Result1
  */
__STATIC_INLINE uint32_t md_crypt_get_result1(CRYPT_TypeDef *CRYPTx)
{
    return READ_REG(CRYPTx->RES1);
}

/**
  * @brief  Get RESULT2
  * @param  CRYPTx: CRYPT Peripheral
  * @retval Result2
  */
__STATIC_INLINE uint32_t md_crypt_get_result2(CRYPT_TypeDef *CRYPTx)
{
    return READ_REG(CRYPTx->RES2);
}

/**
  * @brief  Get RESULT3
  * @param  CRYPTx: CRYPT Peripheral
  * @retval Result3
  */
__STATIC_INLINE uint32_t md_crypt_get_result3(CRYPT_TypeDef *CRYPTx)
{
    return READ_REG(CRYPTx->RES3);
}
/**
  * @}
  */
/** @defgroup MD_CRYPT_Public_Functions_Group6 CON
  * @{
  */
/**
  * @brief  start CRYPT
  * @param  CRYPTx: CRYPT Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_go(CRYPT_TypeDef *CRYPTx)
{
    SET_BIT(CRYPTx->CON, CRYPT_CON_GO_MSK);
}

/**
  * @brief  select the action of CRYPT
  * @param  CRYPTx: CRYPT Peripheral
  * @param  encs This parameter can be one of the following values:
  *         @arg @ref MD_CRYPT_SEL_ENCRYPT
  *         @arg @ref MD_CRYPT_SEL_DECRYPT
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_encs(CRYPT_TypeDef *CRYPTx, uint32_t encs)
{
    MODIFY_REG(CRYPTx->CON, CRYPT_CON_ENCS_MSK, encs);
}

/**
  * @brief  Retrieve the checksum byte order of CRYPT
  * @param  CRYPTx: CRYPT Peripheral
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_CRYPT_SEL_ENCRYPT
  *         @arg @ref MD_CRYPT_SEL_DECRYPT
  */
__STATIC_INLINE uint32_t md_crypt_get_encs(CRYPT_TypeDef *CRYPTx)
{
    return (READ_BIT(CRYPTx->CON, CRYPT_CON_ENCS_MSK));
}

/**
  * @brief  set the mode of CRYPT
  * @param  CRYPTx: CRYPT Peripheral
  * @param  mode: This parameter can be one of the following values:
  *         @arg @ref MD_CRYPT_MODE_ECB
  *         @arg @ref MD_CRYPT_MODE_CBC
  *         @arg @ref MD_CRYPT_MODE_CTR
  *         @arg @ref MD_CRYPT_MODE_GCM
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_mode(CRYPT_TypeDef *CRYPTx, uint32_t mode)
{
    MODIFY_REG(CRYPTx->CON, CRYPT_CON_MODE_MSK, mode);
}

/**
  * @brief  Retrieve the key bits of CRYPT
  * @param  CRYPTx: CRYPT Peripheral
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_CRYPT_MODE_ECB
  *         @arg @ref MD_CRYPT_MODE_CBC
  *         @arg @ref MD_CRYPT_MODE_CTR
  *         @arg @ref MD_CRYPT_MODE_GCM
  */
__STATIC_INLINE uint32_t md_crypt_get_mode(CRYPT_TypeDef *CRYPTx)
{
    return (READ_BIT(CRYPTx->CON, CRYPT_CON_MODE_MSK));
}

/**
  * @brief  CRYPT IV Enable
  * @param  CRYPTx: CRYPT Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_enable_iv(CRYPT_TypeDef *CRYPTx)
{
    SET_BIT(CRYPTx->CON, CRYPT_CON_IVEN_MSK);
}

/**
  * @brief  CRYPT IV Disable
  * @param  CRYPTx: CRYPT Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_disable_iv(CRYPT_TypeDef *CRYPTx)
{
    CLEAR_BIT(CRYPTx->CON, CRYPT_CON_IVEN_MSK);
}

/**
  * @brief  Indicate if CRYPT IV is enabled
  * @param  CRYPTx: CRYPT Peripheral
  * @retval State.
  */
__STATIC_INLINE uint32_t md_crypt_is_enabled_iv(CRYPT_TypeDef *CRYPTx)
{
    return (READ_BIT(CRYPTx->CON, CRYPT_CON_IVEN_MSK) == (CRYPT_CON_IVEN_MSK));
}

/**
  * @brief  CRYPT interrupt Enable
  * @param  CRYPTx: CRYPT Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_enable_interrupt(CRYPT_TypeDef *CRYPTx)
{
    SET_BIT(CRYPTx->CON, CRYPT_CON_IE_MSK);
}

/**
  * @brief  CRYPT interrupt Disable
  * @param  CRYPTx: CRYPT Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_disable_interrupt(CRYPT_TypeDef *CRYPTx)
{
    CLEAR_BIT(CRYPTx->CON, CRYPT_CON_IE_MSK);
}

/**
  * @brief  Indicate if CRYPT interrupt is enabled
  * @param  CRYPTx: CRYPT Peripheral
  * @retval State.
  */
__STATIC_INLINE uint32_t md_crypt_is_enabled_interrupt(CRYPT_TypeDef *CRYPTx)
{
    return (READ_BIT(CRYPTx->CON, CRYPT_CON_IE_MSK) == (CRYPT_CON_IE_MSK));
}

/**
  * @brief  set the data type of CRYPT
  * @param  CRYPTx: CRYPT Peripheral
  * @param  data_type: This parameter can be one of the following values:
  *         @arg @ref MD_CRYPT_TYPE_32
  *         @arg @ref MD_CRYPT_TYPE_16
  *         @arg @ref MD_CRYPT_TYPE_8
  *         @arg @ref MD_CRYPT_TYPE_1
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_data_type(CRYPT_TypeDef *CRYPTx, uint32_t data_type)
{
    MODIFY_REG(CRYPTx->CON, CRYPT_CON_TYPE_MSK, data_type);
}

/**
  * @brief  Retrieve the key bits of CRYPT
  * @param  CRYPTx: CRYPT Peripheral
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_CRYPT_TYPE_32
  *         @arg @ref MD_CRYPT_TYPE_16
  *         @arg @ref MD_CRYPT_TYPE_8
  *         @arg @ref MD_CRYPT_TYPE_1
  */
__STATIC_INLINE uint32_t md_crypt_get_data_type(CRYPT_TypeDef *CRYPTx)
{
    return (READ_BIT(CRYPTx->CON, CRYPT_CON_TYPE_MSK));
}

/**
  * @brief  CRYPT TDES function Enable
  * @param  CRYPTx: CRYPT Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_enable_tdes(CRYPT_TypeDef *CRYPTx)
{
    SET_BIT(CRYPTx->CON, CRYPT_CON_TDES_MSK);
}

/**
  * @brief  CRYPT TDES function Disable
  * @param  CRYPTx: CRYPT Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_disable_tdes(CRYPT_TypeDef *CRYPTx)
{
    CLEAR_BIT(CRYPTx->CON, CRYPT_CON_TDES_MSK);
}

/**
  * @brief  Indicate if CRYPT TDES function is enabled
  * @param  CRYPTx: CRYPT Peripheral
  * @retval State.
  */
__STATIC_INLINE uint32_t md_crypt_is_enabled_teds(CRYPT_TypeDef *CRYPTx)
{
    return (READ_BIT(CRYPTx->CON, CRYPT_CON_TDES_MSK) == (CRYPT_CON_TDES_MSK));
}

/**
  * @brief  select the TDES key's number of CRYPT
  * @param  CRYPTx: CRYPT Peripheral
  * @param  tdes_keys This parameter can be one of the following values:
  *         @arg @ref MD_CRYPT_TDES_KEY_2
  *         @arg @ref MD_CRYPT_TDES_KEY_3
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_tdes_keys(CRYPT_TypeDef *CRYPTx, uint32_t tdes_keys)
{
    MODIFY_REG(CRYPTx->CON, CRYPT_CON_DESKS_MSK, tdes_keys);
}

/**
  * @brief  Retrieve the TDES key's number of CRYPT
  * @param  CRYPTx: CRYPT Peripheral
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_CRYPT_TDES_KEY_2
  *         @arg @ref MD_CRYPT_TDES_KEY_3
  */
__STATIC_INLINE uint32_t md_crypt_get_tdes_keys(CRYPT_TypeDef *CRYPTx)
{
    return (READ_BIT(CRYPTx->CON, CRYPT_CON_DESKS_MSK));
}

/**
  * @brief  CRYPT FIFO Enable
  * @param  CRYPTx: CRYPT Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_enable_fifo(CRYPT_TypeDef *CRYPTx)
{
    SET_BIT(CRYPTx->CON, CRYPT_CON_FIFOEN_MSK);
}

/**
  * @brief  CRYPT FIFO Disable
  * @param  CRYPTx: CRYPT Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_disable_fifo(CRYPT_TypeDef *CRYPTx)
{
    CLEAR_BIT(CRYPTx->CON, CRYPT_CON_FIFOEN_MSK);
}

/**
  * @brief  Indicate if CRYPT FIFO is enabled
  * @param  CRYPTx: CRYPT Peripheral
  * @retval State.
  */
__STATIC_INLINE uint32_t md_crypt_is_enabled_fifo(CRYPT_TypeDef *CRYPTx)
{
    return (READ_BIT(CRYPTx->CON, CRYPT_CON_FIFOEN_MSK) == (CRYPT_CON_FIFOEN_MSK));
}

/**
  * @brief  select the FIFO order of CRYPT
  * @param  CRYPTx: CRYPT Peripheral
  * @param  fifo_order This parameter can be one of the following values:
  *         @arg @ref MD_CRYPT_FIFO_ORDER_0
  *         @arg @ref MD_CRYPT_FIFO_ORDER_3
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_fifo_order(CRYPT_TypeDef *CRYPTx, uint32_t fifo_order)
{
    MODIFY_REG(CRYPTx->CON, CRYPT_CON_FIFOODR_MSK, fifo_order);
}

/**
  * @brief  Retrieve the FIFO order of CRYPT
  * @param  CRYPTx: CRYPT Peripheral
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_CRYPT_FIFO_ORDER_0
  *         @arg @ref MD_CRYPT_FIFO_ORDER_3
  */
__STATIC_INLINE uint32_t md_crypt_get_fifo_order(CRYPT_TypeDef *CRYPTx)
{
    return (READ_BIT(CRYPTx->CON, CRYPT_CON_FIFOODR_MSK));
}

/**
  * @brief  CRYPT DMA Enable request
  * @param  CRYPTx: CRYPT Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_enable_dma_req(CRYPT_TypeDef *CRYPTx)
{
    SET_BIT(CRYPTx->CON, CRYPT_CON_DMAEN_MSK);
}

/**
  * @brief  CRYPT DMA Disable request
  * @param  CRYPTx: CRYPT Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_disable_dma_req(CRYPT_TypeDef *CRYPTx)
{
    CLEAR_BIT(CRYPTx->CON, CRYPT_CON_DMAEN_MSK);
}

/**
  * @brief  Indicate if CRYPT DMA request is enabled
  * @param  CRYPTx: CRYPT Peripheral
  * @retval State.
  */
__STATIC_INLINE uint32_t md_crypt_is_enabled_dma_req(CRYPT_TypeDef *CRYPTx)
{
    return (READ_BIT(CRYPTx->CON, CRYPT_CON_DMAEN_MSK) == (CRYPT_CON_DMAEN_MSK));
}

/**
  * @brief  clear result of CRYPT
  * @param  CRYPTx: CRYPT Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_clear_result(CRYPT_TypeDef *CRYPTx)
{
    SET_BIT(CRYPTx->CON, CRYPT_CON_RESCLR_MSK);
}

/**
  * @brief  Enable SM4 soft reset
  * @param  CRYPTx: CRYPT Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_enable_sm4_soft_reset(CRYPT_TypeDef *CRYPTx)
{
    SET_BIT(CRYPTx->CON, CRYPT_CON_SM4SOFTRST_MSK);
}

/**
  * @brief  Disable SM4 soft reset
  * @param  CRYPTx: CRYPT Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_disable_sm4_soft_reset(CRYPT_TypeDef *CRYPTx)
{
    CLEAR_BIT(CRYPTx->CON, CRYPT_CON_SM4SOFTRST_MSK);
}

/**
  * @brief  Enable SM4 write data
  * @param  CRYPTx: CRYPT Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_enable_sm4_write(CRYPT_TypeDef *CRYPTx)
{
    SET_BIT(CRYPTx->CON, CRYPT_CON_SM4INVALID_MSK);
}

/**
  * @brief  Disable SM4 write data
  * @param  CRYPTx: CRYPT Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_disable_sm4_write(CRYPT_TypeDef *CRYPTx)
{
    CLEAR_BIT(CRYPTx->CON, CRYPT_CON_SM4INVALID_MSK);
}

/**
  * @brief  select the standard of CRYPT
  * @param  CRYPTx: CRYPT Peripheral
  * @param  standard_sel This parameter can be one of the following values:
  *         @arg @ref MD_CRYPT_STANDARD_AES
  *         @arg @ref MD_CRYPT_STANDARD_DES
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_standard(CRYPT_TypeDef *CRYPTx, uint32_t standard_sel)
{
    MODIFY_REG(CRYPTx->CON, CRYPT_CON_CRYSEL_MSK, standard_sel);
}

/**
  * @brief  Retrieve the standard of CRYPT
  * @param  CRYPTx: CRYPT Peripheral
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_CRYPT_STANDARD_AES
  *         @arg @ref MD_CRYPT_STANDARD_DES
  */
__STATIC_INLINE uint32_t md_crypt_get_standard(CRYPT_TypeDef *CRYPTx)
{
    return (READ_BIT(CRYPTx->CON, CRYPT_CON_CRYSEL_MSK));
}
/**
  * @}
  */
/** @defgroup MD_CRYPT_Public_Functions_Group7 IF
  * @{
  */
/**
  * @brief  Get the AES interrupt flag
  * @param  CRYPTx: CRYPT Peripheral
  * @retval Status.
  */
__STATIC_INLINE uint32_t md_crypt_get_flag_aes(CRYPT_TypeDef *CRYPTx)
{
    return (READ_BIT(CRYPTx->IF, CRYPT_IF_AESIF_MSK) == CRYPT_IF_AESIF_MSK);
}

/**
  * @brief  Get the DES interrupt flag
  * @param  CRYPTx: CRYPT Peripheral
  * @retval Status.
  */
__STATIC_INLINE uint32_t md_crypt_get_flag_des(CRYPT_TypeDef *CRYPTx)
{
    return (READ_BIT(CRYPTx->IF, CRYPT_IF_DESIF_MSK) == CRYPT_IF_DESIF_MSK);
}

/**
  * @brief  Get the MULTH interrupt flag
  * @param  CRYPTx: CRYPT Peripheral
  * @retval Status.
  */
__STATIC_INLINE uint32_t md_crypt_get_flag_multh(CRYPT_TypeDef *CRYPTx)
{
    return (READ_BIT(CRYPTx->IF, CRYPT_IF_MULTHIF_MSK) == CRYPT_IF_MULTHIF_MSK);
}

/**
  * @brief  Get SM4 interrupt flag
  * @param  CRYPTx: CRYPT Peripheral
  * @retval Status.
  */
__STATIC_INLINE uint32_t md_crypt_get_flag_sm4_done(CRYPT_TypeDef *CRYPTx)
{
    return (READ_BIT(CRYPTx->IF, CRYPT_IF_SM4IF_MSK) == CRYPT_IF_SM4IF_MSK);
}

/**
  * @brief  Get the DONE flag
  * @param  CRYPTx: CRYPT Peripheral
  * @retval Status.
  */
__STATIC_INLINE uint32_t md_crypt_get_flag_done(CRYPT_TypeDef *CRYPTx)
{
    return (READ_BIT(CRYPTx->IF, CRYPT_IF_DONE_MSK) == CRYPT_IF_DONE_MSK);
}

/**
  * @}
  */
/** @defgroup MD_CRYPT_Public_Functions_Group8 IFC
  * @{
  */
/**
  * @brief  Clear the AES interrupt flag
  * @param  CRYPTx: CRYPT Peripheral
  */
__STATIC_INLINE void md_crypt_clear_flag_aes(CRYPT_TypeDef *CRYPTx)
{
    WRITE_REG(CRYPTx->IFC, CRYPT_IFC_AESIFC_MSK);
}

/**
  * @brief  Clear the DES interrupt flag
  * @param  CRYPTx: CRYPT Peripheral
  */
__STATIC_INLINE void md_crypt_clear_flag_des(CRYPT_TypeDef *CRYPTx)
{
    WRITE_REG(CRYPTx->IFC, CRYPT_IFC_DESIFC_MSK);
}

/**
  * @brief  Clear the MULTH interrupt flag
  * @param  CRYPTx: CRYPT Peripheral
  */
__STATIC_INLINE void md_crypt_clear_flag_multh(CRYPT_TypeDef *CRYPTx)
{
    WRITE_REG(CRYPTx->IFC, CRYPT_IFC_MULTHIFC_MSK);
}

/**
  * @brief  Clear the SM4 interrupt flag
  * @param  CRYPTx: CRYPT Peripheral
  */
__STATIC_INLINE void md_crypt_clear_flag_sm4(CRYPT_TypeDef *CRYPTx)
{
    WRITE_REG(CRYPTx->IFC, CRYPT_IFC_SM4IFC_MSK);
}

/**
  * @}
  */
/** @defgroup MD_CRYPT_Public_Functions_Group9 FIFO
  * @{
  */
/**
  * @brief  set FIFO data of CRYPT
  * @param  CRYPTx: CRYPT Peripheral
  * @param  fifo_data: This parameter can be 0~0xFFFFFFFF
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_fifo_data(CRYPT_TypeDef *CRYPTx, uint32_t fifo_data)
{
    WRITE_REG(CRYPTx->FIFO, fifo_data);
}

/**
  * @brief  Get the FIFO data of CRYPT
  * @param  CRYPTx: CRYPT Peripheral
  * @retval FIFO data
  */
__STATIC_INLINE uint32_t md_crypt_get_fifo_data(CRYPT_TypeDef *CRYPTx)
{
    return READ_REG(CRYPTx->FIFO);
}
/**
  * @}
  */
/** @defgroup MD_CRYPT_Public_Functions_Group1 Initialization
  * @{
  */

void md_crypt_reset(void);
void md_crypt_init(md_crypt_init_t *init);
void md_crypt_init_struct(md_crypt_init_t *init);
void cryp_keyin(uint32_t    *cryp_keyin, uint32_t ksize);
void cryp_datain(uint32_t *crypt_input, uint8_t algorithm);
md_status_t crypt_enable(cryptctx_stt_t *cryptctx);
void cryp_dataout(uint32_t *crypt_output, uint8_t algorithm);
void cryp_fifoout(uint32_t *crypt_output, uint8_t algorithm);
void cryp_fifoin(uint32_t *crypt_input, uint8_t algorithm);
void cryp_ivin(uint32_t *crypt_iv, uint8_t algorithm);
void cryp_iv_enable(uint32_t n);

/* AES ECB function prototypes */
md_status_t aes_ecb_init(cryptctx_stt_t *aesecbctx, const uint8_t *key);
md_status_t aes_ecb_append(cryptctx_stt_t *aesecbctx,
                           const uint8_t *inputmessage, uint32_t ilength,
                           uint8_t *outputmessage);

/* AES CBC function prototypes */
md_status_t aes_cbc_init(cryptctx_stt_t *aescbcctx, const uint8_t *key,
                         const uint8_t *initvectors);
md_status_t aes_cbc_append(cryptctx_stt_t *aescbcctx,
                           const uint8_t *inputmessage, uint32_t ilength,
                           uint8_t *outputmessage);

/* AES CTR function prototypes */
md_status_t aes_ctr_init(cryptctx_stt_t *aesecbctx, const uint8_t *key,
                         const uint8_t *initvectors);
md_status_t aes_ctr_append(cryptctx_stt_t *aesecbctx,
                           const uint8_t *inputmessage, uint32_t ilength,
                           uint8_t *outputmessage);

/* AES GCM function prototypes */
md_status_t aes_gcm_tag(aesgcmctx_stt_t *aesgcmctx, uint8_t *input,
                        uint32_t ilength, const uint8_t *aadata, uint8_t *authtag);
md_status_t aes_gcm_init(aesgcmctx_stt_t *aesgcmctx, const uint8_t *key,
                         const uint8_t *initvectors);
md_status_t aes_gcm_append(aesgcmctx_stt_t *aesgcmctx,
                           const uint8_t *inputmessage, uint32_t ilength,
                           uint8_t *outputmessage);
/* SM4 ECB function prototypes */
md_status_t sm4_ecb_init(cryptctx_stt_t *sm4ecbctx, const uint8_t *key);
md_status_t sm4_ecb_append(cryptctx_stt_t *sm4ecbctx,
                           const uint8_t *inputmessage, uint32_t ilength,
                           uint8_t *outputmessage);
/* SM4 CBC function prototypes */
md_status_t sm4_cbc_init(cryptctx_stt_t *sm4cbcctx, const uint8_t *p_pkey,
                         const uint8_t *initvectors);
md_status_t sm4_cbc_append(cryptctx_stt_t *sm4cbcctx,
                           const uint8_t *inputmessage, uint32_t ilength,
                           uint8_t *outputmessage);
/* DES ECB function prototypes */
md_status_t des_ecb_init(cryptctx_stt_t *desecbctx, const uint8_t *key);
md_status_t des_ecb_append(cryptctx_stt_t *desecbctx,
                           const uint8_t *inputmessage, uint32_t ilength,
                           uint8_t *outputmessage);
/* DES CBC function prototypes */
md_status_t des_cbc_init(cryptctx_stt_t *descbcctx, const uint8_t *p_pkey,
                         const uint8_t *initvectors);
md_status_t des_cbc_append(cryptctx_stt_t *descbcctx,
                           const uint8_t *inputmessage, uint32_t ilength,
                           uint8_t *outputmessage);

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
#endif /* __cplusplus */
#endif /* __MD_CRYPT_H__ */

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
