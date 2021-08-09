/**********************************************************************************
 *
 * @file    md_lptim.h
 * @brief   Header file of LPTIM module driver.
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
#ifndef __MD_LPTIM_H
#define __MD_LPTIM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------ */
#include "md_utils.h"
#include "type.h"

/** @addtogroup Micro_Driver
  * @{
  */

/** @defgroup MD_LPTIM LPTIM
  * @brief LPTIM micro driver
  * @{
  */
/** @defgroup MD_LPTIM_Pubulic_Types LPTIM Pubulic Types
  * @{
  */


/**
  * @brief LPTIM start mode select
  */
typedef enum {
	MD_LPTIM_OUT_MODE_NO        = 0U,	/**< 禁止输出 */
	MD_LPTIM_OUT_MODE_OVERTURN  = 1U,	/**< 计数溢出输出翻转 */
    MD_LPTIM_OUT_MODE_PULSE     = 2U,	/**< 计数溢出输出脉冲 */
	MD_LPTIM_OUT_MODE_PWM       = 3U,	/**< 输出PWM */
} md_lptim_out_mode_t;

  
/**
  * @brief LPTIM prescaler
  */
typedef enum {
	MD_LPTIM_PRESC_1   = 0U,	/**< No prescaler is used */
	MD_LPTIM_PRESC_2   = 1U,	/**< Clock is divided by 2 */
	MD_LPTIM_PRESC_4   = 2U,	/**< Clock is divided by 4 */
	MD_LPTIM_PRESC_8   = 3U,	/**< Clock is divided by 8 */
	MD_LPTIM_PRESC_16  = 4U,	/**< Clock is divided by 16 */
	MD_LPTIM_PRESC_32  = 5U,	/**< Clock is divided by 32 */
	MD_LPTIM_PRESC_64  = 6U,	/**< Clock is divided by 64 */
	MD_LPTIM_PRESC_128 = 7U,	/**< Clock is divided by 128 */
} md_lptim_presc_t;

/**
  * @brief LPTIM start mode select
  */
typedef enum {
	MD_LPTIM_MODE_SINGLE     = 0U,	/**< Start single mode */
	MD_LPTIM_MODE_CONTINUOUS = 1U,	/**< Start continuous mode */
} md_lptim_mode_t;

/**
  * @brief LPTIM Init Structure definition
  */
typedef struct {
	md_lptim_presc_t psc;		/**< Specifies the prescaler value */
	uint16_t arr;			/**< Specifies the update value */
	uint16_t cmp;			/**< Specifies the compare value */
	md_lptim_mode_t mode;		/**< Specifies the start mode */
} md_lptim_init_t;
/**
  * @}
  */
  
/** @defgroup MD_LPTIM_Public_Functions LPTIM Public Functions
  * @{
  */
/** @defgroup MD_LPTIM_Public_Functions_Group2 CON0
  * @{
  */
/**
  * @brief  Set LPTIM clock source.
  * @param  LPTx LPTIM Instance
  * @param  clk: The value of following:
  *         - 0x0: internal clock source
  *         - 0x1: external clock source
  * @retval None
  */
__STATIC_INLINE void md_lptim_set_clock_source(LPTIM_TypeDef *LPTx, uint32_t clk)
{
	MODIFY_REG(LPTx->CON0, LP16T_CON0_CKSEL_MSK, clk << LP16T_CON0_CKSEL_POS);
}

/**
  * @brief  Get LPTIM clock source.
  * @param  LPTx LPTIM Instance
  * @retval  clk: The value of following:
  *         - 0x0: internal clock source
  *         - 0x1: external clock source
  */
__STATIC_INLINE uint32_t md_lptim_get_clock_source(LPTIM_TypeDef *LPTx)
{
	return READ_BITS(LPTx->CON0, LP16T_CON0_CKSEL_MSK, LP16T_CON0_CKSEL_POS);
}

/**
  * @brief  Set LPTIM clock valid edge.
  * @param  LPTx LPTIM Instance
  * @param  ckpol: The value of following:
  *         - 0x0: rising edge valid 
  *         - 0x1: falling edge valid
  * @retval None
  */
