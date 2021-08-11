#include "bsp_flash.h"

#define FLASH_CS_SET() (md_gpio_write_pin(SPI_NSS_PORT, SPI_NSS_PIN, 1));
#define FLASH_CS_CLR() (md_gpio_write_pin(SPI_NSS_PORT, SPI_NSS_PIN, 0));

#define FLASH_WRITE_ENABLE  0x06
#define FLASH_ERASE         0x20
#define FLASH_PROGRAM       0x02
#define FLASH_READ          0x03
#define FLASH_ID            0x9F
#define FLASH_STATUS        0x05

/* Private Macros ------------------------------------------------------------ */

/* Private Variables --------------------------------------------------------- */

/* Public Variables ---------------------------------------------------------- */
uint16_t g_c = 0U;
static md_spi_init_t s_gs_spi;

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
  * @brief  Initializate spi flash pin
  * @retval None.
  */
static void spi_pin_init(void)
{
    md_gpio_init_t l_gpio;

    l_gpio.type  = MD_GPIO_TYPE_TTL;
    l_gpio.odos  = MD_GPIO_PUSH_PULL;
    l_gpio.pupd  = MD_GPIO_PUSH_UP;
    l_gpio.odrv  = MD_GPIO_OUT_DRIVE_NORMAL;
    l_gpio.flt   = MD_GPIO_FILTER_DISABLE;

    l_gpio.func  = MD_GPIO_FUNC_1;
    l_gpio.mode  = MD_GPIO_MODE_OUTPUT;
    md_gpio_init(SPI_NSS_PORT, SPI_NSS_PIN, &l_gpio);    /* 初始化PB13为片选管脚 */
    FLASH_CS_SET();   /* 片选输出高，释放Flash */

    l_gpio.func  = MD_GPIO_FUNC_2;
    l_gpio.mode  = MD_GPIO_MODE_OUTPUT;
    md_gpio_init(SPI_SCK_PORT, SPI_SCK_PIN, &l_gpio);    /* 初始化PB12为时钟输出管脚 */

    l_gpio.func  = MD_GPIO_FUNC_2;
    l_gpio.mode  = MD_GPIO_MODE_OUTPUT;
    md_gpio_init(SPI_MOSI_PORT, SPI_MOSI_PIN, &l_gpio);    /* 初始化PB15为MOSI管脚 */

    l_gpio.func  = MD_GPIO_FUNC_2;
    l_gpio.mode  = MD_GPIO_MODE_INPUT;
    md_gpio_init(SPI_MISO_PORT, SPI_MISO_PIN, &l_gpio);    /* 初始化PB14为MISO管脚 */
}

/**
  * @brief  Read flash id in blocking mode.
  * @retval flash id.
  */
static uint32_t flash_read_id(void)
{
    uint8_t i;
    int r_flag = 0;
    uint8_t flash_id[4] = {0U};

    flash_id[0] = FLASH_ID;

    FLASH_CS_CLR(); /* 片选拉低，选中Flash */

    for (i = 0; i < sizeof(flash_id); i++)
    {
        if (md_spi_send_byte_fast(&s_gs_spi, flash_id[i]) != MD_OK)
        {
            FLASH_CS_SET();     /* 片选拉高，释放Flash */
            return MD_ERROR;
        }
    }

    for (i = 0; i < 3; i++)
    {
        flash_id[i] = md_spi_recv_byte_fast(&s_gs_spi, &r_flag);

        if (r_flag != MD_OK)
        {
            FLASH_CS_SET();
            return MD_ERROR;
        }
    }

    FLASH_CS_SET();

    return ((flash_id[0] << 16) | (flash_id[1] << 8) | (flash_id[2]));  /* 制造商ID flash_id[0]和设备ID flash_id[1:2] */
}

