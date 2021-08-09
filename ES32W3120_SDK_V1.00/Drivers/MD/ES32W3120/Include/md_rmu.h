/**********************************************************************************
 *
 * @file    md_rmu.h
 * @brief   Header file of RMU module driver.
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

#ifndef __MD_RMU_H__
#define __MD_RMU_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------ */

/* Exported Macros ----------------------------------------------------------- */
/* Exported Variables -------------------------------------------------------- */
/* Exported Constants -------------------------------------------------------- */

#include "md_utils.h"
#include "type.h"

/** @addtogroup Micro_Driver
  * @{
  */

/** @defgroup MD_RMU RMU
  * @brief RMU micro driver
  * @{
  */

/* Exported Types ------------------------------------------------------------ */

/** @defgroup MD_RMU_Public_Types RMU Public Types
  * @{
  */

/**
  * @brief Standby wakeup port select
  */
typedef enum
{
    MD_RMU_BORFLT_1 = 0x1U, /**< 1 cycle  */
    MD_RMU_BORFLT_2 = 0x2U, /**< 2 cycles */
    MD_RMU_BORFLT_3 = 0x3U, /**< 3 cycles */
    MD_RMU_BORFLT_4 = 0x4U, /**< 4 cycles */
    MD_RMU_BORFLT_5 = 0x5U, /**< 5 cycles */
    MD_RMU_BORFLT_6 = 0x6U, /**< 6 cycles */
    MD_RMU_BORFLT_7 = 0x7U, /**< 7 cycles */
} md_rmu_bor_filter_t;

/**
  * @brief RMU BOR33 voltage
  */
typedef enum
{
    MD_RMU_VOL33_1_3  = 0x0U,   /**< 1.3V */
    MD_RMU_VOL33_1_4  = 0x1U,   /**< 1.4V */
    MD_RMU_VOL33_1_5  = 0x2U,   /**< 1.5V */
    MD_RMU_VOL33_1_6  = 0x3U,   /**< 1.6V */
    MD_RMU_VOL33_1_7  = 0x4U,   /**< 1.7V */
    MD_RMU_VOL33_2_0  = 0x5U,   /**< 2.0V */
    MD_RMU_VOL33_2_5  = 0x6U,   /**< 2.5V */
    MD_RMU_VOL33_2_7  = 0x7U,   /**< 2.7V */
    MD_RMU_VOL33_DISABLE = 0xFF,    /**< Disable BOR3.3v */
} md_rmu_bor33_vol_t;

/**
  * @brief RMU BOR33 voltage
  */
typedef enum
{
    MD_RMU_VOL11_0_35  = 0x2U,  /**< 0.35V */
    MD_RMU_VOL11_0_45  = 0x3U,  /**< 0.45V */
    MD_RMU_VOL11_0_55  = 0x0U,  /**< 0.55V */
    MD_RMU_VOL11_0_65  = 0x5U,  /**< 0.65V */
    MD_RMU_VOL11_0_75  = 0x6U,  /**< 0.75V */
    MD_RMU_VOL11_DISABLE = 0xFF,    /**< Disable BOR1.1v */
} md_rmu_bor11_vol_t;

/**
  * @brief RMU reset status
  */
typedef enum
{
    MD_RMU_RST_POR    = (1U << 0),  /**< POR */
    MD_RMU_RST_WAKEUP = (1U << 1),  /**< WAKEUP */
    MD_RMU_RST_BOR    = (1U << 2),  /**< BOR */
    MD_RMU_RST_NMRST  = (1U << 3),  /**< NMRST */
    MD_RMU_RST_IWDT   = (1U << 4),  /**< IWDT */
    MD_RMU_RST_WWDT   = (1U << 5),  /**< WWDT */
    MD_RMU_RST_LOCKUP = (1U << 6),  /**< LOCKUP */
    MD_RMU_RST_CHIP   = (1U << 7),  /**< CHIP */
    MD_RMU_RST_MCU    = (1U << 8),  /**< MCU */
    MD_RMU_RST_CPU    = (1U << 9),  /**< CPU */
    MD_RMU_RST_CFG    = (1U << 10), /**< CFG */
    MD_RMU_RST_CFGERR = (1U << 16), /**< CFG Error */
    MD_RMU_RST_ALL    = (0xFFFFFU), /**< ALL */
} md_rmu_state_t;

