cmake_minimum_required(VERSION 3.13)

project(codecrafters-interpreter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23) # Enable the C++23 standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.cpp)

add_executable(interpreter ${SOURCE_FILES})

target_include_directories(interpreter PRIVATE src)