#pragma once

#include <iostream>
#include <map>
#include "tileType.h"
#include <SFML/Graphics.hpp>

namespace SlidingTiles {

/**
* @brief Singleton class that loads and holds the tile textures
*/
class TexturesSingleton
{
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
        static TexturesSingleton& getInstance()
        {
            static TexturesSingleton  instance; // Guaranteed to be destroyed.
                                               // Instantiated on first use.
            return instance;
        }

        /**
        * @brief Returns the texture map keyed by TileType
        */
        std::map<TileType, sf::Texture> getTexturesMap() {return texturesMap;};

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
