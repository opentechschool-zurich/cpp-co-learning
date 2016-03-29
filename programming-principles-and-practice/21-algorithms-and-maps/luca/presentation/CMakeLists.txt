CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(presentation)

ADD_DEFINITIONS("-std=c++11")

ADD_EXECUTABLE (presentation
    main.cpp
)

TARGET_LINK_LIBRARIES(presentation)
