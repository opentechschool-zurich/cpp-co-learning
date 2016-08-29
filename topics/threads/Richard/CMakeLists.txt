CMAKE_MINIMUM_REQUIRED(VERSION 3.1.3)
PROJECT("Threads")

# since cmake 3.1.3
set (CMAKE_CXX_STANDARD 11)
# for older cmake
ADD_DEFINITIONS("-std=c++11")

find_package (Threads)

ADD_EXECUTABLE (YesNoThreads YesNoThreads.cpp)
target_link_libraries(YesNoThreads ${CMAKE_THREAD_LIBS_INIT})

ADD_EXECUTABLE (YesNoThreadsMutex YesNoThreadsMutex.cpp)
target_link_libraries(YesNoThreadsMutex ${CMAKE_THREAD_LIBS_INIT})

ADD_EXECUTABLE (escalator.prg escalator.cpp)
target_link_libraries(escalator.prg ${CMAKE_THREAD_LIBS_INIT} )
