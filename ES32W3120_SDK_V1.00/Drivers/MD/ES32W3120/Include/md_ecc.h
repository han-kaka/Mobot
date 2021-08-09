/**********************************************************************************
 *
 * @file    md_ecc.h
 * @brief   ECC MD driver header file.
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

#ifndef __MD_ECC_H__
#define __MD_ECC_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes -------------------------------------------------------------------*/
#include "es32w3120.h"
#include "md_trng.h"
/** @addtogroup Micro_Driver
  * @{
  */
/** @addtogroup MD_ECC
  * @{
  */
/* Exported Variables -------------------------------------------------------- */

/* Exported Constants -------------------------------------------------------- */

/* Exported Macros ----------------------------------------------------------- */
/** @defgroup Public_Macros Public Macros
  * @{
  */
#define OCTEST256      32
/**
  * @}
  */
/* Exported Types ------------------------------------------------------------ */
/** @defgroup Public_Types Public Types
  * @{
  */
/**
  *@brief ECC return parameter structure
  */
typedef enum
{
    ECC_ERR_BAD_PARAMETER = 2,
    ECC_ERR_HWSTA = 3,
    ECC_WARN_POINT_AT_INFINITY = 4,
    ECC_POINT_INVALID = 5,
    ECC_ERR_KDF_LEN = 6,
    RNG_ERR_UNINIT_STATE = 7,
} errorstatus_t;

/**
  *@brief ECC parameter structure
  */
typedef struct
{
    uint8_t   pma[OCTEST256];       /*!< Pointer to parameter "a" */
    uint8_t   pmb[OCTEST256];       /*!< Pointer to parameter "b" */
    uint8_t   pmp[OCTEST256];       /*!< Pointer to parameter "p" */
    uint8_t   pmn[OCTEST256];       /*!< Pointer to parameter "n" */
    uint8_t   pmgx[OCTEST256];      /*!< Pointer to x coordinate of generator point */
    uint8_t   pmgy[OCTEST256];      /*!< Pointer to y coordinate of generator point */
    uint8_t   pmpk[OCTEST256];      /*!< Pointer to private key */
    void      *pminternalec;        /*!< Pointer to internal structure for handling the parameters */
} ecc_type_t;

/**
  *@brief ECC point structure
  */
typedef struct
{
    uint32_t pmx[OCTEST256 / 4]; /**< BigNum_Type integer for pmX coordinate */
    uint32_t pmy[OCTEST256 / 4]; /**< BigNum_Type integer for pmY coordinate */
} ecc_point_type_t;

/**
  *@brief ECC private Key structure
  */
typedef struct
{
    uint32_t pmd[OCTEST256 / 4]; /**< BigNum Representing the Private Key */
} ecc_privkey_type_t;

/**
  *@brief ECC data union
  */
typedef union
{
    uint8_t byte_type[OCTEST256];
    uint32_t word_type[OCTEST256 / 4];
} ecc_data_type_t;

/**
  *@brief ECC signature structure
  */
typedef struct
{
    uint32_t r[OCTEST256 / 4];  /*!< pointer to paramter R*/
    uint32_t s[OCTEST256 / 4];  /*!< pointer to paramter S*/
} ecdsasignature_type_t;
/**
  * @brief  Structure used in ECDSA signature generation function
  */
typedef struct
{

    ecc_privkey_type_t *privkey;  /*!<  Pointer to the ECC Private Key used in the verification */

    ecc_type_t         *ecc_para;       /*!<  Pointer to Elliptic Curve parameters */

    rngstate_type_t    *rngstate;    /*!<  Pointer to an Initialized Random Engine Status */

} ecdsasignctx_type_t;

/**
  * @brief  Enumeration for the values inside the ECDSA signature
  */
typedef enum
{
    E_ECDSA_SIGNATURE_R_VALUE = 0,  /*!<  Value R  */
    E_ECDSA_SIGNATURE_S_VALUE = 1,  /*!<  Value S */
} ecdsasignvalues_type_t;
/**
  * @brief  Structure used in ECDSA signature verification function
  */
