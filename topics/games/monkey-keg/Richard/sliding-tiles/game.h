#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include "tile.h"
#include <vector>
#include <cmath>
#include <iostream>
#include "tileType.h"
#include "gameBoardSingleton.h"

namespace SlidingTiles {
    class Game
    {
    public:
        Game();

        void init();
        void update(const float dt);
        void render();
        void run();

        enum Direction {
            Unknown, GoLeft, GoRight, GoUp, GoDown
        };

    private:
        sf::RenderWindow window;
        sf::Clock deltaClock;

        bool canSlideTile(Tile movingTile, sf::Vector2i movingTilePosition, sf::Vector2i newPosition);
        void slideTile(Tile movingTile, sf::Vector2i movingTilePosition, sf::Vector2i newPosition);

        sf::Text bannerText;
        Tile tiles [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize];

        sf::Vector2i mousePositionPressed;
        static const int tileSize {60};
        sf::Vector2i findTile(sf::Vector2i mousePosition);
        std::vector<sf::Vector2i> findSolution();
        sf::Vector2i getNextTile(sf::Vector2i tilePosition, Direction direction);
        Direction getTileDirection(sf::Vector2i tilePos, Direction incomingDirection);
        std::string directionToString(Direction direction);
        bool shutUp {false};


    };
}
