#include "gameBoardSingleton.h"
#include <iostream>

GameBoardSingleton::GameBoardSingleton(){
}

// wierdest thing ever: The static member variable needs to be
// declared in the cpp file or the inker gets upset.
const int GameBoardSingleton::boardSize;

void GameBoardSingleton::loadGame( std::string game[GameBoardSingleton::boardSize][GameBoardSingleton::boardSize] ) {
    for (int x = 0; x < GameBoardSingleton::boardSize; ++x)
        for (int y = 0; y < GameBoardSingleton::boardSize; ++y) {
            SlidingTiles::Tile* tile = &GameBoardSingleton::getInstance().tiles[x][y];
            tile->setTilePosition(sf::Vector2i {x,y});
            tile->setTileType( game[y][x] );  // note the inversion here!
            //std::cout << "[" << x << "][" << y << "] char: " << game[x][y] << " became: " << tileTypeToString(tile->getTileType()) << "\n";
        }
}

/**
* Returns the connecting tile from the supplied tile.
* if no connecting tile is found it returns -1,-1
* if we are on an end tile it returns -2
*/
sf::Vector2i GameBoardSingleton::getNextTilePosition(sf::Vector2i tilePos, Direction incomingDirection) {
    TileType type = GameBoardSingleton::getInstance().tiles[tilePos.x][tilePos.y].getTileType();
    sf::Vector2i nextTile {tilePos.x,tilePos.y};

    if (type == TileType::StartRight)
        ++nextTile.x;
    else if (type == TileType::StartLeft)
        --nextTile.x;
    else if (type == TileType::StartTop)
        --nextTile.y;


    else if (type == TileType::StartBottom)
        ++nextTile.y;
    else if (type == TileType::Horizontal && incomingDirection == Direction::GoRight)
        ++nextTile.x;
    else if (type == TileType::Horizontal && incomingDirection == Direction::GoLeft)
        --nextTile.x;
    else if (type == TileType::Vertical && incomingDirection == Direction::GoDown)
        ++nextTile.y;
    else if (type == TileType::Vertical && incomingDirection == Direction::GoUp)
        --nextTile.y;
    else if (type == TileType::LeftBottom && incomingDirection == Direction::GoRight)
        ++nextTile.y;
    else if (type == TileType::LeftBottom && incomingDirection == Direction::GoUp)
        --nextTile.x;
    else if (type == TileType::LeftTop && incomingDirection == Direction::GoDown)
        --nextTile.x;
    else if (type == TileType::LeftTop && incomingDirection == Direction::GoRight)
        --nextTile.y;
    else if (type == TileType::BottomRight && incomingDirection == Direction::GoUp)
        ++nextTile.x;
    else if (type == TileType::BottomRight && incomingDirection == Direction::GoLeft)
        ++nextTile.y;
    else if (type == TileType::TopRight && incomingDirection == Direction::GoLeft)
        --nextTile.y;
    else if (type == TileType::TopRight && incomingDirection == Direction::GoDown)
        ++nextTile.x;
    else if (type == TileType::EndBottom || type == TileType::EndLeft
        || type == TileType::EndRight || type == TileType::EndTop) {
        nextTile.x = -2;
        nextTile.y = -2;
    } else {
        nextTile.x = -1;
        nextTile.y = -1;
    }

    return nextTile;
}
