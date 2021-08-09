/**********************************************************************************
 *
 * @file    md_cmu.h
 * @brief   Header file of CMU module driver.
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


#ifndef __MD_CMU_H__
#define __MD_CMU_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------ */

#include "md_utils.h"

/* Exported Macros ----------------------------------------------------------- */

/* Exported Variables -------------------------------------------------------- */

/* Exported Constants -------------------------------------------------------- */

/** @addtogroup Micro_Driver
  * @{
  */
/** @addtogroup MD_CMU 
  * @{
  */
/* Exported Types ------------------------------------------------------------ */

/** @defgroup MD_CMU_MD_Public_Types CMU Public Types
  * @{
  */

/**
  * @brief CMU state structure definition
  */
typedef enum
{
    MD_CMU_CLOCK_HRC  = 0x1U,   /**< HRC */
    MD_CMU_CLOCK_PLL1 = 0x4U,   /**< PLL1 */
    MD_CMU_CLOCK_HOSC = 0x5U,   /**< HOSC */
    MD_CMU_CLOCK_LSCLK = 0x6U,  /**< LSCLK */
} md_cmu_clock_t;

/**
  * @brief Frequency division select bit
  */
typedef enum
{
    MD_CMU_DIV_1    = 0x0U,     /**< Division by 1 */
    MD_CMU_DIV_2    = 0x1U,     /**< Division by 2 */
    MD_CMU_DIV_4    = 0x2U,     /**< Division by 4 */
    MD_CMU_DIV_8    = 0x3U,     /**< Division by 8 */
    MD_CMU_DIV_16   = 0x4U,     /**< Division by 16 */
    MD_CMU_DIV_32   = 0x5U,     /**< Division by 32 */
    MD_CMU_DIV_64   = 0x6U,     /**< Division by 64 */
    MD_CMU_DIV_128  = 0x7U,     /**< Division by 128 */
    MD_CMU_DIV_256  = 0x8U,     /**< Division by 256 */
    MD_CMU_DIV_512  = 0x9U,     /**< Division by 512 */
    MD_CMU_DIV_1024 = 0xAU,     /**< Division by 1024 */
    MD_CMU_DIV_2048 = 0xBU,     /**< Division by 2048 */
    MD_CMU_DIV_4096 = 0xCU,     /**< Division by 4096 */
} md_cmu_div_t;

/**
  * @brief Bus type
  */
typedef enum
{
    MD_CMU_HCLK_1 = 0x0U,       /**< AHB1 bus */
    MD_CMU_SYS    = 0x1U,       /**< SYS bus */
    MD_CMU_PCLK_1 = 0x2U,       /**< APB1 bus */
    MD_CMU_PCLK_2 = 0x3U,       /**< APB2 bus */
} md_cmu_bus_t;
/**
  * @}
  */

/* Exported Functions -------------------------------------------------------- */

/** @defgroup MD_CMU_Public_Functions CMU Public Functions
  * @{
  */
/** @defgroup MD_CMU_Public_Functions_Group2 CSR
  * @{
  */
/**
  * @brief  Configure system clock.
  * @param  clk: Clock parameter. can be one of the following values:
  *         @arg @ref MD_CMU_CLOCK_HRC
  *         @arg @ref MD_CMU_CLOCK_LSCLK
  *         @arg @ref MD_CMU_CLOCK_PLL1
  *         @arg @ref MD_CMU_CLOCK_HOSC
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_config_clock(md_cmu_clock_t clk)
{
    MODIFY_REG(CMU->CSR, CMU_CSR_SYS_CMD_MSK, clk);
}

/**
  * @brief  Get system clock.
  * @retval Current system clock. Can be one of the following values:
  *         @arg @ref MD_CMU_CLOCK_HRC
  *         @arg @ref MD_CMU_CLOCK_LSCLK
  *         @arg @ref MD_CMU_CLOCK_PLL1
  *         @arg @ref MD_CMU_CLOCK_HOSC
  */
__STATIC_INLINE uint32_t md_cmu_get_current_clock(void)
{
    return READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS);
}

/**
  * @brief  Get Status of switch clock.
  * @retval Status:
  *         - 0: Ready
  *         - 1: Busy
  */
__STATIC_INLINE uint32_t md_cmu_get_sys_rdyn(void)
{
    return READ_BITS(CMU->CSR, CMU_CSR_SYS_RDYN_MSK, CMU_CSR_SYS_RDYN_POS);
}

/**
  * @brief  Configure system clock filter.
  * @param  cft: Value of the following:
  *         - 0x55: Select system clock
  *         - 0xAA: Select shadow clock
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_config_cft(uint32_t cft)
{
    MODIFY_REG(CMU->CSR, CMU_CSR_CFT_CMD_MSK, cft << CMU_CSR_CFT_CMD_POSS);
}

/**
  * @brief  Get system clock.
  * @retval Current filter clock:
  *         - 0: Select system clock
  *         - 1: Select shadow clock
  */
__STATIC_INLINE uint32_t md_cmu_get_active_filter(void)
{
    return READ_BITS(CMU->CSR, CMU_CSR_CFT_STU_MSK, CMU_CSR_CFT_STU_POS);
}

/**
  * @brief  Get Status of switch filter clock.
  * @retval Status:
  *         - 0: Ready
  *         - 1: Busy
  */
__STATIC_INLINE uint32_t md_cmu_get_cft_rdyn(void)
{
    return READ_BITS(CMU->CSR, CMU_CSR_CFT_RDYN_MSK, CMU_CSR_CFT_RDYN_POS);
}
/**
  * @}
  */
/** @defgroup MD_CMU_Public_Functions_Group3 CFGR
  * @{
  */
/**
  * @brief  Sets HCLK1 divider.
  * @param  div: Value of the following:
  *         - 0x0: Fclk / 1
  *         - 0x1: Fclk / 2
  *         - 0x2: Fclk / 4
  *         - 0x3: Fclk / 8
  *         - 0x4: Fclk / 16
  *         - 0x5: Fclk / 32
  *         - 0x6: Fclk / 64
  *         - 0x7: Fclk / 128
  *         - 0x8: Fclk / 256
  *         - 0x9: Fclk / 512
  *         - 0xA: Fclk / 1024
  *         - 0xB: Fclk / 2048
  *         - 0xC: Fclk / 4096
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_set_hclk1_div(uint32_t div)
{
    MODIFY_REG(CMU->CFGR, CMU_CFGR_HCLK1DIV_MSK, div << CMU_CFGR_HCLK1DIV_POSS);
}

/**
  * @brief  Gets HCLK1 divider.
  * @retval  divider: Value of the following:
  *         - 0x0: Fclk / 1
  *         - 0x1: Fclk / 2
  *         - 0x2: Fclk / 4
  *         - 0x3: Fclk / 8
  *         - 0x4: Fclk / 16
  *         - 0x5: Fclk / 32
  *         - 0x6: Fclk / 64
  *         - 0x7: Fclk / 128
  *         - 0x8: Fclk / 256
  *         - 0x9: Fclk / 512
  *         - 0xA: Fclk / 1024
  *         - 0xB: Fclk / 2048
  *         - 0xC: Fclk / 4096
  */
__STATIC_INLINE uint32_t md_cmu_get_hclk1_div(void)
{
    return READ_BITS(CMU->CFGR, CMU_CFGR_HCLK1DIV_MSK, CMU_CFGR_HCLK1DIV_POSS);
}

/**
  * @brief  Sets PCLK1 divider.
  * @param  div: Value of the following:
  *         - 0x0: Fclk / 1
  *         - 0x1: Fclk / 2
  *         - 0x2: Fclk / 4
  *         - 0x3: Fclk / 8
  *         - 0x4: Fclk / 16
  *         - 0x5: Fclk / 32
  *         - 0x6: Fclk / 64
  *         - 0x7: Fclk / 128
  *         - 0x8: Fclk / 256
  *         - 0x9: Fclk / 512
  *         - 0xA: Fclk / 1024
  *         - 0xB: Fclk / 2048
  *         - 0xC: Fclk / 4096
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_set_pclk1_div(uint32_t div)
{
    MODIFY_REG(CMU->CFGR, CMU_CFGR_PCLK1DIV_MSK, div << CMU_CFGR_PCLK1DIV_POSS);
}

/**
  * @brief  Gets PCLK1 divider.
  * @retval  divider: Value of the following:
  *         - 0x0: Fclk / 1
  *         - 0x1: Fclk / 2
  *         - 0x2: Fclk / 4
  *         - 0x3: Fclk / 8
  *         - 0x4: Fclk / 16
  *         - 0x5: Fclk / 32
  *         - 0x6: Fclk / 64
  *         - 0x7: Fclk / 128
  *         - 0x8: Fclk / 256
  *         - 0x9: Fclk / 512
  *         - 0xA: Fclk / 1024
  *         - 0xB: Fclk / 2048
  *         - 0xC: Fclk / 4096
  */
__STATIC_INLINE uint32_t md_cmu_get_pclk1_div(void)
{
    return READ_BITS(CMU->CFGR, CMU_CFGR_PCLK1DIV_MSK, CMU_CFGR_PCLK1DIV_POSS);
}

