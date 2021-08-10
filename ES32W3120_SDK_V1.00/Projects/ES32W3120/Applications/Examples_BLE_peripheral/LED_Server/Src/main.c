/*************************************************************************************************/
/*
Copyright	:	QingDao Eastsoft Communication Technology Co.,Ltd.
File Name	:
Description	:
Author		:	eastsoft
Version		:
Date		:
History		:	None
Note		:	None
*/
/*************************************************************************************************/

#include <stdlib.h>

#include "ald_conf.h"

#include "esble_comm.h"
#include "lib.h"

#include "esapp.h"

#include "global.h"

#include "bsp_system.h"

#include "task_common.h"

uint8_t button_value = 1;

extern uint32_t md_system_clock;
extern uint32_t  Image$$RW_IRAM1$$Base;
uint32_t const * const app_ram_start = &Image$$RW_IRAM1$$Base;

uint8_t send_flag = 0;

//uart_handle_t g_h_uart;
//uint8_t g_rx_buf[32];

#define APP_RAM_START  (uint32_t)app_ram_start
#define SYSCNTL_FREQ			(48000000UL)

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
static void update_sys_clk(void)
{
	md_system_clock = SYSCNTL_FREQ;
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
static void log_init(void)
{
	ESLOG_DEFAULT_INIT();
}

/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:	The GPIO pin map is:
					|---------FUNCTION----------|------------PIN-----------|
					|-----------LED1------------|------------PA6-----------|
					|-----------LED2------------|------------PA7-----------|
					|-----------LED3------------|------------PA11----------|
					|-----------LED4------------|------------PA8-----------|
*/
/*************************************************************************************************/
static void led_init(void)
{
	gpio_init_t x;

	x.mode = GPIO_MODE_OUTPUT;
	x.odos = GPIO_PUSH_PULL;
	x.pupd = GPIO_PUSH_UP;
	x.odrv = MD_GPIO_OUT_DRIVE_NORMAL;
	x.flt  = GPIO_FILTER_DISABLE;
	x.type = GPIO_TYPE_CMOS;
	x.func = GPIO_FUNC_1;

	ald_gpio_init(GPIOA, GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_6 | GPIO_PIN_11, &x);
	ald_gpio_write_pin(GPIOA, GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_6 | GPIO_PIN_11, 1);
}

/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:	The GPIO pin map is:
					|---------FUNCTION----------|------------PIN-----------|
					|-----------KE1-------------|------------PB12----------|
*/
/*************************************************************************************************/
static void button_init(void)
{
	gpio_init_t x;
	exti_init_t exti;

	x.mode = GPIO_MODE_INPUT;
	x.odos = GPIO_PUSH_PULL;
	x.pupd = GPIO_PUSH_DOWN;
	x.odrv = MD_GPIO_OUT_DRIVE_NORMAL;
	x.flt  = GPIO_FILTER_DISABLE;
	x.type = GPIO_TYPE_CMOS;
	x.func = GPIO_FUNC_1;
	ald_gpio_init(GPIOB, GPIO_PIN_12, &x);

	exti.filter      = ENABLE;
	exti.cks         = EXTI_FILTER_CLOCK_10K;
	exti.filter_time = 10;
	ald_gpio_exti_init(GPIOB, GPIO_PIN_12, &exti);

	/* Clear interrupt flag */
	ald_gpio_exti_clear_flag_status(GPIO_PIN_12);
	/* Configure interrupt */
	ald_gpio_exti_interrupt_config(GPIO_PIN_12, EXTI_TRIGGER_BOTH_EDGE, ENABLE);

	__NVIC_EnableIRQ(EXTI12_IRQn);
}

static void esble_ram_start_get(uint32_t * p_app_ram_start)
{
    if (p_app_ram_start == NULL)
    {
        return;
    }

    *p_app_ram_start = APP_RAM_START;
}

static void esble_init_set(void)
{
	uint32_t ram_base_min;
	uint32_t app_ram_base;
	esble_cb_func_t cb;

	esble_ram_start_get(&app_ram_base);

	cb.gapm_cb	= (esble_gapm_cb_t)lib_ble_cb_hdl;
	cb.gapc_cb	= (esble_gapc_cb_t)lib_ble_cb_hdl;
	cb.gattm_cb	= (esble_gattm_cb_t)lib_ble_cb_hdl;
	cb.gattc_cb	= (esble_gattc_cb_t)lib_ble_cb_hdl;

	esble_init(0, &ram_base_min, &cb);

	// Start of RAM, obtained from linker symbol.

    if (ram_base_min > app_ram_base)
    {
        ES_LOG_PRINT("Insufficient RAM allocated for the SoftDevice.\n");

        ES_LOG_PRINT("Change the RAM start location from 0x%x to 0x%x.\n",
                        app_ram_base, ram_base_min);
    }
    else
    {
        ES_LOG_PRINT("RAM starts at 0x%x\n", app_ram_base);
        if (ram_base_min != app_ram_base)
        {
            ES_LOG_PRINT("RAM start location can be adjusted to 0x%x.\n", ram_base_min);

        }
    }
}

//void uart_pin_init(void)
//{
//    gpio_init_t x;
//    memset(&x, 0x00, sizeof(gpio_init_t));

//    /* Initialize tx pin: PA2 */
//    x.mode = GPIO_MODE_OUTPUT;
//    x.odos = GPIO_PUSH_PULL;
//    x.pupd = GPIO_PUSH_UP;
//    x.odrv = MD_GPIO_OUT_DRIVE_NORMAL;
//    x.flt  = GPIO_FILTER_DISABLE;
//    x.type = GPIO_TYPE_TTL;
//    x.func = GPIO_FUNC_2;
//    ald_gpio_init(GPIOA, GPIO_PIN_2, &x);

//    /* Initialize rx pin: PA3 */
//    x.mode = GPIO_MODE_INPUT;
//    x.odos = GPIO_PUSH_PULL;
//    x.pupd = GPIO_PUSH_UP;
//    x.odrv = MD_GPIO_OUT_DRIVE_NORMAL;
//    x.flt  = GPIO_FILTER_DISABLE;
//    x.type = GPIO_TYPE_TTL;
//    x.func = GPIO_FUNC_2;
//    ald_gpio_init(GPIOA, GPIO_PIN_3, &x);

//    return;
//}

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
int main(void)
{
//	uint8_t value = 1;
//	uint8_t data[250] = {0xaa, 0x13, 0xd5, 0x01, 0x01, 0xa2, 0xff, 0xe6, 0x41, 0x6c, 0x15, 0x08, 0x04, 0x10, 0x18, 0x38, 0x9e, 0x01, 0xdf, 0xc7, 
//												0xaa, 0x13, 0xd5, 0x01, 0x01, 0xa2, 0xff, 0xe6, 0x41, 0x6c, 0x15, 0x08, 0x04, 0x10, 0x18, 0x38, 0x9e, 0x01, 0xdf, 0xc7,
//												0xaa, 0x13, 0xd5, 0x01, 0x01, 0xa2, 0xff, 0xe6, 0x41, 0x6c, 0x15, 0x08, 0x04, 0x10, 0x18, 0x38, 0x9e, 0x01, 0xdf, 0xc7,
//												0xaa, 0x13, 0xd5, 0x01, 0x01, 0xa2, 0xff, 0xe6, 0x41, 0x6c, 0x15, 0x08, 0x04, 0x10, 0x18, 0x38, 0x9e, 0x01, 0xdf, 0xc7,
//												0xaa, 0x13, 0xd5, 0x01, 0x01, 0xa2, 0xff, 0xe6, 0x41, 0x6c, 0x15, 0x08, 0x04, 0x10, 0x18, 0x38, 0x9e, 0x01, 0xdf, 0xc7,		
//												0xaa, 0x13, 0xd5, 0x01, 0x01, 0xa2, 0xff, 0xe6, 0x41, 0x6c, 0x15, 0x08, 0x04, 0x10, 0x18, 0x38, 0x9e, 0x01, 0xdf, 0xc7,
//												0xaa, 0x13, 0xd5, 0x01, 0x01, 0xa2, 0xff, 0xe6, 0x41, 0x6c, 0x15, 0x08, 0x04, 0x10, 0x18, 0x38, 0x9e, 0x01, 0xdf, 0xc7,		
//												0xaa, 0x13, 0xd5, 0x01, 0x01, 0xa2, 0xff, 0xe6, 0x41, 0x6c, 0x15, 0x08, 0x04, 0x10, 0x18, 0x38, 0x9e, 0x01, 0xdf, 0xc7,
//												0xaa, 0x13, 0xd5, 0x01, 0x01, 0xa2, 0xff, 0xe6, 0x41, 0x6c, 0x15, 0x08, 0x04, 0x10, 0x18, 0x38, 0x9e, 0x01, 0xdf, 0xc7,
//												0xaa, 0x13, 0xd5, 0x01, 0x01, 0xa2, 0xff, 0xe6, 0x41, 0x6c, 0x15, 0x08, 0x04, 0x10, 0x18, 0x38, 0x9e, 0x01, 0xdf, 0xc7,
//												0xaa, 0x13, 0xd5, 0x01, 0x01, 0xa2, 0xff, 0xe6, 0x41, 0x6c, 0x15, 0x08, 0x04, 0x10, 0x18, 0x38, 0x9e, 0x01, 0xdf, 0xc7,
//												0xaa, 0x13, 0xd5, 0x01, 0x01, 0xa2, 0xff, 0xe6, 0x41, 0x6c, 0x15, 0x08, 0x04, 0x10, 0x18, 0x38, 0x9e, 0x01, 0xdf, 0xc7,
//												0xaa, 0x13, 0xd5, 0x01, 0x01, 0xa2, 0xff, 0xe6, 0x41, 0x6c};
//	uint16_t num = 0;
		
	update_sys_clk();
	log_init();
	led_init();
	button_init();
	esble_init_set();
//	esapp_init();
		
	//初始化IO
	initial_board();
	//开启一些初始任务
	start_initial_task();

	while(1)
	{
//		if(1 == send_flag) {
//			esapp_button(180, data);
//			num++;
//			data[2] = num >> 8;
//			data[3] = num & 0xff;
//			esble_msdelay(60);
//		}
		
		//主回路任务处理
		while(g_Maintask)
		{
				uint8_t m_temp = ga_TaskMapTable[g_Maintask];
				Task_Struct[m_temp].function(m_temp);
		}
		
//		if (value != button_value)
//		{
//			value = button_value;
//			if (button_value)
//			{
//				ald_gpio_write_pin(GPIOA, GPIO_PIN_6, 1);
//				esapp_button(0);
//			}
//			else
//			{
//				ald_gpio_write_pin(GPIOA, GPIO_PIN_6, 0);
//				esapp_button(1);
//			}
//		}
	}
}

/*************************************************************************************************/
/*
	Function	:
	Description	:	Button irq
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
void EXTI12_IRQHandler()
{
	ald_gpio_exti_clear_flag_status(GPIO_PIN_12);

	button_value = ald_gpio_read_pin(GPIOB, GPIO_PIN_12);
}
