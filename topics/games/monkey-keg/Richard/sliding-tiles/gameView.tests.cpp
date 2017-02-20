#include "gameView.h"
#include <gmock/gmock.h>
#include "game.h"

using namespace SlidingTiles;

TEST(GameView, ObjectCreation) {
    SlidingTiles::GameView gameView {};
}

TEST(GameView, bannerText) {
    SlidingTiles::GameView gameView {};
    sf::Text bannerText = gameView.bannerText;
    std::string text = bannerText.getString();
    std::string expected = "Move the tiles with the mouse";
    ASSERT_EQ(expected, text);
}

TEST(GameView, renderMethod) {
    SlidingTiles::GameView gameView {};
    gameView.render();
}
