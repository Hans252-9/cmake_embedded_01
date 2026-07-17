#include "platform.h"

#include "target_config.h"

void platform_init(void)
{
}

const char *platform_get_target_name(void)
{
    return TARGET_NAME;
}

uint32_t platform_get_cpu_frequency_hz(void)
{
    return TARGET_CPU_FREQUENCY_HZ;
}

bool platform_has_fpu(void)
{
    return TARGET_HAS_FPU != 0;
}

bool platform_has_double_precision_fpu(void)
{
    return TARGET_HAS_DOUBLE_PRECISION_FPU != 0;
}

void platform_delay_cycles(uint32_t cycles)
{
    volatile uint32_t remaining = cycles;

    while (remaining > 0U) {
        --remaining;
    }
}
