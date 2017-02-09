#pragma once

#include "direction.h"
#include <SFML/Graphics.hpp>
#include <sstream>

namespace SlidingTiles {
/**
 * @brief A Move of a tile
 */
class Move {
    public:
        /**
        * @brief A single step move for a tile at the supplied position in the
        * supplied direction
        * @param startPosition the game board coordinates of the moving tile
        * @param direction the direction to move in
        */
        Move( sf::Vector2i startPosition, SlidingTiles::Direction direction, std::vector<std::string> startingBoard )
            : startPosition(startPosition), direction(direction), startingBoard(startingBoard) {};

        /**
        * @brief the game board coordinates of the moving tile
        */
        sf::Vector2i startPosition;

        /**
        * @brief the direction we are moving in
        */
        SlidingTiles::Direction direction;

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
        std::vector <SlidingTiles::Move> possibleMoves {};

        /**
        * @brief expalins the move
        */
        std::string toString() {
            std::stringstream ss;
            ss << "Move startPosition: [" << startPosition.x << "][" << startPosition.y << "]";
            ss << " direction: " << directionToString(direction) << "\n";
            return ss.str();
        }

};

} // namespace SlidingTiles