typedef struct
{
    ecc_point_type_t    *ecc_point;  /*!<  Pointer to the ECC Public Key used in the verification */
    ecc_type_t         *ecc_para;    /*!<  Pointer to Elliptic Curve parameters */
} ecdsaverifyctx_type_t;
/**
  * @brief   Enumeration for the coordinates of an elliptic curve point
  */
typedef enum ECcoordinate_e
{
    E_ECC_POINT_COORDINATE_X = 0,  /*!< Coordinate X */

    E_ECC_POINT_COORDINATE_Y = 1,   /*!< Coordinate Y */

    E_ECC_POINT_COORDINATE_Z = 2,   /*!< Coordinate Z */
} eccoordinate_type_t;

/**
  * @brief  The mode of ECC arithmetic
  */
typedef enum
{
    ECC_PARAMETER_H  = 0,  /* parameter H */
    ECC_MONT_MOD_MUL = 1,  /* mont modular multiplication */
    ECC_MONT_MOD_ADD = 2,  /* mont modular addition */
    ECC_MONT_MOD_SUB = 3,  /* mont modular subtraction */
    ECC_MONT_MOD_INV = 4,  /* mont modular inversion */
    ECC_MONT_DOM_OUT = 5,  /* mont modular domain transfer out */
    ECC_MONT_DOM_INT = 6,  /* mont modular domain transfer into */
    ECC_MONT_PNT_MUL = 7,  /* ECC point-multiplication */
} ecc_arithmetic_mode_t;
/**
  * @}
  */
/* Public variables -----------------------------------------------------------*/
/** @defgroup Public_variables Public variables
  * @{
  */
#define TOTAL_FINISH    *(uint32_t *)0x20000F00
/**
  * @}
  */
/* Exported Functions -------------------------------------------------------- */

/* Public functions -----------------------------------------------------------*/
/** @defgroup MD_ECC_Public_Functions Public Functions
  * @{
  */
/**
  * @brief  Enable ECC interrupt
  * @param  None
  * @retval None
  */
__STATIC_INLINE void md_ecc_enable_it(void)
{
    SET_BIT(ECC->CON, ECC_CON_INTEN_MSK);
}

/**
  * @brief  Disable ECC interrupt
  * @param  None
  * @retval None
  */
__STATIC_INLINE void md_ecc_disable_it(void)
{
    CLEAR_BIT(ECC->CON, ECC_CON_INTEN_MSK);
}

/**
  * @brief  Check if ECC interrupt enable
  * @param  None
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_ecc_it_is_enable(void)
{
    return READ_BITS(ECC->CON, ECC_CON_INTEN_MSK, ECC_CON_INTEN_POS);
}

/**
  * @brief  Select ECC arithmetic mode
  * @param  sel: ECC arithmetic mode
  * @retval None
  */
__STATIC_INLINE void md_ecc_sel_arithmetic(uint32_t sel)
{
    MODIFY_REG(ECC->CON, ECC_CON_MODE_MSK, sel << ECC_CON_MODE_POSS);
}

/**
  * @brief  Get ECC arithmetic mode
  * @retval mode:
  *         - 000: Parameter H
  *         - 001: Mont modular multiplication
  *         - 010: Mont modular addition
  *         - 011: Mont modular subtraction
  *         - 100: Mont modular inversion
  *         - 101: Mont domain transfer out
  *         - 110: Mont domain transfer into
  *         - 111: ECC point-multiplication
  */
__STATIC_INLINE uint32_t md_ecc_get_arithmetic(void)
{
    return READ_BITS(ECC->CON, ECC_CON_MODE_MSK, ECC_CON_MODE_POSS);
}

/**
  * @brief  Set address of ECC result in ARAM
  * @param  addr: address
  * @retval None
  */
__STATIC_INLINE void md_ecc_set_result_aram_addr(uint32_t addr)
{
    MODIFY_REG(ECC->CON, ECC_CON_RES_MSK, addr << ECC_CON_RES_POSS);
}

