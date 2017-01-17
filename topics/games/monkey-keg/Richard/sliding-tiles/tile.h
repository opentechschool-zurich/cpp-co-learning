#pragma once

#include <SFML/Graphics.hpp>

namespace SlidingTiles {
/**
 * @brief Box rectangle as a dynamic body filled with a texture loaded from a file
 */
class Tile {
    public:
        Tile(){};  // Don't want
        Tile(
            sf::RenderWindow* window,
            int size,
            sf::Vector2i gridZeroZero,
            sf::Vector2i gameBoardPosition)
            : window(window),
                size(size),
                gridZeroZero(gridZeroZero),
                gameBoardPosition(gameBoardPosition)
            {
                int red = 255 / 6 * gameBoardPosition.x;
                int green = 255 / 6 * gameBoardPosition.y;
                tileColor = sf::Color(red, green, 250);
            };
        void render();
        void update(const float dt);
        bool transition(sf::Vector2i newGameBoardPosition);
        int getX();
        int getY();
        void setColor( sf::Color newColor) { tileColor = newColor; };
        enum TileType {
            Empty,
            Horizontal,
            Vertical,
            StartTop,
            StartBottom,
            StartLeft,
            StartRight,
            EndTop,
            EndBottom,
            EndRight,
            EndLeft,
            LeftTop,
            LeftBottom,
            TopRight,
            BottomRight
        };
        void setTileType(TileType newType);
        TileType getTileType() { return tileType; };
        void setTexture(sf::Texture newTexture) { tileTexture = newTexture; };
        bool winner {false};
        bool transitioning {false};
        bool isMoveable {false};
        /**
        * The position of the tile on the game board
        */
        sf::Vector2i gameBoardPosition {-1, -1};

    private:
        sf::RenderWindow *window;
        int size = -1;

        /**
        * The position of the tile on the game board after the move
        */
        sf::Vector2i newGameBoardPosition {-1, -1};

        static constexpr double TRANSITION_TIME {0.25}; // seconds
        double timeSpentTransitioning {0};

        /**
        * The coordinats in the window of the top left corner of the board
        */
        sf::Vector2i gridZeroZero {0, 0};

        sf::Color tileColor;

        TileType tileType {TileType::Empty};
        sf::Texture tileTexture;
};

} // namespace SlidingTiles
