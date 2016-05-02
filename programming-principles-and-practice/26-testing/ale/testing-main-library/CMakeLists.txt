CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT("sumandtest")

SET(CMAKE_CXX_FLAGS "-std=gnu++11")

ADD_EXECUTABLE (sum
    main.cpp
    numbers.cpp
)

ADD_SUBDIRECTORY(googletest)
ENABLE_TESTING()
INCLUDE_DIRECTORIES(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


ADD_EXECUTABLE (sum-test
    main-test.cpp
    numbers.cpp
)

TARGET_LINK_LIBRARIES(sum-test gtest gtest_main)

ADD_TEST(NAME SumOfIntTest COMMAND sum-test)
