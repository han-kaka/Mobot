/**********************************************************************************
 *
 * @file    md_pis.h
 * @brief   Header file of PIS module driver.
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

#ifndef __MD_PIS_H__
#define __MD_PIS_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------ */

/* Exported Macros ----------------------------------------------------------- */
/* Exported Variables -------------------------------------------------------- */
/* Exported Constants -------------------------------------------------------- */

#include "md_utils.h"
#include "type.h"

/**
  * @addtogroup Micro_Driver
  * @{
  */

/**
  * @defgroup MD_PIS PIS
  * @brief PIS micro driver
  * @{
  */

/* Exported Types ------------------------------------------------------------ */

/** @defgroup MD_PIS_Public_Types PIS Public Types
  * @verbatim
      In PIS module, for the convenience of code maintenance,
      TIMERx is used to indicate the sequence of the timer peripheral.
      Different product series TIMERx represent different meanings:
      1. For ES32F36xx series:
      TIMER0 ----> AD16C4T0
      TIMER1 ----> AD16C4T1
      TIMER2 ----> GP32C4T0
      TIMER3 ----> GP32C4T1

      2. For ES32F393x/ES32F336x/ES32F392x series:
      TIMER0 ----> GP16C4T0
      TIMER1 ----> GP16C4T1
      TIMER2 ----> GP32C4T0
      TIMER3 ----> GP32C4T1
    @endverbatim
  * @{
  */

/**
  * @brief Producer entry
  */
typedef enum
{
    MD_PIS_NON                 = 0x0U,  /**< No async */
    MD_PIS_GPIO_PIN0           = 0x10U, /**< Pin0, level,support async */
    MD_PIS_GPIO_PIN1           = 0x11U, /**< Pin1, level,support async */
    MD_PIS_GPIO_PIN2           = 0x12U, /**< Pin2, level,support async */
    MD_PIS_GPIO_PIN3           = 0x13U, /**< Pin3, level,support async */
    MD_PIS_GPIO_PIN4           = 0x14U, /**< Pin4, level,support async */
    MD_PIS_GPIO_PIN5           = 0x15U, /**< Pin5, level,support async */
    MD_PIS_GPIO_PIN6           = 0x16U, /**< Pin6, level,support async */
    MD_PIS_GPIO_PIN7           = 0x17U, /**< Pin7, level,support async */
    MD_PIS_GPIO_PIN8           = 0x18U, /**< Pin8, level,support async */
    MD_PIS_GPIO_PIN9           = 0x19U, /**< Pin9, level,support async */
    MD_PIS_GPIO_PIN10          = 0x1aU, /**< Pin10, level,support async */
    MD_PIS_GPIO_PIN11          = 0x1bU, /**< Pin11, level,support async */
    MD_PIS_GPIO_PIN12          = 0x1cU, /**< Pin12, level,support async */
    MD_PIS_GPIO_PIN13          = 0x1dU, /**< Pin13, level,support async */
    MD_PIS_GPIO_PIN14          = 0x1eU, /**< Pin14, level,support async */
    MD_PIS_GPIO_PIN15          = 0x1fU, /**< Pin15, level,support async */
    MD_PIS_ADC0_NORMAL         = 0x60U, /**< Adc0 normal, pclk2 pulse,support async */
    MD_PIS_ADC0_INSERT         = 0x61U, /**< Adc0 insert, pclk2 pulse,support async */
    MD_PIS_LVD                 = 0x70U, /**< Lvd, level,support async */
    MD_PIS_UART0_IRDAOUT       = 0x82U, /**< Uart0 irdaout, level,support async */
    MD_PIS_UART0_RTSOUT        = 0x83U, /**< Uart0 rtsout, level,support async */
    MD_PIS_UART0_TXOUT         = 0x84U, /**< Uart0 txout, level,support async */
    MD_PIS_UART0_SYN_SEND      = 0x85U, /**< Uart0 syn send, pulse,support async */
    MD_PIS_UART0_SYN_RECV      = 0x86U, /**< Uart0 syn recv, pulse,support async */
    MD_PIS_UART1_IRDA          = 0x92U, /**< Uart1 irdaout, level,support async */
    MD_PIS_UART1_RTS           = 0x93U, /**< Uart1 rtsout, level,support async */
    MD_PIS_UART1_TXOUT         = 0x94U, /**< Uart1 txout, level,support async */
    MD_PIS_UART1_SYN_SEND      = 0x95U, /**< Uart1 syn send, pulse,support async */
    MD_PIS_UART1_SYN_RECV      = 0x96U, /**< Uart1 syn recv, pulse,support async */
    MD_PIS_UART2_IRDA          = 0xa2U, /**< Uart2 irdaout, level,support async */
    MD_PIS_UART2_RTS           = 0xa3U, /**< Uart2 rtsout, level,support async */
    MD_PIS_UART2_TXOUT         = 0xa4U, /**< Uart2 txout, level,support async */
    MD_PIS_UART2_SYN_SEND      = 0xa5U, /**< Uart2 syn send, pulse,support async */
    MD_PIS_UART2_SYN_RECV      = 0xa6U, /**< Uart2 syn recv, pulse,support async */
    MD_PIS_SPI0_RECV           = 0xe0U, /**< Spi0 recv, plck1 pulse */
    MD_PIS_SPI0_SEND           = 0xe1U, /**< Spi0 send, plck1 pulse */
    MD_PIS_SPI0_NE             = 0xe2U, /**< Spi0 ne, plck1 level */
    MD_PIS_SPI1_RECV           = 0xf0U, /**< Spi1 recv, plck1 pulse */
    MD_PIS_SPI1_SEND           = 0xf1U, /**< Spi1 send, plck1 pulse */
    MD_PIS_SPI1_NE             = 0xf2U, /**< Spi1 ne, plck1 level */
    MD_PIS_I2C0_RECV           = 0x100U,    /**< I2c0 recv, plck1 level */
    MD_PIS_I2C0_SEND           = 0x101U,    /**< I2c0 send, plck1 level */
    MD_PIS_I2C1_RECV           = 0x110U,    /**< I2c1 recv, plck1 level */
    MD_PIS_I2C1_SEND           = 0x111U,    /**< I2c1 send, plck1 level */
    MD_PIS_TIMER0_UPDATA       = 0x120U,    /**< Timer0 updata, plck1 pulse */
    MD_PIS_TIMER0_TRIG         = 0x121U,    /**< Timer0 trig, plck1 pulse */
    MD_PIS_TIMER0_INPUT_1      = 0x122U,    /**< Timer0 chan1 input catch, plck1 pulse */
    MD_PIS_TIMER0_OUTPUT_1     = 0x123U,    /**< Timer0 chan1 output compare, plck1 pulse */
    MD_PIS_TIMER0_INPUT_2      = 0x124U,    /**< Timer0 chan2 input catch, plck1 pulse */
    MD_PIS_TIMER0_OUTPUT_2     = 0x125U,    /**< Timer0 chan2 output compare, plck1 pulse */
    MD_PIS_TIMER0_INPUT_3      = 0x126U,    /**< Timer0 chan3 input catch, plck1 pulse */
    MD_PIS_TIMER0_OUTPUT_3     = 0x127U,    /**< Timer0 chan3 output compare, plck1 pulse */
    MD_PIS_TIMER0_INPUT_4      = 0x128U,    /**< Timer0 chan4 input catch, plck1 pulse */
    MD_PIS_TIMER0_OUTPUT_4     = 0x129U,    /**< Timer0 chan4 output compare, plck1 pulse */
    MD_PIS_TIMER1_UPDATA       = 0x130U,    /**< Timer1 updata, plck1 pulse */
    MD_PIS_TIMER1_TRIG         = 0x131U,    /**< Timer1 trig, plck1 pulse */
    MD_PIS_TIMER1_INPUT_1      = 0x132U,    /**< Timer1 chan1 input catch, plck1 pulse */
    MD_PIS_TIMER1_OUTPUT_1     = 0x133U,    /**< Timer1 chan1 output compare, plck1 pulse */
    MD_PIS_TIMER1_INPUT_2      = 0x134U,    /**< Timer1 chan2 input catch, plck1 pulse */
    MD_PIS_TIMER1_OUTPUT_2     = 0x135U,    /**< Timer1 chan2 output compare, plck1 pulse */
    MD_PIS_TIMER1_INPUT_3      = 0x136U,    /**< Timer1 chan3 input catch, plck1 pulse */
    MD_PIS_TIMER1_OUTPUT_3     = 0x137U,    /**< Timer1 chan3 output compare, plck1 pulse */
    MD_PIS_TIMER1_INPUT_4      = 0x138U,    /**< Timer1 chan4 input catch, plck1 pulse */
    MD_PIS_TIMER1_OUTPUT_4     = 0x139U,    /**< Timer1 chan4 output compare, plck1 pulse */
    MD_PIS_TIMER2_UPDATA       = 0x140U,    /**< Timer2 updata, plck1 pulse */
    MD_PIS_TIMER2_TRIG         = 0x141U,    /**< Timer2 trig, plck1 pulse */
    MD_PIS_TIMER2_INPUT_1      = 0x142U,    /**< Timer2 chan1 input catch, plck1 pulse */
    MD_PIS_TIMER2_OUTPUT_1     = 0x143U,    /**< Timer2 chan1 output compare, plck1 pulse */
    MD_PIS_TIMER2_INPUT_2      = 0x144U,    /**< Timer2 chan2 input catch, plck1 pulse */
    MD_PIS_TIMER2_OUTPUT_2     = 0x145U,    /**< Timer2 chan2 output compare, plck1 pulse */
    MD_PIS_TIMER2_INPUT_3      = 0x146U,    /**< Timer2 chan3 input catch, plck1 pulse */
    MD_PIS_TIMER2_OUTPUT_3     = 0x147U,    /**< Timer2 chan3 output compare, plck1 pulse */
    MD_PIS_TIMER2_INPUT_4      = 0x148U,    /**< Timer2 chan4 input catch, plck1 pulse */
    MD_PIS_TIMER2_OUTPUT_4     = 0x149U,    /**< Timer2 chan4 output compare, plck1 pulse */
    MD_PIS_TIMER3_UPDATA       = 0x150U,    /**< Timer3 updata, plck1 pulse */
    MD_PIS_TIMER3_TRIG         = 0x151U,    /**< Timer3 trig, plck1 pulse */
    MD_PIS_TIMER3_INPUT_1      = 0x152U,    /**< Timer3 chan1 input catch, plck1 pulse */
    MD_PIS_TIMER3_OUTPUT_1     = 0x153U,    /**< Timer3 chan1 output compare, plck1 pulse */
    MD_PIS_TIMER3_INPUT_2      = 0x154U,    /**< Timer3 chan2 input catch, plck1 pulse */
    MD_PIS_TIMER3_OUTPUT_2     = 0x155U,    /**< Timer3 chan2 output compare, plck1 pulse */
    MD_PIS_TIMER3_INPUT_3      = 0x156U,    /**< Timer3 chan3 input catch, plck1 pulse */
    MD_PIS_TIMER3_OUTPUT_3     = 0x157U,    /**< Timer3 chan3 output compare, plck1 pulse */
    MD_PIS_TIMER3_INPUT_4      = 0x158U,    /**< Timer3 chan4 input catch, plck1 pulse */
    MD_PIS_TIMER3_OUTPUT_4     = 0x159U,    /**< Timer3 chan4 output compare, plck1 pulse */
    MD_PIS_RTC_CLOCK           = 0x160U,    /**< Rtc clock, pulse,support async */
    MD_PIS_RTC_ALARM           = 0x161U,    /**< Rtc alarm, pulse,support async */
    MD_PIS_LP16T_SYN_UPDATA    = 0x170U,    /**< Lp16t syn updata, pulse,support async */
    MD_PIS_LP16T_ASY_UPDATA    = 0x171U,    /**< Lp16t asy updata, pulse,support async */
    MD_PIS_DMA                 = 0x190U,    /**< Dma, pulse,support async */
} md_pis_src_t;

