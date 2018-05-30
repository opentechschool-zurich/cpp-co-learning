cmake_minimum_required(VERSION 3.2)
project(async-threaded)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)

find_package (Threads)

add_executable(async-threaded main.cpp)

target_link_libraries (async-threaded ${CMAKE_THREAD_LIBS_INIT})
