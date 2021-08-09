/**********************************************************************************
 *
 * @file    md_msc.h
 * @brief   Header file of MSC module driver.
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


#ifndef __MD_MSC_H__
#define __MD_MSC_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "md_utils.h"

/* Includes ------------------------------------------------------------------ */

/* Exported Variables -------------------------------------------------------- */

/* Exported Constants -------------------------------------------------------- */

/* Public types ------------------------------------------------------------ */

/* Exported Types ------------------------------------------------------------ */

/**
  *@brief config the multi-words write function support automatic erasing
  */
typedef enum
{
    AUTO_ERASE_FALSE = 0x0U,
    AUTO_ERASE_TRUE  = 0x1U,
} type_auto_erase_t;

/**
  *@brief config the IAP work frequence
  */
typedef enum
{
    IAP_FREQUENCE_48M = 0x0U,
    IAP_FREQUENCE_24M = 0x1U,
    IAP_FREQUENCE_12M = 0x2U,
    IAP_FREQUENCE_6M  = 0x3U,
    IAP_FREQUENCE_3M  = 0x4U,
    IAP_FREQUENCE_16M = 0x5U,
    IAP_FREQUENCE_8M  = 0x6U,
    IAP_FREQUENCE_4M  = 0x7U,
} type_iap_freq_t;

/**
  *@brief flash operation commands
  */
typedef enum
{
    FULL_ERASE                      = 0x51AEU,

    CODE_INFO_PAGE_ERASE            = 0x5EA1U,
    CODE_INFO_DWORD_PROGRAM         = 0x5DA2U,
    CODE_INFO_ENTER_FAST_PROGRAM    = 0x5BA4U,
    CODE_INFO_PROCESS_FAST_PROGRAM  = 0x59A6U,
    CODE_INFO_QUIT_FAST_PROGRAM     = 0x58A7U,

    DATA_FLASH_PAGE_ERASE           = 0xAEA1U,
    DATA_FLASH_DWORD_PROGRAM        = 0xADA2U,
    DATA_FLASH_ENTER_FAST_PROGRAM   = 0xABA4U,
    DATA_FLASH_PROCESS_FAST_PROGRAM = 0xA9A6U,
    DATA_FLASH_QUIT_FAST_PROGRAM    = 0xA8A7U,
} type_flash_cmd_t;

/**
  *@brief funtion pointer type for page erase
  */
typedef uint32_t (*iap_pageerase_t)(uint32_t adr, uint32_t clk);

/**
  *@brief funtion pointer type for simple word write
  */
typedef uint32_t (*iap_wordprogram_t)(uint32_t adr, uint32_t data0, uint32_t data1, uint32_t clk);

/**
  *@brief funtion pointer type for double words write
  */
typedef uint32_t (*iap_wordsprogram_t)(uint32_t adr, uint8_t *buf, uint32_t byte_size, uint32_t epif, uint32_t clk);

/* Exported Macros ----------------------------------------------------------- */

/* Public macros ------------------------------------------------------ */

#define IAP_PAGEERASE ((iap_pageerase_t)(*((uint32_t *)0x10000000)))

#define IAP_DWORDPROGRAM ((iap_wordprogram_t)(*((uint32_t *)0x10000004)))

#define IAP_FASTPROGRAM ((iap_wordsprogram_t)(*((uint32_t *)0x10000008)))

#define FLASH_UNLOCK()   WRITE_REG(MSC->IAPUL, 0x000000A5U)
#define FLASH_LOCK()     WRITE_REG(MSC->IAPUL, 0x00000001U)
#define GET_FLASH_LOCK() READ_BIT(MSC->IAPUL, MSC_IAPUL_UL_MSK)

/* Exported Functions -------------------------------------------------------- */

/**
  * @brief  Enable IAP
  * @retval NONE
  */
__STATIC_INLINE void md_msc_enable_iap(void)
{
    SET_BIT(MSC->IAPCR, MSC_IAPCR_IAPEN_MSK);
}

