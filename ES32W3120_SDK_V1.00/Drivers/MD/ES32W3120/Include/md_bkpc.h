/**********************************************************************************
 *
 * @file    md_bkpc.h
 * @brief   Header file of BKPC module driver.
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

#ifndef __MD_BKPC_H__
#define __MD_BKPC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------ */
#include "md_utils.h"

/** @addtogroup Micro_Driver
  * @{
  */

/** @defgroup MD_BKPC BKPC
  * @brief BKPC micro driver
  * @{
  */

/** @defgroup MD_BKPC_Public_Types BKPC Public Types
  * @{
  */
/**
  * @brief BKPC preipheral clock select.
  */
typedef enum {
    MD_BKPC_PREH_CLK_ULRC    = 0x0U,	/**< ULRC */
	MD_BKPC_PREH_CLK_LOSM    = 0x1U,	/**< LOSM */
} md_bkpc_preh_clk_t;

/**
  * @brief Standby wakeup port select
  */
typedef enum {
	MD_PMU_STANDBY_PORT_SEL_PA2  = 0x0U,	/**< Wakeup by PA2 */
	MD_PMU_STANDBY_PORT_SEL_PA3  = 0x1U,	/**< Wakeup by PA3 */
	MD_PMU_STANDBY_PORT_SEL_PA4  = 0x2U,	/**< Wakeup by PA4 */
	MD_PMU_STANDBY_PORT_SEL_PA5  = 0x3U,	/**< Wakeup by PA5 */
	MD_PMU_STANDBY_PORT_SEL_PA6  = 0x4U,	/**< Wakeup by PA6 */
	MD_PMU_STANDBY_PORT_SEL_PA7  = 0x5U,	/**< Wakeup by PA7 */
    MD_PMU_STANDBY_PORT_SEL_PA8  = 0x6U,	/**< Wakeup by PA8 */
	MD_PMU_STANDBY_PORT_SEL_PA9  = 0x7U,	/**< Wakeup by PA9 */
	MD_PMU_STANDBY_PORT_SEL_RTC  = 0x9U,	/**< Wakeup by RTC */
    MD_PMU_STANDBY_PORT_SEL_NONE = 0xAU,	/**< NONE */
} md_bkpc_wakeup_port_t;

/**
  * @brief Standby wakeup level
  */
typedef enum {
	MD_PMU_STANDBY_LEVEL_HIGH = 0x0U,	/**< High level */
	MD_PMU_STANDBY_LEVEL_LOW  = 0x1U,	/**< Low level */
} md_bkpc_wakeup_level_t;
/**
  * @}
  */
/** @defgroup MD_BKPC_Public_Macros BKPC Public Macros
  * @{
  */
#define MD_BKPC_LOCK()		(WRITE_REG(BKPC->PROT, 0U))
#define MD_BKPC_UNLOCK()	(WRITE_REG(BKPC->PROT, 0x9669AA55U))
/**
  * @}
  */
/** @defgroup MD_BKPC_Public_Functions BKPC Public Functions
  * @{
  */
/** @defgroup MD_BKPC_Public_Functions_Group2 PROT
  * @{
  */
/**
  * @brief  Lock bkpc register.
  * @retval None
  */
__STATIC_INLINE void md_bkpc_enable_lock(void)
{
	WRITE_REG(BKPC->PROT, 0);
}

/**
  * @brief  Unlock bkpc register.
  * @retval None
  */
__STATIC_INLINE void md_bkpc_disable_lock(void)
{
	WRITE_REG(BKPC->PROT, 0x9669AA55U);
}

/**
  * @brief  Check if lock is enabled or disabled.
  * @retval Status:
  *           - 0: Unlock
  *           - 1: Lock
  */
__STATIC_INLINE uint32_t md_bkpc_lock_is_enable(void)
{
	return READ_BITS(BKPC->PROT, BKPC_PROT_PROT_MSK, BKPC_PROT_PROT_POS);
}
/**
  * @}
  */
/** @defgroup MD_BKPC_Public_Functions_Group3 PCCR
  * @{
  */

/**
  * @brief  Enable RTC clock.
  * @retval None
  */
__STATIC_INLINE void md_bkpc_enable_rtcck(void)
{
	SET_BIT(BKPC->PCCR, BKPC_PCCR_RTCCKEN_MSK);
}

/**
  * @brief  Disable RTC clock.
  * @retval None
  */
__STATIC_INLINE void md_bkpc_disable_rtcck(void)
{
	CLEAR_BIT(BKPC->PCCR, BKPC_PCCR_RTCCKEN_MSK);
}

