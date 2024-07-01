cmake_minimum_required(VERSION 3.15)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
    LearnQt
    DESCRIPTION "Learn Qt"
    VERSION 0.1.0
)

include(cmake/findqt.cmake)

add_subdirectory(cmake)
add_subdirectory(test)
