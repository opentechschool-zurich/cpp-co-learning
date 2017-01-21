#include "game.h"

namespace SlidingTiles {
    Game::Game():
        window(sf::VideoMode(550, 400, 32), "Sliding tiles")
    {
    }

    sf::Font font;
    void Game::init()
    {
        window.setFramerateLimit(60);

        if (!font.loadFromFile("assets/ChangaOne-Regular.ttf"))
            std::cout << "Can't load font ./assets/ChangaOne-Regular.ttf" << std::endl;

        bannerText.setFont(font);
        bannerText.setCharacterSize(30);
        bannerText.setStyle(sf::Text::Bold);
        bannerText.setColor(sf::Color::Black);
        bannerText.setString("Move the tiles with the mouse");
        bannerText.setPosition(30, 10);

        char game3[4][4] {'-','-','H','s',
                          '-','-','-','V',
                          '-','-','V','-',
                          '-','-','-','D'};


        char game1[4][4] {'S','H','H','l',
                         'e','-','-','V',
                         'V','-','-','V',
                         'R','H','H','L'};



        for (int x = 0; x < GameBoardSingleton::boardSize; ++x)
            for (int y = 0; y < GameBoardSingleton::boardSize; ++y) {
                Tile newTile {&window, tileSize, GameBoardSingleton::getInstance().gridZeroZero, sf::Vector2i {x,y}};
                if (game1[y][x] == '-') {
                    newTile.setTileType(TileType::Empty);
                } else if (game1[y][x] == 'H'){
                    newTile.setTileType(TileType::Horizontal);
                } else if (game1[y][x] == 'V'){
                    newTile.setTileType(TileType::Vertical);

                } else if (game1[y][x] == 'R'){
                    newTile.setTileType(TileType::TopRight);
                } else if (game1[y][x] == 'L'){
                    newTile.setTileType(TileType::LeftTop);
                } else if (game1[y][x] == 'l'){
                    newTile.setTileType(TileType::LeftBottom);
                } else if (game1[y][x] == 'r'){
                    newTile.setTileType(TileType::BottomRight);

                } else if (game1[y][x] == 'S'){
                    newTile.setTileType(TileType::StartRight);
                } else if (game1[y][x] == 's'){
                    newTile.setTileType(TileType::StartBottom);
                } else if (game1[y][x] == 'T'){
                    newTile.setTileType(TileType::StartTop);
                } else if (game1[y][x] == 't'){
                    newTile.setTileType(TileType::StartLeft);

                } else if (game1[y][x] == 'D'){
                    newTile.setTileType(TileType::EndTop);
                } else if (game1[y][x] == 'd'){
                    newTile.setTileType(TileType::EndRight);
                } else if (game1[y][x] == 'E'){
                    newTile.setTileType(TileType::EndLeft);
                } else if (game1[y][x] == 'e'){
                    newTile.setTileType(TileType::EndBottom);
                } else {
                    newTile.setTileType(TileType::Empty);
                }
                tiles[x][y] = newTile;
            }
    }

