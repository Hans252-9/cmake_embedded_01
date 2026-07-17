set(MCU_COMPILE_OPTIONS
        -mcpu=cortex-m3
        -mthumb
        -ffunction-sections
        -fdata-sections
)

set(MCU_LINK_OPTIONS
    -mcpu=cortex-m3
    -mthumb
    -Wl,--gc-sections
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
)

set(MCU_DEFINES
    STM32F103xB
    TARGET_STM32F103C8
    TARGET_DEVICE="STM32F103C8"
)

set(LINKER_SCRIPT
    ${CMAKE_SOURCE_DIR}/cmake/linker/STM32F103C8.ld
)

set(STARTUP_FILE
    "${CMAKE_SOURCE_DIR}/cmake/startup/startup_stm32f103.c"
)