/**
  * @brief  Disable IAP
  * @retval NONE
  */
__STATIC_INLINE void md_msc_disable_iap(void)
{
    CLEAR_BIT(MSC->IAPCR, MSC_IAPCR_IAPEN_MSK);
}

/**
  * @brief  Get IAPEN status
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_msc_is_enabled_iap(void)
{
    return READ_BITS(MSC->IAPCR, MSC_IAPCR_IAPEN_MSK, MSC_IAPCR_IAPEN_POS);
}

/**
  * @brief  Reset IAP
  * @retval NONE
  */
__STATIC_INLINE void md_msc_reset_iap(void)
{
    SET_BIT(MSC->IAPCR, MSC_IAPCR_IAPRST_MSK);
}

/**
  * @brief  Enable flash request
  * @retval NONE
  */
__STATIC_INLINE void md_msc_enable_flash_request(void)
{
    SET_BIT(MSC->IAPCR, MSC_IAPCR_FLASH_REQ_MSK);
}

/**
  * @brief  Disable flash request
  * @retval NONE
  */
__STATIC_INLINE void md_msc_disable_flash_request(void)
{
    CLEAR_BIT(MSC->IAPCR, MSC_IAPCR_FLASH_REQ_MSK);
}

/**
  * @brief  Get flash request status
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_msc_is_enabled_flash_request(void)
{
    return READ_BITS(MSC->IAPCR, MSC_IAPCR_FLASH_REQ_MSK, MSC_IAPCR_FLASH_REQ_POS);
}

/**
  * @brief  Get flash acknowledge status
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_msc_is_enabled_flash_ack(void)
{
    return READ_BITS(MSC->IAPCR, MSC_IAPCR_FLASH_ACK_MSK, MSC_IAPCR_FLASH_ACK_POS);
}

/**
  * @brief  Set IAP work frequence
  * @param  frq: Values of following:
  *         - 0x0: 48MHz
  *         - 0x1: 24MHz
  *         - 0x2: 12MHz
  *         - 0x3: 6MHz
  *         - 0x4: 3MHz
  *         - 0x5: 16MHz
  *         - 0x6: 8MHz
  *         - 0x7: 4MHz
  * @retval None
  */
__STATIC_INLINE void md_msc_set_iap_frequence(uint32_t frq)
{
    MODIFY_REG(MSC->IAPCR, MSC_IAPCR_IAPCKS_MSK, frq << MSC_IAPCR_IAPCKS_POSS);
}

/**
  * @brief  Get IAP work frequence
  * @retval The value of following:
  *         - 0x0: 48MHz
  *         - 0x1: 24MHz
  *         - 0x2: 12MHz
  *         - 0x3: 6MHz
  *         - 0x4: 3MHz
  *         - 0x5: 16MHz
  *         - 0x6: 8MHz
  *         - 0x7: 4MHz
  */
__STATIC_INLINE uint32_t md_msc_get_iap_frequence(void)
{
    return READ_BITS(MSC->IAPCR, MSC_IAPCR_IAPCKS_MSK, MSC_IAPCR_IAPCKS_POSS);
}

/**
  * @brief  Set flash byte address in pages
  * @param  addr
  * @retval None
  */
__STATIC_INLINE void md_msc_set_flash_byte_address(uint32_t addr)
{
    MODIFY_REG(MSC->IAPA, MSC_IAPA_IAPCA_MSK, addr << MSC_IAPA_IAPCA_POSS);
}

/**
  * @brief  Get flash byte address in pages
  * @retval address
  */
__STATIC_INLINE uint32_t md_msc_get_flash_byte_address(void)
{
    return READ_BITS(MSC->IAPA, MSC_IAPA_IAPCA_MSK, MSC_IAPA_IAPCA_POSS);
}

/**
  * @brief  Set flash page address
  * @param  addr: 0x00~0x7F: Page0 ~ Page127
  * @retval None
  */
