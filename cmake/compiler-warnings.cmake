macro(set_warnings project_name)
    set(MSVC_WARNINGS /W4)

    set(CLANG_WARNINGS
        -Wall -Wextra -Wshadow -Wpedantic
    )

    set(GCC_WARNINGS ${CLANG_WARNINGS})

    if(MSVC)
        set(PROJECT_WARNINGS ${MSVC_WARNINGS})
    elseif(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
        set(PROJECT_WARNINGS ${CLANG_WARNINGS})
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(PROJECT_WARNINGS ${GCC_WARNINGS})
    else()
        message(AUTHOR_WARNING "No compiler warnings set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
    endif()

    target_compile_options(${project_name} INTERFACE ${PROJECT_WARNINGS})
    
endmacro()