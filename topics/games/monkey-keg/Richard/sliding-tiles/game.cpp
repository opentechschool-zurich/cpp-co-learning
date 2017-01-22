#include "game.h"

namespace SlidingTiles {
    Game::Game():
        window(sf::VideoMode(550, 400, 32), "Sliding tiles")
    {
    }


    void Game::init()
    {
        RenderingSingleton::getInstance().setRenderWindow( &window );
        RenderingSingleton::getInstance().getRenderWindow()->setFramerateLimit(60);


        gameView.init();

        char game3[4][4] {' ',' ','-','s',
                          ' ',' ',' ','V',
                          ' ',' ','V',' ',
                          ' ',' ',' ','D'};


        char game1[4][4] {'S','-','-','l',
                         'e',' ',' ','V',
                         'V',' ',' ','V',
                         'R','-','-','L'};



        for (int x = 0; x < GameBoardSingleton::boardSize; ++x)
            for (int y = 0; y < GameBoardSingleton::boardSize; ++y) {
                Tile* tile = &GameBoardSingleton::getInstance().tiles[x][y];
                tile->setTilePosition(sf::Vector2i {x,y});
                tile->setTileType( game1[y][x] );
            }
    }

    /**
    * Returns the connecting tile from the supplied tile.
    * if no connecting tile is found it returns -1,-1
    * if we are on an end tile it returns -2
    */
    sf::Vector2i Game::getNextTile(sf::Vector2i tilePos, Direction incomingDirection) {
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

    /**
    * Returns the direction coming out of the supplied tile and incoming direction.
    */
    Direction Game::getTileDirection(sf::Vector2i tilePos, Direction incomingDirection) {
        //TileType type = GameBoardSingleton::getInstance().tiles[tilePos.x][tilePos.y].getTileType();
        return GameBoardSingleton::getInstance().tiles[tilePos.x][tilePos.y].getTileDirection(incomingDirection);
        /*Direction outputDirection = Direction::Unknown;

        if (type == TileType::StartRight)
            return Direction::GoRight;
        else if (type == TileType::StartLeft)
            return Direction::GoLeft;
        else if (type == TileType::StartTop)
            return Direction::GoUp;
        else if (type == TileType::StartBottom)
            return Direction::GoDown;
        else if (type == TileType::Horizontal)
            return incomingDirection;
        else if (type == TileType::Vertical)
            return incomingDirection;
        else if (type == TileType::LeftBottom && incomingDirection == Direction::GoRight)
            return Direction::GoDown;
        else if (type == TileType::LeftBottom && incomingDirection == Direction::GoUp)
            return Direction::GoLeft;
        else if (type == TileType::LeftTop && incomingDirection == Direction::GoDown)
            return Direction::GoLeft;
        else if (type == TileType::LeftTop && incomingDirection == Direction::GoRight)
            return Direction::GoUp;
        else if (type == TileType::TopRight && incomingDirection == Direction::GoDown)
            return Direction::GoRight;
        else if (type == TileType::TopRight && incomingDirection == Direction::GoLeft)
            return Direction::GoUp;
        else if (type == TileType::BottomRight && incomingDirection == Direction::GoLeft)
            return Direction::GoDown;
        else if (type == TileType::BottomRight && incomingDirection == Direction::GoUp)
            return Direction::GoRight;
        else
            return Direction::Unknown; */
    }


    std::vector<sf::Vector2i> Game::findSolution() {
        if ( ! shutUp ) std::cout << "findSolution\n";
        std::vector<sf::Vector2i> solutionPath {};

        bool startFound = false;
        sf::Vector2i startTile {0,0};
        for (int x = 0; (x < GameBoardSingleton::boardSize) && !startFound; ++x)
            for (int y = 0; (y < GameBoardSingleton::boardSize) && !startFound; ++y)
                if ( GameBoardSingleton::getInstance().tiles[x][y].getTileType() == TileType::StartBottom
                    || GameBoardSingleton::getInstance().tiles[x][y].getTileType() == TileType::StartTop
                    || GameBoardSingleton::getInstance().tiles[x][y].getTileType() == TileType::StartLeft
                    || GameBoardSingleton::getInstance().tiles[x][y].getTileType() == TileType::StartRight  ) {
                        startFound = true;
                        startTile.x = x;
                        startTile.y = y;
                    }
        solutionPath.push_back(startTile);

        GameBoardSingleton::getInstance().tiles[startTile.x][startTile.y].winner = true;
        sf::Vector2i nextTile = getNextTile(startTile, Direction::Unknown);
        Direction nextDirection = getTileDirection(startTile, Direction::Unknown);
        if ( ! shutUp )
    /*        std::cout << "getNextTile x[" << startTile.x << "][" << startTile.y
                << "] incomingDirection: " << directionToString(Direction::Unknown)
                << " nextTile: x" << nextTile.x << " y: " << nextTile.y
                << " nextDirection: " << directionToString(nextDirection) << std::endl;*/
        while (nextTile.x > -1) {
            solutionPath.push_back(nextTile);
            sf::Vector2i tempTile = getNextTile(nextTile, nextDirection);
            Direction tempDirection = getTileDirection(nextTile, nextDirection);
            if ( ! shutUp )
                /*std::cout << "getNextTile x[" << nextTile.x << "][" << nextTile.y
                    << "] incomingDirection: " << directionToString(nextDirection)
                    << " nextTile: x" << tempTile.x << " y: " << tempTile.y
                    << " nextDirection: " << directionToString(tempDirection) << std::endl;*/
            nextTile = tempTile;
            nextDirection = tempDirection;
        }
        shutUp = true;

        if ( nextTile.x != -2 )
            solutionPath = {};
        return solutionPath;
    }

    void Game::update(const float dt)
    {
        // send update event to all the tiles
        for (int x = 0; x < GameBoardSingleton::boardSize; ++x)
            for (int y = 0; y < GameBoardSingleton::boardSize; ++y)
                GameBoardSingleton::getInstance().tiles[x][y].tileView.update(dt);

        // see if there is a solution
        std::vector<sf::Vector2i> solutionPath = findSolution();
        if ( solutionPath.size() > 0 ) {
            for ( auto tile : solutionPath )
                GameBoardSingleton::getInstance().tiles[tile.x][tile.y].winner = true;
        } else {
            for (int x = 0; x < GameBoardSingleton::boardSize; ++x)
                for (int y = 0; y < GameBoardSingleton::boardSize; ++y)
                    GameBoardSingleton::getInstance().tiles[x][y].winner = false;
        }
    }



    bool Game::canSlideTile(sf::Vector2i movingTilePosition, sf::Vector2i newPosition) {
        Tile movingTile = GameBoardSingleton::getInstance().tiles[movingTilePosition.x][movingTilePosition.y];
        std::cout << "can slide tile[" << movingTilePosition.x << "][" << movingTilePosition.y << "]"
            << " to [" << newPosition.x << "][" << newPosition.y << "]  "
            << " transitioning: " << movingTile.tileView.transitioning
            << " isMoveable: " << movingTile.isMoveable << "\n";
        if ( ! movingTile.isMoveable )
            return false;

        // check for move off the board
        if ( newPosition.x >= GameBoardSingleton::boardSize
            || newPosition.y >= GameBoardSingleton::boardSize
            || newPosition.x < 0
            || newPosition.y < 0 )
            return false;

        // check if newPosition already taken
        if ( GameBoardSingleton::getInstance().tiles[newPosition.x][newPosition.y].getTileType() != TileType::Empty )
            return false;

        return true;
    }


    /**
    * @brief moves a tile to a new position
    * @param movingTile The coordinates of the tile that is moving
    */
    void Game::slideTile(sf::Vector2i movingTilePosition, sf::Vector2i newPosition) {
        Tile slidingTile = GameBoardSingleton::getInstance().tiles[movingTilePosition.x][movingTilePosition.y];
        if ( canSlideTile(movingTilePosition, newPosition ) ) {
            std::cout << "slide tile[" << movingTilePosition.x << "][" << movingTilePosition.y << "]"
                << " to [" << newPosition.x << "][" << newPosition.y << "] "
                << " transitioning: " << slidingTile.tileView.transitioning << "\n";
            slidingTile.transition(newPosition);
            GameBoardSingleton::getInstance().tiles[newPosition.x][newPosition.y] = slidingTile;
            Tile newTile {};
            newTile.setTilePosition( movingTilePosition );
            newTile.setTileType(TileType::Empty);
            GameBoardSingleton::getInstance().tiles[movingTilePosition.x][movingTilePosition.y] = newTile;
            shutUp = false;
        }
    }

    void Game::run() {
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                else if (event.type == sf::Event::MouseButtonPressed) {
                    mousePositionPressed = sf::Vector2i{event.mouseButton.x, event.mouseButton.y};
                } else if (event.type == sf::Event::MouseButtonReleased) {
                    doMouseReleased(sf::Vector2i {event.mouseButton.x, event.mouseButton.y});
                }
            }

            sf::Time dt = deltaClock.restart();
            update(dt.asSeconds());
            gameView.render();
        }
    }

    void Game::doMouseReleased(sf::Vector2i mousePosition) {
        sf::Vector2i movingTilePosition = RenderingSingleton::getInstance().findTile(mousePositionPressed);
        if ( movingTilePosition.x == -1 || movingTilePosition.y == -1)
            return; // out of grid
        int deltaX = mousePosition.x - mousePositionPressed.x;
        int deltaY = mousePosition.y - mousePositionPressed.y;
        if ( abs(deltaX) > 2 || abs(deltaY) > 2) {
            SlidingTiles::Tile movingTile = GameBoardSingleton::getInstance().tiles[movingTilePosition.x][movingTilePosition.y];
            if (abs(deltaX) > abs(deltaY)) {
                // horizontal movement
                sf::Vector2i newPosition = sf::Vector2i(movingTilePosition.x + copysign(1, deltaX), movingTilePosition.y);
                slideTile(movingTilePosition, newPosition);
            } else {
                // vertical movement
                sf::Vector2i newPosition = sf::Vector2i(movingTilePosition.x, movingTilePosition.y + copysign(1, deltaY));
                slideTile(movingTilePosition, newPosition);
            }
        }
    }

}
