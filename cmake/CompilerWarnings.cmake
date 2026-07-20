function(set_project_warnings target_name)

    if(NOT TARGET ${target_name})
        message(FATAL_ERROR
            "set_project_warnings: Target '${target_name}' does not exist"
        )
    endif()

    if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
        target_compile_options(${target_name} PRIVATE
            -Wall
            -Wextra
            -Wpedantic
        )

    elseif(CMAKE_C_COMPILER_ID MATCHES "Clang")
        target_compile_options(${target_name} PRIVATE
            -Wall
            -Wextra
            -Wpedantic
        )

    elseif(MSVC)
        target_compile_options(${target_name} PRIVATE
            /W4
        )

    else()
        message(WARNING
            "No warning configuration defined for compiler: "
            "${CMAKE_C_COMPILER_ID}"
        )
    endif()

endfunction()