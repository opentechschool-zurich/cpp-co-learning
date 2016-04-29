cmake_minimum_required( VERSION 2.6 )
project( HelloWorld )

SET( CMAKE_CXX_FLAGS "-std=gnu++11" )

set( SOURCE_FILES sumnumbers.cpp multnumbers.cpp)
set( UNIT_TESTS sumnumbers_test.cpp multnumbers_test.cpp)

# these steps compile and link the HelloWorld executable
add_executable( HelloWorld HelloWorld.cpp ${SOURCE_FILES} )
target_link_libraries( HelloWorld )

# these steps compile and link the unit-tests executable
enable_testing()  # gives us a make test target
add_test( all unit-tests ) # gives us a make test all target
add_subdirectory( googletest-master )
include_directories( ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} )
add_executable( unit-tests unit-tests.cpp ${SOURCE_FILES} ${UNIT_TESTS} )
target_link_libraries( unit-tests gtest gtest_main )
