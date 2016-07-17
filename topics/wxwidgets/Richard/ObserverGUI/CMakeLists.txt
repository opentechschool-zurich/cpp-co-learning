CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(ObserverGUI)

if(WIN32)
    set(wxWidgets_ROOT_DIR "C:/Users/Richard/Documents/GitHub/wxWidgets" CACHE PATH "wxWidgets base directory" FORCE)
    # If we build for windows systems, we also include the resource file
    # containing the manifest, icon and other resources
    set(wxWidgets_wxrc_EXECUTABLE "${wxWidgets_ROOT_DIR}/utils/wxrc/wxrc.rc")
endif(WIN32)

set (CMAKE_CXX_STANDARD 11)
set(ObserverGUI_STATIC ON)

FIND_PACKAGE( wxWidgets COMPONENTS core base html adv net aui xrc qa richtext REQUIRED )

# wxWidgets include (this will do all the magic to configure everything)
include( "${wxWidgets_USE_FILE}" )

include_directories("/richi/Src/freechart/include")

# For convenience we define the sources as a variable. You can add
# header files and cpp/c files and CMake will sort them out
set(SRCS
    MyApp.cpp
    MyFrame.cpp
    MyFrame_generated.cpp
    PricePublisher.cpp
    PriceObserver.cpp
    TextCtrlPriceObserver.cpp
    HighPriceObserver.cpp
    LowPriceObserver.cpp
    AvgPriceObserver.cpp
    XYChart.cpp
)


# Here we define the executable ObserverGUI.exe or DrawApplication on other systems
# the above paths and defines will be used in this build
add_executable(ObserverGUI WIN32 ${SRCS})

# We add to our target 'ObserverGUI' the wxWidgets libraries. These are
# set for us by the find script. If you need other libraries, you
# can add them here as well.
target_link_libraries(ObserverGUI ${wxWidgets_LIBRARIES} "/usr/local/lib64/libwxcode_gtk2u_freechart-3.0.so")