/**
  * @brief  Check if RTC clock is enabled or disabled.
  * @retval Status:
  *           - 0: Disable
  *           - 1: Enable
  */
__STATIC_INLINE uint32_t md_bkpc_rtcck_is_enable(void)
{
	return READ_BITS(BKPC->PCCR, BKPC_PCCR_RTCCKEN_MSK, BKPC_PCCR_RTCCKEN_POS);
}

/**
  * @brief  Enable LOSC
  * @retval None
  */
__STATIC_INLINE void md_bkpc_enable_losc(void)
{
	SET_BIT(BKPC->PCCR, BKPC_PCCR_LOSCEN_MSK);
}

/**
  * @brief  Disable LOSC
  * @retval None
  */
__STATIC_INLINE void md_bkpc_disable_losc(void)
{
	CLEAR_BIT(BKPC->PCCR, BKPC_PCCR_LOSCEN_MSK);
}

/**
  * @brief  Check if LOSC is enabled or disabled.
  * @retval Status:
  *           - 0: Disable
  *           - 1: Enable
  */
__STATIC_INLINE uint32_t md_bkpc_losc_is_enable(void)
{
	return READ_BITS(BKPC->PCCR, BKPC_PCCR_LOSCEN_MSK, BKPC_PCCR_LOSCEN_POS);
}

/**
  * @brief  Enable LOSM
  * @retval None
  */
__STATIC_INLINE void md_bkpc_enable_losm(void)
{
	SET_BIT(BKPC->PCCR, BKPC_PCCR_LOSMEN_MSK);
}

/**
  * @brief  Disable LOSM
  * @retval None
  */
__STATIC_INLINE void md_bkpc_disable_losm(void)
{
	CLEAR_BIT(BKPC->PCCR, BKPC_PCCR_LOSMEN_MSK);
}

/**
  * @brief  Check if LOSM is enabled or disabled.
  * @retval Status:
  *           - 0: Disable
  *           - 1: Enable
  */
__STATIC_INLINE uint32_t md_bkpc_losm_is_enable(void)
{
	return READ_BITS(BKPC->PCCR, BKPC_PCCR_LOSMEN_MSK, BKPC_PCCR_LOSMEN_POS);
}

/**
  * @brief  Enable ULRC
  * @retval None
  */
__STATIC_INLINE void md_bkpc_enable_ulrc(void)
{
	SET_BIT(BKPC->PCCR, BKPC_PCCR_ULRCEN_MSK);
}

/**
  * @brief  Disable ULRC
  * @retval None
  */
__STATIC_INLINE void md_disable_bkpc_ulrc(void)
{
	CLEAR_BIT(BKPC->PCCR, BKPC_PCCR_ULRCEN_MSK);
}

/**
  * @brief  Check if ULRC is enabled or disabled.
  * @retval Status:
  *           - 0: Disable
  *           - 1: Enable
  */
__STATIC_INLINE uint32_t md_bkpc_ulrc_is_enable(void)
{
	return READ_BITS(BKPC->PCCR, BKPC_PCCR_ULRCEN_MSK, BKPC_PCCR_ULRCEN_POS);
}

/**
  * @brief  Enable LOSCPM
  * @retval None
  */
__STATIC_INLINE void md_bkpc_enable_loscpm(void)
{
	SET_BIT(BKPC->PCCR, BKPC_PCCR_LOSCPM_MSK);
}

/**
  * @brief  Disable LOSCPM
  * @retval None
  */
__STATIC_INLINE void md_bkpc_disable_loscpm(void)
{
	CLEAR_BIT(BKPC->PCCR, BKPC_PCCR_LOSCPM_MSK);
}

/**
  * @brief  Check if LOSCPM is enabled or disabled.
  * @retval Status:
  *           - 0: Disable
  *           - 1: Enable
  */
__STATIC_INLINE uint32_t md_bkpc_loscpm_is_enable(void)
{
	return READ_BITS(BKPC->PCCR, BKPC_PCCR_LOSCPM_MSK, BKPC_PCCR_LOSCPM_POS);
}

/**
  * @brief  Enable LOSCPS
  * @retval None
  */
__STATIC_INLINE void md_bkpc_enable_loscps(void)
{
	CLEAR_BIT(BKPC->PCCR, BKPC_PCCR_LOSCPS_MSK);
}

/**
  * @brief  Disable LOSCPS
  * @retval None
  */
