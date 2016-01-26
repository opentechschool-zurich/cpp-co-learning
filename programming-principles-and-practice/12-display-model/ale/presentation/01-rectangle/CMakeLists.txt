CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Classes)

ADD_DEFINITIONS("-std=c++11")

# FIND_PACKAGE(FLTK REQUIRED)

ADD_EXECUTABLE (rectangle
    rectangle.cpp
    #main.cpp
    #Window.cpp
    #Simple_window.cpp
    #GUI.cpp
    #Graph.cpp
)

#TARGET_LINK_LIBRARIES(wingraph
    #${FLTK_LIBRARIES}
#)
