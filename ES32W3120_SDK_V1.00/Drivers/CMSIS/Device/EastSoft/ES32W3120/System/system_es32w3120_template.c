/**
  **************************************************************************************
  * @file    system_ES32W3120.c
  * @brief   ESW3120 system File.
  * @data    27 Jun 2019
  * @author  Eastsoft AE Team
  * @note
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *
  **************************************************************************************
  */

#include "ES32W3120.h"

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup ES32W3120_System
  * @{
  */

/** @addtogroup ES32W3120_System_Private_Constants
  * @{
  */

/* ESW3120 system default core clock value */
#define SYSTEM_CORE_CLOCK_DEFAULT_FRE  (48000000)

/**
  * @} ESW3120_System_Private_Constants
  */

/** @addtogroup ESW3120_System_Private_Macros
  * @{
  */

/* Define system clock cinfiguration protection */
#define SYS_CLOCK_CONFIG_ENTER_CRITICAL()       \
do {                                            \
    WRITE_REG(SYSCFG->PROT, 0x55AA6996);        \
} while (0);

#define SYS_CLOCK_CONFIG_LEAVE_CRITICAL()       \
do {                                            \
    WRITE_REG(SYSCFG->PROT, 0x00000000);        \
} while (0);

/**
  * @} ESW3120_System_Private_Macros
  */

/** @addtogroup ESW3120_System_Private_Variables
  * @{
  */

/**
  * @brief update the value of SystemCoreClock after changing the system clock.
  */
/* The default sysytem clock value */
unsigned int SystemCoreClock = SYSTEM_CORE_CLOCK_DEFAULT_FRE;

/**
  * @} ESW3120_System_Private_Variables
  */

/** @addtogroup ESW3120_System_Public_Functions
  * @{
  */

/**
  * @brief:  Setup the microcontroller system.User can refine this function to
  *          set the system clock.
  * @param:  None
  * @retval: None
  */
static void SystemCoreClockUpdate(void)
{
    uint32_t ui32_timeout;

    /* Add your code */

    /* Disable system register write protection */
    SYS_CLOCK_CONFIG_ENTER_CRITICAL();

    /* Enable the external high-speed clock and wait for it to stabilize */
    SET_BIT(CMU->CLKENR, CMU_CLKENR_HOSCEN_MSK);
    ui32_timeout = 0xFFFFF;
    while ((READ_BIT(CMU->CLKSR, CMU_CLKSR_HOSCRDY_MSK) == 0)
           && (--ui32_timeout != 0));
    if (ui32_timeout == 0)
    {
        SYS_CLOCK_CONFIG_LEAVE_CRITICAL();
        return;
    }

    /* Enable the PLL1 and wait for it to stabilize */
    SET_BIT(CMU->CLKENR, CMU_CLKENR_PLL1EN_MSK);
    ui32_timeout = 0xFFFFF;
    while ((READ_BIT(CMU->CLKSR, CMU_CLKSR_PLL1RDY_MSK) == 0)
            && (--ui32_timeout != 0));
    if (ui32_timeout == 0)
    {
        SYS_CLOCK_CONFIG_LEAVE_CRITICAL();
        return;
    }

    /* Change system clock as PLL1 */
    MODIFY_REG(CMU->CSR, CMU_CSR_SYS_CMD_MSK, (0x4<<CMU_CSR_SYS_CMD_POSS));
    ui32_timeout = 0xFFFFF;
    while ((READ_BIT(CMU->CSR, CMU_CSR_SYS_RDYN_MSK) == CMU_CSR_SYS_RDYN_MSK)
          && (--ui32_timeout != 0));
    if (ui32_timeout == 0)
    {
        /* Switch system clock to HRC if switch to PLL1 fails */
        SET_BIT(CMU->CSR, CMU_CSR_SYS_CMD_MSK);
        while ((READ_BIT(CMU->CSR, CMU_CSR_SYS_RDYN_MSK) == CMU_CSR_SYS_RDYN_MSK)
              && (ui32_timeout-- > 0));
        SYS_CLOCK_CONFIG_LEAVE_CRITICAL();
        return;
    }

    /* Enable system register write protection */
    SYS_CLOCK_CONFIG_LEAVE_CRITICAL();

    /* Add your code */
}

/**
  * @brief:  Setup the microcontroller system.This function will be called in the
  *          first time after chip reset in Reset_Handler.
  * @note    We can not change the SystemCoreClock value in SystemInit() function
  *          because the SystemCoreClock value will be set to the default value
  *          in __main() function.So Verify that the system clock is 48MHz before
  *          system start.
  * @param:  None
  * @retval: None
  */
void SystemInit(void)
{
    /* Update the system clock */
    SystemCoreClockUpdate();

    /* Add your code */

    /* Add your code */
}

/**
  * @} ES32W3120_System_Public_Functions
  */

/**
  * @} ES32W3120_System
  */

/**
  * @} CMSIS
  */
  
/******************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
