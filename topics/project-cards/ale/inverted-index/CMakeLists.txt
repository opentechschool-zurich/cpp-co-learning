CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
PROJECT(inverted-index)

# To run with Clang:
# cmake -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_CC_COMPILER=/usr/bin/clang .. 

SET(CMAKE_CXX_STANDARD 14)

ADD_EXECUTABLE(inverted-index main.cpp)
