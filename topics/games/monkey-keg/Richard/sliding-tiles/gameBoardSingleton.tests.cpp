#include "gameBoardSingleton.h"
#include <gmock/gmock.h>
#include "tile.h"
#include <string>

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
    std::string game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
        {"├","-","-","┐",
         "┣","┐"," ","|",
         "┌","┘"," ","|",
         "└","-","-","┘"};
    GameBoardSingleton::getInstance().loadGame(game);
    SlidingTiles::Tile t = GameBoardSingleton::getInstance().tiles[0][0];
    ASSERT_EQ(TileType::StartRight, t.getTileType()) << "Tile 0,0 is of type " << tileTypeToString(t.getTileType());

    t = GameBoardSingleton::getInstance().tiles[1][0];
    ASSERT_EQ(TileType::Horizontal, t.getTileType()) << "Tile 1,0 is of type " << tileTypeToString(t.getTileType());

    t = GameBoardSingleton::getInstance().tiles[2][0];
    ASSERT_EQ(TileType::Horizontal, t.getTileType()) << "Tile 2,0 is of type " << tileTypeToString(t.getTileType());

    t = GameBoardSingleton::getInstance().tiles[3][0];
    ASSERT_EQ(TileType::LeftBottom, t.getTileType()) << "Tile 3,0 is of type " << tileTypeToString(t.getTileType());

    t = GameBoardSingleton::getInstance().tiles[3][1];
    ASSERT_EQ(TileType::Vertical, t.getTileType()) << "Tile 3,1 is of type " << tileTypeToString(t.getTileType());

    t = GameBoardSingleton::getInstance().tiles[3][3];
    ASSERT_EQ(TileType::LeftTop, t.getTileType()) << "Tile 3,3 is of type " << tileTypeToString(t.getTileType());

    t = GameBoardSingleton::getInstance().tiles[0][3];
    ASSERT_EQ(TileType::TopRight, t.getTileType()) << "Tile 0,3 is of type " << tileTypeToString(t.getTileType());

    t = GameBoardSingleton::getInstance().tiles[0][2];
    ASSERT_EQ(TileType::BottomRight, t.getTileType()) << "Tile 0,2 is of type " << tileTypeToString(t.getTileType());

    t = GameBoardSingleton::getInstance().tiles[0][1];
    ASSERT_EQ(TileType::EndRight, t.getTileType()) << "Tile 0,1 is of type " << tileTypeToString(t.getTileType());


}
