#include "tile.h"
#include <gmock/gmock.h>
#include "direction.h"
#include <iostream>

using namespace ::testing;

TEST(Tile, ObjectCreation)
{
    SlidingTiles::Tile tile;
}

TEST(Tile, getTileDirectionStartRight)
{
    SlidingTiles::Tile tile;
    tile.setTileType(TileType::StartRight);
    Direction newDirection = tile.getTileDirection(Direction::Unknown);
    ASSERT_THAT(Direction::GoRight, newDirection);

    newDirection = tile.getTileDirection(Direction::GoDown);
    ASSERT_THAT(Direction::GoRight, newDirection);

    newDirection = tile.getTileDirection(Direction::GoUp);
    ASSERT_THAT(Direction::GoRight, newDirection);

    newDirection = tile.getTileDirection(Direction::GoRight);
    ASSERT_THAT(Direction::GoRight, newDirection);

    newDirection = tile.getTileDirection(Direction::GoLeft);
    ASSERT_THAT(Direction::GoRight, newDirection);
}

TEST(Tile, getTileDirectionStartLeft)
{
    SlidingTiles::Tile tile;
    tile.setTileType(TileType::StartLeft);
    Direction newDirection = tile.getTileDirection(Direction::Unknown);
    ASSERT_THAT(Direction::GoLeft, newDirection);

    newDirection = tile.getTileDirection(Direction::GoDown);
    ASSERT_THAT(Direction::GoLeft, newDirection);

    newDirection = tile.getTileDirection(Direction::GoUp);
    ASSERT_THAT(Direction::GoLeft, newDirection);

    newDirection = tile.getTileDirection(Direction::GoRight);
    ASSERT_THAT(Direction::GoLeft, newDirection);

    newDirection = tile.getTileDirection(Direction::GoLeft);
    ASSERT_THAT(Direction::GoLeft, newDirection);
}

TEST(Tile, getTileDirectionStartTop)
{
    SlidingTiles::Tile tile;
    tile.setTileType(TileType::StartTop);
    Direction newDirection = tile.getTileDirection(Direction::Unknown);
    ASSERT_THAT(Direction::GoUp, newDirection);

    newDirection = tile.getTileDirection(Direction::GoDown);
    ASSERT_THAT(Direction::GoUp, newDirection);

    newDirection = tile.getTileDirection(Direction::GoUp);
    ASSERT_THAT(Direction::GoUp, newDirection);

    newDirection = tile.getTileDirection(Direction::GoRight);
    ASSERT_THAT(Direction::GoUp, newDirection);

    newDirection = tile.getTileDirection(Direction::GoLeft);
    ASSERT_THAT(Direction::GoUp, newDirection);
}

TEST(Tile, getTileDirectionStartBottom)
{
    SlidingTiles::Tile tile;
    tile.setTileType(TileType::StartBottom);
    Direction newDirection = tile.getTileDirection(Direction::Unknown);
    ASSERT_THAT(Direction::GoDown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoDown);
    ASSERT_THAT(Direction::GoDown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoUp);
    ASSERT_THAT(Direction::GoDown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoRight);
    ASSERT_THAT(Direction::GoDown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoLeft);
    ASSERT_THAT(Direction::GoDown, newDirection);
}

TEST(Tile, getTileDirectionEndRight)
{
    SlidingTiles::Tile tile;
    tile.setTileType(TileType::EndRight);
    Direction newDirection = tile.getTileDirection(Direction::Unknown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoDown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoUp);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoRight);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoLeft);
    ASSERT_THAT(Direction::Unknown, newDirection);
}

TEST(Tile, getTileDirectionEndLeft)
{
    SlidingTiles::Tile tile;
    tile.setTileType(TileType::EndLeft);
    Direction newDirection = tile.getTileDirection(Direction::Unknown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoDown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoUp);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoRight);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoLeft);
    ASSERT_THAT(Direction::Unknown, newDirection);
}

TEST(Tile, getTileDirectionEndTop)
{
    SlidingTiles::Tile tile;
    tile.setTileType(TileType::EndTop);
    Direction newDirection = tile.getTileDirection(Direction::Unknown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoDown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoUp);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoRight);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoLeft);
    ASSERT_THAT(Direction::Unknown, newDirection);
}

TEST(Tile, getTileDirectionEndBottom)
{
    SlidingTiles::Tile tile;
    tile.setTileType(TileType::EndBottom);
    Direction newDirection = tile.getTileDirection(Direction::Unknown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoDown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoUp);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoRight);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoLeft);
    ASSERT_THAT(Direction::Unknown, newDirection);
}

TEST(Tile, getTileDirectionVertical)
{
    SlidingTiles::Tile tile;
    tile.setTileType(TileType::Vertical);
    Direction newDirection = tile.getTileDirection(Direction::Unknown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoDown);
    ASSERT_THAT(Direction::GoDown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoUp);
    ASSERT_THAT(Direction::GoUp, newDirection);

    newDirection = tile.getTileDirection(Direction::GoRight);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoLeft);
    ASSERT_THAT(Direction::Unknown, newDirection);
}

TEST(Tile, getTileDirectionHorizontal)
{
    SlidingTiles::Tile tile;
    tile.setTileType(TileType::Horizontal);
    Direction newDirection = tile.getTileDirection(Direction::Unknown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoDown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoUp);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoRight);
    ASSERT_THAT(Direction::GoRight, newDirection);

    newDirection = tile.getTileDirection(Direction::GoLeft);
    ASSERT_THAT(Direction::GoLeft, newDirection);
}


TEST(Tile, getTileDirectionBottomRight)
{
    SlidingTiles::Tile tile;
    tile.setTileType(TileType::BottomRight);
    Direction newDirection = tile.getTileDirection(Direction::Unknown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoDown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoUp);
    ASSERT_THAT(Direction::GoRight, newDirection);

    newDirection = tile.getTileDirection(Direction::GoRight);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoLeft);
    ASSERT_THAT(Direction::GoDown, newDirection);
}

TEST(Tile, getTileDirectionLeftTop)
{
    SlidingTiles::Tile tile;
    tile.setTileType(TileType::LeftTop);
    Direction newDirection = tile.getTileDirection(Direction::Unknown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoDown);
    ASSERT_THAT(Direction::GoLeft, newDirection);

    newDirection = tile.getTileDirection(Direction::GoUp);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoRight);
    ASSERT_THAT(Direction::GoUp, newDirection);

    newDirection = tile.getTileDirection(Direction::GoLeft);
    ASSERT_THAT(Direction::Unknown, newDirection);
}

TEST(Tile, getTileDirectionLeftBottom)
{
    SlidingTiles::Tile tile;
    tile.setTileType(TileType::LeftBottom);
    Direction newDirection = tile.getTileDirection(Direction::Unknown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoDown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoUp);
    ASSERT_THAT(Direction::GoLeft, newDirection);

    newDirection = tile.getTileDirection(Direction::GoRight);
    ASSERT_THAT(Direction::GoDown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoLeft);
    ASSERT_THAT(Direction::Unknown, newDirection);
}

TEST(Tile, TopRight)
{
    SlidingTiles::Tile tile;
    tile.setTileType(TileType::TopRight);
    Direction newDirection = tile.getTileDirection(Direction::Unknown);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoDown);
    ASSERT_THAT(Direction::GoRight, newDirection);

    newDirection = tile.getTileDirection(Direction::GoUp);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoRight);
    ASSERT_THAT(Direction::Unknown, newDirection);

    newDirection = tile.getTileDirection(Direction::GoLeft);
    ASSERT_THAT(Direction::GoUp, newDirection);
}
