CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
PROJECT(sliding-tiles)

SET(CMAKE_CXX_STANDARD 14)

IF (UNIX)
    SET(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules/" "${PROJECT_SOURCE_DIR}" "${CMAKE_MODULE_PATH}")
ENDIF (UNIX)

FIND_PACKAGE(SFML REQUIRED COMPONENTS graphics window audio system)

SET(sliding-tiles_assets_dir "${PROJECT_SOURCE_DIR}/assets")
SET(sliding-tiles-assets
    ${sliding-tiles_assets_dir}/ChangaOne-Regular.ttf
    ${sliding-tiles_assets_dir}/bottomright.png
    ${sliding-tiles_assets_dir}/endbottom.png
    ${sliding-tiles_assets_dir}/endright.png
    ${sliding-tiles_assets_dir}/endtop.png
    ${sliding-tiles_assets_dir}/endleft.png
    ${sliding-tiles_assets_dir}/horizontal.png
    ${sliding-tiles_assets_dir}/leftbottom.png
    ${sliding-tiles_assets_dir}/lefttop.png
    ${sliding-tiles_assets_dir}/startbottom.png
    ${sliding-tiles_assets_dir}/startleft.png
    ${sliding-tiles_assets_dir}/startright.png
    ${sliding-tiles_assets_dir}/starttop.png
    ${sliding-tiles_assets_dir}/topright.png
    ${sliding-tiles_assets_dir}/vertical.png
    ${sliding-tiles_assets_dir}/empty.png
)
FILE(COPY ${sliding-tiles-assets} DESTINATION assets/)

SET(SOURCE_FILES
    game.cpp
    gameView.cpp
    tileView.cpp
    tile.cpp
    texturesSingleton.cpp
    renderingSingleton.cpp
    direction.cpp
    tileType.cpp
    moveNode.cpp
    gameBoard.cpp
    puzzleSolver.cpp
)

set( UNIT_TESTS
    game.tests.cpp
    gameView.tests.cpp
    tileView.tests.cpp
    tile.tests.cpp
    texturesSingleton.tests.cpp
#    gameBoardSingleton.tests.cpp
    renderingSingleton.tests.cpp
    direction.tests.cpp
    tileType.tests.cpp
    gameBoard.tests.cpp
    puzzleSolver.tests.cpp
)

ADD_EXECUTABLE(sliding-tiles main.cpp ${SOURCE_FILES})

TARGET_INCLUDE_DIRECTORIES(sliding-tiles PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}
    ${SFML_INCLUDE_DIRS}
)

TARGET_LINK_LIBRARIES(sliding-tiles LINK_PUBLIC
	${SFML_LIBRARIES}
)

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
add_executable( unit-tests test-main.cpp ${SOURCE_FILES} ${UNIT_TESTS} )
target_link_libraries( unit-tests LINK_PUBLIC gtest gmock ${SFML_LIBRARIES})


# see http://stackoverflow.com/questions/13116488/detailed-guide-on-using-gcov-with-cmake-cdash
SET(CHECK_COVERAGE ON)
if (CHECK_COVERAGE)
    SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
    include(CodeCoverage)
    setup_target_for_coverage(${PROJECT_NAME}_coverage unit-tests coverage)
ENDIF (CHECK_COVERAGE)