/**
  * @brief  Get address of ECC result in ARAM
  * @retval address
  */
__STATIC_INLINE uint32_t md_ecc_get_result_aram_addr(void)
{
    return READ_BITS(ECC->CON, ECC_CON_RES_MSK, ECC_CON_RES_POSS);
}

/**
  * @brief  Set address of ECC operand R in ARAM
  * @param  addr: address
  * @retval None
  */
__STATIC_INLINE void md_ecc_set_opr_aram_addr(uint32_t addr)
{
    MODIFY_REG(ECC->CON, ECC_CON_OPR_MSK, addr << ECC_CON_OPR_POSS);
}

/**
  * @brief  Get address of ECC operand R in ARAM
  * @retval address
  */
__STATIC_INLINE uint32_t md_ecc_get_opr_aram_addr(void)
{
    return READ_BITS(ECC->CON, ECC_CON_OPR_MSK, ECC_CON_OPR_POSS);
}

/**
  * @brief  Set address of ECC operand L in ARAM
  * @param  addr: address
  * @retval None
  */
__STATIC_INLINE void md_ecc_set_opl_aram_addr(uint32_t addr)
{
    MODIFY_REG(ECC->CON, ECC_CON_OPL_MSK, addr << ECC_CON_OPL_POSS);
}

/**
  * @brief  Get address of ECC operand L in ARAM
  * @retval address
  */
__STATIC_INLINE uint32_t md_ecc_get_opl_aram_addr(void)
{
    return READ_BITS(ECC->CON, ECC_CON_OPL_MSK, ECC_CON_OPL_POSS);
}

/**
  * @brief  Enable ECC ARAM data remap
  * @param  None
  * @retval None
  */
__STATIC_INLINE void md_ecc_enable_remap(void)
{
    SET_BIT(ECC->CON, ECC_CON_REMAP_MSK);
}

/**
  * @brief  Disable ECC ARAM data remap
  * @param  None
  * @retval None
  */
__STATIC_INLINE void md_ecc_disable_remap(void)
{
    CLEAR_BIT(ECC->CON, ECC_CON_REMAP_MSK);
}

/**
  * @brief  Check if ECC ARAM data remap enable
  * @param  None
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE(T1<->T4,T2<->T5)
  */
__STATIC_INLINE uint32_t md_ecc_remap_is_enable(void)
{
    return READ_BITS(ECC->CON, ECC_CON_REMAP_MSK, ECC_CON_REMAP_POS);
}

/**
  * @brief  Enable ECC combination arithmetic
  * @retval None
  */
__STATIC_INLINE void md_ecc_enable_comb(void)
{
    SET_BIT(ECC->CON, ECC_CON_COMB_MSK);
}

/**
  * @brief  Disable ECC combination arithmetic
  * @param  None
  * @retval None
  */
__STATIC_INLINE void md_ecc_disable_comb(void)
{
    CLEAR_BIT(ECC->CON, ECC_CON_COMB_MSK);
}

/**
  * @brief  Enable ECC single arithmetic run
  * @param  None
  * @retval None
  */
__STATIC_INLINE void md_ecc_enable_single_run(void)
{
    SET_BIT(ECC->CON, ECC_CON_RUN_MSK);
}

/**
  * @brief  Disable ECC single arithmetic run
  * @param  None
  * @retval None
  */
__STATIC_INLINE void md_ecc_disable_single_run(void)
{
    CLEAR_BIT(ECC->CON, ECC_CON_RUN_MSK);
}

/**
  * @brief  Check if ECC single arithmetic run enable
  * @param  None
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_ecc_single_run_is_enable(void)
{
    return READ_BITS(ECC->CON, ECC_CON_RUN_MSK, ECC_CON_RUN_POS);
}

/**
  * @brief  Get flag if arithmetic is running
  * @param  None
  * @retval Status:
  *         - 0: Free
  *         - 1: Running
  */
