#pragma once

#include "tileView.h"
#include <map>
#include "tileType.h"
#include <iostream>

namespace SlidingTiles {
/**
 * A tile on the board
 */
class Tile {
    public:
        TileView tileView;

        void setTilePosition( sf::Vector2i newGameBoardPosition ) {
            tileView.setCoordinates( RenderingSingleton::getInstance().calculateCoordinates( newGameBoardPosition)) ;
        }

        bool transition(sf::Vector2i newGameBoardPosition);
        void setTileType(TileType newType);
        void setTileType(char c);
        TileType getTileType() { return tileType; };
        bool winner {false};
        bool isMoveable {false};

    private:
        /**
        * @brief The type of the tile
        */
        TileType tileType {TileType::Empty};

        /**
        * @brief sets the isMoveable flag based on the type of tile
        */
        void setMoveable(TileType newType);
};

} // namespace SlidingTiles
