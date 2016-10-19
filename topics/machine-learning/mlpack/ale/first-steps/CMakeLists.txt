CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT("first-steps")

# or better "cmake -DCMAKE_BUILD_TYPE=Debug .."
set(CMAKE_BUILD_TYPE Debug)

ADD_DEFINITIONS("-std=c++11 -Wall")


ADD_EXECUTABLE (first-steps
    main.cpp
)

TARGET_LINK_LIBRARIES(first-steps
    mlpack
)
