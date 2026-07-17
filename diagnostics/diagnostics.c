#include "diagnostics.h"

#include <stdbool.h>

#include "platform.h"
#include "uart.h"

static void write_unsigned(uint32_t value)
{
    char digits[10];
    uint8_t count = 0U;

    do {
        digits[count] = (char)('0' + (value % 10U));
        value /= 10U;
        ++count;
    } while (value != 0U);

    while (count > 0U) {
        --count;
        uart_write_char(digits[count]);
    }
}

static void write_signed(int16_t value)
{
    int32_t wide_value = value;

    if (wide_value < 0) {
        uart_write_char('-');
        wide_value = -wide_value;
    }

    write_unsigned((uint32_t)wide_value);
}

void diagnostics_init(void)
{
    uart_init();
}

void diagnostics_log_startup(void)
{
    uart_write_string("Motor controller startup\r\n");
}

void diagnostics_log_target(void)
{
    uart_write_string("Target: ");
    uart_write_string(platform_get_target_name());
    uart_write_string(", CPU Hz: ");
    write_unsigned(platform_get_cpu_frequency_hz());
    uart_write_string(", FPU: ");
    uart_write_string(platform_has_fpu() ? "yes" : "no");
    uart_write_string(", double FPU: ");
    uart_write_string(platform_has_double_precision_fpu() ? "yes" : "no");
    uart_write_string("\r\n");
}

void diagnostics_log_temperature(int16_t temperature_c)
{
    uart_write_string("Temperature C: ");
    write_signed(temperature_c);
    uart_write_string("\r\n");
}

void diagnostics_log_current(uint16_t current_ma)
{
    uart_write_string("Current mA: ");
    write_unsigned(current_ma);
    uart_write_string("\r\n");
}

void diagnostics_log_overtemperature(void)
{
    uart_write_string("Fault: overtemperature\r\n");
}

void diagnostics_log_overcurrent(void)
{
    uart_write_string("Fault: overcurrent\r\n");
}
