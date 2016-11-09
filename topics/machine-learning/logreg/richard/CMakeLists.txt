CMAKE_MINIMUM_REQUIRED(VERSION 3.1.3)
PROJECT("linear_regression")
set(CMAKE_BUILD_TYPE Debug)
set (CMAKE_CXX_STANDARD 11)
ADD_DEFINITIONS("-Wall")

FIND_PACKAGE( wxWidgets COMPONENTS core base html adv net aui xrc qa richtext REQUIRED )

FIND_PACKAGE( wxfreechart REQUIRED )
include_directories(${wxfreechart_INCLUDE_DIRS})

# wxWidgets include (this will do all the magic to configure everything)
include( "${wxWidgets_USE_FILE}" )

FIND_PACKAGE( Armadillo REQUIRED )
FIND_PACKAGE( Boost REQUIRED COMPONENTS serialization)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
FIND_PACKAGE( Mlpack REQUIRED )

set(SRCS
    #main.cpp
    MyApp.cpp
    MyFrame.cpp
    MyFrame_generated.cpp
    PricePublisher.cpp
    XYChart.cpp
)

ADD_EXECUTABLE (linear_regression ${SRCS})
TARGET_LINK_LIBRARIES(linear_regression
    ${Mlpack_LIBRARIES}
    ${ARMADILLO_LIBRARIES}
    ${Boost_LIBRARIES}
    ${wxWidgets_LIBRARIES}
    ${wxfreechart_LIBRARIES} )
