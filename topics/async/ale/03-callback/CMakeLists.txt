cmake_minimum_required(VERSION 3.2)
project(async-callback)

set(CMAKE_CXX_STANDARD 17)

add_executable(async-callback
    ../shared/task.cpp
    main.cpp
)
