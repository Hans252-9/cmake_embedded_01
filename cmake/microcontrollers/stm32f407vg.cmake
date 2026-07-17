set(MCU_COMPILE_OPTIONS
        -mcpu=cortex-m4
        -mthumb
        -mfpu=fpv4-sp-d16
        -mfloat-abi=hard
        -ffunction-sections
        -fdata-sections
)

set(MCU_LINK_OPTIONS
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
    -Wl,--gc-sections
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
)

set(MCU_DEFINES
    STM32F407xx
    TARGET_STM32F407VG
    TARGET_DEVICE="STM32F407VG"
)

set(LINKER_SCRIPT
    ${CMAKE_SOURCE_DIR}/cmake/linker/STM32F407VG.ld
)

set(STARTUP_FILE
    "${CMAKE_SOURCE_DIR}/cmake/startup/startup_stm32f407.c"
)
