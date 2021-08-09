/**********************************************************************************
 *
 * @file    md_trng.c
 * @brief   TRNG module driver.
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

/* Includes ------------------------------------------------------------------ */
#include "md_trng.h"

/** @addtogroup Micro_Driver
  * @{
  */


/* Private Macros ------------------------------------------------------------ */
/* Private Variables --------------------------------------------------------- */
/* Public Variables ---------------------------------------------------------- */
/* Private Constants --------------------------------------------------------- */

/** @addtogroup MD_TRNG
  * @{
  */
/** @addtogroup MD_TRNG_Public_Functions
  * @{
  */
/** @addtogroup MD_TRNG_Public_Functions_Group1
  * @{
  */

/* Private function prototypes ----------------------------------------------- */

/* Private Function ---------------------------------------------------------- */

/**
  *@brief  TRNG initial
    *@param  RNGstate: Structure of the RNG stat
    *@retval MD_ERROR status: can be MD_OK if MD_OK or MD_ERROR if MD_ERROR occured
*/
md_status_t rnginit(rngstate_type_t *rng_state)
{
    if (rng_state == NULL)
        return MD_ERROR;

    /* set the trng start time */
    MODIFY_REG(TRNG->CFGR, TRNG_CFGR_TSTART_MSK, rng_state->starttime << TRNG_CFGR_TSTART_POSS);
    /* set the trng modify cofficient */
    MODIFY_REG(TRNG->CR, TRNG_CR_ADJC_MSK, rng_state->modnum << TRNG_CR_ADJC_POSS);
    /* set the trng seed selction */
    MODIFY_REG(TRNG->CR, TRNG_CR_SDSEL_MSK, rng_state->rngseed << TRNG_CR_SDSEL_POSS);
    /* set the trng data type */
    MODIFY_REG(TRNG->CR, TRNG_CR_DSEL_MSK, rng_state->rngmode << TRNG_CR_DSEL_POSS);
    /* enable the trng modify */
    SET_BIT(TRNG->CR, TRNG_CR_ADJM_MSK);

    /* set the seed register */
    if (rng_state->seed != NULL)
        WRITE_REG(TRNG->SEED, rng_state->seed);

    return MD_OK;
}

/**
  * @brief  Initializes the TRNG according to the specified
  *         parameters in the md_trng_init_t.
  * @param  init: Pointer to a md_trng_init_t structure that contains
  *         the configuration information.
  * @retval None
  */
void md_trng_init(md_trng_init_t *init)
{
    SET_BIT(TRNG->CR, TRNG_CR_TRNGSEL_MSK);
    MODIFY_REG(TRNG->CR, TRNG_CR_DSEL_MSK, (init->data_width) << TRNG_CR_DSEL_POSS);
    MODIFY_REG(TRNG->CR, TRNG_CR_SDSEL_MSK, (init->seed_type) << TRNG_CR_SDSEL_POSS);
    MODIFY_REG(TRNG->CR, TRNG_CR_ADJC_MSK, (init->adjc) << TRNG_CR_ADJC_POSS);

    if (init->adjc == 0)
    {
        MODIFY_REG(TRNG->CR, TRNG_CR_ADJC_MSK, (0) << TRNG_CR_ADJC_POSS);
    }
    else
    {
        MODIFY_REG(TRNG->CR, TRNG_CR_ADJC_MSK, (1) << TRNG_CR_ADJC_POSS);
    }

    WRITE_REG(TRNG->SEED, init->seed);
    MODIFY_REG(TRNG->CFGR, TRNG_CFGR_TSTART_MSK, (init->t_start) << TRNG_CFGR_TSTART_POSS);
    MODIFY_REG(TRNG->CR, TRNG_CR_POSTEN_MSK, (init->posten) << TRNG_CR_POSTEN_MSK);
}

/**
  * @brief  Set each @ref md_trng_init_t field to default value.
  * @param  init: Pointer to a @ref md_trng_init_t structure which will be initialized.
  * @retval None
  */
