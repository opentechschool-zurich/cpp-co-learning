#pragma once
#include <string>

/**
* @brief The direction you can go
*/
enum Direction {
    Unknown, GoLeft, GoRight, GoUp, GoDown
};

std::string directionToString(Direction direction);