__STATIC_INLINE uint32_t md_ecc_get_flag_arithmetic_run(void)
{
    return READ_BITS(ECC->STA, ECC_STA_WK_MSK, ECC_STA_WK_POS);
}

/**
  * @brief  Get flag if arithmetic is done
  * @param  None
  * @retval Status:
  *         - 0: Undone
  *         - 1: Done
  */
__STATIC_INLINE uint32_t md_ecc_get_flag_arithmetic_done(void)
{
    return READ_BITS(ECC->STA, ECC_STA_DONE_MSK, ECC_STA_DONE_POS);
}

/**
  * @brief  Clear flag if arithmetic is done
  * @param  None
  * @retval None
  */
__STATIC_INLINE void md_ecc_clr_flag_arithmetic_done(void)
{
    WRITE_REG(ECC->STA, ECC_STA_DONE_MSK);
}

/**
  * @brief  Get flag if arithmetic error occurs
  * @param  None
  * @retval Status:
  *         - 0: None error occurs
  *         - 1: Error occurs
  */
__STATIC_INLINE uint32_t md_ecc_get_flag_arithmetic_error(void)
{
    return READ_BITS(ECC->STA, ECC_STA_ERR_MSK, ECC_STA_ERR_POS);
}

/**
  * @brief  Clear flag if arithmetic error occurs
  * @param  None
  * @retval None
  */
__STATIC_INLINE void md_ecc_clr_flag_arithmetic_error(void)
{
    WRITE_REG(ECC->STA, ECC_STA_ERR_MSK);
}

/**
  * @brief  Get flag if ECC arithmetic is over
  * @param  None
  * @retval Status:
  *         - 0: Not over
  *         - 1: Over
  */
__STATIC_INLINE uint32_t md_ecc_get_flag_ecc_arithmetic_over(void)
{
    return READ_BITS(ECC->STA, ECC_STA_ECC_OVER_MSK, ECC_STA_ECC_OVER_POS);
}

/**
  * @brief  Clear flag if ECC arithmetic is over
  * @param  None
  * @retval None
  */
__STATIC_INLINE void md_ecc_clr_flag_ecc_arithmetic_over(void)
{
    WRITE_REG(ECC->STA, ECC_STA_ECC_OVER_MSK);
}

/**
  * @brief  Get flag if arithmetic parameter is zero
  * @param  None
  * @retval Status:
  *         - 0: False
  *         - 1: True
  */
__STATIC_INLINE uint32_t md_ecc_get_flag_arithmetic_parameter_zero(void)
{
    return READ_BITS(ECC->STA, ECC_STA_MI_ZERO_MSK, ECC_STA_MI_ZERO_POS);
}

/**
  * @brief  Clear flag if arithmetic parameter is zero
  * @param  None
  * @retval None
  */
__STATIC_INLINE void md_ecc_clr_flag_ecc_arithmetic_parameter_zero(void)
{
    WRITE_REG(ECC->STA, ECC_STA_MI_ZERO_MSK);
}

/**
  * @brief  Set ECC modular multiplication parameter
  * @param  value: ECC modular multiplication parameter
  * @retval None
  */
__STATIC_INLINE void md_ecc_set_mod_mul_para(uint32_t value)
{
    WRITE_REG(ECC->PARA, value);
}

/**
  * @brief  Get ECC modular multiplication parameter
  * @retval ECC modular multiplication parameter
  */
__STATIC_INLINE uint32_t md_ecc_get_mod_mul_para(void)
{
    return (READ_REG(ECC->PARA));
}

/**
  * @brief  Set ECC point-multiplication scalar0
  * @param  value: ECC point-multiplication scalar0
  * @retval None
  */
__STATIC_INLINE void md_ecc_set_pnt_mul_scalar0(uint32_t value)
{
    WRITE_REG(ECC->SCALAR0, value);
}

/**
  * @brief  Get ECC point-multiplication scalar0
  * @retval ECC point-multiplication scalar0
  */
