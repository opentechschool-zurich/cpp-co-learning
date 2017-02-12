#pragma once

#include "move.h"

namespace SlidingTiles {

    /**
     * @brief A Solution path
     */
    class Solution {
    public:
        /**
         * @brief the game board coordinates of the moving tile
         */
        std::vector<Move> moves{};
    };

} // namespace SlidingTiles
