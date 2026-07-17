cmake_minimum_required(VERSION 3.13)
project(TEST_11 LANGUAGES C)

set(CMAKE_EXECUTABLE_SUFFIX ".elf")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT DEFINED MCU)
    message(FATAL_ERROR
        "MCU is not selected. Use "
        "-DMCU=XXXXXXX"
    )
endif()

set(MCU_CONFIG_FILE
    "${CMAKE_SOURCE_DIR}/cmake/microcontrollers/${MCU}.cmake"
)

if(NOT EXISTS "${MCU_CONFIG_FILE}")
    message(FATAL_ERROR
        "Unsupported MCU '${MCU}'. Supported values: "
        "stm32f103c8, stm32f407vg, stm32h743zi"
    )
endif()

include("${MCU_CONFIG_FILE}")

if(NOT EXISTS "${STARTUP_FILE}")
    message(FATAL_ERROR "Startup file does not exist: ${STARTUP_FILE}")
endif()

if(NOT EXISTS "${LINKER_SCRIPT}")
    message(FATAL_ERROR "Linker script does not exist: ${LINKER_SCRIPT}")
endif()

message(STATUS "Selected MCU: ${MCU}")
message(STATUS "Startup file: ${STARTUP_FILE}")
message(STATUS "Linker script: ${LINKER_SCRIPT}")

add_library(project_features INTERFACE)
target_compile_features(project_features INTERFACE c_std_11)

add_library(project_warnings INTERFACE)
target_compile_options(project_warnings INTERFACE
        -Wall
        -Wextra
        -Wpedantic
        )

add_library(project_config INTERFACE)
target_compile_options(project_config INTERFACE
        ${MCU_COMPILE_OPTIONS}
        )

target_compile_definitions(project_config INTERFACE
        ${MCU_DEFINES}
        )

target_link_options(project_config INTERFACE
        ${MCU_LINK_OPTIONS}
        )

add_subdirectory("include")
add_subdirectory(platform)
add_subdirectory(drivers)
add_subdirectory(diagnostics)
add_subdirectory(control)

add_executable(main
        ${CMAKE_CURRENT_SOURCE_DIR}/app/main.c 
        ${STARTUP_FILE}
        )

target_link_libraries(main PRIVATE
        control
        project_features
        project_warnings
        project_config
        )

target_link_options(main PRIVATE
    -T${LINKER_SCRIPT}
    --specs=nosys.specs
    -nostartfiles
)
