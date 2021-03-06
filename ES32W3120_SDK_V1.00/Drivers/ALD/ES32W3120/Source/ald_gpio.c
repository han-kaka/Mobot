/**********************************************************************************
 *
 * @file    ald_gpio.c
 * @brief   GPIO module driver.
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
#include "ald_gpio.h"

/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup GPIO GPIO
  * @brief GPIO module driver
  * @{
  */

#ifdef ALD_GPIO

/** @defgroup GPIO_Public_Functions GPIO Public Functions
  * @{
  */

/** @defgroup GPIO_Public_Functions_Group1 Initialization functions
  * @brief    Initialization and Configuration functions
  *
    @verbatim
 ===============================================================================
              ##### Initialization functions #####
 ===============================================================================
  [..]
    This section provides functions allowing to initialize the GPIOs or external
    interrupt to be ready for use.

    @endverbatim
  * @{
  */

/* Private Macros ------------------------------------------------------------ */

/* Private Variables --------------------------------------------------------- */

/* Public Variables ---------------------------------------------------------- */

/* Private Constants --------------------------------------------------------- */

/* Private function prototypes ----------------------------------------------- */

/* Private Function ---------------------------------------------------------- */

/**
  * @brief  Initialize the GPIOx peripheral according to the specified
  *         parameters in the gpio_init_t.
  * @param  GPIOx: Where x can be (A--H) to select the GPIO peripheral.
  * @param  pin: The pin which need to initialize.
  * @param  init: Pointer to a gpio_init_t structure that can contains
  *         the configuration information for the specified parameters.
  * @retval None
  */
void ald_gpio_init(GPIO_TypeDef *GPIOx, uint16_t pin, gpio_init_t *init)
{
    uint32_t i, pos, mask, tmp;

    assert_param(IS_GPIO_PORT(GPIOx));
    assert_param(IS_GPIO_PIN(pin));
    assert_param(IS_GPIO_MODE(init->mode));
    assert_param(IS_GPIO_ODOS(init->odos));
    assert_param(IS_GPIO_PUPD(init->pupd));
    assert_param(IS_GPIO_ODRV(init->odrv));
    assert_param(IS_GPIO_FLT(init->flt));
    assert_param(IS_GPIO_TYPE(init->type));
    assert_param(IS_GPIO_FUNC(init->func));

    for (i = 0; i < 16; ++i)
    {
        if (((pin >> i) & 0x1) == 0)
            continue;

        /* Get position and 2-bits mask */
        pos  = i << 1;
        mask = 0x3 << pos;

        /* Set PIN mode */
        tmp  = READ_REG(GPIOx->MODE);
        tmp &= ~mask;
        tmp |= (init->mode << pos);
        WRITE_REG(GPIOx->MODE, tmp);

        /* Set PIN open-drain or push-pull */
        tmp  = READ_REG(GPIOx->ODOS);
        tmp &= ~mask;
        tmp |= (init->odos << pos);
        WRITE_REG(GPIOx->ODOS, tmp);

        /* Set PIN push-up or/and push-down */
        tmp  = READ_REG(GPIOx->PUPD);
        tmp &= ~mask;
        tmp |= (init->pupd << pos);
        WRITE_REG(GPIOx->PUPD, tmp);

        /* Set PIN output driver */
        tmp  = READ_REG(GPIOx->ODRV);
        tmp &= ~mask;
        tmp |= (init->odrv << pos);
        WRITE_REG(GPIOx->ODRV, tmp);

        /* Get position and 1-bit mask */
        pos  = i;
        mask = 0x1 << pos;

        /* Set PIN filter enable or disable */
        tmp  = READ_REG(GPIOx->FLT);
        tmp &= ~mask;
        tmp |= (init->flt << pos);
        WRITE_REG(GPIOx->FLT, tmp);

        /* Set PIN type ttl or smit */
        tmp  = READ_REG(GPIOx->TYPE);
        tmp &= ~mask;
        tmp |= (init->type << pos);
        WRITE_REG(GPIOx->TYPE, tmp);

        /* Configure PIN function */
        pos  = i < 8 ? (i << 2) : ((i - 8) << 2);
        mask = 0xF << pos;
        tmp  = i < 8 ? READ_REG(GPIOx->FUNC0) : READ_REG(GPIOx->FUNC1);
        tmp &= ~mask;
        tmp |= (init->func << pos);
        i < 8 ? WRITE_REG(GPIOx->FUNC0, tmp) : WRITE_REG(GPIOx->FUNC1, tmp);
    }

    return;
}

