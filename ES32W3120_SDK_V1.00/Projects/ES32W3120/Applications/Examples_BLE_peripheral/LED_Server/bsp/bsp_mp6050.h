#ifndef __BSP_MP6050_H
#define __BSP_MP6050_H

//#include "md_conf.h"
#include "ald_conf.h"

#include "bsp_common.h"

//-----------¸÷IO¶¨Òå--------------------------
//#define I2C1_SCL_PORT                          GPIOB
//#define I2C1_SCL_PIN                           MD_GPIO_PIN_4      /* I2CSCL:PB4 */
//#define I2C1_SDA_PORT                          GPIOB
//#define I2C1_SDA_PIN                           MD_GPIO_PIN_5      /* I2CSDA:PB5 */

#define I2C1_SCL_PORT                          GPIOB
#define I2C1_SCL_PIN                           GPIO_PIN_4      /* I2CSCL:PB4 */
#define I2C1_SDA_PORT                          GPIOB
#define I2C1_SDA_PIN                           GPIO_PIN_5      /* I2CSDA:PB5 */

//#define I2C_SCL_PORT    GPIOA
//#define I2C_SCL_PIN GPIO_PIN_14 
//#define I2C_SDA_PORT    GPIOA
//#define I2C_SDA_PIN GPIO_PIN_15

#define SLAVE_ADDR                             0x2D

void i2c_init(void);

#endif


