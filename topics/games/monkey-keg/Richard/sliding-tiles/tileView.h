#pragma once

#include <SFML/Graphics.hpp>
#include "texturesSingleton.h"

namespace SlidingTiles {
/**
 * @brief Box rectangle as a dynamic body filled with a texture loaded from a file
 */
class TileView {
    public:
        TileView(){};  // Don't want
        TileView(
            sf::RenderWindow* window,
            int size,
            sf::Vector2i tileCoordinates)
            : window(window),
                size(size),
                tileCoordinates(tileCoordinates)
            {
            };
        void setRenderWindow( sf::RenderWindow* renderWindow) { window = renderWindow; };
        void setSize( int newSize ) { size = newSize; };
        void render();
        void update(const float dt);
        bool transition(sf::Vector2i newTileCoordinates);
        void setColor( sf::Color newColor) { tileColor = newColor; };
        void setTexture(sf::Texture newTexture) { tileTexture = newTexture; };
        void setTexture(TileType newType) { setTexture(TexturesSingleton::getInstance().getTexturesMap()[newType]);};
        bool winner {false};
        bool transitioning {false};

    private:
        sf::RenderWindow *window;
        int size = -1;

        static constexpr double TRANSITION_TIME {0.25}; // seconds
        double timeSpentTransitioning {0};

        /**
        * The coordinates of the tile
        */
        sf::Vector2i tileCoordinates {0, 0};

        /**
        * The coordinates where to move the tile to if transitioning is true
        */
        sf::Vector2i transitionTileCoordiantes {0, 0};

        sf::Color tileColor;

        sf::Texture tileTexture;
};

} // namespace SlidingTiles
