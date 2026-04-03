cmake_minimum_required(VERSION 3.16)
project(file_io_tests CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Google Test を FetchContent で取得 ---

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP ON
)
# Windows での runtime 設定の上書きを抑止
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# --- プロダクションコード ---

add_library(file_io STATIC src/file_io.cpp)
target_include_directories(file_io PUBLIC src)

# --- テスト ---

enable_testing()
include(GoogleTest)

add_executable(test_file_io test/test_file_io.cpp)
target_include_directories(test_file_io PRIVATE src)
target_link_libraries(test_file_io PRIVATE file_io GTest::gtest_main)
gtest_discover_tests(test_file_io)
