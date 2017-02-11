#include "gameBoardSingleton.h"
#include "move.h"
#include <gmock/gmock.h>

using namespace ::testing;
using namespace SlidingTiles;

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

TEST(GameBoardSingleton, saveAndLoadGame) {
    std::string game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
        {"├","-","-","┐",
         "┣","┐"," ","|",
         "┌","┘"," ","|",
         "└","-","-","┘"};
    GameBoardSingleton::getInstance().loadGame(game);

    std::vector<std::string> savedGame = GameBoardSingleton::getInstance().serialiseGame();
    std::string emptyGame [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
        {" "," "," "," ",
         " "," "," "," ",
         " "," "," "," ",
         " "," "," "," "};
    GameBoardSingleton::getInstance().loadGame(emptyGame);

    SlidingTiles::Tile t = GameBoardSingleton::getInstance().tiles[0][0];
    ASSERT_EQ(TileType::Empty, t.getTileType()) << "Tile 0,0 is of type " << tileTypeToString(t.getTileType());

    t = GameBoardSingleton::getInstance().tiles[1][0];
    ASSERT_EQ(TileType::Empty, t.getTileType()) << "Tile 1,0 is of type " << tileTypeToString(t.getTileType());

    //std::cout << savedGame << "\n";
    GameBoardSingleton::getInstance().loadGame(savedGame);

    t = GameBoardSingleton::getInstance().tiles[0][0];
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

    tilePosition.x = 3;
    tilePosition.y = 2;
    nextTilePosition = GameBoardSingleton::getInstance().getNextTilePosition(tilePosition, Direction::GoUp);
    expectedPosition.x = 3;
    expectedPosition.y = 1;
    ASSERT_EQ(expectedPosition, nextTilePosition)  << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

}

TEST(GameBoardSingleton, findNextTilePosition2) {
    std::string game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
        {"-","-","┤","┐",
         "┣","┐"," ","|",
         "┌","┘"," ","|",
         "└","-","-","┘"};
    GameBoardSingleton::getInstance().loadGame(game);
    sf::Vector2i tilePosition {2,0};
    sf::Vector2i nextTilePosition = GameBoardSingleton::getInstance().getNextTilePosition(tilePosition, Direction::Unknown);
    sf::Vector2i expectedPosition {1,0};
    ASSERT_EQ(expectedPosition, nextTilePosition)  << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
}

TEST(GameBoardSingleton, findNextTilePosition3) {
    std::string game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
    {" "," "," "," ",
     " ","-"," "," ",
     "├"," ","┫"," ",
     " ","-"," "," "};
    GameBoardSingleton::getInstance().loadGame(game);
    sf::Vector2i tilePosition {2,2};
    sf::Vector2i nextTilePosition = GameBoardSingleton::getInstance().getNextTilePosition(tilePosition, Direction::GoRight);
    sf::Vector2i expectedPosition {-2,-2};
    ASSERT_EQ(expectedPosition, nextTilePosition)  << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] of type: "
        << tileTypeToChar( GameBoardSingleton::getInstance().tiles[tilePosition.x][tilePosition.y].getTileType() ) << " getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
}

TEST(GameBoardSingleton, findNextTilePosition4) {
    std::string game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
        {"┬","-","-","┐",
         "|","┐"," ","|",
         "┌","┘"," ","|",
         "└","-","-","┘"};
    GameBoardSingleton::getInstance().loadGame(game);
    sf::Vector2i tilePosition {0,0};
    sf::Vector2i nextTilePosition = GameBoardSingleton::getInstance().getNextTilePosition(tilePosition, Direction::Unknown);
    sf::Vector2i expectedPosition {0,1};
    ASSERT_EQ(expectedPosition, nextTilePosition)  << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
}

