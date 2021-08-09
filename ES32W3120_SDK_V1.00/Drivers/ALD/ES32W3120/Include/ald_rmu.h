/**********************************************************************************
 *
 * @file    ald_rmu.h
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

#ifndef __ALD_RMU_H__
#define __ALD_RMU_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------ */

/* Exported Macros ----------------------------------------------------------- */
/* Exported Variables -------------------------------------------------------- */
/* Exported Constants -------------------------------------------------------- */

#include "utils.h"

/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup RMU
  * @{
  */

/* Exported Types ------------------------------------------------------------ */

/** @defgroup RMU_Public_Types RMU Public Types
  * @{
  */
/**
  * @brief RMU BOR fliter
  */
typedef enum
{
    RMU_BORFLT_1 = 0x1U,    /**< 1 cycle  */
    RMU_BORFLT_2 = 0x2U,    /**< 2 cycles */
    RMU_BORFLT_3 = 0x3U,    /**< 3 cycles */
    RMU_BORFLT_4 = 0x4U,    /**< 4 cycles */
    RMU_BORFLT_5 = 0x5U,    /**< 5 cycles */
    RMU_BORFLT_6 = 0x6U,    /**< 6 cycles */
    RMU_BORFLT_7 = 0x7U,    /**< 7 cycles */
} rmu_bor_filter_t;

/**
  * @brief RMU BOR33 voltage
  */
typedef enum
{
    RMU_VOL33_1_3  = 0x0U,  /**< 1.3V */
    RMU_VOL33_1_4  = 0x1U,  /**< 1.4V */
    RMU_VOL33_1_5  = 0x2U,  /**< 1.5V */
    RMU_VOL33_1_6  = 0x3U,  /**< 1.6V */
    RMU_VOL33_1_7  = 0x4U,  /**< 1.7V */
    RMU_VOL33_2_0  = 0x5U,  /**< 2.0V */
    RMU_VOL33_2_5  = 0x6U,  /**< 2.5V */
    RMU_VOL33_2_7  = 0x7U,  /**< 2.7V */
    RMU_VOL33_DISABLE = 0xFF,    /**< Disable BOR3.3v */
} rmu_bor33_vol_t;

/**
  * @brief RMU BOR33 voltage
  */
typedef enum
{
    RMU_VOL11_0_35  = 0x2U, /**< 0.35V */
    RMU_VOL11_0_45  = 0x3U, /**< 0.45V */
    RMU_VOL11_0_55  = 0x0U, /**< 0.55V */
    RMU_VOL11_0_65  = 0x5U, /**< 0.65V */
    RMU_VOL11_0_75  = 0x6U, /**< 0.75V */
    RMU_VOL11_DISABLE = 0xFF,    /**< Disable BOR1.1v */
} rmu_bor11_vol_t;

/**
  * @brief RMU reset status
  */
typedef enum
{
    RMU_RST_POR    = (1U << 0), /**< POR */
    RMU_RST_WAKEUP = (1U << 1), /**< WAKEUP */
    RMU_RST_BOR    = (1U << 2), /**< BOR */
    RMU_RST_NMRST  = (1U << 3), /**< NMRST */
    RMU_RST_IWDT   = (1U << 4), /**< IWDT */
    RMU_RST_WWDT   = (1U << 5), /**< WWDT */
    RMU_RST_LOCKUP = (1U << 6), /**< LOCKUP */
    RMU_RST_CHIP   = (1U << 7), /**< CHIP */
    RMU_RST_MCU    = (1U << 8), /**< MCU */
    RMU_RST_CPU    = (1U << 9), /**< CPU */
    RMU_RST_CFG_WORD    = (1U << 10),   /**< CFG */
    RMU_RST_CFGERR = (1U << 16),    /**< CFG Error */
    RMU_RST_ALL    = (0xFFFFFU),    /**< ALL */
} rmu_state_t;

/**
  * @brief RMU periperal select bit
  * @verbatim
      In this module, for the convenience of code maintenance,
      TIMERx is used to indicate the sequence of the timer peripheral.
      Different product series TIMERx represent different meanings:
      1. For ES32F36xx series:
      TIMER0 ----> AD16C4T0
      TIMER1 ----> AD16C4T1
      TIMER2 ----> GP32C4T0
      TIMER3 ----> GP32C4T1
      TIMER4 ----> BS16T0
      TIMER5 ----> BS16T1
      TIMER6 ----> GP16C4T0
      TIMER7 ----> GP16C4T1

      2. For ES32F393x/ES32F336x/ES32F392x series:
      TIMER0 ----> GP16C4T0
      TIMER1 ----> GP16C4T1
      TIMER2 ----> GP32C4T0
      TIMER3 ----> GP32C4T1
      TIMER4 ----> BS16T0
      TIMER5 ----> BS16T1
      TIMER6 ----> GP16C4T2
      TIMER7 ----> GP16C4T3
    @endverbatim
  */
typedef enum
{
    RMU_PERH_GPIO    = (1U << 0),       /**< AHB1: GPIO */
    RMU_PERH_CRC     = (1U << 1),       /**< AHB1: CRC */
    RMU_PERH_CALC    = (1U << 2),       /**< AHB1: CALC */
    RMU_PERH_CRYPT   = (1U << 3),       /**< AHB1: CRYPT */
    RMU_PERH_TRNG    = (1U << 4),       /**< AHB1: TRNG */
    RMU_PERH_PIS     = (1U << 5),       /**< AHB1: PIS */
    RMU_PERH_SM3     = (1U << 8),       /**< AHB1: SM3 */
    RMU_PERH_CHIP    = (1U << 0)  | (1U << 27), /**< AHB2: CHIP */
    RMU_PERH_CPU     = (1U << 1)  | (1U << 27), /**< AHB2: CPU */
    RMU_PERH_TIMER0  = (1U << 0)  | (1U << 28), /**< APB1: TIMER0 */
    RMU_PERH_TIMER1  = (1U << 1)  | (1U << 28), /**< APB1: TIMER1 */
    RMU_PERH_TIMER2  = (1U << 2)  | (1U << 28), /**< APB1: TIMER2 */
    RMU_PERH_TIMER3  = (1U << 3)  | (1U << 28), /**< APB1: TIMER3 */
    RMU_PERH_TIMER4  = (1U << 4)  | (1U << 28), /**< APB1: TIMER4 */
    RMU_PERH_TIMER5  = (1U << 5)  | (1U << 28), /**< APB1: TIMER5 */
    RMU_PERH_UART0   = (1U << 8)  | (1U << 28), /**< APB1: UART0 */
    RMU_PERH_UART1   = (1U << 9)  | (1U << 28), /**< APB1: UART1 */
    RMU_PERH_UART2   = (1U << 10) | (1U << 28), /**< APB1: UART2 */
    RMU_PERH_SPI0    = (1U << 16) | (1U << 28), /**< APB1: SPI0 */
    RMU_PERH_SPI1    = (1U << 17) | (1U << 28), /**< APB1: SPI1 */
    RMU_PERH_SPI2    = (1U << 18) | (1U << 28), /**< APB1: SPI2 */
    RMU_PERH_I2C0    = (1U << 20) | (1U << 28), /**< APB1: I2C0 */
    RMU_PERH_I2C1    = (1U << 21) | (1U << 28), /**< APB1: I2C1 */
    RMU_PERH_ADPCM   = (1U << 22) | (1U << 28), /**< APB1: ADPCM */
    RMU_PERH_TK      = (1U << 23) | (1U << 28), /**< APB1: TK */
    RMU_PERH_ECC     = (1U << 26) | (1U << 28),  /**< APB1: ECC */
    RMU_PERH_PDPCM   = (1U << 27) | (1U << 28),  /**< APB1: PDPCM */
    RMU_PERH_QSPI    = (1U << 28) | (1U << 28),  /**< APB1: QSPI */
    RMU_PERH_KSCAN   = (1U << 29) | (1U << 28),  /**< APB1: KSCAN */
    RMU_PERH_QUAD    = (1U << 30) | (1U << 28),  /**< APB1: QUAD */
    RMU_PERH_LP16T   = (1U << 0)  | (1U << 29), /**< APB2: LP16T */
    RMU_PERH_ADC0    = (1U << 4)  | (1U << 29), /**< APB2: ADC0 */
    RMU_PERH_WWDT    = (1U << 12) | (1U << 29), /**< APB2: WWDT */
    RMU_PERH_IWDT    = (1U << 14) | (1U << 29), /**< APB2: IWDT */
    RMU_PERH_RTC     = (1U << 15) | (1U << 29), /**< APB2: RTC */
    RMU_PERH_BLEMDM  = (1U << 0)  | (5U << 27), /**< APB3: BLEMDM */
    RMU_PERH_BLEMAST = (1U << 0)  | (6U << 27), /**< AHB2BLE: BLEMAST */
    RMU_PERH_BLECRYPT = (1U << 1)  | (6U << 27), /**< AHB2BLE: BLECRYPT  */
    RMU_PERH_BLELP   = (1U << 2)  | (6U << 27), /**< AHB2BLE: BLELP */
} rmu_peripheral_t;
/**
  * @}
  */

/**
  * @defgroup RMU_Private_Macros RMU Private Macros
  * @{
  */
#define IS_RMU_BORFLT(x)    (((x) == RMU_BORFLT_1) || \
                             ((x) == RMU_BORFLT_2) || \
                             ((x) == RMU_BORFLT_3) || \
                             ((x) == RMU_BORFLT_4) || \
                             ((x) == RMU_BORFLT_5) || \
                             ((x) == RMU_BORFLT_6) || \
                             ((x) == RMU_BORFLT_7))
