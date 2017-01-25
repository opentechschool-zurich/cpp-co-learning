#include "gameBoardSingleton.h"
#include <gmock/gmock.h>
#include "tile.h"
#include <string>

using namespace ::testing;

TEST(GameBoardSingleton, ObjectCreation) {
    GameBoardSingleton::getInstance();
}

TEST(GameBoardSingleton, BoardSize) {
    ASSERT_EQ(4, GameBoardSingleton::boardSize);
}

TEST(GameBoardSingleton, loadGame) {
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

TEST(GameBoardSingleton, findNextTilePosition) {
    std::string game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
        {"├","-","-","┐",
         "┣","┐"," ","|",
         "┌","┘"," ","|",
         "└","-","-","┘"};
    GameBoardSingleton::getInstance().loadGame(game);
    sf::Vector2i tilePosition {0,0};
    sf::Vector2i nextTilePosition = GameBoardSingleton::getInstance().getNextTilePosition(tilePosition, Direction::Unknown);
    sf::Vector2i expectedPosition {1,0};
    ASSERT_EQ(expectedPosition, nextTilePosition)  << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    tilePosition.x = 1;
    tilePosition.y = 0;
    nextTilePosition = GameBoardSingleton::getInstance().getNextTilePosition(tilePosition, Direction::GoRight);
    expectedPosition.x = 2;
    expectedPosition.y = 0;
    ASSERT_EQ(expectedPosition, nextTilePosition)  << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    tilePosition.x = 3;
    tilePosition.y = 0;
    nextTilePosition = GameBoardSingleton::getInstance().getNextTilePosition(tilePosition, Direction::GoRight);
    expectedPosition.x = 3;
    expectedPosition.y = 1;
    ASSERT_EQ(expectedPosition, nextTilePosition)  << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    tilePosition.x = 3;
    tilePosition.y = 1;
    nextTilePosition = GameBoardSingleton::getInstance().getNextTilePosition(tilePosition, Direction::GoDown);
    expectedPosition.x = 3;
    expectedPosition.y = 2;
    ASSERT_EQ(expectedPosition, nextTilePosition)  << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    tilePosition.x = 3;
    tilePosition.y = 3;
    nextTilePosition = GameBoardSingleton::getInstance().getNextTilePosition(tilePosition, Direction::GoDown);
    expectedPosition.x = 2;
    expectedPosition.y = 3;
    ASSERT_EQ(expectedPosition, nextTilePosition)  << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    tilePosition.x = 2;
    tilePosition.y = 3;
    nextTilePosition = GameBoardSingleton::getInstance().getNextTilePosition(tilePosition, Direction::GoLeft);
    expectedPosition.x = 1;
    expectedPosition.y = 3;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    tilePosition.x = 0;
    tilePosition.y = 3;
    nextTilePosition = GameBoardSingleton::getInstance().getNextTilePosition(tilePosition, Direction::GoLeft);
    expectedPosition.x = 0;
    expectedPosition.y = 2;
    ASSERT_EQ(expectedPosition, nextTilePosition)  << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    tilePosition.x = 0;
    tilePosition.y = 2;
    nextTilePosition = GameBoardSingleton::getInstance().getNextTilePosition(tilePosition, Direction::GoUp);
    expectedPosition.x = 1;
    expectedPosition.y = 2;
    ASSERT_EQ(expectedPosition, nextTilePosition)  << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    tilePosition.x = 1;
    tilePosition.y = 1;
    nextTilePosition = GameBoardSingleton::getInstance().getNextTilePosition(tilePosition, Direction::GoUp);
    expectedPosition.x = 0;
    expectedPosition.y = 1;
    ASSERT_EQ(expectedPosition, nextTilePosition)  << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    tilePosition.x = 0;
    tilePosition.y = 1;
    nextTilePosition = GameBoardSingleton::getInstance().getNextTilePosition(tilePosition, Direction::GoLeft);
    expectedPosition.x = -2;
    expectedPosition.y = -2;
    ASSERT_EQ(expectedPosition, nextTilePosition)  << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
}


TEST(GameBoardSingleton, findNextTilePositionInvalid) {
    std::string game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
        {"├","-","-","┐",
         "┣","┐"," ","|",
         "┌","┘"," ","|",
         "└","-","-","┘"};
    GameBoardSingleton::getInstance().loadGame(game);
    sf::Vector2i tilePosition {1,0};
    sf::Vector2i nextTilePosition = GameBoardSingleton::getInstance().getNextTilePosition(tilePosition, Direction::Unknown);
    sf::Vector2i expectedPosition {-1,-1};
    ASSERT_EQ(expectedPosition, nextTilePosition)  << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    tilePosition.x = 1;
    tilePosition.y = 0;
    nextTilePosition = GameBoardSingleton::getInstance().getNextTilePosition(tilePosition, Direction::GoDown);
    expectedPosition.x = -1;
    expectedPosition.y = -1;
    ASSERT_EQ(expectedPosition, nextTilePosition)  << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
}
