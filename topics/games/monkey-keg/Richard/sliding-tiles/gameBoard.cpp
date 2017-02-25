#include "gameBoard.h"
#include <sstream>
#include "tileType.h"
#include <string>
#include "solution.h"
#include <queue>
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
    /*for (int i = 0; i<positions.size(); ++i) {
        std::cout << i << ": [" << positions[i].x << "][" << positions[i].y << "]\n";
    }*/
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(std::begin(positions), std::end(positions), std::default_random_engine(seed));
    /*std::cout << "After Shuffle...\n";
    for (int i = 0; i<positions.size(); ++i) {
        std::cout << i << ": [" << positions[i].x << "][" << positions[i].y << "]\n";
    }*/

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

    //int emptyTiles = 3;

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


sf::Vector2i GameBoard::getNextTilePosition(const sf::Vector2i & tilePos, const Direction & incomingDirection) {
    TileType type = tiles[tilePos.x][tilePos.y].getTileType();
    sf::Vector2i nextTile{tilePos.x, tilePos.y};

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
    else if ((type == TileType::EndBottom && incomingDirection == Direction::GoUp)
            || (type == TileType::EndLeft && incomingDirection == Direction::GoRight)
            || (type == TileType::EndRight && incomingDirection == Direction::GoLeft)
            || (type == TileType::EndTop && incomingDirection == Direction::GoDown)) {
        nextTile.x = -2;
        nextTile.y = -2;
    } else {
        nextTile.x = -1;
        nextTile.y = -1;
    }

    return nextTile;
}


sf::Vector2i GameBoard::getAdjacentTilePosition(const sf::Vector2i & tilePos, const Direction & direction) {
    sf::Vector2i nextTile{tilePos.x, tilePos.y};

    //std::cout << "getAdjacentTilePosition for ["<< tilePos.x << "][" << tilePos.y << "] direction: " << directionToString(direction) << "\n";
    if (direction == Direction::GoDown) {
        ++nextTile.y;
    } else if (direction == Direction::GoUp)
        --nextTile.y;
    else if (direction == Direction::GoLeft)
        --nextTile.x;
    else if (direction == Direction::GoRight)
        ++nextTile.x;

    if (nextTile.y < 0 || nextTile.x < 0 || nextTile.x >= boardSize || nextTile.x >= boardSize) {
        nextTile.x = -1;
        nextTile.y = -1;
    }
    return nextTile;
}

bool GameBoard::canSlideTile(const sf::Vector2i & movingTilePosition, const sf::Vector2i & newPosition) {
    //std::cout << "can slide tile from [" << movingTilePosition.x << "][" << movingTilePosition.y << "] to ["
    //    << newPosition.x << "][" << newPosition.y << "]\n";
    SlidingTiles::Tile movingTile = tiles[movingTilePosition.x][movingTilePosition.y];
    if (!movingTile.isMoveable)
        return false;

    // check for move off the board
    if (newPosition.x >= boardSize
            || newPosition.y >= boardSize
            || newPosition.x < 0
            || newPosition.y < 0)
        return false;

    // check if newPosition already taken
    if (tiles[newPosition.x][newPosition.y].getTileType() != TileType::Empty)
        return false;

    //std::cout << "is true\n";
    return true;
}

bool GameBoard::canSlideTile(const sf::Vector2i & movingTilePosition, const Direction & direction) {
    sf::Vector2i newPosition = getAdjacentTilePosition(movingTilePosition, direction);
    return canSlideTile(movingTilePosition, newPosition);
}

void GameBoard::slideTile(const sf::Vector2i & movingTilePosition, const sf::Vector2i & newPosition) {
    SlidingTiles::Tile slidingTile = tiles[movingTilePosition.x][movingTilePosition.y];
    if (canSlideTile(movingTilePosition, newPosition)) {
        /*std::cout << "slide tile[" << movingTilePosition.x << "][" << movingTilePosition.y << "]"
            << " to [" << newPosition.x << "][" << newPosition.y << "] "
            << " transitioning: " << slidingTile.tileView.transitioning << "\n";*/
        slidingTile.transition(newPosition);
        tiles[newPosition.x][newPosition.y] = slidingTile;
        SlidingTiles::Tile newTile{};
        newTile.setTilePosition(movingTilePosition);
        newTile.setTileType(TileType::Empty);
        tiles[movingTilePosition.x][movingTilePosition.y] = newTile;
    }
}

void GameBoard::slideTile(const SlidingTiles::Move & move) {
    sf::Vector2i newPosition = getAdjacentTilePosition(move.startPosition, move.direction);
    slideTile(move.startPosition, newPosition);
}

sf::Vector2i GameBoard::findStartTile() {
    sf::Vector2i startTilePos{-1, -1};
    bool startFound = false;
    for (int x = 0; (x < boardSize) && !startFound; ++x)
        for (int y = 0; (y < boardSize) && !startFound; ++y)
            if (isStartTileType( tiles[x][y].getTileType() )) {
                startFound = true;
                startTilePos.x = x;
                startTilePos.y = y;
            }
    return startTilePos;
}

std::vector<sf::Vector2i> GameBoard::isSolved() {
    std::vector<sf::Vector2i> solutionPath{};

    sf::Vector2i startTilePos = findStartTile();
    if (startTilePos.x == -1) return solutionPath; // no start tile
    solutionPath.push_back(startTilePos);

    SlidingTiles::Tile startTile = tiles[startTilePos.x][startTilePos.y];
    sf::Vector2i nextTilePos = getNextTilePosition(startTilePos, Direction::Unknown);
    Direction nextDirection = startTile.outputDirection(Direction::Unknown);
    while (nextTilePos.x > -1) {
        solutionPath.push_back(nextTilePos);
        sf::Vector2i tempTile = getNextTilePosition(nextTilePos, nextDirection);
        SlidingTiles::Tile nextTile = tiles[nextTilePos.x][nextTilePos.y];
        Direction tempDirection = nextTile.outputDirection(nextDirection);
        nextTilePos = tempTile;
        nextDirection = tempDirection;
    }

    if (nextTilePos.x != -2)
        solutionPath = {};
    return solutionPath;
}

