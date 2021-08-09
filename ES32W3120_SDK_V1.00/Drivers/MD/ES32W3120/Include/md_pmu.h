/**********************************************************************************
 *
 * @file    md_pmu.h
 * @brief   Header file of PMU module driver.
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

#ifndef __MD_PMU_H__
#define __MD_PMU_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------ */

/* Exported Macros ----------------------------------------------------------- */
/* Exported Variables -------------------------------------------------------- */
/* Exported Constants -------------------------------------------------------- */

#include "md_utils.h"

/** @addtogroup Micro_Driver
  * @{
  */

/** @defgroup MD_PMU PMU
  * @brief PMU micro driver
  * @{
  */

/* Exported Types ------------------------------------------------------------ */

/** @defgroup MD_PMU_Public_Types PMU Public Types
  * @{
  */

/**
  * @brief Low power mode
  */
typedef enum
{
    MD_PMU_LP_STOP1   = 0x0U,        /**< Stop1 */
    MD_PMU_LP_STOP2   = 0x1U,        /**< Stop2 */
    MD_PMU_LP_STANDBY = 0x2U,        /**< Standby */
} md_pmu_lp_mode_t;

/**
  * @brief LDO_18 mode
  */
typedef enum
{
    MD_PMU_LDO_18_DRV_HIGH = 0x0U, /**< High drive */
    MD_PMU_LDO_18_DRV_LOW  = 0x1U, /**< Low drive */
    MD_PMU_LDO_18_HOLD     = 0x2U, /**< Hold */
    MD_PMU_LDO_18_OFF      = 0x3U, /**< Turn off */
} md_pmu_ldo_18_mode_t;

/**
  * @brief Standby wakeup port select
  */
typedef enum
{
    MD_PMU_STANDBY_PORT_SEL_PA2  = 0x0U,    /**< Wakeup by PA2 */
    MD_PMU_STANDBY_PORT_SEL_PA3  = 0x1U,    /**< Wakeup by PA3 */
    MD_PMU_STANDBY_PORT_SEL_PA4  = 0x2U,    /**< Wakeup by PA4 */
    MD_PMU_STANDBY_PORT_SEL_PA5  = 0x3U,    /**< Wakeup by PA5 */
    MD_PMU_STANDBY_PORT_SEL_PA6  = 0x4U,    /**< Wakeup by PA6 */
    MD_PMU_STANDBY_PORT_SEL_PA7  = 0x5U,    /**< Wakeup by PA7 */
    MD_PMU_STANDBY_PORT_SEL_PA8  = 0x6U,    /**< Wakeup by PA8 */
    MD_PMU_STANDBY_PORT_SEL_PA9  = 0x7U,    /**< Wakeup by PA9 */
    MD_PMU_STANDBY_PORT_SEL_RTC  = 0x9U,    /**< Wakeup by RTC */
    MD_PMU_STANDBY_PORT_SEL_NONE = 0xAU,    /**< NONE */
} md_pmu_wakeup_port_t;

/**
  * @brief Standby wakeup level
  */
typedef enum
{
    MD_PMU_STANDBY_LEVEL_HIGH = 0x0U,   /**< High level */
    MD_PMU_STANDBY_LEVEL_LOW  = 0x1U,   /**< Low level */
} md_pmu_wakeup_level_t;


/**
  * @brief status types
  */
typedef enum
{
    MD_PMU_SR_WUF      = (1U << 0), /**< WakeUp status */
    MD_PMU_SR_STANDBYF = (1U << 1), /**< Standby status */
    MD_PMU_SR_USBRDY   = (1U << 2), /**< USB Readby status */
    MD_PMU_SR_RSTAT    = (1U << 3), /**< RUN/LPRUAN status */
} md_pmu_status_t;

/**
  * @brief LVD voltage select
  */
