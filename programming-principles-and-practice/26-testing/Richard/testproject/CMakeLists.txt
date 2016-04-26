cmake_minimum_required(VERSION 2.6)
project(HelloWorld)

#add_definitions("-std=c++11")
SET(CMAKE_CXX_FLAGS "-std=gnu++11")

set(FILES_TO_TEST Testable.cpp)
set(UNIT_TESTS Test.cpp)
set(MAIN_FILE main.cpp)

add_subdirectory(googletest-master)

enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(HelloWorld HelloWorld.cpp sumnumbers.cpp)
target_link_libraries(HelloWorld gtest gtest_main)

add_test( all unit-tests )
add_executable(unit-tests unit-tests.cpp)
target_link_libraries(unit-tests gtest gtest_main)
