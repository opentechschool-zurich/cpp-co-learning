#include "tile.h"
#include <gmock/gmock.h>
#include "gameBoardSingleton.h"

using namespace ::testing;

TEST(Tile, ObjectCreation)
{
    SlidingTiles::Tile tile;
}

TEST(Tile, outputDirectionStartRight) {
    SlidingTiles::Tile tile;
    tile.setTileType(TileType::StartRight);
    Direction newDirection = tile.outputDirection(Direction::Unknown);
    ASSERT_THAT(Direction::GoRight, newDirection);

    newDirection = tile.outputDirection(Direction::GoDown);
    ASSERT_THAT(Direction::GoRight, newDirection);

    newDirection = tile.outputDirection(Direction::GoUp);
    ASSERT_THAT(Direction::GoRight, newDirection);

    newDirection = tile.outputDirection(Direction::GoRight);
    ASSERT_THAT(Direction::GoRight, newDirection);

    newDirection = tile.outputDirection(Direction::GoLeft);
    ASSERT_THAT(Direction::GoRight, newDirection);
}

TEST(Tile, outputDirectionStartLeft) {
    SlidingTiles::Tile tile;
    tile.setTileType(TileType::StartLeft);
    Direction newDirection = tile.outputDirection(Direction::Unknown);
    ASSERT_THAT(Direction::GoLeft, newDirection);

    newDirection = tile.outputDirection(Direction::GoDown);
    ASSERT_THAT(Direction::GoLeft, newDirection);

    newDirection = tile.outputDirection(Direction::GoUp);
    ASSERT_THAT(Direction::GoLeft, newDirection);

    newDirection = tile.outputDirection(Direction::GoRight);
    ASSERT_THAT(Direction::GoLeft, newDirection);

    newDirection = tile.outputDirection(Direction::GoLeft);
    ASSERT_THAT(Direction::GoLeft, newDirection);
}

TEST(Tile, outputDirectionStartTop) {
    SlidingTiles::Tile tile;
    tile.setTileType(TileType::StartTop);
    Direction newDirection = tile.outputDirection(Direction::Unknown);
    ASSERT_THAT(Direction::GoUp, newDirection);

    newDirection = tile.outputDirection(Direction::GoDown);
    ASSERT_THAT(Direction::GoUp, newDirection);

    newDirection = tile.outputDirection(Direction::GoUp);
    ASSERT_THAT(Direction::GoUp, newDirection);

    newDirection = tile.outputDirection(Direction::GoRight);
    ASSERT_THAT(Direction::GoUp, newDirection);

    newDirection = tile.outputDirection(Direction::GoLeft);
    ASSERT_THAT(Direction::GoUp, newDirection);
}

TEST(Tile, outputDirectionStartBottom) {
    SlidingTiles::Tile tile;
    tile.setTileType(TileType::StartBottom);
    Direction newDirection = tile.outputDirection(Direction::Unknown);
    ASSERT_THAT(Direction::GoDown, newDirection);

    newDirection = tile.outputDirection(Direction::GoDown);
    ASSERT_THAT(Direction::GoDown, newDirection);

    newDirection = tile.outputDirection(Direction::GoUp);
    ASSERT_THAT(Direction::GoDown, newDirection);

    newDirection = tile.outputDirection(Direction::GoRight);
    ASSERT_THAT(Direction::GoDown, newDirection);

    newDirection = tile.outputDirection(Direction::GoLeft);
    ASSERT_THAT(Direction::GoDown, newDirection);
}

