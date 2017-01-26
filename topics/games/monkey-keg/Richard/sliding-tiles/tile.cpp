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
    void Tile::setTileType(std::string c) {
        if (c == "-"){
            setTileType(TileType::Horizontal);
        } else if (c == "|"){
            setTileType(TileType::Vertical);

        } else if (c == "└"){
            setTileType(TileType::TopRight);
        } else if (c == "┘"){
            setTileType(TileType::LeftTop);
        } else if (c == "┐"){
            setTileType(TileType::LeftBottom);
        } else if (c == "┌"){
            setTileType(TileType::BottomRight);

        } else if (c == "├"){
            setTileType(TileType::StartRight);
        } else if (c == "┬"){
            setTileType(TileType::StartBottom);
        } else if (c == "┴"){
            setTileType(TileType::StartTop);
        } else if (c == "┤"){
            setTileType(TileType::StartLeft);

        } else if (c == "┻"){
            setTileType(TileType::EndTop);
        } else if (c == "┣"){
            setTileType(TileType::EndRight);
        } else if (c == "┫"){
            setTileType(TileType::EndLeft);
        } else if (c == "┳"){
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


    /**
    * Returns the direction coming out of the supplied tile and incoming direction.
    */
    Direction Tile::outputDirection(Direction incomingDirection) {
        if (tileType == TileType::StartRight)
            return Direction::GoRight;
        else if (tileType == TileType::StartLeft)
            return Direction::GoLeft;
        else if (tileType == TileType::StartTop)
            return Direction::GoUp;
        else if (tileType == TileType::StartBottom)
            return Direction::GoDown;
        else if (tileType == TileType::Horizontal
            && ( incomingDirection == Direction::GoRight || incomingDirection == Direction::GoLeft) )
            return incomingDirection;
        else if (tileType == TileType::Vertical
            && ( incomingDirection == Direction::GoUp || incomingDirection == Direction::GoDown) )
            return incomingDirection;
        else if (tileType == TileType::LeftBottom && incomingDirection == Direction::GoRight)
            return Direction::GoDown;
        else if (tileType == TileType::LeftBottom && incomingDirection == Direction::GoUp)
            return Direction::GoLeft;
        else if (tileType == TileType::LeftTop && incomingDirection == Direction::GoDown)
            return Direction::GoLeft;
        else if (tileType == TileType::LeftTop && incomingDirection == Direction::GoRight)
            return Direction::GoUp;
        else if (tileType == TileType::TopRight && incomingDirection == Direction::GoDown)
            return Direction::GoRight;
        else if (tileType == TileType::TopRight && incomingDirection == Direction::GoLeft)
            return Direction::GoUp;
        else if (tileType == TileType::BottomRight && incomingDirection == Direction::GoLeft)
            return Direction::GoDown;
        else if (tileType == TileType::BottomRight && incomingDirection == Direction::GoUp)
            return Direction::GoRight;
        else
            return Direction::Unknown;
    }



}