/**
  * @brief Consumer entry
  */
typedef enum
{
    MD_PIS_CH15_DMA_CH15     = 0x00FFU, /* DMA CH15 */
    MD_PIS_CH15_TIM0_ITR3    = 0x00FFU, /* TIM0 ITR3 */
    MD_PIS_CH15_TIM1_ITR3    = 0x00FFU, /* TIM1 ITR3 */
    MD_PIS_CH15_TIM2_ITR3    = 0x00FFU, /* TIM2 ITR3 */
    MD_PIS_CH15_TIM3_ITR3    = 0x00FFU, /* TIM3 ITR3 */
    MD_PIS_CH14_DMA_CH14     = 0x00FEU, /* DMA CH14 */
    MD_PIS_CH14_TIM0_ITR2    = 0x00FEU, /* TIM0 ITR2 */
    MD_PIS_CH14_TIM1_ITR2    = 0x00FEU, /* TIM1 ITR2 */
    MD_PIS_CH14_TIM2_ITR2    = 0x00FEU, /* TIM2 ITR2 */
    MD_PIS_CH14_TIM3_ITR2    = 0x00FEU, /* TIM3 ITR2 */
    MD_PIS_CH13_DMA_CH13     = 0x00FDU, /* DMA CH13 */
    MD_PIS_CH13_TIM0_ITR1    = 0x00FDU, /* TIM0 ITR1 */
    MD_PIS_CH13_TIM1_ITR1    = 0x00FDU, /* TIM1 ITR1 */
    MD_PIS_CH13_TIM2_ITR1    = 0x00FDU, /* TIM2 ITR1 */
    MD_PIS_CH13_TIM3_ITR1    = 0x00FDU, /* TIM3 ITR1 */
    MD_PIS_CH12_DMA_CH12     = 0x00FCU, /* DMA CH12 */
    MD_PIS_CH12_TIM0_ITR0    = 0x00FCU, /* TIM0 ITR0 */
    MD_PIS_CH12_TIM1_ITR0    = 0x00FCU, /* TIM1 ITR0 */
    MD_PIS_CH12_TIM2_ITR0    = 0x00FCU, /* TIM2 ITR0 */
    MD_PIS_CH12_TIM3_ITR0    = 0x00FCU, /* TIM3 ITR0 */
    MD_PIS_CH11_UART2_RXD    = 0x021BU, /**< Uart2 Rx data */
    MD_PIS_CH11_DMA_CH11     = 0x00FBU, /* DMA CH11 */
    MD_PIS_CH10_UART1_RXD    = 0x011AU, /**< Uart1 Rx data */
    MD_PIS_CH10_DMA_CH10     = 0x00FAU, /* DMA CH10 */
    MD_PIS_CH9_UART0_RXD     = 0x0019U, /**< Uart0 Rx data  */
    MD_PIS_CH9_DMA_CH9       = 0x00F9U, /* DMA CH9 */
    MD_PIS_CH8_SPI1_CLK      = 0x0F18U, /**< Spi1 clk */
    MD_PIS_CH8_DMA_CH8       = 0x00F8U, /* DMA CH8 */
    MD_PIS_CH7_SPI1_RX       = 0x0E17U, /**< Spi1 rx */
    MD_PIS_CH7_LP16T_EXT_TRIG7 = 0x00F7U, /* LP16T EXT_TRIG7 */
    MD_PIS_CH7_DMA_CH7       = 0x00F7U, /* DMA CH7 */
    MD_PIS_CH7_ADC_ICHTRG    = 0x00F7U, /* ADC ICHTRG */
    MD_PIS_CH6_9_TIMER3_CMPIN0_3 = 0x1E06,  /**< Tim3 CMPIN0-3*/
    MD_PIS_CH6_9_TIMER2_CMPIN0_3 = 0x1606,  /**< Tim2 CMPIN0-3*/
    MD_PIS_CH6_9_TIMER1_CMPIN0_3 = 0x0E06,  /**< Tim1 CMPIN0-3*/
    MD_PIS_CH6_9_TIMER0_CMPIN0_3 = 0x0606,  /**< Tim0 CMPIN0-3*/
    MD_PIS_CH6_TIMER3_CH2IN  = 0x1906U, /**< Tim3 input chan2 */
    MD_PIS_CH6_TIMER2_CH2IN  = 0x1106U, /**< Tim2 input chan2 */
    MD_PIS_CH6_SPI0_CLK      = 0x0D16U, /**< SPI0 CLK */
    MD_PIS_CH6_LP16T_EXT_TRIG6 = 0x00F6U, /* LP16T EXT_TRIG6 */
    MD_PIS_CH6_DMA_CH6       = 0x00F6U, /* DMA CH6 */
    MD_PIS_CH6_ADC_NCHTRG    = 0x00F6U, /* ADC NCHTRG */
    MD_PIS_CH5_SPI0_RX       = 0x0C15U, /**< SPI0 RX */
    MD_PIS_CH5_LP16T_EXT_TRIG5 = 0x00F5U, /* LP16T EXT_TRIG5 */
    MD_PIS_CH5_DMA_CH5       = 0x00F5U, /* DMA CH5 */
    MD_PIS_CH4_TIMER3_CH4IN  = 0x1B04U, /**< Tim3 input chan4 */
    MD_PIS_CH4_TIMER2_CH4IN  = 0x1304U, /**< Tim2 input chan4 */
    MD_PIS_CH4_TIMER1_CH4IN  = 0x0B04U, /**< Tim1 input chan4 */
    MD_PIS_CH4_TIMER0_CH4IN  = 0x0304U, /**< Tim0 input chan4 */
    MD_PIS_CH4_LP16T_EXT_TRIG4 = 0x00F4U, /* LP16T EXT_TRIG4 */
    MD_PIS_CH4_DMA_CH4       = 0x00F4U, /* DMA CH4 */
    MD_PIS_CH3_TIMER3_CH3IN  = 0x1A03U, /**< Tim3 input chan3 */
    MD_PIS_CH3_TIMER2_CH3IN  = 0x1203U, /**< Tim2 input chan3 */
    MD_PIS_CH3_TIMER1_CH3IN  = 0x0A03U, /**< Tim1 input chan3 */
    MD_PIS_CH3_TIMER0_CH3IN  = 0x0203U, /**< Tim0 input chan3 */
    MD_PIS_CH3_LP16T_EXT_TRIG3 = 0x00F3U, /* LP16T EXT_TRIG3 */
    MD_PIS_CH3_DMA_CH3       = 0x00F3U, /* DMA CH3 */
    MD_PIS_CH2_TIMER3_CH2IN  = 0x1902U, /**< Tim3 input chan2 */
    MD_PIS_CH2_TIMER2_CH2IN  = 0x1102U, /**< Tim2 input chan2 */
    MD_PIS_CH2_TIMER1_CH2IN  = 0x0902U, /**< Tim1 input chan2 */
    MD_PIS_CH2_TIMER0_CH2IN  = 0x0102U, /**< Tim0 input chan2 */
    MD_PIS_CH2_LP16T_EXT_TRIG2 = 0x00F2U, /* LP16T EXT_TRIG2 */
    MD_PIS_CH2_DMA_CH2       = 0x00F2U, /* DMA CH2 */
    MD_PIS_CH1_TIMER3_CH1IN  = 0x1801U, /**< Tim3 input chan1 */
    MD_PIS_CH1_TIMER2_CH1IN  = 0x1001U, /**< Tim2 input chan1 */
    MD_PIS_CH1_TIMER1_CH1IN  = 0x0801U, /**< Tim1 input chan1 */
    MD_PIS_CH1_LP16T_EXT_TRIG1 = 0x00F1U, /* LP16T EXT_TRIG1 */
    MD_PIS_CH1_DMA_CH1       = 0x00F1U, /* DMA CH1 */
    MD_PIS_CH1_TIMER0_CH1IN  = 0x0001U, /**< Tim0 input chan1 */
    MD_PIS_CH0_TIMER0_BRKIN  = 0x0400U, /**< Tim0 break in */
    MD_PIS_CH0_TIMER2_BRKIN  = 0x1400U, /**< Tim2 break in */
    MD_PIS_CH0_TIMER3_BRKIN  = 0x1C00U, /**< Tim3 break in */
    MD_PIS_CH0_LP16T_EXT_TRIG0 = 0x00F0U, /* LP16T EXT_TRIG0 */
    MD_PIS_CH0_DMA_CH0       = 0x00F0U, /* DMA CH0 */
    MD_PIS_TRIG_RESERVE      = 0xFFFFU, /**< Other Consumer */
} md_pis_trig_t;

