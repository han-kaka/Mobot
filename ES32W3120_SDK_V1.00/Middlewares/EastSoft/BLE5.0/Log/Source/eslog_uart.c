/*************************************************************************************************/
/*
Copyright	:	Shanghai Eastsoft Microelectronics Co.,Ltd.
File Name	:
Description	:
Author		:	eastsoft
Version		:
Date		:
History		:	None
Note		:	None
*/
/*************************************************************************************************/
#include "eslog_uart.h"
#include "sdk_conf.h"
#if defined(BLE_LOG_UART) && BLE_LOG_UART
#include "md_uart.h"
#include "es32w3120.h"
#include "md_conf.h"
#include "md_cmu.h"
#include "md_syscfg.h"

md_uart_init_t h_uart;
/**
  * @brief  Initializate pin of uart2 module.
  * @retval None
  */
static void uart_pin_init(void)
{
    md_gpio_init_t x;

	SYSCFG_UNLOCK();
	md_cmu_enable_perh_gpio();
	md_cmu_enable_perh_crc();
	md_cmu_enable_perh_uart2();
	SYSCFG_LOCK();
    /* Initialize tx pin */
    x.mode  = MD_GPIO_MODE_OUTPUT;
    x.odos  = MD_GPIO_PUSH_PULL;
    x.pupd  = MD_GPIO_PUSH_UP;
    x.odrv  = MD_GPIO_OUT_DRIVE_NORMAL;
    x.flt   = MD_GPIO_FILTER_ENABLE;
    x.func  = MD_GPIO_FUNC_4; //UART2-function4
    md_gpio_init(GPIOB, MD_GPIO_PIN_3, &x);

    /* Initialize rx pin */
    x.mode  = MD_GPIO_MODE_INPUT;
    x.odos  = MD_GPIO_PUSH_PULL;
    x.pupd  = MD_GPIO_PUSH_UP;
    x.odrv  = MD_GPIO_OUT_DRIVE_NORMAL;
    x.flt   = MD_GPIO_FILTER_ENABLE;
    x.func  = MD_GPIO_FUNC_4;//UART2-function4
    md_gpio_init(GPIOB, MD_GPIO_PIN_4, &x);

    return;
}

/**
  * @brief  Initialize the UARTx peripheral using the default parameters.
  * @param  init: Pointer to a uart_init_t structure
  * @retval None
  */
static void uart_init_struct(md_uart_init_t *init)
{
    init->baud        = 115200;
    init->word_length = MD_UART_WORD_LENGTH_8B;
    init->stop_bits   = MD_UART_STOP_BITS_1;
    init->parity      = MD_UART_PARITY_NONE;
    init->fctl        = MD_UART_FLOW_CTL_DISABLE;
    init->mode        = MD_UART_MODE;

    return;
}

static void config_uart2_irq(void)
{
	NVIC_ClearPendingIRQ(UART2_IRQn);
	NVIC_EnableIRQ(UART2_IRQn);
	NVIC_SetPriority(UART2_IRQn,1);

}

void uart_write(uint8_t *bufptr, uint8_t size)
{
	uint32_t i;

	for (i = 0; i < size; ++i) {
		md_uart_set_send_data8(UART2, bufptr[i]);	/* send a byte */

		while (md_uart_is_active_it_tbc(UART2) == 0) /* send finish */
			;

		md_uart_clear_it_tbc(UART2);	/* clear FLAG */
	}
}
/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
void eslog_uart_init(void)
{
	/* Enable UART2 interrupt */
	__disable_irq();
	config_uart2_irq();
	__enable_irq();

	/* Initialize UART2 */
    uart_pin_init();
    uart_init_struct(&h_uart);
    md_uart_init(UART2, &h_uart);
}
#endif//BLE_LOG_UART
