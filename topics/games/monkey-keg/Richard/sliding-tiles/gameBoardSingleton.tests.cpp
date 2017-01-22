#include "gameBoardSingleton.h"
#include <gmock/gmock.h>
#include "tile.h"

using namespace ::testing;

TEST(GameBoardSingleton, ObjectCreation)
{
    GameBoardSingleton::getInstance();
}

TEST(GameBoardSingleton, BoardSize)
{
    ASSERT_EQ(4, GameBoardSingleton::boardSize);
}

TEST(GameBoardSingleton, loadGame)
{
    char game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
                    {'S','-','-','l',
                     'e',' ',' ','V',
                     'V',' ',' ','V',
                     'R','-','-','L'};
    GameBoardSingleton::getInstance().loadGame(game);
    SlidingTiles::Tile t = GameBoardSingleton::getInstance().tiles[0][0];
    ASSERT_EQ(TileType::StartRight, t.getTileType());
}
