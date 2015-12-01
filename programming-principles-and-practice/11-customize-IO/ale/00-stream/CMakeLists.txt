CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Punct)

ADD_DEFINITIONS("-std=c++11")

ADD_LIBRARY(punctStream PunctStream.cpp)


add_executable (punct main.cpp)
