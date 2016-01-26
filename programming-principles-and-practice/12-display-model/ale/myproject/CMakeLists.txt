CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT("My funky drill")

ADD_DEFINITIONS("-std=c++11 -lfltk")


FIND_PACKAGE(FLTK REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories("graphicscode/")

ADD_EXECUTABLE (mydrill
    firstexample.cpp
    graphicscode/Simple_window.cpp
    graphicscode/Graph.cpp
    graphicscode/GUI.cpp
    graphicscode/Window.cpp
    graphicscode/Graph.cpp
)

TARGET_LINK_LIBRARIES(mydrill
    ${FLTK_LIBRARIES}
)
