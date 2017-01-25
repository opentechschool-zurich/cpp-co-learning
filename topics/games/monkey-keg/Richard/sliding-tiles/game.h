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
#include "gameView.h"
#include "direction.h"
#include <string>

namespace SlidingTiles {

    /**
    * @brief The main game object
    */
    class Game {
    public:
        Game();

        void init();
        void update(const float dt);
        void run();


        GameView gameView;

    private:
        sf::Clock deltaClock;

        bool canSlideTile(sf::Vector2i movingTilePosition, sf::Vector2i newPosition);
        void slideTile(sf::Vector2i movingTilePosition, sf::Vector2i newPosition);


        sf::Vector2i mousePositionPressed;
        void doMouseReleased(sf::Vector2i mousePosition);

        std::vector<sf::Vector2i> findSolution();

        bool shutUp {false};
        sf::RenderWindow window;


    };
}
