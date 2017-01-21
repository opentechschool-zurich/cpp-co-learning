#include "tileView.h"

namespace SlidingTiles {
    void TileView::render() {
        //sf::Vector2i currentPosition { gridZeroZero.x + gameBoardPosition.x * size, gridZeroZero.y + gameBoardPosition.y * size};
        sf::Vector2i renderPosition = tileCoordinates;
        if ( transitioning ) {
            //sf::Vector2i nextPosition { gridZeroZero.x + newGameBoardPosition.x * size, gridZeroZero.y + newGameBoardPosition.y * size };
            int deltaX = (transitionTileCoordiantes.x - tileCoordinates.x) * timeSpentTransitioning / TRANSITION_TIME;
            int deltaY = (transitionTileCoordiantes.y - tileCoordinates.y) * timeSpentTransitioning / TRANSITION_TIME;
            renderPosition.x += deltaX;
            renderPosition.y += deltaY;
        }

        sf::Sprite sprite;
        sprite.setTexture(tileTexture);
        sprite.setPosition(renderPosition.x, renderPosition.y);
        if (winner)
            sprite.setColor(sf::Color{0,255,0});
        window->draw(sprite);
    }

    void TileView::update(const float dt) {
        if (transitioning) {
            timeSpentTransitioning += dt;
            if ( timeSpentTransitioning > TRANSITION_TIME ) {
                transitioning = false;
                //gameBoardPosition = this->newGameBoardPosition;
            }
        }
    }

    bool TileView::transition(sf::Vector2i newTileCoordinates) {
        if (transitioning) return false;
        transitionTileCoordiantes = newTileCoordinates;
        transitioning = true;
        timeSpentTransitioning = 0;
    }

}
