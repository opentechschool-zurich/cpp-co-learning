#pragma once

#include "direction.h"
#include "gameBoardSingleton.h"
#include "gameView.h"
#include "renderingSingleton.h"
#include "tile.h"
#include "tileType.h"
#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <string>
#include <vector>

namespace SlidingTiles {

    /**
    * @brief The main game object
    */
    class Game {
    public:
        /**
        * @brief Constructor for the game
        */
        Game();

        /**
        * @brief initialises the game
        */
        void init();

        /**
        * @brief update call to modify the model with a delta time in seconds
        */
        void update(const float dt);

        /**
        * @brief entry point for the game
        */
        void run();

        /**
        * @brief the view for the game
        */
        GameView gameView;

    private:
        /**
        * @brief the clock
        */
        sf::Clock deltaClock;

        /**
        * @brief the position of the mouse press to determine the direction of the slide
        */
        sf::Vector2i mousePositionPressed;

        /**
        * @brief the function that figures out what to do when the mouse was released
        */
        void doMouseReleased(sf::Vector2i mousePosition);

        /**
        * @brief the render window
        */
        sf::RenderWindow window;
    };
}
