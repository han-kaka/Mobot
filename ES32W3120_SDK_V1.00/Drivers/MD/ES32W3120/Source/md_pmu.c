/**********************************************************************************
 *
 * @file    md_pmu.c
 * @brief   Power management unit driver.
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
#include "md_pmu.h"
#include "md_rmu.h"
#include "md_syscfg.h"

/* Private Macros ------------------------------------------------------------ */
/* Private Variables --------------------------------------------------------- */
/* Public Variables ---------------------------------------------------------- */
/* Private Constants --------------------------------------------------------- */

/** @addtogroup Micro_Driver
  * @{
  */


/** @addtogroup MD_PMU
  * @{
  */

/* Private function prototypes ----------------------------------------------- */

/* Private Function ---------------------------------------------------------- */

/** @addtogroup MD_PMU_Public_Functions
  * @{
  */
/** @addtogroup MD_PMU_Public_Functions_Group1
  * @{
  */
/**
  * @brief  Reset the PMU register
  * @retval None
  */
void md_pmu_reset(void)
{
    SYSCFG_UNLOCK();
    WRITE_REG(PMU->CR, 0x0);
    WRITE_REG(PMU->LVDCR, 0x0);
    WRITE_REG(PMU->PWRCR, 0x17FF);
    SYSCFG_LOCK();

    return;
}

/**
  * @brief  Enter stop1 mode
  * @retval None
  */
void md_pmu_stop1_enter(void)
{
    SYSCFG_UNLOCK();
    MODIFY_REG(PMU->CR, PMU_CR_LPM_MSK, MD_PMU_LP_STOP1 << PMU_CR_LPM_POSS);
    SYSCFG_LOCK();

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

    SYSCFG_UNLOCK();
    md_rmu_disable_bor33();
    md_pmu_disable_ibias();
    SYSCFG_LOCK();

    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    __WFI();

    SYSCFG_UNLOCK();
    md_rmu_enable_bor33();
    md_pmu_enable_ibias();
    SYSCFG_LOCK();

    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

    return;
}

/**
  * @brief  Enter stop2 mode
  * @retval None
  */
void md_pmu_stop2_enter(void)
{
    SYSCFG_UNLOCK();
    MODIFY_REG(PMU->CR, PMU_CR_LPM_MSK, MD_PMU_LP_STOP2 << PMU_CR_LPM_POSS);
    SYSCFG_LOCK();

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

    SYSCFG_UNLOCK();
    md_rmu_disable_bor33();
    md_pmu_disable_ibias();
    SYSCFG_LOCK();

    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    __WFI();

    SYSCFG_UNLOCK();
    md_rmu_enable_bor33();
    md_pmu_enable_ibias();
    SYSCFG_LOCK();

    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

    return;
}

/**
  * @brief  Set standby mode wake up
  * @param  port: The port whick wake up the standby mode.
  * @param  level: Wakeup level.
  * @retval None
  */
void md_pmu_set_standby_wake_up(md_pmu_wakeup_port_t port, md_pmu_wakeup_level_t level)
{
    if (port == MD_PMU_STANDBY_PORT_SEL_NONE)
    {
        WRITE_REG(BKPC->PROT, 0x9669AA55);
        CLEAR_BIT(BKPC->WKR, BKPC_WKR_WKEN_MSK);
        WRITE_REG(BKPC->PROT, 0);
        return;
    }

    WRITE_REG(BKPC->PROT, 0x9669AA55);
    MODIFY_REG(BKPC->WKR, BKPC_WKR_WKEG_MSK, level << port);
    MODIFY_REG(BKPC->WKR, BKPC_WKR_WKEN_MSK, 1 << port);
    SET_BIT(BKPC->WKR, BKPC_WKR_WKEN_MSK);
    WRITE_REG(BKPC->PROT, 0);
}

/**
  * @brief  Enter standby mode
  * @retval None
  */
void md_pmu_standby_enter()
{
    SYSCFG_UNLOCK();
    MODIFY_REG(PMU->CR, PMU_CR_LPM_MSK, MD_PMU_LP_STANDBY << PMU_CR_LPM_POSS);
    SYSCFG_LOCK();

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

    SYSCFG_UNLOCK();
    md_rmu_disable_bor33();
    md_pmu_disable_ibias();
    SYSCFG_LOCK();

    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    __WFI();

    SYSCFG_UNLOCK();
    md_rmu_enable_bor33();
    md_pmu_enable_ibias();
    SYSCFG_LOCK();

    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

    return;
}

/**
  * @brief  Configure peripheral power
  * @param  perh: The peripheral
  * @param  state: ENABLE/DISABLE
  * @retval None
  */
void md_pmu_perh_power_config(md_pmu_perh_power_t perh, type_func_t state)
{
    SYSCFG_UNLOCK();

    if (state)
        SET_BIT(PMU->PWRCR, perh);
    else
        CLEAR_BIT(PMU->PWRCR, perh);

    SYSCFG_LOCK();
    return;
}

/**
  * @brief  Configure lvd using specified parameters.
  * @param  sel: LVD threshold voltage.
  * @param  mode: LVD trigger mode.
  * @param  state: New state, ENABLE/DISABLE;
  * @retval None
  */
void md_pmu_lvd_config(md_pmu_lvd_voltage_sel_t sel, md_pmu_lvd_trigger_mode_t mode, type_func_t state)
{
    SYSCFG_UNLOCK();

    if (state)
    {
        MODIFY_REG(PMU->LVDCR, PMU_LVDCR_LVDS_MSK, sel << PMU_LVDCR_LVDS_POSS);
        MODIFY_REG(PMU->LVDCR, PMU_LVDCR_LVIFS_MSK, mode << PMU_LVDCR_LVIFS_POSS);
        SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDFLT_MSK);
        SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDCIF_MSK);
        SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDIE_MSK);
        SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDEN_MSK);
    }
    else
    {
        SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDCIF_MSK);
        CLEAR_BIT(PMU->LVDCR, PMU_LVDCR_LVDIE_MSK);
        CLEAR_BIT(PMU->LVDCR, PMU_LVDCR_LVDEN_MSK);
    }

    SYSCFG_LOCK();
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
