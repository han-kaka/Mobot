/**********************************************************************************
 *
 * @file    md_hash.c
 * @brief   HASH MD driver source file.
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
#include "string.h"
#include "md_hash.h"
#include "md_dma.h"

/** @addtogroup Micro_Driver
  * @{
  */
/** @defgroup MD_HASH HASH
  * @{
  */
/* Private Macros ------------------------------------------------------------ */

/* Private Constants --------------------------------------------------------- */

/* Private Variables --------------------------------------------------------- */

/* Public Variables ---------------------------------------------------------- */
/** @defgroup Public_Variables Public Variables
  * @{
  */
/* The lower 9 bits of DMA_CTRLBASE regisitor must be 0 */
md_dma_descriptor_t dma_ctrl[1] __attribute__((aligned(512)));
/**
  * @}
  */

/* Private function prototypes ----------------------------------------------- */

/* Private Function ---------------------------------------------------------- */
/** @defgroup Public_Function Public Function
  * @{
  */
/**
  * @brief  Initialize the DMA controller
  * @param  dma_ctrl_base pointer to a control structure base
  * @retval An ErrorStatus enumeration value. (Return always SUCCESS)
  */
void dma_init()
{
    /* Enable DMA */
    md_dma_enable();

    /* Clear DMA channel request */
    WRITE_REG(DMA0->IFLAG, 0x10000FFF);
    WRITE_REG(DMA0->IER, 0);

    memset(dma_ctrl, 0x0, sizeof(dma_ctrl));

    /* Set control base */
    md_dma_set_ctrlbase((uint32_t)&dma_ctrl);
}

/**
  * @brief:  Use MD library to config DMA.
  * @param:  None
  * @retval: None
  */
void dma_config(uint32_t *message)
{
    md_dma_config_t dma_config;

    md_dma_enable();

    md_dma_config_struct(&dma_config);
    dma_config.data_width     = MD_DMA_DATA_SIZE_WORD;
    dma_config.src_inc        = MD_DMA_DATA_INC_WORD;
    dma_config.dst_inc        = MD_DMA_DATA_INC_NONE;
    dma_config.R_power        = MD_DMA_R_POWER_16;
    dma_config.size           = 16;
    dma_config.src            = (void *)(uint32_t)message;
    dma_config.dst            = (void *)(uint32_t)(&HASH->DIN);
    dma_config.msigsel        = MD_DMA_MSIGSEL_HASH;
    dma_config.msel           = MD_DMA_MSEL_HASH;
    dma_config.high_prio      = DISABLE;
    dma_config.interrupt      = ENABLE;
    dma_config.primary        = ENABLE;
    dma_config.channel        = 0;
    md_dma_config_base(DMA0, MD_DMA_CYCLE_CTRL_BASIC, &dma_config);

    md_dma_enable_channel(MD_DMA_CH_0);
}
/**
  * @brief  word progress.
  * @param  input: the data of byte.
  * @param  output: the data of word.
  * @param  num: the byte length of input.
  * @retval None.
  */
void word_process(const uint8_t *input, uint32_t *output, uint8_t num)
{
    uint8_t i;

    for (i = 0; i < num; i++)
    {
        output[i] = __REV(*((uint32_t *)(input + 4 * i)));
    }
}

/**
  * @brief  halfword progress.
  * @param  input: the data of byte.
  * @param  output: the data of word.
  * @param  num: the byte length of input.
  * @retval None.
  */
void halfword_process(const uint8_t *input, uint32_t *output, uint8_t num)
{
    uint32_t HW1;
    uint32_t HW2;
    uint8_t  i;

    for (i = 0; i < num; i++)
    {
        HW1 = 0x0;
        HW2 = 0x0;
        memcpy(&HW1, input + 4 * i, 2);
        memcpy(&HW2, input + 4 * i + 2, 2);

        output[i] = (__REV(HW1) >> 16) | (__REV(HW2));
    }
}

/**
  * @brief  byte progress.
  * @param  input: the data of byte.
  * @param  output: the data of word.
  * @param  num: the byte length of input.
  * @retval None.
  */
void byte_process(const uint8_t *input, uint32_t *output, uint8_t num)
{
    uint8_t i;

    for (i = 0; i < num; i++)
    {
        memcpy(output + i, input + 4 * i, 4);
    }
}

/**
  * @brief  bit progress.
  * @param  input: the data of byte.
  * @param  output: the data of word.
  * @param  num: the byte length of input.
  * @retval None.
  */
