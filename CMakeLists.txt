cmake_minimum_required(VERSION 3.15...3.31)

project(aoc-cpp
    VERSION 2024.12
    DESCRIPTION "advent-of-code in cpp."
    LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS ON)

include(./deps.cmake)

add_subdirectory(lib)
add_subdirectory(exe)
