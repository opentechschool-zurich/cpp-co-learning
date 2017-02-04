#include "gameBoardSingleton.h"

/**
* Private singleton constructor
*/
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


bool GameBoardSingleton::canSlideTile(sf::Vector2i movingTilePosition, sf::Vector2i newPosition) {
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

    return true;
}


/**
* @brief moves a tile to a new position
* @param movingTile The coordinates of the tile that is moving
*/
void GameBoardSingleton::slideTile(sf::Vector2i movingTilePosition, sf::Vector2i newPosition) {
    SlidingTiles::Tile slidingTile = tiles[movingTilePosition.x][movingTilePosition.y];
    if ( canSlideTile(movingTilePosition, newPosition ) ) {
        std::cout << "slide tile[" << movingTilePosition.x << "][" << movingTilePosition.y << "]"
            << " to [" << newPosition.x << "][" << newPosition.y << "] "
            << " transitioning: " << slidingTile.tileView.transitioning << "\n";
        slidingTile.transition(newPosition);
        GameBoardSingleton::getInstance().tiles[newPosition.x][newPosition.y] = slidingTile;
        SlidingTiles::Tile newTile {};
        newTile.setTilePosition( movingTilePosition );
        newTile.setTileType(TileType::Empty);
        GameBoardSingleton::getInstance().tiles[movingTilePosition.x][movingTilePosition.y] = newTile;
        //shutUp = false;
    }
}


std::vector<sf::Vector2i> GameBoardSingleton::isSolved() {
    //if ( ! shutUp ) std::cout << "starting isSolved\n";
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

    SlidingTiles::Tile startTile = GameBoardSingleton::getInstance().tiles[startTilePos.x][startTilePos.y];
    startTile.setWinner(true);
    sf::Vector2i nextTilePos = GameBoardSingleton::getInstance().getNextTilePosition(startTilePos, Direction::Unknown);
    Direction nextDirection = startTile.outputDirection( Direction::Unknown );
    /*if ( ! shutUp )
        std::cout << "getNextTile x[" << startTilePos.x << "][" << startTilePos.y
            << "] incomingDirection: " << directionToString(Direction::Unknown)
            << " nextTilePos: x" << nextTilePos.x << " y: " << nextTilePos.y
            << " nextDirection: " << directionToString(nextDirection) << std::endl;*/
    while (nextTilePos.x > -1) {
        solutionPath.push_back(nextTilePos);
        sf::Vector2i tempTile = GameBoardSingleton::getInstance().getNextTilePosition(nextTilePos, nextDirection);
        SlidingTiles::Tile nextTile = GameBoardSingleton::getInstance().tiles[nextTilePos.x][nextTilePos.y];
        Direction tempDirection = nextTile.outputDirection(nextDirection);
        /*if ( ! shutUp )
            std::cout << "getNextTile x[" << nextTilePos.x << "][" << nextTilePos.y
                << "] incomingDirection: " << directionToString(nextDirection)
                << " nextTilePos: x" << tempTile.x << " y: " << tempTile.y
                << " nextDirection: " << directionToString(tempDirection) << std::endl; */
        nextTilePos = tempTile;
        nextDirection = tempDirection;
    }
    //shutUp = true;

    if ( nextTilePos.x != -2 )
        solutionPath = {};
    return solutionPath;
}
