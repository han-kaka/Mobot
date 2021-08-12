#include "bsp_dx_bt24_t.h"

/* Private Macros ------------------------------------------------------------ */

/* Private Variables --------------------------------------------------------- */

/* Public Variables ---------------------------------------------------------- */
//static md_dma_descriptor_t g_dma0_ctrl_base[2] __attribute__((aligned(512)));
//uint8_t g_rx_buf[32];
//static md_dma_config_t g_dma_tx_config, g_dma_rx_config;

uart_handle_t g_h_uart;
uint8_t g_rx_buf[256];
uint32_t g_rx_len = sizeof(g_rx_buf);
/* Private Constants --------------------------------------------------------- */

/* Private function prototypes ----------------------------------------------- */

/* Private Function ---------------------------------------------------------- */

/**
  * @brief  Init UART pin
  * @retval None
  */
static void uart_pin_init(void)
{
//    md_gpio_init_t x;
//    md_gpio_init_struct(&x);

//    /* Initialize tx pin: PA2 */
//    x.mode  = MD_GPIO_MODE_OUTPUT;
//    x.odos  = MD_GPIO_PUSH_PULL;
//    x.pupd  = MD_GPIO_PUSH_UP;
//    x.odrv = MD_GPIO_OUT_DRIVE_NORMAL;
//    x.flt   = MD_GPIO_FILTER_DISABLE;
//    x.type  = MD_GPIO_TYPE_TTL;
//    x.func  = MD_GPIO_FUNC_2;
//    md_gpio_init(UART0_TX_PORT, UART0_TX_PIN, &x);

//    /* Initialize rx pin: PA3 */
//    x.mode  = MD_GPIO_MODE_INPUT;
//    x.odos  = MD_GPIO_PUSH_PULL;
//    x.pupd  = MD_GPIO_PUSH_UP;
//    x.odrv = MD_GPIO_OUT_DRIVE_NORMAL;
//    x.flt   = MD_GPIO_FILTER_DISABLE;
//    x.type  = MD_GPIO_TYPE_TTL;
//    x.func  = MD_GPIO_FUNC_2;
//    md_gpio_init(UART0_RX_PORT, UART0_RX_PIN, &x);

    gpio_init_t x;
    memset(&x, 0x00, sizeof(gpio_init_t));

    /* Initialize tx pin: PA2 */
    x.mode = GPIO_MODE_OUTPUT;
    x.odos = GPIO_PUSH_PULL;
    x.pupd = GPIO_PUSH_UP;
    x.odrv = GPIO_OUT_DRIVE_NORMAL;
    x.flt  = GPIO_FILTER_DISABLE;
    x.type = GPIO_TYPE_TTL;
    x.func = GPIO_FUNC_2;
    ald_gpio_init(UART0_TX_PORT, UART0_TX_PIN, &x);

    /* Initialize rx pin: PA3 */
    x.mode = GPIO_MODE_INPUT;
    x.odos = GPIO_PUSH_PULL;
    x.pupd = GPIO_PUSH_UP;
    x.odrv = GPIO_OUT_DRIVE_NORMAL;
    x.flt  = GPIO_FILTER_DISABLE;
    x.type = GPIO_TYPE_TTL;
    x.func = GPIO_FUNC_2;
    ald_gpio_init(UART0_RX_PORT, UART0_RX_PIN, &x);

    return;
}

/**
  * @brief  Send message complete.
  * @param  arg: Pointer to uart_handle_t structure.
  * @retval None.
  */
static void uart_send_complete(uart_handle_t *arg)
{
    return;
}

/**
  * @brief  Receive a message complete.
  * @param  arg: Pointer to uart_handle_t structure.
  * @retval None.
  */
static void uart_recv_complete(uart_handle_t *arg)
{
    static uint8_t s_i;
    s_i++;

    if ((s_i > 1) && (*(g_h_uart.rx_buf - 2) == 0x0D) && (*(g_h_uart.rx_buf - 1) == 0x0A))
    {
        ald_uart_send_by_it(&g_h_uart, g_rx_buf, s_i);
        ald_uart_recv_by_it(&g_h_uart, g_rx_buf, 1);
        s_i = 0;
    }
    else
    {
        if (s_i >= g_rx_len)
            s_i = 0;

        ald_uart_recv_by_it(&g_h_uart, g_rx_buf + s_i, 1);
    }

    return;
}

/**
  * @brief:  Initialize the uart.
  * @param:  None
  * @retval: None
  */
