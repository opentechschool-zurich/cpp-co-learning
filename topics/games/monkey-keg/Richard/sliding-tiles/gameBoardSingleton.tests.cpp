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

TEST(GameBoardSingleton, GridZeroZeroCoordinates)
{
    ASSERT_GT(GameBoardSingleton::getInstance().gridZeroZero.x, 10);
    ASSERT_GT(GameBoardSingleton::getInstance().gridZeroZero.y, 10);
}