typedef enum
{
    MD_RMU_PERH_GPIO    = (1U << 0),        /**< AHB1: GPIO */
    MD_RMU_PERH_CRC     = (1U << 1),        /**< AHB1: CRC */
    MD_RMU_PERH_CALC    = (1U << 2),        /**< AHB1: CALC */
    MD_RMU_PERH_CRYPT   = (1U << 3),        /**< AHB1: CRYPT */
    MD_RMU_PERH_TRNG    = (1U << 4),        /**< AHB1: TRNG */
    MD_RMU_PERH_PIS     = (1U << 5),        /**< AHB1: PIS */
    MD_RMU_PERH_SM3     = (1U << 8),        /**< AHB1: SM3 */
    MD_RMU_PERH_CHIP    = (1U << 0)  | (1U << 27),  /**< AHB2: CHIP */
    MD_RMU_PERH_CPU     = (1U << 1)  | (1U << 27),  /**< AHB2: CPU */
    MD_RMU_PERH_TIMER0  = (1U << 0)  | (1U << 28),  /**< APB1: TIMER0 */
    MD_RMU_PERH_TIMER1  = (1U << 1)  | (1U << 28),  /**< APB1: TIMER1 */
    MD_RMU_PERH_TIMER2  = (1U << 2)  | (1U << 28),  /**< APB1: TIMER2 */
    MD_RMU_PERH_TIMER3  = (1U << 3)  | (1U << 28),  /**< APB1: TIMER3 */
    MD_RMU_PERH_TIMER4  = (1U << 4)  | (1U << 28),  /**< APB1: TIMER4 */
    MD_RMU_PERH_TIMER5  = (1U << 5)  | (1U << 28),  /**< APB1: TIMER5 */
    MD_RMU_PERH_UART0   = (1U << 8)  | (1U << 28),  /**< APB1: UART0 */
    MD_RMU_PERH_UART1   = (1U << 9)  | (1U << 28),  /**< APB1: UART1 */
    MD_RMU_PERH_UART2   = (1U << 10) | (1U << 28),  /**< APB1: UART2 */
    MD_RMU_PERH_SPI0    = (1U << 16) | (1U << 28),  /**< APB1: SPI0 */
    MD_RMU_PERH_SPI1    = (1U << 17) | (1U << 28),  /**< APB1: SPI1 */
    MD_RMU_PERH_SPI2    = (1U << 18) | (1U << 28),  /**< APB1: SPI2 */
    MD_RMU_PERH_I2C0    = (1U << 20) | (1U << 28),  /**< APB1: I2C0 */
    MD_RMU_PERH_I2C1    = (1U << 21) | (1U << 28),  /**< APB1: I2C1 */
    MD_RMU_PERH_ADPCM   = (1U << 22) | (1U << 28),  /**< APB1: ADPCM */
    MD_RMU_PERH_TK      = (1U << 23) | (1U << 28),  /**< APB1: TK */
    MD_RMU_PERH_ECC     = (1U << 26) | (1U << 28),  /**< APB1: ECC */
    MD_RMU_PERH_PDPCM   = (1U << 27) | (1U << 28),  /**< APB1: PDPCM */
    MD_RMU_PERH_QSPI    = (1U << 28) | (1U << 28),  /**< APB1: QSPI */
    MD_RMU_PERH_KSCAN   = (1U << 29) | (1U << 28),  /**< APB1: KSCAN */
    MD_RMU_PERH_QUAD    = (1U << 30) | (1U << 28),  /**< APB1: QUAD */
    MD_RMU_PERH_LP16T   = (1U << 0)  | (1U << 29),  /**< APB2: LP16T */
    MD_RMU_PERH_ADC0    = (1U << 4)  | (1U << 29),  /**< APB2: ADC0 */
    MD_RMU_PERH_WWDT    = (1U << 12) | (1U << 29),  /**< APB2: WWDT */
    MD_RMU_PERH_IWDT    = (1U << 14) | (1U << 29),  /**< APB2: IWDT */
    MD_RMU_PERH_RTC     = (1U << 15) | (1U << 29),  /**< APB2: RTC */
    MD_RMU_PERH_BLEMDM  = (1U << 0)  | (5U << 27),  /**< APB3: BLEMDM */
    MD_RMU_PERH_BLEMAST = (1U << 0)  | (6U << 27),  /**< AHB2BLE: BLEMAST */
    MD_RMU_PERH_BLECRYPT = (1U << 1)  | (6U << 27), /**< AHB2BLE: BLECRYPT  */
    MD_RMU_PERH_BLELP   = (1U << 2)  | (6U << 27),  /**< AHB2BLE: BLELP */
} md_rmu_peripheral_t;
/**
  * @}
  */

