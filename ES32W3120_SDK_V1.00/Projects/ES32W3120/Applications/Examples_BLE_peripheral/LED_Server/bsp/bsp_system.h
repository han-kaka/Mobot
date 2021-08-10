#ifndef __BSP_SYSTEM_H
#define __BSP_SYSTEM_H

#include "md_conf.h"

#include "bsp_common.h"

//-----------��IO����--------------------------
#define LED_RUN_PORT    		                   GPIOB
#define LED_RUN_PIN     		                   MD_GPIO_PIN_3

#define I2C1_SCL_PORT                          GPIOB
#define I2C1_SCL_PIN                           MD_GPIO_PIN_4      /* I2CSCL:PB4 */
#define I2C1_SDA_PORT                          GPIOB
#define I2C1_SDA_PIN                           MD_GPIO_PIN_5      /* I2CSDA:PB5 */

void start_initial_task(void);
void initial_board(void);

#endif