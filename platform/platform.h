#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdbool.h>
#include <stdint.h>

void platform_init(void);
const char *platform_get_target_name(void);
uint32_t platform_get_cpu_frequency_hz(void);
bool platform_has_fpu(void);
bool platform_has_double_precision_fpu(void);
void platform_delay_cycles(uint32_t cycles);

#endif
