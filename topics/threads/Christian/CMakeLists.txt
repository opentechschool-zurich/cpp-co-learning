CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT("Escalator Threads")

set (CMAKE_CXX_STANDARD 11)

ADD_DEFINITIONS("-std=c++11")

find_package (Threads)

ADD_EXECUTABLE (escalator.prg escalator.cpp)

target_link_libraries(escalator.prg ${CMAKE_THREAD_LIBS_INIT})