/**
  * @brief  Initialize the GPIOx peripheral using the default parameters.
  * @param  GPIOx: Where x can be (A--H) to select the GPIO peripheral.
  * @param  pin: The pin which need to initialize.
  * @retval None
  */
void ald_gpio_init_default(GPIO_TypeDef *GPIOx, uint16_t pin)
{
    gpio_init_t init;

    /* Fill GPIO_init_t structure with default parameter */
    init.mode  = GPIO_MODE_OUTPUT;
    init.odos  = GPIO_PUSH_PULL;
    init.pupd  = GPIO_PUSH_UP;
    init.odrv = GPIO_OUT_DRIVE_NORMAL;
    init.flt   = GPIO_FILTER_DISABLE;
    init.type  = GPIO_TYPE_CMOS;
    init.func  = GPIO_FUNC_1;

    ald_gpio_init(GPIOx, pin, &init);
    return;
}

/**
  * @brief  Sets GPIO function to default(func0).
  * @param  GPIOx: Where x can be (A--H) to select the GPIO peripheral.
  * @retval None
  */
void ald_gpio_func_default(GPIO_TypeDef *GPIOx)
{
    WRITE_REG(GPIOx->FUNC0, 0x00);
    WRITE_REG(GPIOx->FUNC1, 0x00);

    return;
}

/**
  * @brief  Initialize the external interrupt according to the specified
  *         parameters in the exti_init_t.
  * @param  GPIOx: Where x can be (A--H) to select the GPIO peripheral.
  * @param  pin: The pin which need to initialize.
  * @param  init: Pointer to a exti_init_t structure that can contains
  *         the configuration information for the specified parameters.
  * @retval None
  */
void ald_gpio_exti_init(GPIO_TypeDef *GPIOx, uint16_t pin, exti_init_t *init)
{
    uint8_t i;
    uint8_t port;

    assert_param(IS_GPIO_PORT(GPIOx));
    assert_param(IS_GPIO_PIN(pin));
    assert_param(IS_FUNC_STATE(init->filter));
    assert_param(IS_EXTI_FLTCKS_TYPE(init->cks));

    /* Get GPIO port */
    if (GPIOx == GPIOA)
        port = 0x0;
    else if (GPIOx == GPIOB)
        port = 0x1;
    else
        port = 0;

    /* Get Pin index */
    for (i = 0; i < 16; ++i)
    {
        if (((pin >> i) & 0x1) == 0x1)
            break;
    }

    /* Select external interrupt line */
    if (i <= 7)
    {
        EXTI->EXTIPSR0 &= ~(0x7U << (i * 4));
        EXTI->EXTIPSR0 |= (port << (i * 4));
    }
    else
    {
        i -= 8;
        EXTI->EXTIPSR1 &= ~(0x7U << (i * 4));
        EXTI->EXTIPSR1 |= (port << (i * 4));
    }

    /* Configure filter parameter */
    if (init->filter == ENABLE)
    {
        SET_BIT(EXTI->EXTIFLTCR, pin);
        MODIFY_REG(EXTI->EXTIFLTCR, GPIO_EXTIFLTCR_FLTCKS_MSK, init->cks << GPIO_EXTIFLTCR_FLTCKS_POSS);
        MODIFY_REG(EXTI->EXTIFLTCR, GPIO_EXTIFLTCR_FLTSEL_MSK, init->filter_time << GPIO_EXTIFLTCR_FLTSEL_POSS);
    }
    else
    {
        CLEAR_BIT(EXTI->EXTIFLTCR, pin);
    }

    return;
}
/**
  * @}
  */

