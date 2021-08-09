/**********************************************************************************
 *
 * @file    md_crypt.c
 * @brief   CRYPT module driver.
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

/* Private Macros ------------------------------------------------------------ */

/* Private Variables --------------------------------------------------------- */

/* Public Variables ---------------------------------------------------------- */

/* Private Constants --------------------------------------------------------- */

/* Includes ------------------------------------------------------------------ */
#include "md_crypt.h"

/** @addtogroup Micro_Driver
  * @{
  */
/** @addtogroup MD_CRYPT
  * @{
  */

/* Private function prototypes ----------------------------------------------- */

/* Private Function ---------------------------------------------------------- */

/** @addtogroup MD_CRYPT_Public_Functions
  * @{
  */
/** @addtogroup MD_CRYPT_Public_Functions_Group1
  * @{
  */
/**
  * @brief  Reset the CRYPT peripheral.
  * @retval None
  */
void md_crypt_reset(void)
{
    WRITE_REG(CRYPT->DATA0, 0);
    WRITE_REG(CRYPT->DATA1, 0);
    WRITE_REG(CRYPT->DATA2, 0);
    WRITE_REG(CRYPT->DATA3, 0);
    WRITE_REG(CRYPT->KEY0, 0);
    WRITE_REG(CRYPT->KEY1, 0);
    WRITE_REG(CRYPT->KEY2, 0);
    WRITE_REG(CRYPT->KEY3, 0);
    WRITE_REG(CRYPT->KEY4, 0);
    WRITE_REG(CRYPT->KEY5, 0);
    WRITE_REG(CRYPT->KEY6, 0);
    WRITE_REG(CRYPT->KEY7, 0);
    WRITE_REG(CRYPT->IV0, 0);
    WRITE_REG(CRYPT->IV1, 0);
    WRITE_REG(CRYPT->IV2, 0);
    WRITE_REG(CRYPT->IV3, 0);
    WRITE_REG(CRYPT->CON, 0x8000);
    WRITE_REG(CRYPT->IFC, 0xFFFF);
}

/**
  * @brief  Initializes the CRYPT mode according to the specified parameters in
  *         the @ref md_crypt_init_t
  * @param  init Pointer to a md_crypt_init_t structure that contains
  *         the configuration information for the specified CRYPT module.
  * @retval None
  */
void md_crypt_init(md_crypt_init_t *init)
{
    md_crypt_reset();
    MODIFY_REG(CRYPT->CON, CRYPT_CON_ENCS_MSK, init->encs);
    MODIFY_REG(CRYPT->CON, CRYPT_CON_MODE_MSK, init->mode);
    MODIFY_REG(CRYPT->CON, CRYPT_CON_TYPE_MSK, init->type);
    MODIFY_REG(CRYPT->CON, CRYPT_CON_FIFOODR_MSK, init->order);
    MODIFY_REG(CRYPT->CON, CRYPT_CON_CRYSEL_MSK, (init->standard << CRYPT_CON_CRYSEL_POSS));
}

/**
  * @brief  Initialize the CRYPT peripheral using the default parameters.
  * @param  init: Pointer to a md_crypt_init_t structure
  * @retval None
  */
void md_crypt_init_struct(md_crypt_init_t *init)
{
    init->standard = MD_CRYPT_STANDARD_AES;
    init->mode     = MD_CRYPT_MODE_ECB;
    init->type     = MD_CRYPT_TYPE_32;
    init->order    = MD_CRYPT_FIFO_ORDER_0;
    init->encs     = MD_CRYPT_SEL_ENCRYPT;
}

/**
  * @brief  Set the register of key.
  * @param  CRYP_KeyIn: the key.
  * @param  ksize: the bit length   of key.
  * @retval none
  */
void cryp_keyin(uint32_t   *cryp_keyin, uint32_t ksize)
{
    switch (ksize)
    {
        case 8:
            WRITE_REG(CRYPT->KEY0, __REV(cryp_keyin[1]));
            WRITE_REG(CRYPT->KEY1, __REV(cryp_keyin[0]));
            break;

        case 16:
            WRITE_REG(CRYPT->KEY0, __REV(cryp_keyin[3]));
            WRITE_REG(CRYPT->KEY1, __REV(cryp_keyin[2]));
            WRITE_REG(CRYPT->KEY2, __REV(cryp_keyin[1]));
            WRITE_REG(CRYPT->KEY3, __REV(cryp_keyin[0]));
            break;

        case 24:
            WRITE_REG(CRYPT->KEY0, __REV(cryp_keyin[5]));
            WRITE_REG(CRYPT->KEY1, __REV(cryp_keyin[4]));
            WRITE_REG(CRYPT->KEY2, __REV(cryp_keyin[3]));
            WRITE_REG(CRYPT->KEY3, __REV(cryp_keyin[2]));
            WRITE_REG(CRYPT->KEY4, __REV(cryp_keyin[1]));
            WRITE_REG(CRYPT->KEY5, __REV(cryp_keyin[0]));
            break;

        case 32:
            WRITE_REG(CRYPT->KEY0, __REV(cryp_keyin[7]));
            WRITE_REG(CRYPT->KEY1, __REV(cryp_keyin[6]));
            WRITE_REG(CRYPT->KEY2, __REV(cryp_keyin[5]));
            WRITE_REG(CRYPT->KEY3, __REV(cryp_keyin[4]));
            WRITE_REG(CRYPT->KEY4, __REV(cryp_keyin[3]));
            WRITE_REG(CRYPT->KEY5, __REV(cryp_keyin[2]));
            WRITE_REG(CRYPT->KEY6, __REV(cryp_keyin[1]));
            WRITE_REG(CRYPT->KEY7, __REV(cryp_keyin[0]));
            break;

        default :
            break;
    }
}

