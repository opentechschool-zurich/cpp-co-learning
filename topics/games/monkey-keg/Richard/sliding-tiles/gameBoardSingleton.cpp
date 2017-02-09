#include "gameBoardSingleton.h"
#include <sstream>
#include "tileType.h"
#include <string>
#include "solution.h"

using namespace SlidingTiles;

/**
* Private singleton constructor
*/
GameBoardSingleton::GameBoardSingleton(){
}

// wierdest thing ever: The static member variable needs to be
// declared in the cpp file or the inker gets upset.
const int GameBoardSingleton::boardSize;

void GameBoardSingleton::loadGame( std::string game[GameBoardSingleton::boardSize][GameBoardSingleton::boardSize] ) {
    for (int x = 0; x < GameBoardSingleton::boardSize; ++x) {
        for (int y = 0; y < GameBoardSingleton::boardSize; ++y) {
            SlidingTiles::Tile* tile = &GameBoardSingleton::getInstance().tiles[x][y];
            tile->setTilePosition(sf::Vector2i {x,y});
            tile->setTileType( game[y][x] );  // note the inversion here!
            //std::cout << "[" << x << "][" << y << "] char: " << game[x][y] << " became: " << tileTypeToString(tile->getTileType()) << "\n";
        }
    }
}

void GameBoardSingleton::loadGame( std::vector<std::string> game ) {
    for (int y = 0; y < GameBoardSingleton::boardSize; ++y) {
        for (int x = 0; x < GameBoardSingleton::boardSize; ++x) {
            SlidingTiles::Tile* tile = &GameBoardSingleton::getInstance().tiles[x][y];
            tile->setTilePosition(sf::Vector2i {x,y});
            tile->setTileType( game[y*4+x] );
            //std::cout << "[" << x << "][" << y << "] game[y*4+x]: " << game[y*4+x] << " became: " << tileTypeToString(tile->getTileType()) << "\n";
        }
    }
}


std::vector<std::string> GameBoardSingleton::serialiseGame() {
    std::vector<std::string> serialisedGame;
    for (int y = 0; y < GameBoardSingleton::boardSize; ++y) {
        for (int x = 0; x < GameBoardSingleton::boardSize; ++x) {
            serialisedGame.push_back( tileTypeToChar( GameBoardSingleton::getInstance().tiles[x][y].getTileType() ) );
        }
    }
    return serialisedGame;
}


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

sf::Vector2i GameBoardSingleton::getAdjacentTilePosition(sf::Vector2i tilePos, Direction direction) {
    sf::Vector2i nextTile {tilePos.x,tilePos.y};

    //std::cout << "getAdjacentTilePosition for ["<< tilePos.x << "][" << tilePos.y << "] direction: " << directionToString(direction) << "\n";
    if (direction == Direction::GoDown) {
        ++nextTile.y;
    }
    else if (direction == Direction::GoUp)
        --nextTile.y;
    else if (direction == Direction::GoLeft)
        --nextTile.x;
    else if (direction == Direction::GoRight)
        ++nextTile.x;

    if ( nextTile.y < 0 || nextTile.x < 0 || nextTile.x >= GameBoardSingleton::boardSize || nextTile.x >= GameBoardSingleton::boardSize) {
        nextTile.x = -1;
        nextTile.y = -1;
    }
    return nextTile;
}


bool GameBoardSingleton::canSlideTile(sf::Vector2i movingTilePosition, sf::Vector2i newPosition) {
    //std::cout << "can slide tile from [" << movingTilePosition.x << "][" << movingTilePosition.y << "] to ["
    //    << newPosition.x << "][" << newPosition.y << "]\n";
    SlidingTiles::Tile movingTile = GameBoardSingleton::getInstance().tiles[movingTilePosition.x][movingTilePosition.y];
    if ( ! movingTile.isMoveable )
        return false;

    // check for move off the board
    if ( newPosition.x >= GameBoardSingleton::boardSize
        || newPosition.y >= GameBoardSingleton::boardSize
        || newPosition.x < 0
        || newPosition.y < 0 )
        return false;

    // check if newPosition already taken
    if ( tiles[newPosition.x][newPosition.y].getTileType() != TileType::Empty )
        return false;

    //std::cout << "is true\n";
    return true;
}

bool GameBoardSingleton::canSlideTile(sf::Vector2i movingTilePosition, Direction direction) {
  sf::Vector2i newPosition = getAdjacentTilePosition(movingTilePosition, direction);
  return canSlideTile(movingTilePosition, newPosition);
}


void GameBoardSingleton::slideTile(sf::Vector2i movingTilePosition, sf::Vector2i newPosition) {
    SlidingTiles::Tile slidingTile = tiles[movingTilePosition.x][movingTilePosition.y];
    if ( canSlideTile(movingTilePosition, newPosition ) ) {
        /*std::cout << "slide tile[" << movingTilePosition.x << "][" << movingTilePosition.y << "]"
            << " to [" << newPosition.x << "][" << newPosition.y << "] "
            << " transitioning: " << slidingTile.tileView.transitioning << "\n";*/
        slidingTile.transition(newPosition);
        GameBoardSingleton::getInstance().tiles[newPosition.x][newPosition.y] = slidingTile;
        SlidingTiles::Tile newTile {};
        newTile.setTilePosition( movingTilePosition );
        newTile.setTileType(TileType::Empty);
        GameBoardSingleton::getInstance().tiles[movingTilePosition.x][movingTilePosition.y] = newTile;
        //shutUp = false;
    }
}

