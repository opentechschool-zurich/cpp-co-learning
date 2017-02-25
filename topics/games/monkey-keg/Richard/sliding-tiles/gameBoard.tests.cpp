#include "gameBoard.h"
#include "move.h"
#include <gmock/gmock.h>

using namespace::testing;
using namespace SlidingTiles;

TEST(GameBoard, BoardSize) {
    ASSERT_EQ(4, GameBoard::boardSize);
}

TEST(GameBoard, loadGame) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"├", "-", "-", "┐",
        "┣", "┐", " ", "|",
        "┌", "┘", " ", "|",
        "└", "-", "-", "┘"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    SlidingTiles::Tile t = gameBoard.tiles[0][0];
    ASSERT_EQ(TileType::StartRight, t.getTileType()) << "Tile 0,0 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[1][0];
    ASSERT_EQ(TileType::Horizontal, t.getTileType()) << "Tile 1,0 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[2][0];
    ASSERT_EQ(TileType::Horizontal, t.getTileType()) << "Tile 2,0 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[3][0];
    ASSERT_EQ(TileType::LeftBottom, t.getTileType()) << "Tile 3,0 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[3][1];
    ASSERT_EQ(TileType::Vertical, t.getTileType()) << "Tile 3,1 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[3][3];
    ASSERT_EQ(TileType::LeftTop, t.getTileType()) << "Tile 3,3 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[0][3];
    ASSERT_EQ(TileType::TopRight, t.getTileType()) << "Tile 0,3 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[0][2];
    ASSERT_EQ(TileType::BottomRight, t.getTileType()) << "Tile 0,2 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[0][1];
    ASSERT_EQ(TileType::EndRight, t.getTileType()) << "Tile 0,1 is of type " << tileTypeToString(t.getTileType());
}

TEST(GameBoard, saveAndLoadGame) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"├", "-", "-", "┐",
        "┣", "┐", " ", "|",
        "┌", "┘", " ", "|",
        "└", "-", "-", "┘"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);

    std::vector<std::string> savedGame = gameBoard.serialiseGame();
    std::string emptyGame [GameBoard::boardSize][GameBoard::boardSize]{" ", " ", " ", " ",
        " ", " ", " ", " ",
        " ", " ", " ", " ",
        " ", " ", " ", " "};
    gameBoard.loadGame(emptyGame);

    SlidingTiles::Tile t = gameBoard.tiles[0][0];
    ASSERT_EQ(TileType::Empty, t.getTileType()) << "Tile 0,0 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[1][0];
    ASSERT_EQ(TileType::Empty, t.getTileType()) << "Tile 1,0 is of type " << tileTypeToString(t.getTileType());

    gameBoard.loadGame(savedGame);

    t = gameBoard.tiles[0][0];
    ASSERT_EQ(TileType::StartRight, t.getTileType()) << "Tile 0,0 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[1][0];
    ASSERT_EQ(TileType::Horizontal, t.getTileType()) << "Tile 1,0 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[2][0];
    ASSERT_EQ(TileType::Horizontal, t.getTileType()) << "Tile 2,0 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[3][0];
    ASSERT_EQ(TileType::LeftBottom, t.getTileType()) << "Tile 3,0 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[3][1];
    ASSERT_EQ(TileType::Vertical, t.getTileType()) << "Tile 3,1 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[3][3];
    ASSERT_EQ(TileType::LeftTop, t.getTileType()) << "Tile 3,3 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[0][3];
    ASSERT_EQ(TileType::TopRight, t.getTileType()) << "Tile 0,3 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[0][2];
    ASSERT_EQ(TileType::BottomRight, t.getTileType()) << "Tile 0,2 is of type " << tileTypeToString(t.getTileType());

    t = gameBoard.tiles[0][1];
    ASSERT_EQ(TileType::EndRight, t.getTileType()) << "Tile 0,1 is of type " << tileTypeToString(t.getTileType());
}

