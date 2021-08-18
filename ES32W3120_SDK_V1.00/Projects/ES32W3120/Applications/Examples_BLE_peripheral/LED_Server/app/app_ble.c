#include "app_ble.h"


/* Private Macros ------------------------------------------------------------ */

/* Private Variables --------------------------------------------------------- */

/* Public Variables ---------------------------------------------------------- */
uint8_t ble_rx_buf[20];
uint8_t ble_tx_buf[256];
uint8_t ble_tx_len;

/* Private Constants --------------------------------------------------------- */

/* Private function prototypes ----------------------------------------------- */

/* Private Function ---------------------------------------------------------- */

int ble_data_decode(void)
{
    uint8_t data_len = sizeof(ble_rx_buf);
    ble_data_t *ble_data;
    uint8_t sum = 0;
    uint8_t i = 0;
    int ret = 0;
    
    if(20 != data_len){
        return -1;
    }
    
    ble_data = (ble_data_t *)ble_rx_buf;
    for(i=0; i<19; i++){
        sum += ble_rx_buf[i];
    }
    
    if(sum != ble_data->sum){
        return -1;
    }
    
    switch(ble_data->cmd){
        case SYSTEM_CMD:
            switch(ble_data->address){
                case SYSTEM_HEART_BEATS:
                    break;
                
                case SYSTEM_ACK:
                    break;
                
                case SYSTEM_RESEND:
                    break;
                
                default:
                    ret = -1;
                    break;
            }
            break;
        
        case CONTROL_CMD:
            switch(ble_data->address){
                case CONTROL_CALIBRATE:
                    break;
                
                case CONTROL_SCAN:
                    break;
                
                case CONTROL_SEND_FLASH_DATA:
                    break;
                
                case CONTROL_NO_DATA:
                    break;
                
                default:
                    ret = -1;
                    break;
            }
            break;
        
        case SET_DATA_CMD:
            switch(ble_data->address){
                case SET_FREQUENCY:
                    break;
                
                default:
                    ret = -1;
                    break;
            }
            break;
        
        case READ_STATE_CMD:
            switch(ble_data->address){
                case STATE_INFO:
                    break;
                
                case STATE_SCAN:
                    break;
                
                default:
                    ret = -1;
                    break;
            }
            break;
        
        case READ_DATA_CMD:
            switch(ble_data->address){
                case DATA_MONITOR_DATA:
                    break;
                
                case DATA_TIME:
                    break;
                
                default:
                    ret = -1;
                    break;
            }
            break;
        
        default:
            ret = -1;
            break;
    }
    
    return ret;
}

