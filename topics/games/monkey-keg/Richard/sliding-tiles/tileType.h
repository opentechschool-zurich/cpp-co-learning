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
std::string tileTypeToString(const TileType & t);

/**
 * @brief Returns a char for the tile type. Used for Serialisation
 */
std::string tileTypeToChar(const TileType & t);

/**
 * @brief Returns if a TileType is a start tile 
 */
bool isStartTileType(const TileType & t);

/**
 * @brief Returns if a random start TileType
 */
TileType randomStartTileType();


/**
 * @brief Returns if a TileType is an end tile 
 */
bool isEndTileType(const TileType & t);

/**
 * @brief Returns if a random end TileType
 */
TileType randomEndTileType();

/**
 * @brief Returns if a tile is a game TileType
 */
bool isGameTileType(const TileType & t);


/**
 * @brief Returns a random game TileType
 */
TileType randomGameTileType();