typedef enum
{
    MD_PMU_LVD_VOL_SEL_1_8 = 0x0U,  /**< 1.8V */
    MD_PMU_LVD_VOL_SEL_1_9 = 0x1U,  /**< 1.9V */
    MD_PMU_LVD_VOL_SEL_2_0 = 0x2U,  /**< 2.0V */
    MD_PMU_LVD_VOL_SEL_2_1 = 0x3U,  /**< 2.1V */
    MD_PMU_LVD_VOL_SEL_2_2 = 0x4U,  /**< 2.2V */
    MD_PMU_LVD_VOL_SEL_2_3 = 0x5U,  /**< 2.3V */
    MD_PMU_LVD_VOL_SEL_2_4 = 0x6U,  /**< 2.4V */
    MD_PMU_LVD_VOL_SEL_2_5 = 0x7U,  /**< 2.5V */
    MD_PMU_LVD_VOL_SEL_2_6 = 0x8U,  /**< 2.6V */
    MD_PMU_LVD_VOL_SEL_2_7 = 0x9U,  /**< 2.7V */
    MD_PMU_LVD_VOL_SEL_2_8 = 0xAU,  /**< 2.8V */
    MD_PMU_LVD_VOL_SEL_2_9 = 0xBU,  /**< 2.9V */
    MD_PMU_LVD_VOL_SEL_3_0 = 0xCU,  /**< 3.0V */
} md_pmu_lvd_voltage_sel_t;

/**
  * @brief LVD trigger mode
  */
typedef enum
{
    MD_PMU_LVD_TRIGGER_RISING_EDGE    = 0x0U,   /**< Rising edge */
    MD_PMU_LVD_TRIGGER_FALLING_EDGE   = 0x1U,   /**< Falling edge */
    MD_PMU_LVD_TRIGGER_HIGH_LEVEL     = 0x2U,   /**< High level */
    MD_PMU_LVD_TRIGGER_LOW_LEVEL      = 0x3U,   /**< Low level */
    MD_PMU_LVD_TRIGGER_RISING_FALLING = 0x4U,   /**< Rising and falling edge */
} md_pmu_lvd_trigger_mode_t;

typedef enum
{
    MD_PMU_POWER_SRAM0 = 0x1U,  /**< SRAM0 */
    MD_PMU_POWER_SRAM1 = 0x2U,  /**< SRAM1 */
    MD_PMU_POWER_SRAM2 = 0x4U,  /**< SRAM2 */
    MD_PMU_POWER_SRAM3 = 0x8U,  /**< SRAM3 */
    MD_PMU_POWER_SRAM4 = 0x10U, /**< SRAM4 */
    MD_PMU_POWER_SRAM5 = 0x20U, /**< SRAM5 */
    MD_PMU_POWER_CAN   = 0x100U,    /**< CAN */
    MD_PMU_POWER_QSPI  = 0x400U,    /**< QSPI */
    MD_PMU_POWER_USB   = 0x800U,    /**< USB */
    MD_PMU_POWER_ROM   = 0x1000U,   /**< ROM */
} md_pmu_perh_power_t;

/**
  * @}
  */

/* Exported Functions -------------------------------------------------------- */

/** @defgroup MD_PMU_Public_Functions PMU Public Functions
  * @{
  */
/** @defgroup MD_PMU_Public_Functions_Group2 CR0
  * @{
  */
/**
  * @brief  Set pmu low power mode.
  * @param  mode: low power mode @see md_pmu_lp_mode_t
  * @retval None
  */
__STATIC_INLINE void md_pmu_set_low_power_mode(md_pmu_lp_mode_t mode)
{
    MODIFY_REG(PMU->CR, PMU_CR_LPM_MSK, mode << PMU_CR_LPM_POSS);
}

/**
  * @brief  Get pmu low power mode.
  * @retval low power mode @see md_pmu_lp_mode_t
  */
__STATIC_INLINE uint32_t md_pmu_get_low_power_mode(void)
{
    return READ_BITS(PMU->CR, PMU_CR_LPM_MSK, PMU_CR_LPM_POSS);
}

