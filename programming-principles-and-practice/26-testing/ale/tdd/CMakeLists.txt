CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT("tdd")

ADD_DEFINITIONS("-std=c++11")

add_subdirectory(googletest)
enable_testing() # is it needed?
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


ADD_EXECUTABLE (tdd
    main.cpp
)

target_link_libraries(tdd gtest gtest_main)
