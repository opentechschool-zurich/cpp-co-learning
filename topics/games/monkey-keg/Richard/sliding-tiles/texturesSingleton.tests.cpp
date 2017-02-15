#include "texturesSingleton.h"
#include <gmock/gmock.h>

using namespace SlidingTiles;

TEST(TexturesSingleton, ObjectCreation) {
    TexturesSingleton::getInstance();
}

TEST(TexturesSingleton, LoadTextures) {
    std::map<TileType, sf::Texture> textureMap = TexturesSingleton::getInstance().getTexturesMap();
    ASSERT_GT(textureMap.size(), 1);
    EXPECT_EQ(textureMap.size(), 15);
}

TEST(TexturesSingleton, RetrieveTextureFromMap) {
    std::map<TileType, sf::Texture> textureMap = TexturesSingleton::getInstance().getTexturesMap();
    sf::Texture emptyTexture{};
    sf::Vector2u textureSize = emptyTexture.getSize();
    ASSERT_EQ(textureSize.x, 0);
    ASSERT_EQ(textureSize.y, 0);
    emptyTexture = textureMap[TileType::Empty];
    textureSize = emptyTexture.getSize();
    ASSERT_GT(textureSize.x, 0);
    ASSERT_GT(textureSize.y, 0);
}

TEST(TexturesSingleton, TestAllTextureSizes) {
    std::map<TileType, sf::Texture> textureMap = TexturesSingleton::getInstance().getTexturesMap();

    for ( const auto &myPair : textureMap ) {
        sf::Texture emptyTexture{};
        sf::Vector2u textureSize = emptyTexture.getSize();
        ASSERT_EQ(textureSize.x, 0);
        ASSERT_EQ(textureSize.y, 0);
        emptyTexture = TexturesSingleton::getInstance().getTexture( myPair.first );
        textureSize = emptyTexture.getSize();
        ASSERT_GT(textureSize.x, 0) << "The width of the texture for TileType::"<< tileTypeToString(myPair.first) << " is too small";
        ASSERT_GT(textureSize.y, 0) << "The height of the texture for TileType::"<< tileTypeToString(myPair.first) << " is too small";
    }
}
