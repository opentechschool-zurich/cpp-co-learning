#pragma once

#include <SFML/Graphics.hpp>
#include "tile.h"
#include <string>
#include <vector>
#include "moveNode.h"
#include "solution.h"


namespace SlidingTiles {

    /**
     * @brief Singleton class that holds the information about the game state
     */
    class GameBoardSingleton {
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
        static GameBoardSingleton& getInstance() {
            static GameBoardSingleton instance; // Guaranteed to be destroyed.
            // Instantiated on first use.
            return instance;
        }

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
        void loadGame(const std::string game[GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]);

        /**
         * @brief load the game into the board
         */
        void loadGame(const std::vector<std::string> & game);

        /**
         * @brief sets up a random game
         */
        void randomGame();


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
         * @brief deepens the Search for possible moves and adds them to the MoveNode's possibleMoves recursively
         * @param moveNode the node on which to Search
         * @param levels how many levels deep to search 1 .. n
         */
        void addPossibleMoves(MoveNode &moveNode, const int & levels);

        /**
         * @brief returns a vector with solution moves. If there is no solution the vector has 0 elements
         */
        std::vector<Solution> solutions(const std::vector<MoveNode> & possibleMoves);


        /**
         * @brief figures out if the moves tree holds a solution
         */
        bool hasASolution(const MoveNode & node);


    private:
        /**
         * @brief Private constructor for singleton
         */
        GameBoardSingleton();

    };

} // namespace
