cmake_minimum_required(VERSION 3.16)
project(concepts_generics CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- デモ実行ファイル ---

add_executable(concepts_demo
    src/main.cpp
)

target_include_directories(concepts_demo PRIVATE include)
