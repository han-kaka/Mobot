/**********************************************************************************
 *
 * @file    md_ecc.c
 * @brief   ECC MD driver source file.
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

/* Includes -------------------------------------------------------------------*/
#include "md_ecc.h"
#include <string.h>
/** @addtogroup Micro_Driver
  * @{
  */
/** @defgroup MD_ECC ECC
  * @{
  */
/* Private Macros ------------------------------------------------------------ */

/* Private Variables --------------------------------------------------------- */

/* Public Variables ---------------------------------------------------------- */

/* Private Constants --------------------------------------------------------- */

/* Private function prototypes ----------------------------------------------- */

/* Private Function ---------------------------------------------------------- */
/** @defgroup Private_Function Private Function
  * @{
  */
/**
  * @brief  Calculate N0.
  * @param  data: the register of N
  * @retval N0.
  */
uint32_t n0_calculate(uint32_t data)
{
    uint32_t x;
    uint32_t result;
    uint8_t  i;

    x = 1;
    result = 1;

    for (i = 0; i < 32; i++)
    {
        if (x % 2 == 1)
            result |= 1 << i;
        else
            result |= 0 << i;

        x = (x + ((result >> i) & 0x1) * data) / 2;
    }

    return result;
}

/**
  * @brief  Wait ECC finish.
  * @retval An md_status_t value:
  *         @arg @ref MD_OK
  *         @arg @reg ECC_ERR_HWSTA
  */
uint32_t ecc_wait_done(void)
{
    /* wait ECC DONE = 1 */
    while (!READ_BIT(ECC->STA, ECC_STA_DONE_MSK));

    /* check the ERR */
    if (READ_BIT(ECC->STA, ECC_STA_ERR_MSK))
        return ECC_ERR_HWSTA;

    /* ECC DONE = 0 */
    SET_BIT(ECC->STA, ECC_STA_DONE_MSK);

    return MD_OK;
}

/**
  * @brief  Calculate H.
  * @param  data: the modulus.
  * @retval An md_status_t value:
  *         @arg @ref MD_OK
  *         @arg @reg ECC_ERR_HWSTA
  */
uint32_t ecc_hcal(const uint8_t *data)
{
    uint32_t       state;

    /* set the modulus */
    memcpy(&ECC->NREG[0], (uint32_t *)data, OCTEST256);

    /* select H calculate and enable ECC*/
    WRITE_REG(ECC->CON, 0x80000000);

    /* wait finish */
    state = ecc_wait_done();

    return state;
}

/**
  * @brief  Computes the point scalar multiplication kP = k*P.
  * @param  ECC_PrivKey: Structure containing the scalar value of the multiplication.
  * @param  ECC_Point: The point that will be multiplied.
  * @param  ECC_ResPoint: The output point, result of the multiplication
  * @param  ECC_Para: Structure describing the curve parameters.
  * @retval An md_status_t value:
  *         @arg @ref MD_OK
  *         @arg @reg ECC_ERR_HWSTA
  *         @arg @reg ECC_ERR_BAD_PARAMETER
  *         @arg @reg ECC_WARN_POINT_AT_INFINITY
  */
