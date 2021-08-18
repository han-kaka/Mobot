#include "bsp_dx_bt24_t.h"

#include "app_ble.h"
#include "app_common.h"

#include "task_common.h"
#include "task_bluetooth.h"

/* Private Macros ------------------------------------------------------------ */

/* Private Variables --------------------------------------------------------- */

/* Public Variables ---------------------------------------------------------- */

/* Private Constants --------------------------------------------------------- */

/* Private function prototypes ----------------------------------------------- */

/* Private Function ---------------------------------------------------------- */

/* Exported Variables -------------------------------------------------------- */
extern uint8_t g_rx_buf[20];
extern uint8_t ble_rx_buf[20];
extern uint8_t g_tx_buf[256];
extern uint8_t ble_tx_buf[256];
extern uint8_t g_tx_len;
extern uint8_t ble_tx_len;

uint8_t bluetooth_task(uint8_t prio)
{
//    RTT_PRINTF("BlueTooth_Task\r\n");

    uint8_t m_SYS_SubTask_prio=0;

    while(ga_Subtask[prio])
    { 
        m_SYS_SubTask_prio = ga_TaskMapTable[ga_Subtask[prio]];
        switch(m_SYS_SubTask_prio)
        {
            case DATA_DECODE:
            {
                memcpy(ble_rx_buf, g_rx_buf, 20);
                memset(g_rx_buf, 0x00, 20);
                if(0 == ble_data_decode()){
                    set_task(BLUETOOTH, RET_ACK);
                }
            }
                break;
            
            case RET_ACK:
            {
                memcpy(g_tx_buf, ble_tx_buf, ble_tx_len);
                memset(ble_tx_buf, 0x00, 256);
                g_tx_len = ble_tx_len;
                send_ble_data();
            }
                break;
            
            default:
                    break;
        }
        if(clear_task(prio,m_SYS_SubTask_prio) == true)
        {
            return true;
        }
    }
    return false;
}
  

