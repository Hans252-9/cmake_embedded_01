set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/motor_controller.c
    ${CMAKE_CURRENT_SOURCE_DIR}/speed_controller.c
    ${CMAKE_CURRENT_SOURCE_DIR}/temperature_filter.c
)

set(LIBRARY_NAME control)

add_library(${LIBRARY_NAME} STATIC ${SOURCE_FILES})
target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${LIBRARY_NAME} PRIVATE 
        drivers
        include_headers
        diagnostics
        platform
        project_features
        project_warnings
        project_config
)