TEST(GameBoardSingleton, findNextTilePosition5) {
    std::string game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
        {"┌","-","-","┐",
         "|","┐"," ","|",
         "┴","┘"," ","|",
         "└","-","-","┘"};
    GameBoardSingleton::getInstance().loadGame(game);
    sf::Vector2i tilePosition {0,2};
    sf::Vector2i nextTilePosition = GameBoardSingleton::getInstance().getNextTilePosition(tilePosition, Direction::Unknown);
    sf::Vector2i expectedPosition {0,1};
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


TEST(GameBoardSingleton, findAdjacentTilePosition) {
    std::string game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
        {"├","-","-","┐",
         "┣","┐"," ","|",
         "┌","┘"," ","|",
         "└","-","-","┘"};
    GameBoardSingleton::getInstance().loadGame(game);
    sf::Vector2i tilePosition {0,0};
    //std::cout << "First test unknown\n";
    sf::Vector2i nextTilePosition = GameBoardSingleton::getInstance().getAdjacentTilePosition(tilePosition, Direction::Unknown);
    sf::Vector2i expectedPosition {0,0};
    ASSERT_EQ(expectedPosition, nextTilePosition)  << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    //std::cout << "Second test go right\n";
    nextTilePosition = GameBoardSingleton::getInstance().getAdjacentTilePosition(tilePosition, Direction::GoRight);
    expectedPosition.x = 1;
    expectedPosition.y = 0;
    ASSERT_EQ(expectedPosition, nextTilePosition)  << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    //std::cout << "Now we want to go down...\n";
    nextTilePosition = GameBoardSingleton::getInstance().getAdjacentTilePosition(tilePosition, Direction::GoDown);
    expectedPosition.x = 0;
    expectedPosition.y = 1;
    ASSERT_EQ(expectedPosition, nextTilePosition)  << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    //std::cout << "Now we want to go left...\n";
    nextTilePosition = GameBoardSingleton::getInstance().getAdjacentTilePosition(tilePosition, Direction::GoLeft);
    expectedPosition.x = -1;
    expectedPosition.y = -1;
    ASSERT_EQ(expectedPosition, nextTilePosition)  << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    nextTilePosition = GameBoardSingleton::getInstance().getAdjacentTilePosition(tilePosition, Direction::GoUp);
    expectedPosition.x = -1;
    expectedPosition.y = -1;
    ASSERT_EQ(expectedPosition, nextTilePosition)  << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";


    tilePosition.x = 3;
    tilePosition.y = 0;
    nextTilePosition = GameBoardSingleton::getInstance().getAdjacentTilePosition(tilePosition, Direction::Unknown);
    expectedPosition.x = 3;
    expectedPosition.y = 0;
    ASSERT_EQ(expectedPosition, nextTilePosition)  << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    nextTilePosition = GameBoardSingleton::getInstance().getAdjacentTilePosition(tilePosition, Direction::GoRight);
    expectedPosition.x = -1;
    expectedPosition.y = -1;
    ASSERT_EQ(expectedPosition, nextTilePosition)  << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    nextTilePosition = GameBoardSingleton::getInstance().getAdjacentTilePosition(tilePosition, Direction::GoDown);
    expectedPosition.x = 3;
    expectedPosition.y = 1;
    ASSERT_EQ(expectedPosition, nextTilePosition)  << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    nextTilePosition = GameBoardSingleton::getInstance().getAdjacentTilePosition(tilePosition, Direction::GoLeft);
    expectedPosition.x = 2;
    expectedPosition.y = 0;
    ASSERT_EQ(expectedPosition, nextTilePosition)  << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    nextTilePosition = GameBoardSingleton::getInstance().getAdjacentTilePosition(tilePosition, Direction::GoUp);
    expectedPosition.x = -1;
    expectedPosition.y = -1;
    ASSERT_EQ(expectedPosition, nextTilePosition)  << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
}

TEST(GameBoardSingleton, canSlideTile) {
    std::string game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
        {"├","-","-","┐",
         "┣","┐"," ","|",
         "┌","┘"," ","|",
         "└","-","-","┘"};
    GameBoardSingleton::getInstance().loadGame(game);
    sf::Vector2i tilePosition {2,0};
    sf::Vector2i newPosition {2,1};
    ASSERT_TRUE( GameBoardSingleton::getInstance().canSlideTile(tilePosition, newPosition) ) << "This slide should work\n";
}


TEST(GameBoardSingleton, canSlideTileOccupied) {
    std::string game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
        {"├","-","-","┐",
         "┣","┐"," ","|",
         "┌","┘"," ","|",
         "└","-","-","┘"};
    GameBoardSingleton::getInstance().loadGame(game);
    sf::Vector2i tilePosition {2,0};
    sf::Vector2i newPosition {3,0};
    ASSERT_FALSE( GameBoardSingleton::getInstance().canSlideTile(tilePosition, newPosition) ) << "This slide should not work\n";
}


TEST(GameBoardSingleton, canSlideTileUnmoveables) {
    std::string game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
        {" ","├","-","┐",
         " ","┣"," ","┘",
         " "," ","-"," ",
         " "," "," "," "};
    GameBoardSingleton::getInstance().loadGame(game);
    sf::Vector2i tilePosition {1,0};
    sf::Vector2i newPosition {0,0};
    ASSERT_FALSE( GameBoardSingleton::getInstance().canSlideTile(tilePosition, newPosition) ) << "This slide should not work because it is a start tile\n";

    tilePosition.x = 1;
    tilePosition.y = 1;
    newPosition.x = 0;
    newPosition.y = 1;
    ASSERT_FALSE( GameBoardSingleton::getInstance().canSlideTile(tilePosition, newPosition) ) << "This slide should not work because it is an end tile\n";

    tilePosition.x = 1;
    tilePosition.y = 2;
    newPosition.x = 2;
    newPosition.y = 2;
    ASSERT_FALSE( GameBoardSingleton::getInstance().canSlideTile(tilePosition, newPosition) ) << "This slide should not work because it is an empty tile\n";
}

TEST(GameBoardSingleton, canSlideTileOffTheBoard) {
    std::string game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
        {" ","├","-","┐",
         " ","┣"," ","┘",
         " "," ","-"," ",
         "-"," "," ","-"};
    GameBoardSingleton::getInstance().loadGame(game);
    sf::Vector2i tilePosition {1,0};
    sf::Vector2i newPosition {1,-1};
    ASSERT_FALSE( GameBoardSingleton::getInstance().canSlideTile(tilePosition, newPosition) ) << "This slide should not work because the new tile is off the board\n";

    tilePosition.x = 3;
    tilePosition.y = 0;
    newPosition.x = 4;
    newPosition.y = 0;
    ASSERT_FALSE( GameBoardSingleton::getInstance().canSlideTile(tilePosition, newPosition) ) << "This slide should not work because the new tile is off the board\n";

    tilePosition.x = 0;
    tilePosition.y = 3;
    newPosition.x = -1;
    newPosition.y = 0;
    ASSERT_FALSE( GameBoardSingleton::getInstance().canSlideTile(tilePosition, newPosition) ) << "This slide should not work because the new tile is off the board\n";

    tilePosition.x = 0;
    tilePosition.y = 3;
    newPosition.x = 0;
    newPosition.y = 4;
    ASSERT_FALSE( GameBoardSingleton::getInstance().canSlideTile(tilePosition, newPosition) ) << "This slide should not work because the new tile is off the board\n";
}


TEST(GameBoardSingleton, isSolved) {
    std::string game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
        {" ","├","-","┐",
         " ","┣","-","┘",
         " "," ","-"," ",
         "-"," "," ","-"};
    GameBoardSingleton::getInstance().loadGame(game);
    std::vector<sf::Vector2i> result = GameBoardSingleton::getInstance().isSolved();
    ASSERT_THAT( 6, result.size() );
}

TEST(GameBoardSingleton, isSolved2) {
    std::string game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
        {" "," "," "," ",
         " ","-"," "," ",
         "├","-","┫"," ",
         " ","-"," "," "};
    GameBoardSingleton::getInstance().loadGame(game);
    std::vector<sf::Vector2i> result = GameBoardSingleton::getInstance().isSolved();
    ASSERT_THAT( 3, result.size() );
}



TEST(GameBoardSingleton, isNotSolved) {
    std::string game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
        {" ","├"," ","┐",
         " ","┣","-","┘",
         " "," ","-"," ",
         "-"," "," ","-"};
    GameBoardSingleton::getInstance().loadGame(game);
    std::vector<sf::Vector2i> result = GameBoardSingleton::getInstance().isSolved();
    ASSERT_THAT( 0, result.size() );
}

TEST(GameBoardSingleton, possibleMovesNone) {
    std::string game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
        {"├","┫"," "," ",
         " "," "," "," ",
         " "," "," "," ",
         " "," "," "," "};
    GameBoardSingleton::getInstance().loadGame(game);
    std::vector<SlidingTiles::MoveNode> possibleMoves = GameBoardSingleton::getInstance().possibleMoves();
    ASSERT_THAT(possibleMoves.size(), 0);
}

TEST(GameBoardSingleton, possibleMovesOne) {
    std::string game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
        {"├","-","┫"," ",
         " "," "," "," ",
         " "," "," "," ",
         " "," "," "," "};
    GameBoardSingleton::getInstance().loadGame(game);
    std::vector<SlidingTiles::MoveNode> possibleMoves = GameBoardSingleton::getInstance().possibleMoves();
    ASSERT_THAT(possibleMoves.size(), 1);
    SlidingTiles::MoveNode move = possibleMoves[0];
    sf::Vector2i expectedTile {1,0};
    ASSERT_EQ(move.startPosition, expectedTile)  << "Expect tile [1][0] to be a possible move but returned tile is [" << move.startPosition.x << "][" << move.startPosition.y << "] \n";
}

TEST(GameBoardSingleton, possibleMovesTwo) {
    std::string game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
        {"├","┫"," "," ",
         " "," "," "," ",
         " "," "," "," ",
         "-"," "," "," "};
    GameBoardSingleton::getInstance().loadGame(game);
    std::vector<SlidingTiles::MoveNode> possibleMoves = GameBoardSingleton::getInstance().possibleMoves();
    ASSERT_THAT(possibleMoves.size(), 2);
    SlidingTiles::MoveNode move = possibleMoves[0];
}

TEST(GameBoardSingleton, possibleMovesFour) {
    std::string game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
        {"├"," ","┫"," ",
         " ","-"," "," ",
         " "," "," "," ",
         " "," "," "," "};
    GameBoardSingleton::getInstance().loadGame(game);
    std::vector<SlidingTiles::MoveNode> possibleMoves = GameBoardSingleton::getInstance().possibleMoves();
    ASSERT_THAT(possibleMoves.size(), 4);
    SlidingTiles::MoveNode move = possibleMoves[0];
}

TEST(GameBoardSingleton, possibleMovesIsSolvedIn1Move) {
    std::string game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
        {"├"," ","┫"," ",
         " ","-"," "," ",
         " "," "," "," ",
         " "," "," "," "};
    GameBoardSingleton::getInstance().loadGame(game);
    std::vector<SlidingTiles::MoveNode> possibleMoves = GameBoardSingleton::getInstance().possibleMoves();
    ASSERT_THAT(possibleMoves.size(), 4);
    std::vector<Solution> solutions = GameBoardSingleton::getInstance().solutions(possibleMoves);
    ASSERT_THAT(solutions.size(), 1);
    Solution s = solutions[0];
    //std::cout << "s: " << s.moves.size() << "\n";
    Move m = s.moves[0];
    m.toString();
    sf::Vector2i expectedTile {1,1};
    ASSERT_EQ(m.startPosition, expectedTile)  << "Expect tile [1][1] to move up for solution but startPosition returned is [" << m.startPosition.x << "][" << m.startPosition.y << "] \n";
}

TEST(GameBoardSingleton, isSolvedIn2SingleMoves) {
    std::string game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
        {" "," "," "," ",
         " ","-"," "," ",
         "├"," ","┫"," ",
         " ","-"," "," "};
    GameBoardSingleton::getInstance().loadGame(game);
    std::vector<SlidingTiles::MoveNode> possibleMoves = GameBoardSingleton::getInstance().possibleMoves();
    ASSERT_THAT(possibleMoves.size(), 7);
    /*std::cout << "Possible moves:\n";
    for ( MoveNode m : possibleMoves ) {
        std::cout << m.toString();
    }*/
    std::vector<Solution> solutions = GameBoardSingleton::getInstance().solutions(possibleMoves);
    ASSERT_THAT(solutions.size(), 2);
}

TEST(GameBoardSingleton, addPossibleMoves) {
    // builds on possibleMovesOne
    std::string game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
        {"├","-","┫"," ",
         " "," "," "," ",
         " "," "," "," ",
         " "," "," "," "};
    GameBoardSingleton::getInstance().loadGame(game);
    std::vector<SlidingTiles::MoveNode> possibleMoves = GameBoardSingleton::getInstance().possibleMoves();
    ASSERT_THAT(possibleMoves.size(), 1);
    SlidingTiles::MoveNode moveNode = possibleMoves[0];
    sf::Vector2i expectedTile {1,0};
    ASSERT_EQ(moveNode.startPosition, expectedTile)  << "Expect tile [1][0] to be a possible move but returned tile is [" << moveNode.startPosition.x << "][" << moveNode.startPosition.y << "] \n";

    // now the addPossibleMoves stuff
    GameBoardSingleton::getInstance().addPossibleMoves( moveNode, 1 );
    ASSERT_THAT(moveNode.possibleMoves.size(), 4);
}


TEST(GameBoardSingleton, addPossibleMoves3Deep) {
    // builds on addPossibleMoves which builds on possibleMovesOne
    std::string game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
        {"├","-","┫"," ",
         " "," "," "," ",
         " "," "," "," ",
         " "," "," "," "};
    GameBoardSingleton::getInstance().loadGame(game);
    std::vector<SlidingTiles::MoveNode> possibleMoves = GameBoardSingleton::getInstance().possibleMoves();
    ASSERT_THAT(possibleMoves.size(), 1);
    SlidingTiles::MoveNode moveNode = possibleMoves[0];
    sf::Vector2i expectedStartTile {1,0};
    ASSERT_EQ(moveNode.startPosition, expectedStartTile)  << "Expect start tile [1][0] to be a possible move but returned tile is [" << moveNode.startPosition.x << "][" << moveNode.startPosition.y << "] \n";

    //std::cout << "\n\n---\n" << moveNode.toString() << "----\n";

    // now the addPossibleMoves stuff
    GameBoardSingleton::getInstance().addPossibleMoves( moveNode, 3 );
    //std::cout << "---\n" << moveNode.toString() << "----\n";
    ASSERT_THAT(moveNode.possibleMoves.size(), 4);


    int i = 0;
    for ( ; i < 4; ++i ) {
        //std::cout << "moveNode.possibleMoves["<<i<<"]: " << moveNode.possibleMoves[i].toString();
        if ( moveNode.possibleMoves[i].direction == Direction::GoDown ) {
            break;
        }
    }

    //std::cout << "Move going down found on index: " << i << "\n";
    //std::cout << moveNode.possibleMoves[i].toString();
    MoveNode secondMove = moveNode.possibleMoves[i];
    ASSERT_THAT( secondMove.direction, Direction::GoDown );
    ASSERT_THAT( secondMove.possibleMoves.size(), 4 );
}

bool hasASolutionOld( const MoveNode & node ) {
    for ( MoveNode n : node.possibleMoves ) {
        GameBoardSingleton::getInstance().loadGame( n.endingBoard );
        if ( GameBoardSingleton::getInstance().isSolved().size() > 0 ) {
            return true;
        };
    }
    return false;
}



TEST(GameBoardSingleton, isSolvedIn1Move) {
    std::string game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
        {"├"," ","┫"," ",
         " ","-"," "," ",
         " "," "," "," ",
         " "," "," "," "};
    GameBoardSingleton::getInstance().loadGame(game);
    SlidingTiles::MoveNode rootNode {sf::Vector2i{-1,-1}, Direction::Unknown, GameBoardSingleton::getInstance().serialiseGame() };
    rootNode.endingBoard = GameBoardSingleton::getInstance().serialiseGame();
    GameBoardSingleton::getInstance().addPossibleMoves( rootNode, 3 );
    ASSERT_TRUE( GameBoardSingleton::getInstance().hasASolution( rootNode ) ) << "There should be at least one solution for this puzzle";
}

TEST(GameBoardSingleton, isSolvedIn2Moves) {
    std::string game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
        {"├"," ","┫"," ",
         " "," "," "," ",
         " ","-"," "," ",
         " "," "," "," "};
    GameBoardSingleton::getInstance().loadGame(game);
    SlidingTiles::MoveNode rootNode {sf::Vector2i{-1,-1}, Direction::Unknown, GameBoardSingleton::getInstance().serialiseGame() };
    rootNode.endingBoard = GameBoardSingleton::getInstance().serialiseGame();
    GameBoardSingleton::getInstance().addPossibleMoves( rootNode, 3 );
    ASSERT_TRUE( GameBoardSingleton::getInstance().hasASolution( rootNode ) ) << "There should be at least one solution for this puzzle";
}

TEST(GameBoardSingleton, noSolution) {
    std::string game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
        {"├"," ","┫"," ",
         " ","|"," "," ",
         " "," "," "," ",
         " "," "," "," "};
    GameBoardSingleton::getInstance().loadGame(game);
    SlidingTiles::MoveNode rootNode {sf::Vector2i{-1,-1}, Direction::Unknown, GameBoardSingleton::getInstance().serialiseGame() };
    rootNode.endingBoard = GameBoardSingleton::getInstance().serialiseGame();
    GameBoardSingleton::getInstance().addPossibleMoves( rootNode, 3 );
    ASSERT_FALSE( GameBoardSingleton::getInstance().hasASolution( rootNode ) ) << "There should be at no solution for this puzzle";
}
