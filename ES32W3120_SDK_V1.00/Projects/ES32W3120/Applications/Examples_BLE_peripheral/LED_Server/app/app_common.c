#include "app_common.h"
#include <stdlib.h>
#include "task_common.h"

//Sys_Flag_Type                           Sys_Flag_Struct = {.reserved = 0,}; 


//ÖÃÆğÈÎÎñ
void set_task(uint8_t main_task,uint8_t sub_task)
{
    uint16_t mm,ss;
    mm = 1<<main_task;
    ss = 1<<sub_task;
    g_Maintask |= mm;
    ga_Subtask[main_task] |= ss;
}

bool clear_task(uint8_t prio, uint8_t m_SYS_SubTask_prio)
{
    ga_Subtask[prio] &=~ (1<<m_SYS_SubTask_prio);
    if(ga_Subtask[prio] == 0)
    {
        g_Maintask &=~(1<<prio);
        return true;
    }
    return false; 
}

uint8_t get_xor(uint8_t *hex_data_buf, uint16_t len_hex)
{
    uint8_t result = hex_data_buf[0];
    for(uint8_t i=1; i<len_hex; i++)
    {
        result ^= hex_data_buf[i];
    }
    return result;
}

bool xor_check(uint8_t *hex_data_buf, uint16_t len_hex)
{
    uint8_t i;
    uint8_t temp = hex_data_buf[0];
    for(i=1; i<(len_hex-1); i++)
    {
        temp ^= hex_data_buf[i];
    }
    if(temp == hex_data_buf[i])
    {
//        RTT_PRINTF("xor true!\r\n");
        return true;
    }
    else
    {
//        RTT_PRINTF("xor false!\r\n");
        return false;
    }
}