/** @defgroup GPIO_Public_Functions_Group2 IO operation functions
  * @brief   GPIO Read and Write
  *
    @verbatim
 ===============================================================================
                       ##### IO operation functions #####
 ===============================================================================
  [..]
    This subsection provides a set of functions allowing to manage the GPIOs.

    @endverbatim
  * @{
  */

/**
  * @brief  Read the specified input port pin.
  * @param  GPIOx: Where x can be (A--H) to select the GPIO peripheral.
  * @param  pin: Specifies the pin to read.
  * @retval The input pin value
  */
uint8_t ald_gpio_read_pin(GPIO_TypeDef *GPIOx, uint16_t pin)
{
    assert_param(IS_GPIO_PORT(GPIOx));
    assert_param(IS_GPIO_PIN(pin));

    if (READ_BIT(GPIOx->DIN, pin))
        return 1;
    else
        return 0;
}

/**
  * @brief  Set or clear the select Pin data.
  * @param  GPIOx: Where x can be (A--H) to select the GPIO peripheral.
  * @param  pin: The specified pin to be written.
  * @param  val: The specifies value to be written.
  * @retval None
  */
void ald_gpio_write_pin(GPIO_TypeDef *GPIOx, uint16_t pin, uint8_t val)
{
    assert_param(IS_GPIO_PORT(GPIOx));
    assert_param(IS_GPIO_PIN(pin));

	if ((val & (0x01)) == 0x00)
		GPIOx->BSRR = pin << 16U;
	else
		GPIOx->BSRR = pin;

    return;
}

/**
  * @brief  Turn over the select data.
  * @param  GPIOx: Where x can be (A--H) to select the GPIO peripheral.
  * @param  pin: Specifies the pin to turn over.
  * @retval None
  */
void ald_gpio_toggle_pin(GPIO_TypeDef *GPIOx, uint16_t pin)
{
    assert_param(IS_GPIO_PORT(GPIOx));
    assert_param(IS_GPIO_PIN(pin));

    WRITE_REG(GPIOx->BIR, pin);
    return;
}

/**
  * @brief  Turn over the direction.
  * @param  GPIOx: Where x can be (A--H) to select the GPIO peripheral.
  * @param  pin: Specifies the pin to turn over.
  * @retval None
  */
void ald_gpio_toggle_dir(GPIO_TypeDef *GPIOx, uint16_t pin)
{
    uint32_t i, pos, mask, tmp, value;

    assert_param(IS_GPIO_PORT(GPIOx));
    assert_param(IS_GPIO_PIN(pin));

    for (i = 0; i < 16; ++i)
    {
        if (((pin >> i) & 0x1) == 0)
            continue;

        /* Get position and 2-bits mask */
        pos  = i << 1;
        mask = 0x3 << pos;

        /* Get the new direction */
        tmp = READ_REG(GPIOx->MODE);
        value = (tmp >> pos) & 0x3;

        if ((value == 2) || (value == 3))
            value = 1;
        else if (value == 1)
        {
            value = 2;
        }
        else
        {
            continue; /* do nothing */
        }

        /* Set PIN mode */
        tmp &= ~mask;
        tmp |= (value << pos);
        WRITE_REG(GPIOx->MODE, tmp);
    }

    return;
}

/**
  * @brief  Lock the GPIO prot. Once locked, can
  *         only change the output data. Only when the CPU
  *         reset to unlock the GPIO port.
  * @param  GPIOx: Where x can be (A--H) to select the GPIO peripheral.
  * @param  pin: The specified Pin to be written.
  * @retval None
  */
void ald_gpio_lock_pin(GPIO_TypeDef *GPIOx, uint16_t pin)
{
    assert_param(IS_GPIO_PORT(GPIOx));
    assert_param(IS_GPIO_PIN(pin));

    MODIFY_REG(GPIOx->LOCK, GPIO_LOCK_KEY_MSK, UNLOCK_KEY << GPIO_LOCK_KEY_POSS);
    WRITE_REG(GPIOx->LOCK, pin);

    return;
}