#define IS_RMU_BORVOL33(x)  (((x) == RMU_VOL33_1_3) || \
                             ((x) == RMU_VOL33_1_4) || \
                             ((x) == RMU_VOL33_1_5) || \
                             ((x) == RMU_VOL33_1_6) || \
                             ((x) == RMU_VOL33_1_7) || \
                             ((x) == RMU_VOL33_2_0) || \
                             ((x) == RMU_VOL33_2_5) || \
                             ((x) == RMU_VOL33_2_7) || \
                             ((x) == RMU_VOL33_DISABLE))
#define IS_RMU_BORVOL09(x)  (((x) == RMU_VOL11_0_35) || \
                             ((x) == RMU_VOL11_0_45) || \
                             ((x) == RMU_VOL11_0_55) || \
                             ((x) == RMU_VOL11_0_65) || \
                             ((x) == RMU_VOL11_0_75) || \
                             ((x) == RMU_VOL11_DISABLE))
#define IS_RMU_STATE(x)     (((x) == RMU_RST_POR)    || \
                             ((x) == RMU_RST_WAKEUP) || \
                             ((x) == RMU_RST_BOR)    || \
                             ((x) == RMU_RST_NMRST)  || \
                             ((x) == RMU_RST_IWDT)   || \
                             ((x) == RMU_RST_WWDT)   || \
                             ((x) == RMU_RST_LOCKUP) || \
                             ((x) == RMU_RST_CHIP)   || \
                             ((x) == RMU_RST_MCU)    || \
                             ((x) == RMU_RST_CPU)    || \
                             ((x) == RMU_RST_CFG_WORD)  || \
                             ((x) == RMU_RST_CFGERR)    || \
                             ((x) == RMU_RST_ALL))