/* Exported Functions -------------------------------------------------------- */

/** @defgroup MD_RMU_Public_Functions RMU Public Functions
  * @{
  */
/** @defgroup MD_RMU_Public_Functions_Group2 CR
  * @{
  */
/**
  * @brief  Set BOR3.3 threshold voltage.
  * @param  vol for BOR3.3 threshold.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_set_bor33_voltage(md_rmu_bor33_vol_t vol)
{
    MODIFY_REG(RMU->CSR, RMU_CSR_BOR33VS_MSK, vol << RMU_CSR_BOR33VS_POSS);
}

/**
  * @brief  Get BOR3.3 threshold voltage.
  * @retval Voltage for BOR3.3 threshold.
  */
__STATIC_INLINE uint32_t md_rmu_get_bor33_voltage(void)
{
    return READ_BITS(RMU->CSR, RMU_CSR_BOR33VS_MSK, RMU_CSR_BOR33VS_POSS);
}

/**
  * @brief  Set BOR1.1 threshold voltage.
  * @param  vol for BOR1.1 threshold.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_set_bor11_voltage(md_rmu_bor11_vol_t vol)
{
    MODIFY_REG(RMU->CSR, RMU_CSR_BOR09VS_MSK, vol << RMU_CSR_BOR09VS_POSS);
}

/**
  * @brief  Get BOR1.1 threshold voltage.
  * @retval Voltage for BOR1.1 threshold.
  */
__STATIC_INLINE uint32_t md_rmu_get_bor11_voltage(void)
{
    return READ_BITS(RMU->CSR, RMU_CSR_BOR09VS_MSK, RMU_CSR_BOR09VS_POSS);
}

/**
  * @brief  Enable rmu BOR1.1.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_bor11(void)
{
    SET_BIT(RMU->CSR, RMU_CSR_BOR09EN_MSK);
}

/**
  * @brief  Disable rmu BOR1.1.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_disable_bor11(void)
{
    CLEAR_BIT(RMU->CSR, RMU_CSR_BOR09EN_MSK);
}

/**
  * @brief  Set period for BOR filter.
  * @param  period for BOR filter.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_set_bor_filter_period(md_rmu_bor_filter_t period)
{
    MODIFY_REG(RMU->CSR, RMU_CSR_BORFLT_MSK, period << RMU_CSR_BORFLT_POSS);
}

/**
  * @brief  Get period for BOR filter.
  * @param  none.
  * @retval period for BOR filter.
  */
__STATIC_INLINE uint32_t md_rmu_get_bor_filter_period(void)
{
    return READ_BITS(RMU->CSR, RMU_CSR_BORFLT_MSK, RMU_CSR_BORFLT_POSS);
}

/**
  * @brief  Enable rmu BOR3.3.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_bor33(void)
{
    SET_BIT(RMU->CSR, RMU_CSR_BOR33EN_MSK);
}


/**
  * @brief  Disable rmu BOR.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_disable_bor33(void)
{
    CLEAR_BIT(RMU->CSR, RMU_CSR_BOR33EN_MSK);
}

/**
  * @brief  Check if rmu is enable bor33.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_enable_bor33(void)
{
    return (READ_BIT(RMU->CSR, RMU_CSR_BOR33EN_MSK) == (RMU_CSR_BOR33EN_MSK));
}

/**
  * @brief  Check if rmu is enable bor11.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_enable_bor11(void)
{
    return (READ_BIT(RMU->CSR, RMU_CSR_BOR09EN_MSK) == (RMU_CSR_BOR09EN_MSK));
}
/**
  * @}
  */
/** @defgroup MD_RMU_Public_Functions_Group3 RSTSR
  * @{
  */