__STATIC_INLINE void md_lptim_set_clock_edge(LPTIM_TypeDef *LPTx, uint32_t ckpol)
{
	MODIFY_REG(LPTx->CON0, LP16T_CON0_CKPOL_MSK, ckpol << LP16T_CON0_CKPOL_POS);
}

/**
  * @brief  Get LPTIM clock valid edge.
  * @param  LPTx LPTIM Instance
  * @retval  ckpol: The value of following:
  *         - 0x0: rising edge valid 
  *         - 0x1: falling edge valid
  */
__STATIC_INLINE uint32_t md_lptim_get_clock_edge(LPTIM_TypeDef *LPTx)
{
	return READ_BITS(LPTx->CON0, LP16T_CON0_CKPOL_MSK, LP16T_CON0_CKPOL_POS);
}

/**
  * @brief  Set LPTIM external clock filter.
  * @param  LPTx LPTIM Instance
  * @param  flt The value of following:
  *         - 0x0: any change 
  *         - 0x1: 2 clk period
  *         - 0x2: 4 clk period
  *         - 0x3: 8 clk period
  * @retval None
  */
__STATIC_INLINE void md_lptim_set_clock_filter(LPTIM_TypeDef *LPTx, uint32_t flt)
{
	MODIFY_REG(LPTx->CON0, LP16T_CON0_CKFLT_MSK, flt << LP16T_CON0_CKFLT_POSS);
}

/**
  * @brief  Get LPTIM external clock filter.
  * @param  LPTx LPTIM Instance
  * @retval  flt: The value of following:
  *         - 0x0: any change 
  *         - 0x1: 2 clk period
  *         - 0x2: 4 clk period
  *         - 0x3: 8 clk period
  */
__STATIC_INLINE uint32_t md_lptim_get_clock_filter(LPTIM_TypeDef *LPTx)
{
	return READ_BITS(LPTx->CON0, LP16T_CON0_CKFLT_MSK, LP16T_CON0_CKFLT_POSS);
}

/**
  * @brief  Set LPTIM trigger signal filter.
  * @param  LPTx LPTIM Instance
  * @param  flt The value of following:
  *         - 0x0: any change 
  *         - 0x1: 2 clk period
  *         - 0x2: 4 clk period
  *         - 0x3: 8 clk period
  * @retval None
  */
__STATIC_INLINE void md_lptim_set_trigger_signal_filter(LPTIM_TypeDef *LPTx, uint32_t flt)
{
	MODIFY_REG(LPTx->CON0, LP16T_CON0_TRGFLT_MSK, flt << LP16T_CON0_TRGFLT_POSS);
}

/**
  * @brief  Get LPTIM trigger signal filter.
  * @param  LPTx LPTIM Instance
  * @retval  flt: The value of following:
  *         - 0x0: any change 
  *         - 0x1: 2 clk period
  *         - 0x2: 4 clk period
  *         - 0x3: 8 clk period
  */
__STATIC_INLINE uint32_t md_lptim_get_trigger_signal_filter(LPTIM_TypeDef *LPTx)
{
	return READ_BITS(LPTx->CON0, LP16T_CON0_TRGFLT_MSK, LP16T_CON0_TRGFLT_POSS);
}

/**
  * @brief  Set LPTIM clock prscaler
  * @param  LPTx LPTIM Instance
  * @param  pre The value of following:
  *         - 0x0: clk/1 
  *         - 0x1: clk/2
  *         - 0x2: clk/4
  *         - 0x3: clk/8
  *         - 0x4: clk/16
  *         - 0x5: clk/32
  *         - 0x6: clk/64
  *         - 0x7: clk/128
  * @retval None
  */
__STATIC_INLINE void md_lptim_set_clock_prescaler(LPTIM_TypeDef *LPTx, uint32_t pre)
{
	MODIFY_REG(LPTx->CON0, LP16T_CON0_PRESC_MSK, pre << LP16T_CON0_PRESC_POSS);
}

