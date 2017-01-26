#include "tileView.h"
#include <gmock/gmock.h>
#include <string>

using namespace ::testing;

TEST(TileView, ObjectCreation)
{
    SlidingTiles::TileView tileView;
}

TEST(TileView, transition)
{
    SlidingTiles::TileView tileView;
    bool result = tileView.transition( sf::Vector2i {0,0} );
    ASSERT_TRUE ( result ) << "First transition should succeed\n";
}