__STATIC_INLINE uint32_t md_ecc_get_pnt_mul_scalar0(void)
{
    return (READ_REG(ECC->SCALAR0));
}

/**
  * @brief  Set ECC point-multiplication scalar1
  * @param  value: ECC point-multiplication scalar1
  * @retval None
  */
__STATIC_INLINE void md_ecc_set_pnt_mul_scalar1(uint32_t value)
{
    WRITE_REG(ECC->SCALAR1, value);
}

/**
  * @brief  Get ECC point-multiplication scalar1
  * @retval ECC point-multiplication scalar1
  */
__STATIC_INLINE uint32_t md_ecc_get_pnt_mul_scalar1(void)
{
    return (READ_REG(ECC->SCALAR1));
}

/**
  * @brief  Set ECC point-multiplication scalar2
  * @param  value: ECC point-multiplication scalar2
  * @retval None
  */
__STATIC_INLINE void md_ecc_set_pnt_mul_scalar2(uint32_t value)
{
    WRITE_REG(ECC->SCALAR2, value);
}

/**
  * @brief  Get ECC point-multiplication scalar2
  * @retval ECC point-multiplication scalar2
  */
__STATIC_INLINE uint32_t md_ecc_get_pnt_mul_scalar2(void)
{
    return (READ_REG(ECC->SCALAR2));
}

/**
  * @brief  Set ECC point-multiplication scalar3
  * @param  value: ECC point-multiplication scalar3
  * @retval None
  */
__STATIC_INLINE void md_ecc_set_pnt_mul_scalar3(uint32_t value)
{
    WRITE_REG(ECC->SCALAR3, value);
}

/**
  * @brief  Get ECC point-multiplication scalar3
  * @retval ECC point-multiplication scalar3
  */
__STATIC_INLINE uint32_t md_ecc_get_pnt_mul_scalar3(void)
{
    return (READ_REG(ECC->SCALAR3));
}

/**
  * @brief  Set ECC point-multiplication scalar4
  * @param  value: ECC point-multiplication scalar4
  * @retval None
  */
__STATIC_INLINE void md_ecc_set_pnt_mul_scalar4(uint32_t value)
{
    WRITE_REG(ECC->SCALAR4, value);
}

/**
  * @brief  Get ECC point-multiplication scalar4
  * @retval ECC point-multiplication scalar4
  */
__STATIC_INLINE uint32_t md_ecc_get_pnt_mul_scalar4(void)
{
    return (READ_REG(ECC->SCALAR4));
}

/**
  * @brief  Set ECC point-multiplication scalar5
  * @param  value: ECC point-multiplication scalar5
  * @retval None
  */
__STATIC_INLINE void md_ecc_set_pnt_mul_scalar5(uint32_t value)
{
    WRITE_REG(ECC->SCALAR5, value);
}

/**
  * @brief  Get ECC point-multiplication scalar5
  * @retval ECC point-multiplication scalar5
  */
__STATIC_INLINE uint32_t md_ecc_get_pnt_mul_scalar5(void)
{
    return (READ_REG(ECC->SCALAR5));
}

/**
  * @brief  Set ECC point-multiplication scalar6
  * @param  value: ECC point-multiplication scalar6
  * @retval None
  */
__STATIC_INLINE void md_ecc_set_pnt_mul_scalar6(uint32_t value)
{
    WRITE_REG(ECC->SCALAR6, value);
}

/**
  * @brief  Get ECC point-multiplication scalar6
  * @retval ECC point-multiplication scalar6
  */
__STATIC_INLINE uint32_t md_ecc_get_pnt_mul_scalar6(void)
{
    return (READ_REG(ECC->SCALAR6));
}

/**
  * @brief  Set ECC point-multiplication scalar7
  * @param  value: ECC point-multiplication scalar7
  * @retval None
  */
__STATIC_INLINE void md_ecc_set_pnt_mul_scalar7(uint32_t value)
{
    WRITE_REG(ECC->SCALAR7, value);
}

