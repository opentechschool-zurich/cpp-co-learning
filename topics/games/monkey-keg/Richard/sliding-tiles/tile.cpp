#include "tile.h"

namespace SlidingTiles {

    /**
    * Sets the type of the tile
    * passes on the request to the tileView so that it can adjust the texture
    */
    void Tile::setTileType(TileType newType) {
        tileType = newType;
        tileView.setTexture(newType);
        setMoveable(newType);
    };

    /**
    * Sets the type of the tile based on a character code
    */
    void Tile::setTileType(char c) {
        if (c == ' ') {
            setTileType(TileType::Empty);
        } else if (c == '-'){
            setTileType(TileType::Horizontal);
        } else if (c == 'V'){
            setTileType(TileType::Vertical);

        } else if (c == 'R'){
            setTileType(TileType::TopRight);
        } else if (c == 'L'){
            setTileType(TileType::LeftTop);
        } else if (c == 'l'){
            setTileType(TileType::LeftBottom);
        } else if (c == 'r'){
            setTileType(TileType::BottomRight);

        } else if (c == 'S'){
            setTileType(TileType::StartRight);
        } else if (c == 's'){
            setTileType(TileType::StartBottom);
        } else if (c == 'T'){
            setTileType(TileType::StartTop);
        } else if (c == 't'){
            setTileType(TileType::StartLeft);

        } else if (c == 'D'){
            setTileType(TileType::EndTop);
        } else if (c == 'd'){
            setTileType(TileType::EndRight);
        } else if (c == 'E'){
            setTileType(TileType::EndLeft);
        } else if (c == 'e'){
            setTileType(TileType::EndBottom);
        } else {
            setTileType(TileType::Empty);
        }
    }


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
        sf::Vector2i newCoordiantes = RenderingSingleton::getInstance().calculateCoordinates( newGameBoardPosition );
        if (! tileView.transition(newCoordiantes) ) return false;
        return true;
    }

}
