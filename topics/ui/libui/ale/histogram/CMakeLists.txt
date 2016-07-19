CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT("histogram")

ADD_DEFINITIONS("-std=c++11 -Wall")

FIND_LIBRARY(UI_LIBRARY ui HINTS ${CMAKE_CURRENT_SOURCE_DIR}/libui)

ADD_EXECUTABLE (histogram-single-class
    main-single-class.cpp
)
TARGET_LINK_LIBRARIES(histogram-single-class PUBLIC ${UI_LIBRARY})

ADD_EXECUTABLE (histogram
    main.cpp
    application.cpp
    color.cpp
    datapoints.cpp
    histogram.cpp
    histogramWidget.cpp
    toolboxWidget.cpp
    window.cpp
)
TARGET_LINK_LIBRARIES(histogram PUBLIC ${UI_LIBRARY})
