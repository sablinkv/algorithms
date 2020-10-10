cmake_minimum_required(VERSION 3.15)

# Project detail
project(algorithms VERSION 0.0.1 LANGUAGES CXX)
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Version: ${PROJECT_VERSION}")

string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPERCASE)

# Enable Google test packeg
include(cmake/googletest.cmake)

# Project options
option(BUILD_TESTS "Building unit tests." ON)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
        $<INSTALL_INTERFACE:include>
)

# Project standard and warnings
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)

include(cmake/compiler-warnings.cmake)
set_warnings(${PROJECT_NAME})

# Alias to library
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# Install library
include(GNUInstallDirs)
install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}-targets
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    EXPORT  ${PROJECT_NAME}-targets
    FILE ${PROJECT_NAME}-targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# Add version header
configure_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/version.hpp.in
    include/${PROJECT_NAME}/version.hpp
    @ONLY
)

install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/version.hpp
  DESTINATION
    include/${PROJECT_NAME}
)

# Install the 'include' directory
install(
    DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)

# Unit test
if(BUILD_TESTS)
    build_googletest()
    enable_testing()
    add_subdirectory(test)
endif()
