#pragma once

#include <SFML/Graphics.hpp>
#include "tile.h"
#include <string>
#include <vector>
#include "moveNode.h"
#include "solution.h"
#include "direction.h"
#include "gameBoard.h"

namespace SlidingTiles {

    /**
     * @brief A Puzzle Solver class
     */
    class PuzzleSolver {
    public:
        /**
         * @brief My game board
         */
        GameBoard gameBoard;

        /**
         * @brief returns all moves that are possible on the current gameboard
         */
        std::vector<SlidingTiles::MoveNode> possibleMoves(const std::vector<std::string> & gameState);

        /**
         * @brief deepens the Search for possible moves and adds them to the MoveNode's possibleMoves recursively
         * @param moveNode the node on which to Search
         * @param levels how many levels deep to search 1 .. n
         */
        void addPossibleMoves(MoveNode & moveNode, const int & levels);

        /**
         * @brief returns a vector with solution moves out of the tree of all 
         * possible moves. If there is no solution the vector has 0 elements.
         */
        std::vector<Solution> solutions(const std::vector<std::string> & gameState, const std::vector<MoveNode> & possibleMoves);

        /**
         * @brief figures out if the moves tree holds a solution
         */
        bool hasASolution(const MoveNode & node);

    };

} // namespace
