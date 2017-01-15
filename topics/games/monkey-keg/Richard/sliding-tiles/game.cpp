#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include "game.h"

namespace SlidingTiles {
    Game::Game():
        window(sf::VideoMode(800, 600, 32), "Sliding tiles")
    {
    }

    sf::Font font;
    void Game::init()
    {
        window.setFramerateLimit(60);
        sf::Texture texture;
        texture.loadFromFile("assets/box.png");
        texturesMap[Tile::TileType::Textured] = texture;

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

        if (!font.loadFromFile("assets/ChangaOne-Regular.ttf"))
            std::cout << "Can't load font ./assets/ChangaOne-Regular.ttf" << std::endl;

        bannerText.setFont(font);
        bannerText.setCharacterSize(30);
        bannerText.setStyle(sf::Text::Bold);
        bannerText.setColor(sf::Color::Black);
        bannerText.setString("Move the tiles with the mouse");
        bannerText.setPosition(30, 10);

        char game2[4][4] {'-','-','H','s',
                          '-','-','-','V',
                          '-','-','-','V',
                          '-','-','-','D'};


        char game1[4][4] {'S','H','H','l',
                         'e','r','l','V',
                         'V','T','D','V',
                         'R','H','H','L'};



        for (int x = 0; x < boardSize; ++x)
            for (int y = 0; y < boardSize; ++y) {
                Tile newTile {&window, tileSize, gridZeroZero, sf::Vector2i {x,y}};
                if (game1[y][x] == '-')
                    newTile.setTileType(Tile::TileType::Empty);
                else if (game1[y][x] == 'H'){
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
                    newTile.setTileType(Tile::TileType::Textured);
                    newTile.setTexture(texturesMap[Tile::TileType::Textured]);
                }
                tiles[x][y] = newTile;
            }
    }

    void Game::update(const float dt)
    {
        for (int x = 0; x < boardSize; ++x)
            for (int y = 0; y < boardSize; ++y)
                tiles[x][y].update(dt);
    }



    void Game::render()
    {
        window.clear(sf::Color::White);

        window.draw(bannerText);

        for (int x = 0; x < boardSize; ++x)
            for (int y = 0; y < boardSize; ++y)
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
        return sf::Vector2i {xPos, yPos};
    }

    void Game::slideTile(Tile movingTile, sf::Vector2i movingTilePosition, sf::Vector2i newPosition) {
        movingTile.transition(newPosition);
        tiles[newPosition.x][newPosition.y] = movingTile;
        Tile newTile {&window, tileSize, gridZeroZero, movingTilePosition };
        newTile.setColor(sf::Color {10,20,30});
        tiles[movingTilePosition.x][movingTilePosition.y] = newTile;
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