/**
  * @brief  Sets PCLK2 divider.
  * @param  div: Value of the following:
  *         - 0x0: Fclk / 1
  *         - 0x1: Fclk / 2
  *         - 0x2: Fclk / 4
  *         - 0x3: Fclk / 8
  *         - 0x4: Fclk / 16
  *         - 0x5: Fclk / 32
  *         - 0x6: Fclk / 64
  *         - 0x7: Fclk / 128
  *         - 0x8: Fclk / 256
  *         - 0x9: Fclk / 512
  *         - 0xA: Fclk / 1024
  *         - 0xB: Fclk / 2048
  *         - 0xC: Fclk / 4096
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_set_pclk2_div(uint32_t div)
{
    MODIFY_REG(CMU->CFGR, CMU_CFGR_PCLK2DIV_MSK, div << CMU_CFGR_PCLK2DIV_POSS);
}

/**
  * @brief  Gets PCLK2 divider.
  * @retval  divider: Value of the following:
  *         - 0x0: Fclk / 1
  *         - 0x1: Fclk / 2
  *         - 0x2: Fclk / 4
  *         - 0x3: Fclk / 8
  *         - 0x4: Fclk / 16
  *         - 0x5: Fclk / 32
  *         - 0x6: Fclk / 64
  *         - 0x7: Fclk / 128
  *         - 0x8: Fclk / 256
  *         - 0x9: Fclk / 512
  *         - 0xA: Fclk / 1024
  *         - 0xB: Fclk / 2048
  *         - 0xC: Fclk / 4096
  */
__STATIC_INLINE uint32_t md_cmu_get_pclk2_div(void)
{
    return READ_BITS(CMU->CFGR, CMU_CFGR_PCLK2DIV_MSK, CMU_CFGR_PCLK2DIV_POSS);
}

/**
  * @brief  Sets HRC frequency
  * @param  freq: Value of the following:
  *         - 0x0: 24MHz
  *         - 0x1: 2MHz
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_set_hrc_freq(uint32_t freq)
{
    MODIFY_REG(CMU->CFGR, CMU_CFGR_HRCFSW_MSK, freq << CMU_CFGR_HRCFSW_POS);
}

/**
  * @brief  Gets HRC frequency
  * @retval  freq: Value of the following:
  *         - 0x0: 24MHz
  *         - 0x1: 2MHz
  */
__STATIC_INLINE uint32_t md_cmu_get_hrc_freq(void)
{
    return READ_BITS(CMU->CFGR, CMU_CFGR_HRCFST_MSK, CMU_CFGR_HRCFST_POS);
}
/**
  * @}
  */
/** @defgroup MD_CMU_Public_Functions_Group4 CLKENR
  * @{
  */
/**
  * @brief  Enable HOSC
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_enable_hosc(void)
{
    SET_BIT(CMU->CLKENR, CMU_CLKENR_HOSCEN_MSK);
}

/**
  * @brief  Disable HOSC
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_disable_hosc(void)
{
    CLEAR_BIT(CMU->CLKENR, CMU_CLKENR_HOSCEN_MSK);
}

/**
  * @brief  Gets HOSC status
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_hosc(void)
{
    return READ_BITS(CMU->CLKENR, CMU_CLKENR_HOSCEN_MSK, CMU_CLKENR_HOSCEN_POS);
}

/**
  * @brief  Enable HRC
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_enable_hrc(void)
{
    SET_BIT(CMU->CLKENR, CMU_CLKENR_HRCEN_MSK);
}

/**
  * @brief  Disable HRC
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_disable_hrc(void)
{
    CLEAR_BIT(CMU->CLKENR, CMU_CLKENR_HRCEN_MSK);
}

/**
  * @brief  Gets HRC status
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_hrc(void)
{
    return READ_BITS(CMU->CLKENR, CMU_CLKENR_HRCEN_MSK, CMU_CLKENR_HRCEN_POS);
}

/**
  * @brief  Enable LRC
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_enable_lrc(void)
{
    SET_BIT(CMU->CLKENR, CMU_CLKENR_LRCEN_MSK);
}

/**
  * @brief  Disable LRC
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_disable_lrc(void)
{
    CLEAR_BIT(CMU->CLKENR, CMU_CLKENR_LRCEN_MSK);
}

/**
  * @brief  Gets LRC status
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_lrc(void)
{
    return READ_BITS(CMU->CLKENR, CMU_CLKENR_LRCEN_MSK, CMU_CLKENR_LRCEN_POS);
}

/**
  * @brief  Enable HOSCB
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_enable_hoscb(void)
{
    SET_BIT(CMU->CLKENR, CMU_CLKENR_HOSCBEN_MSK);
}

/**
  * @brief  Disable HOSCB
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_disable_hoscb(void)
{
    CLEAR_BIT(CMU->CLKENR, CMU_CLKENR_HOSCBEN_MSK);
}

/**
  * @brief  Gets HOSCB status
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_hoscb(void)
{
    return READ_BITS(CMU->CLKENR, CMU_CLKENR_HOSCBEN_MSK, CMU_CLKENR_HOSCBEN_POS);
}

/**
  * @brief  Enable PLL1
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_enable_pll1(void)
{
    SET_BIT(CMU->CLKENR, CMU_CLKENR_PLL1EN_MSK);
}

/**
  * @brief  Disable PLL1
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_disable_pll1(void)
{
    CLEAR_BIT(CMU->CLKENR, CMU_CLKENR_PLL1EN_MSK);
}

/**
  * @brief  Gets PLL1 status
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_pll1(void)
{
    return READ_BITS(CMU->CLKENR, CMU_CLKENR_PLL1EN_MSK, CMU_CLKENR_PLL1EN_POS);
}

/**
  * @brief  Enable PLL1_96M
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_enable_pll196m(void)
{
    SET_BIT(CMU->CLKENR, CMU_CLKENR_PLL1EN_96M_MSK);
}

/**
  * @brief  Disable PLL1_96M
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_disable_pll196m(void)
{
    CLEAR_BIT(CMU->CLKENR, CMU_CLKENR_PLL1EN_96M_MSK);
}

/**
  * @brief  Gets PLL1_96M status
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_pll196m(void)
{
    return READ_BITS(CMU->CLKENR, CMU_CLKENR_PLL1EN_96M_MSK, CMU_CLKENR_PLL1EN_96M_POS);
}

/**
  * @brief  Enable HOSC
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_enable_hoschps(void)
{
    SET_BIT(CMU->CLKENR, CMU_CLKENR_HOSCHPS_MSK);
}

/**
  * @brief  Disable HOSC
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_disable_hoschps(void)
{
    CLEAR_BIT(CMU->CLKENR, CMU_CLKENR_HOSCHPS_MSK);
}

/**
  * @brief  Gets HOSC status
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_hoschps(void)
{
    return READ_BITS(CMU->CLKENR, CMU_CLKENR_HOSCHPS_MSK, CMU_CLKENR_HOSCHPS_POS);
}
/**
  * @}
  */
/** @defgroup MD_CMU_Public_Functions_Group5 CLKSR
  * @{
  */
/**
  * @brief  Check the HOSC is active.
  * @retval Status:
  *         - 0: Not active
  *         - 1: Active
  */
__STATIC_INLINE uint32_t md_cmu_is_active_state_hosc(void)
{
    return READ_BITS(CMU->CLKSR, CMU_CLKSR_HOSCACT_MSK, CMU_CLKSR_HOSCACT_POS);
}

/**
  * @brief  Check the LOSC is active.
  * @retval Status:
  *         - 0: Not active
  *         - 1: Active
  */
__STATIC_INLINE uint32_t md_cmu_is_active_state_losc(void)
{
    return READ_BITS(CMU->CLKSR, CMU_CLKSR_LOSCACT_MSK, CMU_CLKSR_LOSCACT_POS);
}

/**
  * @brief  Check the HRC is active.
  * @retval Status:
  *         - 0: Not active
  *         - 1: Active
  */
__STATIC_INLINE uint32_t md_cmu_is_active_state_hrc(void)
{
    return READ_BITS(CMU->CLKSR, CMU_CLKSR_HRCACT_MSK, CMU_CLKSR_HRCACT_POS);
}

/**
  * @brief  Check the LRC is active.
  * @retval Status:
  *         - 0: Not active
  *         - 1: Active
  */
__STATIC_INLINE uint32_t md_cmu_is_active_state_lrc(void)
{
    return READ_BITS(CMU->CLKSR, CMU_CLKSR_LRCACT_MSK, CMU_CLKSR_LRCACT_POS);
}

/**
  * @brief  Check the ULRC is active.
  * @retval Status:
  *         - 0: Not active
  *         - 1: Active
  */
__STATIC_INLINE uint32_t md_cmu_is_active_state_ulrc(void)
{
    return READ_BITS(CMU->CLKSR, CMU_CLKSR_ULRCACT_MSK, CMU_CLKSR_ULRCACT_POS);
}

/**
  * @brief  Check the PLL1 is active.
  * @retval Status:
  *         - 0: Not active
  *         - 1: Active
  */
__STATIC_INLINE uint32_t md_cmu_is_active_state_pll1(void)
{
    return READ_BITS(CMU->CLKSR, CMU_CLKSR_PLL1ACT_MSK, CMU_CLKSR_PLL1ACT_POS);
}

/**
  * @brief  Check the HOSC is stable.
  * @retval Status:
  *         - 0: Not stable
  *         - 1: Stable
  */
__STATIC_INLINE uint32_t md_cmu_is_stable_state_hosc(void)
{
    return READ_BITS(CMU->CLKSR, CMU_CLKSR_HOSCRDY_MSK, CMU_CLKSR_HOSCRDY_POS);
}

/**
  * @brief  Check the LOSC is stable.
  * @retval Status:
  *         - 0: Not stable
  *         - 1: Stable
  */
__STATIC_INLINE uint32_t md_cmu_is_stable_state_losc(void)
{
    return READ_BITS(CMU->CLKSR, CMU_CLKSR_LOSCRDY_MSK, CMU_CLKSR_LOSCRDY_POS);
}

/**
  * @brief  Check the HRC is stable.
  * @retval Status:
  *         - 0: Not stable
  *         - 1: Stable
  */
__STATIC_INLINE uint32_t md_cmu_is_stable_state_hrc(void)
{
    return READ_BITS(CMU->CLKSR, CMU_CLKSR_HRCRDY_MSK, CMU_CLKSR_HRCRDY_POS);
}