uint32_t eccscalarmul(const ecc_point_type_t *ecc_point, const ecc_privkey_type_t *ecc_privkey,
                      ecc_point_type_t *ecc_respoint, const ecc_type_t *ecc_para)
{
    uint32_t      i;

    /* check the prive key & public key is or nor null */
    if ((ecc_point == NULL) || (ecc_privkey == NULL))
        return ECC_ERR_BAD_PARAMETER;

    /* calculate H */
    ecc_hcal(ecc_para->pmp);

    /* calculate n0, and write to PARA */
    WRITE_REG(ECC->PARA, n0_calculate(ECC->NREG[0]));

    /* write the public key (x,y,z) to the register of AREG */
    for (i = 0; i < 8; i++)
    {
        WRITE_REG(ECC->AREG[i],      ecc_point->pmx[i]);
        WRITE_REG(ECC->AREG[i + 8],  ecc_point->pmx[i]);
        WRITE_REG(ECC->AREG[i + 16], ecc_point->pmy[i]);
        WRITE_REG(ECC->AREG[i + 24], 0x0);
        WRITE_REG(ECC->AREG[i + 32], 0x0);
        WRITE_REG(ECC->AREG[i + 40], 0x0);
        WRITE_REG(ECC->AREG[i + 48], 0x0);
    }

    ECC->AREG[31] = 0x1;
    ECC->AREG[47] = 0x1;

    /* write private key to the register SCALARx */
    WRITE_REG(ECC->SCALAR0, ecc_privkey->pmd[0]);
    WRITE_REG(ECC->SCALAR1, ecc_privkey->pmd[1]);
    WRITE_REG(ECC->SCALAR2, ecc_privkey->pmd[2]);
    WRITE_REG(ECC->SCALAR3, ecc_privkey->pmd[3]);
    WRITE_REG(ECC->SCALAR4, ecc_privkey->pmd[4]);
    WRITE_REG(ECC->SCALAR5, ecc_privkey->pmd[5]);
    WRITE_REG(ECC->SCALAR6, ecc_privkey->pmd[6]);
    WRITE_REG(ECC->SCALAR7, ecc_privkey->pmd[7]);

    /* write public key y to the register YCOx */
    WRITE_REG(ECC->YCO0, ecc_point->pmy[0]);
    WRITE_REG(ECC->YCO1, ecc_point->pmy[1]);
    WRITE_REG(ECC->YCO2, ecc_point->pmy[2]);
    WRITE_REG(ECC->YCO3, ecc_point->pmy[3]);
    WRITE_REG(ECC->YCO4, ecc_point->pmy[4]);
    WRITE_REG(ECC->YCO5, ecc_point->pmy[5]);
    WRITE_REG(ECC->YCO6, ecc_point->pmy[6]);
    WRITE_REG(ECC->YCO7, ecc_point->pmy[7]);

    ECC->AREG[48] = 3;

    /* select scalar multiplication and enable ECC */
    WRITE_REG(ECC->CON, 0xF);

    /* wait scalar multiplication finish */
    while (!TOTAL_FINISH);

    TOTAL_FINISH = 0x0;

    /* check the ecc calculate is or not error */
    if (READ_BIT(ECC->STA, ECC_STA_ERR_MSK))
    {
        /* clear the flag */
        SET_BIT(ECC->STA, ECC_STA_ERR_MSK);
        return MD_ERROR;
    }

    /* check the result is or not infinity point */
    if (READ_BIT(ECC->STA, ECC_STA_MI_ZERO_MSK))
    {
        /* clear the flag */
        SET_BIT(ECC->STA, ECC_STA_MI_ZERO_MSK);
        return ECC_WARN_POINT_AT_INFINITY;
    }

    WRITE_REG(ECC->STA, 0x2);
    /* get the public point */
    memcpy(ecc_respoint->pmx, &ECC->AREG[8], sizeof(ecc_respoint->pmx));
    memcpy(ecc_respoint->pmy, &ECC->AREG[16], sizeof(ecc_respoint->pmy));

    return MD_OK;
}

/**
  * @brief  The modulus multiplication.
  * @param  numA: the data of multiplication.
  * @param  numB: the data of multiplication.
  * @param  result: numA *numB.
  * @retval An md_status_t value:
  *         @arg @ref MD_OK
  *         @arg @reg ECC_ERR_HWSTA
  */
uint32_t ecc_mul(uint32_t *numa, uint32_t *numb, uint32_t *result)
{
    uint32_t state;

    /* numA->T0, numB->T1*/
    memcpy(&ECC->AREG[0], numa, 32);
    memcpy(&ECC->AREG[8], numb, 32);

    /* calculate n0, and write to PARA */
    WRITE_REG(ECC->PARA, n0_calculate(ECC->NREG[0]));

    /* A->T0, H->T7, D = numA * H->T2*/
    ECC->CON = 0x800003a2;
    state = ecc_wait_done();

    if (state != MD_OK)
        return state;

    /* D->T2, B->T1, C = D * B->T4 */
    ECC->CON = 0x800008c2;
    state = ecc_wait_done();

    if (state != MD_OK)
        return state;

    /* get the result from T4 */
    memcpy(result, &ECC->AREG[32], 32);

    return MD_OK;
}

