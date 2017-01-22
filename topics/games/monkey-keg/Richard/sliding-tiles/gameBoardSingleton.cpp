#include "gameBoardSingleton.h"

GameBoardSingleton::GameBoardSingleton(){
}

// wierdest thing ever: The static member variable needs to be
// declared in the cpp file or the inker gets upset.
const int GameBoardSingleton::boardSize;

void GameBoardSingleton::loadGame( char charGame[GameBoardSingleton::boardSize][GameBoardSingleton::boardSize] ) {
    for (int x = 0; x < GameBoardSingleton::boardSize; ++x)
        for (int y = 0; y < GameBoardSingleton::boardSize; ++y) {
            SlidingTiles::Tile* tile = &GameBoardSingleton::getInstance().tiles[x][y];
            tile->setTilePosition(sf::Vector2i {x,y});
            tile->setTileType( charGame[y][x] );
        }
}