/**
  * @brief  Check the LRC is stable.
  * @retval Status:
  *         - 0: Not stable
  *         - 1: Stable
  */
__STATIC_INLINE uint32_t md_cmu_is_stable_state_lrc(void)
{
    return READ_BITS(CMU->CLKSR, CMU_CLKSR_LRCRDY_MSK, CMU_CLKSR_LRCRDY_POS);
}

/**
  * @brief  Check the ULRC is stable.
  * @retval Status:
  *         - 0: Not stable
  *         - 1: Stable
  */
__STATIC_INLINE uint32_t md_cmu_is_stable_state_ulrc(void)
{
    return READ_BITS(CMU->CLKSR, CMU_CLKSR_ULRCRDY_MSK, CMU_CLKSR_ULRCRDY_POS);
}

/**
  * @brief  Check the PLL1 is stable.
  * @retval Status:
  *         - 0: Not stable
  *         - 1: Stable
  */
__STATIC_INLINE uint32_t md_cmu_is_stable_state_pll1(void)
{
    return READ_BITS(CMU->CLKSR, CMU_CLKSR_PLL1RDY_MSK, CMU_CLKSR_PLL1RDY_POS);
}

/**
  * @brief  Sets output clock of PLL1 input clock div.
  * @param  clk: The value of following:
  *         range 1 - 63
  *         example: if HOSC is 32M, then clk is 32.
  * @retval None
  */
__STATIC_INLINE void md_cmu_set_pll1_rdiv(uint32_t clk)
{
    MODIFY_REG(CMU->PLLCFG, CMU_PLLCFG_PLL1RDIV_MSK, clk << CMU_PLLCFG_PLL1RDIV_POSS);
}

/**
  * @brief  Sets output clock of PLL1 test pin port.
  * @param  clk: The value of following:
  *         - 0x0: x6 (96MHz)
  *         - 0x1: x3 (48MHz)
  * @retval None
  */
__STATIC_INLINE void md_cmu_set_pll1_output(uint32_t clk)
{
    MODIFY_REG(CMU->PLLCFG, CMU_PLLCFG_PLL1OS_MSK, clk << CMU_PLLCFG_PLL1OS_POSS);
}

/**
  * @brief  Gets output clock of PLL1 test pin port.
  * @retval The value of following:
  *         - 0x0: x6 (96MHz)
  *         - 0x1: x3 (48MHz)
  */
__STATIC_INLINE uint32_t md_cmu_get_pll1_output(void)
{
    return READ_BITS(CMU->PLLCFG, CMU_PLLCFG_PLL1OS_MSK, CMU_PLLCFG_PLL1OS_POSS);
}

/**
  * @brief  Gets lock state of PLL1.
  * @retval The status of following:
  *         - 0x0: Lock
  *         - 0x1: Unlock
  */
__STATIC_INLINE uint32_t md_cmu_get_pll1_lock(void)
{
    return READ_BITS(CMU->PLLCFG, CMU_PLLCFG_PLL1LCKN_MSK, CMU_PLLCFG_PLL1LCKN_POS);
}
/**
  * @}
  */
/** @defgroup MD_CMU_Public_Functions_Group7 HOSCCFG
  * @{
  */
/**
  * @}
  */
/** @defgroup MD_CMU_Public_Functions_Group8 HOSMCR
  * @{
  */
/**
  * @brief  Enable HOSC safe.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_hosc_safe(void)
{
    SET_BIT(CMU->HOSMCR, CMU_HOSMCR_EN_MSK);
}

/**
  * @brief  Disable HOSC safe.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_hosc_safe(void)
{
    CLEAR_BIT(CMU->HOSMCR, CMU_HOSMCR_EN_MSK);
}

/**
  * @brief  Check HOSC safe is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_hosc_safe(void)
{
    return READ_BITS(CMU->HOSMCR, CMU_HOSMCR_EN_MSK, CMU_HOSMCR_EN_POS);
}

/**
  * @brief  Gets current high-clock.
  * @retval Status:
  *         - 0: HOSC
  *         - 1: HRC
  */
__STATIC_INLINE uint32_t md_cmu_get_high_clock_source(void)
{
    return READ_BITS(CMU->HOSMCR, CMU_HOSMCR_CLKS_MSK, CMU_HOSMCR_CLKS_POS);
}

/**
  * @brief  Sets HOSC frequence region
  * @param  clk: The value of following:
  *         - 0: 1-2MHz
  *         - 1: 2-4MHz
  *         - 2: 4-8MHz
  *         - 3: 8-16MHz
  *         - 4: 16-32MHz
  * @retval None
  */
__STATIC_INLINE void md_cmu_set_hosc_region(uint32_t clk)
{
    MODIFY_REG(CMU->HOSMCR, CMU_HOSMCR_FRQS_MSK, clk << CMU_HOSMCR_FRQS_POSS);
}

/**
  * @brief  Gets HOSC frequence region
  * @retval The value of following:
  *         - 0: 1-2MHz
  *         - 1: 2-4MHz
  *         - 2: 4-8MHz
  *         - 3: 8-16MHz
  *         - 4: 16-32MHz
  */
__STATIC_INLINE uint32_t md_cmu_get_hosc_region(void)
{
    return READ_BITS(CMU->HOSMCR, CMU_HOSMCR_FRQS_MSK, CMU_HOSMCR_FRQS_POSS);
}

/**
  * @brief  Enable STR interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_hosc_str_interrupt(void)
{
    SET_BIT(CMU->HOSMCR, CMU_HOSMCR_STRIE_MSK);
}

/**
  * @brief  Disable STR interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_hosc_str_interrupt(void)
{
    CLEAR_BIT(CMU->HOSMCR, CMU_HOSMCR_STRIE_MSK);
}

/**
  * @brief  Check STR interrupt is enable.
  * @retval Status.
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_hosc_str_interrupt(void)
{
    return READ_BITS(CMU->HOSMCR, CMU_HOSMCR_STRIE_MSK, CMU_HOSMCR_STRIE_POS);
}

/**
  * @brief  Enable STP interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_hosc_stp_interrupt(void)
{
    SET_BIT(CMU->HOSMCR, CMU_HOSMCR_STPIE_MSK);
}

/**
  * @brief  Disable STP interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_hosc_stp_interrupt(void)
{
    CLEAR_BIT(CMU->HOSMCR, CMU_HOSMCR_STPIE_MSK);
}

/**
  * @brief  Check STP interrupt is enable.
  * @retval Status.
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_hosc_stp_interrupt(void)
{
    return READ_BITS(CMU->HOSMCR, CMU_HOSMCR_STPIE_MSK, CMU_HOSMCR_STPIE_POS);
}

/**
  * @brief  Gets STR flag state
  * @retval State
  */
__STATIC_INLINE uint32_t md_cmu_is_active_flag_hosc_str(void)
{
    return READ_BITS(CMU->HOSMCR, CMU_HOSMCR_STRIF_MSK, CMU_HOSMCR_STRIF_POS);
}

/**
  * @brief  Clear STR flag
  * @retval None
  */
__STATIC_INLINE void md_cmu_clear_flag_hosc_str(void)
{
    SET_BIT(CMU->HOSMCR, CMU_HOSMCR_STRIF_MSK);
}

/**
  * @brief  Gets STP flag state
  * @retval State
  */
__STATIC_INLINE uint32_t md_cmu_is_active_flag_hosc_stp(void)
{
    return READ_BITS(CMU->HOSMCR, CMU_HOSMCR_STPIF_MSK, CMU_HOSMCR_STPIF_POS);
}

/**
  * @brief  Clear STP flag
  * @retval None
  */
__STATIC_INLINE void md_cmu_clear_flag_hosc_stp(void)
{
    SET_BIT(CMU->HOSMCR, CMU_HOSMCR_STPIF_MSK);
}

/**
  * @brief  Enable NMI interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_hosc_nmi_interrupt(void)
{
    SET_BIT(CMU->HOSMCR, CMU_HOSMCR_STRPIE_MSK);
}

/**
  * @brief  Disable NMI interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_hosc_nmi_interrupt(void)
{
    CLEAR_BIT(CMU->HOSMCR, CMU_HOSMCR_STRPIE_MSK);
}

/**
  * @brief  Check NMI interrupt is enable.
  * @retval Status.
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_hosc_nmi_interrupt(void)
{
    return READ_BITS(CMU->HOSMCR, CMU_HOSMCR_STRPIE_MSK, CMU_HOSMCR_STRPIE_POS);
}
/**
  * @}
  */
/** @defgroup MD_CMU_Public_Functions_Group9 LOSMCR
  * @{
  */
/**
  * @brief  Enable LOSC safe.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_losc_safe(void)
{
    SET_BIT(CMU->LOSMCR, CMU_LOSMCR_EN_MSK);
}

/**
  * @brief  Disable LOSC safe.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_losc_safe(void)
{
    CLEAR_BIT(CMU->LOSMCR, CMU_LOSMCR_EN_MSK);
}

/**
  * @brief  Check LOSC safe is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_losc_safe(void)
{
    return READ_BITS(CMU->LOSMCR, CMU_LOSMCR_EN_MSK, CMU_LOSMCR_EN_POS);
}

/**
  * @brief  Gets current low-clock.
  * @retval Status:
  *         - 0: LOSC
  *         - 1: LRC
  */
__STATIC_INLINE uint32_t md_cmu_get_low_clock_source(void)
{
    return READ_BITS(CMU->LOSMCR, CMU_LOSMCR_CLKS_MSK, CMU_LOSMCR_CLKS_POS);
}

