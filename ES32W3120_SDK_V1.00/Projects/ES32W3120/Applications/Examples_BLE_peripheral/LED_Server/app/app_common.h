#ifndef __APP_COMMON_H
#define __APP_COMMON_H

#include "global.h"

void set_task(uint8_t main_task, uint8_t sub_task);
bool clear_task(uint8_t prio, uint8_t m_SYS_SubTask_prio);

uint8_t get_xor(uint8_t *hex_data_buf, uint16_t len_hex);
bool xor_check(uint8_t *hex_data_buf, uint16_t len_hex);

#endif