void md_trng_struct_init(md_trng_init_t *init)
{
    init->data_width = MD_TRNG_DSEL_32B;
    init->seed_type  = MD_TRNG_SEED_TYPE_SEED;
    init->seed       = 12345678;
    init->t_start    = 30000;
    init->adjc       = 0;
}

/**
  *@brief  generate trng data
  *@param  RNGstate: Structure of the RNG stat
  *@param  tempdata: pointer to trng data
  *@param  Olength: the byte length of trng data
  *@retval MD_ERROR status: can be MD_OK if MD_OK or MD_ERROR if MD_ERROR occured
*/
md_status_t rnggen(rngstate_type_t *rng_state, uint8_t *rngpdata, uint32_t olength)
{
    uint32_t      i;
    uint8_t       j;

    /* select 1 */
    SET_BIT(TRNG->CR, TRNG_CR_TRNGSEL_MSK);

    /* start interrupt enable*/
    SET_BIT(TRNG->IER, TRNG_IER_START_MSK);

    /* valid data interrupt enable */
    SET_BIT(TRNG->IER, TRNG_IER_DAVLD_MSK);

    /* data error interrupt enable */
    SET_BIT(TRNG->IER, TRNG_IER_SERR_MSK);

    /* enable trng */
    SET_BIT(TRNG->CR, TRNG_CR_TRNGEN_MSK);

    /* wait initial state */
    while (!START_FINISH);

    START_FINISH = 0x0;

    if (rng_state->rngmode == RNG_DATA_BI)
    {
        for (i = 0; i < olength; i++)
        {
            *(rngpdata + i) = 0x0;

            for (j = 0; j < 8; j++)
            {
                while (!VALID_DATA);

                VALID_DATA = 0x0;

                if (ERROR_DATA)
                    return MD_ERROR;

                *(rngpdata + i) |= (READ_REG(TRNG->DR) << j);
            }
        }
    }

    if (rng_state->rngmode == RNG_DATA_BY)
    {
        for (i = 0; i < olength; i++)
        {
            while (!VALID_DATA);

            VALID_DATA = 0x0;

            if (ERROR_DATA)
                return MD_ERROR;

            *(rngpdata + i) = READ_REG(TRNG->DR);
        }
    }

    if (rng_state->rngmode == RNG_DATA_HW)
    {
        for (i = 0; i < olength / 2; i++)
        {
            for (j = 0; j < 2; j++)
            {
                while (!VALID_DATA);

                VALID_DATA = 0x0;

                if (ERROR_DATA)
                    return MD_ERROR;

                *(rngpdata + 2 * i + j) = READ_REG(TRNG->DR);
            }

        }

        if (olength % 2 != 0)
        {
            while (!VALID_DATA);

            VALID_DATA = 0x0;

            if (ERROR_DATA)
                return MD_ERROR;

            *(rngpdata + olength - 1) = READ_REG(TRNG->DR);
        }
    }

    if (rng_state->rngmode == RNG_DATA_W)
    {
        for (i = 0; i < olength / 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                while (!VALID_DATA);

                VALID_DATA = 0x0;

                if (ERROR_DATA)
                    return MD_ERROR;

                *(rngpdata + 4 * i + j) = READ_REG(TRNG->DR);
            }

        }

        if (olength % 4 == 1)
        {
            while (!VALID_DATA);

            VALID_DATA = 0x0;

            if (ERROR_DATA)
                return MD_ERROR;

            *(rngpdata + olength - 1) = READ_REG(TRNG->DR);
        }

        if (olength % 4 == 2)
        {
            for (j = 0; j < 2; j++)
            {
                while (!VALID_DATA);

                VALID_DATA = 0x0;

                if (ERROR_DATA)
                    return MD_ERROR;

                *(rngpdata + olength - 1) = READ_REG(TRNG->DR);
            }
        }

        if (olength % 4 == 3)
        {
            for (j = 0; j < 3; j++)
            {
                while (!VALID_DATA);

                VALID_DATA = 0x0;

                if (ERROR_DATA)
                    return MD_ERROR;

                *(rngpdata + olength - 1) = READ_REG(TRNG->DR);
            }
        }
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
  * @}
  */
/**
  * @}
  */

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