/**
  * @brief  Get LPTIM clock prscaler
  * @param  LPTx LPTIM Instance
  * @retval  The value of following:
  *         - 0x0: clk/1 
  *         - 0x1: clk/2
  *         - 0x2: clk/4
  *         - 0x3: clk/8
  *         - 0x4: clk/16
  *         - 0x5: clk/32
  *         - 0x6: clk/64
  *         - 0x7: clk/128
  */
__STATIC_INLINE uint32_t md_lptim_get_clock_prescaler(LPTIM_TypeDef *LPTx)
{
	return READ_BITS(LPTx->CON0, LP16T_CON0_PRESC_MSK, LP16T_CON0_PRESC_POSS);
}

/**
  * @brief  Set LPTIM trigger source
  * @param  LPTx LPTIM Instance
  * @param  tri The value of following:
  *         - 0x0: ext_trig0 
  *         - 0x1: ext_trig1
  *         - 0x2: ext_trig2
  *         - 0x3: ext_trig3
  *         - 0x4: ext_trig4
  *         - 0x5: ext_trig5
  *         - 0x6: ext_trig6
  *         - 0x7: ext_trig7
  * @retval None
  */
__STATIC_INLINE void md_lptim_set_trigger_source(LPTIM_TypeDef *LPTx, uint32_t tri)
{
	MODIFY_REG(LPTx->CON0, LP16T_CON0_TRIGSEL_MSK, tri << LP16T_CON0_TRIGSEL_POSS);
}

/**
  * @brief  Get LPTIM trigger source
  * @param  LPTx LPTIM Instance
  * @retval  The value of following:
  *         - 0x0: ext_trig0 
  *         - 0x1: ext_trig1
  *         - 0x2: ext_trig2
  *         - 0x3: ext_trig3
  *         - 0x4: ext_trig4
  *         - 0x5: ext_trig5
  *         - 0x6: ext_trig6
  *         - 0x7: ext_trig7
  */
__STATIC_INLINE uint32_t md_lptim_get_trigger_source(LPTIM_TypeDef *LPTx)
{
	return READ_BITS(LPTx->CON0, LP16T_CON0_TRIGSEL_MSK, LP16T_CON0_TRIGSEL_POSS);
}

/**
  * @brief  Set LPTIM trigger polarity 
  * @param  LPTx LPTIM Instance
  * @param  pol The value of following:
  *         - 0x0: software  
  *         - 0x1: rising
  *         - 0x2: falling
  *         - 0x3: both-edge
  * @retval None
  */
__STATIC_INLINE void md_lptim_set_trigger_polarity(LPTIM_TypeDef *LPTx, uint32_t pol)
{
	MODIFY_REG(LPTx->CON0, LP16T_CON0_TRIGEN_MSK, pol << LP16T_CON0_TRIGEN_POSS);
}

/**
  * @brief  Get LPTIM trigger polarity 
  * @param  LPTx LPTIM Instance
  * @retval  The value of following:
  *         - 0x0: software  
  *         - 0x1: rising
  *         - 0x2: falling
  *         - 0x3: both-edge
  */
__STATIC_INLINE uint32_t md_lptim_get_trigger_polarity(LPTIM_TypeDef *LPTx)
{
	return READ_BITS(LPTx->CON0, LP16T_CON0_TRIGEN_MSK, LP16T_CON0_TRIGEN_POSS);
}

/**
  * @brief  Set LPTIM output wave state
  * @param  LPTx LPTIM Instance
  * @param  wave The value of following:
  *         - 0x0: not output  
  *         - 0x1: toggle
  *         - 0x2: pulse
  *         - 0x3: pwm
  * @retval None
  */
__STATIC_INLINE void md_lptim_set_output_state(LPTIM_TypeDef *LPTx, uint32_t wave)
{
	MODIFY_REG(LPTx->CON0, LP16T_CON0_WAVE_MSK, wave << LP16T_CON0_WAVE_POSS);
}

