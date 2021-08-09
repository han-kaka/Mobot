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
#include <stdint.h>
#include <string.h>
#include "sdk_conf.h"
#if defined(BLE_LOG_UART) && BLE_LOG_UART
#include "eslog_uart.h"
#include "eslog_printf_format.h"

#define ES_UART_PRINTF_BUFFER_SIZE             (60)
#define ES_LOG_FORMAT_FLAG_LEFT_JUSTIFY        (1u << 0)
#define ES_LOG_FORMAT_FLAG_PAD_ZERO            (1u << 1)
#define ES_LOG_FORMAT_FLAG_PRINT_SIGN          (1u << 2)

/*********************************************************************
*
*       Types
*
**********************************************************************
*/

typedef struct 
{
  uint8_t* pBuffer;
  uint8_t  BufferSize;
  uint8_t  Cnt;
} ES_UART_PRINTF_DESC;

static void buffer_add(ES_UART_PRINTF_DESC * p, char c) 
{
	unsigned Cnt;

	Cnt = p->Cnt;
	if ((Cnt + 1u) <= p->BufferSize)
	{
		*(p->pBuffer + Cnt) = c;
		p->Cnt = Cnt + 1u;
	}

	if (p->Cnt == p->BufferSize) 
	{
		uart_write(p->pBuffer, p->Cnt);
		p->Cnt = 0u;
  }
}

static void string_print(ES_UART_PRINTF_DESC       * p,
                         char const *              p_str,
                         uint32_t                  FieldWidth,
                         uint32_t                  FormatFlags)
{
    uint32_t Width = 0;
    char c;

    if ((FormatFlags & ES_LOG_FORMAT_FLAG_LEFT_JUSTIFY) == ES_LOG_FORMAT_FLAG_LEFT_JUSTIFY)
    {
        while ((c = *p_str) != '\0')
        {
            p_str++;
            Width++;
            buffer_add(p, c);
        }

        while ((FieldWidth > Width) && (FieldWidth > 0))
        {
            FieldWidth--;
            buffer_add(p, ' ');
        }
    }
    else
    {
        if (p_str != 0)
        {
            Width = strlen(p_str);
        }

        while ((FieldWidth > Width) && (FieldWidth > 0))
        {
            FieldWidth--;
            buffer_add(p, ' ');
        }

        while ((c = *p_str) != '\0')
        {
            p_str++;
            Width++;
            buffer_add(p, c);
        }
    }
}

static void unsigned_print(ES_UART_PRINTF_DESC       * p,
                           uint32_t                  v,
                           uint32_t                  Base,
                           uint32_t                  NumDigits,
                           uint32_t                  FieldWidth,
                           uint32_t                  FormatFlags)
{
    static const char _aV2C[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                                   'A', 'B', 'C', 'D', 'E', 'F' };
    uint32_t Div;
    uint32_t Value;
    uint32_t Width;
    char c;

    Value = v;
    //
    // Get actual field width
    //
    Width = 1u;
    while (Value >= Base)
    {
        Value = (Value / Base);
        Width++;
    }
    if (NumDigits > Width)
    {
        Width = NumDigits;
    }
    //
    // Print leading chars if necessary
    //
    if ((FormatFlags & ES_LOG_FORMAT_FLAG_LEFT_JUSTIFY) == 0u)
    {
        if (FieldWidth != 0u)
        {
            if (((FormatFlags & ES_LOG_FORMAT_FLAG_PAD_ZERO) == ES_LOG_FORMAT_FLAG_PAD_ZERO) &&
                (NumDigits == 0u))
            {
                c = '0';
            }
            else
            {
                c = ' ';
            }
            while ((FieldWidth != 0u) && (Width < FieldWidth))
            {
                FieldWidth--;
                buffer_add(p, c);
            }
        }
    }

    Value = 1;
    /*
     * Compute Digit.
     * Loop until Digit has the value of the highest digit required.
     * Example: If the output is 345 (Base 10), loop 2 times until Digit is 100.
     */
    while (1)
    {
        /* User specified a min number of digits to print? => Make sure we loop at least that
         * often, before checking anything else (> 1 check avoids problems with NumDigits
         * being signed / unsigned)
         */
        if (NumDigits > 1u)
        {
            NumDigits--;
        }
        else
        {
            Div = v / Value;
            // Is our divider big enough to extract the highest digit from value? => Done
            if (Div < Base)
            {
                break;
            }
        }
        Value *= Base;
    }
    //
    // Output digits
    //
    do
    {
        Div = v / Value;
        v -= Div * Value;
        buffer_add(p, _aV2C[Div]);
        Value /= Base;
    } while (Value);
    //
    // Print trailing spaces if necessary
    //
    if ((FormatFlags & ES_LOG_FORMAT_FLAG_LEFT_JUSTIFY) == ES_LOG_FORMAT_FLAG_LEFT_JUSTIFY)
    {
        if (FieldWidth != 0u)
        {
            while ((FieldWidth != 0u) && (Width < FieldWidth))
            {
                FieldWidth--;
                buffer_add(p, ' ');
            }
        }
    }
}

