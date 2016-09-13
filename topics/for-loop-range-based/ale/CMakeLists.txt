CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT("for-loop")

# or better "cmake -DCMAKE_BUILD_TYPE=Debug .."
set(CMAKE_BUILD_TYPE Debug)

ADD_DEFINITIONS("-std=c++11 -Wall")


ADD_EXECUTABLE (introduction
    01-introduction.cpp
)

ADD_EXECUTABLE (type-deduction
    02-automatic-type-deduction.cpp
)
