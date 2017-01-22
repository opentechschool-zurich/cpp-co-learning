#pragma once

#include <SFML/Graphics.hpp>
#include "texturesSingleton.h"
#include "renderingSingleton.h"
#include "gameBoardSingleton.h"

namespace SlidingTiles {
/**
 * @brief The view class for the tile that knows how to render itself
 */
class GameView {
    public:
        GameView(){};  // Don't want
        void init();
        void render();
        sf::Font font;
        sf::Text bannerText;

    private:


};

} // namespace SlidingTiles
