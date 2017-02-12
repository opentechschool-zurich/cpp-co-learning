#include "texturesSingleton.h"

using namespace SlidingTiles;

TexturesSingleton::TexturesSingleton() {
    sf::Texture texture;

    texture.loadFromFile("assets/horizontal.png");
    texturesMap[TileType::Horizontal] = texture;
    texture.loadFromFile("assets/vertical.png");
    texturesMap[TileType::Vertical] = texture;

    texture.loadFromFile("assets/startbottom.png");
    texturesMap[TileType::StartBottom] = texture;
    texture.loadFromFile("assets/starttop.png");
    texturesMap[TileType::StartTop] = texture;
    texture.loadFromFile("assets/startleft.png");
    texturesMap[TileType::StartLeft] = texture;
    texture.loadFromFile("assets/startright.png");
    texturesMap[TileType::StartRight] = texture;

    texture.loadFromFile("assets/endtop.png");
    texturesMap[TileType::EndTop] = texture;
    texture.loadFromFile("assets/endbottom.png");
    texturesMap[TileType::EndBottom] = texture;
    texture.loadFromFile("assets/endleft.png");
    texturesMap[TileType::EndLeft] = texture;
    texture.loadFromFile("assets/endright.png");
    texturesMap[TileType::EndRight] = texture;

    texture.loadFromFile("assets/lefttop.png");
    texturesMap[TileType::LeftTop] = texture;
    texture.loadFromFile("assets/leftbottom.png");
    texturesMap[TileType::LeftBottom] = texture;
    texture.loadFromFile("assets/topright.png");
    texturesMap[TileType::TopRight] = texture;
    texture.loadFromFile("assets/bottomright.png");
    texturesMap[TileType::BottomRight] = texture;
    texture.loadFromFile("assets/empty.png");
    texturesMap[TileType::Empty] = texture;
};
