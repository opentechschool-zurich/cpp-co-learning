#pragma once

#include <SFML/Graphics.hpp>

/**
* @brief Singleton class that holds the information about the GameBoard
*/
class GameBoardSingleton
{
    public:
        /**
        * @brief Deleted to enforce singleton pattern
        */
        GameBoardSingleton(GameBoardSingleton const&) = delete;

        /**
        * @brief Deleted to enforce singleton pattern
        */
        void operator=(GameBoardSingleton const&) = delete;

        /**
        * @brief returns the single instance of the GameBoard singleton
        */
        static GameBoardSingleton& getInstance()
        {
            static GameBoardSingleton instance; // Guaranteed to be destroyed.
                                               // Instantiated on first use.
            return instance;
        }

        static const int boardSize {4};
        sf::Vector2i gridZeroZero { 100, 100 };

    private:
        /**
        * @brief Private constructor for singleton which loads the textures from disk
        * upon initialisation
        */
        GameBoardSingleton();

};