void GameBoardSingleton::slideTile(SlidingTiles::Move move) {
    sf::Vector2i newPosition = getAdjacentTilePosition(move.startPosition, move.direction);
    slideTile( move.startPosition, newPosition);
}


std::vector<sf::Vector2i> GameBoardSingleton::isSolved() {
    std::vector<sf::Vector2i> solutionPath {};

    bool startFound = false;
    sf::Vector2i startTilePos {0,0};
    for (int x = 0; (x < GameBoardSingleton::boardSize) && !startFound; ++x)
        for (int y = 0; (y < GameBoardSingleton::boardSize) && !startFound; ++y)
            if ( GameBoardSingleton::getInstance().tiles[x][y].getTileType() == TileType::StartBottom
                || GameBoardSingleton::getInstance().tiles[x][y].getTileType() == TileType::StartTop
                || GameBoardSingleton::getInstance().tiles[x][y].getTileType() == TileType::StartLeft
                || GameBoardSingleton::getInstance().tiles[x][y].getTileType() == TileType::StartRight  ) {
                    startFound = true;
                    startTilePos.x = x;
                    startTilePos.y = y;
                }
    solutionPath.push_back(startTilePos);
    //std::cout << "Start tile found at [" << startTilePos.x << "][" << startTilePos.y <<"]\n";

    SlidingTiles::Tile startTile = GameBoardSingleton::getInstance().tiles[startTilePos.x][startTilePos.y];
    startTile.setWinner(true);
    sf::Vector2i nextTilePos = GameBoardSingleton::getInstance().getNextTilePosition(startTilePos, Direction::Unknown);
    Direction nextDirection = startTile.outputDirection( Direction::Unknown );
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

    if ( nextTilePos.x != -2 )
        solutionPath = {};
    return solutionPath;
}

std::vector<SlidingTiles::MoveNode> GameBoardSingleton::possibleMoves(){
  std::vector<std::string> priorGameState = serialiseGame();
  std::vector<SlidingTiles::MoveNode> possibleMoves{};
  for (int x = 0; x < GameBoardSingleton::boardSize; ++x)
      for (int y = 0; y < GameBoardSingleton::boardSize; ++y) {
        //std::cout << "possibleMoves testing [" << x << "][" << y << "]\n";
        sf::Vector2i position {x,y};
        if ( tiles[x][y].isMoveable ) {
            if (canSlideTile(position, Direction::GoUp)) {
                SlidingTiles::MoveNode moveNode {position, Direction::GoUp, priorGameState};
                slideTile(moveNode);
                moveNode.setEndingBoard( serialiseGame() );
                possibleMoves.push_back(moveNode);
                loadGame(priorGameState);
                //std::cout << "Can GoUp\n";
            }
            if (canSlideTile(position, Direction::GoDown)) {
                SlidingTiles::MoveNode moveNode {position, Direction::GoDown, priorGameState};
                slideTile(moveNode);
                moveNode.setEndingBoard( serialiseGame() );
                possibleMoves.push_back(moveNode);
                loadGame(priorGameState);
                //std::cout << "Can GoDown\n";
            }
            if (canSlideTile(position, Direction::GoLeft)) {
                SlidingTiles::MoveNode moveNode {position, Direction::GoLeft, priorGameState};
                slideTile(moveNode);
                moveNode.setEndingBoard( serialiseGame() );
                possibleMoves.push_back(moveNode);
                loadGame(priorGameState);
                //std::cout << "Can GoLeft\n";
            }
            if (canSlideTile(position, Direction::GoRight)) {
                SlidingTiles::MoveNode moveNode {position, Direction::GoRight, priorGameState};
                slideTile(moveNode);
                moveNode.setEndingBoard( serialiseGame() );
                possibleMoves.push_back(moveNode);
                loadGame(priorGameState);
                //std::cout << "Can GoRight\n";
            }
        }
      }

  return possibleMoves;
}


/*std::vector<MoveNode> GameBoardSingleton::solutions (std::vector<MoveNode> possibleMoves) {
    std::vector<std::string> priorGameState = serialiseGame();
    std::vector<MoveNode> solutions {};
    for ( MoveNode moveNode : possibleMoves ) {
        //std::cout << "Testing: " << moveNode.toString();
        GameBoardSingleton::getInstance().slideTile(moveNode);
        std::vector<sf::Vector2i> solutionPath = GameBoardSingleton::getInstance().isSolved();
        if ( solutionPath.size() > 0 ) {
            solutions.push_back( moveNode );
            //std::cout << moveNode.toString() << "winner!\n";
        }
        GameBoardSingleton::getInstance().loadGame(priorGameState);
    }
    return solutions;
}*/


std::vector<Solution> GameBoardSingleton::solutions (std::vector<MoveNode> possibleMoves) {
    std::vector<std::string> priorGameState = serialiseGame();
    std::vector<Solution> solutions {};
    for ( MoveNode moveNode : possibleMoves ) {
        Solution currentSolution {};
        //std::cout << "Testing: " << moveNode.toString();
        currentSolution.moves.push_back(moveNode);
        GameBoardSingleton::getInstance().slideTile(moveNode);
        std::vector<sf::Vector2i> solutionPath = GameBoardSingleton::getInstance().isSolved();
        if ( solutionPath.size() > 0 ) {
            solutions.push_back( currentSolution );
            //std::cout << moveNode.toString() << "winner!\n";
        }
        GameBoardSingleton::getInstance().loadGame(priorGameState);
    }
    return solutions;
}
