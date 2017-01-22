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
#include "renderingSingleton.h"

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
        sf::Clock deltaClock;

        bool canSlideTile(sf::Vector2i movingTilePosition, sf::Vector2i newPosition);
        void slideTile(sf::Vector2i movingTilePosition, sf::Vector2i newPosition);

        sf::Text bannerText;

        sf::Vector2i mousePositionPressed;
        std::vector<sf::Vector2i> findSolution();
        sf::Vector2i getNextTile(sf::Vector2i tilePosition, Direction direction);
        Direction getTileDirection(sf::Vector2i tilePos, Direction incomingDirection);
        std::string directionToString(Direction direction);
        bool shutUp {false};
        sf::RenderWindow window;
        void doMouseReleased(sf::Vector2i mousePosition);

    };
}
