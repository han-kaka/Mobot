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

typedef struct {
    uint16_t year;
    uint8_t moon;
    uint8_t day;
    uint8_t hour;
    uint8_t min;
    uint8_t second;
    
} beijing_time_t;

void time_init(void);

#endif