void bit_process(const uint8_t *input, uint32_t *output, uint8_t num)
{
    uint8_t i;
    uint8_t j;
    uint8_t k;
    uint8_t temp[4];

    for (i = 0; i < num; i++)
    {
        for (j = 0; j < 4; j++)
        {
            temp[j] = 0;

            for (k = 0; k < 8; k++)
                temp[j] |= (*(input + 4 * i + j) >> (7 - k) & 0x1) << k;
        }

        output[i] = temp[0] | (temp[1] << 8) | (temp[2] << 16) | (temp[3] << 24);
    }
}

/**
  * @brief  hash operation.
  * @param  Input: the input message.
  * @retval An md_status_t enumeration value:
  *         @arg @ref MD_OK
  *         @arg @reg MD_ERROR
  */
md_status_t hash_process(uint32_t *Input, uint8_t dmaen)
{
    uint8_t i;

    /* write the register DIN */
    if (dmaen == HASH_DMA_DISABLE)
    {
        for (i = 0; i < 16; i++)
            WRITE_REG(HASH->DIN, Input[i]);
    }
    else
    {
        if (dmaen == HASH_DMA_ENABLE)
            dma_config(Input);

        SET_BIT(HASH->CTRL, HASH_CTRL_DMAEN_MSK);

        while (!DMA_FINISH);

        DMA_FINISH = 0x0;
        CLEAR_BIT(HASH->CTRL, HASH_CTRL_DMAEN_MSK);
    }

    /* wait finish */
    while (!HASHFINISH);

    HASHFINISH = 0x0;

    return MD_OK;
}

/**
  * @brief  hash operation of last group.
  * @param  Input: the word message.
  * @param  wlen: the length of word message.
  * @param  blen: the length of byte message.
  * @param  rinput: the byte message.
  * @param  databyp: the type of message.
  * @retval An md_status_t enumeration value:
  *         @arg @ref MD_OK
  *         @arg @reg MD_ERROR
  */
md_status_t hash_lprocess(uint32_t *input, uint8_t wlen, uint8_t blen, uint8_t *rinput, uint8_t databyp)
{
    uint8_t i;
    uint8_t j;
    uint8_t temp;

    /* write word message to DIN */
    for (i = 0; i < wlen; i++)
    {
        WRITE_REG(HASH->DIN, input[i]);
    }

    /* write byte message to DIN */
    switch (databyp)
    {
        case 0:
            for (i = 0; i < blen; i++)
                *((uint8_t *)(&(HASH->DIN)) + 3 - i) = *(rinput + i);

            break;

        case 1:
            for (i = 0; i < blen; i++)
            {
                if (i < 2)
                    *((uint8_t *)(&(HASH->DIN)) + 1 - i) = *(rinput + i);
                else
                    *((uint8_t *)(&(HASH->DIN)) + 5 - i) = *(rinput + i);
            }

            break;

        case 2:
            for (i = 0; i < blen; i++)
                *((uint8_t *)(&(HASH->DIN)) + i) = *(rinput + i);

            break;

        case 3:
            for (i = 0; i < blen; i++)
            {
                temp = 0;

                for (j = 0; j < 8; j++)
                    temp |= (*(rinput + i) >> (7 - j) & 0x1) << j;

                *((uint8_t *)(&(HASH->DIN)) + i) = temp;
            }

            break;

        default :
            return MD_ERROR;
    }

    /* HASH trig */
    SET_BIT(HASH->CTRL, HASH_CTRL_TRIG_MSK);

    /* wait finish */
    while (!HASHFINISH);

    HASHFINISH = 0x0;

    return MD_OK;
}

/**
  * @brief  initial hash paramter.
  * @param  HASHctx: the paramter of hash.
  * @param  Length: the length of message with byte.
  * @param  ITYP: the type of input: no change, halfword change, byte change, bit change.
  * @param  OTYP: the type of output: big endian, little endian.
  * @param  Mode: select SM3 or SHA256.
  * @retval An md_status_t enumeration value:
  *         @arg @ref MD_OK
  *         @arg @reg MD_ERROR
  */
md_status_t hash_init(hashctx_stt_t *hashctx)
{
    /* check the length*/
    if (hashctx->length == 0)
        return MD_ERROR;

    /* set the type of data: word change, halfword change, byte changed, bit change */
    switch (hashctx->datatyp)
    {
        case 0:
            CLEAR_BIT(HASH->CTRL, HASH_CTRL_DATATYP_MSK);
            break;

        case 1:
        case 2:
        case 3:
            MODIFY_REG(HASH->CTRL, HASH_CTRL_DATATYP_MSK, hashctx->datatyp << 6);
            break;

        default :
            return MD_ERROR;
    }

    /* set the type of output: big endian, little endian */
    switch (hashctx->outtyp)
    {
        case 0:
            CLEAR_BIT(HASH->CTRL, HASH_CTRL_OUTTYP_MSK);
            break;

        case 1:
            SET_BIT(HASH->CTRL, HASH_CTRL_OUTTYP_MSK);
            break;

        default:
            return MD_ERROR;
    }

    /* select sm3 or sha256 */
    MODIFY_REG(HASH->CTRL, HASH_CTRL_ALGO_MSK, hashctx->mode << 3);

    /* interrupt enable */
    SET_BIT(HASH->CTRL, HASH_CTRL_INTEN_MSK);

    /* Enable DMA controller */
    if (hashctx->dmaen != HASH_DMA_DISABLE)
        dma_init();

    return MD_OK;
}

