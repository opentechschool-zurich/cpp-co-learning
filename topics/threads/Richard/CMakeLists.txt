CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT("Threads")

set (CMAKE_CXX_STANDARD 11)

find_package (Threads)

ADD_EXECUTABLE (YesNoThreads YesNoThreads.cpp)

target_link_libraries(YesNoThreads ${CMAKE_THREAD_LIBS_INIT})
