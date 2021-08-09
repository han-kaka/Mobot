/**********************************************************************************
 *
 * @file    md_rmu.c
 * @brief   Reset management unit driver.
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
#include "md_rmu.h"
#include "md_syscfg.h"

/* Private Macros ------------------------------------------------------------ */
/* Private Variables --------------------------------------------------------- */
/* Public Variables ---------------------------------------------------------- */
/* Private Constants --------------------------------------------------------- */

/** @addtogroup Micro_Driver
  * @{
  */

/** @addtogroup MD_RMU
  * @{
  */

/* Private function prototypes ----------------------------------------------- */

/* Private Function ---------------------------------------------------------- */

/** @addtogroup MD_RMU_Public_Functions
  * @{
  */
/** @addtogroup MD_RMU_Public_Functions_Group1
  * @{
  */
/**
  * @brief  Reset the RMU register
  * @retval None
  */
void md_rmu_reset(void)
{
    SYSCFG_UNLOCK();
    WRITE_REG(RMU->CSR, 0x0);
    WRITE_REG(RMU->CRSTSR, 0xFFFF);
    WRITE_REG(RMU->AHB1RSTR, 0x0);
    WRITE_REG(RMU->AHB2RSTR, 0x0);
    WRITE_REG(RMU->APB1RSTR, 0x0);
    WRITE_REG(RMU->APB2RSTR, 0x0);
    SYSCFG_LOCK();

    return;
}

/**
  * @brief  Configure BOR parameters.
  * @param  flt: filter time.
  * @param  vol: The voltage.
  * @param  state: The new status: ENABLE/DISABLE.
  * @retval None
  */
void md_rmu_bor_config(md_rmu_bor_filter_t flt, md_rmu_bor33_vol_t vol33, md_rmu_bor11_vol_t vol11)
{
    SYSCFG_UNLOCK();

    if (vol33 != MD_RMU_VOL33_DISABLE)
    {
        MODIFY_REG(RMU->CSR, RMU_CSR_BOR33VS_MSK, vol33 << RMU_CSR_BOR33VS_POSS);
        SET_BIT(RMU->CSR, RMU_CSR_BOR33EN_POS);
    }
    else
    {
        CLEAR_BIT(RMU->CSR, RMU_CSR_BOR33EN_POS);
    }

    if (vol11 != MD_RMU_VOL11_DISABLE)
    {
        MODIFY_REG(RMU->CSR, RMU_CSR_BOR09VS_MSK, vol11 << RMU_CSR_BOR09VS_POSS);
        SET_BIT(RMU->CSR, RMU_CSR_BOR09EN_POS);
    }
    else
    {
        CLEAR_BIT(RMU->CSR, RMU_CSR_BOR09EN_POS);
    }

    MODIFY_REG(RMU->CSR, RMU_CSR_BORFLT_MSK, flt << RMU_CSR_BORFLT_POSS);

    SYSCFG_LOCK();
    return;
}

/**
  * @brief  Get specified reset status
  * @param  state: Speicifies the type of the reset,
  * @retval The status.
  */
uint32_t md_rmu_get_reset_status(md_rmu_state_t state)
{
    if (state == MD_RMU_RST_ALL)
        return RMU->RSTSR;

    if (READ_BIT(RMU->RSTSR, state))
        return SET;

    return RESET;
}

/**
  * @brief  Clear the specified reset status
  * @param  state: Specifies the type of the reset,
  * @retval None
  */
void md_rmu_clear_reset_status(md_rmu_state_t state)
{
    SYSCFG_UNLOCK();
    WRITE_REG(RMU->CRSTSR, state);
    SYSCFG_LOCK();

    return;
}
/**
  * @brief  Reset peripheral device
  * @param  perh: The peripheral device,
  * @retval None
  */
void md_rmu_reset_periperal(md_rmu_peripheral_t perh)
{
    uint32_t idx, pos;

    idx = ((uint32_t)perh >> 27) & 0x7;
    pos = perh & ~(0x7 << 27);
    SYSCFG_UNLOCK();

    switch (idx)
    {
        case 0:
            WRITE_REG(RMU->AHB1RSTR, pos);
            break;

        case 1:
            WRITE_REG(RMU->AHB2RSTR, pos);
            break;

        case 2:
            WRITE_REG(RMU->APB1RSTR, pos);
            break;

        case 4:
            WRITE_REG(RMU->APB2RSTR, pos);
            break;

        case 5:
            WRITE_REG(RMU->APB3RSTR, pos);

        case 6:
            WRITE_REG(RMU->AHB2BLERSTR, pos);

        default:
            break;
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
