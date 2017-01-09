CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
PROJECT(falling-smileys)

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

SET(falling-smileys_assets_dir "${PROJECT_SOURCE_DIR}/assets")
SET(falling-smileys-assets
    ${falling-smileys_assets_dir}/box.png
    ${falling-smileys_assets_dir}/ChangaOne-Regular.ttf
)
FILE(COPY ${falling-smileys-assets} DESTINATION assets/)

SET(falling-smileys-sources
    main.cpp
    game.cpp
)

ADD_EXECUTABLE(falling-smileys ${falling-smileys-sources})

TARGET_INCLUDE_DIRECTORIES(falling-smileys PUBLIC
		${SFML_INCLUDE_DIRS}
		${BOX2D_INCLUDE_DIRS}
		${CMAKE_CURRENT_SOURCE_DIR}
		${CMAKE_SOURCE_DIR}
)

TARGET_LINK_LIBRARIES(falling-smileys LINK_PUBLIC
		${SFML_LIBRARIES}
		${BOX2D_LIBRARIES}
)
