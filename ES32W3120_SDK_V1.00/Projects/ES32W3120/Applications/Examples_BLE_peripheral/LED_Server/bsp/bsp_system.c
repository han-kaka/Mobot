#include "bsp_mp6050.h"
#include "bsp_dx_bt24_t.h"
#include "bsp_flash.h"
#include "bsp_power.h"
#include "bsp_time.h"
#include "bsp_system.h"

void initial_board(void)
{ 
//	md_gpio_init_t x;

//	x.mode = MD_GPIO_MODE_OUTPUT;
//	x.odos = MD_GPIO_PUSH_PULL;
//	x.pupd = MD_GPIO_PUSH_UP;
//	x.odrv = MD_GPIO_OUT_DRIVE_NORMAL;
//	x.flt  = MD_GPIO_FILTER_DISABLE;
//	x.type = MD_GPIO_TYPE_CMOS;
//	x.func = MD_GPIO_FUNC_1;

//	md_gpio_init(LED_RUN_PORT, LED_RUN_PIN, &x);
//	md_gpio_write_pin(LED_RUN_PORT, LED_RUN_PIN, 1);	

    gpio_init_t x;

    x.mode = GPIO_MODE_OUTPUT;
    x.odos = GPIO_PUSH_PULL;
    x.pupd = GPIO_PUSH_UP;
    x.odrv = GPIO_OUT_DRIVE_NORMAL;
    x.flt  = GPIO_FILTER_DISABLE;
    x.type = GPIO_TYPE_CMOS;
    x.func = GPIO_FUNC_1;

    ald_gpio_init(LED_RUN_PORT, LED_RUN_PIN, &x);
    ald_gpio_write_pin(LED_RUN_PORT, LED_RUN_PIN, 1);
}


void start_initial_task(void)
{  
//		/* Configure system clock */
//    md_cmu_clock_config_default();
//    /* Initialize SysTick Interrupt */
//    md_init_1ms_tick();

//    md_cmu_pll1_config(32);
//    md_cmu_clock_config(MD_CMU_CLOCK_PLL1, 48000000);

//    /* Enable ALL peripheral */
//    SYSCFG_UNLOCK();
//    md_cmu_enable_perh_all();
//    SYSCFG_LOCK();	

//		i2c_init();
//		uart_init();
//		spi_init();
//		adc_init();
//	
//		time_init();

    /* Initialize ALD */
    ald_cmu_init();
    /* Configure system clock */
    ald_cmu_pll1_config(32);
    ald_cmu_clock_config(CMU_CLOCK_PLL1, 48000000);
    ald_cmu_perh_clock_config(CMU_PERH_ALL, ENABLE);

//		i2c_init();
    uart_init();
//		spi_init();
//		adc_init();
//	
//		time_init();
}



