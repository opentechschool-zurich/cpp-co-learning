CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT("My funky drill")

ADD_DEFINITIONS("-std=c++11 -lfltk")

FIND_PACKAGE(FLTK REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories("graphicscode/")

ADD_EXECUTABLE (myproject
  firstexample.cpp 
  graphicscode/Window.cpp
  graphicscode/Simple_window.cpp
  graphicscode/GUI.cpp
  graphicscode/Graph.cpp
 )


TARGET_LINK_LIBRARIES(myproject
  ${FLTK_LIBRARIES}
  )
