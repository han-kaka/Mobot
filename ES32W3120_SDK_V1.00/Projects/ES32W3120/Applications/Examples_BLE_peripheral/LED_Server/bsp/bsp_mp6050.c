#include "bsp_mp6050.h"

#define MPU_WRITE   0x68 << 1//MPU6050Ð´µØÖ·
#define MPU_READ    ((0x68 << 1) + 1)//MPU6050¶ÁµØÖ·

#define MPU_ADDR    0x68

/* Private Macros ------------------------------------------------------------ */

/* Private Variables --------------------------------------------------------- */

/* Public Variables ---------------------------------------------------------- */
//md_i2c_init_t g_md_i2c;

//uint8_t g_recv_buf[20U];
//uint8_t g_send_buf[20] = {0x01U, 0x12U, 0x23U, 0x34U, 0x45U, 0x56U, 0x67U, 0x78U, 0x89U, 0x9AU, 0x01U, 0x12U, 0x23U, 0x34U, 0x45U, 0x56U, 0x67U, 0x78U, 0x89U, 0x9AU};

//uint8_t g_complete;
//static md_dma_descriptor_t g_dma0_ctrl_base[2] __attribute__((aligned(512)));
//static md_dma_config_t g_dma_rx_config, g_dma_tx_config;
	
uint8_t g_recv_buf[8];
uint8_t g_recv_len = sizeof(g_recv_buf);
uint8_t g_send_buf[8] = {0x01U, 0x12U, 0x23U, 0x34U, 0x45U, 0x56U, 0x67U, 0x78U};
uint8_t g_send_len = sizeof(g_send_buf);
volatile uint8_t g_rx_complete;
volatile uint8_t g_tx_complete;
i2c_handle_t g_h_i2c;
	
/* Private Constants --------------------------------------------------------- */

/* Private function prototypes ----------------------------------------------- */

/* Private Function ---------------------------------------------------------- */
	
/**
  * @brief  delay some time.
  * @retval None.
  */
static void delay(int i)
{
    while (i--) ;
}

/**
  * @brief  Initializate pin of i2c module.
  * @retval None
  */