/**
  * @brief  Get rmu configuration byte flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_cfgerr(void)
{
    return (READ_BIT(RMU->RSTSR, RMU_RSTSR_CFGERR_MSK) == (RMU_RSTSR_CFGERR_MSK));
}

/**
  * @brief  Get rmu configuration word reset flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_cfg_word(void)
{
    return (READ_BIT(RMU->RSTSR, RMU_RSTSR_CFG_WORD_MSK) == (RMU_RSTSR_CFG_WORD_MSK));
}

/**
  * @brief  Get rmu cpu reset by soft flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_cpu(void)
{
    return (READ_BIT(RMU->RSTSR, RMU_RSTSR_CPU_MSK) == (RMU_RSTSR_CPU_MSK));
}

/**
  * @brief  Get rmu mcu reset by soft flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_mcu(void)
{
    return (READ_BIT(RMU->RSTSR, RMU_RSTSR_MCU_MSK) == (RMU_RSTSR_MCU_MSK));
}

/**
  * @brief  Get rmu chip reset by soft flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_chip(void)
{
    return (READ_BIT(RMU->RSTSR, RMU_RSTSR_CHIP_MSK) == (RMU_RSTSR_CHIP_MSK));
}

/**
  * @brief  Get rmu lockup reset flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_lockup(void)
{
    return (READ_BIT(RMU->RSTSR, RMU_RSTSR_LOCKUP_MSK) == (RMU_RSTSR_LOCKUP_MSK));
}

/**
  * @brief  Get rmu wwdt reset flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_wwdt(void)
{
    return (READ_BIT(RMU->RSTSR, RMU_RSTSR_WWDTF_MSK) == (RMU_RSTSR_WWDTF_MSK));
}

/**
  * @brief  Get rmu iwdt reset flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_iwdt(void)
{
    return (READ_BIT(RMU->RSTSR, RMU_RSTSR_IWDTF_MSK) == (RMU_RSTSR_IWDTF_MSK));
}

/**
  * @brief  Get rmu nmrst reset flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_nmrst(void)
{
    return (READ_BIT(RMU->RSTSR, RMU_RSTSR_NMRST_MSK) == (RMU_RSTSR_NMRST_MSK));
}

/**
  * @brief  Get rmu bor reset flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_bor(void)
{
    return (READ_BIT(RMU->RSTSR, RMU_RSTSR_BOR_MSK) == (RMU_RSTSR_BOR_MSK));
}

/**
  * @brief  Get rmu wake up reset flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_wakeup(void)
{
    return (READ_BIT(RMU->RSTSR, RMU_RSTSR_WAKEUP_MSK) == (RMU_RSTSR_WAKEUP_MSK));
}

/**
  * @brief  Get rmu por reset flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_por(void)
{
    return (READ_BIT(RMU->RSTSR, RMU_RSTSR_POR_MSK) == (RMU_RSTSR_POR_MSK));
}
/**
  * @}
  */
/** @defgroup MD_RMU_Public_Functions_Group4 CRSTSR
  * @{
  */
/**
  * @brief  Clear rmu configuration word reset flag.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_clear_flag_cfg_word(void)
{
    SET_BIT(RMU->CRSTSR, RMU_CRSTSR_CFG_WORD_MSK);
}

/**
  * @brief  Clear rmu cpu reset by soft flag.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_clear_flag_cpu(void)
{
    SET_BIT(RMU->CRSTSR, RMU_CRSTSR_CPU_MSK);
}

/**
  * @brief  Clear rmu mcu reset by soft flag.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_clear_flag_mcu(void)
{
    SET_BIT(RMU->CRSTSR, RMU_CRSTSR_MCU_MSK);
}

/**
  * @brief  Clear rmu chip reset by soft flag.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_clear_flag_chip(void)
{
    SET_BIT(RMU->CRSTSR, RMU_CRSTSR_CHIP_MSK);
}

/**
  * @brief  Clear rmu lockup reset by soft flag.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_clear_flag_lockup(void)
{
    SET_BIT(RMU->CRSTSR, RMU_CRSTSR_LOCKUP_MSK);
}

/**
  * @brief  Clear rmu wwdt reset by soft flag.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_clear_flag_wwdt(void)
{
    SET_BIT(RMU->CRSTSR, RMU_CRSTSR_WWDTC_MSK);
}

/**
  * @brief  Clear rmu iwdt reset by soft flag.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_clear_flag_iwdt(void)
{
    SET_BIT(RMU->CRSTSR, RMU_CRSTSR_IWDTC_MSK);
}

/**
  * @brief  Clear rmu nmrst reset by soft flag.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_clear_flag_nmrst(void)
{
    SET_BIT(RMU->CRSTSR, RMU_CRSTSR_NMRST_MSK);
}

/**
  * @brief  Clear rmu bor reset by soft flag.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_clear_flag_bor(void)
{
    SET_BIT(RMU->CRSTSR, RMU_CRSTSR_BOR_MSK);
}

/**
  * @brief  Clear rmu wakeup reset flag.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_clear_flag_wakeup(void)
{
    SET_BIT(RMU->CRSTSR, RMU_CRSTSR_WAKEUP_MSK);
}

/**
  * @brief  Clear rmu por reset flag.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_clear_flag_por(void)
{
    SET_BIT(RMU->CRSTSR, RMU_CRSTSR_POR_MSK);
}
/**
  * @}
  */
