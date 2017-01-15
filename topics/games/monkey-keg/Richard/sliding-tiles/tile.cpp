#include "tile.h"

namespace SlidingTiles {
    void Tile::render() {
        if (tileType == TileType::Empty)
            return;

        sf::Vector2i currentPosition { gridZeroZero.x + gameBoardPosition.x * size, gridZeroZero.y + gameBoardPosition.y * size};
        if ( transitioning ) {
            sf::Vector2i nextPosition { gridZeroZero.x + newGameBoardPosition.x * size, gridZeroZero.y + newGameBoardPosition.y * size };
            int deltaX = (nextPosition.x - currentPosition.x) * timeSpentTransitioning / TRANSITION_TIME;
            int deltaY = (nextPosition.y - currentPosition.y) * timeSpentTransitioning / TRANSITION_TIME;
            currentPosition.x += deltaX;
            currentPosition.y += deltaY;
        }

        if (tileType == TileType::Colored) {
            sf::RectangleShape rectangle(sf::Vector2f(size, size));
            rectangle.setFillColor(tileColor);
            rectangle.setPosition(currentPosition.x, currentPosition.y);
            window->draw(rectangle);
        } else {
            sf::Sprite sprite;
            sprite.setTexture(tileTexture);
            sprite.setPosition(currentPosition.x, currentPosition.y);
            window->draw(sprite);
        }
    }

    void Tile::update(const float dt) {
        if (transitioning) {
            timeSpentTransitioning += dt;
            if ( timeSpentTransitioning > TRANSITION_TIME ) {
                transitioning = false;
                gameBoardPosition = this->newGameBoardPosition;
            }
        }
    }

    bool Tile::transition(sf::Vector2i newGameBoardPosition) {
        if (transitioning) return false;
        transitioning = true;
        this->newGameBoardPosition = newGameBoardPosition;
    }

    int Tile::getX() {
        return gameBoardPosition.x;
    }

    int Tile::getY() {
        return gameBoardPosition.y;
    }

}
