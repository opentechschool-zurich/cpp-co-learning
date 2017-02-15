#pragma once

#include <iostream>
#include <map>
#include "tileType.h"
#include <SFML/Graphics.hpp>

namespace SlidingTiles {

    /**
     * @brief Singleton class that loads and holds the tile textures
     */
    class TexturesSingleton {
    public:
        /**
         * @brief Deleted to enforce singleton pattern
         */
        TexturesSingleton(TexturesSingleton const&) = delete;

        /**
         * @brief Deleted to enforce singleton pattern
         */
        void operator=(TexturesSingleton const&) = delete;

        /**
         * @brief returns the single instance of the textures singleton creating
         * the object if necessary and loading the textures in the process
         */
        static TexturesSingleton& getInstance() {
            static TexturesSingleton instance; // Guaranteed to be destroyed.
            // Instantiated on first use.
            return instance;
        }

        /**
         * @brief Returns the texture map keyed by TileType
         */
        std::map<TileType, sf::Texture> & getTexturesMap() {
            return texturesMap;
        };

        /**
         * @brief Returns the texture for the supplied TileType
         * Note: the & before the function is super important. If it is missing
         * the texture is lost before the draw actually does the drawing!
         */
        sf::Texture & getTexture(const TileType & tileType) {
            if ( texturesMap.find(tileType) == texturesMap.end() ) {
                std::cout << "Haven't got a texture for tileType: " << tileTypeToString(tileType) << "! Returning an empty Texture instead.\n";
                return texturesMap[TileType::Empty];
            } else {
                //sf::Texture t = texturesMap[tileType];
                //sf::Vector2u textureSize = t.getSize();
                //std::cout << "returning Texture for tileType: " << tileTypeToString(tileType) << " size is: " << textureSize.x << " x " << textureSize.y << "\n";
                return texturesMap[tileType];
            }

        };


    private:
        /**
         * @brief Private constructor for singleton which loads the textures from disk
         * upon initialisation
         */
        TexturesSingleton();

        /**
         * @brief map keyed by TileType with the textures
         */
        std::map<TileType, sf::Texture> texturesMap;
    };

} //namespace
