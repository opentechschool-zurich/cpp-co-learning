#pragma once

#include <SFML/Graphics.hpp>
#include "tileView.h"
#include "direction.h"

namespace SlidingTiles {

    /**
     * @brief A tile on the board
     */
    class Tile {
    public:
        /**
         * @brief the view of the tile
         */
        SlidingTiles::TileView tileView;

        /**
         * @brief sets the tile position to the supplied game board position
         */
        void setTilePosition(const sf::Vector2i & newGameBoardPosition) {
            tileView.setCoordinates(RenderingSingleton::getInstance().calculateCoordinates(newGameBoardPosition));
        }

        /**
         * @brief tells the tile to transition to a new positon in game board coordinates
         */
        bool transition(const sf::Vector2i & newGameBoardPosition);

        /**
         * @brief sets the tile type
         */
        void setTileType(const TileType & newType);

        /**
         * @brief sets the tile type as per the character convetion
         */
        void setTileType(const std::string & c);

        /**
         * @brief Returns the type of the tile
         */
        TileType getTileType() {
            return tileType;
        };

        /**
         * @brief returns if a tile is moveable
         */
        bool isMoveable{false};

        /**
         * @brief returns the Direction that we come out of a tile in if
         * we enter it in the incomingDirection
         * @param incomingDirection the incoming direction
         */
        Direction outputDirection(const Direction & incomingDirection);

        /**
         * @brief settor for the winner flag
         */
        void setWinner(const bool & status);

    private:
        /**
         * @brief The type of the tile
         */
        TileType tileType{TileType::Empty};

        /**
         * @brief sets the isMoveable flag based on the type of tile
         */
        void setMoveable(const TileType & newType);

        /**
         * @brief a bool to tell us if the tile is part of the solution path or not
         */
        bool winner{false};
    };

} // namespace SlidingTiles
