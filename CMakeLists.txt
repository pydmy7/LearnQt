cmake_minimum_required(VERSION 3.15)

project(LearnQt)

if (myself)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

include(cmake/findqt.cmake)
add_subdirectory(cmake)

add_subdirectory(mainwindow)
