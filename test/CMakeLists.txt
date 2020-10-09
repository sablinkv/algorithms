cmake_minimum_required(VERSION 3.15)

set(SOURCES
    test_sort.cpp
)

set(HEADERS
    include/tools.hpp
)

foreach(FILE ${SOURCES})
    string(REPLACE ".cpp" "" NAME ${FILE})
    string(TOUPPER ${NAME} NAME_UPPERCASE)

    add_executable(${NAME_UPPERCASE}
        src/${FILE}
        ${HEADERS}
    )
    
    target_compile_features(${NAME_UPPERCASE} PUBLIC cxx_std_17)
    target_link_libraries(${NAME_UPPERCASE}
            ${PROJECT_NAME} 
            gtest_main
    )

    target_include_directories(${NAME_UPPERCASE} PUBLIC ${PROJECT_SOURCE_DIR}/include)

    add_test(
        NAME ${NAME_UPPERCASE}
        COMMAND ${NAME_UPPERCASE}
    )

    message(STATUS "Unit test ${NAME_UPPERCASE} added")
endforeach()