/**
  * @brief  Enable STR interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_losc_str_interrupt(void)
{
    SET_BIT(CMU->LOSMCR, CMU_LOSMCR_STRIE_MSK);
}

/**
  * @brief  Disable STR interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_losc_str_interrupt(void)
{
    CLEAR_BIT(CMU->LOSMCR, CMU_LOSMCR_STRIE_MSK);
}

/**
  * @brief  Check STR interrupt is enable.
  * @retval Status.
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_losc_str_interrupt(void)
{
    return READ_BITS(CMU->LOSMCR, CMU_LOSMCR_STRIE_MSK, CMU_LOSMCR_STRIE_POS);
}

/**
  * @brief  Enable STP interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_losc_stp_interrupt(void)
{
    SET_BIT(CMU->LOSMCR, CMU_LOSMCR_STPIE_MSK);
}

/**
  * @brief  Disable STP interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_losc_stp_interrupt(void)
{
    CLEAR_BIT(CMU->LOSMCR, CMU_LOSMCR_STPIE_MSK);
}

/**
  * @brief  Check STP interrupt is enable.
  * @retval Status.
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_losc_stp_interrupt(void)
{
    return READ_BITS(CMU->LOSMCR, CMU_LOSMCR_STPIE_MSK, CMU_LOSMCR_STPIE_POS);
}

/**
  * @brief  Gets STR flag state
  * @retval State
  */
__STATIC_INLINE uint32_t md_cmu_is_active_flag_losc_str(void)
{
    return READ_BITS(CMU->LOSMCR, CMU_LOSMCR_STRIF_MSK, CMU_LOSMCR_STRIF_POS);
}

/**
  * @brief  Clear STR flag
  * @retval None
  */
__STATIC_INLINE void md_cmu_clear_flag_losc_str(void)
{
    SET_BIT(CMU->LOSMCR, CMU_LOSMCR_STRIF_MSK);
}

/**
  * @brief  Gets STP flag state
  * @retval State
  */
__STATIC_INLINE uint32_t md_cmu_is_active_flag_losc_stp(void)
{
    return READ_BITS(CMU->LOSMCR, CMU_LOSMCR_STPIF_MSK, CMU_LOSMCR_STPIF_POS);
}

/**
  * @brief  Clear STP flag
  * @retval None
  */
__STATIC_INLINE void md_cmu_clear_flag_losc_stp(void)
{
    SET_BIT(CMU->LOSMCR, CMU_LOSMCR_STPIF_MSK);
}

/**
  * @}
  */
/** @defgroup MD_CMU_Public_Functions_Group10 PULMCR
  * @{
  */
/**
  * @brief  Enable PLL safe.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_pll_safe(void)
{
    SET_BIT(CMU->PULMCR, CMU_PULMCR_EN_MSK);
}

/**
  * @brief  Disable PLL safe.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_pll_safe(void)
{
    CLEAR_BIT(CMU->PULMCR, CMU_PULMCR_EN_MSK);
}

/**
  * @brief  Check PLL safe is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_pll_safe(void)
{
    return READ_BITS(CMU->PULMCR, CMU_PULMCR_EN_MSK, CMU_PULMCR_EN_POS);
}

/**
  * @brief  Gets current clock.
  * @retval Status:
  *         - 0: PLL
  *         - 1: HRC
  */
__STATIC_INLINE uint32_t md_cmu_get_current_clock_source(void)
{
    return READ_BITS(CMU->PULMCR, CMU_PULMCR_CLKS_MSK, CMU_PULMCR_CLKS_POS);
}

/**
  * @brief  Sets system clock when PLL unlock.
  * @param  opt: Value of following:
  *         - 0: Do nothing
  *         - 1: Switch HRC
  *         - 2: Switch HRC. Switch back PLL when Pll is stable.
  * @retval None
  */
__STATIC_INLINE void md_cmu_set_system_clock_pll_unlock(uint32_t opt)
{
    MODIFY_REG(CMU->PULMCR, CMU_PULMCR_MODE_MSK, CMU_PULMCR_MODE_POSS);
}

/**
  * @brief  Gets system clock when PLL unlock.
  * @retval   The mode:
  *         - 0: Do nothing
  *         - 1: Switch HRC
  *         - 2: Switch HRC. Switch back PLL when Pll is stable
  */
__STATIC_INLINE uint32_t md_cmu_get_system_clock_pll_unlock()
{
    return READ_BITS(CMU->PULMCR, CMU_PULMCR_MODE_MSK, CMU_PULMCR_MODE_POSS);
}

/**
  * @brief  Enable LCK interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_pll_lck_interrupt(void)
{
    SET_BIT(CMU->PULMCR, CMU_PULMCR_LCKIE_MSK);
}

/**
  * @brief  Disable LCK interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_pll_lck_interrupt(void)
{
    CLEAR_BIT(CMU->PULMCR, CMU_PULMCR_LCKIE_MSK);
}

/**
  * @brief  Check LCK interrupt is enable.
  * @retval Status.
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_pll_lck_interrupt(void)
{
    return READ_BITS(CMU->PULMCR, CMU_PULMCR_LCKIE_MSK, CMU_PULMCR_LCKIE_POS);
}

/**
  * @brief  Enable ULK interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_pll_ulk_interrupt(void)
{
    SET_BIT(CMU->PULMCR, CMU_PULMCR_ULKIE_MSK);
}

/**
  * @brief  Disable ULK interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_pll_ulk_interrupt(void)
{
    CLEAR_BIT(CMU->PULMCR, CMU_PULMCR_ULKIE_MSK);
}

/**
  * @brief  Check ULK interrupt is enable.
  * @retval Status.
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_pll_ulk_interrupt(void)
{
    return READ_BITS(CMU->PULMCR, CMU_PULMCR_ULKIE_MSK, CMU_PULMCR_ULKIE_POS);
}

/**
  * @brief  Gets LCK flag state
  * @retval State
  */
__STATIC_INLINE uint32_t md_cmu_is_active_flag_pll_lck(void)
{
    return READ_BITS(CMU->PULMCR, CMU_PULMCR_LCKIF_MSK, CMU_PULMCR_LCKIF_POS);
}

/**
  * @brief  Clear LCK flag
  * @retval None
  */
__STATIC_INLINE void md_cmu_clear_flag_pll_lck(void)
{
    SET_BIT(CMU->PULMCR, CMU_PULMCR_LCKIF_MSK);
}

/**
  * @brief  Gets ULK flag state
  * @retval State
  */
__STATIC_INLINE uint32_t md_cmu_is_active_flag_pll_ulk(void)
{
    return READ_BITS(CMU->PULMCR, CMU_PULMCR_ULKIF_MSK, CMU_PULMCR_ULKIF_POS);
}

/**
  * @brief  Clear ULK flag
  * @retval None
  */
__STATIC_INLINE void md_cmu_clear_flag_pll_ulk(void)
{
    SET_BIT(CMU->PULMCR, CMU_PULMCR_ULKIF_MSK);
}

/**
  * @brief  Enable NMI interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_pll_nmi(void)
{
    SET_BIT(CMU->PULMCR, CMU_PULMCR_LCULKIE_MSK);
}

/**
  * @brief  Disable NMI interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_pll_nmi(void)
{
    CLEAR_BIT(CMU->PULMCR, CMU_PULMCR_LCULKIE_MSK);
}

/**
  * @brief  Check NMI interrupt is enable.
  * @retval Status.
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_pll_nmi(void)
{
    return READ_BITS(CMU->PULMCR, CMU_PULMCR_LCULKIE_MSK, CMU_PULMCR_LCULKIE_POS);
}
/**
  * @}
  */
/** @defgroup MD_CMU_Public_Functions_Group11 CLKOCR
  * @{
  */
/**
  * @brief  Enable HSC output.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_hsco(void)
{
    SET_BIT(CMU->CLKOCR, CMU_CLKOCR_HSCOEN_MSK);
}

/**
  * @brief  Disable HSC output.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_hsco(void)
{
    CLEAR_BIT(CMU->CLKOCR, CMU_CLKOCR_HSCOEN_MSK);
}

/**
  * @brief  Check HSC output is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_hsco(void)
{
    return READ_BITS(CMU->CLKOCR, CMU_CLKOCR_HSCOEN_MSK, CMU_CLKOCR_HSCOEN_POS);
}

/**
  * @brief  Sets high clock output type
  * @param  sel : Value of following:
  *         - 0: HOSC
  *         - 1: LOSC
  *         - 2: HRC
  *         - 3: LRC
  *         - 4: CLKFLT
  *         - 5: PLL1
  *         - 7: SYSCLK
  * @retval None
  */
__STATIC_INLINE void md_cmu_set_hsco_type(uint32_t sel)
{
    MODIFY_REG(CMU->CLKOCR, CMU_CLKOCR_HSCOS_MSK, sel << CMU_CLKOCR_HSCOS_POSS);
}

/**
  * @brief  Gets high clock output type
  * @retval Value of following:
  *         - 0: HOSC
  *         - 1: LOSC
  *         - 2: HRC
  *         - 3: LRC
  *         - 4: CLKFLT
  *         - 5: PLL1
  *         - 7: SYSCLK
  */
__STATIC_INLINE uint32_t md_cmu_get_hsco_type(void)
{
    return READ_BITS(CMU->CLKOCR, CMU_CLKOCR_HSCOS_MSK, CMU_CLKOCR_HSCOS_POSS);
}

/**
  * @brief  Sets high clock output divider
  * @param  div: Value of following:
  *         - 0: HSC / 1
  *         - 1: HSC / 2
  *         - 2: HSC / 4
  *         - 3: HSC / 8
  *         - 4: HSC / 16
  *         - 5: HSC / 32
  *         - 6: HSC / 64
  *         - 7: HSC / 128
  * @retval None
  */
