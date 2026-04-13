cmake_minimum_required(VERSION 3.16)
project(cpp_class CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Google Test を FetchContent で取得 ---

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP ON
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# --- プロダクションコード ---

add_library(shape  STATIC src/shape.cpp)
add_library(buffer STATIC src/buffer.cpp)

target_include_directories(shape  PUBLIC include)
target_include_directories(buffer PUBLIC include)

# --- デモ実行ファイル ---

add_executable(cpp_class_demo src/main.cpp)
target_link_libraries(cpp_class_demo PRIVATE shape buffer)

# --- テスト ---

enable_testing()
include(GoogleTest)

add_executable(test_class test/test_class.cpp)
target_link_libraries(test_class PRIVATE shape buffer GTest::gtest_main)
gtest_discover_tests(test_class)
