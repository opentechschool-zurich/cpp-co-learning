#pragma once

#include "direction.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include "move.h"

namespace SlidingTiles {
/**
 * @brief A Move with starting state, ending state and child MoveNodes
 */
class MoveNode : public Move {
    public:
        /**
        * @brief A single step move for a tile at the supplied position in the
        * supplied direction
        * @param startPosition the game board coordinates of the moving tile
        * @param direction the direction to move in
        */
        MoveNode( sf::Vector2i startPosition, SlidingTiles::Direction direction, std::vector<std::string> startingBoard )
            : Move(startPosition, direction), startingBoard(startingBoard) {};

        /**
        * @brief starting board (serialised)
        */
        std::vector <std::string> startingBoard {};

        /**
        * @brief ending board (serialised)
        */
        std::vector <std::string> endingBoard {};

        void setEndingBoard( std::vector <std::string> serialisedGame ) {
            endingBoard = serialisedGame;
        }

        /**
        * @brief next moves
        */
        std::vector <SlidingTiles::MoveNode> possibleMoves {};
};

} // namespace SlidingTiles
