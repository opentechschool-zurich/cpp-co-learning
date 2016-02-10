CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(godexample)

ADD_DEFINITIONS("-std=c++11")

FIND_PACKAGE(FLTK REQUIRED)

ADD_EXECUTABLE (godexample
    main.cpp
    Link.h
)
# 
 TARGET_LINK_LIBRARIES(godexample)
#     ${FLTK_LIBRARIES}
#     dl
# )
