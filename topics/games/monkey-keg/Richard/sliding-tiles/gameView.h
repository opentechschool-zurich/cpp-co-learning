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
        /**
        * @brief constructor for the view of the game
        */
        GameView(){};

        /**
        * @brief initialised the game
        */
        void init();

        /**
        * @brief knows how to render the game
        */
        void render();

        /**
        * @brief a font to use for the text
        */
        sf::Font font;

        /**
        * @brief the text to print
        */
        sf::Text bannerText;
};

} // namespace SlidingTiles
