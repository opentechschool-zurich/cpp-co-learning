CMAKE_MINIMUM_REQUIRED(VERSION 3.1.3)
PROJECT("linear_regression")
set(CMAKE_BUILD_TYPE Debug)
set (CMAKE_CXX_STANDARD 11)
ADD_DEFINITIONS("-Wall")

ADD_EXECUTABLE (linear_regression main.cpp)
TARGET_LINK_LIBRARIES(linear_regression mlpack armadillo boost_serialization)
