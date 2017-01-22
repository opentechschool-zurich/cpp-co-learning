#include "renderingSingleton.h"
#include <gmock/gmock.h>

using namespace ::testing;

TEST(RenderingSingleton, ObjectCreation)
{
    RenderingSingleton::getInstance();
}

TEST(RenderingSingleton, GridZeroZeroCoordinates)
{
    ASSERT_GT(RenderingSingleton::getInstance().gridZeroZero.x, 10);
    ASSERT_GT(RenderingSingleton::getInstance().gridZeroZero.y, 10);
}


TEST(RenderingSingleton, TileSize)
{
    ASSERT_GT(RenderingSingleton::tileSize, 40);
}

TEST(RenderingSingleton, Coordinates00)
{
    sf::Vector2i gridZeroZero = RenderingSingleton::getInstance().gridZeroZero;
    int tileSize = RenderingSingleton::tileSize;
    sf::Vector2i pixelCoordinates = RenderingSingleton::getInstance().calculateCoordinates(sf::Vector2i{0,0});
    ASSERT_EQ(gridZeroZero.x, pixelCoordinates.x);
    ASSERT_EQ(gridZeroZero.y, pixelCoordinates.y);
}

TEST(RenderingSingleton, Coordinates23)
{
    sf::Vector2i gridZeroZero = RenderingSingleton::getInstance().gridZeroZero;
    int tileSize = RenderingSingleton::tileSize;
    int deltaX = 2 * RenderingSingleton::tileSize;
    int deltaY = 3 * RenderingSingleton::tileSize;
    sf::Vector2i pixelCoordinates =
        RenderingSingleton::getInstance().calculateCoordinates(sf::Vector2i{2,3});
    ASSERT_EQ(gridZeroZero.x + deltaX, pixelCoordinates.x);
    ASSERT_EQ(gridZeroZero.y + deltaY, pixelCoordinates.y);
}

TEST(RenderingSingleton, FindTile02)
{
    sf::Vector2i tile = RenderingSingleton::getInstance().findTile(sf::Vector2i{142,251});
    ASSERT_EQ(tile.x, 0);
    ASSERT_EQ(tile.y, 2);
}

TEST(RenderingSingleton, FindTileOutSideGrid1)
{
    sf::Vector2i tile = RenderingSingleton::getInstance().findTile(sf::Vector2i{50,50});
    ASSERT_EQ(tile.x, -1);
    ASSERT_EQ(tile.y, -1);
}

TEST(RenderingSingleton, FindTileOutSideGrid2)
{
    sf::Vector2i tile = RenderingSingleton::getInstance().findTile(sf::Vector2i{50,150});
    ASSERT_EQ(tile.x, -1);
    ASSERT_EQ(tile.y, -1);
}

TEST(RenderingSingleton, FindTileOutSideGrid3)
{
    sf::Vector2i tile = RenderingSingleton::getInstance().findTile(sf::Vector2i{50,110 + 4 * RenderingSingleton::tileSize});
    ASSERT_EQ(tile.x, -1);
    ASSERT_EQ(tile.y, -1);
}

TEST(RenderingSingleton, FindTileOutSideGrid5)
{
    sf::Vector2i tile = RenderingSingleton::getInstance().findTile(sf::Vector2i{150,50});
    ASSERT_EQ(tile.x, -1);
    ASSERT_EQ(tile.y, -1);
}

TEST(RenderingSingleton, FindTileOutSideGrid6)
{
    sf::Vector2i tile = RenderingSingleton::getInstance().findTile(sf::Vector2i{110 + 4 * RenderingSingleton::tileSize, 150});
    ASSERT_EQ(tile.x, -1);
    ASSERT_EQ(tile.y, -1);
}
