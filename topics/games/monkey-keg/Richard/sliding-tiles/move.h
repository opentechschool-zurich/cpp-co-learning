#pragma once

#include "direction.h"
#include <SFML/Graphics.hpp>

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
        Move( sf::Vector2i startPosition, Direction direction )
            : startPosition(startPosition), direction(direction) {};

        /**
        * @brief the game board coordinates of the moving tile
        */
        sf::Vector2i startPosition;

        /**
        * @brief the direction we are moving in
        */
        Direction direction;
};

} // namespace SlidingTiles
