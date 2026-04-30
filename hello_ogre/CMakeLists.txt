cmake_minimum_required(VERSION 3.16)
project(ogre_hello CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ubuntu/Debian の標準インストールパスを hint として追加
list(APPEND CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/OGRE/cmake")

find_package(OGRE REQUIRED COMPONENTS Bites RTShaderSystem)

add_executable(ogre_hello main.cpp)

target_link_libraries(ogre_hello PRIVATE OgreMain OgreBites OgreRTShaderSystem)
