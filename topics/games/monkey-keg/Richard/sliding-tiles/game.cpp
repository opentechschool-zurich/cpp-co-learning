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

        std::string game3[GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
                         {" "," ","-","┬",
                          " "," "," ","|",
                          " "," ","|"," ",
                          " "," "," ","┻"};


        std::string game1[GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
                        {"├","-","-","┐",
                         "┣","┐"," ","|",
                         "┌","┘"," ","|",
                         "└","-","-","┘"};

        GameBoardSingleton::getInstance().loadGame(game1);
    }



    std::vector<sf::Vector2i> Game::findSolution() {
        if ( ! shutUp ) std::cout << "findSolution\n";
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

        Tile startTile = GameBoardSingleton::getInstance().tiles[startTilePos.x][startTilePos.y];
        startTile.winner = true;
        sf::Vector2i nextTilePos = GameBoardSingleton::getInstance().getNextTilePosition(startTilePos, Direction::Unknown);
        Direction nextDirection = startTile.outputDirection( Direction::Unknown );
        if ( ! shutUp )
    /*        std::cout << "getNextTile x[" << startTile.x << "][" << startTile.y
                << "] incomingDirection: " << directionToString(Direction::Unknown)
                << " nextTilePos: x" << nextTilePos.x << " y: " << nextTilePos.y
                << " nextDirection: " << directionToString(nextDirection) << std::endl;*/
        while (nextTilePos.x > -1) {
            solutionPath.push_back(nextTilePos);
            sf::Vector2i tempTile = GameBoardSingleton::getInstance().getNextTilePosition(nextTilePos, nextDirection);
            Tile nextTile = GameBoardSingleton::getInstance().tiles[nextTilePos.x][nextTilePos.y];
            Direction tempDirection = nextTile.outputDirection(nextDirection);
            if ( ! shutUp )
                /*std::cout << "getNextTile x[" << nextTilePos.x << "][" << nextTilePos.y
                    << "] incomingDirection: " << directionToString(nextDirection)
                    << " nextTilePos: x" << tempTile.x << " y: " << tempTile.y
                    << " nextDirection: " << directionToString(tempDirection) << std::endl;*/
            nextTilePos = tempTile;
            nextDirection = tempDirection;
        }
        shutUp = true;

        if ( nextTilePos.x != -2 )
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
