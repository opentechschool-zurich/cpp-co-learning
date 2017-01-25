#pragma once

#include <SFML/Graphics.hpp>
#include "tile.h"
#include <string>

/**
* @brief Singleton class that holds the information about the game state
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

        /**
        * @brief The number of tiles in each direction
        */
        static const int boardSize {4};

        /**
        * @brief The 2d array of tiles that makes up the game board
        */
        SlidingTiles::Tile tiles [boardSize][boardSize];

        /**
         * @brief load the game into the board
         */
        void loadGame( std::string game[GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]);

        /**
        * @brief for a given imput return the position of the next tile
        * @param tilePosition The position of the tile to query
        * @param direction the incoming direction to return the outgoing direction
        */
        sf::Vector2i getNextTilePosition(sf::Vector2i tilePosition, Direction direction);


    private:
        /**
        * @brief Private constructor for singleton
        */
        GameBoardSingleton();

};
