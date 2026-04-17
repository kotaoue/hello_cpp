cmake_minimum_required(VERSION 3.16)
project(fltk_hello CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(FLTK REQUIRED)

add_executable(fltk_hello
    main.cpp
)

target_include_directories(fltk_hello PRIVATE ${FLTK_INCLUDE_DIR})
target_link_libraries(fltk_hello PRIVATE ${FLTK_LIBRARIES})
