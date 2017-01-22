#include "gameView.h"
#include <gmock/gmock.h>
#include <string>

using namespace ::testing;

TEST(GameView, ObjectCreation)
{
    SlidingTiles::GameView gameView;
}

TEST(GameView, initMethod)
{
    SlidingTiles::GameView gameView;
    gameView.init();
}

TEST(GameView, bannerText)
{
    SlidingTiles::GameView gameView;
    gameView.init();
    sf::Text bannerText = gameView.bannerText;
    std::string text = bannerText.getString();
    std::string expected = "Move the tiles with the mouse";
    ASSERT_EQ(expected, text);
}