/**
  * @brief  The point add.
  * @param  ECC_PointA: the point A.
  * @param  ECC_PointB: the point B.
  * @param  ECC_Para: the parameter of ECC curve.
  * @retval An md_status_t value:
  *         @arg @ref MD_OK
  *         @arg @reg ECC_ERR_HWSTA
  */
uint32_t ecc_point_add(ecc_point_type_t *ecc_pointa, ecc_point_type_t *ecc_pointb,
                       const ecc_type_t *ecc_para)
{
    uint32_t     state;
    uint32_t    z[8];
    uint32_t    zinver[8];
    uint32_t    x[8];
    uint32_t    y[8];
    uint32_t    zinver2[8];
    uint32_t    zinver3[8];

    /* x1->T1,y1->T2,x2->T4,y2->T5 */
    memcpy(&ECC->AREG[8], ecc_pointa->pmx, OCTEST256);
    memcpy(&ECC->AREG[16], ecc_pointa->pmy, OCTEST256);
    memset(&ECC->AREG[24], 0x0, OCTEST256);
    memcpy(&ECC->AREG[32], ecc_pointb->pmx, OCTEST256);
    memcpy(&ECC->AREG[40], ecc_pointb->pmy, OCTEST256);
    memcpy(&ECC->NREG[0], (uint32_t *)ecc_para->pmp, OCTEST256);

    /* calculate T3 = Z = T1 - T4 */
    WRITE_REG(ECC->CON, 0x80000636);
    state = ecc_wait_done();

    if (state != MD_OK)
        return state;

    /* save z */
    memcpy(z, &ECC->AREG[24], OCTEST256);

    /* calculate H */
    state = ecc_hcal(ecc_para->pmp);

    if (state != MD_OK)
        return state;

    /* T0~T6 turn into mont region */
    WRITE_REG(ECC->CON, 0X8000000C); /* T0 */
    state = ecc_wait_done();

    if (state != MD_OK)
        return state;

    WRITE_REG(ECC->CON, 0X8000049C); /* T1 */
    state = ecc_wait_done();

    if (state != MD_OK)
        return state;

    WRITE_REG(ECC->CON, 0X8000092C); /* T2 */
    state = ecc_wait_done();

    if (state != MD_OK)
        return state;

    WRITE_REG(ECC->CON, 0X80000dBC); /* T3 */
    state = ecc_wait_done();

    if (state != MD_OK)
        return state;

    WRITE_REG(ECC->CON, 0X8000124C); /* T4 */
    state = ecc_wait_done();

    if (state != MD_OK)
        return state;

    WRITE_REG(ECC->CON, 0X800016DC); /* T5 */
    state = ecc_wait_done();

    if (state != MD_OK)
        return state;

    WRITE_REG(ECC->CON, 0X80001b6C); /* T6 */
    state = ecc_wait_done();

    if (state != MD_OK)
        return state;

    /* ZADDU */
    WRITE_REG(ECC->CON, 0xD8000000);
    state = ecc_wait_done();

    if (state != MD_OK)
        return state;

    /* T0~T6 turn out from  mont region */
    WRITE_REG(ECC->CON, 0X8000000A); /* T0 */
    state = ecc_wait_done();

    if (state != MD_OK)
        return state;

    WRITE_REG(ECC->CON, 0X8000049A); /* T1 */
    state = ecc_wait_done();

    if (state != MD_OK)
        return state;

    WRITE_REG(ECC->CON, 0X8000092A); /* T2 */
    state = ecc_wait_done();

    if (state != MD_OK)
        return state;

    WRITE_REG(ECC->CON, 0X80000dBA); /* T3 */
    state = ecc_wait_done();

    if (state != MD_OK)
        return state;

    WRITE_REG(ECC->CON, 0X8000124A); /* T4 */
    state = ecc_wait_done();

    if (state != MD_OK)
        return state;

    WRITE_REG(ECC->CON, 0X800016DA); /* T5 */
    state = ecc_wait_done();

    if (state != MD_OK)
        return state;

    WRITE_REG(ECC->CON, 0X80001b6A); /* T6 */
    state = ecc_wait_done();

    if (state != MD_OK)
        return state;

    /* convert the result to affine coordinate (x/(z^2), y/(Z^3)) */
    /* get jacobian x & y */
    memcpy(x, &ECC->AREG[32], OCTEST256);
    memcpy(y, &ECC->AREG[40], OCTEST256);

    /* calculate the inverse of z */
    memcpy(&ECC->AREG[24], z, OCTEST256);
    WRITE_REG(ECC->CON, 0x80000038);
    state = ecc_wait_done();

    if (state != MD_OK)
        return state;

    memcpy(zinver, &ECC->AREG[24], 32);

    /* calculate h */
    state = ecc_hcal(ecc_para->pmp);

    if (state != MD_OK)
        return state;

    /* calculate affine coordinate x */
    /* calculate (z^(-1))^2 */
    state = ecc_mul(zinver, zinver, zinver2);

    if (state != MD_OK)
        return state;

    /* calculate x = x*(z^(-1))^2 */
    state = ecc_mul(x, zinver2, ecc_pointa->pmx);

    if (state != MD_OK)
        return state;

    /* calculate affine coordinate y */
    /*calculate (z^(-1))^3 */
    state = ecc_mul(zinver2, zinver, zinver3);

    if (state != MD_OK)
        return state;

    /* calculate y = y*(z^(-1))^3 */
    state = ecc_mul(zinver3, y, ecc_pointa->pmy);

    if (state != MD_OK)
        return state;

    return MD_OK;
}

