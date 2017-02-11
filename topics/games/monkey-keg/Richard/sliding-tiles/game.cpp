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


    void Game::update(const float dt)
    {
        // send update event to all the tiles
        for (int x = 0; x < GameBoardSingleton::boardSize; ++x)
            for (int y = 0; y < GameBoardSingleton::boardSize; ++y)
                GameBoardSingleton::getInstance().tiles[x][y].tileView.update(dt);

        // see if there is a solution
        std::vector<sf::Vector2i> solutionPath = GameBoardSingleton::getInstance().isSolved();
        if ( solutionPath.size() > 0 ) {
            //std::cout << "Game is solved!\n";
            for ( auto tile : solutionPath )
                GameBoardSingleton::getInstance().tiles[tile.x][tile.y].setWinner(true);
        } else {
            //std::cout << "Not solved\n";
            for (int x = 0; x < GameBoardSingleton::boardSize; ++x)
                for (int y = 0; y < GameBoardSingleton::boardSize; ++y)
                    GameBoardSingleton::getInstance().tiles[x][y].setWinner(false);
        }
    }


    void Game::run() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                else if (event.type == sf::Event::MouseButtonPressed) {
                    mousePositionPressed = sf::Vector2i{event.mouseButton.x, event.mouseButton.y};
                } else if (event.type == sf::Event::MouseButtonReleased) {
                    doMouseReleased(sf::Vector2i {event.mouseButton.x, event.mouseButton.y});
                } else if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == 114) //r
                        GameBoardSingleton::getInstance().randomGame();
                    else if (event.text.unicode == 112) //p
                        GameBoardSingleton::getInstance().printGame();
                    else
                        std::cout << "ASCII character typed: " << event.text.unicode << " --> " << static_cast<char>(event.text.unicode) << std::endl;
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
                GameBoardSingleton::getInstance().slideTile(movingTilePosition, newPosition);
            } else {
                // vertical movement
                sf::Vector2i newPosition = sf::Vector2i(movingTilePosition.x, movingTilePosition.y + copysign(1, deltaY));
                GameBoardSingleton::getInstance().slideTile(movingTilePosition, newPosition);
            }
        }
    }

}