TEST(GameBoard, randomGame) {
    GameBoard gameBoard{};
    gameBoard.randomGame();
    int startTiles{0};
    int endTiles{0};
    int gameTiles{0};
    int emptyTiles{0};
    for (int x = 0; x < GameBoard::boardSize; ++x) {
        for (int y = 0; y < GameBoard::boardSize; ++y) {
            TileType t = gameBoard.tiles[x][y].getTileType();
            if (isStartTileType(t)) {
                ++startTiles;
            } else if (isEndTileType(t)) {
                ++endTiles;
            } else if (isGameTileType(t)) {
                ++gameTiles;
            } else if (t == TileType::Empty) {
                ++emptyTiles;
            }
        }
    }
    ASSERT_EQ(startTiles, 1) << "A random game must have 1 start tile";
    ASSERT_EQ(endTiles, 1) << "A random game must have 1 end tile";
    ASSERT_GE(emptyTiles, 1) << "A random game must have at least 1 empty tile";
}

TEST(GameBoard, findNextTilePosition) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"├", "-", "-", "┐",
        "┣", "┐", " ", "|",
        "┌", "┘", " ", "|",
        "└", "-", "-", "┘"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    sf::Vector2i tilePosition{0, 0};
    sf::Vector2i nextTilePosition = gameBoard.getNextTilePosition(tilePosition, Direction::Unknown);
    sf::Vector2i expectedPosition{1, 0};
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    tilePosition.x = 1;
    tilePosition.y = 0;
    nextTilePosition = gameBoard.getNextTilePosition(tilePosition, Direction::GoRight);
    expectedPosition.x = 2;
    expectedPosition.y = 0;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    tilePosition.x = 3;
    tilePosition.y = 0;
    nextTilePosition = gameBoard.getNextTilePosition(tilePosition, Direction::GoRight);
    expectedPosition.x = 3;
    expectedPosition.y = 1;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    tilePosition.x = 3;
    tilePosition.y = 1;
    nextTilePosition = gameBoard.getNextTilePosition(tilePosition, Direction::GoDown);
    expectedPosition.x = 3;
    expectedPosition.y = 2;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    tilePosition.x = 3;
    tilePosition.y = 3;
    nextTilePosition = gameBoard.getNextTilePosition(tilePosition, Direction::GoDown);
    expectedPosition.x = 2;
    expectedPosition.y = 3;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    tilePosition.x = 2;
    tilePosition.y = 3;
    nextTilePosition = gameBoard.getNextTilePosition(tilePosition, Direction::GoLeft);
    expectedPosition.x = 1;
    expectedPosition.y = 3;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    tilePosition.x = 0;
    tilePosition.y = 3;
    nextTilePosition = gameBoard.getNextTilePosition(tilePosition, Direction::GoLeft);
    expectedPosition.x = 0;
    expectedPosition.y = 2;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    tilePosition.x = 0;
    tilePosition.y = 2;
    nextTilePosition = gameBoard.getNextTilePosition(tilePosition, Direction::GoUp);
    expectedPosition.x = 1;
    expectedPosition.y = 2;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    tilePosition.x = 1;
    tilePosition.y = 1;
    nextTilePosition = gameBoard.getNextTilePosition(tilePosition, Direction::GoUp);
    expectedPosition.x = 0;
    expectedPosition.y = 1;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    tilePosition.x = 0;
    tilePosition.y = 1;
    nextTilePosition = gameBoard.getNextTilePosition(tilePosition, Direction::GoLeft);
    expectedPosition.x = -2;
    expectedPosition.y = -2;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    tilePosition.x = 3;
    tilePosition.y = 2;
    nextTilePosition = gameBoard.getNextTilePosition(tilePosition, Direction::GoUp);
    expectedPosition.x = 3;
    expectedPosition.y = 1;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

}

TEST(GameBoard, findNextTilePosition2) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"-", "-", "┤", "┐",
        "┣", "┐", " ", "|",
        "┌", "┘", " ", "|",
        "└", "-", "-", "┘"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    sf::Vector2i tilePosition{2, 0};
    sf::Vector2i nextTilePosition = gameBoard.getNextTilePosition(tilePosition, Direction::Unknown);
    sf::Vector2i expectedPosition{1, 0};
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
}

