SET(monkey-keg-sources
    main.cpp
    game.cpp
    SFMLDebugDraw.cpp
    world/barrel.cpp
    world/ground.cpp
    world/polygon.cpp
    world/worldcontactlistener.cpp
    decoration/text.cpp
)


ADD_EXECUTABLE(monkey-keg ${monkey-keg-sources})

# set include directories
TARGET_INCLUDE_DIRECTORIES(monkey-keg PUBLIC
		${SFML_INCLUDE_DIRS}
		${BOX2D_INCLUDE_DIRS}
		${CMAKE_CURRENT_SOURCE_DIR}
		${CMAKE_SOURCE_DIR}
)

# set_property(TARGET sfml-demo PROPERTY CXX_STANDARD 11)
# set_property(TARGET sfml-demo PROPERTY CXX_STANDARD_REQUIRED ON)

# link our target
TARGET_LINK_LIBRARIES(monkey-keg LINK_PUBLIC
		${SFML_LIBRARIES}
		${BOX2D_LIBRARIES}
)


