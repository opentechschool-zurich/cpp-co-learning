SET(box2d-rolling-sources
    main.cpp
    game.cpp
    world/barrel.cpp
    world/ground.cpp
    world/worldcontactlistener.cpp
)


ADD_EXECUTABLE(box2d-rolling ${box2d-rolling-sources})

# set include directories
TARGET_INCLUDE_DIRECTORIES(box2d-rolling PUBLIC
		${SFML_INCLUDE_DIRS}
		${BOX2D_INCLUDE_DIRS}
		${CMAKE_CURRENT_SOURCE_DIR}
		${CMAKE_SOURCE_DIR}
)

# set_property(TARGET sfml-demo PROPERTY CXX_STANDARD 11)
# set_property(TARGET sfml-demo PROPERTY CXX_STANDARD_REQUIRED ON)

# link our target
TARGET_LINK_LIBRARIES(box2d-rolling LINK_PUBLIC
		${SFML_LIBRARIES}
		${BOX2D_LIBRARIES}
)


