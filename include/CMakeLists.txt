set(LIBRARY_NAME include_headers)

add_library(${LIBRARY_NAME} INTERFACE)
target_include_directories(${LIBRARY_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${LIBRARY_NAME} INTERFACE
    project_features
    project_warnings
    project_config
)