/** @defgroup MD_RMU_Public_Functions_Group5 AHB1RSTR
  * @{
  */
/**
  * @brief  Reset sm3 periperal which depend on AHB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_sm3_reset(void)
{
    SET_BIT(RMU->AHB1RSTR, RMU_AHB1RSTR_SM3RST_MSK);
}

/**
  * @brief  Reset pis periperal which depend on AHB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_pis_reset(void)
{
    SET_BIT(RMU->AHB1RSTR, RMU_AHB1RSTR_PISRST_MSK);
}

/**
  * @brief  Reset trng periperal which depend on AHB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_trng_reset(void)
{
    SET_BIT(RMU->AHB1RSTR, RMU_AHB1RSTR_TRNGRST_MSK);
}

/**
  * @brief  Reset crypt periperal which depend on AHB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_crypt_reset(void)
{
    SET_BIT(RMU->AHB1RSTR, RMU_AHB1RSTR_CRYPTRST_MSK);
}

/**
  * @brief  Reset calc periperal which depend on AHB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_calc_reset(void)
{
    SET_BIT(RMU->AHB1RSTR, RMU_AHB1RSTR_CALCRST_MSK);
}

/**
  * @brief  Reset crc periperal which depend on AHB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_crc_reset(void)
{
    SET_BIT(RMU->AHB1RSTR, RMU_AHB1RSTR_CRCRST_MSK);
}

/**
  * @brief  Reset gpio periperal which depend on AHB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_gpio_reset(void)
{
    SET_BIT(RMU->AHB1RSTR, RMU_AHB1RSTR_GPIORST_MSK);
}
/**
  * @}
  */
/** @defgroup MD_RMU_Public_Functions_Group6 AHB2RSTR
  * @{
  */
/**
  * @brief  Reset kernel processor which depend on AHB2 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_cpu_reset(void)
{
    SET_BIT(RMU->AHB2RSTR, RMU_AHB2RSTR_CPURST_MSK);
}

/**
  * @brief  Reset full chip .
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_chip_reset(void)
{
    SET_BIT(RMU->AHB2RSTR, RMU_AHB2RSTR_CHIPRST_MSK);
}
/**
  * @}
  */
/** @defgroup MD_RMU_Public_Functions_Group7 APB1RSTR
  * @{
  */

