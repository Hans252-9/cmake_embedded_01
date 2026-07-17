#include "gpio.h"

static volatile bool motor_enabled;
static volatile bool fault_led_enabled;

void gpio_init(void)
{
    motor_enabled = false;
    fault_led_enabled = false;
}

void gpio_motor_enable(void)
{
    motor_enabled = true;
}

void gpio_motor_disable(void)
{
    motor_enabled = false;
}

bool gpio_is_motor_enabled(void)
{
    return motor_enabled;
}

void gpio_fault_led_set(bool enabled)
{
    fault_led_enabled = enabled;
}

bool gpio_fault_led_is_set(void)
{
    return fault_led_enabled;
}
