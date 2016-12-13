cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project(sfml_test)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED COMPONENTS graphics window audio system)
find_package(GLEW REQUIRED)
# find_package(Threads REQUIRED)

# find_package(X11 REQUIRED)	# XXX Needed for XInitThreads()
# find_package(OpenGL REQUIRED)	# XXX should be set by SFML...

# pkg_check_modules(BOX2D REQUIRED box2d)

add_subdirectory(src)
