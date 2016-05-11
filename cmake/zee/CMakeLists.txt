  cmake_minimum_required(VERSION 2.6)
  project(helloWorld)
  
  add_definitions("-std=c++11")
  add_executable(helloWorld main.cpp)
  
  target_link_libraries(helloWorld)