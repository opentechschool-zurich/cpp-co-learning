#include "gameBoard.h"
#include <stdlib.h>  // srand, rand
#include <algorithm>    // std::shuffle
#include <random> // random_shuffle, std::default_random_engine
#include <chrono>       // std::chrono::system_clock

using namespace SlidingTiles;

// wierdest thing ever: The static member variable needs to be
// declared in the cpp file or the inker gets upset.
const int GameBoard::boardSize;

void GameBoard::loadGame(const std::string game[boardSize][boardSize]) {
    for (int x = 0; x < boardSize; ++x) {
        for (int y = 0; y < boardSize; ++y) {
            SlidingTiles::Tile* tile = &tiles[x][y];
            tile->setTilePosition(sf::Vector2i{x, y});
            tile->setTileType(game[y][x]); // note the inversion here!
            //std::cout << "[" << x << "][" << y << "] char: " << game[x][y] << " became: " << tileTypeToString(tile->getTileType()) << "\n";
        }
    }
}

void GameBoard::loadGame(const std::vector<std::string> & game) {
    for (int y = 0; y < boardSize; ++y) {
        for (int x = 0; x < boardSize; ++x) {
            SlidingTiles::Tile* tile = &tiles[x][y];
            tile->setTilePosition(sf::Vector2i{x, y});
            tile->setTileType(game[y * 4 + x]);
            //std::cout << "[" << x << "][" << y << "] game[y*4+x]: " << game[y*4+x] << " became: " << tileTypeToString(tile->getTileType()) << "\n";
        }
    }
}

