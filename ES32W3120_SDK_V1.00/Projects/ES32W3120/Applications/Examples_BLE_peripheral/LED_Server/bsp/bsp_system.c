#include "bsp_system.h"
#include "bsp_mp6050.h"


void initial_board(void)
{ 
	md_gpio_init_t x;

	x.mode = MD_GPIO_MODE_OUTPUT;
	x.odos = MD_GPIO_PUSH_PULL;
	x.pupd = MD_GPIO_PUSH_UP;
	x.odrv = MD_GPIO_OUT_DRIVE_NORMAL;
	x.flt  = MD_GPIO_FILTER_DISABLE;
	x.type = MD_GPIO_TYPE_CMOS;
	x.func = MD_GPIO_FUNC_1;

	md_gpio_init(LED_RUN_PORT, LED_RUN_PIN, &x);
	md_gpio_write_pin(LED_RUN_PORT, LED_RUN_PIN, 1);	
}


void start_initial_task(void)
{  
		i2c_init();
	

}



