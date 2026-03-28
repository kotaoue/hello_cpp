cmake_minimum_required(VERSION 3.16)
project(hello_cpp_tests CXX)

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

add_library(calculator STATIC src/calculator.cpp)
target_include_directories(calculator PUBLIC src)

add_library(clock_lib STATIC src/Clock.cpp)
target_include_directories(clock_lib PUBLIC src)

# --- テスト ---

enable_testing()
include(GoogleTest)

# テスト 1: Google Test を使った Calculator のテスト
add_executable(test_calculator test/test_calculator.cpp)
target_include_directories(test_calculator PRIVATE src)
target_link_libraries(test_calculator PRIVATE calculator GTest::gtest_main)
gtest_discover_tests(test_calculator)

# テスト 2: Google Mock を使った Clock のテスト (ITimeProvider をモック化)
add_executable(test_clock test/test_clock.cpp)
target_include_directories(test_clock PRIVATE src)
target_link_libraries(test_clock PRIVATE clock_lib GTest::gtest_main GTest::gmock)
gtest_discover_tests(test_clock)
