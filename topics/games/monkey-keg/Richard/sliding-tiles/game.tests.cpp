#include "game.h"
#include <gmock/gmock.h>

using namespace ::testing;

TEST(Game, First_Test)
{
    ASSERT_THAT(1, Eq(1));
}
