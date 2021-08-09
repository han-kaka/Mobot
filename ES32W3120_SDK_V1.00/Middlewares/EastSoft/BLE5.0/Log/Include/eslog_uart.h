#ifndef _ESLOG_UART_H_
#define _ESLOG_UART_H_
#include <stdint.h>

void uart_write(uint8_t *bufptr, uint8_t size);
void eslog_uart_init(void);

#endif