__STATIC_INLINE void md_msc_set_flash_page_address(uint32_t addr)
{
    MODIFY_REG(MSC->IAPA, MSC_IAPA_IAPPA_MSK, addr << MSC_IAPA_IAPPA_POSS);
}

/**
  * @brief  Get flash page address
  * @retval address
  */
__STATIC_INLINE uint32_t md_msc_get_flash_page_address(void)
{
    return READ_BITS(MSC->IAPA, MSC_IAPA_IAPPA_MSK, MSC_IAPA_IAPPA_POSS);
}

/**
  * @brief  Enable information block
  * @retval NONE
  */
__STATIC_INLINE void md_msc_enable_info(void)
{
    SET_BIT(MSC->IAPA, MSC_IAPA_IFREN_MSK);
}

/**
  * @brief  Disable information block
  * @retval NONE
  */
__STATIC_INLINE void md_msc_disable_info(void)
{
    CLEAR_BIT(MSC->IAPA, MSC_IAPA_IFREN_MSK);
}

/**
  * @brief  Get information block status
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_msc_is_enabled_info(void)
{
    return READ_BITS(MSC->IAPA, MSC_IAPA_IFREN_MSK, MSC_IAPA_IFREN_POS);
}

/**
  * @brief  Set flash operation
  * @param  cmd: 
  *         0x51AE: full erase
  *         0x5EA1: code and info1/2/3 page erase
  *         0x5DA2: code and info1/2/3 double words program
  *         0x5BA4: enter into code and info1/2/3 fast program
  *         0x59A6: process code and info1/2/3 fast program
  *         0x58A7: quit code and info1/2/3 fast program
  *         0xAEA1: data flash page erase
  *         0xADA2: data flash double words program
  *         0xABA4: enter into data flash fast program
  *         0xA9A6: process data flash fast program
  *         0xA8A7: quit data flash fast program
  *         others: Reserved
  * @retval None
  */
__STATIC_INLINE void md_msc_set_flash_operation(uint32_t cmd)
{
    MODIFY_REG(MSC->IAPT, MSC_IAPT_TRIG_MSK, cmd << MSC_IAPT_TRIG_POSS);
}

/**
  * @brief  Get flash operation status
  * @retval 
  *         0x0000: idle
  *         0x0001: page erase
  *         0x0002: double words program
  *         0x0003: enter into fast program
  *         0x0005: process fast program
  *         0x0006: quit fast program
  *         0x0007: full erase
  *         0x0008: datafalsh page erase
  *         0x0009: datafalsh double words program
  *         0x000A: enter into datafalsh fast program
  *         0x000C: process datafalsh fast program
  *         0x000D: quit datafalsh fast program
  *         others: Reserved
  */
__STATIC_INLINE uint32_t md_msc_get_flash_operation_status(void)
{
    return READ_BITS(MSC->IAPT, MSC_IAPT_TRIG_MSK, MSC_IAPT_TRIG_POSS);
}

/**
  * @brief  Get IAP work status
  * @retval Status
  *         - 0: Idle
  *         - 1: Busy
  */
__STATIC_INLINE uint32_t md_msc_get_iap_status(void)
{
    return READ_BITS(MSC->IAPSR, MSC_IAPSR_BUSY_MSK, MSC_IAPSR_BUSY_POS);
}

/**
  * @brief  Check if flash page erase is finished
  * @retval Status
  *         - 0: Unfinished
  *         - 1: Finished
  */
__STATIC_INLINE uint32_t md_msc_flash_perase_is_end(void)
{
    return READ_BITS(MSC->IAPSR, MSC_IAPSR_PERASE_END_MSK, MSC_IAPSR_PERASE_END_POS);
}

/**
  * @brief  Check if flash double words program is finished
  * @retval Status
  *         - 0: Unfinished
  *         - 1: Finished
  */
