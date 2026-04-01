cmake_minimum_required(VERSION 3.16)
project(external_api CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- libcurl を検索する ---
find_package(CURL REQUIRED)

# --- デモ実行ファイル ---

add_executable(external_api_demo
    src/http_client.cpp
    src/main.cpp
)

target_include_directories(external_api_demo PRIVATE include)
target_link_libraries(external_api_demo PRIVATE CURL::libcurl)