/**
  * @brief  Get LPTIM output wave state
  * @param  LPTx LPTIM Instance
  * @retval  The value of following:
  *         - 0x0: not output  
  *         - 0x1: toggle
  *         - 0x2: pulse
  *         - 0x3: pwm
  */
__STATIC_INLINE uint32_t md_lptim_get_output_state(LPTIM_TypeDef *LPTx)
{
	return READ_BITS(LPTx->CON0, LP16T_CON0_WAVE_MSK, LP16T_CON0_WAVE_POSS);
}

/**
  * @brief  Set LPTIM output polarity
  * @param  LPTx LPTIM Instance
  * @param  wavp: The value of following:
  *         - 0x0: not toggle  
  *         - 0x1: toggle
  * @retval None
  */
__STATIC_INLINE void md_lptim_set_wave_polarity(LPTIM_TypeDef *LPTx, uint32_t wavp)
{
	MODIFY_REG(LPTx->CON0, LP16T_CON0_WAVEPOL_MSK, wavp << LP16T_CON0_WAVEPOL_POS);
}

/**
  * @brief  Get LPTIM output polarity
  * @param  LPTx LPTIM Instance
  * @retval  The value of following:
  *         - 0x0: not toggle  
  *         - 0x1: toggle
  */
__STATIC_INLINE uint32_t md_lptim_get_wave_polarity(LPTIM_TypeDef *LPTx)
{
	return READ_BITS(LPTx->CON0, LP16T_CON0_WAVEPOL_MSK, LP16T_CON0_WAVEPOL_POS);
}

/**
  * @brief  Set LPTIM register update mode
  * @param  LPTx LPTIM Instance
  * @param  pld The value of following:
  *         - 0x0: register update after APB write 
  *         - 0x1: register update after count period
  * @retval None
  */
__STATIC_INLINE void md_lptim_set_update_mode(LPTIM_TypeDef *LPTx, uint32_t pld)
{
	MODIFY_REG(LPTx->CON0, LP16T_CON0_PRELOAD_MSK, pld << LP16T_CON0_PRELOAD_POS);
}

/**
  * @brief  Get LPTIM register update mode
  * @param  LPTx LPTIM Instance
  * @retval  The value of following:
  *         - 0x0: register update after APB write 
  *         - 0x1: register update after count period
  */
__STATIC_INLINE uint32_t md_lptim_get_update_mode(LPTIM_TypeDef *LPTx)
{
	return READ_BITS(LPTx->CON0, LP16T_CON0_PRELOAD_MSK, LP16T_CON0_PRELOAD_POS);
}
/**
  * @}
  */
/** @defgroup MD_LPTIM_Public_Functions_Group3 CON1
  * @{
  */
/**
  * @brief  Enable LPTIM 
  * @param  LPTx LPTIM Instance
  * @retval None
  */
__STATIC_INLINE void md_lptim_enable(LPTIM_TypeDef *LPTx)
{
	SET_BIT(LPTx->CON1, LP16T_CON1_ENABLE_MSK);
}

/**
  * @brief  Disable LPTIM 
  * @param  LPTx LPTIM Instance
  * @retval None
  */
__STATIC_INLINE void md_lptim_disable(LPTIM_TypeDef *LPTx)
{
	CLEAR_BIT(LPTx->CON1, LP16T_CON1_ENABLE_MSK);
}

/**
  * @brief  Set LPTIM single mode 
  * @param  LPTx LPTIM Instance
  * @retval None
  */
__STATIC_INLINE void md_lptim_set_single_mode(LPTIM_TypeDef *LPTx)
{
	SET_BIT(LPTx->CON1, LP16T_CON1_SNGSTRT_MSK);
}

/**
  * @brief  Set LPTIM continuous mode 
  * @param  LPTx LPTIM Instance
  * @retval None
  */
__STATIC_INLINE void md_lptim_set_continuous_mode(LPTIM_TypeDef *LPTx)
{
	SET_BIT(LPTx->CON1, LP16T_CON1_CNTSTRT_MSK);
}
/**
  * @}
  */
