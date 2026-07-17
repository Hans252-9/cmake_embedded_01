#ifndef TARGET_CONFIG_H
#define TARGET_CONFIG_H

#include <stdint.h>

#if (defined(TARGET_STM32F103C8) + defined(TARGET_STM32F407VG) + \
     defined(TARGET_STM32H743ZI)) != 1
#error "Define exactly one supported TARGET_* macro"
#endif

#if defined(TARGET_STM32F103C8)
#define TARGET_NAME                         "STM32F103C8T6"
#define TARGET_CPU_FREQUENCY_HZ             UINT32_C(72000000)
#define TARGET_HAS_FPU                      0
#define TARGET_HAS_DOUBLE_PRECISION_FPU     0
#elif defined(TARGET_STM32F407VG)
#define TARGET_NAME                         "STM32F407VGT6"
#define TARGET_CPU_FREQUENCY_HZ             UINT32_C(168000000)
#define TARGET_HAS_FPU                      1
#define TARGET_HAS_DOUBLE_PRECISION_FPU     0
#elif defined(TARGET_STM32H743ZI)
#define TARGET_NAME                         "STM32H743ZIT6"
#define TARGET_CPU_FREQUENCY_HZ             UINT32_C(400000000)
#define TARGET_HAS_FPU                      1
#define TARGET_HAS_DOUBLE_PRECISION_FPU     1
#endif

#endif
