#include "tile.h"

namespace SlidingTiles {
    void Tile::render() {
        sf::Vector2i currentPosition { gridZeroZero.x + gameBoardPosition.x * size, gridZeroZero.y + gameBoardPosition.y * size};
        if ( transitioning ) {
            sf::Vector2i nextPosition { gridZeroZero.x + newGameBoardPosition.x * size, gridZeroZero.y + newGameBoardPosition.y * size };
            int deltaX = (nextPosition.x - currentPosition.x) * timeSpentTransitioning / TRANSITION_TIME;
            int deltaY = (nextPosition.y - currentPosition.y) * timeSpentTransitioning / TRANSITION_TIME;
            currentPosition.x += deltaX;
            currentPosition.y += deltaY;
        }

        sf::Sprite sprite;
        sprite.setTexture(tileTexture);
        sprite.setPosition(currentPosition.x, currentPosition.y);
        if (winner)
            sprite.setColor(sf::Color{0,255,0});
        window->draw(sprite);
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
        timeSpentTransitioning = 0;
        this->newGameBoardPosition = newGameBoardPosition;
    }

    int Tile::getX() {
        return gameBoardPosition.x;
    }

    int Tile::getY() {
        return gameBoardPosition.y;
    }

    void Tile::setTileType(TileType newType) {
        tileType = newType;
        if ( newType == Tile::TileType::Empty
            || newType == Tile::TileType::StartBottom
            || newType == Tile::TileType::StartTop
            || newType == Tile::TileType::StartLeft
            || newType == Tile::TileType::StartRight
            || newType == Tile::TileType::EndBottom
            || newType == Tile::TileType::EndTop
            || newType == Tile::TileType::EndLeft
            || newType == Tile::TileType::EndRight)
            isMoveable = false;
        else
            isMoveable = true;
    };

}
