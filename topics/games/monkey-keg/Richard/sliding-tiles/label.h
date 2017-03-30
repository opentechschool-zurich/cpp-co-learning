#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

namespace SlidingTiles {

    /**
     * @brief A base button class
     */
    class Label {
    public:
        /**
         * @brief Constructor for the label
         */
        Label();

        /**
         * @brief set the position of the label
         */
        void setPosition(float x, float y);

        /**
         * Call this method to have the label rendered
         */
        void render();
        
        /**
         * @brief sets the text of the label
         * @param newText the new text
         */
        void setText(std::string newText);


    private:

        /**
         * @brief a font to use for the text
         */
        sf::Font font;

        /**
         * @brief the text to print
         */
        sf::Text text;

    };
}