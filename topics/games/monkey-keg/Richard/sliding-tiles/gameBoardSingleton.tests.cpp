#include "gameBoardSingleton.h"
#include <gmock/gmock.h>

using namespace ::testing;

TEST(GameBoardSingleton, ObjectCreation)
{
    GameBoardSingleton::getInstance();
}

TEST(GameBoardSingleton, BoardSize)
{
    ASSERT_EQ(4, GameBoardSingleton::boardSize);
}
