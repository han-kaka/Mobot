#include "bsp_time.h"
#include "task_common.h"
#include "app_common.h"

/* Private Macros ------------------------------------------------------------ */

/* Private Variables --------------------------------------------------------- */

/* Public Variables ---------------------------------------------------------- */
timer_handle_t g_ad16c4t_init;
timer_clock_config_t g_ad16c4t_clock_config;
timer_cnt_t time_cnt;
timer_flg_t time_flg;

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
    time_cnt.time_1s_cnt++;
    if(100 <= time_cnt.time_1s_cnt){
        time_cnt.time_1s_cnt = 0;
        ES_LOG_PRINT("1s\n");
    }
    
    if(1 == time_flg.uart_timeout_flg){
        time_cnt.uart_timeout_cnt++;
        if(2 <= time_cnt.uart_timeout_cnt){
            set_task(BLUETOOTH, DATA_DECODE);
        }
    }
    
    
}

void time_init(void)
{
    memset(&time_cnt, 0x0, sizeof(time_cnt));
    
    /* Initialize AD16C4T1 */
    memset(&g_ad16c4t_init, 0x0, sizeof(g_ad16c4t_init));  /* initialize the g_ad16c4t_init */
    g_ad16c4t_init.perh = AD16C4T1;
    g_ad16c4t_init.init.prescaler    = 48 - 1;            /* clk_count: 1MHz */
    g_ad16c4t_init.init.mode         = TIMER_CNT_MODE_UP;  /* count up */
    g_ad16c4t_init.init.period       = 1000 - 1;           /* period is 1000 count clock */
    g_ad16c4t_init.init.clk_div      = TIMER_CLOCK_DIV1;   /* working clock of dead time and filter */
    g_ad16c4t_init.init.re_cnt       = 10 - 1;             /* 10 repeat count */
    g_ad16c4t_init.period_elapse_cbk = ald_timer_period_elapsed_callback;  /* updata period callback function */
    ald_timer_base_init(&g_ad16c4t_init);

    /* Initialize clock source */
    g_ad16c4t_clock_config.source = TIMER_SRC_INTER;   /**< internal clock sources */
    ald_timer_config_clock_source(&g_ad16c4t_init, &g_ad16c4t_clock_config);

    ald_mcu_irq_config(AD16C4T1_UP_IRQn, 0, 0, ENABLE);/* Enable AD16C4T1 interrupt */
    ald_timer_base_start_by_it(&g_ad16c4t_init);       /* Start UPDATE interrupt by interrupt */
}


