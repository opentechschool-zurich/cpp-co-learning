#pragma once

#include "move.h"

namespace SlidingTiles {

    /**
     * @brief A Solution path
     */
    class Solution {
    public:
        /**
         * @brief a vector of moves
         */
        std::vector<Move> moves{};
    };

} // namespace SlidingTiles