#define IS_RMU_STATE_CLEAR(x)   (((x) == RMU_RST_POR)    || \
                                 ((x) == RMU_RST_WAKEUP) || \
                                 ((x) == RMU_RST_BOR)    || \
                                 ((x) == RMU_RST_NMRST)  || \
                                 ((x) == RMU_RST_IWDT)   || \
                                 ((x) == RMU_RST_WWDT)   || \
                                 ((x) == RMU_RST_LOCKUP) || \
                                 ((x) == RMU_RST_CHIP)   || \
                                 ((x) == RMU_RST_MCU)    || \
                                 ((x) == RMU_RST_CPU)    || \
                                 ((x) == RMU_RST_CFG_WORD) || \
                                 ((x) == RMU_RST_ALL))
#define IS_RMU_PERH(x)      (((x) ==RMU_PERH_GPIO)             || \
                             ((x) ==RMU_PERH_CRC)         || \
                             ((x) ==RMU_PERH_CALC)        || \
                             ((x) ==RMU_PERH_CRYPT)       || \
                             ((x) ==RMU_PERH_TRNG)        || \
                             ((x) ==RMU_PERH_PIS)         || \
                             ((x) ==RMU_PERH_SM3)         || \
                             ((x) ==RMU_PERH_CHIP)        || \
                             ((x) ==RMU_PERH_CPU)         || \
                             ((x) ==RMU_PERH_TIMER0)      || \
                             ((x) ==RMU_PERH_TIMER1)      || \
                             ((x) ==RMU_PERH_TIMER2)      || \
                             ((x) ==RMU_PERH_TIMER3)      || \
                             ((x) ==RMU_PERH_TIMER4)      || \
                             ((x) ==RMU_PERH_TIMER5)      || \
                             ((x) ==RMU_PERH_UART0)       || \
                             ((x) ==RMU_PERH_UART1)       || \
                             ((x) ==RMU_PERH_UART2)       || \
                             ((x) ==RMU_PERH_SPI0)        || \
                             ((x) ==RMU_PERH_SPI1)        || \
                             ((x) ==RMU_PERH_SPI2)        || \
                             ((x) ==RMU_PERH_I2C0)        || \
                             ((x) ==RMU_PERH_I2C1)        || \
                             ((x) ==RMU_PERH_ADPCM)       || \
                             ((x) ==RMU_PERH_TK)          || \
                             ((x) ==RMU_PERH_ECC)         || \
                             ((x) ==RMU_PERH_PDPCM)       || \
                             ((x) ==RMU_PERH_QSPI)        || \
                             ((x) ==RMU_PERH_KSCAN)       || \
                             ((x) ==RMU_PERH_QUAD)        || \
                             ((x) ==RMU_PERH_LP16T)       || \
                             ((x) ==RMU_PERH_ADC0)        || \
                             ((x) ==RMU_PERH_WWDT)        || \
                             ((x) ==RMU_PERH_IWDT)        || \
                             ((x) ==RMU_PERH_RTC)         || \
                             ((x) ==RMU_PERH_BLEMDM)      || \
                             ((x) ==RMU_PERH_BLEMAST)     || \
                             ((x) ==RMU_PERH_BLECRYPT)    || \
                             ((x) ==RMU_PERH_BLELP))

/**
  * @}
  */

/* Exported Functions -------------------------------------------------------- */

/** @addtogroup RMU_Public_Functions
  * @{
  */
void ald_rmu_bor_config(rmu_bor_filter_t flt, rmu_bor33_vol_t vol33, rmu_bor11_vol_t vol11);
uint32_t ald_rmu_get_reset_status(rmu_state_t state);
void ald_rmu_clear_reset_status(rmu_state_t state);
void ald_rmu_reset_periperal(rmu_peripheral_t perh);
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

#endif /* __ALD_RMU_H__ */

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