/**
  * @brief input source
  */
typedef enum
{
    MD_SRC_NONE    = 0U,    /**< None input source */
    MD_SRC_GPIO    = 1U,    /**< gpio source */
    MD_SRC_ADC0    = 6U,    /**< adc0 source */
    MD_SRC_LVD     = 7U,    /**< lvd source */
    MD_SRC_UART0   = 8U,    /**< uart0 source */
    MD_SRC_UART1   = 9U,    /**< uart1 source */
    MD_SRC_UART2   = 10U,   /**< uart2 source */
    MD_SRC_SPI0    = 14U,   /**< spi0 source */
    MD_SRC_SPI1    = 15U,   /**< spi1 source */
    MD_SRC_I2C0    = 16U,   /**< i2c0 source */
    MD_SRC_I2C1    = 17U,   /**< i2c1 source */
    MD_SRC_TIM0    = 18U,   /**< tim0 source */
    MD_SRC_TIM1    = 19U,   /**< tim1 source */
    MD_SRC_TIM2    = 20U,   /**< tim2 source */
    MD_SRC_TIM3    = 21U,   /**< tim3 source */
    MD_SRC_RTC     = 22U,   /**< rtc source */
    MD_SRC_LP16T   = 23U,   /**< lp16t source */
    MD_SRC_DMA     = 25U,   /**< dma source */
} md_pis_input_src_t;

/**
  * @brief Clock select
  */
typedef enum
{
    MD_PIS_CLK_PCLK1    = 0U,   /**< APB1 peripherals clock */
    MD_PIS_CLK_PCLK2    = 1U,   /**< APB2 peripherals clock */
    MD_PIS_CLK_SYS      = 2U,   /**< AHB peripherals clock */
    MD_PIS_CLK_RESERVE  = 3U,   /**< reserve clock */
} md_pis_clock_t;

/**
  * @brief Level select
  */
