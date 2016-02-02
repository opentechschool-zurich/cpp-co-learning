CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Menues)

ADD_DEFINITIONS("-std=c++11")

FIND_PACKAGE(FLTK REQUIRED)

ADD_EXECUTABLE (menues
    main.cpp
    Menues_window.cpp
    window-graph/Window.cpp
    window-graph/Simple_window.cpp
    window-graph/GUI.cpp
    window-graph/Graph.cpp
)

TARGET_LINK_LIBRARIES(menues
    ${FLTK_LIBRARIES}
)
# ADD_SUBDIRECTORY(window-graph)
