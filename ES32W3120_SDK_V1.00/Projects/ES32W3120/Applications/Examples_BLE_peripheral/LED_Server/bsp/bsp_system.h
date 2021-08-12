#ifndef __BSP_SYSTEM_H
#define __BSP_SYSTEM_H

#include "md_conf.h"
#include "ald_conf.h"

#include "bsp_common.h"

//-----------¸÷IO¶¨Òå--------------------------
#define LED_RUN_PORT    		                   GPIOB
#define LED_RUN_PIN     		                   MD_GPIO_PIN_3

void start_initial_task(void);
void initial_board(void);

#endif
