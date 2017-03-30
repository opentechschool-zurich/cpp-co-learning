#include "label.h"
#include "renderingSingleton.h"


using namespace SlidingTiles;

Label::Label() {
    if (!font.loadFromFile("assets/Raleway-Regular.ttf"))
        std::cout << "Can't load font ./assets/Raleway-Regular.ttf" << std::endl;

    text.setFont(font);
    text.setCharacterSize(16);
    //text.setStyle(sf::Text::Bold);
    text.setColor(sf::Color::Black);
}

void Label::setPosition(float x, float y) {
    text.setPosition(x, y);
}

void Label::setText(std::string newText) {
    text.setString(newText);
}

void Label::render() {
    RenderingSingleton::getInstance().getRenderWindow()->draw(text);
}