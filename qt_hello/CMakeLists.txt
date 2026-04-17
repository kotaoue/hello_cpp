cmake_minimum_required(VERSION 3.16)
project(qt_hello CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt6 を優先し、なければ Qt5 を使う
find_package(Qt6 QUIET COMPONENTS Widgets)
if(Qt6_FOUND)
    set(QT_VERSION_MAJOR 6)
else()
    find_package(Qt5 REQUIRED COMPONENTS Widgets)
    set(QT_VERSION_MAJOR 5)
endif()

set(CMAKE_AUTOMOC ON)

add_executable(qt_hello
    main.cpp
)

target_link_libraries(qt_hello PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
