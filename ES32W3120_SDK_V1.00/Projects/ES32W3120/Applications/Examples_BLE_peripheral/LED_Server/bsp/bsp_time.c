#include "bsp_time.h"

/* Private Macros ------------------------------------------------------------ */

/* Private Variables --------------------------------------------------------- */

/* Public Variables ---------------------------------------------------------- */
timer_handle_t g_ad16c4t_init;
timer_clock_config_t g_ad16c4t_clock_config;

/* Private Constants --------------------------------------------------------- */

/* Private function prototypes ----------------------------------------------- */

/* Private Function ---------------------------------------------------------- */

/**
  * @brief  ald timer period elapsed callback
  * @param  arg: Pointer to timer_handle_t structure.
  * @retval None.
  */
void ald_timer_period_elapsed_callback(struct timer_handle_s *arg)
{
		
}

void time_init(void)
{
//    md_timer_base_init_t ad16c4t_init;

//    md_timer_base_struct_init(&ad16c4t_init);   /* initialize the ad16c4t_init  */
//    ad16c4t_init.prescaler = 48 - 1;            /* clk_count: 1MHz */
//    ad16c4t_init.clk_div = MD_TIMER_CLOCK_DIV1; /* working clock of dead time and filter */
//    ad16c4t_init.mode = MD_TIMER_CNT_MODE_UP;   /* count up */
//    ad16c4t_init.period = 10000 - 1;            /* period is 1000 count clock */
//    ad16c4t_init.re_cnt = 10 - 1;               /* 100 repeat count */
//    md_timer_base_set_config(AD16C4T0, &ad16c4t_init);

//    md_timer_enable_uit_interrupt(AD16C4T0);    /* enable updata interrupt */
//    md_mcu_irq_config(AD16C4T0_UP_IRQn, 0, 0, ENABLE);  /* enable NVIC AD16C4T0 updata interrupt */
//    md_timer_enable_counter_cnten(AD16C4T0);    /* enable AD16C4T0 */
	
    /* Initialize AD16C4T1 */
    memset(&g_ad16c4t_init, 0x0, sizeof(g_ad16c4t_init));  /* initialize the g_ad16c4t_init */
    g_ad16c4t_init.perh = AD16C4T1;
    g_ad16c4t_init.init.prescaler    = 48 - 1;            /* clk_count: 1MHz */
    g_ad16c4t_init.init.mode         = TIMER_CNT_MODE_UP;  /* count up */
    g_ad16c4t_init.init.period       = 1000 - 1;           /* period is 1000 count clock */
    g_ad16c4t_init.init.clk_div      = TIMER_CLOCK_DIV1;   /* working clock of dead time and filter */
    g_ad16c4t_init.init.re_cnt       = 100 - 1;             /* 10 repeat count */
    g_ad16c4t_init.period_elapse_cbk = ald_timer_period_elapsed_callback;  /* updata period callback function */
    ald_timer_base_init(&g_ad16c4t_init);

    /* Initialize clock source */
    g_ad16c4t_clock_config.source = TIMER_SRC_INTER;   /**< internal clock sources */
    ald_timer_config_clock_source(&g_ad16c4t_init, &g_ad16c4t_clock_config);

    ald_mcu_irq_config(AD16C4T1_UP_IRQn, 0, 0, ENABLE);/* Enable AD16C4T1 interrupt */
    ald_timer_base_start_by_it(&g_ad16c4t_init);       /* Start UPDATE interrupt by interrupt */
}


