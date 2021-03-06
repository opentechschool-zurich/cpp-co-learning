CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
PROJECT(pubsubZMQ)

# To run with Clang:
# cmake -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_CC_COMPILER=/usr/bin/clang .. 

SET(CMAKE_CXX_STANDARD 14)
IF (UNIX)
    SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}" "${CMAKE_MODULE_PATH}")
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


