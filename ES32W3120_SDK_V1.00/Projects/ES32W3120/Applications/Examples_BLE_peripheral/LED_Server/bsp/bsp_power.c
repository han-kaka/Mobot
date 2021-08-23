#include "bsp_power.h"

/* Private Macros ------------------------------------------------------------ */

/* Private Variables --------------------------------------------------------- */
adc_handle_t g_h_adc;
adc_nch_conf_t g_nch_config;
adc_ich_conf_t g_ich_config;
uint32_t g_adc_result;

/* Public Variables ---------------------------------------------------------- */

/* Private Constants --------------------------------------------------------- */

/* Private function prototypes ----------------------------------------------- */

/* Private Function ---------------------------------------------------------- */

/**
  * @brief  Adc normal convert complete.
  * @param  arg: Pointer to adc_handle_t structure.
  * @retval None.
  */
void normal_convert_complete(adc_handle_t *arg)
{
    return;
}

/**
  * @brief  Adc insert convert complete.
  * @param  arg: Pointer to adc_handle_t structure.
  * @retval None.
  */
void insert_convert_complete(adc_handle_t *arg)
{
    return;
}

/**
  * @brief  Adc level out of window complete.
  * @param  arg: Pointer to adc_handle_t structure.
  * @retval None.
  */
void out_window_complete(adc_handle_t *arg)
{
    return;
}

/**
  * @brief  Adc error complete.
  * @param  arg: Pointer to adc_handle_t structure.
  * @retval None.
  */
void error_complete(adc_handle_t *arg)
{
    return;
}

/**
  * @brief  Adc over complete.
  * @param  arg: Pointer to adc_handle_t structure.
  * @retval None.
  */
void ovr_complete(adc_handle_t *arg)
{
    return;
}

/**
  * @brief  Configure the ADC Pins.
  * @param  None
  * @retval None
  */
static void gpio_pin_config()
{
    /* Initialize adc gpio pin */
    gpio_init_t x;
    memset(&x, 0x0, sizeof(gpio_init_t));

    x.mode = GPIO_MODE_CLOSE;
    x.pupd = GPIO_PUSH_UP;
    x.odrv = GPIO_OUT_DRIVE_NORMAL;
    x.flt  = GPIO_FILTER_DISABLE;
    x.type = GPIO_TYPE_CMOS;
    x.func = GPIO_FUNC_0;
    ald_gpio_init(ADC_IN_PORT, ADC_IN0_PIN, &x);

    return;
}

void adc_init(void)
{
    /* Enable interrupt */
    ald_mcu_irq_config(ADC_IRQn, 1, 1, ENABLE);

    /* ADC gpio init */
    gpio_pin_config();

    memset(&g_h_adc, 0x0, sizeof(adc_handle_t));
    memset(&g_nch_config, 0x0, sizeof(adc_nch_conf_t));

    /* Initialize adc */
    g_h_adc.perh = ADC;
    g_h_adc.init.align    = ADC_DATAALIGN_RIGHT;
    g_h_adc.init.scan     = ENABLE;
    g_h_adc.init.cont     = DISABLE;
    g_h_adc.init.disc     = ADC_ALL_DISABLE;
    g_h_adc.init.disc_nr  = ADC_DISC_NR_1;
    g_h_adc.init.data_bit = ADC_CONV_BIT_12;
    g_h_adc.init.div      = ADC_CKDIV_16;
    g_h_adc.init.nche_sel = ADC_NCHESEL_MODE_ALL;
    g_h_adc.init.nch_nr   = ADC_NCH_NR_1;
    g_h_adc.init.n_ref    = ADC_NEG_REF_VSS;
    g_h_adc.init.p_ref    = ADC_POS_REF_VDD;
    ADC_ENABLE(&g_h_adc);
    ADC_DISABLE(&g_h_adc);
    ald_adc_init(&g_h_adc);

    /* Initialize normal convert channel */
    g_nch_config.ch   = ADC_CHANNEL_0;
    g_nch_config.idx  = ADC_NCH_IDX_1;
    g_nch_config.samp = ADC_SAMPLETIME_15;
    ald_adc_normal_channel_config(&g_h_adc, &g_nch_config);

    /* Start normal convert, enable interrupt */
    ald_adc_normal_start_by_it(&g_h_adc);
}
