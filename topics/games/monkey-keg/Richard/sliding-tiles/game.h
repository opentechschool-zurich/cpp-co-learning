#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include "tile.h"

namespace SlidingTiles {
    class Game
    {
    public:
        Game();

        void init();
        void update(const float dt);
        void render();
        void run();

        const int groundWidth = 600;
        const int groundHeight = 16;


    private:
        sf::RenderWindow window;
        sf::Clock deltaClock;

        std::map<Tile::TileType, sf::Texture> texturesMap;

        void slideTile(Tile movingTile, sf::Vector2i movingTilePosition, sf::Vector2i newPosition);

        sf::Text bannerText;
        sf::Vector2i gridZeroZero { 100, 100 };
        static const int boardSize {4};
        Tile tiles [boardSize][boardSize];

        sf::Vector2i mousePositionPressed;
        static const int tileSize {60};
        sf::Vector2i findTile(sf::Vector2i mousePosition);

    };
}
