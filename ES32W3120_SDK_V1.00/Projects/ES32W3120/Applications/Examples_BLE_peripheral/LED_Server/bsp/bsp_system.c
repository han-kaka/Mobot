#include "bsp_mp6050.h"
#include "bsp_dx_bt24_t.h"
#include "bsp_flash.h"
#include "bsp_power.h"
#include "bsp_time.h"
#include "bsp_motor.h"
#include "bsp_led.h"
#include "bsp_system.h"

/* Private Macros ------------------------------------------------------------ */

/* Private Variables --------------------------------------------------------- */

/* Public Variables ---------------------------------------------------------- */
system_state_t ststem_state;

/* Private Constants --------------------------------------------------------- */

/* Private function prototypes ----------------------------------------------- */

/* Private Function ---------------------------------------------------------- */

/* Exported Variables -------------------------------------------------------- */


void initial_board(void)
{ 
    ststem_state.system_mode = E_NORMAL_MODE;
}


void start_initial_task(void)
{
    ald_cmu_perh_clock_config(CMU_PERH_ALL, ENABLE);

//    i2c_init();
    uart_init();
//    spi_init();
    adc_init();
    motor_init();
    led_init();
    
    time_init();
}