/** @defgroup MD_LPTIM_Public_Functions_Group4 ARR
  * @{
  */
/**
  * @brief  Set LPTIM auto reload value  
  * @param  LPTx LPTIM Instance
  * @param  reloadvalue Value between Min_Data=0x00 and Max_Data=0xFFFF
  * @retval None
  */
__STATIC_INLINE void md_lptim_set_auto_reload_value(LPTIM_TypeDef *LPTx, uint32_t reloadvalue)
{
	MODIFY_REG(LPTx->ARR, LP16T_ARR_ARR_MSK, reloadvalue);
}

/**
  * @brief  Get LPTIM auto reload value  
  * @param  LPTx LPTIM Instance
  * @retval Value between Min_Data=0x00 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint32_t md_lptim_get_auto_reload_value(LPTIM_TypeDef *LPTx)
{
	return READ_BITS(LPTx->ARR, LP16T_ARR_ARR_MSK, LP16T_ARR_ARR_POSS);
}
/**
  * @}
  */
/** @defgroup MD_LPTIM_Public_Functions_Group5 CNT
  * @{
  */
/**
  * @brief  Get LPTIM counter count value  
  * @param  LPTx LPTIM Instance
  * @retval Value between Min_Data=0x00 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint32_t md_lptim_get_counter_count_value(LPTIM_TypeDef *LPTx)
{
	return READ_BITS(LPTx->CNT, LP16T_CNT_CNT_MSK, LP16T_CNT_CNT_POSS);
}
/**
  * @}
  */
/** @defgroup MD_LPTIM_Public_Functions_Group6 CMP
  * @{
  */
/**
  * @brief  Set LPTIM compare value
  * @param  LPTx LPTIM Instance
  * @param  cmpvalue Value between Min_Data=0x00 and Max_Data=0xFFFF
  * @retval None
  */
__STATIC_INLINE void md_lptim_set_compare_value(LPTIM_TypeDef *LPTx, uint32_t cmpvalue)
{
	MODIFY_REG(LPTx->CMP, LP16T_CMP_CMP_MSK, cmpvalue);
}

/**
  * @brief  Get LPTIM compare value
  * @param  LPTx LPTIM Instance
  * @retval Value between Min_Data=0x00 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint32_t md_lptim_get_compare_value(LPTIM_TypeDef *LPTx)
{
	return READ_BITS(LPTx->CMP, LP16T_CMP_CMP_MSK, LP16T_CMP_CMP_POSS);
}
/**
  * @}
  */
/** @defgroup MD_LPTIM_Public_Functions_Group7 IER
  * @{
  */
/**
  * @brief  Enable LPTIM CMPMIE interrupt.
  * @param  LPTx LPTIM Instance
  * @retval None
  */
__STATIC_INLINE void md_lptim_enable_cmpmie_intrrupt(LPTIM_TypeDef *LPTx)
{
	SET_BIT(LPTx->IER, LP16T_IER_CMPMIE_MSK);
}

/**
  * @brief  Disable LPTIM CMPMIE interrupt. 
  * @param  LPTx LPTIM Instance
  * @retval None
  */
__STATIC_INLINE void md_lptim_disable_cmpmie_intrrupt(LPTIM_TypeDef *LPTx)
{
	CLEAR_BIT(LPTx->IER, LP16T_IER_CMPMIE_MSK);
}

/**
  * @brief  Check  LPTIM CMPMIE interrupt is enabled. 
  * @param  LPTx LPTIM Instance
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_lptim_cmpmie_interrupt_is_enable(LPTIM_TypeDef *LPTx)
{
	return READ_BITS(LPTx->IER, LP16T_IER_CMPMIE_MSK, LP16T_IER_CMPMIE_POS);
}

/**
  * @brief  Enable LPTIM ARRMIE interrupt. 
  * @param  LPTx LPTIM Instance
  * @retval None
  */
