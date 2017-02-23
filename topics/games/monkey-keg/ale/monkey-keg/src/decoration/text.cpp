#include <iostream>
#include "decoration/text.h"

namespace MonkeyKeg {

    Text::Text(b2Vec2 pos, std::string content)
    {
        font.loadFromFile("assets/Franchise-Bold-hinted.ttf");
        text.setFont(font);
		text.setCharacterSize(24); // in pixels, not points!
		text.setFillColor(sf::Color::Black);

        text.setPosition(pos.x , pos.y);
        text.setString(content);
    }

    void Text::render(sf::RenderWindow* window)
    {
        window->draw(text);
    }
}

