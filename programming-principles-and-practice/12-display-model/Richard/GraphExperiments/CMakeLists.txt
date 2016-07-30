CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Wingraph)

set (CMAKE_CXX_STANDARD 11)

FIND_PACKAGE(FLTK REQUIRED)

ADD_EXECUTABLE (wingraph
    main.cpp
    Window.cpp
    Simple_window.cpp
    GUI.cpp
    Graph.cpp
)

TARGET_LINK_LIBRARIES(wingraph
    ${FLTK_LIBRARIES}
)

CONFIGURE_FILE(image.jpg image.jpg COPYONLY)
