cmake_minimum_required( VERSION 2.6 )
project( HelloWorld )

SET( CMAKE_CXX_FLAGS "-std=gnu++11" )

set( SOURCE_FILES sumnumbers.cpp multnumbers.cpp)
set( UNIT_TESTS sumnumbers_test.cpp multnumbers_test.cpp)


# these steps compile and link the HelloWorld executable
add_executable( HelloWorld HelloWorld.cpp ${SOURCE_FILES} )
target_link_libraries( HelloWorld )


# Download and unpack googletest at configure time
# see https://crascit.com/2015/07/25/cmake-gtest/
configure_file( CMakeLists.txt.in googletest-download/CMakeLists.txt )
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
add_executable( unit-tests unit-tests.cpp ${SOURCE_FILES} ${UNIT_TESTS} )
target_link_libraries( unit-tests gtest )