__STATIC_INLINE void md_cmu_set_hsco_div(uint32_t div)
{
    MODIFY_REG(CMU->CLKOCR, CMU_CLKOCR_HSCODIV_MSK, div << CMU_CLKOCR_HSCODIV_POSS);
}

/**
  * @brief  Gets high clock output divider
  * @retval Value of following:
  *         - 0: HSC / 1
  *         - 1: HSC / 2
  *         - 2: HSC / 4
  *         - 3: HSC / 8
  *         - 4: HSC / 16
  *         - 5: HSC / 32
  *         - 6: HSC / 64
  *         - 7: HSC / 128
  */
__STATIC_INLINE uint32_t md_cmu_get_hsco_div(void)
{
    return READ_BITS(CMU->CLKOCR, CMU_CLKOCR_HSCODIV_MSK, CMU_CLKOCR_HSCODIV_POSS);
}

/**
  * @brief  Enable LSC output.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_lsco(void)
{
    SET_BIT(CMU->CLKOCR, CMU_CLKOCR_LSCOEN_MSK);
}

/**
  * @brief  Disable LSC output.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_lsco(void)
{
    CLEAR_BIT(CMU->CLKOCR, CMU_CLKOCR_LSCOEN_MSK);
}

/**
  * @brief  Check LSC output is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_lsco(void)
{
    return READ_BITS(CMU->CLKOCR, CMU_CLKOCR_LSCOEN_MSK, CMU_CLKOCR_LSCOEN_POS);
}

/**
  * @brief  Sets low clock output type
  * @param  sel : Value of following:
  *         - 0: LOSC
  *         - 1: LRC
  *         - 2: LOSM
  *         - 3: BUZZ
  *         - 4: ULRC
  * @retval None
  */
__STATIC_INLINE void md_cmu_set_lsco_type(uint32_t sel)
{
    MODIFY_REG(CMU->CLKOCR, CMU_CLKOCR_LSCOS_MSK, sel << CMU_CLKOCR_LSCOS_POSS);
}

/**
  * @brief  Gets low clock output type
  * @retval Value of following:
  *         - 0: LOSC
  *         - 1: LRC
  *         - 2: LOSM
  *         - 3: BUZZ
  *         - 4: ULRC
  */
__STATIC_INLINE uint32_t md_cmu_get_lsco_type(void)
{
    return READ_BITS(CMU->CLKOCR, CMU_CLKOCR_LSCOS_MSK, CMU_CLKOCR_LSCOS_POSS);
}
/**
  * @}
  */
/** @defgroup MD_CMU_Public_Functions_Group12 BUZZCR
  * @{
  */
/**
  * @brief  Enable BUZZ output.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_buzz(void)
{
    SET_BIT(CMU->BUZZCR, CMU_BUZZCR_BUZZEN_MSK);
}

/**
  * @brief  Disable BUZZ output.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_buzz(void)
{
    CLEAR_BIT(CMU->BUZZCR, CMU_BUZZCR_BUZZEN_MSK);
}

/**
  * @brief  Check BUZZ output is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_buzz(void)
{
    return READ_BITS(CMU->BUZZCR, CMU_BUZZCR_BUZZEN_MSK, CMU_BUZZCR_BUZZEN_POS);
}

/**
  * @brief  Sets BUZZ divider
  * @param  div: Value of following:
  *         - 0: Freq / 2
  *         - 1: Freq / 4
  *         - 2: Freq / 8
  *         - 3: Freq / 16
  *         - 4: Freq / 32
  *         - 5: Freq / 64
  *         - 6: Freq / 128
  *         - 7: Freq / 256
  * @retval None
  */
__STATIC_INLINE void md_cmu_set_buzz_div(uint32_t div)
{
    MODIFY_REG(CMU->BUZZCR, CMU_BUZZCR_BUZZDIV_MSK, div << CMU_BUZZCR_BUZZDIV_POSS);
}

/**
  * @brief  Gets BUZZ divider
  * @retval Value of following:
  *         - 0: Freq / 2
  *         - 1: Freq / 4
  *         - 2: Freq / 8
  *         - 3: Freq / 16
  *         - 4: Freq / 32
  *         - 5: Freq / 64
  *         - 6: Freq / 128
  *         - 7: Freq / 256
  */
__STATIC_INLINE uint32_t md_cmu_get_buzz_div(void)
{
    return READ_BITS(CMU->BUZZCR, CMU_BUZZCR_BUZZDIV_MSK, CMU_BUZZCR_BUZZDIV_POSS);
}

/**
  * @brief  Sets BUZZ data
  * @param  data: Region is from 0x00 to 0xFFFF
  * @retval None
  */
__STATIC_INLINE void md_cmu_set_buzz_data(uint32_t data)
{
    MODIFY_REG(CMU->BUZZCR, CMU_BUZZCR_BUZZDAT_MSK, data << CMU_BUZZCR_BUZZDAT_POSS);
}

/**
  * @brief  Gets BUZZ data
  * @retval BUZZ data
  */
__STATIC_INLINE uint32_t md_cmu_get_buzz_data(uint32_t data)
{
    return READ_BITS(CMU->BUZZCR, CMU_BUZZCR_BUZZDAT_MSK, CMU_BUZZCR_BUZZDAT_POSS);
}
/**
  * @}
  */
/** @defgroup MD_CMU_Public_Functions_Group13 AHB1ENR
  * @{
  */
/**
  * @brief  Enable GPIO peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_gpio(void)
{
    SET_BIT(CMU->AHB1ENR, CMU_AHB1ENR_GPIOEN_MSK);
}

/**
  * @brief  Disable GPIO peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_gpio(void)
{
    CLEAR_BIT(CMU->AHB1ENR, CMU_AHB1ENR_GPIOEN_MSK);
}

/**
  * @brief  Check GPIO peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_gpio(void)
{
    return READ_BITS(CMU->AHB1ENR, CMU_AHB1ENR_GPIOEN_MSK, CMU_AHB1ENR_GPIOEN_POS);
}

/**
  * @brief  Enable CRC peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_crc(void)
{
    SET_BIT(CMU->AHB1ENR, CMU_AHB1ENR_CRCEN_MSK);
}

/**
  * @brief  Disable CRC peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_crc(void)
{
    CLEAR_BIT(CMU->AHB1ENR, CMU_AHB1ENR_CRCEN_MSK);
}

/**
  * @brief  Check CRC peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_crc(void)
{
    return READ_BITS(CMU->AHB1ENR, CMU_AHB1ENR_CRCEN_MSK, CMU_AHB1ENR_CRCEN_POS);
}

/**
  * @brief  Enable CALC peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_calc(void)
{
    SET_BIT(CMU->AHB1ENR, CMU_AHB1ENR_CALCEN_MSK);
}

/**
  * @brief  Disable CALC peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_calc(void)
{
    CLEAR_BIT(CMU->AHB1ENR, CMU_AHB1ENR_CALCEN_MSK);
}

/**
  * @brief  Check CALC peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_calc(void)
{
    return READ_BITS(CMU->AHB1ENR, CMU_AHB1ENR_CALCEN_MSK, CMU_AHB1ENR_CALCEN_POS);
}

/**
  * @brief  Enable CRYPT peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_crypt(void)
{
    SET_BIT(CMU->AHB1ENR, CMU_AHB1ENR_CRYPTEN_MSK);
}

/**
  * @brief  Disable CRYPT peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_crypt(void)
{
    CLEAR_BIT(CMU->AHB1ENR, CMU_AHB1ENR_CRYPTEN_MSK);
}

/**
  * @brief  Check CRYPT peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_crypt(void)
{
    return READ_BITS(CMU->AHB1ENR, CMU_AHB1ENR_CRYPTEN_MSK, CMU_AHB1ENR_CRYPTEN_POS);
}

/**
  * @brief  Enable TRNG peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_trng(void)
{
    SET_BIT(CMU->AHB1ENR, CMU_AHB1ENR_TRNGEN_MSK);
}

/**
  * @brief  Disable TRNG peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_trng(void)
{
    CLEAR_BIT(CMU->AHB1ENR, CMU_AHB1ENR_TRNGEN_MSK);
}

/**
  * @brief  Check TRNG peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_trng(void)
{
    return READ_BITS(CMU->AHB1ENR, CMU_AHB1ENR_TRNGEN_MSK, CMU_AHB1ENR_TRNGEN_POS);
}

/**
  * @brief  Enable PIS peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_pis(void)
{
    SET_BIT(CMU->AHB1ENR, CMU_AHB1ENR_PISEN_MSK);
}

/**
  * @brief  Disable PIS peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_pis(void)
{
    CLEAR_BIT(CMU->AHB1ENR, CMU_AHB1ENR_PISEN_MSK);
}

/**
  * @brief  Check PIS peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_pis(void)
{
    return READ_BITS(CMU->AHB1ENR, CMU_AHB1ENR_PISEN_MSK, CMU_AHB1ENR_PISEN_POS);
}

/**
  * @brief  Enable SM3 peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_sm3(void)
{
    SET_BIT(CMU->AHB1ENR, CMU_AHB1ENR_PISEN_MSK);
}

/**
  * @brief  Disable SM3 peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_sm3(void)
{
    CLEAR_BIT(CMU->AHB1ENR, CMU_AHB1ENR_PISEN_MSK);
}

/**
  * @brief  Check SM3 peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_sm3(void)
{
    return READ_BITS(CMU->AHB1ENR, CMU_AHB1ENR_PISEN_MSK, CMU_AHB1ENR_PISEN_POS);
}

/**
  * @}
  */
/** @defgroup MD_CMU_Public_Functions_Group14 APB1ENR
  * @{
  */
