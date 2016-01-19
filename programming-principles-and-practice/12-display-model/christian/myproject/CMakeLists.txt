CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT("My funky drill")

ADD_DEFINITIONS("-std=c++11 -lfltk")


FIND_PACKAGE(FLTK REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories("../../guicode/")
include_directories("/home/christian/ProjektePrivat/CppLerngruppe/guicode/")

ADD_EXECUTABLE (mydrill
  firstexample.cpp  )


TARGET_LINK_LIBRARIES(mydrill
  GraphFun)
