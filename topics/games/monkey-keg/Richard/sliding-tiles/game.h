#pragma once
#include "gameView.h"
#include "gameBoard.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "json.hpp"
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

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

        enum GameState {
            Initializing,
            Playing,
            VictoryRolling
        };

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
         * @brief loads the level indicated by the level member var from the levelsArray
         */
        void loadLevel();

        /**
         * @brief Winner sounds
         */
        std::vector<sf::SoundBuffer> winnerSoundBites;

        /**
         * @brief Attitude sounds
         */
        std::vector<sf::SoundBuffer> attitudeSoundBites;


        /**
         * @brief plays a winner soundbite
         */
        void playWinnerSoundBite();

        /**
         * @brief plays an attitude soundbite
         */
        void playAttitudeSoundBite();

        // Create an SFGUI. This is required before doing anything with SFGUI.
        sfg::SFGUI m_sfgui;

        // Create the label pointer here to reach it from OnButtonClick().
        sfg::Label::Ptr levelLabel;
        
        
         void OnButtonClick();
    };
}