/**
  * @brief  Clear wuf flag.
  * @retval None
  */
__STATIC_INLINE void md_pmu_clear_flag_cwuf(void)
{
    SET_BIT(PMU->CR, PMU_CR_CWUF_MSK);
}

/**
  * @brief  Clear standby flag.
  * @retval None
  */
__STATIC_INLINE void md_pmu_clear_flag_standby(void)
{
    SET_BIT(PMU->CR, PMU_CR_CSTANDBYF_MSK);
}

/** @defgroup MD_PMU_Public_Functions_Group4 SR
  * @{
  */
/**
  * @brief  Get Standby flag .
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pmu_is_active_flag_standby(void)
{
    return (READ_BIT(PMU->SR, PMU_SR_STANDBYF_MSK) == PMU_SR_STANDBYF_MSK);
}

/**
  * @brief  Get Wakeup flag .
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pmu_is_active_flag_wakeup(void)
{
    return (READ_BIT(PMU->SR, PMU_SR_WUF_MSK) == PMU_SR_WUF_MSK);
}
/**
  * @}
  */
/** @defgroup MD_PMU_Public_Functions_Group5 LVDCR
  * @{
  */
/**
  * @brief  Get LVD Status flag .
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pmu_is_active_flag_lvdo(void)
{
    return (READ_BIT(PMU->LVDCR, PMU_LVDCR_LVDO_MSK) == PMU_LVDCR_LVDO_MSK);
}

/**
  * @brief  Enable the LVD filter .
  * @retval None
  */
__STATIC_INLINE void md_pmu_enable_lvd_filter(void)
{
    SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDFLT_MSK);
}

/**
  * @brief  Disable the LVD filter .
  * @retval None
  */
__STATIC_INLINE void md_pmu_disable_lvd_filter(void)
{
    CLEAR_BIT(PMU->LVDCR, PMU_LVDCR_LVDFLT_MSK);
}

/**
  * @brief  Check if the LVD filter is enable or disable.
  * @retval State for bit (1 or 0)
  */
__STATIC_INLINE uint32_t md_pmu_is_enable_lvd_filter(void)
{
    return (READ_BIT(PMU->LVDCR, PMU_LVDCR_LVDFLT_MSK) == PMU_LVDCR_LVDFLT_MSK);
}

/**
  * @brief  Set LVD Interrupt mode.
  * @param  mode: lvd interrupt mode @see md_pmu_lvd_trigger_mode_t.
  * @retval None.
  */
__STATIC_INLINE void md_pmu_set_lvd_it_mode(md_pmu_lvd_trigger_mode_t mode)
{
    MODIFY_REG(PMU->LVDCR, PMU_LVDCR_LVIFS_MSK, mode << PMU_LVDCR_LVIFS_POSS);
}

/**
  * @brief  Get LVD Interrupt mode.
  * @retval value for lvd it mode.
  */
__STATIC_INLINE uint32_t md_pmu_get_lvd_it_mode(void)
{
    return READ_BITS(PMU->LVDCR, PMU_LVDCR_LVIFS_MSK, PMU_LVDCR_LVIFS_POSS);
}

/**
  * @brief  Set LVD voltage threshold value.
  * @param  value: threshold value @see md_pmu_lvd_voltage_sel_t.
  * @retval None.
  */
__STATIC_INLINE void md_pmu_set_lvd_vol_threshold(md_pmu_lvd_voltage_sel_t value)
{
    MODIFY_REG(PMU->LVDCR, PMU_LVDCR_LVDS_MSK, value << PMU_LVDCR_LVDS_POSS);
}

/**
  * @brief  Get LVD voltage threshold value.
  * @retval value for lvd voltage threshold @see pmu_lvd_voltage_sel_t.
  */