    /**
    * Returns the connecting tile from the supplied tile.
    * if no connecting tile is found it returns -1,-1
    * if we are on an end tile it returns -2
    */
    sf::Vector2i Game::getNextTile(sf::Vector2i tilePos, Direction incomingDirection) {
        TileType type = tiles[tilePos.x][tilePos.y].getTileType();
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

    std::string Game::directionToString(Direction direction) {
        if ( direction == Direction::GoDown )
            return "GoDown";
        else if ( direction == Direction::GoRight )
            return "GoRight";
        else if ( direction == Direction::GoUp )
            return "GoUp";
        else if ( direction == Direction::GoLeft )
            return "GoLeft";
        else
            return "Unknown";
    }

    /**
    * Returns the direction coming out of the supplied tile and incoming direction.
    */
    Game::Direction Game::getTileDirection(sf::Vector2i tilePos, Direction incomingDirection) {
        TileType type = tiles[tilePos.x][tilePos.y].getTileType();
        Direction outputDirection = Direction::Unknown;

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
            return Direction::Unknown;
    }


    std::vector<sf::Vector2i> Game::findSolution() {
        if ( ! shutUp ) std::cout << "findSolution\n";
        std::vector<sf::Vector2i> solutionPath {};

        bool startFound = false;
        sf::Vector2i startTile {0,0};
        for (int x = 0; (x < GameBoardSingleton::boardSize) && !startFound; ++x)
            for (int y = 0; (y < GameBoardSingleton::boardSize) && !startFound; ++y)
                if ( tiles[x][y].getTileType() == TileType::StartBottom
                    || tiles[x][y].getTileType() == TileType::StartTop
                    || tiles[x][y].getTileType() == TileType::StartLeft
                    || tiles[x][y].getTileType() == TileType::StartRight  ) {
                        startFound = true;
                        startTile.x = x;
                        startTile.y = y;
                    }
        solutionPath.push_back(startTile);

        tiles[startTile.x][startTile.y].winner = true;
        sf::Vector2i nextTile = getNextTile(startTile, Direction::Unknown);
        Direction nextDirection = getTileDirection(startTile, Direction::Unknown);
        if ( ! shutUp )
            std::cout << "getNextTile x[" << startTile.x << "][" << startTile.y
                << "] incomingDirection: " << directionToString(Direction::Unknown)
                << " nextTile: x" << nextTile.x << " y: " << nextTile.y
                << " nextDirection: " << directionToString(nextDirection) << std::endl;
        while (nextTile.x > -1) {
            solutionPath.push_back(nextTile);
            sf::Vector2i tempTile = getNextTile(nextTile, nextDirection);
            Direction tempDirection = getTileDirection(nextTile, nextDirection);
            if ( ! shutUp )
                std::cout << "getNextTile x[" << nextTile.x << "][" << nextTile.y
                    << "] incomingDirection: " << directionToString(nextDirection)
                    << " nextTile: x" << tempTile.x << " y: " << tempTile.y
                    << " nextDirection: " << directionToString(tempDirection) << std::endl;
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
                tiles[x][y].tileView.update(dt);

        // see if there is a solution
        std::vector<sf::Vector2i> solutionPath = findSolution();
        if ( solutionPath.size() > 0 ) {
            for ( auto tile : solutionPath )
                tiles[tile.x][tile.y].winner = true;
        } else {
            for (int x = 0; x < GameBoardSingleton::boardSize; ++x)
                for (int y = 0; y < GameBoardSingleton::boardSize; ++y)
                    tiles[x][y].winner = false;
        }
    }



    void Game::render()
    {
        window.clear(sf::Color::White);

        window.draw(bannerText);

        // first render the tiles that are static
        for (int x = 0; x < GameBoardSingleton::boardSize; ++x)
            for (int y = 0; y < GameBoardSingleton::boardSize; ++y)
                if ( ! tiles[x][y].tileView.transitioning )
                    tiles[x][y].tileView.render();

        // then render the tiles that are transitioning so that they are on top
        for (int x = 0; x < GameBoardSingleton::boardSize; ++x)
            for (int y = 0; y < GameBoardSingleton::boardSize; ++y)
                if ( tiles[x][y].tileView.transitioning )
                    tiles[x][y].tileView.render();

        window.display();
    }

    /**
    * Given the screen coordinates find the corresponding game coordinates in the model
    */
    sf::Vector2i Game::findTile(sf::Vector2i mousePosition) {
        sf::Vector2i gridCoordinates = mousePosition - GameBoardSingleton::getInstance().gridZeroZero;
        int xPos = gridCoordinates.x / tileSize;
        int yPos = gridCoordinates.y / tileSize;
        std::cout << "find tile mouse.x=" << mousePosition.x << " y= "
            << mousePosition.y << " --> tiles[" << xPos << "][" << yPos << "]\n";
        return sf::Vector2i {xPos, yPos};
    }

    bool Game::canSlideTile(Tile movingTile, sf::Vector2i movingTilePosition, sf::Vector2i newPosition) {
        std::cout << "can slide tile[" << movingTilePosition.x << "][" << movingTilePosition.y << "]"
            << " to [" << newPosition.x << "][" << newPosition.y << "]  tile reports x="
            << movingTile.gameBoardPosition.x << " y=" << movingTile.gameBoardPosition.y
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
        if ( tiles[newPosition.x][newPosition.y].getTileType() != TileType::Empty )
            return false;

        return true;
    }


    void Game::slideTile(Tile movingTile, sf::Vector2i movingTilePosition, sf::Vector2i newPosition) {
        if ( canSlideTile(movingTile, movingTilePosition, newPosition ) ) {
            std::cout << "slide tile[" << movingTilePosition.x << "][" << movingTilePosition.y << "]"
                << " to [" << newPosition.x << "][" << newPosition.y << "]  tile reports x="
                << movingTile.gameBoardPosition.x << " y=" << movingTile.gameBoardPosition.y
                << " transitioning: " << movingTile.tileView.transitioning << "\n";
            movingTile.transition(newPosition);
            tiles[newPosition.x][newPosition.y] = movingTile;
            Tile newTile {&window, tileSize, GameBoardSingleton::getInstance().gridZeroZero, movingTilePosition };
            newTile.setTileType(TileType::Empty);
            tiles[movingTilePosition.x][movingTilePosition.y] = newTile;
            shutUp = false;
        }
    }

    void Game::run()
    {
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
                    int deltaX = event.mouseButton.x - mousePositionPressed.x;
                    int deltaY = event.mouseButton.y - mousePositionPressed.y;
                    if ( abs(deltaX) > 2 || abs(deltaY) > 2) {
                        sf::Vector2i movingTilePosition = findTile(mousePositionPressed);
                        SlidingTiles::Tile movingTile = tiles[movingTilePosition.x][movingTilePosition.y];
                        if (abs(deltaX) > abs(deltaY)) {
                            // horizontal movement
                            sf::Vector2i newPosition = sf::Vector2i(movingTilePosition.x + copysign(1, deltaX), movingTilePosition.y);
                            slideTile(movingTile, movingTilePosition, newPosition);
                        } else {
                            // vertical movement
                            sf::Vector2i newPosition = sf::Vector2i(movingTilePosition.x, movingTilePosition.y + copysign(1, deltaY));
                            slideTile(movingTile, movingTilePosition, newPosition);
                        }
                    }
                }
            }

            sf::Time dt = deltaClock.restart();
            update(dt.asSeconds());
            render();
        }
    }

}