__STATIC_INLINE void md_bkpc_disable_loscps(void)
{
	SET_BIT(BKPC->PCCR, BKPC_PCCR_LOSCPS_MSK);
}

/**
  * @brief  Check if LOSCPS is enabled or disabled.
  * @retval Status:
  *           - 1: Disable
  *           - 0: Enable
  */
__STATIC_INLINE uint32_t md_bkpc_loscps_is_enable(void)
{
	return READ_BITS(BKPC->PCCR, BKPC_PCCR_LOSCPS_MSK, BKPC_PCCR_LOSCPS_POS);
}



/**
  * @brief  Enable wakeup port
  * @param  port: Wakeup port:
  *                 @arg @ref MD_PMU_STANDBY_PORT_SEL_PA2
  *                 @arg @ref MD_PMU_STANDBY_PORT_SEL_PA3
  *                 @arg @ref MD_PMU_STANDBY_PORT_SEL_PA4
  *                 @arg @ref MD_PMU_STANDBY_PORT_SEL_PA5
  *                 @arg @ref MD_PMU_STANDBY_PORT_SEL_PA6
  *                 @arg @ref MD_PMU_STANDBY_PORT_SEL_PA7
  *                 @arg @ref MD_PMU_STANDBY_PORT_SEL_PA8
  *                 @arg @ref MD_PMU_STANDBY_PORT_SEL_PA9
  *                 @arg @ref MD_PMU_STANDBY_PORT_SEL_RTC
  * @retval None
  */
__STATIC_INLINE void md_bkpc_enable_wakeup_port(md_bkpc_wakeup_port_t port)
{
	SET_BIT(BKPC->WKR, 1<<(port + BKPC_WKR_WKEN_POSS));
}

/**
  * @brief  Disable wakeup port
  * @param  port: Wakeup port:
  *                 @arg @ref MD_PMU_STANDBY_PORT_SEL_PA2
  *                 @arg @ref MD_PMU_STANDBY_PORT_SEL_PA3
  *                 @arg @ref MD_PMU_STANDBY_PORT_SEL_PA4
  *                 @arg @ref MD_PMU_STANDBY_PORT_SEL_PA5
  *                 @arg @ref MD_PMU_STANDBY_PORT_SEL_PA6
  *                 @arg @ref MD_PMU_STANDBY_PORT_SEL_PA7
  *                 @arg @ref MD_PMU_STANDBY_PORT_SEL_PA8
  *                 @arg @ref MD_PMU_STANDBY_PORT_SEL_PA9
  *                 @arg @ref MD_PMU_STANDBY_PORT_SEL_RTC
  * @retval None
  */
__STATIC_INLINE void md_bkpc_disable_wakeup_port(md_bkpc_wakeup_port_t port)
{
	CLEAR_BIT(BKPC->WKR, 1<<(port + BKPC_WKR_WKEN_POSS));
}

/**
  * @brief  Get wakeup port
  * @retval Wakeup port, @ref md_bkpc_wakeup_port_t
  */
__STATIC_INLINE uint32_t md_bkpc_get_wakeup_port(void)
{
	return READ_BITS(BKPC->WKR, BKPC_WKR_WKEN_MSK, BKPC_WKR_WKEN_POSS);
}

/**
  * @brief  Set wakeup level
  * @param  level: Wakeup level:
  *                  @arg @ref MD_PMU_STANDBY_LEVEL_HIGH
  *                  @arg @ref MD_PMU_STANDBY_LEVEL_LOW
  * @retval None
  */
__STATIC_INLINE void md_bkpc_set_wakeup_level(md_bkpc_wakeup_port_t port, md_bkpc_wakeup_level_t level)
{
	MODIFY_REG(BKPC->WKR, 1<<(port + BKPC_WKR_WKEG_POSS), level << (port + BKPC_WKR_WKEG_POSS));
}

/**
  * @brief  Get wakeup level
  * @retval Wakeup level, @ref md_bkpc_wakeup_level_t
  */
__STATIC_INLINE uint32_t md_bkpc_get_port_wakeup_level(md_bkpc_wakeup_port_t port)
{
	return READ_BITS(BKPC->WKR, 1<<(port + BKPC_WKR_WKEG_POSS), 1<<(port + BKPC_WKR_WKEG_POSS));
}

/**
  * @brief  Clear standby wake up flag.
  * @param  None
  * @retval None
  */
__STATIC_INLINE void md_bkpc_clear_flag_standby_wake_up(void)
{
    SET_BIT(BKPC->WKR, BKPC_WKR_WKSCLR_MSK);
}

