CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT("escalator")

# or better "cmake -DCMAKE_BUILD_TYPE=Debug .."
set(CMAKE_BUILD_TYPE Debug)

ADD_DEFINITIONS("-std=c++11 -Wall")


FIND_PACKAGE(Threads)

ADD_EXECUTABLE (escalator
    main.cpp
)

TARGET_LINK_LIBRARIES(escalator ${CMAKE_THREAD_LIBS_INIT})
