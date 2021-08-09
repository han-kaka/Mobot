/**********************************************************************************
 *
 * @file    md_i2c.c
 * @brief   I2C module driver.
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
#include "md_i2c.h"
#include "md_cmu.h"

/** @addtogroup Micro_Driver
  * @{
  */

/** @defgroup MD_I2C I2C
  * @{
  */

/** @addtogroup MD_I2C_Public_Functions
  * @{
  */

/** @addtogroup MD_I2C_Public_Functions_Group1
  * @{
  */
/**
 * @brief  I2C Configuration Speed function.      
  * @param  I2Cx: I2C instance.
  * @param  init: Pointer to a i2c_init_t structure that contains
  *                the configuration information for the specified I2C.
 * @param  freq: I2C Peripheral bus clock
 * @retval Status, see @ref md_status_t.
 */
static void _i2c_speed_init(I2C_TypeDef *I2Cx, md_i2c_init_t *init, uint32_t freq)
{
	float Tsync, Tscl, Tfre;
	uint32_t Tper, tmp, presc = 0;

	if (init->module == MD_I2C_MODULE_SLAVE) {
		init->clk_speed = 450000;
	}

	if (init->clk_speed <= 100000) {
		tmp  = freq / 4000000;
		freq = 4000000;
	} else {
		tmp  = freq / 8000000;
		freq = 8000000;
	}

	Tscl = 1000.0 / (init->clk_speed / 1000000.0);
	Tfre = 1000.0 / (freq / 1000000);

	Tsync = (READ_BITS(I2Cx->CON2, I2C_CON1_DNF_MSK, I2C_CON1_DNF_POSS) + 2) * 2 * Tfre;
	Tper  = (uint32_t)((Tscl - Tsync) / Tfre);

	while (Tper > 512) {
		Tper -= 512;
		++presc;
	}

	MODIFY_REG(I2Cx->TIMINGR, I2C_TIMINGR_PRESC_MSK, (presc + tmp ) << I2C_TIMINGR_PRESC_POSS);

	if (init->clk_speed <= MD_I2C_STANDARD_MODE_MAX_CLK) {
		MODIFY_REG(I2Cx->TIMINGR, I2C_TIMINGR_SDADEL_MSK, 2 << I2C_TIMINGR_SDADEL_POSS);
		MODIFY_REG(I2Cx->TIMINGR, I2C_TIMINGR_SCLDEL_MSK, 4 << I2C_TIMINGR_SCLDEL_POSS);
		MODIFY_REG(I2Cx->TIMINGR, I2C_TIMINGR_SCLH_MSK, (((Tper - 2) / 2) - 4) << I2C_TIMINGR_SCLH_POSS);
		MODIFY_REG(I2Cx->TIMINGR, I2C_TIMINGR_SCLL_MSK, (((Tper - 2) / 2) + 4) << I2C_TIMINGR_SCLL_POSS);
	}
	else {
		if (init->clk_speed <= MD_I2C_FAST_MODE_MAX_CLK) {
			MODIFY_REG(I2Cx->TIMINGR, I2C_TIMINGR_SDADEL_MSK, 2 << I2C_TIMINGR_SDADEL_POSS);
			MODIFY_REG(I2Cx->TIMINGR, I2C_TIMINGR_SCLDEL_MSK, 3 << I2C_TIMINGR_SCLDEL_POSS);
			MODIFY_REG(I2Cx->TIMINGR, I2C_TIMINGR_SCLH_MSK, (((Tper - 2) / 2) - 6) << I2C_TIMINGR_SCLH_POSS);
			MODIFY_REG(I2Cx->TIMINGR, I2C_TIMINGR_SCLL_MSK, (((Tper - 2) / 2) + 6) << I2C_TIMINGR_SCLL_POSS);
		}
		else {
			MODIFY_REG(I2Cx->TIMINGR, I2C_TIMINGR_SDADEL_MSK, 0 << I2C_TIMINGR_SDADEL_POSS);
			MODIFY_REG(I2Cx->TIMINGR, I2C_TIMINGR_SCLDEL_MSK, 1 << I2C_TIMINGR_SCLDEL_POSS);
			MODIFY_REG(I2Cx->TIMINGR, I2C_TIMINGR_SCLH_MSK, (((Tper - 2) / 2) - 3) << I2C_TIMINGR_SCLH_POSS);
			MODIFY_REG(I2Cx->TIMINGR, I2C_TIMINGR_SCLL_MSK, (((Tper - 2) / 2) + 3) << I2C_TIMINGR_SCLL_POSS);
		}
	}

	return;
}

