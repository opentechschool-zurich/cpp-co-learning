CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(myexercise)

ADD_DEFINITIONS("-std=c++11")

ADD_EXECUTABLE (myexercise
    exercise_main.cpp
)

TARGET_LINK_LIBRARIES(myexercise)
