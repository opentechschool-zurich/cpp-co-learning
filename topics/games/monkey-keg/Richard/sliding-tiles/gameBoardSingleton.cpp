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
