CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Tutorial)
SET(Tutorial_VERSION_MAJOR 0)
SET(Tutorial_VERSION_MINOR 2)

INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}")

option(USE_MYMATH 
        "Use tutorial provided math implementation" OFF)

IF(USE_MYMATH)
    INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/mathFunctions")
    ADD_SUBDIRECTORY(mathFunctions) 
    SET(EXTRA_LIBS ${EXTRA_LIBS} mathFunctions)
ENDIF(USE_MYMATH)

CONFIGURE_FILE(
  "${PROJECT_SOURCE_DIR}/tutorialConfig.h.in"
  "${PROJECT_BINARY_DIR}/tutorialConfig.h"
)

add_executable (tutorial tutorial.cpp)
target_link_libraries (tutorial ${EXTRA_LIBS})
