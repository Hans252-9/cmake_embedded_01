set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/platform.c
)

set(LIBRARY_NAME platform)

add_library(${LIBRARY_NAME} STATIC ${SOURCE_FILES})
target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${LIBRARY_NAME} PRIVATE 
    include_headers
    project_features
    project_config
)

set_project_warnings(${LIBRARY_NAME})