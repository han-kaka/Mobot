/**********************************************************************************
 *
 * @file    md_cmu.c
 * @brief   CMU module driver.
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
#include "md_cmu.h"
#include "md_syscfg.h"

/** @addtogroup Micro_Driver
  * @{
  */

/** @defgroup MD_CMU CMU
  * @{
  */
/**
  * @defgroup MD_CMU_Private_Variables CMU Private Variables
  * @{
  */
uint32_t md_system_clock  = 24000000U;
/**
  * @}
  */
/** @defgroup MD_CMU_Private_Functions CMU Private Functions
  * @{
  */

/**
  * @brief  Update the current system clock. This function
  *         will be invoked, when system clock has changed.
  * @param  clock: The new clock.
  * @retval None
  */

static void md_cmu_clock_update(uint32_t clock)
{
	md_system_clock = clock;
}
/**
  * @}
  */
/** @addtogroup MD_CMU_Public_Functions
  * @{
  */
/** @addtogroup MD_CMU_Public_Functions_Group1
  * @{
  */
/**
  * @brief  Configure system clock using default.
  *         Select MD_CMU_CLOCK_HRC(24MHz) as system clock and
  *         enable MD_CMU_CLOCK_LRC(32768Hz).
  * @retval The status of HAL.
  */
md_status_t md_cmu_clock_config_default(void)
{
	uint32_t cnt = 4000, tmp;

	SYSCFG_UNLOCK();

	/* Select HRC */
	MODIFY_REG(CMU->CSR, CMU_CSR_SYS_CMD_MSK, MD_CMU_CLOCK_HRC << CMU_CSR_SYS_CMD_POSS);

	while (READ_BIT(CMU->CSR, CMU_CSR_SYS_RDYN_MSK) && (--cnt));

	if (READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) != MD_CMU_CLOCK_HRC) {
		SYSCFG_LOCK();
		return MD_ERROR;
	}

	WRITE_REG(CMU->CFGR, 0x0);
	CLEAR_BIT(CMU->CFGR, CMU_CFGR_HRCFST_MSK);	/* Select 24Mhz */

	tmp = READ_REG(CMU->CLKENR);
	/* Enable HRC/LRC/LOSC */
	SET_BIT(tmp, CMU_CLKENR_HRCEN_MSK | CMU_CLKENR_LRCEN_MSK | CMU_CLKENR_LOSCEN_MSK);
	WRITE_REG(CMU->CLKENR, tmp);
	/* Reset LRC */
	for (cnt = 0; cnt < 10000; ++cnt);
	CLEAR_BIT(CMU->CLKENR, CMU_CLKENR_LRCEN_MSK);
	SET_BIT(CMU->CLKENR, CMU_CLKENR_LRCEN_MSK);

//	/* Set flash wait 0 sysclk */
//	MODIFY_REG(MSC->MEMWAIT, MSC_MEMWAIT_FLASH_W_MSK, 0x0 << MSC_MEMWAIT_FLASH_W_POSS);

	SYSCFG_LOCK();
	return MD_OK;
}

/**
  * @brief  Configure system clock using specified parameters
  * @param  clk: The parameter can be one of the following:
  *           @arg @ref MD_CMU_CLOCK_HRC  2MHz or 24MHz
  *           @arg @ref MD_CMU_CLOCK_LRC  32768Hz
  *           @arg @ref MD_CMU_CLOCK_LOSC 32768Hz
  *           @arg @ref MD_CMU_CLOCK_PLL1 36MHz, 48MHz 72MHz or 96MHz
  *           @arg @ref MD_CMU_CLOCK_HOSC 1MHz -- 24MHz
  * @param  clock: The clock which will be set. the value depends
  *         on the parameter of clk.
  * @retval The status of HAL.
  */
