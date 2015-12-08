CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Wingraph)

ADD_DEFINITIONS("-std=c++11")

SET(CMAKE_INCLUDE_CURRENT_DIR ON)

ADD_EXECUTABLE (wingraph
    main.cpp
    Simple_window.cpp
    Graph.cpp
)
