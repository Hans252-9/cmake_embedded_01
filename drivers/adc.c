#include "adc.h"

static volatile int16_t simulated_temperature_c;
static volatile uint16_t simulated_current_ma;

void adc_init(void)
{
    simulated_temperature_c = 20;
    simulated_current_ma = 0U;
}

int16_t adc_read_motor_temperature(void)
{
    return simulated_temperature_c;
}

uint16_t adc_read_motor_current_ma(void)
{
    return simulated_current_ma;
}

void adc_set_simulated_temperature(int16_t temperature_c)
{
    simulated_temperature_c = temperature_c;
}

void adc_set_simulated_current_ma(uint16_t current_ma)
{
    simulated_current_ma = current_ma;
}
