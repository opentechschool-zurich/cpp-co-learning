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

TEST(GameBoardSingleton, findNextTilePosition4) {
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
    std::cout << "First test unknown\n";
    sf::Vector2i nextTilePosition = GameBoardSingleton::getInstance().getAdjacentTilePosition(tilePosition, Direction::Unknown);
    sf::Vector2i expectedPosition {0,0};
    ASSERT_EQ(expectedPosition, nextTilePosition)  << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    std::cout << "Second test go right\n";
    nextTilePosition = GameBoardSingleton::getInstance().getAdjacentTilePosition(tilePosition, Direction::GoRight);
    expectedPosition.x = 1;
    expectedPosition.y = 0;
    ASSERT_EQ(expectedPosition, nextTilePosition)  << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    std::cout << "Now we want to go down...\n";
    nextTilePosition = GameBoardSingleton::getInstance().getAdjacentTilePosition(tilePosition, Direction::GoDown);
    expectedPosition.x = 0;
    expectedPosition.y = 1;
    ASSERT_EQ(expectedPosition, nextTilePosition)  << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    std::cout << "Now we want to go left...\n";
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
    std::vector<SlidingTiles::Move> possibleMoves = GameBoardSingleton::getInstance().possibleMoves();
    ASSERT_THAT(possibleMoves.size(), 0);
}

TEST(GameBoardSingleton, possibleMovesOne) {
    std::string game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
        {"├","-","┫"," ",
         " "," "," "," ",
         " "," "," "," ",
         " "," "," "," "};
    GameBoardSingleton::getInstance().loadGame(game);
    std::vector<SlidingTiles::Move> possibleMoves = GameBoardSingleton::getInstance().possibleMoves();
    ASSERT_THAT(possibleMoves.size(), 1);
    SlidingTiles::Move move = possibleMoves[0];
}

TEST(GameBoardSingleton, possibleMovesTwo) {
    std::string game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
        {"├","┫"," "," ",
         " "," "," "," ",
         " "," "," "," ",
         "-"," "," "," "};
    GameBoardSingleton::getInstance().loadGame(game);
    std::vector<SlidingTiles::Move> possibleMoves = GameBoardSingleton::getInstance().possibleMoves();
    ASSERT_THAT(possibleMoves.size(), 2);
    SlidingTiles::Move move = possibleMoves[0];
}

TEST(GameBoardSingleton, possibleMovesFour) {
    std::string game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
        {"├"," ","┫"," ",
         " ","-"," "," ",
         " "," "," "," ",
         " "," "," "," "};
    GameBoardSingleton::getInstance().loadGame(game);
    std::vector<SlidingTiles::Move> possibleMoves = GameBoardSingleton::getInstance().possibleMoves();
    ASSERT_THAT(possibleMoves.size(), 4);
    SlidingTiles::Move move = possibleMoves[0];
}


TEST(GameBoardSingleton, possibleMovesIsSolved) {
    std::string game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
        {"├"," ","┫"," ",
         " ","-"," "," ",
         " "," "," "," ",
         " "," "," "," "};
    GameBoardSingleton::getInstance().loadGame(game);
    std::vector<SlidingTiles::Move> possibleMoves = GameBoardSingleton::getInstance().possibleMoves();
    ASSERT_THAT(possibleMoves.size(), 4);
    int solutions = 0;
    for ( Move move : possibleMoves ) {
        GameBoardSingleton::getInstance().loadGame(game);
        GameBoardSingleton::getInstance().slideTile(move);
        std::vector<sf::Vector2i> solutionPath = GameBoardSingleton::getInstance().isSolved();
        if ( solutionPath.size() > 0 ) {
            ++solutions;
        }
    }
    ASSERT_THAT(solutions, 1);
}
