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
#include "ald_conf.h"
#include "bsp_mp6050.h"

/* Exported Types ------------------------------------------------------------ */

/* Exported Macros ----------------------------------------------------------- */

/* Exported Variables -------------------------------------------------------- */
extern i2c_handle_t g_h_i2c;
extern uart_handle_t g_h_uart;

/* Exported Constants -------------------------------------------------------- */


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
    ald_inc_tick();
    return;
}

/**
  * @brief  CMU IRQ#6 handler
  * @retval None
  */
void CMU_Handler(void)
{
    ald_cmu_irq_handler();
    return;
}

#ifdef ALD_DMA
/**
  * @brief  DMA IRQ#66 handler
  * @retval None
  */
void DMA_IRQHandler(void)
{
    ald_dma_irq_handler();
}
#endif /*ALD_DMA*/

/**
  * @brief  I2c Event IRQ handler
  * @retval None
  */
void I2C1_EV_IRQHandler(void)
{
    ald_i2c_ev_irq_handler(&g_h_i2c);
}

/**
  * @brief  I2c Error IRQ handler
  * @retval None
  */
void I2C1_ERR_IRQHandler(void)
{
    ald_i2c_er_irq_handler(&g_h_i2c);
}

/**
  * @brief  Uart0 handler
  * @retval None
  */
void UART0_IRQHandler(void)
{
    ald_uart_irq_handler(&g_h_uart);

    return;
}

/**
  * @}
  */
/**
  * @}
  */

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