/** @defgroup MD_BKPC_Public_Functions_Group4 WKSR
  * @{
  */
/**
  * @brief  Get wakeup port flag.
  * @retval Wakeup port.
  */
__STATIC_INLINE uint32_t md_bkpc_get_wakeup_port_flag(void)
{
	return READ_BITS(BKPC->WKSR, BKPC_WKSR_WKF_MSK, BKPC_WKSR_WKF_POSS);
}
/**
  * @}
  */

/**
  * @}
  */
/** @defgroup MD_BKPC_Public_Functions_Group4 PCCR
  * @{
  */
/**
  * @brief  Set RTC clock
  * @param  clock: RTC clock:
  *                  @arg @ref MD_BKPC_PREH_CLK_LOSM
  *                  @arg @ref MD_BKPC_PREH_CLK_LRC
  *                  @arg @ref MD_BKPC_PREH_CLK_HRC_1M
  *                  @arg @ref MD_BKPC_PREH_CLK_HOSC_1M
  * @retval None
  */
__STATIC_INLINE void md_bkpc_rtc_clock_set(md_bkpc_preh_clk_t clock)
{
	MODIFY_REG(BKPC->PCCR, BKPC_PCCR_RTCCK_MSK, clock << BKPC_PCCR_RTCCK_POS);
}

/**
  * @brief  Get RTC clock
  * @retval RTC clock, @ref md_bkpc_preh_clk_t
  */
__STATIC_INLINE uint32_t md_bkpc_rtc_clock_get(void)
{
	return READ_BITS(BKPC->PCCR, BKPC_PCCR_RTCCK_MSK, BKPC_PCCR_RTCCK_POS);
}
/**
  * @}
  */

/** @defgroup MD_BKPC_Public_Functions_Group5 PCR
  * @{
  */

/**
  * @brief  Set dc-dc stable time.
  * @param  tsudc:0-15.
  * @retval None.
  */
__STATIC_INLINE void md_bkpc_set_dcdc_stable_time(uint32_t tsudc)
{
    MODIFY_REG(BKPC->PCR, BKPC_PCR_TSUDC_MSK, tsudc << BKPC_PCR_TSUDC_POSS);
}

/**
  * @brief  Get dc-dc stable time.
  * @param None.
  * @retval  tsudc:0-15.
  */
__STATIC_INLINE uint32_t md_bkpc_get_dcdc_stable_time(void)
{
    return READ_BITS(BKPC->PCR, BKPC_PCR_TSUDC_MSK, BKPC_PCR_TSUDC_POSS);
}

/**
  * @brief  Set ldo stable time.
  * @param  tsuldo:0-15.
  * @retval None.
  */
__STATIC_INLINE void md_bkpc_set_ldo_stable_time(uint32_t tsudc)
{
    MODIFY_REG(BKPC->PCR, BKPC_PCR_TSULDO_MSK, tsudc << BKPC_PCR_TSULDO_POSS);
}

/**
  * @brief  Get ldo stable time.
  * @param  None.
  * @retval tsuldo:0-15.
  */
__STATIC_INLINE uint32_t md_bkpc_get_ldo_stable_time(void)
{
    return READ_BITS(BKPC->PCR, BKPC_PCR_TSULDO_MSK, BKPC_PCR_TSULDO_POSS);
}

/**
  * @brief  Enable DC-DC
  * @retval None
  */
__STATIC_INLINE void md_bkpc_enable_dcpdc(void)
{
	CLEAR_BIT(BKPC->PCR, BKPC_PCR_DCPDC_MSK);
}

/**
  * @brief  Disable DC-DC
  * @retval None
  */
__STATIC_INLINE void md_bkpc_disable_dcpdc(void)
{
	SET_BIT(BKPC->PCR, BKPC_PCR_DCPDC_MSK);
}

/**
  * @brief  Check if DC-DC is enabled or disabled.
  * @retval Status:
  *           - 1: Disable
  *           - 0: Enable
  */
__STATIC_INLINE uint32_t md_bkpc_dcpdc_is_enable(void)
{
	return READ_BITS(BKPC->PCR, BKPC_PCR_DCPDC_MSK, BKPC_PCR_DCPDC_POS);
}

/**
  * @brief  Enable DCPWM
  * @retval None
  */
__STATIC_INLINE void md_bkpc_enable_dcpwm(void)
{
	SET_BIT(BKPC->PCR, BKPC_PCR_DCPWM_MSK);
}

/**
  * @brief  Disable DCPWM
  * @retval None
  */
