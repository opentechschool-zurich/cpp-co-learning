CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
PROJECT(FireworksApp)

if(WIN32)
    set(wxWidgets_ROOT_DIR "C:/Users/Richard/Documents/GitHub/wxWidgets" CACHE PATH "wxWidgets base directory" FORCE)
    # If we build for windows systems, we also include the resource file
    # containing the manifest, icon and other resources
    set(wxWidgets_wxrc_EXECUTABLE "${wxWidgets_ROOT_DIR}/utils/wxrc/wxrc.rc")
endif(WIN32)

set (CMAKE_CXX_STANDARD 14)

FIND_PACKAGE( wxWidgets COMPONENTS core base html adv net aui xrc qa richtext REQUIRED )

# wxWidgets include (this will do all the magic to configure everything)
include( "${wxWidgets_USE_FILE}" )

# For convenience we define the sources as a variable. You can add
# header files and cpp/c files and CMake will sort them out
set(SRCS
    FireworksApp.cpp
    Circle.cpp
    BasicDrawPane.cpp
    StraightLinePositionCalculator.cpp
)

# Here we define the executable DrawApplication.exe or DrawApplication on other systems
# the above paths and defines will be used in this build
add_executable(FireworksApp WIN32 ${SRCS})

# We add to our target 'DrawApplication' the wxWidgets libraries. These are
# set for us by the find script. If you need other libraries, you
# can add them here as well.
target_link_libraries(FireworksApp ${wxWidgets_LIBRARIES})