__STATIC_INLINE uint32_t md_pmu_get_lvd_vol_threshold(void)
{
    return (READ_BITS(PMU->LVDCR, PMU_LVDCR_LVDS_MSK, PMU_LVDCR_LVDS_POSS));
}

/**
  * @brief  Clear LVD interrupt flag bit.
  * @retval None.
  */
__STATIC_INLINE void md_pmu_clear_lvd_it_flag(void)
{
    SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDCIF_MSK);
}

/**
  * @brief  Get LVD interrupt flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pmu_is_active_flag_lvd_it(void)
{
    return (READ_BIT(PMU->LVDCR, PMU_LVDCR_LVDIF_MSK) == PMU_LVDCR_LVDIF_MSK);
}

/**
  * @brief  Enable LVD interrupt.
  * @retval None.
  */
__STATIC_INLINE void md_pmu_enable_lvd_it(void)
{
    SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDIE_MSK);
}

/**
  * @brief  Disable LVD interrupt.
  * @retval None.
  */
__STATIC_INLINE void md_pmu_disable_lvd_it(void)
{
    CLEAR_BIT(PMU->LVDCR, PMU_LVDCR_LVDIE_MSK);
}

/**
  * @brief  Check if LVD interrupt is enable or disable.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pmu_is_enable_lvd_it(void)
{
    return (READ_BIT(PMU->LVDCR, PMU_LVDCR_LVDIE_MSK) == PMU_LVDCR_LVDIE_MSK);
}

/**
  * @brief  Enable LVD.
  * @retval None.
  */
__STATIC_INLINE void md_pmu_enable_lvd(void)
{
    SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDEN_MSK);
}

/**
  * @brief  Disable LVD interrupt.
  * @retval None.
  */
__STATIC_INLINE void md_pmu_disable_lvd(void)
{
    CLEAR_BIT(PMU->LVDCR, PMU_LVDCR_LVDEN_MSK);
}

/**
  * @brief  Check if LVD is enable or disable.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pmu_lvd_is_enable(void)
{
    return (READ_BIT(PMU->LVDCR, PMU_LVDCR_LVDEN_MSK) == PMU_LVDCR_LVDEN_MSK);
}
/**
  * @}
  */
/** @defgroup MD_PMU_Public_Functions_Group6 PWRCR
  * @{
  */

/**
  * @brief  Set SRAM1 entry power down mode.
  * @retval None
  */
__STATIC_INLINE void md_pmu_enable_sram_power_down(void)
{
    SET_BIT(PMU->PWRCR, PMU_PWRCR_SRAMPD_MSK);
}

/**
  * @brief  Set SRAM1 exit power down mode.
  * @retval None
  */
__STATIC_INLINE void md_pmu_disable_sram_power_down(void)
{
    CLEAR_BIT(PMU->PWRCR, PMU_PWRCR_SRAMPD_MSK);
}

/**
  * @brief  Get SRAM1 power mode.
  * @retval srampds power mode.
  */
__STATIC_INLINE uint32_t md_pmu_is_enable_sram_power_down(void)
{
    return (READ_BIT(PMU->PWRCR, PMU_PWRCR_SRAMPD_MSK) == PMU_PWRCR_SRAMPD_MSK);
}

/**
  * @brief  Get SRAM1 power status.
  * @retval srampds power status.
  */
__STATIC_INLINE uint32_t md_pmu_is_active_sram_power_down(void)
{
    return (READ_BIT(PMU->PWRCR, PMU_PWRCR_SRAMPDS_MSK) == PMU_PWRCR_SRAMPDS_MSK);
}

/**
  * @brief  Enable 1.1V Ldo.
  * @retval None
  */
__STATIC_INLINE void md_pmu_enable_ldo1p1(void)
{
    SET_BIT(PMU->PWRCR, PMU_PWRCR_LDO1P1EN_MSK);
}

/**
  * @brief  Disable 1.1V Ldo.
  * @retval None
  */
