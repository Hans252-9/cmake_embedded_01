#include "pwm.h"

static volatile uint8_t current_duty_percent;

void pwm_init(void)
{
    current_duty_percent = 0U;
}

void pwm_set_duty(uint8_t duty_percent)
{
    if (duty_percent > 100U) {
        duty_percent = 100U;
    }

    current_duty_percent = duty_percent;
}

uint8_t pwm_get_duty(void)
{
    return current_duty_percent;
}
