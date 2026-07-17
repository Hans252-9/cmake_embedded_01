#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include <stdint.h>

void diagnostics_init(void);
void diagnostics_log_startup(void);
void diagnostics_log_target(void);
void diagnostics_log_temperature(int16_t temperature_c);
void diagnostics_log_current(uint16_t current_ma);
void diagnostics_log_overtemperature(void);
void diagnostics_log_overcurrent(void);

#endif
