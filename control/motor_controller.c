#include "motor_controller.h"

#include "adc.h"
#include "app_config.h"
#include "diagnostics.h"
#include "gpio.h"
#include "platform.h"
#include "pwm.h"
#include "speed_controller.h"
#include "temperature_filter.h"

#define MOTOR_OVERCURRENT_LIMIT_MA UINT16_C(5000)

static bool overtemperature;
static bool overcurrent;
static uint8_t commanded_duty;
static uint16_t simulated_measured_speed_rpm;

void motor_controller_init(void)
{
    platform_init();
    gpio_init();
    adc_init();
    pwm_init();
    temperature_filter_init();
    speed_controller_init();
    diagnostics_init();

    overtemperature = false;
    overcurrent = false;
    commanded_duty = 0U;
    simulated_measured_speed_rpm = 0U;

    diagnostics_log_startup();
    diagnostics_log_target();
    gpio_motor_enable();
}

uint8_t motor_controller_calculate_temperature_duty(int16_t temperature_c)
{
    int32_t temperature_range;
    int32_t temperature_offset;
    int32_t duty_range;
    int32_t duty;

    if (temperature_c < APP_MIN_MOTOR_TEMPERATURE_C) {
        return APP_MIN_PWM_DUTY_PERCENT;
    }

    if (temperature_c >= APP_WARNING_MOTOR_TEMPERATURE_C) {
        return APP_MAX_PWM_DUTY_PERCENT;
    }

    temperature_range =
        APP_WARNING_MOTOR_TEMPERATURE_C - APP_MIN_MOTOR_TEMPERATURE_C;
    temperature_offset = temperature_c - APP_MIN_MOTOR_TEMPERATURE_C;
    duty_range = APP_MAX_PWM_DUTY_PERCENT - APP_MIN_PWM_DUTY_PERCENT;
    duty = APP_MIN_PWM_DUTY_PERCENT +
           ((temperature_offset * duty_range) / temperature_range);

    return (uint8_t)duty;
}

void motor_controller_update(void)
{
    const int16_t raw_temperature = adc_read_motor_temperature();
    const uint16_t current_ma = adc_read_motor_current_ma();
    const int16_t filtered_temperature =
        temperature_filter_update(raw_temperature);
    const uint8_t temperature_duty =
        motor_controller_calculate_temperature_duty(filtered_temperature);
    const uint8_t speed_duty = speed_controller_calculate_duty(
        APP_TARGET_MOTOR_SPEED_RPM, simulated_measured_speed_rpm);

    commanded_duty =
        temperature_duty > speed_duty ? temperature_duty : speed_duty;

    diagnostics_log_temperature(filtered_temperature);
    diagnostics_log_current(current_ma);

    if (filtered_temperature >= APP_SHUTDOWN_MOTOR_TEMPERATURE_C) {
        if (!overtemperature) {
            diagnostics_log_overtemperature();
        }
        overtemperature = true;
    }

    if (current_ma > MOTOR_OVERCURRENT_LIMIT_MA) {
        if (!overcurrent) {
            diagnostics_log_overcurrent();
        }
        overcurrent = true;
    }

    if (overtemperature || overcurrent) {
        commanded_duty = 0U;
        pwm_set_duty(commanded_duty);
        gpio_motor_disable();
        gpio_fault_led_set(true);
        simulated_measured_speed_rpm = 0U;
        return;
    }

    pwm_set_duty(commanded_duty);
    gpio_motor_enable();
    gpio_fault_led_set(false);
    simulated_measured_speed_rpm =
        (uint16_t)(((uint32_t)commanded_duty *
                    APP_TARGET_MOTOR_SPEED_RPM) / 100U);
}

bool motor_controller_has_overtemperature(void)
{
    return overtemperature;
}

bool motor_controller_has_overcurrent(void)
{
    return overcurrent;
}

uint8_t motor_controller_get_commanded_duty(void)
{
    return commanded_duty;
}
