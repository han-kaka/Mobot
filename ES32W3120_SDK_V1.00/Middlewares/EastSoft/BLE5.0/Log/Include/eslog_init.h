#ifndef _ESLOG_INIT_H_
#define _ESLOG_INIT_H_

#include "sdk_conf.h"
//RTT
#include "SEGGER_RTT_Conf.h"
#include "SEGGER_RTT.h"

//UART
#include "eslog_uart.h"
#include "eslog_printf_format.h"

#define ESLOG_DEFAULT_INIT() eslog_init()

#if(BLE_LOG_RTT)
#define ES_LOG_PRINT(...) 	SEGGER_RTT_printf(0,__VA_ARGS__)
#endif
#if(BLE_LOG_UART)
#define ES_LOG_PRINT(...)	eslog_fprintf(__VA_ARGS__)
#endif

void eslog_init(void);

#endif
