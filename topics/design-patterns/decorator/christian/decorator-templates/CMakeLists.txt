CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT("Decorator")

# or better "cmake -DCMAKE_BUILD_TYPE=Debug .."
set(CMAKE_BUILD_TYPE Debug)

ADD_DEFINITIONS("-std=c++11 -Wall")

ADD_EXECUTABLE (decorator
    main.cpp
)