TEST(GameBoard, findNextTilePosition3) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{" ", " ", " ", " ",
        " ", "-", " ", " ",
        "├", " ", "┫", " ",
        " ", "-", " ", " "};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    sf::Vector2i tilePosition{2, 2};
    sf::Vector2i nextTilePosition = gameBoard.getNextTilePosition(tilePosition, Direction::GoRight);
    sf::Vector2i expectedPosition{-2, -2};
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] of type: "
            << tileTypeToChar(gameBoard.tiles[tilePosition.x][tilePosition.y].getTileType()) << " getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
}

TEST(GameBoard, findNextTilePosition4) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"┬", "-", "-", "┐",
        "|", "┐", " ", "|",
        "┌", "┘", " ", "|",
        "└", "-", "-", "┘"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    sf::Vector2i tilePosition{0, 0};
    sf::Vector2i nextTilePosition = gameBoard.getNextTilePosition(tilePosition, Direction::Unknown);
    sf::Vector2i expectedPosition{0, 1};
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
}

TEST(GameBoard, findNextTilePosition5) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"┌", "-", "-", "┐",
        "|", "┐", " ", "|",
        "┴", "┘", " ", "|",
        "└", "-", "-", "┘"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    sf::Vector2i tilePosition{0, 2};
    sf::Vector2i nextTilePosition = gameBoard.getNextTilePosition(tilePosition, Direction::Unknown);
    sf::Vector2i expectedPosition{0, 1};
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
}

TEST(GameBoard, findNextTilePositionInvalid1) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"├", "-", "-", "┐",
        "┣", "┐", " ", "|",
        "┌", "┘", " ", "|",
        "└", "-", "-", "┘"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    sf::Vector2i tilePosition{1, 0};
    sf::Vector2i nextTilePosition = gameBoard.getNextTilePosition(tilePosition, Direction::Unknown);
    sf::Vector2i expectedPosition{-1, -1};
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    tilePosition.x = 1;
    tilePosition.y = 0;
    nextTilePosition = gameBoard.getNextTilePosition(tilePosition, Direction::GoDown);
    expectedPosition.x = -1;
    expectedPosition.y = -1;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
}

TEST(GameBoard, findNextTilePositionInvalid2) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"|", "┘", " ", "-",
        "|", "├", "-", "┳",
        "┘", "-", " ", "|",
        " ", "|" "-", "|"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    sf::Vector2i tilePosition{3, 1};
    sf::Vector2i nextTilePosition = gameBoard.getNextTilePosition(tilePosition, Direction::GoRight);
    sf::Vector2i expectedPosition{-1, -1};
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    nextTilePosition = gameBoard.getNextTilePosition(tilePosition, Direction::GoUp);
    expectedPosition.x = -2;
    expectedPosition.y = -2;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getNextTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
}

TEST(GameBoard, findAdjacentTilePosition) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"├", "-", "-", "┐",
        "┣", "┐", " ", "|",
        "┌", "┘", " ", "|",
        "└", "-", "-", "┘"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    sf::Vector2i tilePosition{0, 0};
    //std::cout << "First test unknown\n";
    sf::Vector2i nextTilePosition = gameBoard.getAdjacentTilePosition(tilePosition, Direction::Unknown);
    sf::Vector2i expectedPosition{0, 0};
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    //std::cout << "Second test go right\n";
    nextTilePosition = gameBoard.getAdjacentTilePosition(tilePosition, Direction::GoRight);
    expectedPosition.x = 1;
    expectedPosition.y = 0;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    //std::cout << "Now we want to go down...\n";
    nextTilePosition = gameBoard.getAdjacentTilePosition(tilePosition, Direction::GoDown);
    expectedPosition.x = 0;
    expectedPosition.y = 1;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    //std::cout << "Now we want to go left...\n";
    nextTilePosition = gameBoard.getAdjacentTilePosition(tilePosition, Direction::GoLeft);
    expectedPosition.x = -1;
    expectedPosition.y = -1;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    nextTilePosition = gameBoard.getAdjacentTilePosition(tilePosition, Direction::GoUp);
    expectedPosition.x = -1;
    expectedPosition.y = -1;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";


    tilePosition.x = 3;
    tilePosition.y = 0;
    nextTilePosition = gameBoard.getAdjacentTilePosition(tilePosition, Direction::Unknown);
    expectedPosition.x = 3;
    expectedPosition.y = 0;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    nextTilePosition = gameBoard.getAdjacentTilePosition(tilePosition, Direction::GoRight);
    expectedPosition.x = -1;
    expectedPosition.y = -1;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    nextTilePosition = gameBoard.getAdjacentTilePosition(tilePosition, Direction::GoDown);
    expectedPosition.x = 3;
    expectedPosition.y = 1;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    nextTilePosition = gameBoard.getAdjacentTilePosition(tilePosition, Direction::GoLeft);
    expectedPosition.x = 2;
    expectedPosition.y = 0;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";

    nextTilePosition = gameBoard.getAdjacentTilePosition(tilePosition, Direction::GoUp);
    expectedPosition.x = -1;
    expectedPosition.y = -1;
    ASSERT_EQ(expectedPosition, nextTilePosition) << "Tile[" << tilePosition.x << "][" << tilePosition.y << "] getAdjacentTilePosition returned: x[" << nextTilePosition.x << "][" << nextTilePosition.y << "] expected was: [" << expectedPosition.x << "][" << expectedPosition.y << "]\n";
}