TEST(Tile, outputDirectionEndRight) {
    SlidingTiles::Tile tile;
    tile.setTileType(TileType::EndRight);
    Direction newDirection = tile.outputDirection(Direction::Unknown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(Direction::GoDown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(Direction::GoUp);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(Direction::GoRight);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(Direction::GoLeft);
    ASSERT_THAT(Direction::Unknown, newDirection);
}

TEST(Tile, outputDirectionEndLeft) {
    SlidingTiles::Tile tile;
    tile.setTileType(TileType::EndLeft);
    Direction newDirection = tile.outputDirection(Direction::Unknown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(Direction::GoDown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(Direction::GoUp);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(Direction::GoRight);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(Direction::GoLeft);
    ASSERT_THAT(Direction::Unknown, newDirection);
}

TEST(Tile, outputDirectionEndTop) {
    SlidingTiles::Tile tile;
    tile.setTileType(TileType::EndTop);
    Direction newDirection = tile.outputDirection(Direction::Unknown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(Direction::GoDown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(Direction::GoUp);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(Direction::GoRight);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(Direction::GoLeft);
    ASSERT_THAT(Direction::Unknown, newDirection);
}

TEST(Tile, outputDirectionEndBottom) {
    SlidingTiles::Tile tile;
    tile.setTileType(TileType::EndBottom);
    Direction newDirection = tile.outputDirection(Direction::Unknown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(Direction::GoDown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(Direction::GoUp);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(Direction::GoRight);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(Direction::GoLeft);
    ASSERT_THAT(Direction::Unknown, newDirection);
}

TEST(Tile, outputDirectionVertical) {
    SlidingTiles::Tile tile;
    tile.setTileType(TileType::Vertical);
    Direction newDirection = tile.outputDirection(Direction::Unknown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(Direction::GoDown);
    ASSERT_THAT(Direction::GoDown, newDirection);

    newDirection = tile.outputDirection(Direction::GoUp);
    ASSERT_THAT(Direction::GoUp, newDirection);

    newDirection = tile.outputDirection(Direction::GoRight);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(Direction::GoLeft);
    ASSERT_THAT(Direction::Unknown, newDirection);
}

TEST(Tile, outputDirectionHorizontal) {
    SlidingTiles::Tile tile;
    tile.setTileType(TileType::Horizontal);
    Direction newDirection = tile.outputDirection(Direction::Unknown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(Direction::GoDown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(Direction::GoUp);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(Direction::GoRight);
    ASSERT_THAT(Direction::GoRight, newDirection);

    newDirection = tile.outputDirection(Direction::GoLeft);
    ASSERT_THAT(Direction::GoLeft, newDirection);
}


TEST(Tile, outputDirectionBottomRight) {
    SlidingTiles::Tile tile;
    tile.setTileType(TileType::BottomRight);
    Direction newDirection = tile.outputDirection(Direction::Unknown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(Direction::GoDown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(Direction::GoUp);
    ASSERT_THAT(Direction::GoRight, newDirection);

    newDirection = tile.outputDirection(Direction::GoRight);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(Direction::GoLeft);
    ASSERT_THAT(Direction::GoDown, newDirection);
}

TEST(Tile, outputDirectionLeftTop) {
    SlidingTiles::Tile tile;
    tile.setTileType(TileType::LeftTop);
    Direction newDirection = tile.outputDirection(Direction::Unknown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(Direction::GoDown);
    ASSERT_THAT(Direction::GoLeft, newDirection);

    newDirection = tile.outputDirection(Direction::GoUp);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(Direction::GoRight);
    ASSERT_THAT(Direction::GoUp, newDirection);

    newDirection = tile.outputDirection(Direction::GoLeft);
    ASSERT_THAT(Direction::Unknown, newDirection);
}

TEST(Tile, outputDirectionLeftBottom) {
    SlidingTiles::Tile tile;
    tile.setTileType(TileType::LeftBottom);
    Direction newDirection = tile.outputDirection(Direction::Unknown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(Direction::GoDown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(Direction::GoUp);
    ASSERT_THAT(Direction::GoLeft, newDirection);

    newDirection = tile.outputDirection(Direction::GoRight);
    ASSERT_THAT(Direction::GoDown, newDirection);

    newDirection = tile.outputDirection(Direction::GoLeft);
    ASSERT_THAT(Direction::Unknown, newDirection);
}

TEST(Tile, TopRight) {
    SlidingTiles::Tile tile;
    tile.setTileType(TileType::TopRight);
    Direction newDirection = tile.outputDirection(Direction::Unknown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(Direction::GoDown);
    ASSERT_THAT(Direction::GoRight, newDirection);

    newDirection = tile.outputDirection(Direction::GoUp);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(Direction::GoRight);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.outputDirection(Direction::GoLeft);
    ASSERT_THAT(Direction::GoUp, newDirection);
}

TEST(Tile, setTileTypeChar) {
    SlidingTiles::Tile tile;

    tile.setTileType( "-");
    ASSERT_EQ(TileType::Horizontal, tile.getTileType());

    tile.setTileType( "|");
    ASSERT_EQ(TileType::Vertical, tile.getTileType());


    tile.setTileType( "┐");
    ASSERT_EQ(TileType::LeftBottom, tile.getTileType());

    tile.setTileType( "└");
    ASSERT_EQ(TileType::TopRight, tile.getTileType());

    tile.setTileType( "┘");
    ASSERT_EQ(TileType::LeftTop, tile.getTileType());

    tile.setTileType( "┌");
    ASSERT_EQ(TileType::BottomRight, tile.getTileType());


    tile.setTileType( "├");
    ASSERT_EQ(TileType::StartRight, tile.getTileType());

    tile.setTileType( "┤");
    ASSERT_EQ(TileType::StartLeft, tile.getTileType());

    tile.setTileType( "┬");
    ASSERT_EQ(TileType::StartBottom, tile.getTileType());

    tile.setTileType( "┴");
    ASSERT_EQ(TileType::StartTop, tile.getTileType());


    tile.setTileType( "┣");
    ASSERT_EQ(TileType::EndRight, tile.getTileType());

    tile.setTileType( "┫");
    ASSERT_EQ(TileType::EndLeft, tile.getTileType());

    tile.setTileType( "┳");
    ASSERT_EQ(TileType::EndBottom, tile.getTileType());

    tile.setTileType( "┻");
    ASSERT_EQ(TileType::EndTop, tile.getTileType());


    tile.setTileType( " ");
    ASSERT_EQ(TileType::Empty, tile.getTileType());
}

TEST(Tile, transition) {
    std::string game [GameBoardSingleton::boardSize][GameBoardSingleton::boardSize]
        {"├","-","-","┐",
         "┣","┐"," ","|",
         "┌","┘"," ","|",
         "└","-","-","┘"};
    GameBoardSingleton::getInstance().loadGame(game);
    SlidingTiles::Tile t = GameBoardSingleton::getInstance().tiles[0][0];
    sf::Vector2i topLeftPostion {0,0};
    bool result = t.transition( topLeftPostion );
    ASSERT_TRUE(result) << "Transitioning should be possible first time\n";
    result = t.transition( topLeftPostion );
    ASSERT_FALSE(result) << "Transitioning should not be possible when transitioning in progress\n";
}
