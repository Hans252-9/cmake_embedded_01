#ifndef TEMPERATURE_FILTER_H
#define TEMPERATURE_FILTER_H

#include <stdint.h>

void temperature_filter_init(void);
int16_t temperature_filter_update(int16_t sample);
int16_t temperature_filter_get_value(void);

#endif
