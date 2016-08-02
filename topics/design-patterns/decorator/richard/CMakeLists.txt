CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT("Decorator Pattern: Initial Design")

set (CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE (DecoratorBroken DecoratorBroken.cpp)
ADD_EXECUTABLE (DecoratorFixed DecoratorFixed.cpp)
ADD_EXECUTABLE (EarlyBinding EarlyBinding.cpp)
ADD_EXECUTABLE (LateBinding LateBinding.cpp)
