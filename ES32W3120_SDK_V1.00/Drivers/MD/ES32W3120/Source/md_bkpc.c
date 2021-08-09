/**********************************************************************************
 *
 * @file    md_bkpc.c
 * @brief   Backup control unit driver.
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
#include "md_bkpc.h"


/** @addtogroup Micro_Driver
  * @{
  */

/** @addtogroup MD_BKPC
  * @{
  */

/** @addtogroup MD_BKPC_Public_Functions
  * @{
  */
/** @addtogroup MD_BKPC_Public_Functions_Group1
  * @{
  */
/**
  * @brief  Configure standby wakeup in backup field
  * @param  port: Wakeup port
  * @param  level: HIGH/LOW.
  * @retval None
  */
void md_bkpc_standby_wakeup_config(md_bkpc_wakeup_port_t port, md_bkpc_wakeup_level_t level)
{
	if (port == MD_PMU_STANDBY_PORT_SEL_NONE) {
		MD_BKPC_UNLOCK();
        CLEAR_BIT(BKPC->WKR, BKPC_WKR_WKEN_MSK);
		MD_BKPC_LOCK();
		return;
	}

	MD_BKPC_UNLOCK();
    MODIFY_REG(BKPC->WKR, BKPC_WKR_WKEG_MSK, level<<port);
    MODIFY_REG(BKPC->WKR, BKPC_WKR_WKEN_MSK, 1<<port);
    SET_BIT(BKPC->WKR, BKPC_WKR_WKEN_MSK);
	MD_BKPC_LOCK();

	return;
}

/**
  * @brief  Configure rtc clock in backup field
  * @param  clock: Clock
  * @retval None
  */
void md_bkpc_rtc_clock_config(md_bkpc_preh_clk_t clock)
{
	MD_BKPC_UNLOCK();
	MODIFY_REG(BKPC->PCCR, BKPC_PCCR_RTCCK_MSK, clock << BKPC_PCCR_RTCCK_POS);
	MD_BKPC_LOCK();

	return;
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