TEST(GameBoard, canSlideTile) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"├", "-", "-", "┐",
        "┣", "┐", " ", "|",
        "┌", "┘", " ", "|",
        "└", "-", "-", "┘"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    sf::Vector2i tilePosition{2, 0};
    sf::Vector2i newPosition{2, 1};
    ASSERT_TRUE(gameBoard.canSlideTile(tilePosition, newPosition)) << "This slide should work\n";
}

TEST(GameBoard, canSlideTileOccupied) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"├", "-", "-", "┐",
        "┣", "┐", " ", "|",
        "┌", "┘", " ", "|",
        "└", "-", "-", "┘"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    sf::Vector2i tilePosition{2, 0};
    sf::Vector2i newPosition{3, 0};
    ASSERT_FALSE(gameBoard.canSlideTile(tilePosition, newPosition)) << "This slide should not work\n";
}

TEST(GameBoard, canSlideTileUnmoveables) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{" ", "├", "-", "┐",
        " ", "┣", " ", "┘",
        " ", " ", "-", " ",
        " ", " ", " ", " "};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    sf::Vector2i tilePosition{1, 0};
    sf::Vector2i newPosition{0, 0};
    ASSERT_FALSE(gameBoard.canSlideTile(tilePosition, newPosition)) << "This slide should not work because it is a start tile\n";

    tilePosition.x = 1;
    tilePosition.y = 1;
    newPosition.x = 0;
    newPosition.y = 1;
    ASSERT_FALSE(gameBoard.canSlideTile(tilePosition, newPosition)) << "This slide should not work because it is an end tile\n";

    tilePosition.x = 1;
    tilePosition.y = 2;
    newPosition.x = 2;
    newPosition.y = 2;
    ASSERT_FALSE(gameBoard.canSlideTile(tilePosition, newPosition)) << "This slide should not work because it is an empty tile\n";
}

TEST(GameBoard, canSlideTileOffTheBoard) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{" ", "├", "-", "┐",
        " ", "┣", " ", "┘",
        " ", " ", "-", " ",
        "-", " ", " ", "-"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    sf::Vector2i tilePosition{1, 0};
    sf::Vector2i newPosition{1, -1};
    ASSERT_FALSE(gameBoard.canSlideTile(tilePosition, newPosition)) << "This slide should not work because the new tile is off the board\n";

    tilePosition.x = 3;
    tilePosition.y = 0;
    newPosition.x = 4;
    newPosition.y = 0;
    ASSERT_FALSE(gameBoard.canSlideTile(tilePosition, newPosition)) << "This slide should not work because the new tile is off the board\n";

    tilePosition.x = 0;
    tilePosition.y = 3;
    newPosition.x = -1;
    newPosition.y = 0;
    ASSERT_FALSE(gameBoard.canSlideTile(tilePosition, newPosition)) << "This slide should not work because the new tile is off the board\n";

    tilePosition.x = 0;
    tilePosition.y = 3;
    newPosition.x = 0;
    newPosition.y = 4;
    ASSERT_FALSE(gameBoard.canSlideTile(tilePosition, newPosition)) << "This slide should not work because the new tile is off the board\n";
}