/**
  * @brief  Reset quad periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_quad_reset(void)
{
    SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_QUADRST_MSK);
}

/**
  * @brief  Reset kscan periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_kscan_reset(void)
{
    SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_KSCANRST_MSK);
}

/**
  * @brief  Reset qspi periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_qspi_reset(void)
{
    SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_QSPIRST_MSK);
}

/**
  * @brief  Reset pdpcm periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_pdpcm_reset(void)
{
    SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_PDPCMRST_MSK);
}

/**
  * @brief  Reset ecc periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_ecc_reset(void)
{
    SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_ECCRST_MSK);
}

/**
  * @brief  Reset tk periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_tk_reset(void)
{
    SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_TKRST_MSK);
}

/**
  * @brief  Reset adpcm periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_adpcm_reset(void)
{
    SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_ADPCMRST_MSK);
}

/**
  * @brief  Reset i2c1 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_i2c1_reset(void)
{
    SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_I2C1RST_MSK);
}

/**
  * @brief  Reset i2c0 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_i2c0_reset(void)
{
    SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_I2C0RST_MSK);
}

/**
  * @brief  Reset spi1 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_spi1_reset(void)
{
    SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_SPI1RST_MSK);
}

/**
  * @brief  Reset spi0 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_spi0_reset(void)
{
    SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_SPI0RST_MSK);
}

/**
  * @brief  Reset uart2 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_uart2_reset(void)
{
    SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_UART2RST_MSK);
}

/**
  * @brief  Reset uart1 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_uart1_reset(void)
{
    SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_UART1RST_MSK);
}

/**
  * @brief  Reset uart0 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_uart0_reset(void)
{
    SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_UART0RST_MSK);
}

/**
  * @brief  Reset timer5 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_timer5_reset(void)
{
    SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_TIM5RST_MSK);
}

/**
  * @brief  Reset timer4 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_timer4_reset(void)
{
    SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_TIM4RST_MSK);
}

/**
  * @brief  Reset timer3 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_timer3_reset(void)
{
    SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_TIM3RST_MSK);
}

/**
  * @brief  Reset timer2 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_timer2_reset(void)
{
    SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_TIM2RST_MSK);
}

/**
  * @brief  Reset timer1 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_timer1_reset(void)
{
    SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_TIM1RST_MSK);
}

/**
  * @brief  Reset timer0 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_timer0_reset(void)
{
    SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_TIM0RST_MSK);
}
/**
  * @}
  */
/** @defgroup MD_RMU_Public_Functions_Group8 APB2RSTR
  * @{
  */

/**
  * @brief  Reset rtc periperal which depend on APB2 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_rtc_reset(void)
{
    SET_BIT(RMU->APB2RSTR, RMU_APB2RSTR_RTCRST_MSK);
}

/**
  * @brief  Reset iwdt periperal which depend on APB2 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_iwdt_reset(void)
{
    SET_BIT(RMU->APB2RSTR, RMU_APB2RSTR_IWDTRST_MSK);
}

/**
  * @brief  Reset wwdt periperal which depend on APB2 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_wwdt_reset(void)
{
    SET_BIT(RMU->APB2RSTR, RMU_APB2RSTR_WWDTRST_MSK);
}

/**
  * @brief  Reset adc0 periperal which depend on APB2 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_adc0_reset(void)
{
    SET_BIT(RMU->APB2RSTR, RMU_APB2RSTR_ADC0RST_MSK);
}

/**
  * @brief  Reset lp16t periperal which depend on APB2 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_lp16t_reset(void)
{
    SET_BIT(RMU->APB2RSTR, RMU_APB2RSTR_LP16TRST_MSK);
}

/**
  * @}
  */

/** @defgroup MD_RMU_Public_Functions_Group9 APB3RSTR
  * @{
  */
/**
  * @brief  Reset blemdm periperal which depend on APB2 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_blemdm_reset(void)
{
    SET_BIT(RMU->APB3RSTR, RMU_APB3RSTR_BLEMDMRST_MSK);
}
/**
  * @}
  */

/** @defgroup MD_RMU_Public_Functions_Group9 APB3RSTR
  * @{
  */
/**
  * @brief  Reset blemast periperal which depend on AHB2BLERSTR bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_blemast_reset(void)
{
    SET_BIT(RMU->AHB2BLERSTR, RMU_AHB2BLERSTR_MASTRST_MSK);
}

/**
  * @brief  Reset blecryp periperal which depend on AHB2BLERSTR bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_blecryp_reset(void)
{
    SET_BIT(RMU->AHB2BLERSTR, RMU_AHB2BLERSTR_CRYPTRST_MSK);
}

/**
  * @brief  Reset blelp periperal which depend on AHB2BLERSTR bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_blelp_reset(void)
{
    SET_BIT(RMU->AHB2BLERSTR, RMU_AHB2BLERSTR_LPRST_MSK);
}
/**
  * @}
  */

/** @defgroup MD_RMU_Public_Functions_Group1 Initialization
  * @{
  */
extern void md_rmu_reset(void);
extern void md_rmu_bor_config(md_rmu_bor_filter_t flt, md_rmu_bor33_vol_t vol33, md_rmu_bor11_vol_t vol11);
extern uint32_t md_rmu_get_reset_status(md_rmu_state_t state);
extern void md_rmu_clear_reset_status(md_rmu_state_t state);
extern void md_rmu_reset_periperal(md_rmu_peripheral_t perh);
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

#endif /* __MD_RMU_H__ */

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
