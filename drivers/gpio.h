#ifndef GPIO_H
#define GPIO_H

#include <stdbool.h>

void gpio_init(void);
void gpio_motor_enable(void);
void gpio_motor_disable(void);
bool gpio_is_motor_enabled(void);
void gpio_fault_led_set(bool enabled);
bool gpio_fault_led_is_set(void);

#endif
