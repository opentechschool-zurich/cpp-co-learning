project(test1)

cmake_minimum_required(VERSION 2.8)

ADD_DEFINITIONS("-std=c++11 -Wall")

aux_source_directory(. SRC_LIST)

#FIND_LIBRARY(MLPACK mlpack HINTS ${CMAKE_CURRENT_SOURCE_DIR}/libui)

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(test1 mlpack armadillo)
