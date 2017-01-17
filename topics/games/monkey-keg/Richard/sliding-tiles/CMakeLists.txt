CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
PROJECT(sliding-tiles)

SET(CMAKE_CXX_STANDARD 14)

IF (UNIX)
    SET(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules/" "${CMAKE_MODULE_PATH}")
ENDIF (UNIX)

FIND_PACKAGE(SFML REQUIRED COMPONENTS graphics window audio system)

IF(BOX2D_INCLUDE_DIR)
  # Already in cache, be silent
  SET(BOX2D_FIND_QUIETLY TRUE)
ENDIF(BOX2D_INCLUDE_DIR)

FIND_PATH(BOX2D_INCLUDE_DIR Box2D/Box2D.h)

SET(BOX2D_NAMES box2d Box2d BOX2D Box2D)
FIND_LIBRARY(BOX2D_LIBRARY NAMES ${BOX2D_NAMES})

SET(BOX2D_INCLUDE_DIRS "${BOX2D_INCLUDE_DIR}")
SET(BOX2D_LIBRARIES    "${BOX2D_LIBRARY}")

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

SET(sliding-tiles-sources
    main.cpp
    game.cpp
    tile.cpp
)

ADD_EXECUTABLE(sliding-tiles ${sliding-tiles-sources})

TARGET_INCLUDE_DIRECTORIES(sliding-tiles PUBLIC
		${SFML_INCLUDE_DIRS}
		${BOX2D_INCLUDE_DIRS}
		${CMAKE_CURRENT_SOURCE_DIR}
		${CMAKE_SOURCE_DIR}
)

TARGET_LINK_LIBRARIES(sliding-tiles LINK_PUBLIC
		${SFML_LIBRARIES}
		${BOX2D_LIBRARIES}
)