__STATIC_INLINE void md_pmu_disable_ldo1p1(void)
{
    CLEAR_BIT(PMU->PWRCR, PMU_PWRCR_LDO1P1EN_MSK);
}

/**
  * @brief  Get 1.1V Ldo is enable or disable.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pmu_is_enable_ldo1p1(void)
{
    return (READ_BIT(PMU->PWRCR, PMU_PWRCR_LDO1P1EN_MSK) == PMU_PWRCR_LDO1P1EN_MSK);
}

/**
  * @brief  Get 1.1V LDO flag .
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pmu_is_active_ldo1p1(void)
{
    return (READ_BIT(PMU->PWRCR, PMU_PWRCR_LDO1P1S_MSK) == PMU_PWRCR_LDO1P1S_MSK);
}

/**
  * @brief  Enable Ibias.
  * @retval None
  */
__STATIC_INLINE void md_pmu_enable_ibias(void)
{
    SET_BIT(PMU->PWRCR, PMU_PWRCR_IBIASEN_MSK);
}

/**
  * @brief  Disable Ibias.
  * @retval None
  */
__STATIC_INLINE void md_pmu_disable_ibias(void)
{
    CLEAR_BIT(PMU->PWRCR, PMU_PWRCR_IBIASEN_MSK);
}

/**
  * @brief  Get ibias is enable or disable.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pmu_is_enable_ibias(void)
{
    return (READ_BIT(PMU->PWRCR, PMU_PWRCR_LDO1P1EN_MSK) == PMU_PWRCR_LDO1P1EN_MSK);
}

/**
  * @brief  Set BB Exchange Memory1 entry power down mode.
  * @retval None
  */
__STATIC_INLINE void md_pmu_enable_bbsram_power_down(void)
{
    SET_BIT(PMU->PWRCR, PMU_PWRCR_BBSRAMPD_MSK);
}

/**
  * @brief  Set BB Exchange Memory1 exit power down mode.
  * @retval None
  */
__STATIC_INLINE void md_pmu_disable_bbsram_power_down(void)
{
    CLEAR_BIT(PMU->PWRCR, PMU_PWRCR_BBSRAMPD_MSK);
}

/**
  * @brief  Get BB Exchange Memory1 power down mode is enable or disable.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pmu_is_enable_bbsram_power_down(void)
{
    return (READ_BIT(PMU->PWRCR, PMU_PWRCR_BBSRAMPD_MSK) == PMU_PWRCR_BBSRAMPD_MSK);
}

/**
  * @}
  */

/** @defgroup MD_PMU_Public_Functions_Group8 TWUR
  * @{
  */
/**
  * @brief  Set wake up time.
  * @param  wkt:0-4095
  * @retval None
  */
__STATIC_INLINE void md_pmu_set_wake_up_time(uint32_t mkt)
{
    MODIFY_REG(PMU->TWUR, PMU_TWUR_WKT_MSK, mkt << PMU_TWUR_WKT_POSS);
}

/**
  * @brief  Set wake up time.
  * @param  NONE
  * @retval wkt:0-4095
  */
__STATIC_INLINE uint32_t md_pmu_get_wake_up_time(uint32_t mkt)
{
    return READ_BITS(PMU->TWUR, PMU_TWUR_WKT_MSK, PMU_TWUR_WKT_POSS);
}

/** @defgroup MD_PMU_Public_Functions_Group9 VDETCR
  * @{
  */

/**
  * @brief  Enable VDET.
  * @retval None
  */
__STATIC_INLINE void md_pmu_enable_vdet(void)
{
    SET_BIT(PMU->VDETCR, PMU_VDETCR_EN_MSK);
}
/**
  * @brief  Disable VDET.
  * @retval None
  */
__STATIC_INLINE void md_pmu_disable_vdet(void)
{
    CLEAR_BIT(PMU->VDETCR, PMU_VDETCR_EN_MSK);
}

