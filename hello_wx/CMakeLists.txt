cmake_minimum_required(VERSION 3.16)
project(wx_hello CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

add_executable(wx_hello WIN32 MACOSX_BUNDLE
    main.cpp
)

target_link_libraries(wx_hello PRIVATE ${wxWidgets_LIBRARIES})
