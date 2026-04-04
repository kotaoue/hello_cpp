cmake_minimum_required(VERSION 3.16)
project(character_encoding_tests CXX)

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

add_library(encoding_converter STATIC src/encoding_converter.cpp)
target_include_directories(encoding_converter PUBLIC src)

# --- テスト ---

enable_testing()
include(GoogleTest)

add_executable(test_encoding_converter test/test_encoding_converter.cpp)
target_include_directories(test_encoding_converter PRIVATE src)
target_link_libraries(test_encoding_converter PRIVATE encoding_converter GTest::gtest_main)
gtest_discover_tests(test_encoding_converter)
