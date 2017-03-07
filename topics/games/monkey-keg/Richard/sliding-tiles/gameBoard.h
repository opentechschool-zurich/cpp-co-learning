#pragma once

#include <SFML/Graphics.hpp>
#include "tile.h"
#include <vector>
#include "moveNode.h"

namespace SlidingTiles {

    /**
     * @brief A Game board
     */
    class GameBoard {
    public:
        /**
         * @brief The number of tiles in each direction
         */
        static const int boardSize{4};

        /**
         * @brief The 2d array of tiles that makes up the game board
         */
        SlidingTiles::Tile tiles [boardSize][boardSize];

        /**
         * @brief load the game into the board
         */
        void loadGame(const std::string game[boardSize][boardSize]);

        /**
         * @brief load the game into the board
         */
        void loadGame(const std::vector<std::string> & game);

        /**
         * @brief load the game into the board
         */
        void loadGame(const std::wstring & game);
        
        
        /**
         * @brief sets up a random game
         * @param emptyTiles the number of empty tiles to place defaults to 3
         */
        void randomGame(const int emptyTiles = 3);


        /**
         * @brief saves the game into an vector of string characters
         */
        std::vector<std::string> serialiseGame();
        
        /**
         * @brief saves the game into a string;
         */
        std::string serialiseGameToString();

        /**
         * @brief prints the game to the console
         */
        void printGame();
            
        /**
         * @brief Returns the adjacent tile in the supplied direction and check for off-the board condition.
         * If no adjacent tile is possible it returns -1,-1
         * @param move The position of the tile to query and the direction
         */
        sf::Vector2i getAdjacentTilePosition(const Move & move);

        /**
         * @brief return whether the move is possible
         * @param move the position of the tile to move and the direction in which to move it
         * @return true if a slide is allowed, false if not
         */
        bool canSlideTile(const Move & move);
        
        /**
         * @brief slides the tile from the movingTilePosition to the newPosition if
         * this is legal.
         * @param move the movement
         */
        void slideTile(const Move & move);

        /**
         *  @brief returns the start tile on the gameboard. If none is found it returns -1,-1
         */
        sf::Vector2i findStartTile();

        /**
         *  @brief returns the start tile on the gameboard. If none is found it returns -1,-1
         */
        sf::Vector2i findEndTile();

        /**
         * @brief Used to find a solution by returning the output tile if we 
         * roll a ball into the tile from the supplied direction.
         * If we hit a matching end tile it returns -2,-2. If we can't end properly 
         * because of an off the board or empty tile we return -1,-1
         * @param move The move to for the ball
         */
        sf::Vector2i getOutputPosition(const Move & move);
        
        /**
         * @brief returns if the puzzle is in a solved state by checking the path
         * from the start tile to the end tile.
         * @return a vector with the tile positions of the solution if solved otherwise returns an empty vector
         */
        std::vector<sf::Vector2i> isSolved();

        /**
         * @brief sets the winner tiles to winner true
         */
        void setWinnerTiles(std::vector<sf::Vector2i> & solutionPath) {
            for (auto tile : solutionPath)
                tiles[tile.x][tile.y].setWinner(true);
        }

        /**
         * @brief sets all tiles back to no winner status
         */
        void clearWinnerTiles() {
            for (int x = 0; x < boardSize; ++x)
                for (int y = 0; y < boardSize; ++y)
                    tiles[x][y].setWinner(false);
        }

    };

} // namespace