/**
  * @brief  Set the register of input.
  * @param  CRYPT_Input: the input data.
  * @retval none
  */
void cryp_datain(uint32_t *crypt_input, uint8_t algorithm)
{
    if (algorithm != CRYPT_DES)
    {
        WRITE_REG(CRYPT->DATA0, __REV(*(crypt_input + 3)));
        WRITE_REG(CRYPT->DATA1, __REV(*(crypt_input + 2)));
        WRITE_REG(CRYPT->DATA2, __REV(*(crypt_input + 1)));
        WRITE_REG(CRYPT->DATA3, __REV(*(crypt_input + 0)));
    }
    else
    {
        WRITE_REG(CRYPT->DATA0, __REV(*(crypt_input + 1)));
        WRITE_REG(CRYPT->DATA1, __REV(*(crypt_input + 0)));
    }

}

/**
  * @brief  AES encrypt.
  * @param  ksize: the bit length   of key.
  * @retval An md_status_t enumeration value:
            @arg @ref   MD_OK
            @arg @reg   MD_ERROR
    */
md_status_t crypt_enable(cryptctx_stt_t *cryptctx)
{
    if (cryptctx->mode == CRYPT_GCM)
    {
        WRITE_REG(CRYPT->CON, 0x0);
        /* clear result register */
        SET_BIT(CRYPT->CON, CRYPT_CON_RESCLR_MSK);
    }

    /* select   mode */
    if (cryptctx->mode > 3)
        return MD_ERROR;

    MODIFY_REG(CRYPT->CON, CRYPT_CON_MODE_MSK, cryptctx->mode << 4);

    /* select   ase/des/sm4 */
    MODIFY_REG(CRYPT->CON, CRYPT_CON_CRYSEL_MSK, cryptctx->algori << 30);

    /* enable interrupt */
    SET_BIT(CRYPT->CON, CRYPT_CON_IE_MSK);

    /* select key size */
    /* AES */
    if (cryptctx->algori == CRYPT_AES)
    {
        if (cryptctx->mode != CRYPT_GCM)
        {
            switch (cryptctx->keysize)
            {
                case 16:
                    CLEAR_BIT(CRYPT->CON,   CRYPT_CON_AESKS_MSK);
                    break;

                case 24:
                    MODIFY_REG(CRYPT->CON, CRYPT_CON_AESKS_MSK, 0x1 << 2);
                    break;

                case 32:
                    MODIFY_REG(CRYPT->CON, CRYPT_CON_AESKS_MSK, 0x2 << 2);
                    break;

                default :
                    return MD_ERROR;
            }

            /* encrypt */
            if (cryptctx->encry_decry   == CRYPT_ENCRYPT)
                SET_BIT(CRYPT->CON, CRYPT_CON_ENCS_MSK);
            else
                CLEAR_BIT(CRYPT->CON,   CRYPT_CON_ENCS_MSK);
        }
    }

    /* DES */
    if (cryptctx->algori == CRYPT_DES)
    {
        switch (cryptctx->keysize)
        {
            case 8:
                CLEAR_BIT(CRYPT->CON, CRYPT_CON_TDES_MSK);
                break;

            case 16:
                CLEAR_BIT(CRYPT->CON, CRYPT_CON_DESKS_MSK);
                SET_BIT(CRYPT->CON, CRYPT_CON_TDES_MSK);
                break;

            case 24:
                SET_BIT(CRYPT->CON, CRYPT_CON_DESKS_MSK);
                SET_BIT(CRYPT->CON, CRYPT_CON_TDES_MSK);
                break;

            default :
                return MD_ERROR;
        }

        /* encrypt */
        if (cryptctx->encry_decry   == CRYPT_ENCRYPT)
            SET_BIT(CRYPT->CON, CRYPT_CON_ENCS_MSK);
        else
            CLEAR_BIT(CRYPT->CON,   CRYPT_CON_ENCS_MSK);
    }

    /* SM4 */
    if (cryptctx->algori == CRYPT_SM4)
    {
        /* encrypt */
        if (cryptctx->encry_decry   == CRYPT_ENCRYPT)
            SET_BIT(CRYPT->CON, CRYPT_CON_ENCS_MSK);
        else
            CLEAR_BIT(CRYPT->CON,   CRYPT_CON_ENCS_MSK);
    }

    if (cryptctx->fifoen == DISABLE)
    {
        /* enable   CRYPT   */
        SET_BIT(CRYPT->CON, CRYPT_CON_GO_MSK);
    }
    else
    {
        /* enable FIFO */
        SET_BIT(CRYPT->CON, CRYPT_CON_FIFOEN_MSK);

        if (cryptctx->ftype == FIFO_DATA0)
            CLEAR_BIT(CRYPT->CON,   CRYPT_CON_FIFOODR_MSK);
        else
            SET_BIT(CRYPT->CON, CRYPT_CON_FIFOODR_MSK);

        /* enable DMA */
        if (cryptctx->dmaen != DMA_DISABLE)
            SET_BIT(CRYPT->CON, CRYPT_CON_DMAEN_MSK);
    }

    return MD_OK;
}

