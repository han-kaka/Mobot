#ifndef __BSP_FLASH_H
#define __BSP_FLASH_H

//#include "md_conf.h"
#include "ald_conf.h"

#include "bsp_common.h"

//-----------¸÷IO¶¨Òå--------------------------
//#define SPI_NSS_PORT                          GPIOB
//#define SPI_NSS_PIN                           MD_GPIO_PIN_13
//#define SPI_SCK_PORT                          GPIOB
//#define SPI_SCK_PIN                           MD_GPIO_PIN_12
//#define SPI_MOSI_PORT                         GPIOB
//#define SPI_MOSI_PIN                          MD_GPIO_PIN_15
//#define SPI_MISO_PORT                         GPIOB
//#define SPI_MISO_PIN                          MD_GPIO_PIN_14

#define SPI_NSS_PORT                          GPIOB
#define SPI_NSS_PIN                           GPIO_PIN_13
#define SPI_SCK_PORT                          GPIOB
#define SPI_SCK_PIN                           GPIO_PIN_12
#define SPI_MOSI_PORT                         GPIOB
#define SPI_MOSI_PIN                          GPIO_PIN_15
#define SPI_MISO_PORT                         GPIOB
#define SPI_MISO_PIN                          GPIO_PIN_14

void spi_init(void);

//md_status_t flash_write(uint32_t addr, char *buf, uint8_t size);

//md_status_t flash_read(uint32_t addr, char *buf, uint16_t size);
#endif