void spi_init(void)
{
		uint32_t id;
	
		spi_pin_init();
	
		s_gs_spi.SPIx      = SPI0;                 /* 使用SPI0 */
    s_gs_spi.mode      = MD_SPI_MODE_MASTER;   /* SPI主机模式 */
    s_gs_spi.baud      = MD_SPI_BAUD_4;        /* 时钟48MHz/4=12MHz */
    s_gs_spi.data_size = MD_SPI_DATA_SIZE_8;   /* 8位模式 */
    s_gs_spi.polarity  = MD_SPI_CPOL_HIGH;     /* 空闲高电平 */
    s_gs_spi.phase     = MD_SPI_CPHA_SECOND;   /* 第二个边沿接收数据 */
    s_gs_spi.first_bit = MD_SPI_FIRSTBIT_MSB;  /* 先发送MSB */
    s_gs_spi.dir       = MD_SPI_DIRECTION_2LINES;
    s_gs_spi.ss_en     = DISABLE;
    s_gs_spi.crc_calc  = DISABLE;
    s_gs_spi.crc_poly  = 0;

    md_spi_init(&s_gs_spi);                    /* 按照参数初始化SPI外设 */
	
		id = flash_read_id();
		ES_LOG_PRINT("\r\nManufacturer ID is %02x & Device ID is %02x %02x\r\n", (uint8_t)(id >> 16), (uint8_t)(id >> 8), (uint8_t)id);
}

/**
  * @brief  transmit an amount of data in blocking mode.
  * @param  addr: Specific address which to be write.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @retval Status, see @ref md_status_t.
  */
md_status_t flash_write(uint32_t addr, char *buf, uint8_t size)
{
    uint8_t cmd_buf[4];
    uint8_t i = 0U;

    if (buf == NULL)
        return MD_ERROR;

    cmd_buf[0] = FLASH_PROGRAM;
    cmd_buf[1] = (addr >> 16) & 0xff;
    cmd_buf[2] = (addr >> 8) & 0xff;
    cmd_buf[3] = addr & 0xff;

    FLASH_CS_CLR();     /* 片选拉低，选中Flash */

    if (md_spi_send_byte_fast(&s_gs_spi, FLASH_WRITE_ENABLE) != MD_OK)
    {
        FLASH_CS_SET();
        return MD_ERROR;
    }

    FLASH_CS_SET();    /* 片选拉高，释放Flash */

    delay(100);
    FLASH_CS_CLR();

    for (i = 0; i < sizeof(cmd_buf); i++)     /* 发送编程指令和三个字节的Flash地址 */
    {
        if (md_spi_send_byte_fast(&s_gs_spi, cmd_buf[i]) != MD_OK)
        {
            FLASH_CS_SET();
            return MD_ERROR;
        }
    }

    for (i = 0; i < size; i++)  /* 待写数据发送到Flash */
    {
        if (md_spi_send_byte_fast(&s_gs_spi, buf[i]) != MD_OK)
        {
            FLASH_CS_SET();
            return MD_ERROR;
        }
    }

    FLASH_CS_SET();

    return MD_OK;
}

/**
  * @brief  Receive an amount of data in blocking mode.
  * @param  addr: address of flash where want to read.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be received
  * @retval Status, see @ref md_status_t.
  */
md_status_t flash_read(uint32_t addr, char *buf, uint16_t size)
{
    uint8_t cmd_buf[4];
    uint8_t i = 0U;
    int r_flag = 0;

    if (buf == NULL)
        return MD_ERROR;

    cmd_buf[0] = FLASH_READ;
    cmd_buf[1] = (addr >> 16) & 0xff;
    cmd_buf[2] = (addr >> 8) & 0xff;
    cmd_buf[3] = addr & 0xff;

    FLASH_CS_CLR();     /* 片选拉低，选中Flash */

    for (i = 0; i < sizeof(cmd_buf); i++)   /* 发送编程指令和三个字节的Flash地址 */
    {
        if (md_spi_send_byte_fast(&s_gs_spi, cmd_buf[i]) != MD_OK)
        {
            FLASH_CS_SET();     /* 片选拉高，释放Flash */
            g_c = 1;
            return MD_ERROR;
        }
    }

    for (i = 0; i < size; i++)  /* 发送编程指令和三个字节的Flash地址 */
    {
        buf[i] = md_spi_recv_byte_fast(&s_gs_spi, &r_flag);

        if (r_flag != MD_OK)
        {
            FLASH_CS_SET();
            g_c = 2;
            return MD_ERROR;
        }
    }

    FLASH_CS_SET();

    return MD_OK;
}

