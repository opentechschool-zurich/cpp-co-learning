project(myobserver)
cmake_minimum_required(VERSION 2.8)

ADD_DEFINITIONS("-std=c++11")

aux_source_directory(. SRC_LIST)

add_executable(${PROJECT_NAME} ${SRC_LIST})

