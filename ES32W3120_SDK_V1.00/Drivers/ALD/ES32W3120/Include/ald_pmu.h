/**********************************************************************************
 *
 * @file    ald_pmu.h
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

#ifndef __ALD_PMU_H__
#define __ALD_PMU_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------ */

#include "utils.h"
#include "ald_syscfg.h"
#include "ald_bkpc.h"

/* Exported Macros ----------------------------------------------------------- */
/* Exported Variables -------------------------------------------------------- */
/* Exported Constants -------------------------------------------------------- */

/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup PMU
  * @{
  */

/** @defgroup PMU_Public_Macros PMU Public Macros
  * @{
  */
#define PMU_LPSTOP_ENABLE()             \
    do {                            \
        SYSCFG_UNLOCK();                \
        SET_BIT(PMU->CR0, PMU_CR0_LPSTOP_MSK);      \
        SYSCFG_LOCK();                  \
    } while (0)
#define PMU_LPSTOP_DISABLE()                \
    do {                            \
        SYSCFG_UNLOCK();                \
        CLEAR_BIT(PMU->CR0, PMU_CR0_LPSTOP_MSK);    \
        SYSCFG_LOCK();                  \
    } while (0)
#define PMU_FLASH_MODE_IDLE()               \
    do {                            \
        SYSCFG_UNLOCK();                \
        CLEAR_BIT(PMU->CR0, PMU_CR0_SFPD_MSK);      \
        SYSCFG_LOCK();                  \
    } while (0)
#define PMU_FLASH_MODE_WAIT()               \
    do {                            \
        SYSCFG_UNLOCK();                \
        SET_BIT(PMU->CR0, PMU_CR0_SFPD_MSK);        \
        SYSCFG_LOCK();                  \
    } while (0)
#define PMU_MTSTOP_ENABLE()             \
    do {                            \
        SYSCFG_UNLOCK();                \
        SET_BIT(PMU->CR0, PMU_CR0_MTSTOP_MSK);      \
        SYSCFG_LOCK();                  \
    } while (0)
#define PMU_MTSTOP_DISABLE()                \
    do {                            \
        SYSCFG_UNLOCK();                \
        CLEAR_BIT(PMU->CR0, PMU_CR0_MTSTOP_MSK);    \
        SYSCFG_LOCK();                  \
    } while (0)
#define PMU_VREF_ENABLE()               \
    do {                            \
        SYSCFG_UNLOCK();                \
        SET_BIT(PMU->VREFCR, PMU_VREFCR_VREFEN_MSK);    \
        SYSCFG_LOCK();                  \
    } while (0)
#define PMU_VREF_DISABLE()              \
    do {                            \
        SYSCFG_UNLOCK();                \
        CLEAR_BIT(PMU->VREFCR, PMU_VREFCR_VREFEN_MSK);  \
        SYSCFG_LOCK();                  \
    } while (0)

#define PMU_GET_LVD_STATUS()    (READ_BITS(PMU->LVDCR, PMU_LVDCR_LVDO_MSK, PMU_LVDCR_LVDO_POS))
/**
  * @}
  */

/* Exported Types ------------------------------------------------------------ */

/** @defgroup PMU_Public_Types PMU Public Types
  * @{
  */
/**
  * @brief Low power mode
  */
typedef enum
{
    PMU_LP_STOP1   = 0x0U,  /**< Stop1 */
    PMU_LP_STOP2   = 0x1U,  /**< Stop2 */
    PMU_LP_STANDBY = 0x2U,  /**< Standby */
} pmu_lp_mode_t;

/**
  * @brief LDO_18 mode
  */
typedef enum
{
    PMU_LDO_18_DRV_HIGH = 0x0U, /**< High drive */
    PMU_LDO_18_DRV_LOW  = 0x1U, /**< Low drive */
    PMU_LDO_18_HOLD     = 0x2U, /**< Hold */
    PMU_LDO_18_OFF      = 0x3U, /**< Turn off */
} pmu_ldo_18_mode_t;

typedef enum
{
    PMU_SR_WUF      = (1U << 0),    /**< WakeUp status */
    PMU_SR_STANDBYF = (1U << 1),    /**< Standby status */
} pmu_status_t;

/**
  * @brief LVD voltage select
  */
typedef enum
{
    PMU_LVD_VOL_SEL_1_8 = 0x0U,  /**< 1.8V */
    PMU_LVD_VOL_SEL_1_9 = 0x1U,  /**< 1.9V */
    PMU_LVD_VOL_SEL_2_0 = 0x2U,  /**< 2.0V */
    PMU_LVD_VOL_SEL_2_1 = 0x3U,  /**< 2.1V */
    PMU_LVD_VOL_SEL_2_2 = 0x4U,  /**< 2.2V */
    PMU_LVD_VOL_SEL_2_3 = 0x5U,  /**< 2.3V */
    PMU_LVD_VOL_SEL_2_4 = 0x6U,  /**< 2.4V */
    PMU_LVD_VOL_SEL_2_5 = 0x7U,  /**< 2.5V */
    PMU_LVD_VOL_SEL_2_6 = 0x8U,  /**< 2.6V */
    PMU_LVD_VOL_SEL_2_7 = 0x9U,  /**< 2.7V */
    PMU_LVD_VOL_SEL_2_8 = 0xAU,  /**< 2.8V */
    PMU_LVD_VOL_SEL_2_9 = 0xBU,  /**< 2.9V */
    PMU_LVD_VOL_SEL_3_0 = 0xCU,  /**< 3.0V */
} pmu_lvd_voltage_sel_t;

/**
  * @brief LVD trigger mode
  */
typedef enum
{
    PMU_LVD_TRIGGER_RISING_EDGE    = 0x0U,  /**< Rising edge */
    PMU_LVD_TRIGGER_FALLING_EDGE   = 0x1U,  /**< Falling edge */
    PMU_LVD_TRIGGER_HIGH_LEVEL     = 0x2U,  /**< High level */
    PMU_LVD_TRIGGER_LOW_LEVEL      = 0x3U,  /**< Low level */
    PMU_LVD_TRIGGER_RISING_FALLING = 0x4U,  /**< Rising and falling edge */
} pmu_lvd_trigger_mode_t;

/**
  * @brief LDO output voltage selest in low power mode
  */
typedef enum
{
    PMU_LDO_LPMODE_OUTPUT_0_9 = 0x0U,   /**< 0.9V */
    PMU_LDO_LPMODE_OUTPUT_1_0 = 0x1U,   /**< 1.0V */
    PMU_LDO_LPMODE_OUTPUT_1_1 = 0x2U,   /**< 1.1V */
    PMU_LDO_LPMODE_OUTPUT_1_2 = 0x3U,   /**< 1.2V */
} pmu_ldo_lpmode_output_t;

typedef enum
{
    PMU_POWER_SRAM0 = 0x1U,     /**< SRAM0 */
    PMU_POWER_SRAM1 = 0x2U,     /**< SRAM1 */
    PMU_POWER_SRAM2 = 0x4U,     /**< SRAM2 */
    PMU_POWER_SRAM3 = 0x8U,     /**< SRAM3 */
    PMU_POWER_SRAM4 = 0x10U,    /**< SRAM4 */
    PMU_POWER_SRAM5 = 0x20U,    /**< SRAM5 */
    PMU_POWER_CAN   = 0x100U,   /**< CAN */
    PMU_POWER_QSPI  = 0x400U,   /**< QSPI */
    PMU_POWER_USB   = 0x800U,   /**< USB */
    PMU_POWER_ROM   = 0x1000U,  /**< ROM */
} pmu_perh_power_t;

/**
  * @}
  */

/**
  * @defgroup PMU_Private_Macros PMU Private Macros
  * @{
  */
#define IS_PMU_LP_MODE(x)       (((x) == PMU_LP_STOP1) || \
                                 ((x) == PMU_LP_STOP2) || \
                                 ((x) == PMU_LP_STANDBY))
