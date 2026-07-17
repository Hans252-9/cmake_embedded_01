#include "uart.h"

static volatile char dummy_uart_output;

void uart_init(void)
{
    dummy_uart_output = '\0';
}

void uart_write_char(char value)
{
    dummy_uart_output = value;
}

void uart_write_string(const char *text)
{
    if (text == (const char *)0) {
        return;
    }

    while (*text != '\0') {
        uart_write_char(*text);
        ++text;
    }
}