/**
  * @brief  Hash progress.
  * @param  HASHctx: the paramter of hash.
  * @param  InputBuffer: the input message.
  * @retval An md_status_t enumeration value:
  *         @arg @ref MD_OK
  *         @arg @reg MD_ERROR
  */
md_status_t hash_append(hashctx_stt_t *hashctx, const uint8_t *inputbuffer)
{
    uint32_t i;
    uint32_t n;
    uint32_t m;
    uint32_t rlen;
    uint32_t input[16];

    /* n: the number of groups which are 512bits without padding */
    if (hashctx->length >= 64)
        n = (hashctx->length % 64) ? (hashctx->length / 64) : (hashctx->length / 64 - 1);
    else
        n = 0;

    /* hash enable */
    SET_BIT(HASH->CTRL, HASH_CTRL_EN_MSK);

    /* carry out hash */
    for (i = 0; i < n; i++)
    {
        /* devide message into groups according to DATATYP*/
        switch (hashctx->datatyp)
        {
            case 0:
                word_process(inputbuffer + 64 * i, input + 16 * i, 16); /* word */
                break;

            case 1:
                halfword_process(inputbuffer + 64 * i, input + 16 * i, 16); /* halfword */
                break;

            case 2:
                byte_process(inputbuffer + 64 * i, input + 16 * i, 16); /* byte */
                break;

            case 3:
                bit_process(inputbuffer + 64 * i, input + 16 * i, 16); /* bit */
                break;

            default:
                return MD_ERROR;
        }

        /* hash operation */
        hash_process(input, hashctx->dmaen);
    }

    /* rlen:the number of remaind bytes */
    rlen = hashctx->length - n * 64;
    /* n:the number of words of remaind bytes */
    m = (rlen % 4) ? (rlen / 4) : (rlen / 4 - 1);

    /* carry out hash for the last messagge */
    for (i = 0; i < m; i++)
    {
        /* devide message into groups according to datatyp*/
        switch (hashctx->datatyp)
        {
            case 0:
                word_process(inputbuffer + 64 * n + 4 * i, input + i, 1); /* word */
                break;

            case 1:
                halfword_process(inputbuffer + 64 * n + 4 * i, input + i, 1); /* halfword */
                break;

            case 2:
                byte_process(inputbuffer + 64 * n + 4 * i, input + i, 1); /* byte */
                break;

            case 3:
                bit_process(inputbuffer + 64 * n + 4 * i, input + i, 1); /* bit */
                break;

            default:
                return MD_ERROR;
        }
    }

    /* hash operation */
    hash_lprocess(input, m, rlen - 4 * m, (uint8_t *)inputbuffer + hashctx->length - rlen + 4 * m, hashctx->datatyp);

    return MD_OK;
}

/**
  * @brief  Get the result of hash.
  * @param  OutputBuffer: the result of hash.
  * @param  otyp: the type of output.
  * @retval An md_status_t enumeration value:
  *         @arg @ref MD_OK
  *         @arg @reg MD_ERROR
  */
md_status_t hash_finish(uint8_t *outputbuffer, uint8_t otyp)
{
    uint32_t    output[8];

    /* get the result */
    if (otyp == HASH_OUT_L)
    {
        output[0] = READ_REG(HASH->RES7);
        output[1] = READ_REG(HASH->RES6);
        output[2] = READ_REG(HASH->RES5);
        output[3] = READ_REG(HASH->RES4);
        output[4] = READ_REG(HASH->RES3);
        output[5] = READ_REG(HASH->RES2);
        output[6] = READ_REG(HASH->RES1);
        output[7] = READ_REG(HASH->RES0);
    }
    else
    {
        output[0] = __REV(READ_REG(HASH->RES7));
        output[1] = __REV(READ_REG(HASH->RES6));
        output[2] = __REV(READ_REG(HASH->RES5));
        output[3] = __REV(READ_REG(HASH->RES4));
        output[4] = __REV(READ_REG(HASH->RES3));
        output[5] = __REV(READ_REG(HASH->RES2));
        output[6] = __REV(READ_REG(HASH->RES1));
        output[7] = __REV(READ_REG(HASH->RES0));
    }

    /* convert word to byte */
    memcpy(outputbuffer, output, 32);

    return MD_OK;
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
/******************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
