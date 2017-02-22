#include "game.h"
#include <gmock/gmock.h>

using namespace ::testing;
using namespace SlidingTiles;

TEST(Game, Constructor) {
    Game game{};
    ASSERT_THAT(1, Eq(1));
}

TEST(Game, DoRandomGame) {
    Game game{};
    game.doRandomGame();
    ASSERT_THAT(1, Eq(1));
}
