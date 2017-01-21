#pragma once

#include "tileView.h"
#include <map>
#include "tileType.h"

namespace SlidingTiles {
/**
 * A tile on the board
 */
class Tile {
    public:

        Tile(){};  // Don't want
        Tile(
            sf::RenderWindow* window,
            int size,
            sf::Vector2i gridZeroZero,
            sf::Vector2i tileCoordinates)
            : gameBoardPosition(gameBoardPosition)
            {
                tileView.setRenderWindow(window);
                tileView.setSize(size);
                sf::Vector2i currentPosition { gridZeroZero.x + gameBoardPosition.x * size, gridZeroZero.y + gameBoardPosition.y * size};
            };

        TileView tileView;
        void setMoveable(TileType newType);
        bool transition(sf::Vector2i newGameBoardPosition);
        int getX();
        int getY();
        void setTileType(TileType newType);
        TileType getTileType() { return tileType; };
        bool winner {false};
        bool isMoveable {false};
        /**
        * The position of the tile on the game board
        */
        sf::Vector2i gameBoardPosition {-1, -1};

    private:
        /**
        * The position of the tile on the game board after the move
        */
        sf::Vector2i newGameBoardPosition {-1, -1};

        TileType tileType {TileType::Empty};
};

} // namespace SlidingTiles