/**
  * @brief  Get ECC point-multiplication scalar7
  * @retval ECC point-multiplication scalar7
  */
__STATIC_INLINE uint32_t md_ecc_get_pnt_mul_scalar7(void)
{
    return (READ_REG(ECC->SCALAR7));
}

/**
  * @brief  Set ECC Y coordinate0
  * @param  value: ECC Y coordinate0
  * @retval None
  */
__STATIC_INLINE void md_ecc_set_y_coordinate0(uint32_t value)
{
    WRITE_REG(ECC->YCO0, value);
}

/**
  * @brief  Get ECC Y coordinate0
  * @retval ECC Y coordinate0
  */
__STATIC_INLINE uint32_t md_ecc_get_y_coordinate0(void)
{
    return (READ_REG(ECC->YCO0));
}

/**
  * @brief  Set ECC Y coordinate1
  * @param  value: ECC Y coordinate1
  * @retval None
  */
__STATIC_INLINE void md_ecc_set_y_coordinate1(uint32_t value)
{
    WRITE_REG(ECC->YCO1, value);
}

/**
  * @brief  Get ECC Y coordinate1
  * @retval ECC Y coordinate1
  */
__STATIC_INLINE uint32_t md_ecc_get_y_coordinate1(void)
{
    return (READ_REG(ECC->YCO1));
}

/**
  * @brief  Set ECC Y coordinate2
  * @param  value: ECC Y coordinate2
  * @retval None
  */
__STATIC_INLINE void md_ecc_set_y_coordinate2(uint32_t value)
{
    WRITE_REG(ECC->YCO2, value);
}

/**
  * @brief  Get ECC Y coordinate2
  * @retval ECC Y coordinate2
  */
__STATIC_INLINE uint32_t md_ecc_get_y_coordinate2(void)
{
    return (READ_REG(ECC->YCO2));
}

/**
  * @brief  Set ECC Y coordinate3
  * @param  value: ECC Y coordinate3
  * @retval None
  */
__STATIC_INLINE void md_ecc_set_y_coordinate3(uint32_t value)
{
    WRITE_REG(ECC->YCO3, value);
}

/**
  * @brief  Get ECC Y coordinate3
  * @retval ECC Y coordinate3
  */
__STATIC_INLINE uint32_t md_ecc_get_y_coordinate3(void)
{
    return (READ_REG(ECC->YCO3));
}

/**
  * @brief  Set ECC Y coordinate4
  * @param  value: ECC Y coordinate4
  * @retval None
  */
__STATIC_INLINE void md_ecc_set_y_coordinate4(uint32_t value)
{
    WRITE_REG(ECC->YCO4, value);
}

/**
  * @brief  Get ECC Y coordinate4
  * @retval ECC Y coordinate4
  */
__STATIC_INLINE uint32_t md_ecc_get_y_coordinate4(void)
{
    return (READ_REG(ECC->YCO4));
}

/**
  * @brief  Set ECC Y coordinate5
  * @param  value: ECC Y coordinate5
  * @retval None
  */
__STATIC_INLINE void md_ecc_set_y_coordinate5(uint32_t value)
{
    WRITE_REG(ECC->YCO5, value);
}

/**
  * @brief  Get ECC Y coordinate5
  * @retval ECC Y coordinate5
  */
__STATIC_INLINE uint32_t md_ecc_get_y_coordinate5(void)
{
    return (READ_REG(ECC->YCO5));
}

/**
  * @brief  Set ECC Y coordinate6
  * @param  value: ECC Y coordinate6
  * @retval None
  */
__STATIC_INLINE void md_ecc_set_y_coordinate6(uint32_t value)
{
    WRITE_REG(ECC->YCO6, value);
}

/**
  * @brief  Get ECC Y coordinate6
  * @retval ECC Y coordinate6
  */
__STATIC_INLINE uint32_t md_ecc_get_y_coordinate6(void)
{
    return (READ_REG(ECC->YCO6));
}

/**
  * @brief  Set ECC Y coordinate7
  * @param  value: ECC Y coordinate7
  * @retval None
  */