/**
  * @brief  Check VDET is enable or disable.
  * @retval State of bit (1 or 0).

  */
__STATIC_INLINE uint32_t md_pmu_is_enable_vdet(void)
{
    return (READ_BIT(PMU->VDETCR, PMU_VDETCR_EN_MSK) == PMU_VDETCR_EN_MSK);
}

/**
  * @brief  Set VDET Divided voltage.
  * @param  sel
  *         - 0x0: VOUT=1/6VIN
  *         - 0x2: VOUT=1/3VIN
  *         - 0x4: VOUT=1/2VIN
  *         - 0x8: VOUT=2/3VIN
  * @retval None
  */
__STATIC_INLINE void md_pmu_set_vdet_divided_voltage(uint32_t sel)
{
    MODIFY_REG(PMU->VDETCR, PMU_VDETCR_SEL_MSK, sel << PMU_VDETCR_SEL_POSS);
}

/**
  * @brief  Get VDET Divided voltage.
  * @param  None
  * @retval  sel
  *         - 0x0: VOUT=1/6VIN
  *         - 0x2: VOUT=1/3VIN
  *         - 0x4: VOUT=1/2VIN
  *         - 0x8: VOUT=2/3VIN
  */
__STATIC_INLINE uint32_t md_pmu_get_vdet_divided_voltage(void)
{
    return READ_BITS(PMU->VDETCR, PMU_VDETCR_SEL_MSK, PMU_VDETCR_SEL_POSS);
}

/**
  * @}
  */

/** @defgroup MD_PMU_Public_Functions_Group10 DCCR
  * @{
  */
/**
  * @brief  Enable Nonoverlap CLK wide.
  * @retval None
  */
__STATIC_INLINE void md_pmu_enable_nonoverlap_clock_wide(void)
{
    SET_BIT(PMU->DCCR, PMU_DCCR_DELAY_MSK);
}

/**
  * @brief  Disable Nonoverlap CLK wide.
  * @retval None
  */
__STATIC_INLINE void md_pmu_disable_nonoverlap_clock_wide(void)
{
    CLEAR_BIT(PMU->DCCR, PMU_DCCR_DELAY_MSK);
}

/**
  * @brief  Check Nonoverlap CLK wide is enable or disable.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pmu_is_enable_nonoverlap_clock_wide(void)
{
    return (READ_BIT(PMU->DCCR, PMU_DCCR_DELAY_MSK) == PMU_DCCR_DELAY_MSK);
}

/**
  * @brief  Set DCDC mode.
  * @param  mode:
  *         -0: PWM
  *         -1: BURST
  * @retval None
  */
__STATIC_INLINE void md_pmu_set_dcdc_mode(uint32_t mode)
{
    MODIFY_REG(PMU->DCCR, PMU_DCCR_MODE_MSK, mode << PMU_DCCR_MODE_POS);
}

/**
  * @brief  Get DCDC mode.
  * @param  NONE
  * @retval  mode:
  *         -0: PWM
  *         -1: BURST
  */
__STATIC_INLINE uint32_t md_pmu_get_dcdc_mode(void)
{
    return READ_BITS(PMU->DCCR, PMU_DCCR_MODE_MSK, PMU_DCCR_MODE_POS);
}

/**
  * @brief  Enable overcurrent detect.
  * @retval None
  */
__STATIC_INLINE void md_pmu_enable_overcurrent_detect(void)
{
    SET_BIT(PMU->DCCR, PMU_DCCR_OVCCEN_MSK);
}

/**
  * @brief  Disable overcurrent detect.
  * @retval None
  */
__STATIC_INLINE void md_pmu_disable_overcurrent_detect(void)
{
    CLEAR_BIT(PMU->DCCR, PMU_DCCR_OVCCEN_MSK);
}

