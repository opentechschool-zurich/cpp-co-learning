cmake_minimum_required(VERSION 2.6)
project(repeatedWords)

add_definitions("-std=c++11")
add_executable(repeatedWords checkDouble.cpp)

target_link_libraries(repeatedWords)