/**********************************************************************************
 *
 * @file    md_calc.h
 * @brief   Header file of CALC module driver.
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

#ifndef __MD_CALC_H__
#define __MD_CALC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------ */
#include "md_utils.h"


/** @addtogroup Micro_Driver
  * @{
  */

/** @addtogroup CALC
  * @{
  */

/** @addtogroup CALC_Public_Functions
  * @{
  */
extern uint32_t md_calc_sqrt(uint32_t data);
extern uint32_t md_calc_div(uint32_t dividend, uint32_t divisor, uint32_t *remainder);
extern int32_t md_calc_div_sign(int32_t dividend, int32_t divisor, int32_t *remainder);
extern flag_status_t md_calc_get_dz_status(void);
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

#endif /* __ALD_CALC_H__ */

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
