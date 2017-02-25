#pragma once

#include <SFML/Graphics.hpp>
#include "tile.h"
#include <string>
#include <vector>
#include "moveNode.h"
#include "solution.h"
#include "direction.h"

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
         * @brief sets up a random game
         * @param emptyTiles the number of empty tiles to place defaults to 3
         */
        void randomGame(const int & emptyTiles = 3);


        /**
         * @brief saves the game into an array
         */
        std::vector<std::string> serialiseGame();

        /**
         * @brief prints the game to the console
         */
        void printGame();

        /**
         * @brief for a given input return the position of the next tile, If we hit a matching end tile
         * it returns -2,-2. If we can't end properly we return -1,-1
         * @param tilePosition The position of the tile to query
         * @param direction the incoming direction to return the outgoing direction
         */
        sf::Vector2i getNextTilePosition(const sf::Vector2i & tilePosition, const Direction & direction);

        /**
         * @brief Returns the adjacent tile in the direction
         * if no adjacent tile is possible it returns -1,-1
         * @param tilePos The position of the tile to query
         * @param direction the incoming direction to return the outgoing direction
         */
        sf::Vector2i getAdjacentTilePosition(const sf::Vector2i & tilePos, const Direction & direction);


        /**
         * @brief return whether a tile at the movingTilePosition can slide to
         * the newPosition.
         * @param movingTilePosition the position of the tile to move
         * @param newPosition the new position of the tile
         * @return true if a slide is allowed, false if not
         */
        bool canSlideTile(const sf::Vector2i & movingTilePosition, const sf::Vector2i & newPosition);

        /**
         * @brief return whether a tile at the movingTilePosition can slide in the supplied direction.
         * @param movingTilePosition the position of the tile to move
         * @param direction the direction to slide
         * @return true if a slide is allowed, false if not
         */
        bool canSlideTile(const sf::Vector2i & movingTilePosition, const Direction & direction);

        /**
         * @brief slides the tile from the movingTilePosition to the newPosition if
         * this is legal.
         * @param movingTilePosition the position of the tile to move
         * @param newPosition the new position of the tile
         */
        void slideTile(const sf::Vector2i & movingTilePosition, const sf::Vector2i & newPosition);

        /**
         * @brief slides the tile from the movingTilePosition to the newPosition if
         * this is legal.
         * @param move the movement
         */
        void slideTile(const SlidingTiles::Move & move);


        /**
         *  @brief returns the start tile on the gameboard. If none is found it returns -1,-1
         */
        sf::Vector2i findStartTile();

        /**
         *  @brief returns the start tile on the gameboard. If none is found it returns -1,-1
         */
        sf::Vector2i findEndTile();


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