static void uart0_init(void)
{
//    md_uart_init_t h_uart;
//    md_uart_init_struct(&h_uart);

//    /* Initialize UART0 */
//    h_uart.baud        = 9600;
//    h_uart.word_length = MD_UART_WORD_LENGTH_8B;
//    h_uart.stop_bits   = MD_UART_STOP_BITS_1;
//    h_uart.parity      = MD_UART_PARITY_NONE;
//    h_uart.fctl        = MD_UART_FLOW_CTL_DISABLE;
//    h_uart.mode        = MD_UART_MODE;
//    md_uart_init(UART0, &h_uart);
	
//		return;
	
		memset(&g_h_uart, 0x00, sizeof(uart_handle_t));
    /* Initialize uart */
    g_h_uart.perh             = UART0;
    g_h_uart.init.baud        = 9600;
    g_h_uart.init.word_length = UART_WORD_LENGTH_8B;
    g_h_uart.init.stop_bits   = UART_STOP_BITS_1;
    g_h_uart.init.parity      = UART_PARITY_NONE;
    g_h_uart.init.mode        = UART_MODE_UART;
    g_h_uart.init.fctl        = UART_HW_FLOW_CTL_DISABLE;
    g_h_uart.rx_cplt_cbk      = uart_recv_complete;
    g_h_uart.tx_cplt_cbk      = uart_send_complete;
    ald_uart_init(&g_h_uart);
		
		return;
}

///**
//  * @brief  dma_start_tx init.
//  * @param  None
//  * @retval None
//  */
//static void dma_send_tx(void)
//{
//    memset(&g_dma_tx_config, 0x0, sizeof(md_dma_config_t));
//    md_dma_set_ctrlbase((uint32_t)&g_dma0_ctrl_base);
//    md_dma_enable();

//    md_dma_config_struct(&g_dma_tx_config);

//    g_dma_tx_config.channel = 1;
//    g_dma_tx_config.data_width = MD_DMA_DATA_SIZE_BYTE;
//    g_dma_tx_config.primary = ENABLE;
//    g_dma_tx_config.R_power = MD_DMA_R_POWER_1;
//    g_dma_tx_config.dst     = (void *)&UART0->TXBUF;
//    g_dma_tx_config.src     = (void *)(g_rx_buf);;
//    g_dma_tx_config.dst_inc = MD_DMA_DATA_INC_NONE;
//    g_dma_tx_config.src_inc = MD_DMA_DATA_INC_BYTE;
//    g_dma_tx_config.size    = 32;
//    g_dma_tx_config.msel    = MD_DMA_MSEL_UART0;
//    g_dma_tx_config.msigsel = MD_DMA_MSIGSEL_UART_TXEMPTY;
//    g_dma_tx_config.burst   = ENABLE;
//    g_dma_tx_config.interrupt = ENABLE;

//}
///**
//  * @brief  dma_start_rx init.
//  * @param  None
//  * @retval None
//  */
//static void dma_recv_rx(void)
//{
//    memset(&g_dma_rx_config, 0x0, sizeof(md_dma_config_t));
//    md_dma_set_ctrlbase((uint32_t)&g_dma0_ctrl_base);

//    /* Enable DMA */
//    md_dma_enable();

//    g_dma_rx_config.data_width = MD_DMA_DATA_SIZE_BYTE;
//    g_dma_rx_config.src_inc    = MD_DMA_DATA_INC_NONE;
//    g_dma_rx_config.dst_inc    = MD_DMA_DATA_INC_BYTE;
//    g_dma_rx_config.R_power    = MD_DMA_R_POWER_1;
//    g_dma_rx_config.primary    = ENABLE;
//    g_dma_rx_config.burst      = DISABLE;
//    g_dma_rx_config.high_prio  = DISABLE;
//    g_dma_rx_config.interrupt  = ENABLE;

//    g_dma_rx_config.channel = 0;
//    g_dma_rx_config.src     = (void *)(&UART0->RXBUF);
//    g_dma_rx_config.dst     = (void *)(g_rx_buf);
//    g_dma_rx_config.size    = 32;
//    g_dma_rx_config.msel    = MD_DMA_MSEL_UART0;
//    g_dma_rx_config.msigsel = MD_DMA_MSIGSEL_UART_RNR;

//}

void uart_init(void)
{
//		uart_pin_init();
//		uart0_init();
//	
//		memset(g_dma0_ctrl_base, 0x0, sizeof(g_dma0_ctrl_base));
//	
//		/* send */
//    dma_send_tx();
//    /* receive */
//    dma_recv_rx();
//		
//		md_dma_config_base(DMA0, MD_DMA_CYCLE_CTRL_BASIC, &g_dma_rx_config);
//    md_dma_clear_flag_done(MD_DMA_CH_1);
//    md_dma_clear_flag_done(MD_DMA_CH_0);
//    md_dma_enable_channel(MD_DMA_CH_0);
//    md_uart_enable_rxdma(UART0);
	
		ald_mcu_irq_config(UART0_IRQn, 3, 3, ENABLE);
	
		/* Initialize pin */
    uart_pin_init();
	
		uart0_init();
		
		ald_uart_rx_fifo_config(&g_h_uart, UART_RXFIFO_1BYTE);
    ald_uart_tx_fifo_config(&g_h_uart, UART_TXFIFO_EMPTY);

    ald_uart_recv_by_it(&g_h_uart, g_rx_buf, 1);
}






