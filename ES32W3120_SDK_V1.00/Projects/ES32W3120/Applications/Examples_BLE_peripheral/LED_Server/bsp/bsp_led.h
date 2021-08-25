#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "ald_conf.h"

#include "bsp_common.h"

//-----------¸÷IO¶¨Òå--------------------------
#define LED_RUN_PORT                               GPIOB
#define LED_RUN_PIN                                GPIO_PIN_3

void led_init(void);

#endif