/**
  * @brief  Verify the public key.
  * @param  ECC_Point: the public key.
  * @param  ECC_Para: the parameter of ECC curve.
  * @retval An md_status_t value:
  *         @arg @ref MD_OK
  *         @arg @reg ECC_ERR_HWSTA
  *         @arg @reg ECC_ERR_BAD_PARAMETER
  */
uint32_t eccvalidatepubkey(ecc_point_type_t *ecc_point, const ecc_type_t *ecc_para)
{
    ecc_privkey_type_t  ecc_privkey;
    ecc_point_type_t    ecc_respoint;
    uint32_t          y2result[8];
    uint32_t          addresult[8];
    uint32_t           state;
    uint32_t          zero[8];
    uint32_t          x2[8];
    uint32_t          x3[8];
    uint32_t          ax[8];

    /* check the public key is or not 0 */
    memset(zero, 0, sizeof(zero));

    if (!memcmp(ecc_point->pmx, zero, sizeof(zero)))
        return ECC_ERR_BAD_PARAMETER;

    if (!memcmp(ecc_point->pmy, zero, sizeof(zero)))
        return ECC_ERR_BAD_PARAMETER;

    /* check y^2 = x^3 + a*x + b (modp) */
    /* calculate H */
    state = ecc_hcal(ecc_para->pmp);

    if (state != MD_OK)
        return state;

    /* calculat y^2 */
    state = ecc_mul(ecc_point->pmy, ecc_point->pmy, y2result);

    if (state != MD_OK)
        return state;

    /* calculate x^3 */
    state = ecc_mul(ecc_point->pmx, ecc_point->pmx, x2);

    if (state != MD_OK)
        return state;

    state = ecc_mul(ecc_point->pmx, x2, x3);

    if (state != MD_OK)
        return state;

    /* calculate ax */
    state = ecc_mul((uint32_t *)ecc_para->pma, ecc_point->pmx, ax);

    if (state != MD_OK)
        return state;

    /* calculate x^3 + ax */
    memcpy(&ECC->AREG[48], x3, OCTEST256);
    memcpy(&ECC->AREG[40], ax, OCTEST256);
    WRITE_REG(ECC->CON, 0x80001ac4);
    state = ecc_wait_done();

    if (state == ECC_ERR_HWSTA)
        return ECC_ERR_HWSTA;

    /* calculate x^3 + ax + b */
    memcpy(&ECC->AREG[8], ecc_para->pmb, sizeof(ecc_para->pmb));
    WRITE_REG(ECC->CON, 0x800010d4);
    state = ecc_wait_done();

    if (state == ECC_ERR_HWSTA)
        return ECC_ERR_HWSTA;

    memcpy(addresult, &ECC->AREG[40], OCTEST256);

    /* check y^2 = x^3+ax+b (mod p) */
    if (memcmp(y2result, addresult, OCTEST256))
        return ECC_POINT_INVALID;

    state = eccsetprivkeyvalue(&ecc_privkey, ecc_para->pmn, 32);

    if (state != MD_OK)
        return state;
    else
        state = eccscalarmul(ecc_point, &ecc_privkey, &ecc_respoint, ecc_para);

    if (state != ECC_WARN_POINT_AT_INFINITY)
        return MD_ERROR;

    return MD_OK;
}

