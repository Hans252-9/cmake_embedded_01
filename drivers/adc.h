#ifndef ADC_H
#define ADC_H

#include <stdint.h>

void adc_init(void);
int16_t adc_read_motor_temperature(void);
uint16_t adc_read_motor_current_ma(void);
void adc_set_simulated_temperature(int16_t temperature_c);
void adc_set_simulated_current_ma(uint16_t current_ma);

#endif