/**
  * @brief  Read the specified input port pin.
  * @param  GPIOx: Where x can be (A--H) to select the GPIO peripheral.
  * @retval The value;
  */
uint16_t ald_gpio_read_port(GPIO_TypeDef *GPIOx)
{
    assert_param(IS_GPIO_PORT(GPIOx));

    return READ_REG(GPIOx->DIN);
}

/**
  * @brief  Set or clear the select Pin data.
  * @param  GPIOx: Where x can be (A--H) to select the GPIO peripheral.
  * @param  val: The specifies value to be written.
  * @retval None
  */
void ald_gpio_write_port(GPIO_TypeDef *GPIOx, uint16_t val)
{
    assert_param(IS_GPIO_PORT(GPIOx));

    WRITE_REG(GPIOx->DOUT, val);
    return;
}
/**
  * @}
  */

/** @defgroup GPIO_Public_Functions_Group3 Control functions
  * @brief EXTI Control functions
  *
    @verbatim
 ===============================================================================
                       ##### Control functions #####
 ===============================================================================
  [..]
    This subsection provides a set of functions allowing to
    control external interrupt.

    @endverbatim
  * @{
  */

/**
  * @brief  Configure the interrupt according to the specified parameter.
  * @param  pin: The Pin which need to configure.
  * @param  style: External interrupt trigger style.
  * @param  status:
  *           @arg ENABLE
  *           @arg DISABLE
  * @retval None
  */
void ald_gpio_exti_interrupt_config(uint16_t pin, exti_trigger_style_t style, type_func_t status)
{
    assert_param(IS_GPIO_PIN(pin));
    assert_param(IS_TRIGGER_STYLE(style));
    assert_param(IS_FUNC_STATE(status));

    if (status == ENABLE)
    {
        if (style == EXTI_TRIGGER_RISING_EDGE)
        {
            SET_BIT(EXTI->EXTIRER, pin);
        }
        else if (style == EXTI_TRIGGER_TRAILING_EDGE)
        {
            SET_BIT(EXTI->EXTIFER, pin);
        }
        else if (style == EXTI_TRIGGER_BOTH_EDGE)
        {
            SET_BIT(EXTI->EXTIRER, pin);
            SET_BIT(EXTI->EXTIFER, pin);
        }
        else
        {
            ; /* do nothing */
        }

        WRITE_REG(EXTI->EXTICFR, 0xffff);
        SET_BIT(EXTI->EXTIEN, pin);
    }
    else
    {
        if (style == EXTI_TRIGGER_RISING_EDGE)
        {
            CLEAR_BIT(EXTI->EXTIRER, pin);
        }
        else if (style == EXTI_TRIGGER_TRAILING_EDGE)
        {
            CLEAR_BIT(EXTI->EXTIFER, pin);
        }
        else if (style == EXTI_TRIGGER_BOTH_EDGE)
        {
            CLEAR_BIT(EXTI->EXTIRER, pin);
            CLEAR_BIT(EXTI->EXTIFER, pin);
        }
        else
        {
            ; /* do nothing */
        }

        CLEAR_BIT(EXTI->EXTIEN, pin);
    }

    return;
}

/**
  * @brief  Get the Flag about external interrupt.
  * @param  pin: The pin which belong to external interrupt.
  * @retval Flag status
  *         - SET
  *         - RESET
  */
flag_status_t ald_gpio_exti_get_flag_status(uint16_t pin)
{
    assert_param(IS_GPIO_PIN(pin));

    if (READ_BIT(EXTI->EXTIFLAG, pin))
        return SET;

    return RESET;
}

/**
  * @brief  Clear the external interrupt flag.
  * @param  pin: The pin which belong to external interrupt.
  * @retval None
  */
void ald_gpio_exti_clear_flag_status(uint16_t pin)
{
    assert_param(IS_GPIO_PIN(pin));

    WRITE_REG(EXTI->EXTICFR, pin);
    return;
}
/**
  * @}
  */

/**
  * @}
  */

#endif /* ALD_GPIO */
/**
  * @}
  */

/**
  * @}
  */

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
