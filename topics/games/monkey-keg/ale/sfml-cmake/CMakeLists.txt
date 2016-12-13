CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
PROJECT(sfml_test)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

IF (UNIX)
    SET(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules/" "${CMAKE_MODULE_PATH}")
ENDIF (UNIX)

SET(CMAKE_CXX_STANDARD 14)

FIND_PACKAGE(SFML REQUIRED COMPONENTS graphics window audio system)
FIND_PACKAGE(GLEW REQUIRED)
# find_package(Threads REQUIRED)

# find_package(X11 REQUIRED)	# XXX Needed for XInitThreads()
# find_package(OpenGL REQUIRED)	# XXX should be set by SFML...

# pkg_check_modules(BOX2D REQUIRED box2d)

add_subdirectory(src)
