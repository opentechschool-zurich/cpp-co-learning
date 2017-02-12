#pragma once

#include <SFML/Graphics.hpp>
#include "texturesSingleton.h"
#include "renderingSingleton.h"

namespace SlidingTiles {

    /**
     * @brief The view class for the tile that knows how to render itself
     */
    class TileView {
    public:

        TileView() {
        };

        /**
         * @brief Constructs a new TileView with the appropriate screen coordinates
         */
        TileView(sf::Vector2i tileCoordinates)
        : tileCoordinates(tileCoordinates) {
        };

        /**
         * @brief knows how to render the tile
         */
        void render();

        /**
         * @brief need to be called periodically with a delta time to
         * update the position etc.
         * @param dt The passing time since last call in seconds
         */
        void update(const float dt);

        /**
         * @brief starts a transition to the supplied new pixel coordinates
         * @return true if transition kicked off, false if not
         */
        bool transition(const sf::Vector2i & newTileCoordinates);

        /**
         * @brief settor for a texture of the tile
         * @param newType the new type of the tile. Will figure out the correct texture from the TexturesSingleton
         */
        void setTexture(const TileType & newType) {
            setTexture(TexturesSingleton::getInstance().getTexturesMap()[newType]);
        };

        /**
         * @brief a bool to tell us if the tile is currently undergoing a transition
         */
        bool transitioning{false};

        /**
         * @brief settor for the tile coordinates in screen coordinates
         */
        void setCoordinates(const sf::Vector2i & newCoordinates) {
            tileCoordinates = newCoordinates;
        };

        /**
         * @brief settor for the winner flag
         */
        void setWinner(const bool & status) {
            winner = status;
        };

    private:
        /**
         * @brief A constant that gives the amount of time in seconds that the transition will last
         */
        static constexpr double TRANSITION_TIME{0.15}; // seconds

        /**
         * @brief a tracker to figure out how much of TRANSITION_TIME has passed
         */
        double timeSpentTransitioning{0};

        /**
         * The coordinates of the tile
         */
        sf::Vector2i tileCoordinates{0, 0};

        /**
         * The coordinates where to move the tile to if transitioning is true
         */
        sf::Vector2i transitionTileCoordiantes{0, 0};

        /**
         * @brief The color with which to tint the textures
         */
        sf::Color tileColor;

        /**
         * @brief The texture for the tile
         */
        sf::Texture tileTexture;

        /**
         * @brief settor for the Texture
         */
        void setTexture(const sf::Texture & newTexture) {
            tileTexture = newTexture;
        };

        /**
         * @brief a bool to tell us if the tile is part of the solution path or not
         */
        bool winner{false};
    };


} // namespace SlidingTiles