__STATIC_INLINE void md_bkpc_disable_dcpwm(void)
{
	CLEAR_BIT(BKPC->PCR, BKPC_PCR_DCPWM_MSK);
}

/**
  * @brief  Check if DCPWM is enabled or disabled.
  * @retval Status:
  *           - 0: Disable
  *           - 1: Enable
  */
__STATIC_INLINE uint32_t md_bkpc_dcpwm_is_enable(void)
{
	return READ_BITS(BKPC->PCR, BKPC_PCR_DCPDC_MSK, BKPC_PCR_DCPDC_POS);
}

/**
  * @brief  Enable DCBURST
  * @retval None
  */
__STATIC_INLINE void md_bkpc_enable_dcburst(void)
{
	CLEAR_BIT(BKPC->PCR, BKPC_PCR_DCBURST_MSK);
}

/**
  * @brief  Disable DCBURST
  * @retval None
  */
__STATIC_INLINE void md_bkpc_disable_dcburst(void)
{
	SET_BIT(BKPC->PCR, BKPC_PCR_DCBURST_MSK);
}

/**
  * @brief  Check if DCBURST is enabled or disabled.
  * @retval Status:
  *           - 1: Disable
  *           - 0: Enable
  */
__STATIC_INLINE uint32_t md_bkpc_dcburst_is_enable(void)
{
	return READ_BITS(BKPC->PCR, BKPC_PCR_DCBURST_MSK, BKPC_PCR_DCBURST_POS);
}

/**
  * @brief  Enable DCOPD
  * @retval None
  */
__STATIC_INLINE void md_bkpc_enable_dcopd(void)
{
	CLEAR_BIT(BKPC->PCR, BKPC_PCR_DCBURST_MSK);
}

/**
  * @brief  Disable DCOPD
  * @retval None
  */
__STATIC_INLINE void md_bkpc_disable_dcopd(void)
{
	SET_BIT(BKPC->PCR, BKPC_PCR_DCBURST_MSK);
}

/**
  * @brief  Check if DCOPD is enabled or disabled.
  * @retval Status:
  *           - 1: Disable
  *           - 0: Enable
  */
__STATIC_INLINE uint32_t md_bkpc_dcopd_is_enable(void)
{
	return READ_BITS(BKPC->PCR, BKPC_PCR_DCBURST_MSK, BKPC_PCR_DCBURST_POS);
}

/**
  * @brief  Set dc-dc bybass.
  * @param  dcby:
  *         -0: output 3.3V
  *         -1: output 1.4V
  * @retval None.
  */
__STATIC_INLINE void md_bkpc_set_dcdc_bybass(uint32_t dcby)
{
    MODIFY_REG(BKPC->PCR, BKPC_PCR_DCBY_MSK, dcby << BKPC_PCR_DCBY_POS);
}

/**
  * @brief  Get dc-dc bybass.
  * @param None.
  * @retval  dcby:
  *         -0: output 3.3V
  *         -1: output 1.4V
  */
__STATIC_INLINE uint32_t md_bkpc_get_dcdc_bybass(void)
{
    return READ_BITS(BKPC->PCR, BKPC_PCR_DCBY_MSK, BKPC_PCR_DCBY_POS);
}

/**
  * @brief  Set ble afe.
  * @param  afepd:
  *         -0: Power up
  *         -1: Power down
  * @retval None.
  */
__STATIC_INLINE void md_bkpc_set_ble_afe(uint32_t afepd)
{
    MODIFY_REG(BKPC->PCR, BKPC_PCR_AFEPD_MSK, afepd << BKPC_PCR_AFEPD_POS);
}

/**
  * @brief  Get ble afe.
  * @param None.
  * @retval  afepd:
  *         -0: Power up
  *         -1: Power down
  */
__STATIC_INLINE uint32_t md_bkpc_get_ble_afe(void)
{
    return READ_BITS(BKPC->PCR, BKPC_PCR_AFEPD_MSK, BKPC_PCR_AFEPD_POS);
}

/**
  * @brief  Enable DC-DC BandGap.
  * @retval None
  */
__STATIC_INLINE void md_bkpc_enable_dcbgpd(void)
{
	CLEAR_BIT(BKPC->PCR, BKPC_PCR_DCBGPD_MSK);
}

/**
  * @brief  Disable DC-DC BandGap.
  * @retval None
  */
__STATIC_INLINE void md_bkpc_disable_dcbgpd(void)
{
	SET_BIT(BKPC->PCR, BKPC_PCR_DCBGPD_MSK);
}