/**
  * @brief  Enable TIMER0 peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_timer0(void)
{
    SET_BIT(CMU->APB1ENR, CMU_APB1ENR_TIM0EN_MSK);
}

/**
  * @brief  Disable TIMER0 peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_timer0(void)
{
    CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_TIM0EN_MSK);
}

/**
  * @brief  Check TIMER0 peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_timer0(void)
{
    return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_TIM0EN_MSK, CMU_APB1ENR_TIM0EN_POS);
}

/**
  * @brief  Enable TIMER1 peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_timer1(void)
{
    SET_BIT(CMU->APB1ENR, CMU_APB1ENR_TIM1EN_MSK);
}

/**
  * @brief  Disable TIMER1 peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_timer1(void)
{
    CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_TIM1EN_MSK);
}

/**
  * @brief  Check TIMER1 peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_timer1(void)
{
    return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_TIM1EN_MSK, CMU_APB1ENR_TIM1EN_POS);
}

/**
  * @brief  Enable TIMER2 peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_timer2(void)
{
    SET_BIT(CMU->APB1ENR, CMU_APB1ENR_TIM2EN_MSK);
}

/**
  * @brief  Disable TIMER2 peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_timer2(void)
{
    CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_TIM2EN_MSK);
}

/**
  * @brief  Check TIMER2 peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_timer2(void)
{
    return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_TIM2EN_MSK, CMU_APB1ENR_TIM2EN_POS);
}

/**
  * @brief  Enable TIMER3 peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_timer3(void)
{
    SET_BIT(CMU->APB1ENR, CMU_APB1ENR_TIM3EN_MSK);
}

/**
  * @brief  Disable TIMER3 peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_timer3(void)
{
    CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_TIM3EN_MSK);
}

/**
  * @brief  Check TIMER3 peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_timer3(void)
{
    return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_TIM3EN_MSK, CMU_APB1ENR_TIM3EN_POS);
}

/**
  * @brief  Enable TIMER4 peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_timer4(void)
{
    SET_BIT(CMU->APB1ENR, CMU_APB1ENR_TIM4EN_MSK);
}

/**
  * @brief  Disable TIMER4 peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_timer4(void)
{
    CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_TIM4EN_MSK);
}

/**
  * @brief  Check TIMER4 peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_timer4(void)
{
    return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_TIM4EN_MSK, CMU_APB1ENR_TIM4EN_POS);
}

/**
  * @brief  Enable TIMER5 peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_timer5(void)
{
    SET_BIT(CMU->APB1ENR, CMU_APB1ENR_TIM5EN_MSK);
}

/**
  * @brief  Disable TIMER5 peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_timer5(void)
{
    CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_TIM5EN_MSK);
}

/**
  * @brief  Check TIMER5 peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_timer5(void)
{
    return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_TIM5EN_MSK, CMU_APB1ENR_TIM5EN_POS);
}

/**
  * @brief  Enable UART0 peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_uart0(void)
{
    SET_BIT(CMU->APB1ENR, CMU_APB1ENR_UART0EN_MSK);
}

/**
  * @brief  Disable UART0 peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_uart0(void)
{
    CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_UART0EN_MSK);
}

/**
  * @brief  Check UART0 peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_uart0(void)
{
    return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_UART0EN_MSK, CMU_APB1ENR_UART0EN_POS);
}

/**
  * @brief  Enable UART1 peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_uart1(void)
{
    SET_BIT(CMU->APB1ENR, CMU_APB1ENR_UART1EN_MSK);
}

/**
  * @brief  Disable UART1 peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_uart1(void)
{
    CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_UART1EN_MSK);
}

/**
  * @brief  Check UART1 peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_uart1(void)
{
    return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_UART1EN_MSK, CMU_APB1ENR_UART1EN_POS);
}

/**
  * @brief  Enable UART2 peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_uart2(void)
{
    SET_BIT(CMU->APB1ENR, CMU_APB1ENR_UART2EN_MSK);
}

/**
  * @brief  Disable UART2 peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_uart2(void)
{
    CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_UART2EN_MSK);
}

/**
  * @brief  Check UART2 peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_uart2(void)
{
    return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_UART2EN_MSK, CMU_APB1ENR_UART2EN_POS);
}

/**
  * @brief  Enable SPI0 peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_spi0(void)
{
    SET_BIT(CMU->APB1ENR, CMU_APB1ENR_SPI0EN_MSK);
}

/**
  * @brief  Disable SPI0 peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_spi0(void)
{
    CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_SPI0EN_MSK);
}

/**
  * @brief  Check SPI0 peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_spi0(void)
{
    return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_SPI0EN_MSK, CMU_APB1ENR_SPI0EN_POS);
}

/**
  * @brief  Enable SPI1 peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_spi1(void)
{
    SET_BIT(CMU->APB1ENR, CMU_APB1ENR_SPI1EN_MSK);
}

/**
  * @brief  Disable SPI1 peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_spi1(void)
{
    CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_SPI1EN_MSK);
}

/**
  * @brief  Check SPI1 peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_spi1(void)
{
    return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_SPI1EN_MSK, CMU_APB1ENR_SPI1EN_POS);
}

/**
  * @brief  Enable I2C0 peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_i2c0(void)
{
    SET_BIT(CMU->APB1ENR, CMU_APB1ENR_I2C0EN_MSK);
}

/**
  * @brief  Disable I2C0 peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_i2c0(void)
{
    CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_I2C0EN_MSK);
}

/**
  * @brief  Check I2C0 peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_i2c0(void)
{
    return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_I2C0EN_MSK, CMU_APB1ENR_I2C0EN_POS);
}

/**
  * @brief  Enable I2C1 peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_i2c1(void)
{
    SET_BIT(CMU->APB1ENR, CMU_APB1ENR_I2C1EN_MSK);
}

/**
  * @brief  Disable I2C1 peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_i2c1(void)
{
    CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_I2C1EN_MSK);
}

/**
  * @brief  Check I2C1 peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_i2c1(void)
{
    return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_I2C1EN_MSK, CMU_APB1ENR_I2C1EN_POS);
}

/**
  * @brief  Enable ADPCM peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_adpcm(void)
{
    SET_BIT(CMU->APB1ENR, CMU_APB1ENR_ADPCMEN_MSK);
}

/**
  * @brief  Disable ADPCM peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_adpcm(void)
{
    CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_ADPCMEN_MSK);
}

/**
  * @brief  Check ADPCM peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_adpcm(void)
{
    return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_ADPCMEN_MSK, CMU_APB1ENR_ADPCMEN_POS);
}

/**
  * @brief  Enable TK peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_tk(void)
{
    SET_BIT(CMU->APB1ENR, CMU_APB1ENR_TKEN_MSK);
}

/**
  * @brief  Disable TK peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_tk(void)
{
    CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_TKEN_MSK);
}

/**
  * @brief  Check TK peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_tk(void)
{
    return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_TKEN_MSK, CMU_APB1ENR_TKEN_POS);
}

/**
  * @brief  Enable ECC peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_ecc(void)
{
    SET_BIT(CMU->APB1ENR, CMU_APB1ENR_ECCEN_MSK);
}

/**
  * @brief  Disable ECC peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_ecc(void)
{
    CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_ECCEN_MSK);
}

/**
  * @brief  Check ECC peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_ecc(void)
{
    return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_ECCEN_MSK, CMU_APB1ENR_ECCEN_POS);
}

/**
  * @brief  Enable PDPCM peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_pdpcm(void)
{
    SET_BIT(CMU->APB1ENR, CMU_APB1ENR_PDPCMEN_MSK);
}

/**
  * @brief  Disable PDPCM peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_pdpcm(void)
{
    CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_PDPCMEN_MSK);
}

/**
  * @brief  Check PDPCM peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_pdpcm(void)
{
    return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_PDPCMEN_MSK, CMU_APB1ENR_PDPCMEN_POS);
}

/**
  * @brief  Enable QSPI-P peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_qspi_p(void)
{
    SET_BIT(CMU->APB1ENR, CMU_APB1ENR_QSPIEN_MSK);
}

/**
  * @brief  Disable QSPI-P peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_qspi_p(void)
{
    CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_QSPIEN_MSK);
}

/**
  * @brief  Check QSPI-P peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_qspi_p(void)
{
    return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_QSPIEN_MSK, CMU_APB1ENR_QSPIEN_POS);
}

/**
  * @brief  Enable QUAD peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_quad(void)
{
    SET_BIT(CMU->APB1ENR, CMU_APB1ENR_QUADEN_MSK);
}

/**
  * @brief  Disable QUAD peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_quad(void)
{
    CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_QUADEN_MSK);
}

/**
  * @brief  Check QUAD peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_quad(void)
{
    return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_QUADEN_MSK, CMU_APB1ENR_QUADEN_POS);
}

/**
  * @}
  */
/** @defgroup MD_CMU_Public_Functions_Group15 APB2ENR
  * @{
  */
