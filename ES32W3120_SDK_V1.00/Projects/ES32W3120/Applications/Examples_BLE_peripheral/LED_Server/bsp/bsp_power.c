#include "bsp_power.h"

/* Private Macros ------------------------------------------------------------ */

/* Private Variables --------------------------------------------------------- */
md_adc_init_t g_adc_init;
uint32_t g_adc_result;

/* Public Variables ---------------------------------------------------------- */

/* Private Constants --------------------------------------------------------- */

/* Private function prototypes ----------------------------------------------- */

/* Private Function ---------------------------------------------------------- */

/**
  * @brief  Configure the ADC Pins.
  * @param  None
  * @retval None
  */
static void gpio_pin_config()
{
    md_gpio_init_t x;
    md_gpio_init_struct(&x);

    /* Initialize adc gpio pin: PC0 */
    x.mode  = MD_GPIO_MODE_CLOSE;
    x.pupd  = MD_GPIO_PUSH_UP;
    x.odos  = MD_GPIO_PUSH_PULL;
    x.odrv  = MD_GPIO_OUT_DRIVE_NORMAL;
    x.flt   = MD_GPIO_FILTER_DISABLE;
    x.type  = MD_GPIO_TYPE_CMOS;
    x.func  = MD_GPIO_FUNC_0;

    md_gpio_init(ADC_CHANNEL5_GPIO_PORT, ADC_CHANNEL5_PIN, &x);

    return;
}

/**
  * @brief  Configure the ADC.
  * @param  None
  * @retval None
  */
void adc_base_config()
{
    md_adc_struct_init(&g_adc_init);

    /* Set ADC Base Configuration:  */
    g_adc_init.align    = MD_ADC_DATAALIGN_RIGHT;     /* Specifies ADC data alignment */
    g_adc_init.data_bit = MD_ADC_CONV_BIT_12;
    g_adc_init.div      = MD_ADC_CKDIV_16;            /* ADCCLK divider */
    g_adc_init.n_ref    = MD_ADC_NEG_REF_VSS;
    g_adc_init.p_ref    = MD_ADC_POS_REF_VDD;         /* The positive reference voltage*/
    md_adc_init(ADC, &g_adc_init);

    /* Trigger the NCHE FALG mode */
    md_adc_set_eoc_selection_nchesel(ADC, MD_ADC_NCHESEL_MODE_ALL);
    /*Enable ADC sequencers scan mode*/
    md_adc_scan_mode_enable_scanen(ADC);
    /* Set ADC group REG sequencer length and scan direction,ADC conversion 1 channel */
    md_adc_set_normal_channel_length_nsl(ADC, MD_ADC_NCH_NR_1);
    /* Set ADC continuous conversion mode on ADC group REG.*/
    md_adc_continuous_conversion_disable_cm(ADC);
    /*Set ADC group REG sequence: channel on the selected scan sequence rank.*/
    md_adc_set_normal_1st_conv_ns1(ADC, MD_ADC_CHANNEL_5);
    md_adc_set_smpt1_cht(ADC, MD_ADC_SAMPLETIME_15);
    /*ADC通道正负相输入buffer使能*/
    md_adc_channal_p_input_buffer_enable(ADC);
    md_adc_channal_n_input_buffer_enable(ADC);

    /*ADC 尼日不参考选择 3:ADC_VREFP = 2.4V  ADC_VCM = 1.2V
    md_adc_select_inside_vref_sel(ADC,0x3);

    md_adc_set_forward_ref_voltage_vrpsel(ADC,0x1);

    md_adc_set_reference_voltage_buffer_vrefen(ADC,0x0);
    */

    /* Set priority for ADC_IRQn */
    NVIC_SetPriority(ADC_IRQn, 0);
    /* Enable ADC_IRQn */
    NVIC_EnableIRQ(ADC_IRQn);
    /*Enable interruption ADC group REG end of sequence conversions.*/
    md_adc_conv_end_interrupt_enable_ncheie(ADC);
}

void adc_init(void)
{
		/* Enable the selected ADC instance.*/
    md_adc_converter_enable_adcen(ADC);
    /* Disable the selected ADC instance.*/
    md_adc_converter_disable_adcen(ADC);
	
    /* Pin Configuration */
    gpio_pin_config();
    /* ADC Base Feature Configuration */
    adc_base_config();

    /*Enable the selected ADC instance.*/
    md_adc_converter_enable_adcen(ADC);

    /* Enable ADC group REG conversion trigger source internal (SW start)*/
    md_adc_set_normal_channel_conv_start_nchtrg(ADC);
}
