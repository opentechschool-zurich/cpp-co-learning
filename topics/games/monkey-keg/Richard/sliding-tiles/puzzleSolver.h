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
        //std::vector<SlidingTiles::MoveNode> possibleMoves(const std::vector<std::string> & gameState);
        std::vector<SlidingTiles::MoveNode> possibleMoves(const MoveNode & parentNode);

        /**
         * @brief Adds the possibleMoves as MoveNodes to the supplied MoveNode
         * @param moveNode the node on which to Search and add the new Moves
         * @param levels how many levels deep to search 1 .. n
         */
        void addPossibleMoves(MoveNode & moveNode, const int & levels);

        /**
         * @brief returns the root node with the whole tree attached to it.
         * @param game The serialised game
         */
        MoveNode getTree(std::vector<std::string> game);
        
        /**
         * @brief returns a vector with solution moves out of the tree of all 
         * possible moves. If there is no solution the vector has 0 elements.
         */
        //std::vector<Solution> solutions(const std::vector<std::string> & gameState, const std::vector<MoveNode> & possibleMoves);

        /**
         * @brief figures out if the moves tree holds a solution
         * @details Used a breadth-first search to visit all MoveNode nodes. 
         * Since each MoveNode has the endGameState we can load that state
         * into a GameBoard and ask the GameBoard if it is solved.
         */
        bool hasASolution(const MoveNode & node);

    };

} // namespace