/**
  * @brief  Check overcurrent detect is enable or disable.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pmu_is_enable_overcurrent_detect(void)
{
    return (READ_BIT(PMU->DCCR, PMU_DCCR_OVCCEN_MSK) == PMU_DCCR_OVCCEN_MSK);
}

/**
  * @brief  Set PWM OSC capacitance.
  * @param  fs : 0-7
  * @retval None
  */
__STATIC_INLINE void md_pmu_set_pwm_osc_capacitance(uint32_t fs)
{
    MODIFY_REG(PMU->DCCR, PMU_DCCR_FC_MSK, fs << PMU_DCCR_FC_POSS);
}

/**
  * @brief  Get PWM OSC capacitance.
  * @param  NONE
  * @retval  fs : 0-7
  */
__STATIC_INLINE uint32_t md_pmu_get_pwm_osc_capacitance(void)
{
    return READ_BITS(PMU->DCCR, PMU_DCCR_FC_MSK, PMU_DCCR_FC_POSS);
}

/**
  * @brief  Set BURST Hys.
  * @param  hysctl : 0-7
  * @retval None
  */
__STATIC_INLINE void md_pmu_set_burst_hys(uint32_t hysctl)
{
    MODIFY_REG(PMU->DCCR, PMU_DCCR_HYSCTL_MSK, hysctl << PMU_DCCR_HYSCTL_POSS);
}

/**
  * @brief  Get BURST Hys.
  * @param  NONE
  * @retval hysctl : 0-7
  */
__STATIC_INLINE uint32_t md_pmu_get_burst_hys(void)
{
    return READ_BITS(PMU->DCCR, PMU_DCCR_HYSCTL_MSK, PMU_DCCR_HYSCTL_POSS);
}

/**
  * @brief  Set PWM OSC current.
  * @param  fi : 0-7
  * @retval None
  */
__STATIC_INLINE void md_pmu_set_pwm_osc_current(uint32_t fi)
{
    MODIFY_REG(PMU->DCCR, PMU_DCCR_FI_MSK, fi << PMU_DCCR_FI_POSS);
}

/**
  * @brief  Get BURST Hys.
  * @param  NONE
  * @retval fi : 0-7
  */
__STATIC_INLINE uint32_t md_pmu_get_pwm_osc_current(void)
{
    return READ_BITS(PMU->DCCR, PMU_DCCR_FI_MSK, PMU_DCCR_FI_POSS);
}

/**
  * @brief  Set DCDC voltage.
  * @param  vctl : 0-15
  * @retval None
  */
__STATIC_INLINE void md_pmu_set_dcdc_voltage(uint32_t vctl)
{
    MODIFY_REG(PMU->DCCR, PMU_DCCR_VCTL_MSK, vctl << PMU_DCCR_VCTL_POSS);
}

/**
  * @brief  Get DCDC voltage.
  * @param  NONE
  * @retval vctl : 0-7
  */
__STATIC_INLINE uint32_t md_pmu_get_dcdc_voltage(void)
{
    return READ_BITS(PMU->DCCR, PMU_DCCR_VCTL_MSK, PMU_DCCR_VCTL_POSS);
}

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup MD_PMU_Public_Functions_Group1 Initialization
  * @{
  */
__STATIC_INLINE__ void md_pmu_sleep()
{
    __WFI();
}

__STATIC_INLINE__ void md_pmu_sleep_deep()
{
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    __WFI();
}

extern void md_pmu_reset(void);
extern void md_pmu_stop1_enter(void);
extern void md_pmu_stop2_enter(void);
void md_pmu_set_standby_wake_up(md_pmu_wakeup_port_t port, md_pmu_wakeup_level_t level);
extern void md_pmu_standby_enter(void);
extern void md_pmu_perh_power_config(md_pmu_perh_power_t perh, type_func_t state);
extern void md_pmu_lvd_config(md_pmu_lvd_voltage_sel_t sel, md_pmu_lvd_trigger_mode_t mode, type_func_t state);
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

#endif /* __MD_PMU_H__ */

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
