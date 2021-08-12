#include "bsp_time.h"

/* Private Macros ------------------------------------------------------------ */

/* Private Variables --------------------------------------------------------- */

/* Public Variables ---------------------------------------------------------- */

/* Private Constants --------------------------------------------------------- */

/* Private function prototypes ----------------------------------------------- */

/* Private Function ---------------------------------------------------------- */



void time_init(void)
{
    md_timer_base_init_t ad16c4t_init;

    md_timer_base_struct_init(&ad16c4t_init);   /* initialize the ad16c4t_init  */
    ad16c4t_init.prescaler = 48 - 1;            /* clk_count: 1MHz */
    ad16c4t_init.clk_div = MD_TIMER_CLOCK_DIV1; /* working clock of dead time and filter */
    ad16c4t_init.mode = MD_TIMER_CNT_MODE_UP;   /* count up */
    ad16c4t_init.period = 10000 - 1;            /* period is 1000 count clock */
    ad16c4t_init.re_cnt = 10 - 1;               /* 100 repeat count */
    md_timer_base_set_config(AD16C4T0, &ad16c4t_init);

    md_timer_enable_uit_interrupt(AD16C4T0);    /* enable updata interrupt */
    md_mcu_irq_config(AD16C4T0_UP_IRQn, 0, 0, ENABLE);  /* enable NVIC AD16C4T0 updata interrupt */
    md_timer_enable_counter_cnten(AD16C4T0);    /* enable AD16C4T0 */
}


