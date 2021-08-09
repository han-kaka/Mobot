/*************************************************************************************************/
/*
Copyright	:	Shanghai Eastsoft Microelectronics Co.,Ltd.
File Name	:
Description	:
Author		:	eastsoft
Version		:
Date		:
History		:	None
Note		:	None
*/
/*************************************************************************************************/

#include "eslog_init.h"

extern uint32_t  Image$$RW_IRAM1$$Base;
extern uint32_t  Image$$RW_IRAM1$$Limit;
uint32_t const * const m_ram_start = &Image$$RW_IRAM1$$Base;
uint32_t const * const m_ram_end = &Image$$RW_IRAM1$$Limit;
extern uint32_t  Image$$RW_IRAM1$$ZI$$Base;
extern uint32_t  Image$$RW_IRAM1$$ZI$$Limit;
uint32_t const * const m_ZI_start = &Image$$RW_IRAM1$$ZI$$Base;
uint32_t const * const m_ZI_end = &Image$$RW_IRAM1$$ZI$$Limit;
/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
void eslog_init(void)
{
	#if(BLE_LOG_RTT)
	SEGGER_RTT_Init();
	#endif//BLE_LOG_RTT

	#if(BLE_LOG_UART)
	eslog_uart_init();
	#endif//BLE_LOG_UART
}
