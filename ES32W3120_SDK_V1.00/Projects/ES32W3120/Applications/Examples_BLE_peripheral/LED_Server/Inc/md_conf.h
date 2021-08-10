/**********************************************************************************
 *
 * @file    md_conf.h
 * @brief   Enable/Disable the peripheral module.
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


#ifndef __MD_CONF_H__
#define __MD_CONF_H__

/* Includes ------------------------------------------------------------------ */

#define MD_ADC
/* #define MD_BKPC */
/* #define MD_CALC */
#define MD_CMU
/* #define MD_CRC */
/* #define MD_CRYPT */
#define MD_DMA
/* #define MD_ECC */
#define MD_GPIO
/* #define MD_HASH */
#define MD_I2C
/* #define MD_IWDT */
/* #define MD_LPTIM */
/* #define MD_MSC */
#define MD_PIS
/* #define MD_PMU */
/* #define MD_RMU */
#define MD_SPI
#define MD_SYSCFG
/* #define MD_TIMER */
/* #define MD_TRNG */
#define MD_UART
#define MD_UTILS
/* #define MD_WWDT */
/* #define MD_TYPE */

#ifdef MD_ADC
    #include "md_adc.h"
#endif /* MD_ADC */

#ifdef MD_BKPC
    #include "md_bkpc.h"
#endif /* MD_BKPC */

#ifdef MD_CALC
    #include "md_calc.h"
#endif /* MD_CALC */

#ifdef MD_CMU
    #include "md_cmu.h"
#endif /* MD_CMU */

#ifdef MD_CRC
    #include "md_crc.h"
#endif /* MD_CRC */

#ifdef MD_CRYPT
    #include "md_crypt.h"
#endif /* MD_CRYPT */

#ifdef MD_DMA
    #include "md_dma.h"
#endif /* MD_DMA */

#ifdef MD_ECC
    #include "md_ecc.h"
#endif /* MD_ECC */

#ifdef MD_GPIO
    #include "md_gpio.h"
#endif /* MD_GPIO */

#ifdef MD_HASH
    #include "md_hash.h"
#endif /* MD_HASH */

#ifdef MD_I2C
    #include "md_i2c.h"
#endif /* MD_I2C */

#ifdef MD_IWDT
    #include "md_iwdt.h"
#endif /* MD_IWDT */

#ifdef MD_LPTIM
    #include "md_lptim.h"
#endif /* MD_LPTIM */

#ifdef MD_MSC
    #include "md_msc.h"
#endif /* MD_MSC */

#ifdef MD_PIS
    #include "md_pis.h"
#endif /* MD_PIS */

#ifdef MD_PMU
    #include "md_pmu.h"
#endif /* MD_PMU */

#ifdef MD_RMU
    #include "md_rmu.h"
#endif /* MD_RMU */

#ifdef MD_SPI
    #include "md_spi.h"
#endif /* MD_SPI */

#ifdef MD_SYSCFG
    #include "md_syscfg.h"
#endif /* MD_SYSCFG */

#ifdef MD_TIMER
    #include "md_timer.h"
#endif /* MD_TIMER */

#ifdef MD_TRNG
    #include "md_trng.h"
#endif /* MD_TRNG */

#ifdef MD_UART
    #include "md_uart.h"
#endif /* MD_UART */

#ifdef MD_UTILS
    #include "md_utils.h"
#endif /* MD_UTILS */

#ifdef MD_WWDT
    #include "md_wwdt.h"
#endif /* MD_WWDT */

#ifdef MD_TYPE
    #include "type.h"
#endif /* MD_TYPE */

/* Exported Types ------------------------------------------------------------ */
/* Exported Macros ----------------------------------------------------------- */
/* Exported Variables -------------------------------------------------------- */
/* Exported Constants -------------------------------------------------------- */
/* Exported Functions -------------------------------------------------------- */

#endif /*__MD_CONF_H__*/

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
