#ifndef __BSP_POWER_H
#define __BSP_POWER_H

#include "ald_conf.h"

#include "bsp_common.h"

//-----------¸÷IO¶¨Òå--------------------------
#define ADC_CHANNEL5_GPIO_PORT      GPIOA
#define ADC_CHANNEL5_PIN            GPIO_PIN_7

void adc_init(void);

#endif


