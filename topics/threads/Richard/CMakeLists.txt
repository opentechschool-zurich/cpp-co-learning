CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT("Threads")

set (CMAKE_CXX_STANDARD 11)
add_definitions("-D_GLIBCXX_USE_NANOSLEEP")

find_package (Threads)

ADD_EXECUTABLE (YesNoThreads YesNoThreads.cpp)

target_link_libraries(YesNoThreads ${CMAKE_THREAD_LIBS_INIT})

ADD_EXECUTABLE (YesNoThreadsMutex YesNoThreadsMutex.cpp)

target_link_libraries(YesNoThreadsMutex ${CMAKE_THREAD_LIBS_INIT})
