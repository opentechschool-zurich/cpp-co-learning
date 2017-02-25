#pragma once
#include <SFML/Graphics.hpp>
#include "gameBoard.h"

namespace SlidingTiles {

    /**
     * @brief The view class for the tile that knows how to render itself
     */
    class GameView {
    public:
        /**
         * @brief constructor for the view of the game
         */
        GameView();

        /**
         * @brief knows how to render the game
         */
        void render();

        /**
         * @brief a font to use for the text
         */
        sf::Font font;

        /**
         * @brief the text to print
         */
        sf::Text bannerText;
        
        /**
         * @brief pointer to the gameBoard
         */
        SlidingTiles::GameBoard* gameBoard;
        
        /**
         * @brief set the Game Board
         */
        void setGameBoard(SlidingTiles::GameBoard * gB) {
            gameBoard = gB;
        }
        
    };

} // namespace SlidingTiles