md_status_t md_cmu_clock_config(md_cmu_clock_t clk, uint32_t clock)
{
	uint32_t cnt = 4000;
    
    WRITE_REG(BKPC->PROT, 0x9669AA55U);
    SET_BIT(BKPC->PCR, BKPC_PCR_LDOERPD_MSK);
    SET_BIT(BKPC->PCR, BKPC_PCR_DCBGPD_MSK);
    WRITE_REG(BKPC->PROT, 0U);
    
	SYSCFG_UNLOCK();
	MODIFY_REG(CMU->CFGR, 0xFFFFFFU, 0);

	switch (clk) {
	case MD_CMU_CLOCK_HRC:
		assert_param(clock == 24000000 || clock == 2000000);

		MODIFY_REG(CMU->CSR, CMU_CSR_SYS_CMD_MSK, MD_CMU_CLOCK_HRC << CMU_CSR_SYS_CMD_POSS);
		while (READ_BIT(CMU->CSR, CMU_CSR_SYS_RDYN_MSK) && (--cnt));

		if (READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) != MD_CMU_CLOCK_HRC) {
			SYSCFG_LOCK();
			return MD_ERROR;
		}

		if (clock == 24000000)
			CLEAR_BIT(CMU->CFGR, CMU_CFGR_HRCFSW_MSK);
		else
			SET_BIT(CMU->CFGR, CMU_CFGR_HRCFSW_MSK);

		SET_BIT(CMU->CLKENR, CMU_CLKENR_HRCEN_MSK);

		for (cnt = 4000; cnt; --cnt);
		cnt = 4000;
		while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_HRCACT_MSK))) && (--cnt));
		cnt = 4000;
		while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_HRCRDY_MSK))) && (--cnt));

		md_cmu_clock_update(clock);
		break;


	case MD_CMU_CLOCK_PLL1:
        assert_param(clock == 48000000);
//		/* Set flash wait 2 sysclk */
//		MODIFY_REG(MSC->MEMWAIT, MSC_MEMWAIT_FLASH_W_MSK, 0x2 << MSC_MEMWAIT_FLASH_W_POSS);
		for (cnt = 0; cnt < 5000; ++cnt);

		MODIFY_REG(CMU->CSR, CMU_CSR_CFT_CMD_MSK, 0xAA << CMU_CSR_CFT_CMD_POSS);
		MODIFY_REG(CMU->CSR, CMU_CSR_SYS_CMD_MSK, MD_CMU_CLOCK_PLL1 << CMU_CSR_SYS_CMD_POSS);
		while (READ_BIT(CMU->CSR, CMU_CSR_SYS_RDYN_MSK) && (--cnt));

		if (READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) != MD_CMU_CLOCK_PLL1) {
			SYSCFG_LOCK();
			return MD_ERROR;
		}

		SET_BIT(CMU->CLKENR, CMU_CLKENR_PLL1EN_MSK);

		for (cnt = 0; cnt < 5000; ++cnt);
		while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_PLL1ACT_MSK))) && (--cnt));
		cnt = 4000;
		while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_PLL1RDY_MSK))) && (--cnt));

		if (clock == 48000000) {
			MODIFY_REG(CMU->CFGR, CMU_CFGR_PCLK2DIV_MSK, 0x1 << CMU_CFGR_PCLK2DIV_POSS);
//			/* Set flash wait 1 sysclk */
//			MODIFY_REG(MSC->MEMWAIT, MSC_MEMWAIT_FLASH_W_MSK, 0x1 << MSC_MEMWAIT_FLASH_W_POSS);
		}

		md_cmu_clock_update(clock);
		break;

	case MD_CMU_CLOCK_HOSC:
		assert_param(clock <= 48000000);
    
//        MODIFY_REG(MSC->MEMWAIT, MSC_MEMWAIT_FLASH_W_MSK, 0x2 << MSC_MEMWAIT_FLASH_W_POSS);

		MODIFY_REG(CMU->CSR, CMU_CSR_SYS_CMD_MSK, MD_CMU_CLOCK_HOSC << CMU_CSR_SYS_CMD_POSS);
		while (READ_BIT(CMU->CSR, CMU_CSR_SYS_RDYN_MSK) && (--cnt));

		if (READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) != MD_CMU_CLOCK_HOSC) {
			SYSCFG_LOCK();
			return MD_ERROR;
		}

		SET_BIT(CMU->CLKENR, CMU_CLKENR_HOSCEN_MSK);

		for (cnt = 8000; cnt; --cnt);
		cnt = 4000;
		while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_HOSCACT_MSK))) && (--cnt));
		cnt = 4000;
		while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_HOSCRDY_MSK))) && (--cnt));

		md_cmu_clock_update(clock);
		break;

	default:
		break;
	}

	SYSCFG_LOCK();
	return MD_OK;
}

/**
  * @brief  Configure PLL1 using specified parameters.
  * @param  hosc_clock: The hosc clock / 1000000.
  * @retval None
  */