/**
  * @brief  ECDSA: generate ECC signature r and s.
  * @param  ECC_Point: the public key.
  * @param  ECC_Para: the parameter of ECC curve.
  * @retval An md_status_t value:
  *         @arg @ref MD_OK
  *         @arg @reg ECC_ERR_HWSTA
  */
uint32_t ecc_r_s(const uint32_t *datax, const uint32_t *datak,
                 const uint8_t *dataz, const uint32_t  *privekey,
                 const ecc_type_t *ecc_para, ecdsasignature_type_t *ecdsa_signature)
{
    uint32_t        state;
    uint8_t        i;
    uint32_t       tempres[8];
    uint32_t       zero[8];

    /* calculate H */
    ecc_hcal(ecc_para->pmn);

    /* calculate r, r = x mod n */
    memset(&ECC->AREG[0], 0x0, OCTEST256);
    memcpy(&ECC->AREG[8], datax, OCTEST256);

    /* (T0+T1)mod n -> T2 */
    WRITE_REG(ECC->CON, 0x800000a4);
    state = ecc_wait_done();

    if (state != MD_OK)
        return state;

    /* check r is or not 0 */
    memset(zero, 0, sizeof(zero));

    if (!memcmp(&ECC->AREG[16], zero, sizeof(zero)))
        return MD_ERROR;

    /* get the signature r */
    for (i = 0; i < 8; i++)
        ecdsa_signature->r[i] = READ_REG(ECC->AREG[16 + i]);

    /* calculate s, s= k^(-1)(z+r*da)mod n */
    /* r*privekey mod n*/
    ecc_mul(ecdsa_signature->r, (uint32_t *)privekey, tempres);

    /* r*privekey->T1, z->T0, z+r*privekey->T2 */
    for (i = 0; i < 8; i++)
    {
        WRITE_REG(ECC->AREG[8 + i], tempres[i]);
        WRITE_REG(ECC->AREG[i], *(uint32_t *)(dataz + i * 4));
    }

    WRITE_REG(ECC->CON, 0x800000a4);
    state = ecc_wait_done();

    if (state != MD_OK)
        return state;

    /* k^-1->T3 */
    memcpy(&ECC->AREG[24], datak, OCTEST256);
    ECC->CON = 0x80000038;
    state = ecc_wait_done();

    if (state != MD_OK)
        return state;

    /* k^-1->T3,z+r*privekey->T2,k^(-1)(z+r*da)mod n -> T0 */
    /* calculate H */
    ecc_hcal(ecc_para->pmn);
    ecc_mul(&ECC->AREG[16], &ECC->AREG[24], tempres);

    for (i = 0; i < OCTEST256 / 4; i++)
        ecdsa_signature->s[i] = tempres[i];

    return MD_OK;
}

/**
  * @brief  ECDSA: verify ECC signature r & s.
  * @param  DataZ: the hash of message
  * @param  ECDSA_Signature: the ECC signature r & s.
  * @param  ECDSA_VerifyCtx: the ECC parameter & public key.
  * @retval An md_status_t value:
  *         @arg @ref MD_OK
  *         @arg @reg ECC_ERR_HWSTA
  *         @arg @reg ECC_ERR_BAD_PARAMETER
  */