/**
  * @brief  Check if DC-DC BandGap is enabled or disabled.
  * @retval Status:
  *           - 1: Disable
  *           - 0: Enable
  */
__STATIC_INLINE uint32_t md_bkpc_dcbgpd_is_enable(void)
{
	return READ_BITS(BKPC->PCR, BKPC_PCR_DCBGPD_MSK, BKPC_PCR_DCBGPD_POS);
}

/**
  * @brief  Set LDO power consumption.
  * @param  ldosel:
  *         -0: Low power
  *         -1: High power
  * @retval None.
  */
__STATIC_INLINE void md_bkpc_set_ldo_power(uint32_t ldosel)
{
    MODIFY_REG(BKPC->PCR, BKPC_PCR_LDOSEL_MSK, ldosel << BKPC_PCR_LDOSEL_POS);
}

/**
  * @brief  Get LDO power consumption.
  * @param None.
  * @retval  ldosel:
  *         -0: Low power
  *         -1: High power
  */
__STATIC_INLINE uint32_t md_bkpc_get_ldo_power(void)
{
    return READ_BITS(BKPC->PCR, BKPC_PCR_LDOSEL_MSK, BKPC_PCR_LDOSEL_POS);
}

/**
  * @brief  Enable LDO external refernce volatile.
  * @retval None
  */
__STATIC_INLINE void md_bkpc_enable_ldoerpd(void)
{
	CLEAR_BIT(BKPC->PCR, BKPC_PCR_LDOERPD_MSK);
}

/**
  * @brief  Disable LDO external refernce volatile.
  * @retval None
  */
__STATIC_INLINE void md_bkpc_disable_ldoerpd(void)
{
	SET_BIT(BKPC->PCR, BKPC_PCR_LDOERPD_MSK);
}

/**
  * @brief  Check if LDO external refernce volatile is enabled or disabled.
  * @retval Status:
  *           - 1: Disable
  *           - 0: Enable
  */
__STATIC_INLINE uint32_t md_bkpc_ldoerpd_is_enable(void)
{
	return READ_BITS(BKPC->PCR, BKPC_PCR_LDOERPD_MSK, BKPC_PCR_LDOERPD_POS);
}

/**
  * @brief  Enable high power LDO.
  * @retval None
  */
__STATIC_INLINE void md_bkpc_enable_hpldo(void)
{
	SET_BIT(BKPC->PCR, BKPC_PCR_HPLDOEN_MSK);
}

/**
  * @brief  Disable high power LDO.
  * @retval None
  */
__STATIC_INLINE void md_bkpc_disable_hpldo(void)
{
	CLEAR_BIT(BKPC->PCR, BKPC_PCR_HPLDOEN_MSK);
}

/**
  * @brief  Check if high power LDO is enabled or disabled.
  * @retval Status:
  *           - 0: Disable
  *           - 1: Enable
  */
__STATIC_INLINE uint32_t md_bkpc_hpldo_is_enable(void)
{
	return READ_BITS(BKPC->PCR, BKPC_PCR_HPLDOEN_MSK, BKPC_PCR_HPLDOEN_POS);
}

/**
  * @brief  Enable power.
  * @retval None
  */
__STATIC_INLINE void md_bkpc_enable_pwcts(void)
{
	SET_BIT(BKPC->PCR, BKPC_PCR_PWCTSEN_MSK);
}

/**
  * @brief  Disable power.
  * @retval None
  */
__STATIC_INLINE void md_bkpc_disable_pwcts(void)
{
	CLEAR_BIT(BKPC->PCR, BKPC_PCR_PWCTSEN_MSK);
}

/**
  * @brief  Check if power is enabled or disabled.
  * @retval Status:
  *           - 0: Disable
  *           - 1: Enable
  */
__STATIC_INLINE uint32_t md_bkpc_pwcts_is_enable(void)
{
	return READ_BITS(BKPC->PCR, BKPC_PCR_PWCTSEN_MSK, BKPC_PCR_PWCTSEN_POS);
}

/**
  * @}
  */


/** @defgroup MD_BKPC_Public_Functions_Group1 Configure
  * @{
  */
extern void md_bkpc_standby_wakeup_config(md_bkpc_wakeup_port_t port, md_bkpc_wakeup_level_t level);
extern void md_bkpc_rtc_clock_config(md_bkpc_preh_clk_t clock);
extern void md_bkpc_tsense_clock_config(md_bkpc_preh_clk_t clock);
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
#endif

#endif

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