static void i2c_pin_init(void)
{
//		md_gpio_init_t x;
//		md_gpio_init_struct(&x);

//		/* Initialize scl pin */
//		x.mode  = MD_GPIO_MODE_OUTPUT;
//		x.odos  = MD_GPIO_OPEN_DRAIN;
//		x.pupd  = MD_GPIO_PUSH_UP;
//		x.odrv  = MD_GPIO_OUT_DRIVE_NORMAL;
//		x.flt   = MD_GPIO_FILTER_DISABLE;
//		x.type  = MD_GPIO_TYPE_CMOS;
//		x.func  = MD_GPIO_FUNC_3;
//		md_gpio_init(I2C1_SCL_PORT, I2C1_SCL_PIN, &x);

//		/* Initialize sda pin */
//		x.mode  = MD_GPIO_MODE_OUTPUT;
//		x.odos  = MD_GPIO_OPEN_DRAIN;
//		x.pupd  = MD_GPIO_PUSH_UP;
//		x.odrv  = MD_GPIO_OUT_DRIVE_NORMAL;
//		x.flt   = MD_GPIO_FILTER_DISABLE;
//		x.type  = MD_GPIO_TYPE_CMOS;
//		x.func  = MD_GPIO_FUNC_3;
//		md_gpio_init(I2C1_SDA_PORT, I2C1_SDA_PIN, &x);

//		return;

//    gpio_init_t x;
//    memset(&x, 0, sizeof(gpio_init_t));

//    /* Initialize scl pin */
//    x.mode = GPIO_MODE_OUTPUT;
//    x.odos = GPIO_OPEN_DRAIN;
//    x.pupd = GPIO_PUSH_UP;
//    x.odrv = GPIO_OUT_DRIVE_NORMAL;
//    x.flt  = GPIO_FILTER_DISABLE;
//    x.type = GPIO_TYPE_TTL;
//    x.func = GPIO_FUNC_3;
//    ald_gpio_init(I2C1_SCL_PORT, I2C1_SCL_PIN, &x);

//    /* Initialize sda pin */
//    x.mode = GPIO_MODE_OUTPUT;
//    x.odos = GPIO_OPEN_DRAIN;
//    x.pupd = GPIO_PUSH_UP;
//    x.odrv = GPIO_OUT_DRIVE_NORMAL;
//    x.flt  = GPIO_FILTER_DISABLE;
//    x.type = GPIO_TYPE_TTL;
//    x.func = GPIO_FUNC_3;
//    ald_gpio_init(I2C1_SDA_PORT, I2C1_SDA_PIN, &x);

//    return;

//    gpio_init_t x;
//    memset(&x, 0, sizeof(gpio_init_t));

//    /* Initialize scl pin */
//    x.mode = GPIO_MODE_OUTPUT;
//    x.odos = GPIO_OPEN_DRAIN;
//    x.pupd = GPIO_PUSH_UP;
//    x.odrv = GPIO_OUT_DRIVE_NORMAL;
//    x.flt  = GPIO_FILTER_DISABLE;
//    x.type = GPIO_TYPE_TTL;
//    x.func = GPIO_FUNC_4;
//    ald_gpio_init(I2C_SCL_PORT, I2C_SCL_PIN, &x);

//    /* Initialize sda pin */
//    x.mode = GPIO_MODE_OUTPUT;
//    x.odos = GPIO_OPEN_DRAIN;
//    x.pupd = GPIO_PUSH_UP;
//    x.odrv = GPIO_OUT_DRIVE_NORMAL;
//    x.flt  = GPIO_FILTER_DISABLE;
//    x.type = GPIO_TYPE_TTL;
//    x.func = GPIO_FUNC_4;
//    ald_gpio_init(I2C_SDA_PORT, I2C_SDA_PIN, &x);

//    return;

		gpio_init_t x;

		x.mode = GPIO_MODE_OUTPUT;
		x.odos = GPIO_PUSH_PULL;
		x.pupd = GPIO_PUSH_UP;
		x.odrv = GPIO_OUT_DRIVE_NORMAL;
		x.flt  = GPIO_FILTER_DISABLE;
		x.type = GPIO_TYPE_CMOS;
		x.func = GPIO_FUNC_1;

		ald_gpio_init(I2C1_SCL_PORT, I2C1_SCL_PIN, &x);
		ald_gpio_write_pin(I2C1_SCL_PORT, I2C1_SCL_PIN, 1);
		
		x.mode = GPIO_MODE_OUTPUT;
		x.odos = GPIO_PUSH_PULL;
		x.pupd = GPIO_PUSH_UP;
		x.odrv = GPIO_OUT_DRIVE_NORMAL;
		x.flt  = GPIO_FILTER_DISABLE;
		x.type = GPIO_TYPE_CMOS;
		x.func = GPIO_FUNC_1;

		ald_gpio_init(I2C1_SDA_PORT, I2C1_SDA_PIN, &x);
		ald_gpio_write_pin(I2C1_SDA_PORT, I2C1_SDA_PIN, 1);
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

//    /* Enable DMA */
//    md_dma_enable();

//    md_dma_config_struct(&g_dma_tx_config);
//    g_dma_tx_config.data_width = MD_DMA_DATA_SIZE_BYTE;
//    g_dma_tx_config.src_inc    = MD_DMA_DATA_INC_BYTE;
//    g_dma_tx_config.dst_inc    = MD_DMA_DATA_INC_NONE;
//    g_dma_tx_config.R_power    = MD_DMA_R_POWER_1;
//    g_dma_tx_config.primary    = ENABLE;
//    g_dma_tx_config.burst      = ENABLE;
//    g_dma_tx_config.high_prio  = DISABLE;
//    g_dma_tx_config.interrupt  = ENABLE;
//    g_dma_tx_config.channel    = 0;
//    g_dma_tx_config.src        = (void *)(g_send_buf);
//    g_dma_tx_config.dst        = (void *)(&I2C1->TXDATA);
//    g_dma_tx_config.size       = sizeof(g_send_buf);
//    g_dma_tx_config.msel       = MD_DMA_MSEL_I2C1;
//    g_dma_tx_config.msigsel    = MD_DMA_MSIGSEL_I2C_TXEMPTY;
//    md_dma_config_base(DMA0, MD_DMA_CYCLE_CTRL_BASIC, &g_dma_tx_config);
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

//    md_dma_config_struct(&g_dma_rx_config);
//    /* initialize DMA */
//    g_dma_rx_config.data_width = MD_DMA_DATA_SIZE_BYTE;
//    g_dma_rx_config.src_inc    = MD_DMA_DATA_INC_NONE;
//    g_dma_rx_config.dst_inc    = MD_DMA_DATA_INC_BYTE;
//    g_dma_rx_config.R_power    = MD_DMA_R_POWER_1;
//    g_dma_rx_config.primary    = ENABLE;
//    g_dma_rx_config.burst      = ENABLE;
//    g_dma_rx_config.high_prio  = DISABLE;
//    g_dma_rx_config.interrupt  = ENABLE;
//    g_dma_rx_config.channel    = 1;
//    g_dma_rx_config.src        = (void *)(&I2C1->RXDATA);
//    g_dma_rx_config.dst        = (void *)(g_recv_buf);
//    g_dma_rx_config.size       = sizeof(g_recv_buf);
//    g_dma_rx_config.msel       = MD_DMA_MSEL_I2C1;
//    g_dma_rx_config.msigsel    = MD_DMA_MSIGSEL_I2C_RNR;
//    md_dma_config_base(DMA0, MD_DMA_CYCLE_CTRL_BASIC, &g_dma_rx_config);
//}

/*Completion of the host*/
static void master_tx_complete(i2c_handle_t *arg)
{
    g_tx_complete = 1;
		ES_LOG_PRINT("i2c1 master_tx_complete\n");
    return;
}

/*The host receives the complete*/
static void master_rx_complete(i2c_handle_t *arg)
{
    g_rx_complete = 1;
		ES_LOG_PRINT("i2c1 master_rx_complete\n");
    return;
}

void i2c_start(void)
{
		ald_gpio_write_pin(I2C1_SDA_PORT, I2C1_SDA_PIN, 1);
		ald_gpio_write_pin(I2C1_SCL_PORT, I2C1_SCL_PIN, 1);
		
		delay(2);
	
		ald_gpio_write_pin(I2C1_SDA_PORT, I2C1_SDA_PIN, 0);
	
		delay(2);
	
		ald_gpio_write_pin(I2C1_SCL_PORT, I2C1_SCL_PIN, 0);
}

void IIC_Send_Byte(uint8_t txd)
{   
		uint8_t t;
	
		ald_gpio_write_pin(I2C1_SCL_PORT, I2C1_SCL_PIN, 0);
	
		for(t=0;t<8;t++) {
				ald_gpio_write_pin(I2C1_SDA_PORT, I2C1_SDA_PIN, (txd&0x80)>>7);
				txd<<=1;
				delay(2);
				ald_gpio_write_pin(I2C1_SCL_PORT, I2C1_SCL_PIN, 1);
				delay(2);
				ald_gpio_write_pin(I2C1_SCL_PORT, I2C1_SCL_PIN, 0);
		}
} 

uint8_t i2c_wait_ack(void)
{
		uint8_t ucErrTime=0;
	
		gpio_init_t x;
		
		x.mode = GPIO_MODE_INPUT;
    x.odos = GPIO_PUSH_PULL;
    x.pupd = GPIO_PUSH_DOWN;
    x.odrv = GPIO_OUT_DRIVE_NORMAL;
    x.flt  = GPIO_FILTER_DISABLE;
    x.type = GPIO_TYPE_CMOS;
		x.func = GPIO_FUNC_1;

		ald_gpio_init(I2C1_SDA_PORT, I2C1_SDA_PIN, &x);
		delay(2);

		ald_gpio_write_pin(I2C1_SCL_PORT, I2C1_SCL_PIN, 1);
		delay(2);
	
		while(ald_gpio_read_pin(I2C1_SDA_PORT, I2C1_SDA_PIN)==1) 
		{
				ucErrTime++;
			  if(ucErrTime>250){
						ES_LOG_PRINT("return 1\n");
						return 1;
				}
		}
		ald_gpio_write_pin(I2C1_SCL_PORT, I2C1_SCL_PIN, 0);
		ES_LOG_PRINT("return 0\n");
		return 0; 
	

}

void i2c_ack(void)
{
//	SCL=0;
//	SDA_OUT();
//	SDA_w=0;
//	delay_us(2);
//	SCL=1;
//	delay_us(2);
//	SCL=0;
}

void i2c_nack(void)
{
//	SCL=0;
//	SDA_OUT();
//	SDA_w=1;
//	delay_us(2);
//	SCL=1;
//	delay_us(2);
//	SCL=0;
}

uint8_t IIC_Read_Byte(unsigned char ack)
{
		unsigned char i,receive=0;
	
		gpio_init_t x;
		
		x.mode = GPIO_MODE_INPUT;
    x.odos = GPIO_PUSH_PULL;
    x.pupd = GPIO_PUSH_DOWN;
    x.odrv = GPIO_OUT_DRIVE_NORMAL;
    x.flt  = GPIO_FILTER_DISABLE;
    x.type = GPIO_TYPE_CMOS;
		x.func = GPIO_FUNC_1;

		ald_gpio_init(I2C1_SDA_PORT, I2C1_SDA_PIN, &x);
	
		for(i=0;i<8;i++)
		{
				ald_gpio_write_pin(I2C1_SCL_PORT, I2C1_SCL_PIN, 0);
				delay(2);
				ald_gpio_write_pin(I2C1_SCL_PORT, I2C1_SCL_PIN, 1);
				receive<<=1;
				if(ald_gpio_read_pin(I2C1_SDA_PORT, I2C1_SDA_PIN)==1){
						receive++;
				}
				delay(2);
		}
		
		if(!ack){
				i2c_nack();
		}
		else{
				i2c_ack();
		}
		ES_LOG_PRINT("data %u\n", receive);
		return receive;
}

void i2c_init(void)
{
//    i2c_pin_init();
//	
//		md_i2c_struct_init(&g_md_i2c);
//    /* initialize I2C */
//    g_md_i2c.module       = MD_I2C_MODULE_MASTER;
//    g_md_i2c.addr_mode    = MD_I2C_ADDR_7BIT;
//    g_md_i2c.clk_speed    = MD_I2C_STANDARD_MODE_MAX_CLK;
//    g_md_i2c.dual_addr    = MD_I2C_DUALADDR_DISABLE;
//    g_md_i2c.general_call = MD_I2C_GENERALCALL_DISABLE;
//    g_md_i2c.no_stretch   = MD_I2C_NOSTRETCH_ENABLE;
//    g_md_i2c.own_addr1    = 0x5A;
//    md_i2c_init(I2C1, &g_md_i2c);
//    md_i2c_set_receive_fifo_reset(I2C1);
//    md_i2c_set_transmit_fifo_reset(I2C1);
//		
//    dma_send_tx();
//    dma_recv_rx();
//		
//		/* set slave address */
//    md_i2c_set_addr_0_9_bit(I2C1, SLAVE_ADDR << 1);
//		
//		/* set transmission length */
//    md_i2c_set_transmit_length(I2C1, sizeof(g_send_buf));
//		
//		md_dma_config_base(DMA0, MD_DMA_CYCLE_CTRL_BASIC, &g_dma_tx_config);
//		
//		/* send */
//    g_complete = 0;
//    /* Enable DMA channel */
//    md_dma_enable_channel(MD_DMA_CH_0);
//    /* select master write mode */
//    md_i2c_enable_master_write(I2C1);
//    /* enable TX DMA */
//    md_i2c_enable_dma_transmit(I2C1);
//    /* produce start signal */
//    md_i2c_set_start(I2C1);
//    while (!g_complete);

//    i2c_pin_init();
//		
//		/* Enable I2c interrupt */
//    ald_mcu_irq_config(I2C1_EV_IRQn, 3, 3, ENABLE);
//    ald_mcu_irq_config(I2C1_ERR_IRQn, 3, 3, ENABLE);
//		
//		/* clear i2c_handle_t structure */
//    memset(&g_h_i2c, 0, sizeof(i2c_handle_t));
//    /* Initialize i2c */
//    g_h_i2c.perh = I2C1;
//    g_h_i2c.init.module   = I2C_MODULE_MASTER;
//    g_h_i2c.init.addr_mode    = I2C_ADDR_7BIT;
//    g_h_i2c.init.clk_speed    = 100000;
//    g_h_i2c.init.dual_addr    = I2C_DUALADDR_ENABLE;
//    g_h_i2c.init.general_call = I2C_GENERALCALL_DISABLE;
//    g_h_i2c.init.no_stretch   = I2C_NOSTRETCH_DISABLE;
//    g_h_i2c.master_rx_cplt_cbk = master_rx_complete;
//    g_h_i2c.master_tx_cplt_cbk = master_tx_complete;
//    g_h_i2c.init.own_addr1    = 0xA0;
//    ald_i2c_init(&g_h_i2c);

//    SET_BIT(g_h_i2c.perh->FCON, I2C_FCON_TXFRST_MSK);
//    SET_BIT(g_h_i2c.perh->FCON, I2C_FCON_RXFRST_MSK);
//    MODIFY_REG(I2C1->FCON, I2C_FCON_RXFTH_MSK, (0 << I2C_FCON_RXFTH_POSS));
//    MODIFY_REG(I2C1->FCON, I2C_FCON_TXFTH_MSK, (0 << I2C_FCON_TXFTH_POSS));
		
//		/* recv data by interrupt */
//    g_rx_complete = 0;
//    ald_i2c_master_recv_by_it(&g_h_i2c, 0x2D << 1, g_recv_buf, g_recv_len);

//    while (g_rx_complete != 1);

//    /* send data by interrupt */
//    g_tx_complete = 0;
//    ald_i2c_master_send_by_it(&g_h_i2c, 0x2D << 1, g_send_buf, g_send_len);

//    while (g_tx_complete != 1);

		i2c_pin_init();
		
		uint8_t res;
		
		i2c_start(); 
		IIC_Send_Byte((MPU_ADDR<<1)|0);
		i2c_wait_ack();
		IIC_Send_Byte(0x75);
		i2c_wait_ack();
		res = IIC_Read_Byte(0);
		
}






