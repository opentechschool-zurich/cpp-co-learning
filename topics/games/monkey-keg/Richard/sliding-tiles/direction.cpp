#include "direction.h"

std::string SlidingTiles::directionToString(Direction direction) {
    if ( direction == Direction::GoDown )
        return "GoDown";
    else if ( direction == Direction::GoRight )
        return "GoRight";
    else if ( direction == Direction::GoUp )
        return "GoUp";
    else if ( direction == Direction::GoLeft )
        return "GoLeft";
    else
        return "Unknown";
}
