#include "gameBoardSingleton.h"
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

/**
 * Private singleton constructor
 */
GameBoardSingleton::GameBoardSingleton() {
}

// wierdest thing ever: The static member variable needs to be
// declared in the cpp file or the inker gets upset.
const int GameBoardSingleton::boardSize;

void GameBoardSingleton::loadGame(const std::string game[GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]) {
    for (int x = 0; x < GameBoardSingleton::boardSize; ++x) {
        for (int y = 0; y < GameBoardSingleton::boardSize; ++y) {
            SlidingTiles::Tile* tile = &GameBoardSingleton::getInstance().tiles[x][y];
            tile->setTilePosition(sf::Vector2i{x, y});
            tile->setTileType(game[y][x]); // note the inversion here!
            //std::cout << "[" << x << "][" << y << "] char: " << game[x][y] << " became: " << tileTypeToString(tile->getTileType()) << "\n";
        }
    }
}

void GameBoardSingleton::loadGame(const std::vector<std::string> & game) {
    for (int y = 0; y < GameBoardSingleton::boardSize; ++y) {
        for (int x = 0; x < GameBoardSingleton::boardSize; ++x) {
            SlidingTiles::Tile* tile = &GameBoardSingleton::getInstance().tiles[x][y];
            tile->setTilePosition(sf::Vector2i{x, y});
            tile->setTileType(game[y * 4 + x]);
            //std::cout << "[" << x << "][" << y << "] game[y*4+x]: " << game[y*4+x] << " became: " << tileTypeToString(tile->getTileType()) << "\n";
        }
    }
}

