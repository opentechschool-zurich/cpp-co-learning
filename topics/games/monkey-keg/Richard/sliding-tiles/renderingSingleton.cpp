#include "renderingSingleton.h"

using namespace SlidingTiles;

RenderingSingleton::RenderingSingleton(){
}

const int RenderingSingleton::tileSize;

sf::Vector2i RenderingSingleton::calculateCoordinates( sf::Vector2i xy ) {
    return calculateCoordinates( xy.x, xy.y);
}

sf::Vector2i RenderingSingleton::calculateCoordinates( int x, int y ) {
    sf::Vector2i coordinates = gridZeroZero;
    coordinates.x += x * tileSize;
    coordinates.y += y * tileSize;
    return coordinates;
}


sf::Vector2i RenderingSingleton::findTile(sf::Vector2i mousePosition) {
    sf::Vector2i gridCoordinates = mousePosition - gridZeroZero;
    if ( gridCoordinates.x < 0 || gridCoordinates.y < 0
        || gridCoordinates.x > 4 * tileSize || gridCoordinates.y > 4 * tileSize )
        return sf::Vector2i{-1,-1};
    int xPos = gridCoordinates.x / tileSize;
    int yPos = gridCoordinates.y / tileSize;
    return sf::Vector2i {xPos, yPos};
}