/**
  * @brief  Initializes the I2C according to the specified parameters
  *         in the i2c_init_t and initialize the associated handle.
  * @param  I2Cx: I2C instance.
  * @param  init: Pointer to a i2c_init_t structure that contains
  *                the configuration information for the specified I2C.
  * @retval Status, see @ref md_status_t.
  */
md_status_t md_i2c_init(I2C_TypeDef *I2Cx, md_i2c_init_t *init)
{
	uint32_t freq;

	if ((I2Cx == NULL) || (init == NULL))
		return MD_ERROR;

	freq = md_cmu_get_pclk1_clock();
	MD_I2C_DISABLE(I2Cx);

	_i2c_speed_init(I2Cx, init, freq);
	MODIFY_REG(I2Cx->CON1, I2C_CON1_NOSTRETCH_MSK, (init->no_stretch) << I2C_CON1_NOSTRETCH_POS);
	MODIFY_REG(I2Cx->CON1, I2C_CON1_GCEN_MSK, (init->general_call) << I2C_CON1_GCEN_POS);

	if (init->dual_addr == MD_I2C_DUALADDR_ENABLE) {
		CLEAR_BIT(I2Cx->ADDR1, I2C_ADDR1_OA1EN_MSK);
		MODIFY_REG(I2Cx->ADDR1, I2C_ADDR1_OA1_MSK, (init->own_addr1 & 0x3FF) << I2C_ADDR1_OA1_POSS);
		SET_BIT(I2Cx->ADDR1, I2C_ADDR1_OA1EN_MSK);

		CLEAR_BIT(I2Cx->ADDR2, I2C_ADDR2_OA2EN_MSK);
		MODIFY_REG(I2Cx->ADDR2, I2C_ADDR2_OA2_MSK, (init->own_addr2 & 0x7F) << I2C_ADDR2_OA2_POSS);
		SET_BIT(I2Cx->ADDR2, I2C_ADDR2_OA2EN_MSK);
	} else {
		if (init->addr_mode == MD_I2C_ADDR_10BIT) {
			CLEAR_BIT(I2Cx->ADDR1, I2C_ADDR1_OA1EN_MSK);
			SET_BIT(I2Cx->ADDR1, I2C_ADDR1_OA1MODE_MSK);
			MODIFY_REG(I2Cx->ADDR1, I2C_ADDR1_OA1_MSK, (init->own_addr1 & 0x3FF) << I2C_ADDR1_OA1_POSS);
			SET_BIT(I2Cx->ADDR1, I2C_ADDR1_OA1EN_MSK);
		}
		else {
			CLEAR_BIT(I2Cx->ADDR2, I2C_ADDR2_OA2EN_MSK);
			MODIFY_REG(I2Cx->ADDR2, I2C_ADDR2_OA2_MSK, (init->own_addr2 & 0x7F) << I2C_ADDR2_OA2_POSS);
			SET_BIT(I2Cx->ADDR2, I2C_ADDR2_OA2EN_MSK);
		}
	}

	MD_I2C_ENABLE(I2Cx);
	return MD_OK;
}

/**
  * @brief  Set each @ref md_i2c_init_t field to default value.
  * @param  init Pointer to a @ref md_i2c_init_t structure.
  * @retval None
  */
void md_i2c_struct_init(md_i2c_init_t *init)
{
	init->module       = MD_I2C_MODULE_MASTER;
	init->clk_speed    = MD_I2C_STANDARD_MODE_MAX_CLK;
	init->own_addr1    = 0xA0;
	init->addr_mode    = MD_I2C_ADDR_7BIT;
	init->dual_addr    = MD_I2C_DUALADDR_DISABLE;
	init->own_addr2    = 0x0;
	init->general_call = MD_I2C_GENERALCALL_DISABLE;
	init->no_stretch   = MD_I2C_NOSTRETCH_ENABLE;
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
