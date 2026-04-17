cmake_minimum_required(VERSION 3.16)
project(gtk_hello CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)

# GTK4 を優先し、なければ GTK3 を使う
pkg_check_modules(GTK4 QUIET gtk4)
if(GTK4_FOUND)
    set(GTK_INCLUDE_DIRS    ${GTK4_INCLUDE_DIRS})
    set(GTK_LIBRARY_DIRS    ${GTK4_LIBRARY_DIRS})
    set(GTK_LIBRARIES       ${GTK4_LIBRARIES})
    set(GTK_CFLAGS_OTHER    ${GTK4_CFLAGS_OTHER})
else()
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
    set(GTK_INCLUDE_DIRS    ${GTK3_INCLUDE_DIRS})
    set(GTK_LIBRARY_DIRS    ${GTK3_LIBRARY_DIRS})
    set(GTK_LIBRARIES       ${GTK3_LIBRARIES})
    set(GTK_CFLAGS_OTHER    ${GTK3_CFLAGS_OTHER})
endif()

add_executable(gtk_hello main.cpp)

target_include_directories(gtk_hello PRIVATE ${GTK_INCLUDE_DIRS})
target_link_directories(gtk_hello PRIVATE ${GTK_LIBRARY_DIRS})
target_compile_options(gtk_hello PRIVATE ${GTK_CFLAGS_OTHER})
target_link_libraries(gtk_hello PRIVATE ${GTK_LIBRARIES})
