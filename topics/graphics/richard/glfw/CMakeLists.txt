CMAKE_MINIMUM_REQUIRED(VERSION 3.1.3)
PROJECT("HelloGlfw")
set(CMAKE_BUILD_TYPE Debug)
set (CMAKE_CXX_STANDARD 11)
ADD_DEFINITIONS("-Wall")

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW3 REQUIRED glfw3)
#include_directories(${GLFW3_INCLUDE_DIRS} /richi/Src/glad/build/include/ /richi/Src/glfw/deps/)

message("GLFW3_INCLUDE_DIR: " ${GLFW3_INCLUDE_DIR})
message("GLFW3_LIBRARIES: " ${GLFW3_LIBRARIES})
message("GLFW3_LIBRARIES: " ${GLFW3_STATIC_LIBRARIES})

find_package(OpenGL REQUIRED)
message("OpenGL was found: " ${OPENGL_FOUND})
message("OPENGL_gl_LIBRARY: " ${OPENGL_gl_LIBRARY})
#include_directories(${OPENGL_INCLUDE_DIR})

find_package(X11 REQUIRED)

set(SRCS
    main.cpp
)

ADD_EXECUTABLE (HelloGlfw ${SRCS})
#target_include_directories(HelloGlfw ${OPENGL_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(HelloGlfw
#    GLEW glfw3 GL X11 Xi Xrandr Xxf86vm Xinerama Xcursor dl pthread
    ${GLFW3_STATIC_LIBRARIES}

#    ${OPENGL_gl_LIBRARY}
#    ${OPENGL_glu_LIBRARY}
#    ${GLFW3_LIBRARIES}
)

#message ("Debug this:")
#FOREACH(item ${GLFW3_STATIC_LIBRARIES} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${X11_LIBRARIES})
#     MESSAGE(STATUS "  using lib: " ${item})
#ENDFOREACH()
