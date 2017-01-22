#include "renderingSingleton.h"
#include <iostream>

RenderingSingleton::RenderingSingleton(){
}

const int RenderingSingleton::tileSize;

sf::Vector2i RenderingSingleton:: calculateCoordinates( sf::Vector2i xy ) {
    sf::Vector2i coordinates = gridZeroZero;
    coordinates.x += xy.x * tileSize;
    coordinates.y += xy.y * tileSize;
    return coordinates;
}

sf::Vector2i RenderingSingleton::RenderingSingleton::findTile(sf::Vector2i mousePosition) {
    sf::Vector2i gridCoordinates = mousePosition - gridZeroZero;
    if ( gridCoordinates.x < 0 || gridCoordinates.y < 0
        || gridCoordinates.x > 4 * tileSize || gridCoordinates.y > 4 * tileSize )
        return sf::Vector2i{-1,-1};
    int xPos = gridCoordinates.x / tileSize;
    int yPos = gridCoordinates.y / tileSize;
    return sf::Vector2i {xPos, yPos};
}