typedef enum
{
    MD_PIS_EDGE_NONE    = 0U,   /**< None edge */
    MD_PIS_EDGE_UP      = 1U,   /**< Up edge */
    MD_PIS_EDGE_DOWN    = 2U,   /**< Down edge */
    MD_PIS_EDGE_UP_DOWN = 3U,   /**< Up and down edge */
} md_pis_edge_t;

/**
  * @brief Output style
  */
typedef enum
{
    MD_PIS_OUT_LEVEL = 0U,  /**< Level */
    MD_PIS_OUT_PULSE = 1U,  /**< Pulse */
} md_pis_output_t;
/**
  * @brief Sync select
  */
typedef enum
{
    MD_PIS_SYN_DIRECT         = 0U, /**< Direct */
    MD_PIS_SYN_LEVEL_ASY_APB1 = 1U, /**< Producer level signal and Consumer in APB1 */
    MD_PIS_SYN_LEVEL_ASY_APB2 = 2U, /**< Producer level signal and Consumer in APB2 */
    MD_PIS_SYN_LEVEL_ASY_AHB  = 3U, /**< Producer level signal and Consumer in AHB */
    MD_PIS_SYN_PULSE_ASY_APB1 = 4U, /**< Producer Pulse signal and Consumer in APB1 */
    MD_PIS_SYN_PULSE_ASY_APB2 = 5U, /**< Producer Pulse signal and Consumer in APB2 */
    MD_PIS_SYN_PULSE_ASY_AHB  = 6U, /**< Producer Pulse signal and Consumer in AHB */
} md_pis_syncsel_t;

/**
  * @brief Pis channel
  */
typedef enum
{
    MD_PIS_CH_0 = 0U,   /**< Channel 0 */
    MD_PIS_CH_1 = 1U,   /**< Channel 1 */
    MD_PIS_CH_2 = 2U,   /**< Channel 2 */
    MD_PIS_CH_3 = 3U,   /**< Channel 3 */
    MD_PIS_CH_4 = 4U,   /**< Channel 4 */
    MD_PIS_CH_5 = 5U,   /**< Channel 5 */
    MD_PIS_CH_6 = 6U,   /**< Channel 6 */
    MD_PIS_CH_7 = 7U,   /**< Channel 7 */
    MD_PIS_CH_8 = 8U,   /**< Channel 8 */
    MD_PIS_CH_9 = 9U,   /**< Channel 9 */
    MD_PIS_CH_10 = 10U, /**< Channel 10 */
    MD_PIS_CH_11 = 11U, /**< Channel 11 */
    MD_PIS_CH_12 = 12U, /**< Channel 12 */
    MD_PIS_CH_13 = 13U, /**< Channel 13 */
    MD_PIS_CH_14 = 14U, /**< Channel 14 */
    MD_PIS_CH_15 = 15U, /**< Channel 15 */
} md_pis_ch_t;

/**
  * @brief PIS init structure definition
  */
typedef struct
{
    md_pis_src_t p_src;     /**< Producer entry */
    md_pis_output_t p_output;   /**< Producer signal mode */
    md_pis_clock_t p_clk;       /**< Producer module clock */
    md_pis_edge_t p_edge;       /**< Producer module pin output edge */
    md_pis_trig_t c_trig;       /**< Consumer entry */
    md_pis_clock_t c_clk;       /**< Consumer clock */
} md_pis_init_t;

/**
  * @brief PIS state structures definition
  */
typedef enum
{
    MD_PIS_STATE_RESET   = 0x00U,   /**< Peripheral is not initialized */
    MD_PIS_STATE_READY   = 0x01U,   /**< Peripheral Initialized and ready for use */
    MD_PIS_STATE_BUSY    = 0x02U,   /**< An internal process is ongoing */
    MD_PIS_STATE_TIMEOUT = 0x03U,   /**< Timeout state */
    MD_PIS_STATE_ERROR   = 0x04U,   /**< Error */
} md_pis_state_t;

/**
  * @brief PIS modulate target
  */
typedef enum
{
    MD_PIS_UART0_TX   = 0U, /**< Modulate uart0 tx */
    MD_PIS_UART1_TX   = 1U, /**< Modulate uart1 tx */
    MD_PIS_UART2_TX   = 2U, /**< Modulate uart2 tx */
} md_pis_modu_targ_t;

/**
  * @brief PIS modulate level
  */
typedef enum
{
    MD_PIS_LOW_LEVEL  = 0U, /**< Modulate low level */
    MD_PIS_HIGH_LEVEL = 1U, /**< Modulate high level */
} md_pis_modu_level_t;

/**
  * @brief PIS modulate source
  */
typedef enum
{
    MD_PIS_SRC_NONE     = 0U,   /**< Stop modulate */
    MD_PIS_SRC_TIMER0   = 1U,   /**< Modulate source is TIMER0 */
    MD_PIS_SRC_TIMER1   = 2U,   /**< Modulate source is TIMER1 */
    MD_PIS_SRC_TIMER2   = 3U,   /**< Modulate source is TIMER2 */
    MD_PIS_SRC_TIMER3   = 4U,   /**< Modulate source is TIMER3 */
    MD_PIS_SRC_LP16T    = 7U,   /**< Modulate source is LP16T */
    MD_PIS_SRC_BUZ      = 8U,   /**< Modulate source is buz */
} md_pis_modu_src_t;

/**
  * @brief PIS modulate channel
  */
typedef enum
{
    MD_PIS_TIMER_CH1 = 0U,  /**< Src is TIMERx and choose channel 1 */
    MD_PIS_TIMER_CH2 = 1U,  /**< Src is TIMERx and choose channel 2 */
    MD_PIS_TIMER_CH3 = 2U,  /**< Src is TIMERx and choose channel 3 */
    MD_PIS_TIMER_CH4 = 3U,  /**< Src is TIMERx and choose channel 4 */
} md_pis_modu_channel_t;
/**
  * @}
  */

/* Exported Functions -------------------------------------------------------- */

/** @defgroup MD_PIS_Public_Functions PIS Public Functions
  * @{
  */
/** @defgroup MD_PIS_Public_Functions_Group2 CH_CON
  * @{
  */
/**
  * @brief  Set pis signal synchronization type.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  signal PIS signal.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_signal_syn_type(PIS_TypeDef *PISx, md_pis_ch_t channel, md_pis_syncsel_t signal)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_SYNCSEL_MSK, signal << PIS_CH0_CON_SYNCSEL_POSS);
}

/**
  * @brief  Get pis signal synchronization type.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis channel signal synchronization type @ref md_pis_syncsel_t
  */
__STATIC_INLINE uint32_t md_pis_get_signal_syn_type(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_SYNCSEL_MSK, PIS_CH0_CON_SYNCSEL_POSS);
}

/**
  * @brief  Set pis edge sampling clock.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  clock PIS sample clock.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_edge_sample_clock(PIS_TypeDef *PISx, md_pis_ch_t channel, md_pis_clock_t clock)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_PULCK_MSK, clock << PIS_CH0_CON_PULCK_POSS);
}

/**
  * @brief  Get pis edge sampling clock.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis edge sampling clock @ref md_pis_clock_t
  */
__STATIC_INLINE uint32_t md_pis_get_edge_sample_clock(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_PULCK_MSK, PIS_CH0_CON_PULCK_POSS);
}

/**
  * @brief  Set pis sample edge.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  edge PIS sample edge.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_sample_edge(PIS_TypeDef *PISx, md_pis_ch_t channel, md_pis_edge_t edge)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_EDGS_MSK, edge << PIS_CH0_CON_EDGS_POSS);
}

/**
  * @brief  Get pis sample edge.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis edge sampling clock @ref md_pis_edge_t
  */
