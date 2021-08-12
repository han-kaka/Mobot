/**********************************************************************************
 *
 * @file    irq.c
 * @brief   Interrupt handler
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

#include "bsp_mp6050.h"
#include "md_utils.h"

/* Exported Types ------------------------------------------------------------ */
/* Exported Macros ----------------------------------------------------------- */
/* Exported Variables -------------------------------------------------------- */
//extern uint8_t g_complete;
//extern md_dma_config_t g_dma_rx_config, g_dma_tx_config;
//extern uint32_t g_adc_result;

/* Exported Constants -------------------------------------------------------- */
/* Exported Functions -------------------------------------------------------- */

/** @addtogroup Projects_Examples_ALD
  * @{
  */

/** @addtogroup Examples
  * @{
  */

/**
  * @brief  NMI IRQ handler
  * @retval None
  */
void NMI_Handler(void)
{
    /* Added Emergency operation */
    return;
}

/**
  * @brief  Hardfault IRQ handler
  * @retval None
  */
void HardFault_Handler(void)
{
    /* Added debug information */
    while (1)
        ;
}

/**
  * @brief  MemManage IRQ handler
  * @retval None
  */
void MemManage_Handler(void)
{
    /* Added debug information */
    while (1)
        ;
}

/**
  * @brief  BusFault IRQ handler
  * @retval None
  */
void BusFault_Handler(void)
{
    /* Added debug information */
    while (1)
        ;
}

/**
  * @brief  UsageFault IRQ handler
  * @retval None
  */
void UsageFault_Handler(void)
{
    /* Added debug information */
    while (1)
        ;
}

/**
  * @brief  Supervisor Call IRQ handler
  * @retval None
  */
void SVC_Handler(void)
{
    /* Added system callback */
    return;
}

/**
  * @brief  Debug Monitor IRQ handler
  * @retval None
  */
void DebugMon_Handler(void)
{
    /* Added debug operation */
    return;
}

/**
  * @brief  PendSV IRQ handler
  * @retval None
  */
void PendSV_Handler(void)
{
    /* Added thread switching operation */
    return;
}

/**
  * @brief  SysTick IRQ handler
  * @retval None
  */
void SysTick_Handler(void)
{
    md_inc_tick();
    return;
}

/**
  * @brief ADC_IRQHandler.
  * @param none
  * @retval none
  */

void ADC_IRQHandler(void)
{
//    if (md_adc_get_stat_nche(ADC) == 1)
//    {
//        md_adc_set_clr_nche(ADC);
//        md_adc_set_clr_nchs(ADC);

//        g_adc_result = md_adc_get_normal_channel_val(ADC) * 3320 / 4096;
//    }
}

/**
  * @brief  GP16C4T1 UPDATE IRQ handler
  * @retval None
  */
void AD16C4T0_UP_IRQHandler(void)
{
//    /* update interrupt service program */
//    if (md_timer_get_update_valid_interrupt_flag_uei(AD16C4T0) == 1)
//    {
//        md_timer_clear_update_interrupt_flag_ueic(AD16C4T0);

//    }

//    return;
}

/**
  * @brief  I2C Event IRQ handler
  * @retval None
  */
void I2C0_EV_IRQHandler(void)
{
    return;
}

/**
  * @brief  I2C Error IRQ handler
  * @retval None
  */
void I2C0_ERR_IRQHandler(void)
{
    return;
}

/**
  * @brief  DMA IRQ handler
  * @retval None
  */
void DMA_IRQHandler(void)
{
//    if (md_dma_is_active_flag_done(MD_DMA_CH_0)&&md_dma_is_enabled_it_done(MD_DMA_CH_0))
//    {
//        md_dma_clear_flag_done(MD_DMA_CH_0);
//        md_dma_disable_it_done(MD_DMA_CH_0);
//        md_i2c_set_stop(I2C1);
//        g_complete = 1;
//    }

//    if (md_dma_is_active_flag_done(MD_DMA_CH_1)&&md_dma_is_enabled_it_done(MD_DMA_CH_1))
//    {
//        md_dma_clear_flag_done(MD_DMA_CH_1);
//        md_dma_disable_it_done(MD_DMA_CH_1);
//        md_i2c_set_stop(I2C1);
//        g_complete = 1;
//    }

//    return;
}
/**
  * @}
  */
/**
  * @}
  */

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
