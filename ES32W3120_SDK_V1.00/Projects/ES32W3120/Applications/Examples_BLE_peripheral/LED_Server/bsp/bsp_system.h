#ifndef __BSP_SYSTEM_H
#define __BSP_SYSTEM_H

#include "ald_conf.h"

#include "bsp_common.h"

typedef enum {
    E_NORMAL_MODE = 0,
    E_IDLE_MODE = 0,
    E_SHUTDOWN_MODE = 0,

    E_MODE_MAX,
}system_mode_e;

typedef struct {
    system_mode_e system_mode;
    
} system_state_t;

void start_initial_task(void);
void initial_board(void);

#endif