__STATIC_INLINE uint32_t md_pis_get_sample_edge(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_EDGS_MSK, PIS_CH0_CON_EDGS_POSS);
}

/**
  * @brief  Set pis input source.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  src PIS input source.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_input_src(PIS_TypeDef *PISx, md_pis_ch_t channel, md_pis_input_src_t src)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_SRCS_MSK, src << PIS_CH0_CON_SRCS_POSS);
}

/**
  * @brief  Get pis input source.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source @ref md_pis_input_src_t
  */
__STATIC_INLINE uint32_t md_pis_get_input_src(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_SRCS_MSK, PIS_CH0_CON_SRCS_POSS);
}

/**
  * @brief  Set pis input source gpiob.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  pin PIS input source gpiob.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_src_gpiob(PIS_TypeDef *PISx, md_pis_ch_t channel, uint8_t pin)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, pin << PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Get pis input source gpiob.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source gpiob.
  */
__STATIC_INLINE uint32_t md_pis_get_src_gpiob(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Set pis input source adc0.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  adc0 PIS input source adc0.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_src_adc0(PIS_TypeDef *PISx, md_pis_ch_t channel, uint32_t adc0)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, adc0 << PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Get pis input source adc0.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source adc0.
  */
__STATIC_INLINE uint32_t md_pis_get_src_adc0(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Set pis input source lvd.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  lvd PIS input source lvd.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_src_lvd(PIS_TypeDef *PISx, md_pis_ch_t channel, uint32_t lvd)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, lvd << PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Get pis input source lvd.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source lvd.
  */
__STATIC_INLINE uint32_t md_pis_get_src_lvd(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Set pis input source uart0.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  uart0 PIS input source uart0.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_src_uart0(PIS_TypeDef *PISx, md_pis_ch_t channel, uint32_t uart0)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, uart0 << PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Get pis input source uart0.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source uart0.
  */
__STATIC_INLINE uint32_t md_pis_get_src_uart0(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Set pis input source uart1.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  uart1 PIS input source uart1.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_src_uart1(PIS_TypeDef *PISx, md_pis_ch_t channel, uint32_t uart1)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, uart1 << PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Get pis input source uart1.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source uart1.
  */
__STATIC_INLINE uint32_t md_pis_get_src_uart1(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Set pis input source uart2.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  uart2 PIS input source uart2.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_src_uart2(PIS_TypeDef *PISx, md_pis_ch_t channel, uint32_t uart2)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, uart2 << PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Get pis input source uart2.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source uart2.
  */
__STATIC_INLINE uint32_t md_pis_get_src_uart2(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Set pis input source spi0.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  spi0 PIS input source spi0.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_src_spi0(PIS_TypeDef *PISx, md_pis_ch_t channel, uint32_t spi0)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, spi0 << PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Get pis input source spi0.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source spi0.
  */
__STATIC_INLINE uint32_t md_pis_get_src_spi0(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Set pis input source spi1.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  spi1 PIS input source spi1.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_src_spi1(PIS_TypeDef *PISx, md_pis_ch_t channel, uint32_t spi1)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, spi1 << PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Get pis input source spi1.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source spi1.
  */
__STATIC_INLINE uint32_t md_pis_get_src_spi1(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Set pis input source i2c0.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  i2c0 PIS input source i2c0.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_src_i2c0(PIS_TypeDef *PISx, md_pis_ch_t channel, uint32_t i2c0)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, i2c0 << PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Get pis input source i2c0.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source i2c0.
  */
__STATIC_INLINE uint32_t md_pis_get_src_i2c0(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Set pis input source i2c1.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  i2c1 PIS input source i2c1.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_src_i2c1(PIS_TypeDef *PISx, md_pis_ch_t channel, uint32_t i2c1)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, i2c1 << PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Get pis input source i2c1.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source i2c1
  */
__STATIC_INLINE uint32_t md_pis_get_src_i2c1(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Set pis input source tim0.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  tim0 PIS input source tim0.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_src_tim0(PIS_TypeDef *PISx, md_pis_ch_t channel, uint32_t tim0)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, tim0 << PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Get pis input source tim0.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source tim0
  */
__STATIC_INLINE uint32_t md_pis_get_src_tim0(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Set pis input source tim1.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  tim1 PIS input source tim1.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_src_tim1(PIS_TypeDef *PISx, md_pis_ch_t channel, uint32_t tim1)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, tim1 << PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Get pis input source tim1.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source tim1
  */
__STATIC_INLINE uint32_t md_pis_get_src_tim1(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Set pis input source tim2.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  tim2 PIS input source tim2.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_src_tim2(PIS_TypeDef *PISx, md_pis_ch_t channel, uint32_t tim2)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, tim2 << PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Get pis input source tim2.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source tim2
  */
__STATIC_INLINE uint32_t md_pis_get_src_tim2(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Set pis input source tim3.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  tim3 PIS input source tim3.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_src_tim3(PIS_TypeDef *PISx, md_pis_ch_t channel, uint32_t tim3)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, tim3 << PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Get pis input source tim3.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source tim3
  */
__STATIC_INLINE uint32_t md_pis_get_src_tim3(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Set pis input source rtc.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  rtc PIS input source rtc.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_src_rtc(PIS_TypeDef *PISx, md_pis_ch_t channel, uint32_t rtc)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, rtc << PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Get pis input source rtc.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source rtc
  */
__STATIC_INLINE uint32_t md_pis_get_src_rtc(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Set pis input source lp16t.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  lptim0 PIS input source lp16t.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_src_lp16t(PIS_TypeDef *PISx, md_pis_ch_t channel, uint32_t lp16t)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, lp16t << PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Get pis input source lp16t.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source lp16t
  */
__STATIC_INLINE uint32_t md_pis_get_src_lp16t(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Set pis input source dma.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  dma PIS input source dma.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_src_dma(PIS_TypeDef *PISx, md_pis_ch_t channel, uint32_t dma)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, dma << PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Get pis input source dma.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source dma.
  */
__STATIC_INLINE uint32_t md_pis_get_src_dma(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, PIS_CH0_CON_MSIGS_POSS);
}
/**
  * @}
  */
/** @defgroup MD_PIS_Public_Functions_Group3 CH_OER
  * @{
  */
/**
  * @brief  Disable pis channel 3 output to port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_ch3_output(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->CH_OER, PIS_CH_OER_CH3OE_MSK);
}

/**
  * @brief  Enable pis channel 3 output to port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_disable_ch3_output(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->CH_OER, PIS_CH_OER_CH3OE_MSK);
}

/**
  * @brief  Indicate if pis channel 3 output to port is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_ch3_output(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->CH_OER, PIS_CH_OER_CH3OE_MSK) == (PIS_CH_OER_CH3OE_MSK));
}

/**
  * @brief  Disable pis channel 2 output to port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_ch2_output(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->CH_OER, PIS_CH_OER_CH2OE_MSK);
}

/**
  * @brief  Enable pis channel 2 output to port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_disable_ch2_output(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->CH_OER, PIS_CH_OER_CH2OE_MSK);
}

/**
  * @brief  Indicate if pis channel 2 output to port is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_ch2_output(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->CH_OER, PIS_CH_OER_CH2OE_MSK) == (PIS_CH_OER_CH2OE_MSK));
}

/**
  * @brief  Disable pis channel 1 output to port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_ch1_output(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->CH_OER, PIS_CH_OER_CH1OE_MSK);
}

/**
  * @brief  Enable pis channel 1 output to port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_disable_ch1_output(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->CH_OER, PIS_CH_OER_CH1OE_MSK);
}

/**
  * @brief  Indicate if pis channel 1 output to port is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_ch1_output(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->CH_OER, PIS_CH_OER_CH1OE_MSK) == (PIS_CH_OER_CH1OE_MSK));
}

/**
  * @brief  Disable pis channel 0 output to port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_ch0_output(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->CH_OER, PIS_CH_OER_CH0OE_MSK);
}

/**
  * @brief  Enable pis channel 0 output to port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_disable_ch0_output(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->CH_OER, PIS_CH_OER_CH0OE_MSK);
}

/**
  * @brief  Indicate if pis channel 0 output to port is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_ch0_output(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->CH_OER, PIS_CH_OER_CH0OE_MSK) == (PIS_CH_OER_CH0OE_MSK));
}
/**
  * @}
  */
/** @defgroup MD_PIS_Public_Functions_Group4 TAR_CON0
  * @{
  */
/**
  * @brief  Set pis tim3 input capture ch4 chose ch4.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim3_ch4in_ch4(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM3_CH4IN_SEL_MSK);
}

/**
  * @brief  Set pis tim3 input capture ch4 chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim3_ch4in_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM3_CH4IN_SEL_MSK);
}

/**
  * @brief  Indicate if pis tim3 input capture ch4 chose ch4 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_tim3_ch4in_ch4(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM3_CH4IN_SEL_MSK) == (PIS_TAR_CON0_TIM3_CH4IN_SEL_MSK));
}

/**
  * @brief  Set pis tim3 input capture ch3 chose ch3.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim3_ch3in_ch3(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM3_CH3IN_SEL_MSK);
}

/**
  * @brief  Set pis tim3 input capture ch3 chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim3_ch3in_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM3_CH3IN_SEL_MSK);
}

/**
  * @brief  Indicate if pis tim3 input capture ch3 chose ch3 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_tim3_ch3in_ch3(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM3_CH3IN_SEL_MSK) == (PIS_TAR_CON0_TIM3_CH3IN_SEL_MSK));
}

/**
  * @brief  Set pis tim3 input capture ch2 chose ch2.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim3_ch2in_ch2(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM3_CH2IN_SEL_MSK);
}

/**
  * @brief  Set pis tim3 input capture ch2 chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim3_ch2in_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM3_CH2IN_SEL_MSK);
}

/**
  * @brief  Indicate if pis tim3 input capture ch2 chose ch6 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_tim3_ch2in_ch2(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM3_CH2IN_SEL_MSK) == (PIS_TAR_CON0_TIM3_CH2IN_SEL_MSK));
}

/**
  * @brief  Set pis tim3 input capture ch1 chose ch1.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim3_ch1in_ch1(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM3_CH1IN_SEL_MSK);
}

/**
  * @brief  Set pis tim3 input capture ch1 chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim3_ch1in_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM3_CH1IN_SEL_MSK);
}

/**
  * @brief  Indicate if pis tim3 input capture ch1 chose ch1 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_tim3_ch1in_ch1(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM3_CH1IN_SEL_MSK) == (PIS_TAR_CON0_TIM3_CH1IN_SEL_MSK));
}

/**
  * @brief  Set pis tim2 input capture ch4 chose ch4.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim2_ch4in_ch4(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM2_CH4IN_SEL_MSK);
}

/**
  * @brief  Set pis tim2 input capture ch4 chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim2_ch4in_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM2_CH4IN_SEL_MSK);
}

/**
  * @brief  Indicate if pis tim2 input capture ch4 chose ch4 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_tim2_ch4in_ch4(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM2_CH4IN_SEL_MSK) == (PIS_TAR_CON0_TIM2_CH4IN_SEL_MSK));
}

/**
  * @brief  Set pis tim2 input capture ch3 chose ch3.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim2_ch3in_ch3(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM2_CH3IN_SEL_MSK);
}

/**
  * @brief  Set pis tim2 input capture ch3 chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim2_ch3in_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM2_CH3IN_SEL_MSK);
}

/**
  * @brief  Indicate if pis tim2 input capture ch3 chose ch3 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_tim2_ch3in_ch3(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM2_CH3IN_SEL_MSK) == (PIS_TAR_CON0_TIM2_CH3IN_SEL_MSK));
}

/**
  * @brief  Set pis tim2 input capture ch2 chose ch2.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim2_ch2in_ch2(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM2_CH2IN_SEL_MSK);
}

/**
  * @brief  Set pis tim2 input capture ch2 chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim2_ch2in_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM2_CH2IN_SEL_MSK);
}

/**
  * @brief  Indicate if pis tim2 input capture ch2 chose ch2 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_tim2_ch2in_ch2(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM2_CH2IN_SEL_MSK) == (PIS_TAR_CON0_TIM2_CH2IN_SEL_MSK));
}

/**
  * @brief  Set pis tim2 input capture ch1 chose ch1.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim2_ch1in_ch1(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM2_CH1IN_SEL_MSK);
}

/**
  * @brief  Set pis tim2 input capture ch1 chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim2_ch1in_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM2_CH1IN_SEL_MSK);
}

/**
  * @brief  Indicate if pis tim2 input capture ch1 chose ch1 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_tim2_ch1in_ch1(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM2_CH1IN_SEL_MSK) == (PIS_TAR_CON0_TIM2_CH1IN_SEL_MSK));
}

/**
  * @brief  Set pis tim1 input capture ch4 chose ch4.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim1_ch4in_ch4(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM1_CH4IN_SEL_MSK);
}

/**
  * @brief  Set pis tim1 input capture ch4 chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim1_ch4in_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM1_CH4IN_SEL_MSK);
}

/**
  * @brief  Indicate if pis tim1 input capture ch4 chose ch4 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_tim1_ch4in_ch4(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM1_CH4IN_SEL_MSK) == (PIS_TAR_CON0_TIM1_CH4IN_SEL_MSK));
}

/**
  * @brief  Set pis tim1 input capture ch3 chose ch3.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim1_ch3in_ch3(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM1_CH3IN_SEL_MSK);
}

/**
  * @brief  Set pis tim1 input capture ch3 chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim1_ch3in_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM1_CH3IN_SEL_MSK);
}

/**
  * @brief  Indicate if pis tim1 input capture ch3 chose ch3 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_tim1_ch3in_ch3(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM1_CH3IN_SEL_MSK) == (PIS_TAR_CON0_TIM1_CH3IN_SEL_MSK));
}

/**
  * @brief  Set pis tim1 input capture ch2 chose ch2.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim1_ch2in_ch2(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM1_CH2IN_SEL_MSK);
}

/**
  * @brief  Set pis tim1 input capture ch2 chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim1_ch2in_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM1_CH2IN_SEL_MSK);
}

/**
  * @brief  Indicate if pis tim1 input capture ch2 chose ch2 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_tim1_ch2in_ch2(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM1_CH2IN_SEL_MSK) == (PIS_TAR_CON0_TIM1_CH2IN_SEL_MSK));
}

/**
  * @brief  Set pis tim1 input capture ch1 chose ch1.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim1_ch1in_ch1(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM1_CH1IN_SEL_MSK);
}

/**
  * @brief  Set pis tim1 input capture ch1 chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim1_ch1in_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM1_CH1IN_SEL_MSK);
}

/**
  * @brief  Indicate if pis tim1 input capture ch1 chose ch1 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_tim1_ch1in_ch1(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM1_CH1IN_SEL_MSK) == (PIS_TAR_CON0_TIM1_CH1IN_SEL_MSK));
}

/**
  * @brief  Set pis tim0 input capture ch4 chose ch4.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim0_ch4in_ch4(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM0_CH4IN_SEL_MSK);
}

/**
  * @brief  Set pis tim0 input capture ch4 chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim0_ch4in_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM0_CH4IN_SEL_MSK);
}

/**
  * @brief  Indicate if pis tim0 input capture ch4 chose ch4 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_tim0_ch4in_ch4(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM0_CH4IN_SEL_MSK) == (PIS_TAR_CON0_TIM0_CH4IN_SEL_MSK));
}

/**
  * @brief  Set pis tim0 input capture ch3 chose ch3.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim0_ch3in_ch3(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM0_CH3IN_SEL_MSK);
}

/**
  * @brief  Set pis tim0 input capture ch3 chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim0_ch3in_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM0_CH3IN_SEL_MSK);
}

/**
  * @brief  Indicate if pis tim0 input capture ch3 chose ch3 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_tim0_ch3in_ch3(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM0_CH3IN_SEL_MSK) == (PIS_TAR_CON0_TIM0_CH3IN_SEL_MSK));
}

/**
  * @brief  Set pis tim0 input capture ch2 chose ch2.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim0_ch2in_ch2(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM0_CH2IN_SEL_MSK);
}

/**
  * @brief  Set pis tim0 input capture ch2 chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim0_ch2in_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM0_CH2IN_SEL_MSK);
}

/**
  * @brief  Indicate if pis tim0 input capture ch2 chose ch2 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_tim0_ch2in_ch2(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM0_CH2IN_SEL_MSK) == (PIS_TAR_CON0_TIM0_CH2IN_SEL_MSK));
}

/**
  * @brief  Set pis tim0 input capture ch1 chose ch1.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim0_ch1in_ch1(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM0_CH1IN_SEL_MSK);
}

/**
  * @brief  Set pis tim0 input capture ch1 chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim0_ch1in_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM0_CH1IN_SEL_MSK);
}

/**
  * @brief  Indicate if pis tim0 input capture ch1 chose ch1 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_tim0_ch1in_ch1(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON0, PIS_TAR_CON0_TIM0_CH1IN_SEL_MSK) == (PIS_TAR_CON0_TIM0_CH1IN_SEL_MSK));
}
/**
  * @}
  */
/** @defgroup MD_PIS_Public_Functions_Group5 TAR_CON1
  * @{
  */
/**
  * @brief  Set pis spi1 clk input chose ch8.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_spi1_clk_ch8(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON1, PIS_TAR_CON1_SPI1_CLK_SEL_MSK);
}

/**
  * @brief  Set pis spi1 clk input chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_spi1_clk_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON1, PIS_TAR_CON1_SPI1_CLK_SEL_MSK);
}

/**
  * @brief  Indicate if pis spi1 clk input chose ch8 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_spi1_clk_ch8(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON1, PIS_TAR_CON1_SPI1_CLK_SEL_MSK) == (PIS_TAR_CON1_SPI1_CLK_SEL_MSK));
}

/**
  * @brief  Set pis spi1 rx input chose ch7.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_spi1_rx_ch7(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON1, PIS_TAR_CON1_SPI1_RX_SEL_MSK);
}

/**
  * @brief  Set pis spi1 rx input chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_spi1_rx_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON1, PIS_TAR_CON1_SPI1_RX_SEL_MSK);
}

/**
  * @brief  Indicate if pis spi1 rx input chose ch7 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_spi1_rx_ch7(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON1, PIS_TAR_CON1_SPI1_RX_SEL_MSK) == (PIS_TAR_CON1_SPI1_RX_SEL_MSK));
}

/**
  * @brief  Set pis spi0 clk input chose ch6.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_spi0_clk_ch6(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON1, PIS_TAR_CON1_SPI0_CLK_SEL_MSK);
}

/**
  * @brief  Set pis spi0 clk input chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_spi0_clk_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON1, PIS_TAR_CON1_SPI0_CLK_SEL_MSK);
}

/**
  * @brief  Indicate if pis spi0 clk input chose ch6 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_spi0_clk_ch6(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON1, PIS_TAR_CON1_SPI0_CLK_SEL_MSK) == (PIS_TAR_CON1_SPI0_CLK_SEL_MSK));
}

/**
  * @brief  Set pis spi0 rx input chose ch5.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_spi0_rx_ch5(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON1, PIS_TAR_CON1_SPI0_RX_SEL_MSK);
}

/**
  * @brief  Set pis spi0 rx input chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_spi0_rx_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON1, PIS_TAR_CON1_SPI0_RX_SEL_MSK);
}

/**
  * @brief  Indicate if pis spi0 rx input chose ch5 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_spi0_rx_ch5(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON1, PIS_TAR_CON1_SPI0_RX_SEL_MSK) == (PIS_TAR_CON1_SPI0_RX_SEL_MSK));
}

/**
  * @brief  Set pis uart2 rx input chose ch11.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_uart2_rx_ch11(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON1, PIS_TAR_CON1_UART2_RXD_SEL_MSK);
}

/**
  * @brief  Set pis uart2 rx input chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_uart2_rx_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON1, PIS_TAR_CON1_UART2_RXD_SEL_MSK);
}

/**
  * @brief  Indicate if pis uart2 rx input chose ch11 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_uart2_rx_ch11(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON1, PIS_TAR_CON1_UART2_RXD_SEL_MSK) == (PIS_TAR_CON1_UART2_RXD_SEL_MSK));
}

/**
  * @brief  Set pis uart1 rx input chose ch10.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_uart1_rx_ch10(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON1, PIS_TAR_CON1_UART1_RXD_SEL_MSK);
}

/**
  * @brief  Set pis uart1 rx input chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_uart1_rx_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON1, PIS_TAR_CON1_UART1_RXD_SEL_MSK);
}

/**
  * @brief  Indicate if pis uart1 rx input chose ch10 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_uart1_rx_ch10(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON1, PIS_TAR_CON1_UART1_RXD_SEL_MSK) == (PIS_TAR_CON1_UART1_RXD_SEL_MSK));
}

/**
  * @brief  Set pis uart0 rx input chose ch9.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_uart0_rx_ch9(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON1, PIS_TAR_CON1_UART0_RXD_SEL_MSK);
}

/**
  * @brief  Set pis uart0 rx input chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_uart0_rx_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON1, PIS_TAR_CON1_UART0_RXD_SEL_MSK);
}

/**
  * @brief  Indicate if pis uart0 rx input chose ch10 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_uart0_rx_ch9(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON1, PIS_TAR_CON1_UART0_RXD_SEL_MSK) == (PIS_TAR_CON1_UART0_RXD_SEL_MSK));
}
/**
  * @}
  */
/** @defgroup MD_PIS_Public_Functions_Group6 UART0_TXMCR
  * @{
  */
/**
  * @brief  Set pis uart0 tx modulation level high.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_uart0_tx_mod_high(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->UART0_TXMCR, PIS_UART0_TXMCR_TXMLVLS_MSK);
}

/**
  * @brief  Set pis uart0 tx modulation level low.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_uart0_tx_mod_low(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->UART0_TXMCR, PIS_UART0_TXMCR_TXMLVLS_MSK);
}

/**
  * @brief  Indicate if pis uart0 tx modulation level high is set
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_set_uart0_tx_mod_high(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->UART0_TXMCR, PIS_UART0_TXMCR_TXMLVLS_MSK) == (PIS_UART0_TXMCR_TXMLVLS_MSK));
}

/**
  * @brief  Set pis uart0 modulation source.
  * @param  PISx PIS Instance.
  * @param  src PIS uart0 modulation source.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_uart0_mod_src(PIS_TypeDef *PISx, md_pis_modu_src_t src)
{
    MODIFY_REG(PISx->UART0_TXMCR, PIS_UART0_TXMCR_TXMSS_MSK, src << PIS_UART0_TXMCR_TXMSS_POSS);
}

/**
  * @brief  Get pis uart0 modulation source.
  * @param  PISx PIS Instance.
  * @retval uart0 modulation source @ref md_pis_modu_src_t
  */
__STATIC_INLINE uint32_t md_pis_get_uart0_mod_src(PIS_TypeDef *PISx)
{
    return READ_BITS(PISx->UART0_TXMCR, PIS_UART0_TXMCR_TXMSS_MSK, PIS_UART0_TXMCR_TXMSS_POSS);
}

/**
  * @brief  Set pis uart0 modulation timx channel.
  * @param  PISx PIS Instance.
  * @param  channel PIS timx modulation channel.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_uart0_mod_tim_channel(PIS_TypeDef *PISx, md_pis_modu_channel_t channel)
{
    MODIFY_REG(PISx->UART0_TXMCR, PIS_UART0_TXMCR_TXSIGS_MSK, channel << PIS_UART0_TXMCR_TXSIGS_POSS);
}

/**
  * @brief  Get pis uart0 timx modulation channel.
  * @param  PISx PIS Instance.
  * @retval uart0 timx modulation channel @ref md_pis_modu_channel_t
  */
__STATIC_INLINE uint32_t md_pis_get_uart0_mod_tim_channel(PIS_TypeDef *PISx)
{
    return READ_BITS(PISx->UART0_TXMCR, PIS_UART0_TXMCR_TXSIGS_MSK, PIS_UART0_TXMCR_TXSIGS_POSS);
}
/**
  * @}
  */
/** @defgroup MD_PIS_Public_Functions_Group7 UART1_TXMCR
  * @{
  */
/**
  * @brief  Set pis uart1 tx modulation level high.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_uart1_tx_mod_high(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->UART1_TXMCR, PIS_UART1_TXMCR_TXMLVLS_MSK);
}

/**
  * @brief  Set pis uart1 tx modulation level low.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_uart1_tx_mod_low(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->UART1_TXMCR, PIS_UART1_TXMCR_TXMLVLS_MSK);
}

/**
  * @brief  Indicate if pis uart1 tx modulation level high is set
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_set_uart1_tx_mod_high(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->UART1_TXMCR, PIS_UART1_TXMCR_TXMLVLS_MSK) == (PIS_UART1_TXMCR_TXMLVLS_MSK));
}

/**
  * @brief  Set pis uart1 modulation source.
  * @param  PISx PIS Instance.
  * @param  src PIS uart1 modulation source.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_uart1_mod_src(PIS_TypeDef *PISx, md_pis_modu_src_t src)
{
    MODIFY_REG(PISx->UART1_TXMCR, PIS_UART1_TXMCR_TXMSS_MSK, src << PIS_UART1_TXMCR_TXMSS_POSS);
}

/**
  * @brief  Get pis uart1 modulation source.
  * @param  PISx PIS Instance.
  * @retval uart1 modulation source @ref md_pis_modu_src_t
  */
__STATIC_INLINE uint32_t md_pis_get_uart1_mod_src(PIS_TypeDef *PISx)
{
    return READ_BITS(PISx->UART1_TXMCR, PIS_UART1_TXMCR_TXMSS_MSK, PIS_UART1_TXMCR_TXMSS_POSS);
}

/**
  * @brief  Set pis uart1 modulation timx channel.
  * @param  PISx PIS Instance.
  * @param  channel PIS timx modulation channel.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_uart1_mod_tim_channel(PIS_TypeDef *PISx, md_pis_modu_channel_t channel)
{
    MODIFY_REG(PISx->UART1_TXMCR, PIS_UART1_TXMCR_TXSIGS_MSK, channel << PIS_UART1_TXMCR_TXSIGS_POSS);
}

/**
  * @brief  Get pis uart1 timx modulation channel.
  * @param  PISx PIS Instance.
  * @retval uart1 timx modulation channel @ref md_pis_modu_channel_t
  */
__STATIC_INLINE uint32_t md_pis_get_uart1_mod_tim_channel(PIS_TypeDef *PISx)
{
    return READ_BITS(PISx->UART1_TXMCR, PIS_UART1_TXMCR_TXSIGS_MSK, PIS_UART1_TXMCR_TXSIGS_POSS);
}
/**
  * @}
  */
/** @defgroup MD_PIS_Public_Functions_Group8 UART2_TXMCR
  * @{
  */
/**
  * @brief  Set pis uart2 tx modulation level high.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_uart2_tx_mod_high(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->UART2_TXMCR, PIS_UART2_TXMCR_TXMLVLS_MSK);
}

/**
  * @brief  Set pis uart2 tx modulation level low.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_uart2_tx_mod_low(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->UART2_TXMCR, PIS_UART2_TXMCR_TXMLVLS_MSK);
}

/**
  * @brief  Indicate if pis uart2 tx modulation level high is set
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_set_uart2_tx_mod_high(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->UART2_TXMCR, PIS_UART2_TXMCR_TXMLVLS_MSK) == (PIS_UART2_TXMCR_TXMLVLS_MSK));
}

/**
  * @brief  Set pis uart2 modulation source.
  * @param  PISx PIS Instance.
  * @param  src PIS uart2 modulation source.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_uart2_mod_src(PIS_TypeDef *PISx, md_pis_modu_src_t src)
{
    MODIFY_REG(PISx->UART2_TXMCR, PIS_UART2_TXMCR_TXMSS_MSK, src << PIS_UART2_TXMCR_TXMSS_POSS);
}

/**
  * @brief  Get pis uart2 modulation source.
  * @param  PISx PIS Instance.
  * @retval uart2 modulation source @ref md_pis_modu_src_t
  */
__STATIC_INLINE uint32_t md_pis_get_uart2_mod_src(PIS_TypeDef *PISx)
{
    return READ_BITS(PISx->UART2_TXMCR, PIS_UART2_TXMCR_TXMSS_MSK, PIS_UART2_TXMCR_TXMSS_POSS);
}

/**
  * @brief  Set pis uart2 modulation timx channel.
  * @param  PISx PIS Instance.
  * @param  channel PIS timx modulation channel.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_uart2_mod_tim_channel(PIS_TypeDef *PISx, md_pis_modu_channel_t channel)
{
    MODIFY_REG(PISx->UART2_TXMCR, PIS_UART2_TXMCR_TXSIGS_MSK, channel << PIS_UART2_TXMCR_TXSIGS_POSS);
}

/**
  * @brief  Get pis uart2 timx modulation channel.
  * @param  PISx PIS Instance.
  * @retval uart2 timx modulation channel @ref md_pis_modu_channel_t
  */
__STATIC_INLINE uint32_t md_pis_get_uart2_mod_tim_channel(PIS_TypeDef *PISx)
{
    return READ_BITS(PISx->UART2_TXMCR, PIS_UART2_TXMCR_TXSIGS_MSK, PIS_UART2_TXMCR_TXSIGS_POSS);
}
/**
  * @}
  */

/** @defgroup MD_PIS_Public_Functions_Group1 Initialization
  * @{
  */
extern void md_pis_reset(void);
extern md_status_t md_pis_init(md_pis_init_t *init);
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

#endif /* __MD_PIS_H__ */

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