#define IS_PMU_LDO18_MODE(x)        (((x) == PMU_LDO_18_DRV_HIGH) || \
                                     ((x) == PMU_LDO_18_DRV_LOW) || \
                                     ((x) == PMU_LDO_18_HOLD) || \
                                     ((x) == PMU_LDO_18_OFF))
#define IS_PMU_STATUS(x)        (((x) == PMU_SR_WUF) || \
                                 ((x) == PMU_SR_STANDBYF))
#define IS_PMU_LVD_VOL_SEL(x)       (((x) == PMU_LVD_VOL_SEL_1_8) || \
                                     ((x) == PMU_LVD_VOL_SEL_1_9) || \
                                     ((x) == PMU_LVD_VOL_SEL_2_0) || \
                                     ((x) == PMU_LVD_VOL_SEL_2_1) || \
                                     ((x) == PMU_LVD_VOL_SEL_2_2) || \
                                     ((x) == PMU_LVD_VOL_SEL_2_3) || \
                                     ((x) == PMU_LVD_VOL_SEL_2_4) || \
                                     ((x) == PMU_LVD_VOL_SEL_2_5) || \
                                     ((x) == PMU_LVD_VOL_SEL_2_6) || \
                                     ((x) == PMU_LVD_VOL_SEL_2_7) || \
                                     ((x) == PMU_LVD_VOL_SEL_2_8) || \
                                     ((x) == PMU_LVD_VOL_SEL_2_9) || \
                                     ((x) == PMU_LVD_VOL_SEL_3_0))
