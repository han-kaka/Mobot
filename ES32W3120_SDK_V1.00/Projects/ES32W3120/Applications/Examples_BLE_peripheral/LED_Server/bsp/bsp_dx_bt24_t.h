#ifndef __BSP_DX_BT24_T_H
#define __BSP_DX_BT24_T_H

//#include "md_conf.h"
#include "ald_conf.h"

#include "bsp_common.h"

//-----------¸÷IO¶¨Òå--------------------------
//#define UART0_TX_PORT   GPIOA
//#define UART0_TX_PIN    MD_GPIO_PIN_2
//#define UART0_RX_PORT   GPIOA
//#define UART0_RX_PIN    MD_GPIO_PIN_3

#define UART0_TX_PORT   GPIOA
#define UART0_TX_PIN    GPIO_PIN_2
#define UART0_RX_PORT   GPIOA
#define UART0_RX_PIN    GPIO_PIN_3

#define UARTX           UART0

void uart_init(void);

#endif


