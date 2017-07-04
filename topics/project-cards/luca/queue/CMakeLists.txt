CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
PROJECT(queueTasker)

# To run with Clang:
# cmake -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_CC_COMPILER=/usr/bin/clang .. 

SET(CMAKE_CXX_STANDARD 14)

ADD_EXECUTABLE(queueTasker main.cpp)