uint32_t ecc_r_s_check(const uint8_t *dataz, const ecdsasignature_type_t *ecdsa_signature,
                       const ecdsaverifyctx_type_t *ecdsa_verifyctx)
{
    uint32_t           state;
    uint32_t          i;
    uint32_t          tmpu1[8];
    uint32_t          tmpu2[8];
    ecc_point_type_t    tmpg;
    ecc_point_type_t    u1g;
    ecc_point_type_t    u2q;
    ecc_privkey_type_t  ecc_privkey;
    uint32_t          sinver[8];
    uint32_t          cmp[8];
    uint32_t          zero[8];

    /* check r,s in [1,n-1] */
    memset(zero, 0, 32);

    if (!memcmp(ecdsa_signature->r, zero, 32))
        return ECC_ERR_BAD_PARAMETER;

    if (!memcmp(ecdsa_signature->s, zero, 32))
        return ECC_ERR_BAD_PARAMETER;

    memcpy(cmp, ecdsa_verifyctx->ecc_para->pmn, 32);
    cmp[0] = cmp[0] - 1;

    for (i = 0; i < 8; i++)
    {
        if (memcmp(&ecdsa_signature->r[7 - i], &cmp[7 - i], 4) > 0)
            return ECC_ERR_BAD_PARAMETER;

        if (memcmp(&ecdsa_signature->r[7 - i], &cmp[7 - i], 4) < 0)
            break;
    }

    for (i = 0; i < 8; i++)
    {
        if (memcmp(&ecdsa_signature->s[7 - i], &cmp[7 - i], 4) > 0)
            return ECC_ERR_BAD_PARAMETER;

        if (memcmp(&ecdsa_signature->s[7 - i], &cmp[7 - i], 4) < 0)
            break;
    }

    /* calculate H */
    state = ecc_hcal(ecdsa_verifyctx->ecc_para->pmn);

    if (state != MD_OK)
        return state;

    /* calculate s^(-1) */
    memcpy(&ECC->AREG[24], ecdsa_signature->s, 32);
    ECC->CON = 0x80000038;
    state = ecc_wait_done();

    if (state != MD_OK)
        return state;

    memcpy(sinver, &ECC->AREG[24], 32);

    /* u1 = DataZ * s^(-1) */
    /* calculate H */
    ecc_hcal(ecdsa_verifyctx->ecc_para->pmn);
    /* calculate DataZ*s^(-1) */
    state = ecc_mul(sinver, (uint32_t *)dataz, tmpu1);

    if (state != MD_OK)
        return state;

    /* u2 = r * s^(-1) */
    state = ecc_mul(sinver, (uint32_t *)ecdsa_signature->r, tmpu2);

    if (state != MD_OK)
        return state;

    /* u1G = u1 * G(basic key) */
    memcpy(ecc_privkey.pmd, tmpu1, 32);
    memcpy(tmpg.pmx, (uint32_t *)ecdsa_verifyctx->ecc_para->pmgx, 32);
    memcpy(tmpg.pmy, (uint32_t *)ecdsa_verifyctx->ecc_para->pmgy, 32);
    state = eccscalarmul(&tmpg, &ecc_privkey, &u1g, ecdsa_verifyctx->ecc_para);

    if (state != MD_OK)
        return state;

    /* u2Q = u2 * Q(public key) */
    memcpy(ecc_privkey.pmd, tmpu2, 32);
    memcpy(tmpg.pmx, ecdsa_verifyctx->ecc_point->pmx, 32);
    memcpy(tmpg.pmy, ecdsa_verifyctx->ecc_point->pmy, 32);
    state = eccscalarmul(&tmpg, &ecc_privkey, &u2q, ecdsa_verifyctx->ecc_para);

    if (state != MD_OK)
        return state;

    /* u1G = u1G + u2Q */
    state = ecc_point_add(&u1g, &u2q, ecdsa_verifyctx->ecc_para);

    if (state != MD_OK)
        return state;

    /* calculate H */
    state = ecc_hcal(ecdsa_verifyctx->ecc_para->pmn);

    if (state != MD_OK)
        return state;

    /* calculate r, r = x mod n */
    /* 0x0->T0, r->T1 */
    memset(&ECC->AREG[0], 0x0, OCTEST256);
    memcpy(&ECC->AREG[8], u1g.pmx, OCTEST256);
    /* (T0+T1)mod n -> T2 */
    WRITE_REG(ECC->CON, 0x800000a4);
    state = ecc_wait_done();

    if (state != MD_OK)
        return state;

    /* verify r */
    for (i = 0; i < 8; i++)
    {
        if (READ_REG(ECC->AREG[16 + i]) != ecdsa_signature->r[i])
            return MD_ERROR;
    }

    return MD_OK;
}
/**
  * @}
  */
/**
  * @}
  */
/**
 * @} ES32FXXX_ALD
 */
/******************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
