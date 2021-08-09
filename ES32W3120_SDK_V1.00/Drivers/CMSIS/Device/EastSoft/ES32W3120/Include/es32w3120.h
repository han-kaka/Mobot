/**
  **************************************************************************************
  * @file    ES32W3120.h
  * @brief   ES32W3120 Device Head File
  * @data    27 Jun 2019
  * @author  Eastsoft AE Team
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *
  **************************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup ES32W3120
  * @{
  */

#ifndef __ES32W3120_H__
#define __ES32W3120_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Configuration_section_for_CMSIS
  * @{
  */

/**
  * @brief configuration of the cortex-M3 processor and core peripherals.
  */
#define __CM3_REV                 0x0201U       /* Core Revision r2p1 */
#define __NVIC_PRIO_BITS          4U            /* ES32W3120 uses 4 Bits for the Priority Levels */
#define __Vendor_SysTickConfig    0             /* Set to 0 if different SysTick Config is used */
/**
  * @} Configuration_section_for_CMSIS
  */

/** @addtogroup peripherals_interrupt_number_definition
  * @{
  */

typedef enum IRQn
{
    /****** ES32 Processor Exceptions Numbers ******************************************************/

    NMI_IRQn                    = -14,
    HardFault_IRQn              = -13,
    MemManage_IRQn              = -12,
    BusFault_IRQn               = -11,
    UsageFault_IRQn             = -10,
    SVCall_IRQn                 = -5,
    DebugMonitor_IRQn           = -4,
    PendSV_IRQn                 = -2,
    SysTick_IRQn                = -1,
    WWDG_IRQn                   = 0,
    IWDG_IRQn                   = 1,
    LVD_IRQn                    = 2,
    RTC_WAKE_IRQn               = 3,
    RTC_ALARM_IRQn              = 4,
    CMU_IRQn                    = 6,
    ADC_IRQn                    = 7,
    LP16T_IRQn                  = 8,
    BS16T0_IRQn                 = 10,
    BS16T1_IRQn                 = 11,
    GP16C4T0_IRQn               = 12,
    GP16C4T1_IRQn               = 16,
    AD16C4T0_BRK_IRQn           = 20,
    AD16C4T0_UP_IRQn            = 21,
    AD16C4T0_TRIG_COM_IRQn      = 22,
    AD16C4T0_CC_IRQn            = 23,
    AD16C4T1_BRK_IRQn           = 24,
    AD16C4T1_UP_IRQn            = 25,
    AD16C4T1_TRIG_COM_IRQn      = 26,
    AD16C4T1_CC_IRQn            = 27,
    I2C0_EV_IRQn                = 28,
    I2C0_ERR_IRQn               = 29,
    I2C1_EV_IRQn                = 30,
    I2C1_ERR_IRQn               = 31,
    SPI0_IRQn                   = 32,
    SPI1_IRQn                   = 33,
    UART0_IRQn                  = 34,
    UART1_IRQn                  = 35,
    UART2_IRQn                  = 36,
    PDM2PCM_IRQn                = 38,
    TK_IRQn                     = 39,
    KSCAN_IRQn                  = 40,
    QSPI_IRQn                   = 41,
    CRYPT_IRQn                  = 42,
    ADPCM_IRQn                  = 43,
    HASH_IRQn                   = 45,
    ECC_IRQn                    = 47,
    TRNG_IRQn                   = 48,
    EXTI0_IRQn                  = 50,
    EXTI1_IRQn                  = 51,
    EXTI2_IRQn                  = 52,
    EXTI3_IRQn                  = 53,
    EXTI4_IRQn                  = 54,
    EXTI5_IRQn                  = 55,
    EXTI6_IRQn                  = 56,
    EXTI7_IRQn                  = 57,
    EXTI8_IRQn                  = 58,
    EXTI9_IRQn                  = 59,
    EXTI10_IRQn                 = 60,
    EXTI11_IRQn                 = 61,
    EXTI12_IRQn                 = 62,
    EXTI13_IRQn                 = 63,
    EXTI14_IRQn                 = 64,
    EXTI15_IRQn                 = 65,
    DMA_IRQn                    = 66,
    BLE_ERROR_IRQn              = 80,
    BLE_HSLOT_IRQn              = 81,
    BLE_RX_IRQn                 = 82,
    BLE_TX_IRQn                 = 83,
    BLE_START_IRQn              = 84,
    BLE_END_IRQn                = 85,
    BLE_SKIP_IRQn               = 86,
    BLE_SLP_IRQn                = 87,
    BLE_CRYPT_IRQn              = 88,
    BLE_GROSSTGTIM_IRQn         = 89,
    BLE_FINETGTIM_IRQn          = 90,
    BLE_TIMESTAMP_TGT_IRQn      = 91,
    BLE_SW_IRQn                 = 92,
    BLE_AUDIO0_IRQn             = 93,
    BLE_AUDIO1_IRQn             = 94,
    BLE_AUDIO2_IRQn             = 95,
} IRQn_Type;

/**
  * @} peripherals_interrupt_number_definition
  */

/* Includes-------------------------------------------------------------------------------*/

#include "core_cm3.h"
#if defined(__CC_ARM)
#pragma anon_unions
#endif

/**
  * @brief these files declare Peripheral register bit_definition.
  */

#include "reg_calc.h"
#include "reg_cmu.h"
#include "reg_crc.h"
#include "reg_dma.h"
#include "reg_gpio.h"
#include "reg_iwdt.h"
#include "reg_pis.h"
#include "reg_pmu.h"
#include "reg_rmu.h"
#include "reg_syscfg.h"
#include "reg_wwdt.h"
#include "reg_msc.h"
#include "reg_bkfc.h"
#include "reg_rtc.h"
#include "reg_spi.h"
#include "reg_qspi.h"
#include "reg_lptim.h"
#include "reg_uart.h"
#include "reg_timer.h"
#include "reg_adc.h"
#include "reg_i2c.h"
#include "reg_crypt.h"
#include "reg_ecc.h"
#include "reg_hash.h"
#include "reg_trng.h"

/******************************************************************************/
/*                              Peripheral register                           */
/******************************************************************************/

/*   allow anonymous structures and anonymous enumeration    */


/******************************************************************************/
/*                            Peripheral memory map                           */
/******************************************************************************/

/*********************      Base addresses        *************************/
#define FLASH_BASE            (0x00000000UL)
#define SRAM_BASE             (0x20000000UL)
#define QSPI_MEMORY_BASE      (0x14000000UL)
#define APB1_BASE             (0x40000000UL)
#define APB2_BASE             (0x40040000UL)
#define AHB1_BASE             (0x40080000UL)
#define AHB2_BASE             (0x400C0000UL)

/*****************     peripherals base addresses      ********************/
/* APB1 */
#define GP16C4T0_BASE     (APB1_BASE + 0x00000)
#define GP16C4T1_BASE     (APB1_BASE + 0x00400)
#define AD16C4T0_BASE     (APB1_BASE + 0x00800)
#define AD16C4T1_BASE     (APB1_BASE + 0x00C00)
#define BS16T0_BASE       (APB1_BASE + 0x01000)
#define BS16T1_BASE       (APB1_BASE + 0x01400)
#define UART0_BASE        (APB1_BASE + 0x04000)
#define UART1_BASE        (APB1_BASE + 0x04400)
#define UART2_BASE        (APB1_BASE + 0x04800)
#define SPI0_BASE         (APB1_BASE + 0x06000)
#define SPI1_BASE         (APB1_BASE + 0x06400)
#define I2C0_BASE         (APB1_BASE + 0x08000)
#define I2C1_BASE         (APB1_BASE + 0x08400)
#define ADPCM_BASE        (APB1_BASE + 0x08800)
#define TK_BASE           (APB1_BASE + 0x08C00)
#define ECC_BASE          (APB1_BASE + 0x09800)
#define PDM2PCM_BASE      (APB1_BASE + 0x09000)
#define DMA0_BASE         (APB1_BASE + 0x0C000)
#define QSPI_BASE         (APB1_BASE + 0x0E000)
#define KSCAN_BASE        (APB1_BASE + 0x0F000)
#define QDEC_BASE         (APB1_BASE + 0x0F400)
/* APB2 */
#define LP16T_BASE        (APB2_BASE + 0x00000)
#define ADC_BASE          (APB2_BASE + 0x02000)
#define WWDT_BASE         (APB2_BASE + 0x06000)
#define IWDT_BASE         (APB2_BASE + 0x08000)
#define RTC_BASE          (APB2_BASE + 0x08400)
#define BKP1_BASE         (APB2_BASE + 0x08C00)
#define BKPC_BASE         (APB2_BASE + 0x09000)
#define BKPRAM_BASE       (APB2_BASE + 0x09400)
#define BKP2_BASE         (APB2_BASE + 0x09800)
#define BKP3_BASE         (APB2_BASE + 0x09C00)
/* AHB1 */
#define SYSCFG_BASE       (AHB1_BASE + 0x00000)
#define CMU_BASE          (AHB1_BASE + 0x00400)
#define RMU_BASE          (AHB1_BASE + 0x00800)
#define PMU_BASE          (AHB1_BASE + 0x00C00)
#define MSC_BASE          (AHB1_BASE + 0x01000)
#define GPIOA_BASE        (AHB1_BASE + 0x04000)
#define GPIOB_BASE        (AHB1_BASE + 0x04040)
#define GPIOEXTI_BASE     (AHB1_BASE + 0x04300)
#define CRC_BASE          (AHB1_BASE + 0x05000)
#define CALC_BASE         (AHB1_BASE + 0x05400)
#define CRYPT_BASE        (AHB1_BASE + 0x05800)
#define TRNG_BASE         (AHB1_BASE + 0x05C00)
#define PIS_BASE          (AHB1_BASE + 0x06000)
#define HASH_BASE         (AHB1_BASE + 0x06800)

/*********************      Peripheral declaration        *************************/
/* APB1 */
#define GP16C4T0            ((TIMER_TypeDef *) GP16C4T0_BASE)
#define GP16C4T1            ((TIMER_TypeDef *) GP16C4T1_BASE)
#define AD16C4T0            ((TIMER_TypeDef *) AD16C4T0_BASE)
#define AD16C4T1            ((TIMER_TypeDef *) AD16C4T1_BASE)
#define BS16T0              ((TIMER_TypeDef *) BS16T0_BASE)
#define BS16T1              ((TIMER_TypeDef *) BS16T1_BASE)
#define SPI0                ((SPI_I2S_TypeDef *) SPI0_BASE)
#define SPI1                ((SPI_I2S_TypeDef *) SPI1_BASE)
#define I2S0                ((SPI_I2S_TypeDef *) SPI0_BASE)
#define I2S1                ((SPI_I2S_TypeDef *) SPI1_BASE)
#define I2C0                ((I2C_TypeDef *) I2C0_BASE)
#define I2C1                ((I2C_TypeDef *) I2C1_BASE)
#define DMA0                ((DMA_TypeDef *) DMA0_BASE)
#define QSPI                ((QSPI_TypeDef *)    QSPI_BASE)
#define UART0               ((UART_TypeDef *) UART0_BASE)
#define UART1               ((UART_TypeDef *) UART1_BASE)
#define UART2               ((UART_TypeDef *) UART2_BASE)
#define ECC                 ((ECC_TypeDef *) ECC_BASE )

/* APB2 */
#define LP16T               ((LPTIM_TypeDef *) LP16T_BASE)
#define WWDT                ((WWDT_TypeDef *) WWDT_BASE)
#define IWDT                ((WWDT_TypeDef *) IWDT_BASE)
#define BKPC                ((BKPC_TypeDef *) BKPC_BASE)
#define ADC                 ((ADC_TypeDef *) ADC_BASE)
#define RTC                 ((RTC_TypeDef  *)  RTC_BASE)

/* AHB1 */
#define SYSCFG              ((SYSCFG_TypeDef *) SYSCFG_BASE)
#define CMU                 ((CMU_TypeDef *) CMU_BASE)
#define RMU                 ((RMU_TypeDef *) RMU_BASE)
#define PMU                 ((PMU_TypeDef *) PMU_BASE)
#define MSC                 ((MSC_TypeDef *) MSC_BASE)
#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)
#define EXTI                ((GPIOEXTI_TypeDef *) GPIOEXTI_BASE)
#define CRC                 ((CRC_TypeDef *) CRC_BASE)
#define PIS                 ((PIS_TypeDef *) PIS_BASE)
#define CALC                ((CALC_TypeDef *) CALC_BASE)
#define CRYPT               ((CRYPT_TypeDef *)CRYPT_BASE)
#define HASH                ((HASH_TypeDef *) HASH_BASE )
#define TRNG                ((TRNG_TypeDef *) TRNG_BASE )



#ifdef __cplusplus
}
#endif

#endif

/**
  * @} ES32W3120
  */

/**
  * @} CMSIS
  */