void md_cmu_pll1_config(uint32_t hosc_clock)
{
	uint32_t cnt = 4000;

	SYSCFG_UNLOCK();
    
    if(hosc_clock == 0 || hosc_clock > 63)
        return;
    
    SET_BIT(CMU->CLKENR, CMU_CLKENR_HOSCEN_MSK);
    while((!READ_BIT(CMU->CLKSR, CMU_CLKSR_HOSCRDY_MSK)) && (--cnt));
    MODIFY_REG(CMU->PLLCFG, CMU_PLLCFG_PLL1RDIV_MSK, hosc_clock << CMU_PLLCFG_PLL1RDIV_POSS);
    SET_BIT(CMU->CLKENR, CMU_CLKENR_PLL1EN_MSK);
    for (cnt = 0; cnt < 4000; ++cnt);
	while ((READ_BIT(CMU->PLLCFG, CMU_PLLCFG_PLL1LCKN_MSK)) && (--cnt));
	cnt = 4000;
	while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_PLL1RDY_MSK))) && (--cnt));
    
    SET_BIT(CMU->PULMCR, CMU_PULMCR_EN_MSK);
	MODIFY_REG(CMU->PULMCR, CMU_PULMCR_MODE_MSK, 0x3 << CMU_PULMCR_MODE_POSS);

	SYSCFG_LOCK();
	return;
}

/**
  * @brief  Configure the bus division.
  * @param  bus: The type of bus:
  *          @arg CMU_HCLK_1
  *          @arg CMU_SYS
  *          @arg CMU_PCLK_1
  *          @arg CMU_PCLK_2
  * @param  div: The value of divider.
  * @retval None
  */
void md_cmu_div_config(md_cmu_bus_t bus, md_cmu_div_t div)
{
	SYSCFG_UNLOCK();

	switch (bus) {
	case MD_CMU_HCLK_1:
		MODIFY_REG(CMU->CFGR, CMU_CFGR_HCLK1DIV_MSK, div << CMU_CFGR_HCLK1DIV_POSS);
		break;

	case MD_CMU_SYS:

		break;

	case MD_CMU_PCLK_1:
		MODIFY_REG(CMU->CFGR, CMU_CFGR_PCLK1DIV_MSK, div << CMU_CFGR_PCLK1DIV_POSS);
		break;

	case MD_CMU_PCLK_2:
		MODIFY_REG(CMU->CFGR, CMU_CFGR_PCLK2DIV_MSK, div << CMU_CFGR_PCLK2DIV_POSS);
		break;

	default:
		break;
	}

	SYSCFG_LOCK();
	return;
}

/**
  * @brief  Get AHB1 clock.
  * @retval The value of AHB1 clock.
  */
uint32_t md_cmu_get_hclk1_clock(void)
{
	uint32_t sys_div = 0;
	uint32_t ahb_div = READ_BITS(CMU->CFGR, CMU_CFGR_HCLK1DIV_MSK, CMU_CFGR_HCLK1DIV_POSS);

	return (md_system_clock >> sys_div) >> ahb_div;
}

/**
  * @brief  Get AHB2 clock.
  * @retval The value of AHB2 clock.
  */
uint32_t md_cmu_get_hclk2_clock(void)
{
	uint32_t sys_div = 0;
	uint32_t ahb_div = READ_BITS(CMU->CFGR, CMU_CFGR_HCLK2DIV_MSK, CMU_CFGR_HCLK2DIV_POSS);

	return (md_system_clock >> sys_div) >> ahb_div;
}

/**
  * @brief  Get SYS clock
  * @retval The value of SYS clock
  */
uint32_t md_cmu_get_sys_clock(void)
{
	uint32_t sys_div = 0;

	return md_system_clock >> sys_div;
}

/**
  * @brief  Get APB1 clock.
  * @retval The value of APB1 clock.
  */
uint32_t md_cmu_get_pclk1_clock(void)
{
	uint32_t sys_div  = 0;
	uint32_t apb1_div = READ_BITS(CMU->CFGR, CMU_CFGR_PCLK1DIV_MSK, CMU_CFGR_PCLK1DIV_POSS);

	return (md_system_clock >> sys_div) >> apb1_div;
}

/**
  * @brief  Get APB2 clock.
  * @retval The value of APB2 clock.
  */
uint32_t md_cmu_get_pclk2_clock(void)
{
	uint32_t sys_div  = 0;
	uint32_t apb2_div = READ_BITS(CMU->CFGR, CMU_CFGR_PCLK2DIV_MSK, CMU_CFGR_PCLK2DIV_POSS);

	return (md_system_clock >> sys_div) >> apb2_div;
}

/**
  * @brief  Gets current system clock.
  * @retval The value of system clock.
  */
uint32_t md_cmu_get_clock(void)
{
	return md_system_clock;
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
