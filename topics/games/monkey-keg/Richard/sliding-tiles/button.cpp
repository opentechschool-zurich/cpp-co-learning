#include "button.h"
#include "renderingSingleton.h"


using namespace SlidingTiles;

Button::Button(const std::string & filename) {
    texture.loadFromFile(filename);

    sprite.setTexture(texture);
}

void Button::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void Button::render() {
    RenderingSingleton::getInstance().getRenderWindow()->draw(sprite);
}

bool Button::mouseReleased(const sf::Vector2i & mousePosition) {
    return sprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y);
}