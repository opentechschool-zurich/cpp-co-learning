CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(ClassedAcidSmiley)

set (CMAKE_CXX_STANDARD 11)

FIND_PACKAGE(FLTK REQUIRED)

ADD_EXECUTABLE (ClassedAcidSmiley
    main.cpp
    Window.cpp
    Simple_window.cpp
    GUI.cpp
    Graph.cpp
)

TARGET_LINK_LIBRARIES(ClassedAcidSmiley
    ${FLTK_LIBRARIES}
)
