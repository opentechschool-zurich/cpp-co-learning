#pragma once

#include "direction.h"
#include <SFML/Graphics.hpp>

namespace SlidingTiles {
/**
 * @brief A Move of a tile
 */
class Move {
    public:
      Move( sf::Vector2i startPosition, Direction direction )
          : startPosition(startPosition), direction(direction) {};
        sf::Vector2i startPosition;
        Direction direction;
};

} // namespace SlidingTiles