__STATIC_INLINE void md_lptim_enable_arrmie_intrrupt(LPTIM_TypeDef *LPTx)
{
	SET_BIT(LPTx->IER, LP16T_IER_ARRMIE_MSK);
}

/**
  * @brief   Disable LPTIM ARRMIE interrupt. 
  * @param  LPTx LPTIM Instance
  * @retval None
  */
__STATIC_INLINE void md_lptim_disable_arrmie_intrrupt(LPTIM_TypeDef *LPTx)
{
	CLEAR_BIT(LPTx->IER, LP16T_IER_ARRMIE_MSK);
}

/**
  * @brief  Check  LPTIM ARRMIE interrupt is enabled. 
  * @param  LPTx LPTIM Instance
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_lptim_arrmie_interrupt_is_enable(LPTIM_TypeDef *LPTx)
{
	return READ_BITS(LPTx->IER, LP16T_IER_ARRMIE_MSK, LP16T_IER_ARRMIE_POS);
}

/**
  * @brief  Enable LPTIM EXTTRIGIE interrupt. 
  * @param  LPTx LPTIM Instance
  * @retval None
  */
__STATIC_INLINE void md_lptim_enable_exttrigie_intrrupt(LPTIM_TypeDef *LPTx)
{
	SET_BIT(LPTx->IER, LP16T_IER_EXTTRIGIE_MSK);
}

/**
  * @brief  Disable LPTIM EXTTRIGIE interrupt. 
  * @param  LPTx LPTIM Instance
  * @retval None
  */
__STATIC_INLINE void md_lptim_disable_exttrigie_intrrupt(LPTIM_TypeDef *LPTx)
{
	CLEAR_BIT(LPTx->IER, LP16T_IER_EXTTRIGIE_MSK);
}

/**
  * @brief  Check  LPTIM EXTTRIGIE interrupt is enabled. 
  * @param  LPTx LPTIM Instance
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_lptim_exttrigie_interrupt_is_enable(LPTIM_TypeDef *LPTx)
{
	return READ_BITS(LPTx->IER, LP16T_IER_EXTTRIGIE_MSK, LP16T_IER_EXTTRIGIE_POS);
}
/**
  * @}
  */
/** @defgroup MD_LPTIM_Public_Functions_Group8 ISR
  * @{
  */
/**
  * @brief  Get LPTIM CMPM interrutpt state
  * @param  LPTx LPTIM Instance
  * @retval State
  */
__STATIC_INLINE uint32_t md_lptim_get_cmpm_interrupt_state(LPTIM_TypeDef *LPTx)
{
	return READ_BITS(LPTx->ISR, LP16T_ISR_CMPM_MSK, LP16T_ISR_CMPM_POS);
}

/**
  * @brief  Get LPTIM ARRM interrutpt state
  * @param  LPTx LPTIM Instance
  * @retval State
  */
__STATIC_INLINE uint32_t md_lptim_get_arrm_interrupt_state(LPTIM_TypeDef *LPTx)
{
	return READ_BITS(LPTx->ISR, LP16T_ISR_ARRM_MSK, LP16T_ISR_ARRM_POS);
}

/**
  * @brief  Get LPTIM EXTTRIG interrutpt state
  * @param  LPTx LPTIM Instance
  * @retval State
  */
__STATIC_INLINE uint32_t md_lptim_get_exttrig_interrupt_state(LPTIM_TypeDef *LPTx)
{
	return READ_BITS(LPTx->ISR, LP16T_ISR_EXTTRIG_MSK, LP16T_ISR_EXTTRIG_POS);
}
/**
  * @}
  */
/** @defgroup MD_LPTIM_Public_Functions_Group9 IFC
  * @{
  */
/**
  * @brief  Clear LPTIM CMPM interrutpt flag
  * @param  LPTx LPTIM Instance
  * @retval State
  */
__STATIC_INLINE void md_lptim_clear_cmpm_interrupt_flag(LPTIM_TypeDef *LPTx)
{
	SET_BIT(LPTx->IFC, LP16T_IFC_CMPM_MSK);
}

