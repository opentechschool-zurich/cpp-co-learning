CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(sawsample)

ADD_DEFINITIONS("-std=c++11")

ADD_EXECUTABLE (sawsample
    main.cpp
    saw.cpp
    dowel.cpp
)


