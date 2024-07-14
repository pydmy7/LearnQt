cmake_minimum_required(VERSION 3.15)

project(
    LearnQt
    DESCRIPTION "Learn Qt"
    VERSION 0.1.0
)

if (myself)
    set(CMAKE_C_COMPILER clang)
    set(CMAKE_CXX_COMPILER clang++)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include(cmake/findqt.cmake)
add_subdirectory(cmake)

add_subdirectory(mainwindow)
