#include "tileView.h"

namespace SlidingTiles {
    void TileView::render() {
        sf::Vector2i renderPosition = tileCoordinates;
        if ( transitioning ) {
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
        RenderingSingleton::getInstance().getRenderWindow()->draw(sprite);
    }

    void TileView::update(const float dt) {
        if (transitioning) {
            timeSpentTransitioning += dt;
            if ( timeSpentTransitioning > TRANSITION_TIME ) {
                transitioning = false;
                tileCoordinates = transitionTileCoordiantes;
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