__STATIC_INLINE uint32_t md_msc_flash_dwprog_is_end(void)
{
    return READ_BITS(MSC->IAPSR, MSC_IAPSR_WPROG_END_MSK, MSC_IAPSR_WPROG_END_POS);
}

/**
  * @brief  Check if flash fast program is started
  * @retval Status
  *         - 0: Not started
  *         - 1: Started
  */
__STATIC_INLINE uint32_t md_msc_flash_fast_prog_is_started(void)
{
    return READ_BITS(MSC->IAPSR, MSC_IAPSR_PPROGS_END_MSK, MSC_IAPSR_PPROGS_END_POS);
}

/**
  * @brief  Check if flash fast program is proceeding
  * @retval Status
  *         - 0: Unfinished
  *         - 1: Finished
  */
__STATIC_INLINE uint32_t md_msc_flash_fast_prog_is_proc(void)
{
    return READ_BITS(MSC->IAPSR, MSC_IAPSR_PPROGD_END_MSK, MSC_IAPSR_PPROGD_END_POS);
}

/**
  * @brief  Check if flash fast program is quited
  * @retval Status
  *         - 0: Not quited
  *         - 1: Quited
  */
__STATIC_INLINE uint32_t md_msc_flash_fast_prog_is_quit(void)
{
    return READ_BITS(MSC->IAPSR, MSC_IAPSR_PPROGE_END_MSK, MSC_IAPSR_PPROGE_END_POS);
}

/**
  * @brief  Check if flash full erase is finished
  * @retval Status
  *         - 0: Unfinished
  *         - 1: Finished
  */
__STATIC_INLINE uint32_t md_msc_flash_merase_is_finished(void)
{
    return READ_BITS(MSC->IAPSR, MSC_IAPSR_MERASE_END_MSK, MSC_IAPSR_MERASE_END_POS);
}

/**
  * @brief  Check if private code protected block is operated
  * @retval Status
  *         - 0: Not operated
  *         - 1: Operated
  */
__STATIC_INLINE uint32_t md_msc_if_private_code_is_operated(void)
{
    return READ_BITS(MSC->IAPSR, MSC_IAPSR_PCRDP_F_MSK, MSC_IAPSR_PCRDP_F_POS);
}

/**
  * @brief  Check if write protect block is operated
  * @retval Status
  *         - 0: Not operated
  *         - 1: Operated
  */
__STATIC_INLINE uint32_t md_msc_if_write_protect_is_operated(void)
{
    return READ_BITS(MSC->IAPSR, MSC_IAPSR_WRP_F_MSK, MSC_IAPSR_WRP_F_POS);
}

/**
  * @brief  Check if whole read protect is valid
  * @retval Status
  *         - 0: Invalid
  *         - 1: Valid
  */
__STATIC_INLINE uint32_t md_msc_if_whole_read_protect_is_valid(void)
{
    return READ_BITS(MSC->IAPSR, MSC_IAPSR_GBRDP_F_MSK, MSC_IAPSR_GBRDP_F_POS);
}

/**
  * @brief  Get operated block is code or data
  * @retval Status
  *         - 0: Code flash
  *         - 1: Data flash
  */
__STATIC_INLINE uint32_t md_msc_operated_block_code_or_data(void)
{
    return READ_BITS(MSC->IAPSR, MSC_IAPSR_DFLS_F_MSK, MSC_IAPSR_DFLS_F_POS);
}

/**
  * @brief  Flash program data low address register
  * @retval NONE
  */
__STATIC_INLINE void md_msc_write_flash_prog_data_low(uint32_t datal)
{
    WRITE_REG(MSC->IAPDL, datal);
}

/**
  * @brief  Get flash program low address data 
  * @retval data low
  */
__STATIC_INLINE uint32_t md_msc_read_flash_prog_data_low(void)
{
    return READ_BIT(MSC->IAPDL, MSC_IAPDL_DATAL_MSK);
}

/**
  * @brief  Flash program data high address register
  * @retval NONE
  */
