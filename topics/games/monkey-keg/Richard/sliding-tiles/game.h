#pragma once
#include "gameView.h"
#include "gameBoard.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include "button.h"
#include "label.h"
#include "json.hpp"
#include "randomSoundPlayer.h"

namespace SlidingTiles {

    /**
     * @brief The main game object. This class acts like the Controller and the 
     * Model in MVC and it owns the view (GameView)
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
        SlidingTiles::GameBoard gameBoard{};

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

        /**
         * @brief advance to the next level
         */
        void doLevelUp();

        /**
         * @brief the game states
         */
        enum GameState {
            Initializing,
            Playing,
            VictoryRolling
        };

        /**
         * @brief the state of the current game
         */
        GameState gameState{GameState::Initializing};

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
         * @brief the current level
         */
        std::size_t level{0};

        /**
         * @brief the "array" of levels, loaded from the JSON file
         */
        nlohmann::json levelsArray;

        /**
         * @brief loads the level indicated by the level member variable from the levelsArray
         */
        void loadLevel();

        /**
         * @brief opens a random level
         */
        void onRandomButtonClick();

        /**
         * @brief advances to the next level
         */
        void onNextButtonClick();

        /**
         * @brief restarts the level
         */
        void onRestartButtonClick();

        /**
         * @brief The number of tiles in each direction
         */
        static constexpr float VICTORY_ROLL_TIME{1.0f};

        /**
         *@brief The amount of time left for the victory roll in seconds.  
         */
        float victoryRollingTime{0.0f};

        /**
         * a Button for a random level
         */
        Button randomSfmlButton{"assets/button_random.png"};
        /**
         * a Button to go to the next level
         */
        Button nextSfmlButton{"assets/button_next.png"};
        /**
         * a restart button
         */
        Button restartSfmlButton{"assets/button_restart.png"};

        /**
         * a label to show the current level
         */
        Label levelLabel;

        /**
         * @brief the number of moves in the game
         */
        std::size_t moves{0};

        /**
         * a label to show the number of moves
         */
        Label movesLabel;


        /**
         * @brief the par number of moves in the game
         */
        std::size_t par{0};

        /**
         * a label to show the par number of moves
         */
        Label parLabel;

        /**
         * an object with winner sounds to be played randomly when a game is won 
         */
        RandomSoundPlayer winnerSounds;
        /**
         * an object with attitude sounds to be played randomly when the users is taking too long or restarts a level
         */
        RandomSoundPlayer attitudeSounds;

    };
}
