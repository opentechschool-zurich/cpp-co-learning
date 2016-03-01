CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(TimingContainers)

ADD_DEFINITIONS("-std=c++11")

ADD_EXECUTABLE (TimingContainers
    main.cpp
)

TARGET_LINK_LIBRARIES(TimingContainers)