static void int_print(ES_UART_PRINTF_DESC       * p,
                      int32_t                   v,
                      uint32_t                  Base,
                      uint32_t                  NumDigits,
                      uint32_t                  FieldWidth,
                      uint32_t                  FormatFlags)
{
    uint32_t Width;
    int32_t Number;

    Number = (v < 0) ? -v : v;

    //
    // Get actual field width
    //
    Width = 1u;
    while (Number >= (int32_t)Base)
    {
        Number = (Number / (int32_t)Base);
        Width++;
    }
    if (NumDigits > Width)
    {
        Width = NumDigits;
    }
    if ((FieldWidth > 0u) && ((v < 0) ||
        ((FormatFlags & ES_LOG_FORMAT_FLAG_PRINT_SIGN) == ES_LOG_FORMAT_FLAG_PRINT_SIGN)))
    {
        FieldWidth--;
    }
    //
    // Print leading spaces if necessary
    //
    if ((((FormatFlags & ES_LOG_FORMAT_FLAG_PAD_ZERO) == 0u) || (NumDigits != 0u)) &&
        ((FormatFlags & ES_LOG_FORMAT_FLAG_LEFT_JUSTIFY) == 0u))
    {
        if (FieldWidth != 0u)
        {
            while ((FieldWidth != 0u) && (Width < FieldWidth))
            {
                FieldWidth--;
                buffer_add(p, ' ');
            }
        }
    }
    //
    // Print sign if necessary
    //
    if (v < 0)
    {
        v = -v;
        buffer_add(p, '-');
    }
    else if ((FormatFlags & ES_LOG_FORMAT_FLAG_PRINT_SIGN) == ES_LOG_FORMAT_FLAG_PRINT_SIGN)
    {
        buffer_add(p, '+');
    }
    else
    {
        /* do nothing */
    }
    //
    // Print leading zeros if necessary
    //
    if (((FormatFlags & ES_LOG_FORMAT_FLAG_PAD_ZERO) == ES_LOG_FORMAT_FLAG_PAD_ZERO) &&
        ((FormatFlags & ES_LOG_FORMAT_FLAG_LEFT_JUSTIFY) == 0u) && (NumDigits == 0u))
    {
        if (FieldWidth != 0u)
        {
            while ((FieldWidth != 0u) && (Width < FieldWidth))
            {
                FieldWidth--;
                buffer_add(p, '0');
            }
        }
    }
    //
    // Print number without sign
    //
    unsigned_print(p, (uint32_t)v, Base, NumDigits, FieldWidth, FormatFlags);
}

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
void eslog_printf_fmt(char const *p_fmt, va_list *p_args)
{
	if (p_fmt == NULL)
    {
        return;
    }

    char c;
	ES_UART_PRINTF_DESC BufferDesc;
    int32_t v;
    uint32_t NumDigits;
    uint32_t FormatFlags;
    uint32_t FieldWidth;
	uint8_t Buffer[ES_UART_PRINTF_BUFFER_SIZE];

	BufferDesc.pBuffer        = Buffer;
	BufferDesc.BufferSize     = ES_UART_PRINTF_BUFFER_SIZE;
	BufferDesc.Cnt            = 0u;

    do
    {
        c = *p_fmt;
        p_fmt++;

        if (c == 0u)
        {
            break;
        }
        if (c == '%')
        {
            //
            // Filter out flags
            //
            FormatFlags = 0u;
            v = 1;

            do
            {
                c = *p_fmt;
                switch (c)
                {
                    case '-':
                        FormatFlags |= ES_LOG_FORMAT_FLAG_LEFT_JUSTIFY;
                        p_fmt++;
                        break;
                    case '0':
                        FormatFlags |= ES_LOG_FORMAT_FLAG_PAD_ZERO;
                        p_fmt++;
                        break;
                    case '+':
                        FormatFlags |= ES_LOG_FORMAT_FLAG_PRINT_SIGN;
                        p_fmt++;
                        break;
                    default:
                        v = 0;
                        break;
                }
            } while (v);

            //
            // filter out field width
            //
            FieldWidth = 0u;
            do
            {
                if (c == '*')
                {
                    /*lint -save -e64 -e56*/
                    FieldWidth += va_arg(*p_args, unsigned);
                    /*lint -restore*/
                    p_fmt++;
                    break;
                }
                c = *p_fmt;
                if ((c < '0') || (c > '9'))
                {
                    break;
                }
                p_fmt++;
                FieldWidth = (FieldWidth * 10u) + (c - '0');
            } while (1);

            //
            // Filter out precision (number of digits to display)
            //
            NumDigits = 0u;
            c = *p_fmt;
            if (c == '.')
            {
                p_fmt++;
                do
                {
                    c = *p_fmt;
                    if ((c < '0') || (c > '9'))
                    {
                        break;
                    }
                    p_fmt++;
                    NumDigits = NumDigits * 10u + (c - '0');
                } while (1);
            }
            //
            // Filter out length modifier
            //
            c = *p_fmt;
            do
            {
                if ((c == 'l') || (c == 'h'))
                {
                    p_fmt++;
                    c = *p_fmt;
                }
                else
                {
                    break;
                }
            } while (1);
            //
            // Handle specifiers
            //
            /*lint -save -e64*/
            switch (c)
            {
                case 'c':
                {
                    char c0;
                    v = va_arg(*p_args, int32_t);
                    c0 = (char)v;
                    buffer_add(&BufferDesc, c0);
                    break;
                }
                case 'd':
                case 'i':
                    v = va_arg(*p_args, int32_t);
                    int_print(&BufferDesc,
                              v,
                              10u,
                              NumDigits,
                              FieldWidth,
                              FormatFlags);
                    break;
                case 'u':
                    v = va_arg(*p_args, int32_t);
                    unsigned_print(&BufferDesc,
                                   (uint32_t)v,
                                   10u,
                                   NumDigits,
                                   FieldWidth,
                                   FormatFlags);
                    break;
                case 'x':
                case 'X':
                    v = va_arg(*p_args, int32_t);
                    unsigned_print(&BufferDesc,
                                   (uint32_t)v,
                                   16u,
                                   NumDigits,
                                   FieldWidth,
                                   FormatFlags);
                    break;
                case 's':
                {
                    char const * p_s = va_arg(*p_args, const char *);
                    string_print(&BufferDesc, p_s, FieldWidth, FormatFlags);
                    break;
                }
                case 'p':
                    v = va_arg(*p_args, int32_t);
                    buffer_add(&BufferDesc, '0');
                    buffer_add(&BufferDesc, 'x');
                    unsigned_print(&BufferDesc, (uint32_t)v, 16u, 8u, 8u, 0);
                    break;
                case '%':
                    buffer_add(&BufferDesc, '%');
                    break;
                default:
                    break;
            }
            /*lint -restore*/
            p_fmt++;
        }
        else
        {
            buffer_add(&BufferDesc, c);
        }
    } while (*p_fmt != '\0');
	if (BufferDesc.Cnt != 0u) {
      uart_write(Buffer, BufferDesc.Cnt);
    }
}

void eslog_fprintf(char const *              p_fmt,
                                           ...)
{

    if (p_fmt == NULL)
    {
        return;
    }

    va_list args = {0};
    va_start(args, p_fmt);

    eslog_printf_fmt(p_fmt, &args);

    va_end(args);
}
#endif//BLE_LOG_UART

