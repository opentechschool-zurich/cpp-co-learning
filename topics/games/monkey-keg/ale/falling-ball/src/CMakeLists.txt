# source files
SET(falling-ball-sources
    main.cpp
)

SET(falling-ball-assets
    ${FALLINGBALL_ASSETS}/ground.png
    ${FALLINGBALL_ASSETS}/box.png
)

FILE(COPY ${falling-ball-assets} DESTINATION assets/)

ADD_EXECUTABLE(falling-ball ${falling-ball-sources})

# set include directories
TARGET_INCLUDE_DIRECTORIES(falling-ball PUBLIC
		${SFML_INCLUDE_DIRS}
		${BOX2D_INCLUDE_DIRS}
		${CMAKE_CURRENT_SOURCE_DIR}
		${CMAKE_SOURCE_DIR}
)

# set_property(TARGET sfml-demo PROPERTY CXX_STANDARD 11)
# set_property(TARGET sfml-demo PROPERTY CXX_STANDARD_REQUIRED ON)

# link our target
TARGET_LINK_LIBRARIES(falling-ball LINK_PUBLIC
		${SFML_LIBRARIES}
		${BOX2D_LIBRARIES}
)


