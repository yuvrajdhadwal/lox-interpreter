cmake_minimum_required(VERSION 3.13)

project(lox_interpreter VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23) # Enable the C++23 standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lox_interpreter 
    src/main.cpp
    src/scanning/scanning_utils.cpp)

target_include_directories(lox_interpreter PRIVATE
    include
    )

target_compile_options(lox_interpreter PRIVATE
    $<$<CONFIG:Debug>:-fdiagnostics-color=always>
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Debug>:-ggdb>
    $<$<CONFIG:Debug>:-Wall>
    $<$<CONFIG:Debug>:-Weffc++>
    $<$<CONFIG:Debug>:-Wextra>
    $<$<CONFIG:Debug>:-Wconversion>
    $<$<CONFIG:Debug>:-Wsign-conversion>
    $<$<CONFIG:Debug>:-Werror>
    $<$<CONFIG:Debug>:-Wshadow>
    $<$<CONFIG:Debug>:-Wpedantic>
    $<$<CONFIG:Debug>:-pedantic-errors>
)
