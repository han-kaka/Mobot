#ifndef _ESLOG_PRINTF_FORMAT_H_
#define _ESLOG_PRINTF_FORMAT_H_
#include <stdarg.h>

void eslog_printf_fmt(char const *p_fmt, va_list *p_args);
void eslog_fprintf(char const *              p_fmt,
                                           ...);

#endif
