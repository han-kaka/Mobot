/**********************************************************************************
 *
 * @file    md_lptim.c
 * @brief   RTC module driver.
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
#include "md_lptim.h"

/** @addtogroup Micro_Driver
  * @{
  */



/** @addtogroup MD_LPTIM
  * @{
  */

/** @addtogroup MD_LPTIM_Public_Functions
  * @{
  */
/** @addtogroup MD_LPTIM_Public_Functions_Group1
  * @{
  */

/**
  * @brief  Initializes the LPTIM peripheral and normal group according to
  *         parameters specified in structure LPTIM_TypeDef.
  * @param  LPTx: LPTIM Instance.
  * @param  init: Pointer to a md_lptim_init_t structure that contains
  *         the configuration information for the specified ADC module.
  * @retval md_status_t, see @ref md_status_t.
  */
md_status_t md_lptim_base_init(LPTIM_TypeDef *LPTx, md_lptim_init_t *init)
{
	WRITE_REG(LPTx->UPDATE, 1);
	MODIFY_REG(LPTx->CON0, LP16T_CON0_PRESC_MSK, (init->psc) << LP16T_CON0_PRESC_POSS);
	WRITE_REG(LPTx->ARR, init->arr);
	WRITE_REG(LPTx->CMP, init->cmp);
	WRITE_REG(LPTx->UPDATE, 0);

	while (READ_BIT(LPTx->SYNCSTAT, LP16T_SYNCSTAT_ARRWBSY_MSK));
	while (READ_BIT(LPTx->SYNCSTAT, LP16T_SYNCSTAT_CMPWBSY_MSK));
	return MD_OK;
}

/**
  * @brief  Set each @ref md_lptim_init_t field to default value.
  * @param  init: Pointer to a @ref md_lptim_init_t structure
  *                whose fields will be set to default values.
  * @retval None
  */
void md_lptim_struct_init(md_lptim_init_t *init)
{
	init->psc   = MD_LPTIM_PRESC_1;
	init->arr   = 0x0FFF;
	init->mode  = MD_LPTIM_MODE_CONTINUOUS;
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