void GameBoard::randomGame(const int & emptyTiles) {
    std::vector<sf::Vector2i> positions{};
    for (int x = 0; x < boardSize; ++x) {
        for (int y = 0; y < boardSize; ++y) {
            positions.push_back(sf::Vector2i{x, y});
        }
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(std::begin(positions), std::end(positions), std::default_random_engine(seed));

    sf::Vector2i startPos = positions[0];
    Tile startTile{};
    startTile.setTilePosition(startPos);
    startTile.setTileType(randomStartTileType());
    tiles[startPos.x][startPos.y] = startTile;

    sf::Vector2i endPos = positions[1];
    Tile endTile{};
    endTile.setTilePosition(endPos);
    endTile.setTileType(randomEndTileType());
    tiles[endPos.x][endPos.y] = endTile;

    for (int i = 0; i < emptyTiles; ++i) {
        sf::Vector2i emptyPos = positions[2 + i];
        Tile emptyTile{};
        emptyTile.setTilePosition(emptyPos);
        emptyTile.setTileType(TileType::Empty);
        tiles[emptyPos.x][emptyPos.y] = emptyTile;
    }

    int totalTiles = boardSize * boardSize;
    for (int i = 2 + emptyTiles; i < totalTiles; ++i) {
        TileType tileType{TileType::Empty};
        switch (rand() % 6) {
            case 0: tileType = TileType::Horizontal;
                break;
            case 1: tileType = TileType::Vertical;
                break;
            case 2: tileType = TileType::LeftTop;
                break;
            case 3: tileType = TileType::LeftBottom;
                break;
            case 4: tileType = TileType::TopRight;
                break;
            case 5: tileType = TileType::BottomRight;
                break;
        }
        sf::Vector2i tilePos = positions[i];
        Tile tile{};
        tile.setTilePosition(tilePos);
        tile.setTileType(tileType);
        tiles[tilePos.x][tilePos.y] = tile;
    }
}

std::vector<std::string> GameBoard::serialiseGame() {
    std::vector<std::string> serialisedGame;
    for (int y = 0; y < boardSize; ++y) {
        for (int x = 0; x < boardSize; ++x) {
            serialisedGame.push_back(tileTypeToChar(tiles[x][y].getTileType()));
        }
    }
    return serialisedGame;
}

void GameBoard::printGame() {
    for (int y = 0; y < boardSize; ++y) {
        for (int x = 0; x < boardSize; ++x) {
            std::cout << tileTypeToChar(tiles[x][y].getTileType());
        }
        std::cout << std::endl;
    }
}

sf::Vector2i GameBoard::getAdjacentTilePosition(const Move & move) {
    sf::Vector2i adjacentPosition{move.startPosition.x, move.startPosition.y};

    if (move.direction == Direction::GoDown) {
        ++adjacentPosition.y;
    } else if (move.direction == Direction::GoUp)
        --adjacentPosition.y;
    else if (move.direction == Direction::GoLeft)
        --adjacentPosition.x;
    else if (move.direction == Direction::GoRight)
        ++adjacentPosition.x;

    if (adjacentPosition.y < 0 || adjacentPosition.x < 0 || adjacentPosition.x >= boardSize || adjacentPosition.x >= boardSize) {
        adjacentPosition.x = -1;
        adjacentPosition.y = -1;
    }
    return adjacentPosition;
}

bool GameBoard::canSlideTile(const Move & move) {
    SlidingTiles::Tile movingTile = tiles[move.startPosition.x][move.startPosition.y];
   /*std::cout << "canSlideTile: [" << move.startPosition.x << "][" << move.startPosition.y
            << "] Direction: " << directionToString(move.direction) << "\n";*/
    if (!movingTile.isMoveable)
        return false;

    sf::Vector2i newPosition = getAdjacentTilePosition(move);
    // check for move off the board
    if (newPosition.x >= boardSize
            || newPosition.y >= boardSize
            || newPosition.x < 0
            || newPosition.y < 0)
        return false;

    // check if newPosition already taken
    if (tiles[newPosition.x][newPosition.y].getTileType() != TileType::Empty)
        return false;

    return true;
}

void GameBoard::slideTile(const Move & move) {
    if (canSlideTile(move)) {
        sf::Vector2i newPosition = getAdjacentTilePosition(move);
        SlidingTiles::Tile slidingTile = tiles[move.startPosition.x][move.startPosition.y];
        slidingTile.transition(newPosition);
        tiles[newPosition.x][newPosition.y] = slidingTile;
        SlidingTiles::Tile newTile{};
        newTile.setTilePosition(move.startPosition);
        newTile.setTileType(TileType::Empty);
        tiles[move.startPosition.x][move.startPosition.y] = newTile;
    }
}

sf::Vector2i GameBoard::findStartTile() {
    sf::Vector2i startTilePos{-1, -1};
    bool startFound = false;
    for (int x = 0; (x < boardSize) && !startFound; ++x)
        for (int y = 0; (y < boardSize) && !startFound; ++y)
            if (isStartTileType(tiles[x][y].getTileType())) {
                startFound = true;
                startTilePos.x = x;
                startTilePos.y = y;
            }
    return startTilePos;
}

sf::Vector2i GameBoard::getOutputPosition(const Move & move) {
    TileType type = tiles[move.startPosition.x][move.startPosition.y].getTileType();
    sf::Vector2i nextTile{move.startPosition.x, move.startPosition.y};

    if (type == TileType::StartRight)
        ++nextTile.x;
    else if (type == TileType::StartLeft)
        --nextTile.x;
    else if (type == TileType::StartTop)
        --nextTile.y;


    else if (type == TileType::StartBottom)
        ++nextTile.y;
    else if (type == TileType::Horizontal && move.direction == Direction::GoRight)
        ++nextTile.x;
    else if (type == TileType::Horizontal && move.direction == Direction::GoLeft)
        --nextTile.x;
    else if (type == TileType::Vertical && move.direction == Direction::GoDown)
        ++nextTile.y;
    else if (type == TileType::Vertical && move.direction == Direction::GoUp)
        --nextTile.y;
    else if (type == TileType::LeftBottom && move.direction == Direction::GoRight)
        ++nextTile.y;
    else if (type == TileType::LeftBottom && move.direction == Direction::GoUp)
        --nextTile.x;
    else if (type == TileType::LeftTop && move.direction == Direction::GoDown)
        --nextTile.x;
    else if (type == TileType::LeftTop && move.direction == Direction::GoRight)
        --nextTile.y;
    else if (type == TileType::BottomRight && move.direction == Direction::GoUp)
        ++nextTile.x;
    else if (type == TileType::BottomRight && move.direction == Direction::GoLeft)
        ++nextTile.y;
    else if (type == TileType::TopRight && move.direction == Direction::GoLeft)
        --nextTile.y;
    else if (type == TileType::TopRight && move.direction == Direction::GoDown)
        ++nextTile.x;
    else if ((type == TileType::EndBottom && move.direction == Direction::GoUp)
            || (type == TileType::EndLeft && move.direction == Direction::GoRight)
            || (type == TileType::EndRight && move.direction == Direction::GoLeft)
            || (type == TileType::EndTop && move.direction == Direction::GoDown)) {
        nextTile.x = -2;
        nextTile.y = -2;
    } else {
        nextTile.x = -1;
        nextTile.y = -1;
    }

    return nextTile;
}

std::vector<sf::Vector2i> GameBoard::isSolved() {
    std::vector<sf::Vector2i> solutionPath{};

    sf::Vector2i startTilePos = findStartTile();
    if (startTilePos.x == -1) return solutionPath; // no start tile
    solutionPath.push_back(startTilePos);

    SlidingTiles::Tile startTile = tiles[startTilePos.x][startTilePos.y];
    Move move{startTilePos, Direction::Unknown};
    sf::Vector2i nextTilePos = getOutputPosition(move);
    Direction nextDirection = startTile.outputDirection(Direction::Unknown);
    while (nextTilePos.x > -1) {
        solutionPath.push_back(nextTilePos);
        Move nextMove{nextTilePos, nextDirection};
        sf::Vector2i tempTile = getOutputPosition(nextMove);
        SlidingTiles::Tile nextTile = tiles[nextTilePos.x][nextTilePos.y];
        Direction tempDirection = nextTile.outputDirection(nextDirection);
        nextTilePos = tempTile;
        nextDirection = tempDirection;
    }

    if (nextTilePos.x != -2)
        solutionPath = {};
    return solutionPath;
}