/**
  * @brief  Enable LP16T peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_lp16t(void)
{
    SET_BIT(CMU->APB2ENR, CMU_APB2ENR_LP16TEN_MSK);
}

/**
  * @brief  Disable LP16T peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_lp16t(void)
{
    CLEAR_BIT(CMU->APB2ENR, CMU_APB2ENR_LP16TEN_MSK);
}

/**
  * @brief  Check LP16T peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_lp16t(void)
{
    return READ_BITS(CMU->APB2ENR, CMU_APB2ENR_LP16TEN_MSK, CMU_APB2ENR_LP16TEN_POS);
}

/**
  * @brief  Enable ADC0 peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_adc0(void)
{
    SET_BIT(CMU->APB2ENR, CMU_APB2ENR_ADC0EN_MSK);
}

/**
  * @brief  Disable ADC0 peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_adc0(void)
{
    CLEAR_BIT(CMU->APB2ENR, CMU_APB2ENR_ADC0EN_MSK);
}

/**
  * @brief  Check ADC0 peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_adc0(void)
{
    return READ_BITS(CMU->APB2ENR, CMU_APB2ENR_ADC0EN_MSK, CMU_APB2ENR_ADC0EN_POS);
}

/**
  * @brief  Enable WWDT peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_wwdt(void)
{
    SET_BIT(CMU->APB2ENR, CMU_APB2ENR_WWDTEN_MSK);
}

/**
  * @brief  Disable WWDT peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_wwdt(void)
{
    CLEAR_BIT(CMU->APB2ENR, CMU_APB2ENR_WWDTEN_MSK);
}

/**
  * @brief  Check WWDT peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_wwdt(void)
{
    return READ_BITS(CMU->APB2ENR, CMU_APB2ENR_WWDTEN_MSK, CMU_APB2ENR_WWDTEN_POS);
}

/**
  * @brief  Enable IWDT peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_iwdt(void)
{
    SET_BIT(CMU->APB2ENR, CMU_APB2ENR_IWDTEN_MSK);
}

/**
  * @brief  Disable IWDT peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_iwdt(void)
{
    CLEAR_BIT(CMU->APB2ENR, CMU_APB2ENR_IWDTEN_MSK);
}

/**
  * @brief  Check IWDT peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_iwdt(void)
{
    return READ_BITS(CMU->APB2ENR, CMU_APB2ENR_IWDTEN_MSK, CMU_APB2ENR_IWDTEN_POS);
}

/**
  * @brief  Enable RTC peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_rtc(void)
{
    SET_BIT(CMU->APB2ENR, CMU_APB2ENR_RTCEN_MSK);
}

/**
  * @brief  Disable RTC peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_rtc(void)
{
    CLEAR_BIT(CMU->APB2ENR, CMU_APB2ENR_RTCEN_MSK);
}

/**
  * @brief  Check RTC peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_rtc(void)
{
    return READ_BITS(CMU->APB2ENR, CMU_APB2ENR_RTCEN_MSK, CMU_APB2ENR_RTCEN_POS);
}

/**
  * @brief  Enable BKPC peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_bkpc(void)
{
    SET_BIT(CMU->APB2ENR, CMU_APB2ENR_BKPCEN_MSK);
}

/**
  * @brief  Disable BKPC peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_bkpc(void)
{
    CLEAR_BIT(CMU->APB2ENR, CMU_APB2ENR_BKPCEN_MSK);
}

/**
  * @brief  Check BKPC peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_bkpc(void)
{
    return READ_BITS(CMU->APB2ENR, CMU_APB2ENR_BKPCEN_MSK, CMU_APB2ENR_BKPCEN_POS);
}

/**
  * @brief  Enable DBGC peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_dbgc(void)
{
    SET_BIT(CMU->APB2ENR, CMU_APB2ENR_DBGEN_MSK);
}

/**
  * @brief  Disable DBGC peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_dbgc(void)
{
    CLEAR_BIT(CMU->APB2ENR, CMU_APB2ENR_DBGEN_MSK);
}

/**
  * @brief  Check DBGC peripheral is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_dbgc(void)
{
    return READ_BITS(CMU->APB2ENR, CMU_APB2ENR_DBGEN_MSK, CMU_APB2ENR_DBGEN_POS);
}

/**
  * @brief  Enable ALL peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_all(void)
{
    WRITE_REG(CMU->AHB1ENR, 0xFFFFFFFF);
    WRITE_REG(CMU->APB1ENR, 0xFFFFFFFF);
    WRITE_REG(CMU->APB2ENR, 0xFFFFFFFF);
}

/**
  * @brief  Disable ALL peripheral.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_all(void)
{
    WRITE_REG(CMU->AHB1ENR, 0x0);
    WRITE_REG(CMU->APB1ENR, 0x0);
    WRITE_REG(CMU->APB2ENR, 0x0);
}
/**
  * @}
  */
/** @defgroup MD_CMU_Public_Functions_Group16 LPENR
  * @{
  */
/**
  * @brief  Enable LRC low power mode.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_lp_lrc(void)
{
    SET_BIT(CMU->AHB1LPENR, CMU_AHB1LPENR_LRCEN_MSK);
}

/**
  * @brief  Disable LRC low power mode.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_lp_lrc(void)
{
    CLEAR_BIT(CMU->AHB1LPENR, CMU_AHB1LPENR_LRCEN_MSK);
}

/**
  * @brief  Check LRC low power mode is enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_lp_lrc(void)
{
    return READ_BITS(CMU->AHB1LPENR, CMU_AHB1LPENR_LRCEN_MSK, CMU_AHB1LPENR_LRCEN_POS);
}

/**
  * @}
  */
/** @defgroup MD_CMU_Public_Functions_Group17 PERICR
  * @{
  */
/**
  * @brief  Stes LP16T clock source.
  * @param  clk: Value of following:
  *         - 0x0: PCLK2
  *         - 0x1: HRC
  *         - 0x2: HRC divide to 1MHz
  *         - 0x3: HOSC
  *         - 0x4: LRC
  *         - 0x5: LOSM
  *         - 0x6: ULRC
  *         - 0x7: LS_CLK
  * @retval None
  */
__STATIC_INLINE void md_cmu_set_lp16t_clock_source(uint32_t clk)
{
    MODIFY_REG(CMU->PERICR, CMU_PERICR_LP16TCS_MSK, clk << CMU_PERICR_LP16TCS_POSS);
}

/**
  * @brief  Gets LP16T clock source.
  * @retval Value of following:
  *         - 0x0: PCLK2
  *         - 0x1: HRC
  *         - 0x2: HRC divide to 1MHz
  *         - 0x3: HOSC
  *         - 0x4: LRC
  *         - 0x5: LOSM
  *         - 0x6: ULRC
  *         - 0x7: LS_CLK
  */
__STATIC_INLINE uint32_t md_cmu_get_lp16t_clock_source(void)
{
    return READ_BITS(CMU->PERICR, CMU_PERICR_LP16TCS_MSK, CMU_PERICR_LP16TCS_POSS);
}

/**
  * @}
  */
/** @defgroup MD_CMU_Public_Functions_Group18 CLKDOT
  * @{
  */

/**
  * @brief  Set LDOT value.
  * @param  ldot: 0 - 4095
  * @retval None
  */
__STATIC_INLINE void md_cmu_set_ldot_value(uint32_t ldot)
{
    MODIFY_REG(CMU->CKLDOT, CMU_CKLDOT_LDOT_MSK, ldot << CMU_CKLDOT_LDOT_POSS);
}

/**
  * @brief  Get LDOT value.
  * @retval ldot: 0 - 4095
  */
__STATIC_INLINE uint32_t md_cmu_get_ldot_value(void)
{
    return READ_BITS(CMU->CKLDOT, CMU_CKLDOT_LDOT_MSK, CMU_CKLDOT_LDOT_POSS);
}

/**
  * @brief  Get LDOF status.
  * @retval Status
  */
__STATIC_INLINE uint32_t md_cmu_is_active_flag_ldof(void)
{
    return (READ_BIT(CMU->CKLDOT, CMU_CKLDOT_LDOF_MSK) == CMU_CKLDOT_LDOF_MSK);
}

/**
  * @}
  */

/** @defgroup MD_CMU_Public_Functions_Group19 HOSCT
  * @{
  */

/**
  * @brief  Set HOSCT value.
  * @param  ldot: 0 - 1023
  * @retval None
  */
__STATIC_INLINE void md_cmu_set_hosct_value(uint32_t hosct)
{
    MODIFY_REG(CMU->HOSCT, CMU_HOSCT_HOSCT_MSK, hosct << CMU_HOSCT_HOSCT_POSS);
}

/**
  * @brief  Get HOSCT value.
  * @retval ldot: 0 - 1023
  */
__STATIC_INLINE uint32_t md_cmu_get_hosct_value(void)
{
    return READ_BITS(CMU->HOSCT, CMU_HOSCT_HOSCT_MSK, CMU_HOSCT_HOSCT_POSS);
}

/**
  * @brief  Get HOSCF status.
  * @retval Status
  */
__STATIC_INLINE uint32_t md_cmu_is_active_flag_hoscf(void)
{
    return (READ_BIT(CMU->HOSCT, CMU_HOSCT_HOSCF_MSK) == CMU_HOSCT_HOSCT_MSK);
}

/**
  * @}
  */

/** @defgroup MD_CMU_Public_Functions_Group20 PLLT
  * @{
  */

/**
  * @brief  Set PLL1T value.
  * @param  ldot: 0 - 31
  * @retval None
  */
__STATIC_INLINE void md_cmu_set_pll1t_value(uint32_t pll1t)
{
    MODIFY_REG(CMU->HOSCT, CMU_HOSCT_HOSCT_MSK, pll1t << CMU_HOSCT_HOSCT_POSS);
}

/**
  * @brief  Get PLL1T value.
  * @retval ldot: 0 - 31
  */
__STATIC_INLINE uint32_t md_cmu_get_pll1t_value(void)
{
    return READ_BITS(CMU->HOSCT, CMU_HOSCT_HOSCT_MSK, CMU_HOSCT_HOSCT_POSS);
}

/**
  * @brief  Get PLL1F status.
  * @retval Status
  */
__STATIC_INLINE uint32_t md_cmu_is_active_flag_pll1f(void)
{
    return (READ_BIT(CMU->HOSCT, CMU_HOSCT_HOSCF_MSK) == CMU_HOSCT_HOSCT_MSK);
}

/**
  * @}
  */

/** @defgroup MD_CMU_Public_Functions_Group21 CKSEQR
  * @{
  */