void GameBoardSingleton::randomGame() {
    std::vector<sf::Vector2i> positions{};
    for (int x = 0; x < GameBoardSingleton::boardSize; ++x) {
        for (int y = 0; y < GameBoardSingleton::boardSize; ++y) {
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

    TileType startTileType{TileType::Empty};
    switch (rand() % 4) {
        case 0: startTileType = TileType::StartTop;
            break;
        case 1: startTileType = TileType::StartBottom;
            break;
        case 2: startTileType = TileType::StartLeft;
            break;
        case 3: startTileType = TileType::StartRight;
            break;
    }
    sf::Vector2i startPos = positions[0];
    Tile startTile{};
    startTile.setTilePosition(startPos);
    //GameBoardSingleton::getInstance().tiles[startPos.x][startPos.y].setTileType(startTileType);
    startTile.setTileType(startTileType);
    GameBoardSingleton::getInstance().tiles[startPos.x][startPos.y] = startTile;

    TileType endTileType{TileType::Empty};
    switch (rand() % 4) {
        case 0: endTileType = TileType::EndTop;
            break;
        case 1: endTileType = TileType::EndBottom;
            break;
        case 2: endTileType = TileType::EndLeft;
            break;
        case 3: endTileType = TileType::EndRight;
            break;
    }
    sf::Vector2i endPos = positions[1];
    Tile endTile{};
    endTile.setTilePosition(endPos);
    endTile.setTileType(endTileType);
    GameBoardSingleton::getInstance().tiles[endPos.x][endPos.y] = endTile;

    int emptyTiles = 3;

    for (int i = 0; i < emptyTiles; ++i) {
        sf::Vector2i emptyPos = positions[2 + i];
        Tile emptyTile{};
        emptyTile.setTilePosition(emptyPos);
        emptyTile.setTileType(TileType::Empty);
        GameBoardSingleton::getInstance().tiles[emptyPos.x][emptyPos.y] = emptyTile;
    }

    int tiles = GameBoardSingleton::boardSize * GameBoardSingleton::boardSize;
    for (int i = 2 + emptyTiles; i < tiles; ++i) {
        TileType tileType{TileType::Empty};
        switch (rand() % 4) {
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
        GameBoardSingleton::getInstance().tiles[tilePos.x][tilePos.y] = tile;
    }
}

std::vector<std::string> GameBoardSingleton::serialiseGame() {
    std::vector<std::string> serialisedGame;
    for (int y = 0; y < GameBoardSingleton::boardSize; ++y) {
        for (int x = 0; x < GameBoardSingleton::boardSize; ++x) {
            serialisedGame.push_back(tileTypeToChar(GameBoardSingleton::getInstance().tiles[x][y].getTileType()));
        }
    }
    return serialisedGame;
}

void GameBoardSingleton::printGame() {
    for (int y = 0; y < GameBoardSingleton::boardSize; ++y) {
        for (int x = 0; x < GameBoardSingleton::boardSize; ++x) {
            std::cout << tileTypeToChar(GameBoardSingleton::getInstance().tiles[x][y].getTileType());
        }
        std::cout << std::endl;
    }
}

sf::Vector2i GameBoardSingleton::getNextTilePosition(const sf::Vector2i & tilePos, const Direction & incomingDirection) {
    TileType type = GameBoardSingleton::getInstance().tiles[tilePos.x][tilePos.y].getTileType();
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

sf::Vector2i GameBoardSingleton::getAdjacentTilePosition(const sf::Vector2i & tilePos, const Direction & direction) {
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

    if (nextTile.y < 0 || nextTile.x < 0 || nextTile.x >= GameBoardSingleton::boardSize || nextTile.x >= GameBoardSingleton::boardSize) {
        nextTile.x = -1;
        nextTile.y = -1;
    }
    return nextTile;
}

bool GameBoardSingleton::canSlideTile(const sf::Vector2i & movingTilePosition, const sf::Vector2i & newPosition) {
    //std::cout << "can slide tile from [" << movingTilePosition.x << "][" << movingTilePosition.y << "] to ["
    //    << newPosition.x << "][" << newPosition.y << "]\n";
    SlidingTiles::Tile movingTile = GameBoardSingleton::getInstance().tiles[movingTilePosition.x][movingTilePosition.y];
    if (!movingTile.isMoveable)
        return false;

    // check for move off the board
    if (newPosition.x >= GameBoardSingleton::boardSize
            || newPosition.y >= GameBoardSingleton::boardSize
            || newPosition.x < 0
            || newPosition.y < 0)
        return false;

    // check if newPosition already taken
    if (tiles[newPosition.x][newPosition.y].getTileType() != TileType::Empty)
        return false;

    //std::cout << "is true\n";
    return true;
}

bool GameBoardSingleton::canSlideTile(const sf::Vector2i & movingTilePosition, const Direction & direction) {
    sf::Vector2i newPosition = getAdjacentTilePosition(movingTilePosition, direction);
    return canSlideTile(movingTilePosition, newPosition);
}

void GameBoardSingleton::slideTile(const sf::Vector2i & movingTilePosition, const sf::Vector2i & newPosition) {
    SlidingTiles::Tile slidingTile = tiles[movingTilePosition.x][movingTilePosition.y];
    if (canSlideTile(movingTilePosition, newPosition)) {
        /*std::cout << "slide tile[" << movingTilePosition.x << "][" << movingTilePosition.y << "]"
            << " to [" << newPosition.x << "][" << newPosition.y << "] "
            << " transitioning: " << slidingTile.tileView.transitioning << "\n";*/
        slidingTile.transition(newPosition);
        GameBoardSingleton::getInstance().tiles[newPosition.x][newPosition.y] = slidingTile;
        SlidingTiles::Tile newTile{};
        newTile.setTilePosition(movingTilePosition);
        newTile.setTileType(TileType::Empty);
        GameBoardSingleton::getInstance().tiles[movingTilePosition.x][movingTilePosition.y] = newTile;
        //shutUp = false;
    }
}

void GameBoardSingleton::slideTile(const SlidingTiles::Move & move) {
    sf::Vector2i newPosition = getAdjacentTilePosition(move.startPosition, move.direction);
    slideTile(move.startPosition, newPosition);
}

sf::Vector2i GameBoardSingleton::findStartTile() {
    sf::Vector2i startTilePos{-1, -1};
    bool startFound = false;
    for (int x = 0; (x < GameBoardSingleton::boardSize) && !startFound; ++x)
        for (int y = 0; (y < GameBoardSingleton::boardSize) && !startFound; ++y)
            if (GameBoardSingleton::getInstance().tiles[x][y].getTileType() == TileType::StartBottom
                    || GameBoardSingleton::getInstance().tiles[x][y].getTileType() == TileType::StartTop
                    || GameBoardSingleton::getInstance().tiles[x][y].getTileType() == TileType::StartLeft
                    || GameBoardSingleton::getInstance().tiles[x][y].getTileType() == TileType::StartRight) {
                startFound = true;
                startTilePos.x = x;
                startTilePos.y = y;
            }
    return startTilePos;
}

std::vector<sf::Vector2i> GameBoardSingleton::isSolved() {
    std::vector<sf::Vector2i> solutionPath{};

    sf::Vector2i startTilePos = findStartTile();
    if (startTilePos.x == -1) return solutionPath;
    solutionPath.push_back(startTilePos);
    //std::cout << "Start tile found at [" << startTilePos.x << "][" << startTilePos.y <<"]\n";

    SlidingTiles::Tile startTile = GameBoardSingleton::getInstance().tiles[startTilePos.x][startTilePos.y];
    //startTile.setWinner(true);
    sf::Vector2i nextTilePos = GameBoardSingleton::getInstance().getNextTilePosition(startTilePos, Direction::Unknown);
    Direction nextDirection = startTile.outputDirection(Direction::Unknown);
    /*std::cout << "getNextTile x[" << startTilePos.x << "][" << startTilePos.y
            << "] incomingDirection: " << directionToString(Direction::Unknown)
            << " nextTilePos: x" << nextTilePos.x << " y: " << nextTilePos.y
            << " nextDirection: " << directionToString(nextDirection) << std::endl;*/
    while (nextTilePos.x > -1) {
        solutionPath.push_back(nextTilePos);
        sf::Vector2i tempTile = GameBoardSingleton::getInstance().getNextTilePosition(nextTilePos, nextDirection);
        SlidingTiles::Tile nextTile = GameBoardSingleton::getInstance().tiles[nextTilePos.x][nextTilePos.y];
        Direction tempDirection = nextTile.outputDirection(nextDirection);
        /*std::cout << "getNextTile x[" << nextTilePos.x << "][" << nextTilePos.y
                << "] incomingDirection: " << directionToString(nextDirection)
                << " nextTilePos: x" << tempTile.x << " y: " << tempTile.y
                << " nextDirection: " << directionToString(tempDirection) << std::endl;*/
        nextTilePos = tempTile;
        nextDirection = tempDirection;
    }

    if (nextTilePos.x != -2)
        solutionPath = {};
    return solutionPath;
}

std::vector<SlidingTiles::MoveNode> GameBoardSingleton::possibleMoves() {
    MoveNode rootNode{sf::Vector2i{-1, -1}, Direction::Unknown, serialiseGame()};
    rootNode.endingBoard = serialiseGame();
    for (int x = 0; x < GameBoardSingleton::boardSize; ++x)
        for (int y = 0; y < GameBoardSingleton::boardSize; ++y) {
            sf::Vector2i position{x, y};
            if (tiles[x][y].isMoveable) {
                if (canSlideTile(position, Direction::GoUp)) {
                    SlidingTiles::MoveNode moveNode{position, Direction::GoUp, rootNode.startingBoard};
                    slideTile(moveNode);
                    moveNode.setEndingBoard(serialiseGame());
                    rootNode.possibleMoves.push_back(moveNode);
                    loadGame(rootNode.startingBoard);
                    //std::cout << "Creating a possible move(GoUp): " << moveNode.toString();
                }
                if (canSlideTile(position, Direction::GoDown)) {
                    SlidingTiles::MoveNode moveNode{position, Direction::GoDown, rootNode.startingBoard};
                    slideTile(moveNode);
                    moveNode.setEndingBoard(serialiseGame());
                    rootNode.possibleMoves.push_back(moveNode);
                    loadGame(rootNode.startingBoard);
                    //std::cout << "Creating a possible move(GoDown): " << moveNode.toString();
                }
                if (canSlideTile(position, Direction::GoLeft)) {
                    SlidingTiles::MoveNode moveNode{position, Direction::GoLeft, rootNode.startingBoard};
                    slideTile(moveNode);
                    moveNode.setEndingBoard(serialiseGame());
                    rootNode.possibleMoves.push_back(moveNode);
                    loadGame(rootNode.startingBoard);
                    //std::cout << "Creating a possible move(GoLeft): " << moveNode.toString();
                }
                if (canSlideTile(position, Direction::GoRight)) {
                    SlidingTiles::MoveNode moveNode{position, Direction::GoRight, rootNode.startingBoard};
                    slideTile(moveNode);
                    moveNode.setEndingBoard(serialiseGame());
                    rootNode.possibleMoves.push_back(moveNode);
                    loadGame(rootNode.startingBoard);
                    //std::cout << "Creating a possible move(GoRight): " << moveNode.toString();
                }
            }
        }
    return rootNode.possibleMoves;
}

void GameBoardSingleton::addPossibleMoves(MoveNode &parentNode, const int & levels) {
    //std::cout << "\n\naddPossibleMoves levels: " << levels << " " << parentNode.toString();

    std::vector<std::string> priorGameState = serialiseGame();
    GameBoardSingleton::getInstance().loadGame(parentNode.endingBoard);
    std::vector<MoveNode> possMoves = possibleMoves();
    if (levels > 0) {
        //std::cout << "Entering if with levels: " << levels << "\n";
        for (MoveNode & mn : possMoves) {
            // note the & above to ensure we work with the members and not a copy
            addPossibleMoves(mn, levels - 1);
        }
    }
    // note do the insert after the recursive call above because insert copies the object and it might copy without the content in the vector!
    parentNode.possibleMoves.insert(std::end(parentNode.possibleMoves), std::begin(possMoves), std::end(possMoves));
    //std::cout << "parentNode after insert: " << parentNode.toString();
    //std::cout << "finished addPosibleMoves levels: " << levels << " " << parentNode.toString();
    GameBoardSingleton::getInstance().loadGame(priorGameState);
}

std::vector<Solution> GameBoardSingleton::solutions(const std::vector<MoveNode> & possibleMoves) {
    std::vector<std::string> priorGameState = serialiseGame();
    std::vector<Solution> solutions{};
    for (MoveNode moveNode : possibleMoves) {
        Solution currentSolution{};
        //std::cout << "Testing: " << moveNode.toString();
        currentSolution.moves.push_back(moveNode);
        GameBoardSingleton::getInstance().slideTile(moveNode);
        std::vector<sf::Vector2i> solutionPath = GameBoardSingleton::getInstance().isSolved();
        if (solutionPath.size() > 0) {
            solutions.push_back(currentSolution);
            //std::cout << moveNode.toString() << "winner!\n";
        }
        GameBoardSingleton::getInstance().loadGame(priorGameState);
    }
    return solutions;
}

bool GameBoardSingleton::hasASolution(const MoveNode & node) {
    std::vector<std::string> priorGameState = serialiseGame();
    // inspired by https://gist.github.com/douglas-vaz/5072998
    std::queue<MoveNode> Q;
    Q.push(node);
    while (!Q.empty()) {
        MoveNode t = Q.front();
        Q.pop();
        GameBoardSingleton::getInstance().loadGame(t.endingBoard);
        if (GameBoardSingleton::getInstance().isSolved().size() > 0) {
            GameBoardSingleton::getInstance().loadGame(priorGameState);
            return true;
        };
        for (int i = 0; i < t.possibleMoves.size(); ++i) {
            Q.push(t.possibleMoves[i]);
        }
    }
    GameBoardSingleton::getInstance().loadGame(priorGameState);
    return false;
}
