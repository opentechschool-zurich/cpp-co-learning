#pragma once
#include <string>

enum TileType {
    Empty,
    Horizontal,
    Vertical,
    StartTop,
    StartBottom,
    StartLeft,
    StartRight,
    EndTop,
    EndBottom,
    EndRight,
    EndLeft,
    LeftTop,
    LeftBottom,
    TopRight,
    BottomRight
};

/**
* @brief Returns a string of the tile type. Helpful for debugging
*/
std::string tileTypeToString( TileType t);