#define IS_PMU_LVD_TRIGGER_MODE(x)  (((x) == PMU_LVD_TRIGGER_RISING_EDGE)  || \
                                     ((x) == PMU_LVD_TRIGGER_FALLING_EDGE) || \
                                     ((x) == PMU_LVD_TRIGGER_HIGH_LEVEL)   || \
                                     ((x) == PMU_LVD_TRIGGER_LOW_LEVEL)    || \
                                     ((x) == PMU_LVD_TRIGGER_RISING_FALLING))
#define IS_PMU_LDO_LPMODE_OUTPUT(x) (((x) == PMU_LDO_LPMODE_OUTPUT_0_9) || \
                                     ((x) == PMU_LDO_LPMODE_OUTPUT_1_0) || \
                                     ((x) == PMU_LDO_LPMODE_OUTPUT_1_1) || \
                                     ((x) == PMU_LDO_LPMODE_OUTPUT_1_2))
#define IS_PMU_PERH_POWER(x)        (((x) == PMU_POWER_SRAM0) || \
                                     ((x) == PMU_POWER_SRAM1) || \
                                     ((x) == PMU_POWER_SRAM2) || \
                                     ((x) == PMU_POWER_SRAM3) || \
                                     ((x) == PMU_POWER_SRAM4) || \
                                     ((x) == PMU_POWER_SRAM5) || \
                                     ((x) == PMU_POWER_CAN)   || \
                                     ((x) == PMU_POWER_QSPI)  || \
                                     ((x) == PMU_POWER_USB)   || \
                                     ((x) == PMU_POWER_ROM))

/**
  * @}
  */

/* Exported Functions -------------------------------------------------------- */

/** @addtogroup PMU_Public_Functions
  * @{
  */
/** @addtogroup PMU_Public_Functions_Group1
  * @{
  */
/* Low power mode select */
__STATIC_INLINE__ void ald_pmu_sleep()
{
    __WFI();
}

__STATIC_INLINE__ void ald_pmu_sleep_deep()
{
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    __WFI();
}

void ald_pmu_stop1_enter(void);
void ald_pmu_stop2_enter(void);
void ald_pmu_standby_enter(bkpc_wakeup_port_t port, bkpc_wakeup_level_t level);
void ald_pmu_ldo_12_config(type_func_t state);
void ald_pmu_ldo_18_config(pmu_ldo_18_mode_t mode);

#ifdef ES32F336x  /* MCU Series: ES32F336x */
void ald_pmu_lprun_config(pmu_ldo_lpmode_output_t vol, type_func_t state);
#endif /* ES32F336x */

flag_status_t ald_pmu_get_status(pmu_status_t sr);
void ald_pmu_clear_status(pmu_status_t sr);
void ald_pmu_perh_power_config(pmu_perh_power_t perh, type_func_t state);
/**
  * @}
  */
/** @addtogroup PMU_Public_Functions_Group2
  * @{
  */
/* LVD configure */
void ald_pmu_lvd_config(pmu_lvd_voltage_sel_t sel, pmu_lvd_trigger_mode_t mode, type_func_t state);
void ald_lvd_irq_handler(void);
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

#endif /* __ALD_PMU_H__ */

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
