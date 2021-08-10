#ifndef __BSP_SYSTEM_H
#define __BSP_SYSTEM_H

#include "ald_conf.h"

#include "bsp_common.h"

//-----------¸÷IO¶¨Òå--------------------------
#define LED_RUN_PORT    		                   GPIOB
#define LED_RUN_PIN     		                   GPIO_PIN_3

void start_initial_task(void);
void initial_board(void);

#endif
