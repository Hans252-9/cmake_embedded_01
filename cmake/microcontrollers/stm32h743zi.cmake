set(MCU_COMPILE_OPTIONS
        -mcpu=cortex-m7
        -mthumb
        -mfpu=fpv5-d16
        -mfloat-abi=hard
        -ffunction-sections
        -fdata-sections
)

set(MCU_LINK_OPTIONS
    -mcpu=cortex-m7
    -mthumb
    -mfpu=fpv5-d16
    -mfloat-abi=hard
    -Wl,--gc-sections
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
)

set(MCU_DEFINES
    STM32H743xx
    TARGET_STM32H743ZI
    TARGET_DEVICE="STM32H743ZI"
)

set(LINKER_SCRIPT
    ${CMAKE_SOURCE_DIR}/cmake/linker/STM32H743ZI.ld
)

set(STARTUP_FILE
    "${CMAKE_SOURCE_DIR}/cmake/startup/startup_stm32h743.c"
)
