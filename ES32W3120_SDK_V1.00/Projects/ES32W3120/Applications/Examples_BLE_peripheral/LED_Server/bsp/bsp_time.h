#ifndef __BSP_TIME_H
#define __BSP_TIME_H

#include "ald_conf.h"

#include "bsp_common.h"

typedef struct {
    uint32_t time_1s_cnt;
    uint32_t uart_timeout_cnt;
    
} timer_cnt_t;

typedef struct {
    uint32_t uart_timeout_flg;
    
} timer_flg_t;

void time_init(void);

#endif


