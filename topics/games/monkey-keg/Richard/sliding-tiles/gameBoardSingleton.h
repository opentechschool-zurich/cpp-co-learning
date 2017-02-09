#pragma once

#include <SFML/Graphics.hpp>
#include "tile.h"
#include <string>
#include <vector>
#include "moveNode.h"


namespace SlidingTiles {

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
         * @brief load the game into the board
         */
        void loadGame( std::vector<std::string> game);

        /**
         * @brief saves the game into an array
         */
        std::vector<std::string> serialiseGame();


        /**
        * @brief for a given imput return the position of the next tile
        * @param tilePosition The position of the tile to query
        * @param direction the incoming direction to return the outgoing direction
        */
        sf::Vector2i getNextTilePosition(sf::Vector2i tilePosition, Direction direction);

        /**
        * @brief Returns the adjacent tile in the direction
        * if no adjacent tile is possible it returns -1,-1
        * @param tilePos The position of the tile to query
        * @param direction the incoming direction to return the outgoing direction
        */
        sf::Vector2i getAdjacentTilePosition(sf::Vector2i tilePos, Direction direction);


        /**
        * @brief return whether a tile at the movingTilePosition can slide to
        * the newPosition.
        * @param movingTilePosition the position of the tile to move
        * @param newPosition the new position of the tile
        * @return true if a slide is allowed, false if not
        */
        bool canSlideTile(sf::Vector2i movingTilePosition, sf::Vector2i newPosition);

        /**
        * @brief return whether a tile at the movingTilePosition can slide in the supplied direction.
        * @param movingTilePosition the position of the tile to move
        * @param direction the direction to slide
        * @return true if a slide is allowed, false if not
        */
        bool canSlideTile(sf::Vector2i movingTilePosition, Direction direction);

        /**
        * @brief slides the tile from the movingTilePosition to the newPosition if
        * this is legal.
        * @param movingTilePosition the position of the tile to move
        * @param newPosition the new position of the tile
        */
        void slideTile(sf::Vector2i movingTilePosition, sf::Vector2i newPosition);

        /**
        * @brief slides the tile from the movingTilePosition to the newPosition if
        * this is legal.
        * @param move the movement
        */
        void slideTile(SlidingTiles::Move move);


        /**
        * @brief returns if the puzzle is in a solved state by checkin the path
        * from the start tile to the end tile.
        * @return a vector with the tile positions of the solution if solved otherwise rturns an empty vector
        */
        std::vector<sf::Vector2i> isSolved();

        /**
        * @brief returns all moves that are possible on the current gameboard
        */
        std::vector<SlidingTiles::MoveNode> possibleMoves();

        /**
        * @brief returns a vector with moves that lead to a solution if there is no solution the vector has 0 elements
        */
        std::vector<MoveNode> solutions (std::vector<MoveNode> possibleMoves);


    private:
        /**
        * @brief Private constructor for singleton
        */
        GameBoardSingleton();

};

} // namespace
