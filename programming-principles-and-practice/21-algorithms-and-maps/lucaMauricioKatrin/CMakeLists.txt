CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(bob)

ADD_DEFINITIONS("-std=c++11")

ADD_EXECUTABLE (bobby
    main.cpp
)

TARGET_LINK_LIBRARIES(SetExercises)
