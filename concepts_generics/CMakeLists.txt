cmake_minimum_required(VERSION 3.20)
project(concepts_generics LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(concepts_demo
    src/main.cpp
)

target_include_directories(concepts_demo PRIVATE include)

target_compile_options(concepts_demo PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)