__STATIC_INLINE void md_msc_write_flash_prog_data_high(uint32_t datah)
{
    WRITE_REG(MSC->IAPDH, datah);
}

/**
  * @brief  Get flash program high address data 
  * @retval data high
  */
__STATIC_INLINE uint32_t md_msc_read_flash_prog_data_high(void)
{
    return READ_BIT(MSC->IAPDH, MSC_IAPDH_DATAH_MSK);
}

/**
  * @brief  Set flash read waiting period
  * @param  period: 0x0~0xF: 0~15 SYSCLK period
  * @retval None
  */
__STATIC_INLINE void md_msc_set_flash_wait_period(uint32_t period)
{
	uint32_t tmp;

	tmp = MSC->MEMWAIT;
	MODIFY_REG(tmp, MSC_MEMWAIT_FLASH_W_MSK, (0x30U | period) << MSC_MEMWAIT_FLASH_W_POSS);
	MSC->MEMWAIT = tmp;
}

/**
  * @brief  Get flash read waiting period
  * @retval 0x0~0xF: 0~15 SYSCLK period
  */
__STATIC_INLINE uint32_t md_msc_get_flash_wait_period(void)
{
    return READ_BITS(MSC->MEMWAIT, MSC_MEMWAIT_FLASH_W_MSK, MSC_MEMWAIT_FLASH_W_POSS);
}

/**
  * @brief  Set sram read waiting period
  * @param  period: 0x0~0x3: 0~3 SYSCLK period
  * @retval None
  */
__STATIC_INLINE void md_msc_set_sram_wait_period(uint32_t period)
{
    MODIFY_REG(MSC->MEMWAIT, MSC_MEMWAIT_SRAM_W_MSK, (0x30U | period) << MSC_MEMWAIT_SRAM_W_POSS);
}

/**
  * @brief  Get sram read waiting period
  * @retval 0x0~0x3: 0~3 SYSCLK period
  */
__STATIC_INLINE uint32_t md_msc_get_sram_wait_period(void)
{
    return READ_BITS(MSC->MEMWAIT, MSC_MEMWAIT_SRAM_W_MSK, MSC_MEMWAIT_SRAM_W_POSS);
}

/**
  * @brief  Get flash redundance 0 data
  * @retval bit[0]: 0x1: Flash redundance 0 is not used for repairing.
  *                 0x0: Flash redundance 0 is used for repairing.
  *         bit[7:1]: Page address of flash which is defective
  */
__STATIC_INLINE uint32_t md_msc_get_flash_repair0(void)
{
    return READ_BITS(MSC->FREPSR, MSC_FREPSR_REP0_MSK, MSC_FREPSR_REP0_POSS);
}

/**
  * @brief  Check flash redundance 0 repair information is true or false
  * @retval 0x0: True, 0x1: False
  */
__STATIC_INLINE uint32_t md_msc_flash_repair0_is_true(void)
{
    return READ_BITS(MSC->FREPSR, MSC_FREPSR_REP0LS_MSK, MSC_FREPSR_REP0LS_POS);
}

/**
  * @brief  Get flash redundance 1 data
  * @retval bit[0]: 0x1: Flash redundance 1 is not used for repairing.
  *                 0x0: Flash redundance 1 is used for repairing.
  *         bit[7:1]: Page address of flash which is defective
  */
__STATIC_INLINE uint32_t md_msc_get_flash_repair1(void)
{
    return READ_BITS(MSC->FREPSR, MSC_FREPSR_REP1_MSK, MSC_FREPSR_REP1_POSS);
}

/**
  * @brief  Check flash redundance 1 repair information is true or false
  * @retval 0x0: True, 0x1: False
  */
__STATIC_INLINE uint32_t md_msc_flash_repair1_is_true(void)
{
    return READ_BITS(MSC->FREPSR, MSC_FREPSR_REP1LS_MSK, MSC_FREPSR_REP1LS_POS);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _MD_MSC_H_ */

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