__STATIC_INLINE void md_ecc_set_y_coordinate7(uint32_t value)
{
    WRITE_REG(ECC->YCO7, value);
}

/**
  * @brief  Get ECC Y coordinate7
  * @retval ECC Y coordinate7
  */
__STATIC_INLINE uint32_t md_ecc_get_y_coordinate7(void)
{
    return (READ_REG(ECC->YCO7));
}

/* Public functions prototypes ------------------------------------------------*/
uint32_t eccinitec(ecc_type_t *ecc_para);
uint32_t eccsetpointcoordinate(ecc_point_type_t *ecc_point, eccoordinate_type_t coordinate,
                               const uint8_t *coordinatevalue, uint32_t p_coordinatesize);
uint32_t eccgetpointcoordinate(const ecc_point_type_t *ecc_point, eccoordinate_type_t coordinate,
                               uint8_t *coordinatevalue, uint32_t *coordinatesize);
uint32_t ecckeygen(ecc_privkey_type_t *ecc_privkey, ecc_point_type_t *ecc_respoint,
                   rngstate_type_t *rngstate, const ecc_type_t *ecc_para);
uint32_t eccscalarmul(const ecc_point_type_t *ecc_point, const ecc_privkey_type_t *ecc_privkey,
                      ecc_point_type_t *ecc_respoint, const ecc_type_t *ecc_para);
uint32_t eccvalidatepubkey(ecc_point_type_t *ecc_point, const ecc_type_t *ecc_para);
uint32_t eccsetprivkeyvalue(ecc_privkey_type_t *ecc_privkey, const uint8_t *privatekey,
                            uint32_t privatekeysize);
uint32_t eccgetprivkeyvalue(const ecc_privkey_type_t *ecc_privkey, uint8_t *privatekey,
                            uint32_t *p_pprivatekeysize);
uint32_t ecckeyderive(const uint32_t *sharekey, const uint32_t sharekeylen,
                      const uint8_t *otherinfo, const uint32_t otherinfolen,
                      uint8_t *derivekey, const uint32_t keydatalen);
uint32_t ecdsasign(const uint8_t *ecdsa_mdigest, uint32_t ecdsa_mdigestsize,
                   ecdsasignature_type_t *ecdsa_signature,
                   const ecdsasignctx_type_t *ecdsa_signctx);
uint32_t ecc_r_s(const uint32_t *datax, const uint32_t *datak,
                 const uint8_t *dataz, const uint32_t *privekey,
                 const ecc_type_t *ecc_para, ecdsasignature_type_t *ecdsa_signature);
uint32_t ecdsagetsignature(ecdsasignature_type_t *ecdsa_signature,
                           ecdsasignvalues_type_t p_rors, uint8_t *svalue,
                           uint32_t *valuesize) ;
uint32_t ecdsasetsignature(ecdsasignature_type_t *ecdsa_signature,
                           ecdsasignvalues_type_t p_rors, const uint8_t *svalue,
                           uint32_t *valuesize);
uint32_t ecdsaverify(const uint8_t *ecdsa_mdigest, uint32_t ecdsa_mdigestsize,
                     const ecdsasignature_type_t *ecdsa_signature,
                     const ecdsaverifyctx_type_t *ecdsa_verifyctx);
uint32_t ecc_r_s_check(const uint8_t *dataz, const ecdsasignature_type_t *ecdsa_signature,
                       const ecdsaverifyctx_type_t *ecdsa_verifyctx);
uint32_t ecdsafreesign(ecdsasignature_type_t *ecdsa_signature);
uint32_t eccfreeprivkey(ecc_privkey_type_t *ecc_privkey);
uint32_t eccfreepoint(ecc_point_type_t *ecc_point);
uint32_t eccfreeec(ecc_type_t *ecc_para);
/**
  * @}
  */
/**
  * @}
  */

/**
 * @} ES32FXXX_ALD
 */
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MD_ECC_H__ */

/******************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