/**
  * @brief  Get the result.
  * @param  CRYPT_Output:   the result of   encrypt or decrypt.
  * @retval none
  */
void cryp_dataout(uint32_t *crypt_output, uint8_t algorithm)
{
    if (algorithm != CRYPT_DES)
    {
        crypt_output[3] = __REV(CRYPT->RES0);
        crypt_output[2] = __REV(CRYPT->RES1);
        crypt_output[1] = __REV(CRYPT->RES2);
        crypt_output[0] = __REV(CRYPT->RES3);
    }
    else
    {
        crypt_output[1] = __REV(CRYPT->RES0);
        crypt_output[0] = __REV(CRYPT->RES1);
    }
}

/**
  * @brief  Get the result.
  * @param  CRYPT_Output:   the result of   encrypt or decrypt.
  * @param  Rfirst: RES0 first or   RES3 first.
  * @retval none
  */
void cryp_fifoout(uint32_t *crypt_output, uint8_t algorithm)
{
    if (algorithm != CRYPT_DES)
    {
        crypt_output[0] = CRYPT->FIFO;
        crypt_output[1] = CRYPT->FIFO;
        crypt_output[2] = CRYPT->FIFO;
        crypt_output[3] = CRYPT->FIFO;
    }
    else
    {
        crypt_output[0] = CRYPT->FIFO;
        crypt_output[1] = CRYPT->FIFO;
    }
}

/**
  * @brief  Set the register of fifo.
  * @param  CRYPT_Input: the input data.
  * @param  Dfirst:DATA0 first or   DATA3   first.
  * @retval none
  */
void cryp_fifoin(uint32_t *crypt_input, uint8_t algorithm)
{
    if (algorithm != CRYPT_DES)
    {
        WRITE_REG(CRYPT->FIFO, *(crypt_input + 0));
        WRITE_REG(CRYPT->FIFO, *(crypt_input + 1));
        WRITE_REG(CRYPT->FIFO, *(crypt_input + 2));
        WRITE_REG(CRYPT->FIFO, *(crypt_input + 3));
    }
    else
    {
        WRITE_REG(CRYPT->FIFO, *(crypt_input + 0));
        WRITE_REG(CRYPT->FIFO, *(crypt_input + 1));
    }
}

/**
  * @brief  Set the register of iv.
  * @param  CRYPT_IV:   the iv data.
  * @retval none
  */
void cryp_ivin(uint32_t *crypt_iv, uint8_t algorithm)
{
    if (algorithm != CRYPT_DES)
    {
        WRITE_REG(CRYPT->IV0, __REV(crypt_iv[3]));
        WRITE_REG(CRYPT->IV1, __REV(crypt_iv[2]));
        WRITE_REG(CRYPT->IV2, __REV(crypt_iv[1]));
        WRITE_REG(CRYPT->IV3, __REV(crypt_iv[0]));
    }
    else
    {
        WRITE_REG(CRYPT->IV0, __REV(crypt_iv[1]));
        WRITE_REG(CRYPT->IV1, __REV(crypt_iv[0]));
    }
}

/**
  * @brief  iv enable.
  * @param  n: the number   of calls.
  * @retval none
  */
void cryp_iv_enable(uint32_t n)
{
    if (n == 0)
        SET_BIT(CRYPT->CON, CRYPT_CON_IVEN_MSK);
    else
        CLEAR_BIT(CRYPT->CON, CRYPT_CON_IVEN_MSK);
}

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

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