/**
  * @brief  Clear LPTIM ARRM interrutpt flag
  * @param  LPTx LPTIM Instance
  * @retval State
  */
__STATIC_INLINE void md_lptim_clear_arrm_interrupt_flag(LPTIM_TypeDef *LPTx)
{
	SET_BIT(LPTx->IFC, LP16T_IFC_ARRM_MSK);
}

/**
  * @brief  Clear LPTIM EXTTRIG interrutpt flag
  * @param  LPTx LPTIM Instance
  * @retval State
  */
__STATIC_INLINE void md_lptim_clear_exttrig_interrupt_flag(LPTIM_TypeDef *LPTx)
{
	SET_BIT(LPTx->IFC, LP16T_IFC_EXTTRIG_MSK);
}
/**
  * @}
  */
/** @defgroup MD_LPTIM_Public_Functions_Group10 UPDATE
  * @{
  */
/**
  * @brief  Set LPTIM UDIS update 
  * @param  LPTx LPTIM Instance
  * @param  ud The value of following:
  *         - 0x0: new value update to low speed region
  *         - 0x1: not update register after write
  * @retval None
  */
__STATIC_INLINE void md_lptim_set_register_update_udis(LPTIM_TypeDef *LPTx, uint32_t ud)
{
	MODIFY_REG(LPTx->UPDATE, LP16T_UPDATE_UDIS_MSK, ud << LP16T_UPDATE_UDIS_POS);
}

/**
  * @brief  Get LPTIM UDIS update 
  * @param  LPTx LPTIM Instance
  * @retval The value of following:
  *         - 0x0: new value update to low speed region
  *         - 0x1: not update register after write
  */
__STATIC_INLINE uint32_t md_lptim_get_register_update_udis(LPTIM_TypeDef *LPTx)
{
	return READ_BITS(LPTx->UPDATE, LP16T_UPDATE_UDIS_MSK, LP16T_UPDATE_UDIS_POS);
}
/**
  * @}
  */
/** @defgroup MD_LPTIM_Public_Functions_Group11 SYNCSTAT
  * @{
  */
/**
  * @brief  Get LPTIM CON1WBSY update state 
  * @param  LPTx LPTIM Instance
  * @retval The value of following:
  *         - 0x0: update not start or update has finished
  *         - 0x1: updating
  */
__STATIC_INLINE uint32_t md_lptim_get_con1_update_state(LPTIM_TypeDef *LPTx)
{
	return READ_BITS(LPTx->SYNCSTAT, LP16T_SYNCSTAT_CON1WBSY_MSK, LP16T_SYNCSTAT_CON1WBSY_POS);
}

/**
  * @brief  Get LPTIM ARRWBSY update state 
  * @param  LPTx LPTIM Instance
  * @retval The value of following:
  *         - 0x0: update not start or update has finished
  *         - 0x1: updating
  */
__STATIC_INLINE uint32_t md_lptim_get_arr_update_state(LPTIM_TypeDef *LPTx)
{
	return READ_BITS(LPTx->SYNCSTAT, LP16T_SYNCSTAT_ARRWBSY_MSK, LP16T_SYNCSTAT_ARRWBSY_POS);
}

/**
  * @brief  Get LPTIM CMPWBSY update state 
  * @param  LPTx LPTIM Instance
  * @retval The value of following:
  *         - 0x0: update not start or update has finished
  *         - 0x1: updating
  */
__STATIC_INLINE uint32_t md_lptim_get_cmp_update_state(LPTIM_TypeDef *LPTx)
{
	return READ_BITS(LPTx->SYNCSTAT, LP16T_SYNCSTAT_CMPWBSY_MSK, LP16T_SYNCSTAT_CMPWBSY_POS);
}

/**
  * @}
  */
/** @defgroup MD_LPTIM_Public_Functions_Group1 Initialization
  * @{
  */
extern md_status_t md_lptim_base_init(LPTIM_TypeDef *LPTx, md_lptim_init_t *init);
extern void md_lptim_struct_init(md_lptim_init_t *init);
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