TEST(GameBoard, isSolved) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{" ", "├", "-", "┐",
        " ", "┣", "-", "┘",
        " ", " ", "-", " ",
        "-", " ", " ", "-"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    std::vector<sf::Vector2i> result = gameBoard.isSolved();
    ASSERT_THAT(6, result.size());
}

TEST(GameBoard, isSolved2) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{" ", " ", " ", " ",
        " ", "-", " ", " ",
        "├", "-", "┫", " ",
        " ", "-", " ", " "};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    std::vector<sf::Vector2i> result = gameBoard.isSolved();
    ASSERT_THAT(3, result.size());
}

TEST(GameBoard, isNotSolved) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{" ", "├", " ", "┐",
        " ", "┣", "-", "┘",
        " ", " ", "-", " ",
        "-", " ", " ", "-"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    std::vector<sf::Vector2i> result = gameBoard.isSolved();
    ASSERT_THAT(0, result.size());
}

TEST(GameBoard, isNotSolved2) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{" ", " ", " ", " ",
        " ", " ", " ", " ",
        " ", " ", "-", " ",
        "┫", "-" "-", "┤"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    std::vector<sf::Vector2i> result = gameBoard.isSolved();
    ASSERT_THAT(0, result.size());
}

TEST(GameBoard, isNotSolved3) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{" ", " ", " ", " ",
        " ", " ", " ", " ",
        " ", " ", "-", " ",
        "┤", "-" "-", "┫"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    std::vector<sf::Vector2i> result = gameBoard.isSolved();
    ASSERT_THAT(0, result.size());
}

TEST(GameBoard, isNotSolved4) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"|", "┘", " ", "-",
        "|", "├", "-", "┳",
        "┘", "-", " ", "|",
        " ", "|" "-", "|"};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    std::vector<sf::Vector2i> result = gameBoard.isSolved();
    ASSERT_THAT(0, result.size());
}

/*TEST(GameBoard, possibleMovesNone) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"├", "┫", " ", " ",
        " ", " ", " ", " ",
        " ", " ", " ", " ",
        " ", " ", " ", " "};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    std::vector<SlidingTiles::MoveNode> possibleMoves = gameBoard.possibleMoves();
    ASSERT_THAT(possibleMoves.size(), 0);
}

TEST(GameBoard, possibleMovesOne) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"├", "-", "┫", " ",
        " ", " ", " ", " ",
        " ", " ", " ", " ",
        " ", " ", " ", " "};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    std::vector<SlidingTiles::MoveNode> possibleMoves = gameBoard.possibleMoves();
    ASSERT_THAT(possibleMoves.size(), 1);
    SlidingTiles::MoveNode move = possibleMoves[0];
    sf::Vector2i expectedTile{1, 0};
    ASSERT_EQ(move.startPosition, expectedTile) << "Expect tile [1][0] to be a possible move but returned tile is [" << move.startPosition.x << "][" << move.startPosition.y << "] \n";
}

TEST(GameBoard, possibleMovesTwo) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"├", "┫", " ", " ",
        " ", " ", " ", " ",
        " ", " ", " ", " ",
        "-", " ", " ", " "};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    std::vector<SlidingTiles::MoveNode> possibleMoves = gameBoard.possibleMoves();
    ASSERT_THAT(possibleMoves.size(), 2);
    SlidingTiles::MoveNode move = possibleMoves[0];
}

TEST(GameBoard, possibleMovesFour) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"├", " ", "┫", " ",
        " ", "-", " ", " ",
        " ", " ", " ", " ",
        " ", " ", " ", " "};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    std::vector<SlidingTiles::MoveNode> possibleMoves = gameBoard.possibleMoves();
    ASSERT_THAT(possibleMoves.size(), 4);
    SlidingTiles::MoveNode move = possibleMoves[0];
}

*/