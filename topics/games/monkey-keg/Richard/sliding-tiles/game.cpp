#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
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
        sf::Texture texture;

        texture.loadFromFile("assets/horizontal.png");
        texturesMap[Tile::TileType::Horizontal] = texture;
        texture.loadFromFile("assets/vertical.png");
        texturesMap[Tile::TileType::Vertical] = texture;

        texture.loadFromFile("assets/startbottom.png");
        texturesMap[Tile::TileType::StartBottom] = texture;
        texture.loadFromFile("assets/starttop.png");
        texturesMap[Tile::TileType::StartTop] = texture;
        texture.loadFromFile("assets/startleft.png");
        texturesMap[Tile::TileType::StartLeft] = texture;
        texture.loadFromFile("assets/startright.png");
        texturesMap[Tile::TileType::StartRight] = texture;

        texture.loadFromFile("assets/endtop.png");
        texturesMap[Tile::TileType::EndTop] = texture;
        texture.loadFromFile("assets/endbottom.png");
        texturesMap[Tile::TileType::EndBottom] = texture;
        texture.loadFromFile("assets/endleft.png");
        texturesMap[Tile::TileType::EndLeft] = texture;
        texture.loadFromFile("assets/endright.png");
        texturesMap[Tile::TileType::EndRight] = texture;

        texture.loadFromFile("assets/lefttop.png");
        texturesMap[Tile::TileType::LeftTop] = texture;
        texture.loadFromFile("assets/leftbottom.png");
        texturesMap[Tile::TileType::LeftBottom] = texture;
        texture.loadFromFile("assets/topright.png");
        texturesMap[Tile::TileType::TopRight] = texture;
        texture.loadFromFile("assets/bottomright.png");
        texturesMap[Tile::TileType::BottomRight] = texture;
        texture.loadFromFile("assets/empty.png");
        texturesMap[Tile::TileType::Empty] = texture;

        if (!font.loadFromFile("assets/ChangaOne-Regular.ttf"))
            std::cout << "Can't load font ./assets/ChangaOne-Regular.ttf" << std::endl;

        bannerText.setFont(font);
        bannerText.setCharacterSize(30);
        bannerText.setStyle(sf::Text::Bold);
        bannerText.setColor(sf::Color::Black);
        bannerText.setString("Move the tiles with the mouse");
        bannerText.setPosition(30, 10);

        char game1[4][4] {'-','-','H','s',
                          '-','-','-','V',
                          '-','-','V','-',
                          '-','-','-','D'};


        char game2[4][4] {'S','H','H','l',
                         'e','r','l','V',
                         'V','T','D','V',
                         'R','H','H','L'};



        for (int x = 0; x < boardSize; ++x)
            for (int y = 0; y < boardSize; ++y) {
                Tile newTile {&window, tileSize, gridZeroZero, sf::Vector2i {x,y}};
                if (game1[y][x] == '-') {
                    newTile.setTileType(Tile::TileType::Empty);
                    newTile.setTexture(texturesMap[Tile::TileType::Empty]);
                } else if (game1[y][x] == 'H'){
                    newTile.setTileType(Tile::TileType::Horizontal);
                    newTile.setTexture(texturesMap[Tile::TileType::Horizontal]);
                } else if (game1[y][x] == 'V'){
                    newTile.setTileType(Tile::TileType::Vertical);
                    newTile.setTexture(texturesMap[Tile::TileType::Vertical]);

                } else if (game1[y][x] == 'R'){
                    newTile.setTileType(Tile::TileType::TopRight);
                    newTile.setTexture(texturesMap[Tile::TileType::TopRight]);
                } else if (game1[y][x] == 'L'){
                    newTile.setTileType(Tile::TileType::LeftTop);
                    newTile.setTexture(texturesMap[Tile::TileType::LeftTop]);
                } else if (game1[y][x] == 'l'){
                    newTile.setTileType(Tile::TileType::LeftBottom);
                    newTile.setTexture(texturesMap[Tile::TileType::LeftBottom]);
                } else if (game1[y][x] == 'r'){
                    newTile.setTileType(Tile::TileType::BottomRight);
                    newTile.setTexture(texturesMap[Tile::TileType::BottomRight]);

                } else if (game1[y][x] == 'S'){
                    newTile.setTileType(Tile::TileType::StartRight);
                    newTile.setTexture(texturesMap[Tile::TileType::StartRight]);
                } else if (game1[y][x] == 's'){
                    newTile.setTileType(Tile::TileType::StartBottom);
                    newTile.setTexture(texturesMap[Tile::TileType::StartBottom]);
                } else if (game1[y][x] == 'T'){
                    newTile.setTileType(Tile::TileType::StartTop);
                    newTile.setTexture(texturesMap[Tile::TileType::StartTop]);
                } else if (game1[y][x] == 't'){
                    newTile.setTileType(Tile::TileType::StartLeft);
                    newTile.setTexture(texturesMap[Tile::TileType::StartLeft]);

                } else if (game1[y][x] == 'D'){
                    newTile.setTileType(Tile::TileType::EndTop);
                    newTile.setTexture(texturesMap[Tile::TileType::EndTop]);
                } else if (game1[y][x] == 'd'){
                    newTile.setTileType(Tile::TileType::EndRight);
                    newTile.setTexture(texturesMap[Tile::TileType::EndRight]);
                } else if (game1[y][x] == 'E'){
                    newTile.setTileType(Tile::TileType::EndLeft);
                    newTile.setTexture(texturesMap[Tile::TileType::EndLeft]);
                } else if (game1[y][x] == 'e'){
                    newTile.setTileType(Tile::TileType::EndBottom);
                    newTile.setTexture(texturesMap[Tile::TileType::EndBottom]);
                } else {
                    newTile.setTileType(Tile::TileType::Empty);
                    newTile.setTexture(texturesMap[Tile::TileType::Empty]);
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
        Tile::TileType type = tiles[tilePos.x][tilePos.y].getTileType();
        sf::Vector2i nextTile {tilePos.x,tilePos.y};

        if (type == Tile::TileType::StartRight)
            ++nextTile.x;
        else if (type == Tile::TileType::StartLeft)
            --nextTile.x;
        else if (type == Tile::TileType::StartTop)
            --nextTile.y;


        else if (type == Tile::TileType::StartBottom)
            ++nextTile.y;
        else if (type == Tile::TileType::Horizontal && incomingDirection == Direction::GoRight)
            ++nextTile.x;
        else if (type == Tile::TileType::Horizontal && incomingDirection == Direction::GoLeft)
            --nextTile.x;
        else if (type == Tile::TileType::Vertical && incomingDirection == Direction::GoDown)
            ++nextTile.y;
        else if (type == Tile::TileType::Vertical && incomingDirection == Direction::GoUp)
            --nextTile.y;
        else if (type == Tile::TileType::LeftBottom && incomingDirection == Direction::GoRight)
            ++nextTile.y;
        else if (type == Tile::TileType::LeftBottom && incomingDirection == Direction::GoUp)
            --nextTile.x;
        else if (type == Tile::TileType::LeftTop && incomingDirection == Direction::GoDown)
            --nextTile.x;
        else if (type == Tile::TileType::LeftTop && incomingDirection == Direction::GoRight)
            --nextTile.y;
        else if (type == Tile::TileType::BottomRight && incomingDirection == Direction::GoUp)
            ++nextTile.x;
        else if (type == Tile::TileType::BottomRight && incomingDirection == Direction::GoLeft)
            ++nextTile.y;
        else if (type == Tile::TileType::TopRight && incomingDirection == Direction::GoLeft)
            --nextTile.y;
        else if (type == Tile::TileType::TopRight && incomingDirection == Direction::GoDown)
            ++nextTile.x;
        else if (type == Tile::TileType::EndBottom || type == Tile::TileType::EndLeft
            || type == Tile::TileType::EndRight || type == Tile::TileType::EndTop) {
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
        Tile::TileType type = tiles[tilePos.x][tilePos.y].getTileType();
        Direction outputDirection = Direction::Unknown;

        if (type == Tile::TileType::StartRight)
            return Direction::GoRight;
        else if (type == Tile::TileType::StartLeft)
            return Direction::GoLeft;
        else if (type == Tile::TileType::StartTop)
            return Direction::GoUp;
        else if (type == Tile::TileType::StartBottom)
            return Direction::GoDown;
        else if (type == Tile::TileType::Horizontal)
            return incomingDirection;
        else if (type == Tile::TileType::Vertical)
            return incomingDirection;
        else if (type == Tile::TileType::LeftBottom && incomingDirection == Direction::GoRight)
            return Direction::GoDown;
        else if (type == Tile::TileType::LeftBottom && incomingDirection == Direction::GoUp)
            return Direction::GoLeft;
        else if (type == Tile::TileType::LeftTop && incomingDirection == Direction::GoDown)
            return Direction::GoLeft;
        else if (type == Tile::TileType::LeftTop && incomingDirection == Direction::GoRight)
            return Direction::GoUp;
        else if (type == Tile::TileType::TopRight && incomingDirection == Direction::GoDown)
            return Direction::GoRight;
        else if (type == Tile::TileType::TopRight && incomingDirection == Direction::GoLeft)
            return Direction::GoUp;
        else if (type == Tile::TileType::BottomRight && incomingDirection == Direction::GoLeft)
            return Direction::GoDown;
        else if (type == Tile::TileType::BottomRight && incomingDirection == Direction::GoUp)
            return Direction::GoRight;
        else
            return Direction::Unknown;
    }


    std::vector<sf::Vector2i> Game::findSolution() {
        if ( ! shutUp ) std::cout << "findSolution\n";
        std::vector<sf::Vector2i> solutionPath {};

        bool startFound = false;
        sf::Vector2i startTile {0,0};
        for (int x = 0; (x < boardSize) && !startFound; ++x)
            for (int y = 0; (y < boardSize) && !startFound; ++y)
                if ( tiles[x][y].getTileType() == Tile::TileType::StartBottom
                    || tiles[x][y].getTileType() == Tile::TileType::StartTop
                    || tiles[x][y].getTileType() == Tile::TileType::StartLeft
                    || tiles[x][y].getTileType() == Tile::TileType::StartRight  ) {
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
        for (int x = 0; x < boardSize; ++x)
            for (int y = 0; y < boardSize; ++y)
                tiles[x][y].update(dt);

        // see if there is a solution
        std::vector<sf::Vector2i> solutionPath = findSolution();
        if ( solutionPath.size() > 0 ) {
            for ( auto tile : solutionPath )
                tiles[tile.x][tile.y].winner = true;
        } else {
            for (int x = 0; x < boardSize; ++x)
                for (int y = 0; y < boardSize; ++y)
                    tiles[x][y].winner = false;
        }
    }



    void Game::render()
    {
        window.clear(sf::Color::White);

        window.draw(bannerText);

        // first render the tiles that are static
        for (int x = 0; x < boardSize; ++x)
            for (int y = 0; y < boardSize; ++y)
                if ( ! tiles[x][y].transitioning )
                    tiles[x][y].render();

        // then render the tiles that are transitioning so that they are on top
        for (int x = 0; x < boardSize; ++x)
            for (int y = 0; y < boardSize; ++y)
                if ( tiles[x][y].transitioning )
                    tiles[x][y].render();

        window.display();
    }

    /**
    * Given the screen coordinates find the corresponding game coordinates in the model
    */
    sf::Vector2i Game::findTile(sf::Vector2i mousePosition) {
        sf::Vector2i gridCoordinates = mousePosition - gridZeroZero;
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
            << " transitioning: " << movingTile.transitioning
            << " isMoveable: " << movingTile.isMoveable << "\n";
        if ( ! movingTile.isMoveable )
            return false;

        // check for move off the board
        if ( newPosition.x >= boardSize
            || newPosition.y >= boardSize
            || newPosition.x < 0
            || newPosition.y < 0 )
            return false;

        // check if newPosition already taken
        if ( tiles[newPosition.x][newPosition.y].getTileType() != Tile::TileType::Empty )
            return false;

        return true;
    }


    void Game::slideTile(Tile movingTile, sf::Vector2i movingTilePosition, sf::Vector2i newPosition) {
        if ( canSlideTile(movingTile, movingTilePosition, newPosition ) ) {
            std::cout << "slide tile[" << movingTilePosition.x << "][" << movingTilePosition.y << "]"
                << " to [" << newPosition.x << "][" << newPosition.y << "]  tile reports x="
                << movingTile.gameBoardPosition.x << " y=" << movingTile.gameBoardPosition.y
                << " transitioning: " << movingTile.transitioning << "\n";
            movingTile.transition(newPosition);
            tiles[newPosition.x][newPosition.y] = movingTile;
            Tile newTile {&window, tileSize, gridZeroZero, movingTilePosition };
            newTile.setTileType(Tile::TileType::Empty);
            newTile.setTexture(texturesMap[Tile::TileType::Empty]);
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
