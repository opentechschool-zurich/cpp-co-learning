#include "tile.h"

namespace SlidingTiles {

    int Tile::getX() {
        return gameBoardPosition.x;
    }

    int Tile::getY() {
        return gameBoardPosition.y;
    }

    /**
    * Sets the type of the tile
    * passes on the request to the tileView so that it can adjust the texture
    */
    void Tile::setTileType(TileType newType) {
        tileType = newType;
        tileView.setTexture(newType);
    };

    void Tile::setMoveable(TileType newType) {
    if ( newType == TileType::Empty
        || newType == TileType::StartBottom
        || newType == TileType::StartTop
        || newType == TileType::StartLeft
        || newType == TileType::StartRight
        || newType == TileType::EndBottom
        || newType == TileType::EndTop
        || newType == TileType::EndLeft
        || newType == TileType::EndRight)
        isMoveable = false;
    else
        isMoveable = true;
    };

    bool Tile::transition(sf::Vector2i newGameBoardPosition) {
        sf::Vector2i gridZeroZero {100,100};
        int size = 60;
        sf::Vector2i newCoordiantes { gridZeroZero.x + newGameBoardPosition.x * size, gridZeroZero.y + newGameBoardPosition.y * size};
        if (! tileView.transition(newCoordiantes) ) return false;
        this->newGameBoardPosition = newGameBoardPosition;
        return true;
    }

}
