CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
PROJECT(ZeroMQ)

# To run with Clang:
# cmake -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_CC_COMPILER=/usr/bin/clang .. 

SET(CMAKE_CXX_STANDARD 14)
IF (WIN32)
  SET(SFML_ROOT "C:/Users/Richard/Documents/SFML-2.4.2")
  SET(CMAKE_MODULE_PATH "${SFML_ROOT}/cmake/Modules" "${PROJECT_SOURCE_DIR}" "${CMAKE_MODULE_PATH}")
  message( STATUS "CMAKE_GENERATOR: ${CMAKE_GENERATOR}")
  message( STATUS "CMAKE_CL_64: ${CMAKE_CL_64}")
ENDIF (WIN32)
IF (UNIX)
    SET(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules/" "${PROJECT_SOURCE_DIR}" "${CMAKE_MODULE_PATH}")
ENDIF (UNIX)


find_package(ZeroMQ)



ADD_EXECUTABLE(hwserver hwserver.cpp)

TARGET_INCLUDE_DIRECTORIES(hwserver PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}
    ${ZeroMQ_INCLUDE_DIR}
)

TARGET_LINK_LIBRARIES(hwserver LINK_PUBLIC
    ${ZeroMQ_LIBRARIES}
)


ADD_EXECUTABLE(hwclient hwclient.cpp)

TARGET_INCLUDE_DIRECTORIES(hwclient PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}
    ${ZeroMQ_INCLUDE_DIR}
)

TARGET_LINK_LIBRARIES(hwclient LINK_PUBLIC
    ${ZeroMQ_LIBRARIES}
)


IF (WIN32)
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ZeroMQ)
  set_target_properties(hwserver PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY $(Configuration))
ENDIF (WIN32)


# Download and unpack googletest at configure time
# see https://crascit.com/2015/07/25/cmake-gtest/
# copy the CMakeLists.txt.in to build area as CMakeLists.txt
configure_file( CMakeLists.txt.in googletest-download/CMakeLists.txt )
# we need to execute the build steps at config time so that
# the tests can find the gtest libraries when they configure
execute_process( COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process( COMMAND ${CMAKE_COMMAND} --build .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set( gtest_force_shared_crt ON CACHE BOOL "" FORCE )

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory( ${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build )

# these steps compile and link the unit-tests executable
enable_testing()  # gives us a make test target
add_test( all unit-tests ) # gives us a make test all target
add_executable( unit-tests test-main.cpp test-main.cpp )
TARGET_INCLUDE_DIRECTORIES( unit-tests PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}
    ${ZeroMQ_INCLUDE_DIR}
)
target_link_libraries( unit-tests LINK_PUBLIC
    gtest gmock ${ZeroMQ_LIBRARIES}
)



