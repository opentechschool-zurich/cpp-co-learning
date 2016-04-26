CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT("Chapter 26: testing")

ADD_DEFINITIONS("-std=c++11")


# git clone https://github.com/google/googletest.git
add_subdirectory(googletest)

include_directories(googletest/googletest/include)

ADD_EXECUTABLE (testprog
  main.cpp
  
 )

target_link_libraries( testprog gtest gtest_main)
