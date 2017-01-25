#pragma once

#include "tileView.h"
#include <map>
#include "tileType.h"
#include <iostream>
#include "direction.h"
#include <string>


namespace SlidingTiles {
/**
 * @brief A tile on the board
 */
class Tile {
    public:
        TileView tileView;

        void setTilePosition( sf::Vector2i newGameBoardPosition ) {
            tileView.setCoordinates( RenderingSingleton::getInstance().calculateCoordinates( newGameBoardPosition)) ;
        }

        bool transition(sf::Vector2i newGameBoardPosition);
        void setTileType(TileType newType);
        void setTileType(std::string c);
        TileType getTileType() { return tileType; };
        bool winner {false};
        bool isMoveable {false};
        Direction outputDirection(Direction incomingDirection);

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
