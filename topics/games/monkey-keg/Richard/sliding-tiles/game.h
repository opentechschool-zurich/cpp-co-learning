#pragma once
#include "gameView.h"
#include "gameBoard.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>

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
         * @brief update call to modify the model with a delta time in seconds
         */
        void update(const float & dt);

        /**
         * @brief entry point for the game
         */
        void run();

        /**
         * @brief the main gameboard of the game
         */
        SlidingTiles::GameBoard gameBoard {};
        
        /**
         * @brief the view for the game
         */
        SlidingTiles::GameView gameView;

        /**
         * @brief handler method for when the user wants to play a new random game
         */
        void doRandomGame();

        /**
         * @brief handler for the mouse pressed. Essentially records the coordinates
         */
        void doMousePressed(const sf::Vector2i & mousePosition);
        
        /**
         * @brief the function that figures out what to do when the mouse was released
         */
        void doMouseReleased(const sf::Vector2i & mousePosition);

    private:
        /**
         * @brief the clock
         */
        sf::Clock deltaClock;

        /**
         * @brief the position of the mouse press to determine the direction of the slide
         */
        sf::Vector2i mousePositionPressed;

    };
}