/**
  * @brief  Enable HOSC and PLL control by soft.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_ckstm_control_by_soft(void)
{
    SET_BIT(CMU->CKSEQR, CMU_CKSEQR_CKSTM_MSK);
}

/**
  * @brief  Disable HOSC and PLL control by soft.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_ckstm_control_by_soft(void)
{
    CLEAR_BIT(CMU->CKSEQR, CMU_CKSEQR_CKSTM_MSK);
}

/**
  * @brief  Check HOSC and PLL control by soft is enable or disable.
  * @retval Status
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enable_ckstm_control_by_soft(void)
{
    return (READ_BIT(CMU->CKSEQR, CMU_CKSEQR_CKSTM_MSK) == CMU_CKSEQR_CKSTM_MSK);
}

/**
  * @brief  Enable PLL LOSK always effect.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_pll_lock_byp(void)
{
    SET_BIT(CMU->CKSEQR, CMU_CKSEQR_LOCK_BYP_MSK);
}

/**
  * @brief  Disable PLL LOSK always effect.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_pll_lock_byp(void)
{
    CLEAR_BIT(CMU->CKSEQR, CMU_CKSEQR_LOCK_BYP_MSK);
}

/**
  * @brief  Check HOSC and PLL control by soft is enable or disable.
  * @retval Status
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enable_pll_lock_byp(void)
{
    return (READ_BIT(CMU->CKSEQR, CMU_CKSEQR_LOCK_BYP_MSK) == CMU_CKSEQR_LOCK_BYP_MSK);
}

/**
  * @}
  */

/** @defgroup MD_CMU_Public_Functions_Group22 PDPCMCFG
  * @{
  */

/**
  * @brief  Set PCM2PDM fw.
  * @param  fw: 0 - 65535
  * @retval None
  */
__STATIC_INLINE void md_cmu_set_pdm2pcm_fw(uint32_t fw)
{
    MODIFY_REG(CMU->PDPCMCFG, CMU_PDPCMCFG_FW_MSK, fw << CMU_PDPCMCFG_FW_POSS);
}

/**
  * @brief  Get PCM2PDM fw.
  * @param  NONE
  * @retval fw: 0-65535
  */
__STATIC_INLINE uint32_t md_cmu_get_pdm2pcm_fw(void)
{
    return READ_BITS(CMU->PDPCMCFG, CMU_PDPCMCFG_FW_MSK, CMU_PDPCMCFG_FW_POSS);
}

/**
  * @brief  Set PCM2PDM fdiv.
  * @param  fdiv:
  *         - 0x0: DIV1_0
  *         - 0x3: DIV1_5
  *         - 0x4: DIV2_0
  *         - 0x5: DIV2_5
  *         - 0x6: DIV3_0
  *         - 0x7: DIV3_5
  *         - 0x8: DIV4_0
  *         - 0x9: DIV4_5
  *         - 0xA: DIV5_0
  *         - 0xB: DIV5_5
  *         - 0xC: DIV6_0
  *         - 0xD: DIV6_5
  *         - 0xE: DIV_Auto
  * @retval None
  */
__STATIC_INLINE void md_cmu_set_pdm2pcm_fdiv(uint32_t fdiv)
{
    MODIFY_REG(CMU->PDPCMCFG, CMU_PDPCMCFG_FDIV_MSK, fdiv << CMU_PDPCMCFG_FDIV_POSS);
}

/**
  * @brief  Get PCM2PDM fdiv.
  * @param  NONE
  * @retval fdiv:
  *         - 0x0: DIV1_0
  *         - 0x3: DIV1_5
  *         - 0x4: DIV2_0
  *         - 0x5: DIV2_5
  *         - 0x6: DIV3_0
  *         - 0x7: DIV3_5
  *         - 0x8: DIV4_0
  *         - 0x9: DIV4_5
  *         - 0xA: DIV5_0
  *         - 0xB: DIV5_5
  *         - 0xC: DIV6_0
  *         - 0xD: DIV6_5
  *         - 0xE: DIV_Auto
  */
__STATIC_INLINE uint32_t md_cmu_get_pdm2pcm_fdiv(void)
{
    return READ_BITS(CMU->PDPCMCFG, CMU_PDPCMCFG_FDIV_MSK, CMU_PDPCMCFG_FDIV_POSS);
}

/**
  * @}
  */

/** @defgroup MD_CMU_Public_Functions_Group22 BLEENR
  * @{
  */

/**
  * @brief  Enable BLE BBEN0.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_ble_bben0(void)
{
    SET_BIT(CMU->BLEENR, CMU_BLEENR_BBEN0_MSK);
}

/**
  * @brief  Disable BLE BBEN0.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_ble_bben0(void)
{
    CLEAR_BIT(CMU->BLEENR, CMU_BLEENR_BBEN0_MSK);
}

/**
  * @brief  Check BLE BBEN0 is eanble or disable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enable_ble_bben0(void)
{
    return (READ_BIT(CMU->BLEENR, CMU_BLEENR_BBEN0_MSK) == CMU_BLEENR_BBEN0_MSK);
}

/**
  * @brief  Enable BLE BBEN1.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_ble_bben1(void)
{
    SET_BIT(CMU->BLEENR, CMU_BLEENR_BBEN1_MSK);
}

/**
  * @brief  Disable BLE BBEN1.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_ble_bben1(void)
{
    CLEAR_BIT(CMU->BLEENR, CMU_BLEENR_BBEN1_MSK);
}

/**
  * @brief  Check BLE BBEN1 is eanble or disable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enable_ble_bben1(void)
{
    return (READ_BIT(CMU->BLEENR, CMU_BLEENR_BBEN1_MSK) == CMU_BLEENR_BBEN1_MSK);
}

/**
  * @brief  Enable BLE Modem clock.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_ble_mdmen0(void)
{
    SET_BIT(CMU->BLEENR, CMU_BLEENR_MDMEN0_MSK);
}

/**
  * @brief  Disable BLE Modem clock.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_ble_mdmen0(void)
{
    CLEAR_BIT(CMU->BLEENR, CMU_BLEENR_MDMEN0_MSK);
}

/**
  * @brief  Check BLE Modem clock is eanble or disable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enable_ble_mdmen0(void)
{
    return (READ_BIT(CMU->BLEENR, CMU_BLEENR_MDMEN0_MSK) == CMU_BLEENR_MDMEN0_MSK);
}

/**
  * @}
  */

/** @defgroup MD_CMU_Public_Functions_Group22 BLECFG
  * @{
  */

/**
  * @brief  Set BLE Baseband clock.
  * @param  bbmcks:
  *         - 0x0: SYSCLK_DIV1
  *         - 0x1: SYSCLK_DIV2
  *         - 0x2: SYSCLK_DIV4
  *         - 0x3: SYSCLK_DIV4
  */
__STATIC_INLINE void md_cmu_set_ble_baseband_clock(uint8_t bbmcks)
{
    MODIFY_REG(CMU->BLECFG, CMU_BLECFG_BBMCKS_MSK, bbmcks << CMU_BLECFG_BBMCKS_POSS);
}

/**
  * @brief  Get BLE Baseband clock.
  * @param  NONE
  * @retval bbmcks:
  *         - 0x0: SYSCLK_DIV1
  *         - 0x1: SYSCLK_DIV2
  *         - 0x2: SYSCLK_DIV4
  *         - 0x3: SYSCLK_DIV4
  */
__STATIC_INLINE uint32_t md_cmu_get_ble_baseband_clock(void)
{
    return (READ_BITS(CMU->BLECFG, CMU_BLECFG_BBMCKS_MSK, CMU_BLECFG_BBMCKS_POSS));
}

/**
  * @}
  */

/** @defgroup MD_CMU_Public_Functions_Group22 BLECFG
  * @{
  */

/**
  * @brief  Set BLE clock.
  * @param  bbmcks:
  *         - 0x0: SYSCLK_DIV1
  *         - 0x1: SYSCLK_DIV2
  *         - 0x2: SYSCLK_DIV4
  *         - 0x3: SYSCLK_DIV4
  */
__STATIC_INLINE void md_cmu_set_ble_clock(uint32_t bbscks)
{
    MODIFY_REG(CMU->BLECKS, CMU_BLECKS_BBSCKS_MSK, bbscks << CMU_BLECKS_BBSCKS_POSS);
}

/**
  * @brief  Get BLE clock.
  * @param  NONE
  * @retval bbmcks:
  *         - 0x0: SYSCLK_DIV1
  *         - 0x1: SYSCLK_DIV2
  *         - 0x2: SYSCLK_DIV4
  *         - 0x3: SYSCLK_DIV4
  */
__STATIC_INLINE uint32_t md_cmu_get_ble_clock()
{
    return READ_BITS(CMU->BLECKS, CMU_BLECKS_BBSCKS_MSK, CMU_BLECKS_BBSCKS_POSS);
}

/**
  * @}
  */

/** @defgroup MD_CMU_Public_Functions_Group1 Initialization and Get BUS Clock value
  * @{
  */
extern md_status_t md_cmu_clock_config_default(void);
extern md_status_t md_cmu_clock_config(md_cmu_clock_t clk, uint32_t clock);
extern void md_cmu_pll1_config(uint32_t hosc_clock);
extern void md_cmu_div_config(md_cmu_bus_t bus, md_cmu_div_t div);
extern uint32_t md_cmu_get_hclk1_clock(void);
extern uint32_t md_cmu_get_hclk2_clock(void);
extern uint32_t md_cmu_get_sys_clock(void);
extern uint32_t md_cmu_get_pclk1_clock(void);
extern uint32_t md_cmu_get_pclk2_clock(void);
extern uint32_t md_cmu_get_clock(void);
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
/**
  * @}
  */
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __MD_CMU_H__ */

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
